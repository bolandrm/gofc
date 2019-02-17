#include "pru_loader.h"
#include <stdio.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include "shared_headers/types.h"
#include <string.h>

void LoadPRU(int pru, char *text_file, char *data_file) {
  prussdrv_init();
  if (prussdrv_open(PRU_EVTOUT_0) == -1) {
    printf("prussdrv_open() failed\n");
  }

  tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
  prussdrv_pruintc_init(&pruss_intc_initdata);

  if (prussdrv_load_datafile(pru, data_file) < 0) {
    fprintf(stderr, "Error loading %s\n", data_file);
  } else {
    printf("Data file loaded\n");
  }

  if (prussdrv_exec_program(pru, text_file) < 0) {
    fprintf(stderr, "Error loading %s\n", text_file);
  }
}

int pop_debug_buffer(volatile shared_mem_t *sm, char *data) {
    int32_t next;

    // if the head == tail, we don't have any data
    if (sm->debug_buffer_head == sm->debug_buffer_tail) {
      return -1;
    }

    // next is where tail will point to after this read.
    next = sm->debug_buffer_tail + 1;
    if (next >= sm->debug_buffer_maxlen) {
      next = 0;
    }

    strcpy(data, sm->debug_buffer[sm->debug_buffer_tail]);
    sm->debug_buffer_tail = next; // tail to next offset.
    return 0;  // return success to indicate successful pop.
}

void ReadRCValues(uint32_t *data) {
  volatile shared_mem_t *shared_mem;
  prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, (void **) &shared_mem);

  data[0] = shared_mem->rc_values[0];
  data[1] = shared_mem->rc_values[1];
  data[2] = shared_mem->rc_values[2];
  data[3] = shared_mem->rc_values[3];
}

void UpdateDebug(uint32_t *data) {
  volatile shared_mem_t *shared_mem;
  prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, (void **) &shared_mem);

  data[0] = shared_mem->debug[0];
  data[1] = shared_mem->debug[1];
  data[2] = shared_mem->debug[2];
  data[3] = shared_mem->debug[3];
  data[4] = shared_mem->debug[4];
  data[5] = shared_mem->debug[5];

  char line[1000] = {0};
  int pop;

  while((pop = pop_debug_buffer(shared_mem, line)) != -1) {
    printf("====> [PRU LOG] %s\n", line);
  }
}

void ReadMpuData(int32_t *data) {
  volatile shared_mem_t *shared_mem;
  prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, (void **) &shared_mem);

  data[0] = shared_mem->gyro.x;
  data[1] = shared_mem->gyro.y;
  data[2] = shared_mem->gyro.z;
}
