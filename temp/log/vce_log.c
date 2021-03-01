// #include <arpa/inet.h>
// #include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

// #include "vce_common.h"
#include "vce_log.h"
#include "vce_cfg.h"

extern struct vce_cfg_stct vce_cfg_instance;

static FILE *log_f;

static int vlog(const char *log_level, const char *fmt, va_list ap);

int vce_log_init()
{
	log_f = fopen(vce_cfg_instance.log_file, "a");
	return 0;
}

int log_(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vlog(NULL, fmt, ap);
	va_end(ap);
	return 0;
}

int logD(const char *fmt, ...) // debug
{
	va_list ap;
	va_start(ap, fmt);
	vlog("DEBUG", fmt, ap);
	va_end(ap);
	return 0;
}

int logI(const char *fmt, ...) // info
{
	va_list ap;
	va_start(ap, fmt);
	vlog("INFO ", fmt, ap);
	va_end(ap);
	return 0;
}

int logW(const char *fmt, ...) // warn
{
	va_list ap;
	va_start(ap, fmt);
	vlog("WARN ", fmt, ap);
	va_end(ap);
	return 0;
}

int logE(const char *fmt, ...) // error
{
	va_list ap;
	va_start(ap, fmt);
	vlog("ERROR", fmt, ap);
	va_end(ap);
	return 0;
}

static int vlog(const char *log_level, const char *fmt, va_list ap)
{
	time_t _now_time_ = time(NULL);

	// This structure memory space is automatically allocated and managed by the operating system.
	// Do not take the initiative to release. Do not call the 'free(_now_tm_)' function.
	struct tm *_now_tm_ = localtime(&_now_time_);

	fprintf(log_f, "%d-%02d-%02d %02d:%02d:%02d ",
			_now_tm_ -> tm_year + 1900,
			_now_tm_ -> tm_mon + 1,
			_now_tm_ -> tm_mday,
			_now_tm_ -> tm_hour,
			_now_tm_ -> tm_min,
			_now_tm_ -> tm_sec);

	if (log_level != NULL)
		fprintf(log_f, "[%s] ", log_level);

	vfprintf(log_f, fmt, ap);
	fprintf(log_f, "\n");
	fflush(log_f);
	return 0;
}
