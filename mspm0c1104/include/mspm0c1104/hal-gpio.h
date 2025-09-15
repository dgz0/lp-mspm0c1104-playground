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

#include "hal-compiler.h"
#include "hal-iomux.h"
#include "hal-util.h"

#define HAL_GPIO0 ((struct hal_gpio_regs *const)(0x400A0000))

#define HAL_GPIO_PWREN_KEY_MASK                                           \
	(HAL_BIT_31 | HAL_BIT_30 | HAL_BIT_29 | HAL_BIT_28 | HAL_BIT_27 | \
	 HAL_BIT_26 | HAL_BIT_25 | HAL_BIT_24)

#define HAL_GPIO_PWREN_KEY_SHIFT (24)
#define HAL_GPIO_PWREN_KEY_VAL ((0x26) << HAL_GPIO_PWREN_KEY_SHIFT)

#define HAL_GPIO_PWREN_BIT_ENABLE (HAL_BIT_0)

#define HAL_GPIO_RSTCTL_KEY_MASK                                          \
	(HAL_BIT_31 | HAL_BIT_30 | HAL_BIT_29 | HAL_BIT_28 | HAL_BIT_27 | \
	 HAL_BIT_26 | HAL_BIT_25 | HAL_BIT_24)

#define HAL_GPIO_RSTCTL_KEY_SHIFT (24)
#define HAL_GPIO_RSTCTL_KEY_VAL ((0x26) << HAL_GPIO_RSTCTL_KEY_SHIFT)

#define HAL_GPIO_RSTCTL_BIT_RESETSTKYCLR (HAL_BIT_1)
#define HAL_GPIO_RSTCTL_BIT_RESETASSERT (HAL_BIT_0)

enum hal_gpio_pin {
	// clang-format off

	HAL_GPIO_PIN_PA0	= HAL_BIT_0,
	HAL_GPIO_PIN_PA1	= HAL_BIT_1,
	HAL_GPIO_PIN_PA2	= HAL_BIT_2,
	HAL_GPIO_PIN_PA4	= HAL_BIT_4,
	HAL_GPIO_PIN_PA6	= HAL_BIT_6,
	HAL_GPIO_PIN_PA11	= HAL_BIT_11,
	HAL_GPIO_PIN_PA16	= HAL_BIT_16,
	HAL_GPIO_PIN_PA17	= HAL_BIT_17,
	HAL_GPIO_PIN_PA18	= HAL_BIT_18,
	HAL_GPIO_PIN_PA19	= HAL_BIT_19,
	HAL_GPIO_PIN_PA20	= HAL_BIT_20,
	HAL_GPIO_PIN_PA22	= HAL_BIT_22,
	HAL_GPIO_PIN_PA23	= HAL_BIT_23,
	HAL_GPIO_PIN_PA24	= HAL_BIT_24,
	HAL_GPIO_PIN_PA25	= HAL_BIT_25,
	HAL_GPIO_PIN_PA26	= HAL_BIT_26,
	HAL_GPIO_PIN_PA27	= HAL_BIT_27,
	HAL_GPIO_PIN_PA28	= HAL_BIT_28

	// clang-format on
};

enum hal_gpio_unused_pin_cfg_strategy {
	/** All unused pins are configured to output low. */
	HAL_GPIO_UNUSED_PIN_CFG_STRATEGY_OUTPUT_LOW = 0,

	/**
	 * All unused pins are configured as inputs with the internal pull-up
	 * resistor enabled. If an unused pin belongs to the ODIO I/O structure,
	 * no programmable resistor is applied as pins belonging to the ODIO I/O
	 * structure do not support internal pull-up resistors.
	 */
	HAL_GPIO_UNUSED_PIN_CFG_STRATEGY_INPUT_PULLUP = 1,

	/**
	 * All unused pins are configured as inputs with the internal pull-down
	 * resistor enabled.
	 */
	HAL_GPIO_UNUSED_PIN_CFG_STRATEGY_INPUT_PULLDOWN = 2
};

enum hal_gpio_unused_pin_cfg_debug_pins {
	HAL_GPIO_UNUSED_PIN_CFG_EXCLUDE_DEBUG_PINS = 0,
	HAL_GPIO_UNUSED_PIN_CFG_INCLUDE_DEBUG_PINS = 1
};

enum hal_gpio_pin_initial_state {
	HAL_GPIO_PIN_INITIAL_STATE_LOW = 0,
	HAL_GPIO_PIN_INITIAL_STATE_HIGH = 1
};

