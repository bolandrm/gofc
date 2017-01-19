#ifndef SHARED_HEADERS_TYPES_H
#define SHARED_HEADERS_TYPES_H

// make sure this is 32 bit aligned... pack/align directives are not working
typedef struct {
  uint32_t rc_values[6];
  uint32_t iep_started;
  uint32_t debug[10];
} shared_mem_t;

typedef struct {
  int16_t x, y, z;
} axis_int16_t;

#endif
