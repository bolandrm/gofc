GEN_DIR=.build
BIN=gofc

.PHONY: all clean

all: $(GEN_DIR)/$(BIN)

build-compiler:
	docker build -t gofc-builder .

GO_FILES:=$(shell find . -name "*.go" -print)
C_FILES:=$(shell find . -name "*.c" -print)
$(GEN_DIR)/$(BIN): $(GO_FILES) $(C_FILES)
	docker run -it -v $(shell pwd):/go/src/github.com/bolandrm/gofc gofc-builder make build

push: $(GEN_DIR)/$(BIN)
	scp .build/gofc .build/pru0/pru0_data.bin .build/pru0/pru0_text.bin .build/pru1/pru1_data.bin .build/pru1/pru1_text.bin config-pins.sh root@bbe:~/gofc/

build:
	make -C src/pru_loader
	make -C src/pid_pru0
	make -C src/rc_pru1
	go build -o .build/gofc

#clean:
#	rm -r .build/*
