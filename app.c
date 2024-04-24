#include "soes/ecat_slv.h"

/* BUILD */
#include "hooks.c"
#include "lan9252.c"
/**/

static esc_cfg_t _cfg = {
  .user_arg                    = NULL,
  .use_interrupt               = 0,
  .watchdog_cnt                = 0,
  .skip_default_initialization = false,
  .set_defaults_hook           = NULL,
  .pre_state_change_hook       = NULL,
  .post_state_change_hook      = NULL,
  .application_hook            = NULL,
  .safeoutput_override         = NULL,
  .pre_object_download_hook    = NULL,
  .post_object_download_hook   = NULL,
  .pre_object_upload_hook      = NULL,
  .post_object_upload_hook     = NULL,
  .rxpdo_override              = NULL,
  .txpdo_override              = NULL,
  .esc_hw_interrupt_enable     = NULL,
  .esc_hw_interrupt_disable    = NULL,
  .esc_hw_eep_handler          = NULL,
  .esc_check_dc_handler        = NULL,
  .get_device_id               = NULL,
};

void
setup(void) {
	ecat_slv_init(&_cfg);
}

void
loop(void) {
	ecat_slv_poll();
	DIG_process(DIG_PROCESS_WD_FLAG);
}
