#include <stdint.h>
#include <pru_cfg.h>
#include <pru_iep.h>
#include <string.h>
#include "mini-printf.h"
#include "shared_headers/types.h"
#include "shared_headers/macros.h"
#include "i2c.h"
#include "mpu.h"

volatile shared_mem_t *shared_mem = (shared_mem_t *) 0x00010000;

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void init();
void init_debug_buffer();
int push_debug_buffer(volatile shared_mem_t*, char *);

#define LOG(f_) push_debug_buffer(shared_mem, (f_));

#define LOGV(f_, ...) {\
  char log_entry[LOG_BUFFER_ENTRY_LEN];\
  mini_snprintf(log_entry, LOG_BUFFER_ENTRY_LEN, (f_), __VA_ARGS__);\
  log_entry[LOG_BUFFER_ENTRY_LEN - 1] = '\0';\
  push_debug_buffer(shared_mem, log_entry);\
}

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
  init_debug_buffer();
  LOG("initializing PID PRU");

  int n = 0;
  while (n < 5) {
    n += 1;
    LOGV("writing #%d", n);
  }

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
    LOG("failed to initialize MPU");
    while(1);
  }
}

void init_debug_buffer() {
  shared_mem->debug_buffer_maxlen = LOG_BUFFER_LEN;
  shared_mem->debug_buffer_head = 0;
  shared_mem->debug_buffer_tail = 0;
}

int push_debug_buffer(volatile shared_mem_t *sm, char *data) {
    int32_t next;

    // next is where head will point to after this write.
    next = sm->debug_buffer_head + 1;

    if (next >= sm->debug_buffer_maxlen) {
      next = 0;
    }

    // if the head + 1 == tail, circular buffer is full
    if (next == sm->debug_buffer_tail) {
      return -1;
    }

    strncpy(sm->debug_buffer[sm->debug_buffer_head], data, LOG_BUFFER_ENTRY_LEN);  // Load data and then move
    sm->debug_buffer[sm->debug_buffer_head][LOG_BUFFER_ENTRY_LEN - 1] = '\0';

    sm->debug_buffer_head = next; // head to next data offset.
    return 0;  // return success to indicate successful push.
}

