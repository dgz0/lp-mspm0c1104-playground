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
#include "hal-util.h"

enum hal_tim_instance {
	HAL_TIM_INSTANCE_TIM0 = 0,
	HAL_TIM_INSTANCE_TIM1 = 1,
	HAL_TIM_INSTANCE_TIM2 = 2
};

struct hal_tim_cfg_basic {
	u64 timeout;
	bool repeating;
	void (*cb)(void);
};

/**
 * Initializes the HAL timer layer for use.
 *
 * Must be called by the HAL internally only.
 */
void hal_tim_init(void);

/**
 * @brief Starts the given timer instance.
 *
 * @param tim The desired timer instance.
 *
 * @note An assertion will be fired if the timer was not previously configured
 * for use.
 */
void hal_tim_start(enum hal_tim_instance tim);

/**
 * @brief Stops the given timer instance.
 *
 * @param tim The timer instance to stop.
 */
void hal_tim_stop(enum hal_tim_instance tim);

/**
 * @brief Stops the timer if running and powers it off, leaving it free for use.
 *
 * @param tim The timer to free.
 */
void hal_tim_free(enum hal_tim_instance tim);

enum hal_tim_instance hal_tim_init_basic(const struct hal_tim_cfg_basic *cfg);
