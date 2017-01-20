package fc

import (
	"fmt"
	"github.com/bolandrm/gofc/fc/pru"
	"time"
)

func Initialize() {
	pru.Load()

	rcData := make([]uint32, 4)
	for {
		pru.UpdateRC(rcData)
		fmt.Printf("RC values: %v \n", rcData)
		time.Sleep(1 * time.Second)
	}
}
