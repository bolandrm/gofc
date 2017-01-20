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
	scp .build/gofc root@bbe:~/gofc

build:
	make -C src/pru_loader
	go build -o .build/gofc
