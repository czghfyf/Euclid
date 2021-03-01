#ifndef _VCE_LOG___H_

#define _VCE_LOG___H_ 1

int vce_log_init();

int log_(const char *fmt, ...);
int logD(const char *fmt, ...); // debug
int logI(const char *fmt, ...); // info
int logW(const char *fmt, ...); // warn
int logE(const char *fmt, ...); // error

#endif
