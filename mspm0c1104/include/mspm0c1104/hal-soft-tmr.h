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

#include <stdbool.h>
#include <stdint.h>
#include "hal-cfg.h"

#ifdef HAL_SOFT_TMR_ENABLE

enum hal_soft_tmr_state {
	HAL_SOFT_TMR_STATE_DISABLED = 0,
	HAL_SOFT_TMR_STATE_RUNNING = 1,
	HAL_SOFT_TMR_STATE_EXPIRED = 2
};

struct hal_soft_tmr {
	enum hal_soft_tmr_state state;
	HAL_SYSTICK_TICK_TYPE start_ts;
	HAL_SYSTICK_TICK_TYPE expire_ts;
};

void hal_soft_tmr_start(struct hal_soft_tmr *tmr,
			HAL_SYSTICK_TICK_TYPE start_ts);

void hal_soft_tmr_extend(struct hal_soft_tmr *tmr, HAL_SYSTICK_TICK_TYPE delay);

bool hal_soft_tmr_expired(struct hal_soft_tmr *tmr);

#endif // HAL_SOFT_TMR_ENABLE
