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

#include <mspm0c1104/hal-clk.h>
#include <mspm0c1104/hal-systick.h>
#include <mspm0c1104/util.h>

/** @brief SysTick Control and Status Register */
#define SYST_CSR (*(volatile uint32_t *const)(0xE000E010))

/** @brief SysTick Reload Value Register */
#define SYST_RVR (*(volatile uint32_t *const)(0xE000E014))

/** @brief SysTick Current Value Register */
#define SYST_CVR (*(volatile uint32_t *const)(0xE000E018))

/** @brief SysTick Calibration Value Register */
#define SYST_CALIB (*(volatile const uint32_t *const)(0xE000E01C))

#define SYST_CSR_BIT_CLKSOURCE (BIT_2)
#define SYST_CSR_BIT_TICKINT (BIT_1)
#define SYST_CSR_BIT_ENABLE (BIT_0)

static HAL_SYSTICK_TICK_TYPE num_ticks;

NODISCARD HAL_SYSTICK_TICK_TYPE hal_ticks_get(void)
{
	return num_ticks;
}

void hal_isr_SysTick(void)
{
	num_ticks++;
}

void hal_systick_init(const uint32_t tick_rate)
{
	SYST_CVR = 0;
	SYST_RVR = HAL_FREQ_CPUCLK_HZ / tick_rate;
	SYST_CSR = SYST_CSR_BIT_CLKSOURCE | SYST_CSR_BIT_TICKINT |
		   SYST_CSR_BIT_ENABLE;
}
