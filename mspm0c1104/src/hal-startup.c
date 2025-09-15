// SPDX-License-Identifier: MIT
//
// Copyright 2025 dgz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the “Software”), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/** @file hal-startup.c Provides startup code for the TI MSPM0C1104. */

#include "mspm0c1104/hal-compiler.h"
#include "mspm0c1104/hal-util.h"

/**
 * @brief Defines the vector table offsets corresponding to exception vectors.
 *
 * @see ARMv6-M Architecture Reference Manual, page 192
 */
enum vec_tbl_off {
	// clang-format off

	VEC_TBL_OFF_SP_main	= 0,
	VEC_TBL_OFF_Reset	= 1,
	VEC_TBL_OFF_NMI		= 2,
	VEC_TBL_OFF_HardFault	= 3,
	VEC_TBL_OFF_SVCall	= 11,
	VEC_TBL_OFF_PendSV	= 14,

	VEC_TBL_OFF_INT_GROUP0	= 16,
	VEC_TBL_OFF_GPIO0	= 17,
	VEC_TBL_OFF_TIMG8	= 18,
	VEC_TBL_OFF_ADC		= 20,
	VEC_TBL_OFF_SPI0	= 25,
	VEC_TBL_OFF_UART0	= 31,
	VEC_TBL_OFF_TIMG14	= 32,
	VEC_TBL_OFF_TIMA0	= 34,
	VEC_TBL_OFF_I2C0	= 40,
	VEC_TBL_OFF_DMA		= 47

	// clang-format on
};

/** Stack pointer defined by the linker script. */
extern u32 __stack;

/** picolibc entry point. */
extern void _start(void) HAL_NORETURN;

#define ISR_FUNC HAL_WEAK_SYMBOL HAL_ALIAS("hal_isr_default")

ISR_FUNC void hal_isr_NMI(void);
ISR_FUNC void hal_isr_HardFault(void);
ISR_FUNC void hal_isr_SVCall(void);
ISR_FUNC void hal_isr_PendSV(void);

ISR_FUNC void hal_isr_INT_GROUPO(void);
ISR_FUNC void hal_isr_GPIO0(void);
ISR_FUNC void hal_isr_TIMG8(void);
ISR_FUNC void hal_isr_ADC(void);
ISR_FUNC void hal_isr_SPI0(void);
ISR_FUNC void hal_isr_UART0(void);
ISR_FUNC void hal_isr_TIMG14(void);
ISR_FUNC void hal_isr_TIMA0(void);
ISR_FUNC void hal_isr_I2C0(void);
ISR_FUNC void hal_isr_DMA(void);

#undef ISR_FUNC

void hal_isr_default(void)
{
	hal_halt_processor();
}

HAL_PLACE_IN_SECTION(".init")
const void *const __interrupt_vector[64] = {
	// clang-format off

	[VEC_TBL_OFF_SP_main]		= &__stack,
	[VEC_TBL_OFF_Reset]		= _start,
	[VEC_TBL_OFF_NMI]		= hal_isr_NMI,
	[VEC_TBL_OFF_HardFault]		= hal_isr_HardFault,
	[VEC_TBL_OFF_SVCall]		= hal_isr_SVCall,
	[VEC_TBL_OFF_PendSV]		= hal_isr_PendSV,
	[VEC_TBL_OFF_INT_GROUP0]	= hal_isr_INT_GROUPO,
	[VEC_TBL_OFF_GPIO0]		= hal_isr_GPIO0,
	[VEC_TBL_OFF_TIMG8]		= hal_isr_TIMG8,
	[VEC_TBL_OFF_ADC]		= hal_isr_ADC,
	[VEC_TBL_OFF_SPI0]		= hal_isr_SPI0,
	[VEC_TBL_OFF_UART0]		= hal_isr_UART0,
	[VEC_TBL_OFF_TIMG14]		= hal_isr_TIMG14,
	[VEC_TBL_OFF_TIMA0]		= hal_isr_TIMA0,
	[VEC_TBL_OFF_I2C0]		= hal_isr_I2C0,
	[VEC_TBL_OFF_DMA]		= hal_isr_DMA

	// clang-format on
};
