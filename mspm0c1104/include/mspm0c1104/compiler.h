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

#include <stdint.h>

/**
 * @brief Place code into a particular section.
 *
 * @param x The section to place the code into. This must be defined in the
 * linker script.
 */
#define PLACE_IN_SECTION(x) __attribute__((section((x))))

/** This function's return value must not be discarded. */
#define NODISCARD __attribute__((warn_unused_result))

/** This function will not return. */
#define NORETURN __attribute__((noreturn))

/** This control path is unreachable. */
#define UNREACHABLE __builtin_unreachable()

/** This function is aliased to another. */
#define ALIAS(x) __attribute__((alias((x))))

/**
 * This function is a weak symbol, i.e., it can be overridden by providing a
 * definition in another translation unit.
 */
#define WEAK_SYMBOL __attribute__((weak))

/** This function will always be inlined regardless of compiler heuristics. */
#define ALWAYS_INLINE static inline __attribute__((always_inline))

/**
 * Perform a count leading zeroes operation.
 *
 * @param x The parameter to count the number of leading zeroes on.
 * @return The number of leading zeroes.
 */
ALWAYS_INLINE NODISCARD uint32_t clz_u32(const uint32_t x)
{
	return 31 - __builtin_clz(x);
}
