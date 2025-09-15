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

#include "hal-types.h"

/**
 * @brief Place code into a particular section.
 *
 * @param x The section to place the code into. This must be defined in the
 * linker script.
 */
#define HAL_PLACE_IN_SECTION(x) __attribute__((section((x))))

/** This function's return value must not be discarded. */
#define HAL_NODISCARD __attribute__((warn_unused_result))

/** This function will not return. */
#define HAL_NORETURN __attribute__((noreturn))

/** This control path is unreachable. */
#define HAL_UNREACHABLE __builtin_unreachable()

/** This function is aliased to another. */
#define HAL_ALIAS(x) __attribute__((alias((x))))

/**
 * This function is a weak symbol, i.e., it can be overridden by providing a
 * definition in another translation unit.
 */
#define HAL_WEAK_SYMBOL __attribute__((weak))

/** This function will always be inlined regardless of compiler heuristics. */
#define HAL_ALWAYS_INLINE static inline __attribute__((always_inline))
