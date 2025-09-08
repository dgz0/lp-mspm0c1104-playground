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

#include <stdint.h>
#include "mspm0c1104/compiler.h"

/**
 * @defgroup mspm0c1104_vec_tbl_offsets TI MSPM0C1104 vector table offsets
 * @brief Defines the vector table offsets needed to call ISRs.
 *
 * @{
 */

#define VEC_SP_main	(0)
#define VEC_Reset	(1)
#define VEC_NMI		(2)
#define VEC_HardFault	(3)
#define VEC_SVCall	(11)
#define VEC_PendSV	(14)
#define VEC_SysTick	(15)
#define VEC_INT_GROUP0	(16)
#define VEC_GPIO0	(17)
#define VEC_TIMG8	(18)
#define VEC_ADC		(20)
#define VEC_SPI0	(25)
#define VEC_UART0	(31)
#define VEC_TIMG14	(32)
#define VEC_TIMA0	(34)
#define VEC_I2C0	(40)
#define VEC_DMA		(47)

/** @} */

#define ISR_FUNC WEAK_SYMBOL ALIAS("hal_isr_default")

/** Stack pointer defined by the linker script. */
extern uint32_t __stack;

/** picolibc entry point. */
extern void _start(void) NORETURN;

ISR_FUNC void hal_isr_NMI(void);
ISR_FUNC void hal_isr_HardFault(void);
ISR_FUNC void hal_isr_SVCall(void);
ISR_FUNC void hal_isr_PendSV(void);
ISR_FUNC void hal_isr_SysTick(void);
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

void hal_isr_default(void)
{
	asm("BKPT");
}

PLACE_IN_SECTION(".init")
const void *const __interrupt_vector[64] = {
	[VEC_SP_main]		= &__stack,
	[VEC_Reset]		= _start,
	[VEC_NMI]		= hal_isr_NMI,
	[VEC_HardFault]		= hal_isr_HardFault,
	[VEC_SVCall]		= hal_isr_SVCall,
	[VEC_PendSV]		= hal_isr_PendSV,
	[VEC_SysTick]		= hal_isr_SysTick,
	[VEC_INT_GROUP0]	= hal_isr_INT_GROUPO,
	[VEC_GPIO0]		= hal_isr_GPIO0,
	[VEC_TIMG8]		= hal_isr_TIMG8,
	[VEC_ADC]		= hal_isr_ADC,
	[VEC_SPI0]		= hal_isr_SPI0,
	[VEC_UART0]		= hal_isr_UART0,
	[VEC_TIMG14]		= hal_isr_TIMG14,
	[VEC_TIMA0]		= hal_isr_TIMA0,
	[VEC_I2C0]		= hal_isr_I2C0,
	[VEC_DMA]		= hal_isr_DMA
};
