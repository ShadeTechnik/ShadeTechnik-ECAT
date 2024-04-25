#include "main.h"
#include "misc.h"

/* user defined */
extern enum Result lan9252_readwrite_user(void* rx, const void* tx, int len);

/* peak lazy */
#define _rw(RX_, TX_, N_) lan9252_readwrite_user(RX_, TX_, N_)
#define _rw_arr(RX_, TX_) lan9252_readwrite_user(RX_, TX_, array_len_(RX_))
/* a pointer would be dubious here */
#define _rw_var(RX_, TX_) lan9252_readwrite_user(RX_, TX_, sizeof(*(RX_)))

enum Registers {
	ECAT_PRAM_RD_DATA     = 0x0000,
	ECAT_PRAM_WR_DATA     = 0x0020,
	ID_REV                = 0x0050,
	IRQ_CFG               = 0x0054,
	IRQ_STS               = 0x0058,
	INT_EN                = 0x005c,
	BYTE_TEST             = 0x0064,
	HW_CFG                = 0x0074,
	PMT_CTRL              = 0x0084,
	GPT_CFG               = 0x008c,
	GPT_CNT               = 0x0090,
	FREE_RUN              = 0x009c,
	RESET_CTL             = 0x01f8,
	ECAT_CSR_DATA         = 0X0300,
	ECAT_CSR_CMD          = 0x0304,
	ECAT_PRAM_RD_ADDR_LEN = 0x0308,
	ECAT_PRAM_RD_CMD      = 0x030c,
	ECAT_PRAM_WR_ADDR_LEN = 0x0310,
	ECAT_PRAM_WR_CMD      = 0x0314,
};

enum Instructions {
	EQIO     = 0x38, /* enable sqi */
	RSTQIO   = 0xff, /* reset sqi */

	READ     = 0x03, /* up to 30 mhz */
	FASTREAD = 0x0b, /* up to 80 mhz */
	SDOR     = 0x3b, /* dual output read */
	SDIOR    = 0xbb, /* dual io read */
	SQOR     = 0x6b, /* quad output read */
	SQIOR    = 0xeb, /* quad io read */

	WRITE    = 0x02,
	SDDW     = 0x32, /* dual data write */
	SDADW    = 0xb2, /* dual address write */
	SQDW     = 0x62, /* quad data write */
	SQADW    = 0xe2, /* quad address write */
};

#define BYTE_TEST_GOOD    0x87654321
#define BYTE_TEST_GOOD_BE big_endian32_(BYTE_TEST_GOOD)

enum Lan9252_Byte_Order {
	Lan9252_Endian_Undefined,
	Lan9252_Endian_Little,
	Lan9252_Endian_Big,
};

enum Lan9252_Byte_Order
lan9252_byte_test(void) {
	u32 byte_test = 0;
	u32 dummy     = 0;
	if (_rw_var(&byte_test, &dummy) == Fail) { return Lan9252_Endian_Undefined; }

	if (byte_test == BYTE_TEST_GOOD) { return Lan9252_Endian_Little; }
	if (byte_test == BYTE_TEST_GOOD_BE) { return Lan9252_Endian_Big; }
	return Lan9252_Endian_Undefined;
}

int
lan9252_wait_for_idle(void) {
	int i = 0;
	for (; i < 32; i += 1) {
		if (lan9252_byte_test() != Lan9252_Endian_Undefined) { break; }
	}
	return i;
}

enum Result
lan9252_init(void) {
	lan9252_wait_for_idle();
	return Okay;
}

int
lan9252_read(u32 addr, void* buf, int buflen) {
	return 0;
}

int
lan9252_write(u32 addr, const void* data, int len) {
	return 0;
}
