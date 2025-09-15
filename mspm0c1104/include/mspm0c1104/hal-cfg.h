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

/**
 * @file hal-cfg.h Defines the compile-time configuration of the HAL.
 *
 * This header allows example programs to control the characteristics and
 * behavior of the HAL at compile-time; each example gets its own custom
 * configured HAL. For some examples, this may be more efficient in the way of
 * code size, performance, or reduced compile times.
 *
 * The default configuration if not overridden by an example is as follows:
 *
 * - HAL tick support is enabled and initialized at HAL initialization time with
 *   a tick rate of 1ms. The underlying tick representation is an unsigned
 *   32-bit integer; it will overflow in 49.71 days. If you wish, you may change
 *   the underlying tick representation to an unsigned 64-bit integer, but this
 *   is not recommended as it will increase code size and be slower.
 *
 * - Software timer support is enabled. Software timers depend on SysTick, so
 *   the HAL will fail to compile if SysTick support isn't present. The
 *   underlying timestamp representation is the same as the SysTick tick
 *   representation.
 *
 * - After the GPIO pins specified in `hal_gpio_cfg_initial` are configured,
 *   pins that were NOT specified *ARE NOT* configured automatically; the user
 *   must explicitly configure unused GPIO pins. There is a helper function to
 *   do this called `hal_gpio_cfg_unused_pins()`.
 */

#pragma once

#include "hal-types.h"

#ifndef HAL_SYSTICK_ENABLE
#define HAL_SYSTICK_ENABLE
#endif // HAL_SYSTICK_ENABLE

#if defined(HAL_SYSTICK_ENABLE) && !defined(HAL_SYSTICK_TICK_TYPE)
#define HAL_SYSTICK_TICK_TYPE u32
#endif // defined(HAL_SYSTICK_ENABLE) && !defined(HAL_SYSTICK_TICK_TYPE)

#if defined(HAL_SYSTICK_ENABLE) && !defined(HAL_SYSTICK_INIT_ON_START)
#define HAL_SYSTICK_INIT_ON_START (1)
#endif // defined(HAL_SYSTICK_ENABLE) && !defined(HAL_SYSTICK_INIT_ON_START)

#if defined(HAL_SYSTICK_INIT_ON_START) && !defined(HAL_SYSTICK_TICK_RATE_MS)
#define HAL_SYSTICK_TICK_RATE_MS (1)
#endif // defined(HAL_SYSTICK_INIT_ON_START) && !defined(HAL_SYSTICK_TICK_RATE_MS)

#if !defined(HAL_SOFT_TIM_ENABLE) && defined(HAL_SYSTICK_ENABLE)
#define HAL_SOFT_TIM_ENABLE
#endif // !defined(HAL_SOFT_TIM_ENABLE) && defined(HAL_SYSTICK_ENABLE)
