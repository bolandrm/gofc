package main

import (
	"fmt"
	"github.com/bolandrm/gofc/fc"
	"github.com/bolandrm/gofc/pru"
	"time"
)

func main() {
	fmt.Println("vim-go")
	fc.Tester()
	pru.Load()

	rcData := make([]uint32, 4)
	for {
		pru.UpdateRC(rcData)
		fmt.Printf("RC values: %v \n", rcData)
		time.Sleep(1 * time.Second)
	}
}
