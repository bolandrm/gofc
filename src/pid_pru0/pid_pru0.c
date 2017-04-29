#include <stdint.h>
#include <pru_cfg.h>
#include <pru_iep.h>
#include "shared_headers/types.h"
#include "shared_headers/macros.h"
#include "i2c.h"
#include "mpu.h"

volatile shared_mem_t *shared_mem = (shared_mem_t *) 0x00010000;

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void init();

void main(void) {
  init();

  axis_int32_t gyro_data;

  while(1) {
    mpu_read_gyro(&shared_mem->gyro);

    shared_mem->debug[0] = ((CM_PER_I2C1_CLKCTRL >> 16) & 0x03);
    shared_mem->debug[1] = 10125;
    shared_mem->debug[2] = ++shared_mem->debug[2];
    shared_mem->debug[3] = 0;
    shared_mem->debug[4] = I2C1_CON;
    shared_mem->debug[5] = CM_PER_I2C1_CLKCTRL;

    __delay_cycles(100 * MILLIS_TO_CYCLES);
  }
}

void init() {
  shared_mem->debug[0] = 0;
  shared_mem->debug[1] = 0;
  shared_mem->debug[2] = 0;
  shared_mem->debug[3] = 0;
  shared_mem->debug[4] = 0;
  shared_mem->debug[5] = 0;

	// Clear SYSCFG[STANDBY_INIT] to enable OCP master port
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

  i2c_init();
  if (!mpu_init()) {
    shared_mem->debug[0] = 100;
    while(1);
  }
}
