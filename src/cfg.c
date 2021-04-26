#include "cfg.h"

static struct config cfg = { 8766 };

struct config *get_cfg()
{
	return &cfg;
}
