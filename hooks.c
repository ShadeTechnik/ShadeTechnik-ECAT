#include "misc.h"
#include "soes/esc.h"
#include "soes/ecat_slv.h"

#define SDO_OBJECT_COUNT 16
const _objectlist SDOobjects[SDO_OBJECT_COUNT];

void
ESC_init(const esc_cfg_t* cfg) {
	(void)cfg;
}

void
ESC_reset(void) { }

void
ESC_read(u16 addr, void* buf, u16 n) { }

void
ESC_write(u16 addr, void* data, u16 n) { }

void
cb_get_inputs(void) { }

void
cb_set_outputs(void) { }
