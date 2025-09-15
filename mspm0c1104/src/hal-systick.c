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
#include <mspm0c1104/hal-tim.h>
#include <mspm0c1104/hal-systick.h>

static HAL_SYSTICK_TICK_TYPE num_ticks;
static enum hal_tim_instance tim;

static void isr_systick_tmr(void)
{
	num_ticks++;
}

HAL_NODISCARD HAL_SYSTICK_TICK_TYPE hal_ticks_get(void)
{
	return num_ticks;
}

void hal_systick_init(const uint32_t tick_rate)
{
	const struct hal_tim_cfg_basic tim_systick_cfg = {
		// clang-format off

		.timeout	= hal_ms_to_ns(tick_rate),
		.repeating	= true,
		.cb		= isr_systick_tmr

		// clang-format on
	};
	tim = hal_tim_init_basic(&tim_systick_cfg);
	hal_tim_start(tim);
}
