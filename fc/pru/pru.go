package pru

/*
#cgo CFLAGS: -I${SRCDIR}/../../src/pru_loader
#cgo LDFLAGS: -L${SRCDIR}/../../.build -lpruloader -lprussdrv
#include <stdlib.h>
#include <stdint.h>
#include "pru_loader.h"
*/
import "C"

import (
	"fmt"
	"math"
	"os/exec"
	"unsafe"
)

const basePath = "/root/gofc"

func Load() {
	fmt.Println("PRU setup...")

	if cmdout, err := exec.Command(fmt.Sprintf("%v/config-pins.sh", basePath)).Output(); err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(string(cmdout))
	}

	loadPru(0)
	loadPru(1)

	fmt.Println("Done")
}

func UpdateRC(data []uint32) {
	C.ReadRCValues((*C.uint32_t)(&data[0]))

	for i, val := range data {
		scaledVal := float64(val) * 0.005
		data[i] = uint32(math.Ceil(scaledVal - 0.5))
	}
}

func UpdateDebug(data []uint32) {
	C.UpdateDebug((*C.uint32_t)(&data[0]))
}

func UpdateMpuData(data []int32) {
	C.ReadMpuData((*C.int32_t)(&data[0]))
}

func loadPru(pruNum int) {
	text := C.CString(fmt.Sprintf("%v/pru%v_text.bin", basePath, pruNum))
	defer C.free(unsafe.Pointer(text))

	data := C.CString(fmt.Sprintf("%v/pru%v_data.bin", basePath, pruNum))
	defer C.free(unsafe.Pointer(data))

	C.LoadPRU(C.int(pruNum), text, data)
}
