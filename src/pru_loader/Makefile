GEN_DIR=../../.build

ARCHIVE=libpruloader.a
OBJ=pru_loader.o

.PHONY: all clean

all: $(GEN_DIR)/$(ARCHIVE) 

$(GEN_DIR)/$(OBJ): *.c *.h ../shared_headers/*.h
	@mkdir -p $(GEN_DIR)
	$(CC) -c -fPIC -O3 -std=c99 -finline-functions -Wall -Wmissing-prototypes -I. -I.. -lprussdrv -o $@ pru_loader.c
	$(info building libpruloader.a)

$(GEN_DIR)/$(ARCHIVE): $(GEN_DIR)/$(OBJ)
	$(AR) -rcs $(GEN_DIR)/$(ARCHIVE) $(GEN_DIR)/$(OBJ)

clean:
	rm $(GEN_DIR)/$(ARCHIVE)
	rm $(GEN_DIR)/$(OBJ)
