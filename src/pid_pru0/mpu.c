#include "i2c.h"
#include "mpu.h"
#include "shared_headers/macros.h"

void mpu_write_reg(uint16_t addr, uint8_t data) {
  i2c_start_transfer(MPU_I2C_ADDRESS);
  i2c_write(addr);
  i2c_write(data);
  i2c_end_transfer();
  __delay_cycles(1 * MILLIS_TO_CYCLES);
}

uint8_t mpu_read_byte(uint16_t addr) {
  i2c_start_transfer(MPU_I2C_ADDRESS);
  i2c_write(MPU_REG_WHOAMI);
  i2c_end_transfer();
  i2c_request_from(MPU_I2C_ADDRESS, 1);
  return i2c_read();
}

uint16_t mpu_read_word(uint16_t addr) {
  i2c_start_transfer(MPU_I2C_ADDRESS);
  i2c_write(MPU_REG_WHOAMI);
  i2c_end_transfer();
  i2c_request_from(MPU_I2C_ADDRESS, 2);
  return (i2c_read() << 8) | i2c_read();
}

void mpu_read_gyro(axis_int16_t *gyro_rates) {
  int16_t gyro_x = mpu_read_word(MPU_REG_GYRO_XOUT_H);
  int16_t gyro_y = mpu_read_word(MPU_REG_GYRO_YOUT_H);
  int16_t gyro_z = mpu_read_word(MPU_REG_GYRO_ZOUT_H);

  gyro_rates->x = gyro_y;
  gyro_rates->y = -1 * gyro_x;
  gyro_rates->z = -1 * gyro_z;
}

void mpu_read_accel(axis_int16_t *accel_raws) {
  int16_t accel_x = mpu_read_word(MPU_REG_ACCEL_XOUT_H);
  int16_t accel_y = mpu_read_word(MPU_REG_ACCEL_YOUT_H);
  int16_t accel_z = mpu_read_word(MPU_REG_ACCEL_ZOUT_H);

  accel_raws->x = accel_y;
  accel_raws->y = -1 * accel_x;
  accel_raws->z = accel_z;
}

uint8_t mpu_init() {
  mpu_write_reg(MPU_REG_PWR_MGMT_1, BIT_H_RESET);
  __delay_cycles(100 * MILLIS_TO_CYCLES);

  // Wake Up device and select GyroZ clock (better performance)
  mpu_write_reg(MPU_REG_PWR_MGMT_1, MPU_CLK_SEL_PLLGYROZ);
  mpu_write_reg(MPU_REG_PWR_MGMT_2, 0);

  mpu_write_reg(MPU_REG_SMPLRT_DIV, 0x00);     // Sample rate = 1kHz
  mpu_write_reg(MPU_REG_INT_ENABLE, 0x01);     // Enable data ready interrupt

  // FS & DLPF   FS=1000º/s, DLPF = 42Hz (low pass filter)
  mpu_write_reg(MPU_REG_CONFIG, BITS_DLPF_CFG_188HZ);
  mpu_write_reg(MPU_REG_GYRO_CONFIG, BITS_FS_1000DPS);  // Gyro scale 1000º/s
  mpu_write_reg(MPU_REG_ACCEL_CONFIG, 0x08);   // Accel scale +-4g

  return mpu_read_byte(MPU_REG_WHOAMI) == MPU_WHOAMI_IDENTIFIER;
}