struct hal_gpio_pin_digital_attrib {
	u32 func;
	bool data_inversion;
	bool hysteresis;
	enum hal_iomux_resistor_type resistor;
};

struct hal_gpio_pin_cfg {
	enum hal_gpio_pin pin;
	enum hal_gpio_pin_initial_state initial_state;
	bool input_enabled;
	bool analog;
	struct hal_gpio_pin_digital_attrib digital;
};

struct hal_gpio_regs_intr_grp {
	const u32 pad0;

	/** Interrupt index */
	volatile const u32 IIDX;

	const u32 pad1;

	/** Interrupt mask  */
	volatile u32 IMASK;

	const u32 pad2;

	/** Raw interrupt status */
	volatile const u32 RIS;

	const u32 pad3;

	/** Masked interrupt status */
	volatile const u32 MIS;

	const u32 pad4;

	/** Interrupt set */
	volatile u32 ISET;

	const u32 pad5;

	/** Interrupt clear */
	volatile u32 ICLR;
};

struct hal_gpio_regs {
	const u32 pad0[256];

	/** 0x400 - Subscriber Port 0 */
	volatile u32 FSUB_0;

	/** 0x404 - Subscriber Port 1 */
	volatile u32 FSUB_1;

	const u32 pad1[15];

	/** 0x444 - Publisher Port 0 */
	volatile u32 FPUB_0;

	/** 0x448 - Publisher Port 1 */
	volatile u32 FPUB_1;

	const u32 pad2[237];

	/** 0x800 - Power enable */
	volatile u32 PWREN;

	/** 0x804 - Reset Control */
	volatile u32 RSTCTL;

	const u32 pad3[3];

	/** 0x814 - Status Register */
	volatile const u32 STAT;

	const u32 pad4[510];

	/** 0x1010 - Clock Override */
	volatile u32 CLKOVR;

	const u32 pad5;

	/** 0x1018 - Peripheral Debug Control */
	volatile u32 PDBGCTL;

	/** 0x1020 - 0x1048: CPU_INT interrupt group */
	struct hal_gpio_regs_intr_grp CPU_INT;

	/** 0x1050 - 0x1078: GEN_EVENT0 interrupt group */
	struct hal_gpio_regs_intr_grp GEN_EVENT0;

	/** 0x1080 - 0x10A8: GEN_EVENT1 interrupt group */
	struct hal_gpio_regs_intr_grp GEN_EVENT1;

	const u32 pad6[13];

	/** 0x10E0 - Event mode */
	volatile const u32 EVT_MODE;

	const u32 pad7[6];

	/** 0x10FC - Module Description */
	volatile const u32 DESC;

	const u32 pad8[64];

	/** 0x1200 - Data output 3 to 0 */
	volatile u32 DOUT3_0;

	/** 0x1204 - Data output 7 to 4 */
	volatile u32 DOUT7_4;

	/** 0x1208 - Data output 11 to 8 */
	volatile u32 DOUT11_8;

	/** 0x120C - Data output 15 to 12 */
	volatile u32 DOUT15_12;

	/** 0x1210 - Data output 19 to 16 */
	volatile u32 DOUT19_16;

	/** 0x1214 - Data output 23 to 20 */
	volatile u32 DOUT23_20;

	/** 0x1218 - Data output 27 to 24 */
	volatile u32 DOUT27_24;

	/** 0x121C - Data output 31 to 28 */
	volatile u32 DOUT31_28;

	const u32 pad9[24];

	/** 0x1280 - Data output 31 to 0 */
	volatile u32 DOUT31_0;

	const u32 pad10[3];

	/** 0x1290 - Data output set 31 to 0 */
	volatile u32 DOUTSET31_0;

	const u32 pad11[3];

	/** 0x12A0 - Data output clear 31 to 0 */
	volatile u32 DOUTCLR31_0;

	const u32 pad12[3];

	/** 0x12B0 - Data output toggle 31 to 0 */
	volatile u32 DOUTTGL31_0;

	const u32 pad13[3];

	/** 0x12C0 - Data output enable 31 to 0 */
	volatile u32 DOE31_0;

	const u32 pad14[3];

	/** 0x12D0 - Data output enable set 31 to 0 */
	volatile u32 DOESET31_0;

	const u32 pad15[3];

	/** 0x12E0 - Data output enable clear 31 to 0 */
	volatile u32 DOECLR31_0;

	const u32 pad16[7];

