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

#include "hal-cfg.h"

const struct hal_gpio_pin_cfg hal_gpio_cfg_initial[] = {
	// clang-format off

	[0] = {
		.pin		= HAL_GPIO_PIN_TEST_PIN,
		.input_enabled	= false,
		.digital_attrib	= {
			.func		= HAL_IOMUX_PIN_DIGITAL_FUNC_GPIO,
			.resistor	= HAL_IOMUX_RESISTOR_TYPE_NONE,
			.data_inversion	= false,
			.hysteresis	= false
		}
	}

	// clang-format on
};

const uint32_t hal_gpio_cfg_initial_num_entries = ARRAY_SIZE(hal_gpio_cfg_initial);
