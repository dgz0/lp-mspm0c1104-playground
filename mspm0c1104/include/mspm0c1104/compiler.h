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

#ifdef __GNUC__
#define PLACE_IN_SECTION(x) __attribute__((section((x))))
#define NODISCARD __attribute__((warn_unused_result))
#define NORETURN __attribute__((noreturn))
#define UNREACHABLE __builtin_unreachable()
#define ALIAS(x) __attribute__((alias((x))))
#define WEAK_SYMBOL __attribute__((weak))
#define ALWAYS_INLINE static inline __attribute__((always_inline))

ALWAYS_INLINE NODISCARD uint32_t clz_u32(const uint32_t x)
{
	return 31 - __builtin_clz(x);
}

#else
#error "Unknown compiler!"
#endif // __GNUC__
