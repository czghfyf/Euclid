#ifndef _EUCLID_OAE__CFG_H_
#define _EUCLID_OAE__CFG_H_ 1

struct config {
	int port;
};

struct config *get_cfg();

int init_cfg(int argc, char *argv[]);

#endif

