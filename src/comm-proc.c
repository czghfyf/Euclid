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

