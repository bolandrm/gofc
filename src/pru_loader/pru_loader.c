#include "pru_loader.h"
#include <stdio.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include "shared_headers/types.h"

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
}

void ReadMpuData(int32_t *data) {
  volatile shared_mem_t *shared_mem;
  prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, (void **) &shared_mem);

  data[0] = shared_mem->gyro.x;
  data[1] = shared_mem->gyro.y;
  data[2] = shared_mem->gyro.z;
}
