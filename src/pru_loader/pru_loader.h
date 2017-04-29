#include <stdint.h>

void LoadPRU(int pru, char *text_file, char *data_file);
void ReadRCValues(uint32_t *data);
void ReadMpuData(int32_t *data);
void UpdateDebug(uint32_t *data);
