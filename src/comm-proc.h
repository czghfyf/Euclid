#ifndef __EUCLID_COMM_PROC_H__
#define __EUCLID_COMM_PROC_H__

typedef struct euclid_command {
	char *mem_addr;
	unsigned int data_pkg_capacity;
	unsigned short command_type;
	char *command;
	unsigned int command_length;
} eCommand;

eCommand *convert_to_command(char *mem_addr);

eCommand *plan_exe_command(eCommand *ec);

void process_command(char *command_stat);

#endif