	/** 0x1300 - Data input 3 to 0 */
	volatile const u32 DIN3_0;

	/** 0x1304 - Data input 7 to 4 */
	volatile const u32 DIN7_4;

	/** 0x1308 - Data input 11 to 8 */
	volatile const u32 DIN11_8;

	/** 0x130C - Data input 15 to 12 */
	volatile const u32 DIN15_12;

	/** 0x1310 - Data input 19 to 16 */
	volatile const u32 DIN19_16;

	/** 0x1314 - Data input 23 to 20 */
	volatile const u32 DIN23_20;

	/** 0x1318 - Data input 27 to 24 */
	volatile const u32 DIN27_24;

	/** 0x131C - Data input 31 to 28 */
	volatile const u32 DIN31_28;

	const u32 pad17[24];

	/** 0x1380 - Data input 31 to 0 */
	volatile const u32 DIN31_0;

	const u32 pad18[3];

	/** 0x1390 - Polarity 15 to 0 */
	volatile u32 POLARITY15_0;

	const u32 pad19[3];

	/** 0x13A0 - Polarity 31 to 16 */
	volatile u32 POLARITY31_16;

	const u32 pad20[23];

	/** 0x1400 - FAST WAKE GLOBAL EN */
	volatile u32 CTL;

	/** 0x1404 - FAST WAKE ENABLE */
	volatile u32 FASTWAKE;

	const u32 pad21[62];

	/** 0x1500 - Subscriber 0 configuration */
	volatile u32 SUB0CFG;

	const u32 pad22;

	/** 0x1508 - Filter Enable 15 to 0 */
	volatile u32 FILTEREN15_0;

	/** 0x150C - Filter Enable 31 to 16 */
	volatile u32 FILTEREN31_16;

	/** 0x1510 - DMA Write MASK */
	volatile u32 DMAMASK;

	const u32 pad23[3];

	/** 0x1520 - Subscriber 1 configuration */
	volatile u32 SUB1CFG;
};

