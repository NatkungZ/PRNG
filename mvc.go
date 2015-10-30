package main

import (
	//"bufio"
	//"fmt"
	//"io/ioutil"
	"math/rand"
	//"os"
	"log"
	//"reflect"
	"time"
)

const CMWC_CYCLE = 4096
const CMWC_C_MAX = 809430660

var Q [CMWC_CYCLE]uint32
var c uint32 = 362436

func check(e error) {
	if e != nil {
		panic(e)
	}
}
func rand32() uint32 {
	var result uint32 = 0
	result = rand.Uint32()
	result <<= 16
	result |= rand.Uint32()
	return result
}
func initCMWC() {
	rand.Seed(time.Now().UTC().UnixNano())
	for i := 0; i < CMWC_CYCLE; i++ {
		Q[i] = rand32()
	}
	for {
		c = rand32()
		if c >= CMWC_C_MAX {
			break
		}
	}
}
func randCMWC() uint32 {
	var i uint32 = CMWC_CYCLE - 1
	var t uint32 = 0
	var a uint32 = 18782
	var r uint32 = 0xfffffffe
	var x uint32 = 0

	i = (i + 1) & (CMWC_CYCLE - 1)
	t = a*Q[i] + c
	c = t >> 32
	x = t + c
	if x < c {
		x++
		c++
	}
	Q[i] = r - x
	return Q[i]
}

func main() {
	// fmt.Println(reflect.TypeOf(Q))
	// fmt.Println(reflect.TypeOf(c))
	// fmt.Println(c)
	// fmt.Println(rand32())

	initCMWC()
	// fmt.Printf("Random CMWC: %u\n", randCMWC())
	// fmt.Printf("Random CMWC: %u\n", randCMWC())
	// fmt.Printf("Random CMWC: %u\n", randCMWC())
	// fmt.Printf("Random CMWC: %u\n", randCMWC())
	// fmt.Printf("Random CMWC: %u\n", randCMWC())

	log.SetFlags(0)
	//log.Println(randCMWC())
	for i := 0; i < 1000; i++ {
		log.Println(randCMWC())
	}

	//count := 10000000
	/*for i := 0; i < count; i++ {
		fmt.Printf("Random CMWC: %u\n", randCMWC())
	}*/

}
