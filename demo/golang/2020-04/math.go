package main

import (
	"fmt"
	"math"
)

func main() {
	fmt.Printf("%.1f", math.Log2(100))//6.6
	fmt.Println(" ")
	//亿100000000
	fmt.Printf("%.1f", math.Log10(100000000))//8
	fmt.Printf("%.1f", math.Log2(100000000))//32

}


// - func Cbrt(x float64) float64 // 立方根函数
// - func Pow(x, y float64) float64  // x 的幂函数
// - func Pow10(e int) float64 // 10 根的幂函数
// - func Sqrt(x float64) float64 // 平方根
// - func Log(x float64) float64 // 对数函数
// - func Log10(x float64) float64 // 10 为底的对数函数
// - func Log2(x float64) float64  // 2 为底的对数函数
// - func Log1p(x float64) float64 // log(1 + x)
// - func Logb(x float64) float64 // 相当于 log2(x) 的绝对值
// - func Ilogb(x float64) int // 相当于 log2(x) 的绝对值的整数部分
// - func Exp(x float64) float64 // 指数函数
// - func Exp2(x float64) float64 // 2 为底的指数函数
// - func Expm1(x float64) float64 // Exp(x) - 1