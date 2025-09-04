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

#include <mspm0c1104/hal-iomux.h>

// clang-format off

#define PINCM_BIT_INV		(BIT_26)
#define PINCM_BIT_HIZ1		(BIT_25)
#define PINCM_BIT_HYSTEN	(BIT_19)
#define PINCM_BIT_PIPU		(BIT_17)
#define PINCM_BIT_PIPD		(BIT_16)
#define PINCM_BIT_INENA		(BIT_18)
#define PINCM_BIT_PC		(BIT_7)
#define PINCM_MASK_PF		(BIT_5 | BIT_4 | BIT_3 | BIT_2 | BIT_1 | BIT_0)

#define IO_FEAT_INV_CTRL		(BIT_0)
#define IO_FEAT_HYSTERESIS_CTRL		(BIT_1)
#define IO_FEAT_PULLUP_RESISTOR		(BIT_2)
#define IO_FEAT_PULLDOWN_RESISTOR	(BIT_3)

#define IO_STRUCT_SDIO \
	(IO_FEAT_INV_CTRL | IO_FEAT_PULLUP_RESISTOR | IO_FEAT_PULLDOWN_RESISTOR)

#define IO_STRUCT_ODIO \
	(IO_FEAT_INV_CTRL | IO_FEAT_HYSTERESIS_CTRL | IO_FEAT_PULLDOWN_RESISTOR)

// clang-format on

