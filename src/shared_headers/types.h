#ifndef SHARED_HEADERS_TYPES_H
#define SHARED_HEADERS_TYPES_H

#define LOG_BUFFER_LEN 100
#define LOG_BUFFER_ENTRY_LEN 30

typedef struct __attribute__((__packed__)) {
  int32_t x, y, z;
} axis_int32_t;

typedef struct __attribute__((__packed__)) {
  uint32_t rc_values[6];
  uint32_t iep_started;
  uint32_t debug[10];
  axis_int32_t gyro;

  uint32_t debug_buffer_head;
  uint32_t debug_buffer_tail;

  char debug_buffer[LOG_BUFFER_LEN][LOG_BUFFER_ENTRY_LEN];

  uint32_t debug_buffer_maxlen;
} shared_mem_t;

#endif
