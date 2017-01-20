package pru

import "fmt"

/*
#cgo CFLAGS: -I${SRCDIR}/../src/pru_loader
#cgo LDFLAGS: -L${SRCDIR}/../.build -lpruloader -lprussdrv
#include "pru_loader.h"
*/
import "C"

func Load() {
	fmt.Printf("Invoking c2 library...\n")
	C.test()
	fmt.Println("Done")
}

// #cgo CFLAGS: -I/Users/bolandrm/www/gowork/src/github.com/bolandrm/gofc/src