static const struct pin_attrib {
	const uint8_t io_struct;
	const uint8_t valid_digital_funcs;
	const bool supports_analog_funcs;
} pin_attrib_tbl[] = {
	// clang-format off

	[HAL_IOMUX_PIN_IDX_PA0] = {
		.io_struct		= IO_STRUCT_ODIO,
		.valid_digital_funcs	=
			HAL_IOMUX_PIN_DIGITAL_FUNC_GPIO         |
			HAL_IOMUX_PIN_PA0_DIGITAL_FUNC_BEEP     |
			HAL_IOMUX_PIN_PA0_DIGITAL_FUNC_I2C0_SDA |
			HAL_IOMUX_PIN_PA0_DIGITAL_FUNC_TIMG8_C0 |
			HAL_IOMUX_PIN_PA0_DIGITAL_FUNC_SPI0_CS1 |
			HAL_IOMUX_PIN_PA0_DIGITAL_FUNC_FCC_IN   |
			HAL_IOMUX_PIN_PA0_DIGITAL_FUNC_TIMA_FAL1,
		.supports_analog_funcs	= false
	},

	[HAL_IOMUX_PIN_IDX_PA1]	= {
		.io_struct		= IO_STRUCT_ODIO,
		.valid_digital_funcs	=
			HAL_IOMUX_PIN_DIGITAL_FUNC_GPIO         |
			HAL_IOMUX_PIN_PA1_DIGITAL_FUNC_I2C0_SCL |
			HAL_IOMUX_PIN_PA1_DIGITAL_FUNC_TIM8_C0  |
			HAL_IOMUX_PIN_PA1_DIGITAL_FUNC_HFCLK_IN |
			HAL_IOMUX_PIN_PA1_DIGITAL_FUNC_TIMA0_C1,
		.supports_analog_funcs	= false
	},

	[HAL_IOMUX_PIN_IDX_PA2] = {
		.io_struct		= IO_STRUCT_SDIO,
		.valid_digital_funcs	=
			HAL_IOMUX_PIN_DIGITAL_FUNC_GPIO         |
			HAL_IOMUX_PIN_PA2_DIGITAL_FUNC_TIMG8_C1 |
			HAL_IOMUX_PIN_PA2_DIGITAL_FUNC_SPI0_CS0 |
			HAL_IOMUX_PIN_PA2_DIGITAL_FUNC_TIMA0_C0 |
			HAL_IOMUX_PIN_PA2_DIGITAL_FUNC_TIMG8_IDX,
		.supports_analog_funcs	= false
	},

	[HAL_IOMUX_PIN_IDX_PA4] = {
		.io_struct		= IO_STRUCT_SDIO,
		.valid_digital_funcs	=
			HAL_IOMUX_PIN_DIGITAL_FUNC_GPIO          |
			HAL_IOMUX_PIN_PA4_DIGITAL_FUNC_TIMA0_C0N |
			HAL_IOMUX_PIN_PA4_DIGITAL_FUNC_SPI0_POCI |
			HAL_IOMUX_PIN_PA4_DIGITAL_FUNC_LFCLK_IN  |
			HAL_IOMUX_PIN_PA4_DIGITAL_FUNC_HFCLK_IN  |
			HAL_IOMUX_PIN_PA4_DIGITAL_FUNC_TIMA0_C1N,
		.supports_analog_funcs	= false
	},

	[HAL_IOMUX_PIN_IDX_PA6] = {
		.io_struct		= IO_STRUCT_SDIO,
		.valid_digital_funcs	=
			HAL_IOMUX_PIN_DIGITAL_FUNC_GPIO           |
			HAL_IOMUX_PIN_PA6_DIGITAL_FUNC_TIMG14__C1 |
			HAL_IOMUX_PIN_PA6_DIGITAL_FUNC_SPI0_SCK   |
			HAL_IOMUX_PIN_PA6_DIGITAL_FUNC_TIMA0_C1   |
			HAL_IOMUX_PIN_PA6_DIGITAL_FUNC_TIMG14_C2  |
			HAL_IOMUX_PIN_PA6_DIGITAL_FUNC_SPI0_CS0   |
			HAL_IOMUX_PIN_PA6_DIGITAL_FUNC_TIMA_FAL0,
		.supports_analog_funcs	= false
	},

	[HAL_IOMUX_PIN_IDX_PA11] = {
		.io_struct		= IO_STRUCT_SDIO,
		.valid_digital_funcs	=
			HAL_IOMUX_PIN_DIGITAL_FUNC_GPIO          |
			HAL_IOMUX_PIN_PA11_DIGITAL_FUNC_SPI0_SCK |
			HAL_IOMUX_PIN_PA11_DIGITAL_FUNC_I2C0_SCL |
			HAL_IOMUX_PIN_PA11_DIGITAL_FUNC_TIMA_FAL0,
		.supports_analog_funcs	= false
	},

	[HAL_IOMUX_PIN_IDX_PA16] = {
		.io_struct		= IO_STRUCT_SDIO,
		.valid_digital_funcs	=
			HAL_IOMUX_PIN_DIGITAL_FUNC_GPIO           |
			HAL_IOMUX_PIN_PA16_DIGITAL_FUNC_TIMA0_C1N |
			HAL_IOMUX_PIN_PA16_DIGITAL_FUNC_SPI0_POCI |
			HAL_IOMUX_PIN_PA16_DIGITAL_FUNC_TIMG14_C0 |
			HAL_IOMUX_PIN_PA16_DIGITAL_FUNC_FCC_IN,
		.supports_analog_funcs	= true
	},

	[HAL_IOMUX_PIN_IDX_PA17] = {
		.io_struct		= IO_STRUCT_SDIO,
		.valid_digital_funcs	=
			HAL_IOMUX_PIN_DIGITAL_FUNC_GPIO           |
			HAL_IOMUX_PIN_PA17_DIGITAL_FUNC_UART0_TX  |
			HAL_IOMUX_PIN_PA17_DIGITAL_FUNC_TIMA0_C0N |
			HAL_IOMUX_PIN_PA17_DIGITAL_FUNC_SPI0_SCK  |
			HAL_IOMUX_PIN_PA17_DIGITAL_FUNC_TIMA0_C2  |
			HAL_IOMUX_PIN_PA17_DIGITAL_FUNC_SPI0_CS1  |
			HAL_IOMUX_PIN_PA17_DIGITAL_FUNC_TIMA0_C3,
		.supports_analog_funcs	= true
	},

	[HAL_IOMUX_PIN_IDX_PA18] = {
		.io_struct		= IO_STRUCT_SDIO,
		.valid_digital_funcs	=
			HAL_IOMUX_PIN_DIGITAL_FUNC_GPIO           |
			HAL_IOMUX_PIN_PA18_DIGITAL_FUNC_UART0_RX  |
			HAL_IOMUX_PIN_PA18_DIGITAL_FUNC_SPI0_PICO |
			HAL_IOMUX_PIN_PA18_DIGITAL_FUNC_TIMA0_C1N |
			HAL_IOMUX_PIN_PA18_DIGITAL_FUNC_CLK_OUT   |
			HAL_IOMUX_PIN_PA18_DIGITAL_FUNC_TIMA0_C3  |
			HAL_IOMUX_PIN_PA18_DIGITAL_FUNC_TIMA0_C3N,
		.supports_analog_funcs = true
	};

	// clang-format on
};

