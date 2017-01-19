package pru

import "fmt"

// #cgo CFLAGS: -I/Users/bolandrm/www/gowork/src/github.com/bolandrm/gofc/src
// #cgo LDFLAGS: /Users/bolandrm/www/gowork/src/github.com/bolandrm/gofc/.build/pru_loader.a
// #include <pru_loader/pru_loader.h>
// import "C"

func Load() {
	fmt.Printf("Invoking c library...\n")
	//C.test()
	fmt.Println("Done")
}
