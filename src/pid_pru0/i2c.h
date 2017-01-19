#ifndef PID_PRU_I2C_H
#define PID_PRU_I2C_H

#include <stdint.h>
#include "shared_headers/macros.h"

#define CM_PER_I2C1_CLKCTRL ADDRESS(0x44E00048)
#define I2C1_BASE_ADR 0x4802A000
#define I2C1_PSC ADDRESS(I2C1_BASE_ADR + 0xB0)
#define I2C1_SCLL ADDRESS(I2C1_BASE_ADR + 0xB4)
#define I2C1_SCLH ADDRESS(I2C1_BASE_ADR + 0xB8)
#define I2C1_CON ADDRESS(I2C1_BASE_ADR + 0xA4)
#define I2C1_CNT ADDRESS(I2C1_BASE_ADR + 0x98)
#define I2C1_DATA ADDRESS(I2C1_BASE_ADR + 0x9C)
#define I2C1_STATUS_RAW ADDRESS(I2C1_BASE_ADR + 0x24)
#define I2C1_SLAVE_ADDRESS ADDRESS(I2C1_BASE_ADR + 0xAC)
#define I2C1_SYSC ADDRESS(I2C1_BASE_ADR + 0x10)
#define I2C1_SYSS ADDRESS(I2C1_BASE_ADR + 0x90)

#define CM_PER_I2C1_CLOCK_ENABLE 0x2
#define CM_PER_I2C1_CLOCK_DISABLED 0x00030000
#define I2C_EN 0x8000
#define I2C_MASTER 0x400
#define I2C_CMD_TRX_BIT 9
#define I2C_CMD_START 0x1
#define I2C_CMD_RX 0x0
#define I2C_CMD_TX 0x200
#define I2C_CMD_STOP 0x2
#define I2C_CMD_STOP_BIT 1
#define I2C_BUS_BUSY_BIT 12
#define I2C_SRST 0x02
#define I2C_RESET_DONE_BIT 0

#define I2C_FCLK_RATE 48000000
#define I2C_DESIRED_INTERNAL_CLK_RATE 12000000
#define I2C_TRANSFER_RATE_BPS 400000

void i2c_init();
void i2c_start_transfer(uint8_t device_adddress);
void i2c_write(uint8_t data);
void i2c_end_transfer();
void i2c_request_from(uint8_t device_adddress, uint32_t data_size);
uint8_t i2c_read();

#endif