void hal_iomux_set_pin_inv(const enum hal_iomux_pin_idx pin_idx, const bool inv)
{
	if (inv) {
		HAL_IOMUX->PINCM[pin_idx] |= PINCM_BIT_INV;
	} else {
		HAL_IOMUX->PINCM[pin_idx] &= ~PINCM_BIT_INV;
	}
}

void hal_iomux_set_pin_hysteresis(const enum hal_iomux_pin_idx pin_idx,
				  const bool hysteresis)
{
	if (hysteresis) {
		if (!(pin_attrib_tbl[pin_idx].io_struct &
		      IO_FEAT_HYSTERESIS_CTRL)) {
			return;
		}

		HAL_IOMUX->PINCM[pin_idx] |= PINCM_BIT_HYSTEN;
	} else {
		HAL_IOMUX->PINCM[pin_idx] &= ~PINCM_BIT_HYSTEN;
	}
}

void hal_iomux_set_pin_resistor(const enum hal_iomux_pin_idx pin_idx,
				const enum hal_iomux_resistor_type resistor_type)
{
	switch (resistor_type) {
	case HAL_IOMUX_RESISTOR_TYPE_NONE:
		HAL_IOMUX->PINCM[pin_idx] &= ~(PINCM_BIT_PIPU | PINCM_BIT_PIPD);
		return;

	case HAL_IOMUX_RESISTOR_TYPE_PULL_UP:
		// check if pin supports pullup resistors
		HAL_IOMUX->PINCM[pin_idx] &= ~PINCM_BIT_PIPD;
		HAL_IOMUX->PINCM[pin_idx] |= PINCM_BIT_PIPU;

		return;

	case HAL_IOMUX_RESISTOR_TYPE_PULL_DOWN:
		HAL_IOMUX->PINCM[pin_idx] |= PINCM_BIT_PIPD;
		HAL_IOMUX->PINCM[pin_idx] &= ~PINCM_BIT_PIPU;

		return;

	default:
		HAL_ASSERT_OR_UNREACHABLE();
	}
}

void hal_iomux_set_pin_func(const enum hal_iomux_pin_idx pin_idx, uint8_t func,
			    const bool input_enabled)
{
	// This pin does not support the digital I/O function requested.
	HAL_ASSERT((pin_attrib_tbl[pin_idx].valid_digital_funcs & func) != 0);

	// Clear the PC bit (input/output connect bit) and INENA (input connect
	// bit) in the corresponding PINCMx register
	HAL_IOMUX->PINCM[pin_idx] &= ~(PINCM_BIT_PC | PINCM_BIT_INENA);

	// Write 0x0 to the PF field in the PINCMx to clear the logic in the
	// data path
	set_val_by_mask(HAL_IOMUX->PINCM[pin_idx], PINCM_MASK_PF, 0x0);

	func = clz_u32(func);

	// Select the new peripheral function by writing the peripheral function
	// ID to the PF register
	set_val_by_mask(HAL_IOMUX->PINCM[pin_idx], PINCM_MASK_PF, func);

	// Set the PC and INENA bits in the PINCMx register to connect the newly
	// selected peripheral
	if (input_enabled) {
		HAL_IOMUX->PINCM[pin_idx] |= (PINCM_BIT_PC | PINCM_BIT_INENA);
	} else {
		HAL_IOMUX->PINCM[pin_idx] |= PINCM_BIT_PC;
	}
}
