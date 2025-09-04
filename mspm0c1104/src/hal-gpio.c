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

#include <mspm0c1104/hal-gpio.h>

// clang-format off

#define PWREN_MASK_KEY		(0x26 << 24)
#define PWREN_BIT_ENABLE	(BIT_0)

#define RSTCTL_MASK_KEY		(0xB1 << 24)
#define RSTCTL_BIT_RESETASSERT	(BIT_0)

#define GPIO_PIN(num)						\
	const struct hal_gpio_pin HAL_GPIO_PIN_PA## num = {	\
		.pin_idx	= BIT_## num,			\
		.iomux_idx	= HAL_IOMUX_PIN_IDX_PA## num	\
	}							\

GPIO_PIN(0);
GPIO_PIN(1);
GPIO_PIN(2);
GPIO_PIN(4);
GPIO_PIN(6);
GPIO_PIN(11);
GPIO_PIN(16);
GPIO_PIN(17);
GPIO_PIN(18);
GPIO_PIN(19);
GPIO_PIN(20);
GPIO_PIN(22);
GPIO_PIN(23);
GPIO_PIN(24);
GPIO_PIN(25);
GPIO_PIN(26);
GPIO_PIN(27);
GPIO_PIN(28);

#undef GPIO_PIN

// clang-format on

static uint32_t configured_pins;

void hal_gpio_pwr_enable(void)
{
	HAL_GPIO0->PWREN = PWREN_MASK_KEY | PWREN_BIT_ENABLE;
}

void hal_gpio_rst(void)
{
	HAL_GPIO0->RSTCTL = RSTCTL_MASK_KEY | RSTCTL_BIT_RESETASSERT;
}

void hal_gpio_enable_pin_output(const struct hal_gpio_pin *const pin)
{
	HAL_GPIO0->DOE31_0 |= pin->pin_idx;
}

void hal_gpio_cfg_pin(const struct hal_gpio_pin_cfg *const cfg)
{
	hal_iomux_set_pin_hysteresis(cfg->pin->iomux_idx,
				     cfg->digital_attrib.hysteresis);

	hal_iomux_set_pin_resistor(cfg->pin->iomux_idx,
				   cfg->digital_attrib.resistor);

	hal_iomux_set_pin_func(cfg->pin->iomux_idx, cfg->digital_attrib.func,
			       cfg->input_enabled);

	configured_pins |= cfg->pin->pin_idx;
}

void hal_gpio_init(void)
{
	hal_gpio_rst();
	hal_gpio_pwr_enable();

	for (uint32_t i = 0; i < hal_gpio_cfg_initial_num_entries; ++i) {
		hal_gpio_cfg_pin(&hal_gpio_cfg_initial[i]);
	}
}

void hal_gpio_cfg_unused_pins(
	enum hal_gpio_unused_pin_cfg_strategy unused_pin_cfg_strategy)
{
	for (uint32_t i = 0; i < HAL_IOMUX_NUM_PINS; ++i) {
	}
}
