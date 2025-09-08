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

#pragma once

#include "compiler.h"
#include "util.h"

enum hal_nvic_irq {
	// clang-format off

	HAL_NVIC_IRQ_INT_GROUP0	= 0,
	HAL_NVIC_IRQ_GPIO0	= 1,
	HAL_NVIC_IRQ_TIMG8	= 2,
	HAL_NVIC_IRQ_ADC	= 4,
	HAL_NVIC_IRQ_SPI0	= 9,
	HAL_NVIC_IRQ_UART0	= 15,
	HAL_NVIC_IRQ_TIMG14	= 16,
	HAL_NVIC_IRQ_TIMA0	= 18,
	HAL_NVIC_IRQ_I2C0	= 24,
	HAL_NVIC_IRQ_DMA	= 31

	// clang-format on
};

#define HAL_NVIC_ISER (*(volatile uint32_t *const)(0xE000E100))
#define HAL_NVIC_ICER (*(volatile uint32_t *const)(0xE000E180))

ALWAYS_INLINE void hal_nvic_irq_en(const enum hal_nvic_irq irq)
{
	HAL_NVIC_ISER |= (1 << irq);
	hal_dsb();
	hal_isb();
}

ALWAYS_INLINE void hal_nvic_irq_disable(const enum hal_nvic_irq irq)
{
	HAL_NVIC_ICER |= (1 << irq);
	hal_dsb();
	hal_isb();
}
