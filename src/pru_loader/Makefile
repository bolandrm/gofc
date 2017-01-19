GEN_DIR=../../.build

ARCHIVE=pru_loader.a
OBJ=pru_loader.o

LDFLAGS +=
CFLAGS ?= -O2 -Wall -Wextra -Wno-unused-parameter

.PHONY: all clean

all: $(GEN_DIR)/$(ARCHIVE)

$(GEN_DIR)/$(OBJ): *.c
	@mkdir -p $(GEN_DIR)
	#$(CC) -shared -fPIC -O3 -std=c99 -finline-functions -Wall -Wmissing-prototypes -I. -I.. -lprussdrv -o $@ pru_loader.c
	$(CC) -c -O3 -std=c99 -finline-functions -Wall -Wmissing-prototypes -I. -I.. -o $@ pru_loader.c

$(GEN_DIR)/$(ARCHIVE): $(GEN_DIR)/$(OBJ)
	$(AR) rcs $(GEN_DIR)/$(ARCHIVE) $(GEN_DIR)/$(OBJ)

clean:
	rm $(GEN_DIR)/$(ARCHIVE)
	rm $(GEN_DIR)/$(OBJ)
