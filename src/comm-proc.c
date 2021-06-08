#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comm-proc.h"

extern int scan_comm_stat(const char *cs);
extern void cleanup_yy_str_buff();
extern int yyparse(void);

void init_comm_proc()
{
	// init command_agree
	char *mem_addr = malloc(6);
	memset(mem_addr, 0, 6);
	*((int *) mem_addr) = 6;
	*((short *) (mem_addr + 4)) = CT_AGREE;
	command_agree = convert_to_command(mem_addr);

	// init FIXC_done
	char *fixcDoneMem= malloc(6);
	memset(fixcDoneMem, 0, 6);
	*((int *) fixcDoneMem) = 6;
	*((short *) (fixcDoneMem + 4)) = FIXC_DONE;
	FIXC_done = convert_to_command(fixcDoneMem);

	// init fixcDisconnect
	char *disconnMem = malloc(6);
	memset(disconnMem, 0, 6);
	*((int *) disconnMem) = 6;
	*((short *) (disconnMem + 4)) = FIXC_DISCONNECT;
	fixcDisconnect = convert_to_command(disconnMem);

	// init fixc_intent_cli
	char * fixc_intent_cli_mem = malloc(8);
       memset(fixc_intent_cli_mem, 0, 8);
	*fixc_intent_cli_mem = 8;
	fixc_intent_cli = convert_to_command(fixc_intent_cli_mem);

	// init fixc_intent_cnode
	char * fixc_intent_cnode_mem = malloc(8);
       memset(fixc_intent_cnode_mem, 0, 8);
	*fixc_intent_cnode_mem= 8;
	*(fixc_intent_cnode_mem + 6) = 1;
	fixc_intent_cnode= convert_to_command(fixc_intent_cnode_mem);
}

void freeCommand(eCommand *cp)
{
	free(cp -> mem_addr);
	free(cp);
}

eCommand *convert_to_command(char *m_addr)
{
	eCommand *p = (eCommand *)malloc(sizeof(eCommand));
	if (p == NULL)
		return p;

	int u_int_s = sizeof(unsigned int);
	int u_short_s = sizeof(unsigned short);

	p -> mem_addr = m_addr;
	p -> data_pkg_capacity = *((unsigned int *) m_addr);
	p -> command_type = *((unsigned short *) (m_addr + u_int_s));
	p -> command = m_addr + u_int_s + u_short_s;
	p -> command_length = p -> data_pkg_capacity - u_int_s - u_short_s;

	return p;
}

eCommand *plan_exe_command(eCommand *ec)
{
	// TODO
	return NULL;
}


void process_command(char *command_stat)
{
	// TODO
	printf("processing:\n%s\n", command_stat);

	scan_comm_stat(command_stat);

	free(command_stat);

	yyparse();
	cleanup_yy_str_buff();

}

