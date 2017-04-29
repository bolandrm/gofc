#ifndef SHARED_HEADERS_TYPES_H
#define SHARED_HEADERS_TYPES_H

typedef struct {
  int32_t x, y, z;
} axis_int32_t;

typedef struct {
  uint32_t rc_values[6];
  uint32_t iep_started;
  uint32_t debug[10];
  axis_int32_t gyro;
} shared_mem_t;

#endif
