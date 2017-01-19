#ifndef PID_PRU_MPU_H
#define PID_PRU_MPU_H

#include <stdint.h>
#include "shared_headers/types.h"

#define MPU_WHOAMI_IDENTIFIER 0x68

#define MPU_I2C_ADDRESS 0x68
#define MPU_GYRO_500D_SENS 65.5
#define MPU_GYRO_1000D_SENS 32.77
#define MPU_ACCEL_4G_SENS 8192.0

// MPU 6000 registers
#define MPU_REG_WHOAMI         0x75
#define MPU_REG_SMPLRT_DIV     0x19
#define MPU_REG_CONFIG         0x1A
#define MPU_REG_GYRO_CONFIG    0x1B
#define MPU_REG_ACCEL_CONFIG   0x1C
#define MPU_REG_FIFO_EN        0x23
#define MPU_REG_INT_PIN_CFG    0x37
#define MPU_REG_INT_ENABLE     0x38
#define MPU_REG_INT_STATUS     0x3A
#define MPU_REG_ACCEL_XOUT_H   0x3B
#define MPU_REG_ACCEL_XOUT_L   0x3C
#define MPU_REG_ACCEL_YOUT_H   0x3D
#define MPU_REG_ACCEL_YOUT_L   0x3E
#define MPU_REG_ACCEL_ZOUT_H   0x3F
#define MPU_REG_ACCEL_ZOUT_L   0x40
#define MPU_REG_TEMP_OUT_H     0x41
#define MPU_REG_TEMP_OUT_L     0x42
#define MPU_REG_GYRO_XOUT_H    0x43
#define MPU_REG_GYRO_XOUT_L    0x44
#define MPU_REG_GYRO_YOUT_H    0x45
#define MPU_REG_GYRO_YOUT_L    0x46
#define MPU_REG_GYRO_ZOUT_H    0x47
#define MPU_REG_GYRO_ZOUT_L    0x48
#define MPU_REG_USER_CTRL      0x6A
#define MPU_REG_PWR_MGMT_1     0x6B
#define MPU_REG_PWR_MGMT_2     0x6C
#define MPU_REG_FIFO_COUNTH    0x72
#define MPU_REG_FIFO_COUNTL    0x73
#define MPU_REG_FIFO_R_W       0x74

// Configuration bits
#define BIT_SLEEP                   0x40
#define BIT_H_RESET                 0x80
#define BITS_CLKSEL                 0x07
#define MPU_CLK_SEL_PLLGYROX        0x01
#define MPU_CLK_SEL_PLLGYROZ        0x03
#define MPU_EXT_SYNC_GYROX          0x02
#define BITS_FS_250DPS              0x00
#define BITS_FS_500DPS              0x08
#define BITS_FS_1000DPS             0x10
#define BITS_FS_2000DPS             0x18
#define BITS_FS_MASK                0x18
#define BITS_DLPF_CFG_256HZ_NOLPF2  0x00
#define BITS_DLPF_CFG_188HZ         0x01
#define BITS_DLPF_CFG_98HZ          0x02
#define BITS_DLPF_CFG_42HZ          0x03
#define BITS_DLPF_CFG_20HZ          0x04
#define BITS_DLPF_CFG_10HZ          0x05
#define BITS_DLPF_CFG_5HZ           0x06
#define BITS_DLPF_CFG_2100HZ_NOLPF  0x07
#define BITS_DLPF_CFG_MASK          0x07
#define BIT_INT_ANYRD_2CLEAR        0x10
#define BIT_RAW_RDY_EN              0x01
#define BIT_I2C_IF_DIS              0x10
#define BIT_INT_STATUS_DATA         0x01

uint8_t mpu_init();
void mpu_read_gyro(axis_int16_t *gyro_rates);
void mpu_read_accel(axis_int16_t *accel_raws);

#endif
