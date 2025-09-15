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

#include <mspm0c1104/hal-irq.h>
#include <mspm0c1104/hal-gpio.h>

static uint32_t configured_pins;

static void (*edge_detect_cb_tbl[32])(void);

static void enable_pin_output(const enum hal_gpio_pin pins)
{
	HAL_GPIO0->DOESET31_0 |= pins;
}

void hal_isr_GPIO0(void)
{
	u32 irq = 0;
	while (HAL_GPIO0->CPU_INT.MIS) {
		const u32 bit = UINT32_C(1) << irq;

		if (HAL_GPIO0->CPU_INT.MIS & bit) {
			HAL_GPIO0->CPU_INT.ICLR |= bit;
			edge_detect_cb_tbl[irq]();
		}
		irq++;
	}
}

HAL_NODISCARD static enum hal_iomux_pincm
gpio_pin_to_iomux_pincm(const enum hal_gpio_pin pin)
{
	return hal_clz_u32(pin);
}

void hal_gpio_pwr_enable(void)
{
	HAL_GPIO0->PWREN = HAL_GPIO_PWREN_KEY_VAL | HAL_GPIO_PWREN_BIT_ENABLE;
}

void hal_gpio_rst(void)
{
	HAL_GPIO0->RSTCTL = HAL_GPIO_RSTCTL_KEY_VAL |
			    HAL_GPIO_RSTCTL_BIT_RESETASSERT;
}

void hal_gpio_init(void)
{
	hal_gpio_rst();
	hal_gpio_pwr_enable();

	for (uint32_t i = 0; i < hal_gpio_cfg_init_num_entries; ++i)
		hal_gpio_cfg_pin(&hal_gpio_cfg_init[i]);
}

void hal_gpio_cfg_pin(const struct hal_gpio_pin_cfg *const cfg)
{
	if (!cfg->input_enabled)
		enable_pin_output(cfg->pin);

	if (cfg->initial_state == HAL_GPIO_PIN_INITIAL_STATE_LOW) {
		hal_gpio_pin_set_low(cfg->pin);
	} else {
		hal_gpio_pin_set_high(cfg->pin);
	}

	const enum hal_iomux_pincm pincm = gpio_pin_to_iomux_pincm(cfg->pin);

	if (cfg->analog) {
		hal_iomux_set_pin_func(pincm, 0, cfg->input_enabled);
		configured_pins |= cfg->pin;

		return;
	}

	hal_iomux_set_pin_hysteresis(pincm, cfg->digital.hysteresis);
	hal_iomux_set_pin_resistor(pincm, cfg->digital.resistor);
	hal_iomux_set_pin_func(pincm, cfg->digital.func, cfg->input_enabled);

	configured_pins |= cfg->pin;
}

void hal_gpio_pin_edge_detect_mode_set(
	const enum hal_gpio_pin pin,
	const enum hal_gpio_pin_edge_detect_mode edge_detect_mode,
	void (*cb)(void))
{
	volatile u32 *reg;
	u32 val = hal_clz_u32(pin);

	if (pin < HAL_GPIO_PIN_PA16)
		reg = &HAL_GPIO0->POLARITY15_0;
	else {
		reg = &HAL_GPIO0->POLARITY31_16;
		val -= 16;
	}

	const u32 mask = 0x3 << (val * 2);
	hal_set_val_by_mask(*reg, mask, edge_detect_mode);

	HAL_GPIO0->CPU_INT.ICLR |= pin;
	HAL_GPIO0->CPU_INT.IMASK |= pin;

	edge_detect_cb_tbl[hal_clz_u32(pin)] = cb;
	hal_irq_en(HAL_IRQ_GPIO0);
}
