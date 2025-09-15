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

#include "hal-compiler.h"
#include "hal-util.h"

enum hal_irq {
	// clang-format off

	HAL_IRQ_INT_GROUP0	= HAL_BIT_0,
	HAL_IRQ_GPIO0		= HAL_BIT_1,
	HAL_IRQ_TIMG8		= HAL_BIT_2,
	HAL_IRQ_ADC		= HAL_BIT_4,
	HAL_IRQ_SPI0		= HAL_BIT_9,
	HAL_IRQ_UART0		= HAL_BIT_15,
	HAL_IRQ_TIMG14		= HAL_BIT_16,
	HAL_IRQ_TIMA0		= HAL_BIT_18,
	HAL_IRQ_I2C0		= HAL_BIT_24,
	HAL_IRQ_DMA		= HAL_BIT_31

	// clang-format on
};

#define HAL_NVIC_ISER (*(volatile u32 *const)(0xE000E100))
#define HAL_NVIC_ICER (*(volatile u32 *const)(0xE000E180))

HAL_ALWAYS_INLINE void hal_irq_en(const enum hal_irq irq)
{
	HAL_NVIC_ISER |= irq;
	hal_dsb();
	hal_isb();
}

HAL_ALWAYS_INLINE void hal_irq_dis(const enum hal_irq irq)
{
	HAL_NVIC_ICER |= irq;
	hal_dsb();
	hal_isb();
}
