GEN_DIR=../../.build

ARCHIVE=libpruloader.a
OBJ=pru_loader.o
#PRU_LIB=libprussdrv.a

.PHONY: all clean

all: $(GEN_DIR)/$(ARCHIVE) 
#$(GEN_DIR)/$(PRU_LIB)

$(GEN_DIR)/$(OBJ): *.c *.h
	@mkdir -p $(GEN_DIR)
	$(CC) -c -fPIC -O3 -std=c99 -finline-functions -Wall -Wmissing-prototypes -I. -I.. -lprussdrv -o $@ pru_loader.c
	$(info building libpruloader.a)

#$(GEN_DIR)/$(PRU_LIB): libprussdrv.a
#	cp libprussdrv.a $(GEN_DIR)/libprussdrv.a

$(GEN_DIR)/$(ARCHIVE): $(GEN_DIR)/$(OBJ)
	$(AR) -rcs $(GEN_DIR)/$(ARCHIVE) $(GEN_DIR)/$(OBJ)

clean:
	rm $(GEN_DIR)/$(ARCHIVE)
	rm $(GEN_DIR)/$(OBJ)
