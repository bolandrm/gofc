#include "i2c.h"

uint32_t transfer_data_size = 0;

void i2c_init() {
	// Enable clock for I2C1
  CM_PER_I2C1_CLKCTRL |= CM_PER_I2C1_CLOCK_ENABLE;

  // Wait until I2C module's clock is enabled
  while((CM_PER_I2C1_CLKCTRL & CM_PER_I2C1_CLOCK_DISABLED) == CM_PER_I2C1_CLOCK_DISABLED) { __delay_cycles(200); }

  // Reset the I2C module
  I2C1_SYSC |= I2C_SRST;
  I2C1_CON = I2C_EN;
  while(!bit_read(I2C1_SYSS, I2C_RESET_DONE_BIT)) { __delay_cycles(200); }

  // Setup i2c module clock prescaler
  I2C1_PSC = (I2C_FCLK_RATE / I2C_DESIRED_INTERNAL_CLK_RATE) - 1;

  // Set clock low and high durations
  I2C1_SCLL = (I2C_DESIRED_INTERNAL_CLK_RATE / I2C_TRANSFER_RATE_BPS) - 7;
  I2C1_SCLH = (I2C_DESIRED_INTERNAL_CLK_RATE / I2C_TRANSFER_RATE_BPS) - 5;
}

void i2c_start_transfer(uint8_t device_adddress) {
  I2C1_SLAVE_ADDRESS = device_adddress;
  transfer_data_size = 0;
}

void i2c_write(uint8_t data) {
  I2C1_DATA = data;
  transfer_data_size++;
}

void i2c_end_transfer() {
  I2C1_CNT = transfer_data_size;
  while(bit_read(I2C1_STATUS_RAW, I2C_BUS_BUSY_BIT)) { __delay_cycles(200); }
  I2C1_CON = I2C_EN | I2C_MASTER | I2C_CMD_START | I2C_CMD_STOP | I2C_CMD_TX;
  while(bit_read(I2C1_CON, I2C_CMD_STOP_BIT)) { __delay_cycles(200); }
}

void i2c_request_from(uint8_t device_adddress, uint32_t data_size) {
  I2C1_CNT = data_size;
  while(bit_read(I2C1_STATUS_RAW, I2C_BUS_BUSY_BIT)) { __delay_cycles(200); }
  I2C1_CON = I2C_EN | I2C_MASTER | I2C_CMD_START | I2C_CMD_STOP | I2C_CMD_RX;
  while(bit_read(I2C1_CON, I2C_CMD_STOP_BIT)) { __delay_cycles(200); }
}

uint8_t i2c_read() {
  return I2C1_DATA;
}
