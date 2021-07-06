#ifndef __EUCLID_COMM_PROC_H__
#define __EUCLID_COMM_PROC_H__ 1

#define CT_INTENT             0
#define CT_AGREE              1
#define CT_GO_TO_JOIN_CLUSTER 2
#define FIXC_DISCONNECT       3
#define FIXC_DONE             4
#define CREATE_DIMENSION      5
#define CREATE_MEMBER         6

typedef struct euclid_command {
	char *mem_addr;
	unsigned int data_pkg_capacity;
	unsigned short command_type;
	char *command;
	unsigned int command_length;
} eCommand;

eCommand *command_agree;
eCommand *FIXC_done;
eCommand *fixcDisconnect;
eCommand *fixc_intent_cli;
eCommand *fixc_intent_cnode;

void init_comm_proc();

void freeCommand(eCommand *cp);

eCommand *convert_to_command(char *mem_addr);

eCommand *plan_exe_command(eCommand *ec);

void process_command(char *command_stat);

#endif