hal_static_assert_offset(struct hal_gpio_regs, FSUB_0, 0x400);
hal_static_assert_offset(struct hal_gpio_regs, FSUB_1, 0x404);
hal_static_assert_offset(struct hal_gpio_regs, FPUB_0, 0x444);
hal_static_assert_offset(struct hal_gpio_regs, FPUB_1, 0x448);
hal_static_assert_offset(struct hal_gpio_regs, PWREN, 0x800);
hal_static_assert_offset(struct hal_gpio_regs, RSTCTL, 0x804);
hal_static_assert_offset(struct hal_gpio_regs, STAT, 0x814);
hal_static_assert_offset(struct hal_gpio_regs, CLKOVR, 0x1010);
hal_static_assert_offset(struct hal_gpio_regs, PDBGCTL, 0x1018);
hal_static_assert_offset(struct hal_gpio_regs, CPU_INT.IIDX, 0x1020);
hal_static_assert_offset(struct hal_gpio_regs, CPU_INT.IMASK, 0x1028);
hal_static_assert_offset(struct hal_gpio_regs, CPU_INT.RIS, 0x1030);
hal_static_assert_offset(struct hal_gpio_regs, CPU_INT.MIS, 0x1038);
hal_static_assert_offset(struct hal_gpio_regs, CPU_INT.ISET, 0x1040);
hal_static_assert_offset(struct hal_gpio_regs, CPU_INT.ICLR, 0x1048);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT0.IIDX, 0x1050);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT0.IMASK, 0x1058);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT0.RIS, 0x1060);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT0.MIS, 0x1068);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT0.ISET, 0x1070);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT0.ICLR, 0x1078);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT1.IIDX, 0x1080);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT1.IMASK, 0x1088);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT1.RIS, 0x1090);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT1.MIS, 0x1098);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT1.ISET, 0x10A0);
hal_static_assert_offset(struct hal_gpio_regs, GEN_EVENT1.ICLR, 0x10A8);
hal_static_assert_offset(struct hal_gpio_regs, EVT_MODE, 0x10E0);
hal_static_assert_offset(struct hal_gpio_regs, DESC, 0x10FC);
hal_static_assert_offset(struct hal_gpio_regs, DOUT3_0, 0x1200);
hal_static_assert_offset(struct hal_gpio_regs, DOUT7_4, 0x1204);
hal_static_assert_offset(struct hal_gpio_regs, DOUT11_8, 0x1208);
hal_static_assert_offset(struct hal_gpio_regs, DOUT15_12, 0x120C);
hal_static_assert_offset(struct hal_gpio_regs, DOUT19_16, 0x1210);
hal_static_assert_offset(struct hal_gpio_regs, DOUT23_20, 0x1214);
hal_static_assert_offset(struct hal_gpio_regs, DOUT27_24, 0x1218);
hal_static_assert_offset(struct hal_gpio_regs, DOUT31_28, 0x121C);
hal_static_assert_offset(struct hal_gpio_regs, DOUT31_0, 0x1280);
hal_static_assert_offset(struct hal_gpio_regs, DOUTSET31_0, 0x1290);
hal_static_assert_offset(struct hal_gpio_regs, DOUTCLR31_0, 0x12A0);
hal_static_assert_offset(struct hal_gpio_regs, DOUTTGL31_0, 0x12B0);
hal_static_assert_offset(struct hal_gpio_regs, DOE31_0, 0x12C0);
hal_static_assert_offset(struct hal_gpio_regs, DOESET31_0, 0x12D0);
hal_static_assert_offset(struct hal_gpio_regs, DOECLR31_0, 0x12E0);
hal_static_assert_offset(struct hal_gpio_regs, DIN3_0, 0x1300);
hal_static_assert_offset(struct hal_gpio_regs, DIN7_4, 0x1304);
hal_static_assert_offset(struct hal_gpio_regs, DIN11_8, 0x1308);
hal_static_assert_offset(struct hal_gpio_regs, DIN15_12, 0x130C);
hal_static_assert_offset(struct hal_gpio_regs, DIN19_16, 0x1310);
hal_static_assert_offset(struct hal_gpio_regs, DIN23_20, 0x1314);
hal_static_assert_offset(struct hal_gpio_regs, DIN27_24, 0x1318);
hal_static_assert_offset(struct hal_gpio_regs, DIN31_28, 0x131C);
hal_static_assert_offset(struct hal_gpio_regs, DIN31_0, 0x1380);
hal_static_assert_offset(struct hal_gpio_regs, POLARITY15_0, 0x1390);
hal_static_assert_offset(struct hal_gpio_regs, POLARITY31_16, 0x13A0);
hal_static_assert_offset(struct hal_gpio_regs, CTL, 0x1400);
hal_static_assert_offset(struct hal_gpio_regs, FASTWAKE, 0x1404);
hal_static_assert_offset(struct hal_gpio_regs, SUB0CFG, 0x1500);
hal_static_assert_offset(struct hal_gpio_regs, FILTEREN15_0, 0x1508);
hal_static_assert_offset(struct hal_gpio_regs, FILTEREN31_16, 0x150C);
hal_static_assert_offset(struct hal_gpio_regs, DMAMASK, 0x1510);
hal_static_assert_offset(struct hal_gpio_regs, SUB1CFG, 0x1520);

/**
 * Sets a given bitmask of bits corresponding to GPIO pins low.
 *
 * @param pins The pins to set low.
 */
HAL_ALWAYS_INLINE void hal_gpio_pin_set_low(const enum hal_gpio_pin pins)
{
	HAL_GPIO0->DOUTCLR31_0 |= pins;
}

/**
 * Sets a given bitmask of bits corresponding to GPIO pins high.
 *
 * @param pins The pins to set high.
 */
HAL_ALWAYS_INLINE void hal_gpio_pin_set_high(const enum hal_gpio_pin pins)
{
	HAL_GPIO0->DOUTSET31_0 |= pins;
}

/**
 * Toggles a given bitmask of bits corresponding to GPIO pins.
 *
 * @param pins The pins to toggle.
 */
HAL_ALWAYS_INLINE void hal_gpio_pin_toggle(const enum hal_gpio_pin pins)
{
	HAL_GPIO0->DOUTTGL31_0 |= pins;
}

void hal_gpio_init(void);

void hal_gpio_cfg_pin(const struct hal_gpio_pin_cfg *cfg);

void hal_gpio_cfg_unused_pins(
	enum hal_gpio_unused_pin_cfg_strategy unused_pin_cfg_strategy,
	enum hal_gpio_unused_pin_cfg_debug_pins debug_pins);

/**
 * Defines the GPIO pins that should be configured when the HAL is initialized.
 */
extern const struct hal_gpio_pin_cfg hal_gpio_cfg_init[];

/** Defines the number of HAL GPIO configuration entries. */
extern const u32 hal_gpio_cfg_init_num_entries;
