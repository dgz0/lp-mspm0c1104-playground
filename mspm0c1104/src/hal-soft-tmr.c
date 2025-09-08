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

#include <mspm0c1104/hal-soft-tmr.h>
#include <mspm0c1104/hal-systick.h>

void hal_soft_tmr_start(struct hal_soft_tmr *const tmr,
			const HAL_SYSTICK_TICK_TYPE start_ts)
{
	tmr->state = HAL_SOFT_TMR_STATE_RUNNING;
	tmr->expire_ts = hal_ticks_get() + start_ts;
}

void hal_soft_tmr_extend(struct hal_soft_tmr *const tmr,
			 const HAL_SYSTICK_TICK_TYPE delay)
{
	tmr->expire_ts += delay;
}

bool hal_soft_tmr_expired(struct hal_soft_tmr *const tmr)
{
	if ((hal_ticks_get() - tmr->start_ts) >= tmr->expire_ts) {
		tmr->state = HAL_SOFT_TMR_STATE_EXPIRED;
		return true;
	}
	return false;
}
