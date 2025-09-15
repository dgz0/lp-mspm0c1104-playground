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

#include <stddef.h>
#include "hal-compiler.h"

// clang-format off

#define HAL_BIT_31	(UINT32_C(1) << 31)
#define HAL_BIT_30	(1 << 30)
#define HAL_BIT_29	(1 << 29)
#define HAL_BIT_28	(1 << 28)
#define HAL_BIT_27	(1 << 27)
#define HAL_BIT_26	(1 << 26)
#define HAL_BIT_25	(1 << 25)
#define HAL_BIT_24	(1 << 24)
#define HAL_BIT_23	(1 << 23)
#define HAL_BIT_22	(1 << 22)
#define HAL_BIT_21	(1 << 21)
#define HAL_BIT_20	(1 << 20)
#define HAL_BIT_19	(1 << 19)
#define HAL_BIT_18	(1 << 18)
#define HAL_BIT_17	(1 << 17)
#define HAL_BIT_16	(1 << 16)
#define HAL_BIT_15	(1 << 15)
#define HAL_BIT_14	(1 << 14)
#define HAL_BIT_13	(1 << 13)
#define HAL_BIT_12	(1 << 12)
#define HAL_BIT_11	(1 << 11)
#define HAL_BIT_10	(1 << 10)
#define HAL_BIT_9	(1 << 9)
#define HAL_BIT_8	(1 << 8)
#define HAL_BIT_7	(1 << 7)
#define HAL_BIT_6	(1 << 6)
#define HAL_BIT_5	(1 << 5)
#define HAL_BIT_4	(1 << 4)
#define HAL_BIT_3	(1 << 3)
#define HAL_BIT_2	(1 << 2)
#define HAL_BIT_1	(1 << 1)
#define HAL_BIT_0	(1 << 0)

// clang-format on

/**
 * Perform a count leading zeroes operation.
 *
 * @param x The parameter to count the number of leading zeroes on.
 * @return The number of leading zeroes.
 */
HAL_ALWAYS_INLINE HAL_NODISCARD u32 hal_clz_u32(const u32 x)
{
	return 31 - __builtin_clz(x);
}

HAL_ALWAYS_INLINE void hal_no_op(void)
{
	asm volatile("NOP" ::: "memory");
}

HAL_ALWAYS_INLINE void hal_isb(void)
{
	asm volatile("ISB" ::: "memory");
}

HAL_ALWAYS_INLINE void hal_dsb(void)
{
	asm volatile("DSB" ::: "memory");
}

HAL_ALWAYS_INLINE void hal_halt_processor(void)
{
	// check if a watchdog is running, let it fire if so
	asm volatile("BKPT" ::: "memory");
}

#ifndef NDEBUG
#define hal_assert(expr)                      \
	({                                    \
		if (!(expr)) {                \
			hal_halt_processor(); \
			HAL_UNREACHABLE;      \
		}                             \
	})

#define HAL_ASSERT_OR_UNREACHABLE(expr) hal_assert(false)
#else
#define hal_assert(expr)
#define HAL_ASSERT_OR_UNREACHABLE() HAL_UNREACHABLE
#endif // NDEBUG

#define hal_static_assert_offset(x, memb, off) \
	_Static_assert(offsetof(x, memb) == (off), "Offset is not correct")

#define hal_array_size(x) (sizeof(x) / sizeof((x)[0]))

#define hal_set_val_by_mask(dst, mask, val)                              \
	({                                                               \
		const int shift = __builtin_ffs((mask)) - 1;             \
		(dst) = ((dst) & ~(mask)) | (((val) << shift) & (mask)); \
	})

#define hal_get_val_by_mask(src, mask)                       \
	({                                                   \
		const int shift = __builtin_ffs((mask)) - 1; \
		((src) & (mask)) >> shift;                   \
	})

#define hal_mhz_to_hz(mhz) ((mhz) * (1000000))
#define hal_sec_to_ms(sec) ((sec) * (1000))
#define hal_sec_to_ns(sec) ((sec) * (UINT64_C(1000000000)))
#define hal_ms_to_ns(ms) ((ms) * (1000000))

#define hal_clamp(val, lo, hi)					\
	({							\
		__typeof__(val) _val = (val);			\
		__typeof__(lo) _lo = (lo);			\
		__typeof__(hi) _hi = (hi);			\
		_val > _hi ? _hi : (_val < _lo ? _lo : _val);	\
	})

#define hal_is_unsigned_type(type) ((type)0 < (type) - 1)
