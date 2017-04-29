package fc

import (
	"fmt"
	"github.com/bolandrm/gofc/fc/pru"
	"time"
)

func Initialize() {
	pru.Load()

	rcData := make([]uint32, 4)
	debugData := make([]uint32, 6)
	mpuData := make([]int32, 3)

	for {
		pru.UpdateRC(rcData)
		pru.UpdateDebug(debugData)
		pru.UpdateMpuData(mpuData)
		fmt.Printf("RC values: %v \n", rcData)
		fmt.Printf("Debug values: %v \n", debugData)
		fmt.Printf("MPU values: %v \n", mpuData)
		time.Sleep(1 * time.Second)
	}
}
