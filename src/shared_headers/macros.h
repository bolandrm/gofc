#ifndef SHARED_HEADERS_MACROS_H
#define SHARED_HEADERS_MACROS_H

#define bv(bit) (1 << (bit))
#define bit_read(value, bit) (((value) >> (bit)) & 0x01)
#define bit_set(value, bit) ((value) |= bv(bit))
#define bit_clear(value, bit) ((value) &= ~bv(bit))

#define ADDRESS(adr) (*(volatile uint32_t *)(adr))

#define MICROS_TO_CYCLES 200
#define MILLIS_TO_CYCLES (MICROS_TO_CYCLES * 1000)

#endif
