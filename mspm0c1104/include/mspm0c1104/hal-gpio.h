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

#include "compiler.h"
#include "util.h"
#include "hal-iomux.h"

#define HAL_GPIO0 ((struct hal_gpio_regs *const)(0x400A0000))

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

struct hal_gpio_pin_digital_attrib {
	uint32_t func;
	bool data_inversion;
	bool hysteresis;
	enum hal_iomux_resistor_type resistor;
};

struct hal_gpio_pin {
	const uint32_t pin_idx;
	const enum hal_iomux_pin_idx iomux_idx;
};

struct hal_gpio_pin_cfg {
	const struct hal_gpio_pin *pin;
	bool input_enabled;
	const struct hal_gpio_pin_digital_attrib digital_attrib;
};

struct hal_gpio_regs_intr_grp {
	const uint32_t pad0;

	/** Interrupt index */
	volatile const uint32_t IIDX;

	const uint32_t pad1;

	/** Interrupt mask  */
	volatile uint32_t IMASK;

	const uint32_t pad2;

	/** Raw interrupt status */
	volatile const uint32_t RIS;

	const uint32_t pad3;

	/** Masked interrupt status */
	volatile const uint32_t MIS;

	const uint32_t pad4;

	/** Interrupt set */
	volatile uint32_t ISET;

	const uint32_t pad5;

	/** Interrupt clear */
	volatile uint32_t ICLR;
};

struct hal_gpio_regs {
	const uint32_t pad0[256];

	/** 0x400 - Subscriber Port 0 */
	volatile uint32_t FSUB_0;

	/** 0x404 - Subscriber Port 1 */
	volatile uint32_t FSUB_1;

	const uint32_t pad1[15];

	/** 0x444 - Publisher Port 0 */
	volatile uint32_t FPUB_0;

	/** 0x448 - Publisher Port 1 */
	volatile uint32_t FPUB_1;

	const uint32_t pad2[237];

	/** 0x800 - Power enable */
	volatile uint32_t PWREN;

	/** 0x804 - Reset Control */
	volatile uint32_t RSTCTL;

	const uint32_t pad3[3];

	/** 0x814 - Status Register */
	volatile const uint32_t STAT;

	const uint32_t pad4[510];

	/** 0x1010 - Clock Override */
	volatile uint32_t CLKOVR;

	const uint32_t pad5;

	/** 0x1018 - Peripheral Debug Control */
	volatile uint32_t PDBGCTL;

	/** 0x1020 - 0x1048: CPU_INT interrupt group */
	struct hal_gpio_regs_intr_grp CPU_INT;

	/** 0x1050 - 0x1078: GEN_EVENT0 interrupt group */
	struct hal_gpio_regs_intr_grp GEN_EVENT0;

	/** 0x1080 - 0x10A8: GEN_EVENT1 interrupt group */
	struct hal_gpio_regs_intr_grp GEN_EVENT1;

	const uint32_t pad6[13];

	/** 0x10E0 - Event mode */
	volatile const uint32_t EVT_MODE;

	const uint32_t pad7[6];

	/** 0x10FC - Module Description */
	volatile const uint32_t DESC;

	const uint32_t pad8[64];

	/** 0x1200 - Data output 3 to 0 */
	volatile uint32_t DOUT3_0;

	/** 0x1204 - Data output 7 to 4 */
	volatile uint32_t DOUT7_4;

	/** 0x1208 - Data output 11 to 8 */
	volatile uint32_t DOUT11_8;

	/** 0x120C - Data output 15 to 12 */
	volatile uint32_t DOUT15_12;

	/** 0x1210 - Data output 19 to 16 */
	volatile uint32_t DOUT19_16;

	/** 0x1214 - Data output 23 to 20 */
	volatile uint32_t DOUT23_20;

	/** 0x1218 - Data output 27 to 24 */
	volatile uint32_t DOUT27_24;

	/** 0x121C - Data output 31 to 28 */
	volatile uint32_t DOUT31_28;

	const uint32_t pad9[24];

	/** 0x1280 - Data output 31 to 0 */
	volatile uint32_t DOUT31_0;

	const uint32_t pad10[3];

	/** 0x1290 - Data output set 31 to 0 */
	volatile uint32_t DOUTSET31_0;

	const uint32_t pad11[3];

	/** 0x12A0 - Data output clear 31 to 0 */
	volatile uint32_t DOUTCLR31_0;

	const uint32_t pad12[3];

	/** 0x12B0 - Data output toggle 31 to 0 */
	volatile uint32_t DOUTTGL31_0;

	const uint32_t pad13[3];

	/** 0x12C0 - Data output enable 31 to 0 */
	volatile uint32_t DOE31_0;

	const uint32_t pad14[3];

	/** 0x12D0 - Data output enable set 31 to 0 */
	volatile uint32_t DOESET31_0;

	const uint32_t pad15[3];

	/** 0x12E0 - Data output enable clear 31 to 0 */
	volatile uint32_t DOECLR31_0;

	const uint32_t pad16[7];

	/** 0x1300 - Data input 3 to 0 */
	volatile const uint32_t DIN3_0;

	/** 0x1304 - Data input 7 to 4 */
	volatile const uint32_t DIN7_4;

	/** 0x1308 - Data input 11 to 8 */
	volatile const uint32_t DIN11_8;

	/** 0x130C - Data input 15 to 12 */
	volatile const uint32_t DIN15_12;

	/** 0x1310 - Data input 19 to 16 */
	volatile const uint32_t DIN19_16;

	/** 0x1314 - Data input 23 to 20 */
	volatile const uint32_t DIN23_20;

	/** 0x1318 - Data input 27 to 24 */
	volatile const uint32_t DIN27_24;

	/** 0x131C - Data input 31 to 28 */
	volatile const uint32_t DIN31_28;

	const uint32_t pad17[24];

	/** 0x1380 - Data input 31 to 0 */
	volatile const uint32_t DIN31_0;

	const uint32_t pad18[3];

	/** 0x1390 - Polarity 15 to 0 */
	volatile uint32_t POLARITY15_0;

	const uint32_t pad19[3];

	/** 0x13A0 - Polarity 31 to 16 */
	volatile uint32_t POLARITY31_16;

	const uint32_t pad20[23];

	/** 0x1400 - FAST WAKE GLOBAL EN */
	volatile uint32_t CTL;

	/** 0x1404 - FAST WAKE ENABLE */
	volatile uint32_t FASTWAKE;

	const uint32_t pad21[62];

	/** 0x1500 - Subscriber 0 configuration */
	volatile uint32_t SUB0CFG;

	const uint32_t pad22;

	/** 0x1508 - Filter Enable 15 to 0 */
	volatile uint32_t FILTEREN15_0;

	/** 0x150C - Filter Enable 31 to 16 */
	volatile uint32_t FILTEREN31_16;

	/** 0x1510 - DMA Write MASK */
	volatile uint32_t DMAMASK;

	const uint32_t pad23[3];

	/** 0x1520 - Subscriber 1 configuration */
	volatile uint32_t SUB1CFG;
};

STATIC_ASSERT_OFFSET(struct hal_gpio_regs, FSUB_0, 0x400);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, FSUB_1, 0x404);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, FPUB_0, 0x444);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, FPUB_1, 0x448);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, PWREN, 0x800);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, RSTCTL, 0x804);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, STAT, 0x814);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, CLKOVR, 0x1010);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, PDBGCTL, 0x1018);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, CPU_INT.IIDX, 0x1020);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, CPU_INT.IMASK, 0x1028);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, CPU_INT.RIS, 0x1030);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, CPU_INT.MIS, 0x1038);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, CPU_INT.ISET, 0x1040);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, CPU_INT.ICLR, 0x1048);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT0.IIDX, 0x1050);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT0.IMASK, 0x1058);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT0.RIS, 0x1060);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT0.MIS, 0x1068);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT0.ISET, 0x1070);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT0.ICLR, 0x1078);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT1.IIDX, 0x1080);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT1.IMASK, 0x1088);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT1.RIS, 0x1090);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT1.MIS, 0x1098);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT1.ISET, 0x10A0);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, GEN_EVENT1.ICLR, 0x10A8);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, EVT_MODE, 0x10E0);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DESC, 0x10FC);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUT3_0, 0x1200);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUT7_4, 0x1204);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUT11_8, 0x1208);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUT15_12, 0x120C);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUT19_16, 0x1210);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUT23_20, 0x1214);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUT27_24, 0x1218);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUT31_28, 0x121C);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUT31_0, 0x1280);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUTSET31_0, 0x1290);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUTCLR31_0, 0x12A0);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOUTTGL31_0, 0x12B0);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOE31_0, 0x12C0);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOESET31_0, 0x12D0);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DOECLR31_0, 0x12E0);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DIN3_0, 0x1300);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DIN7_4, 0x1304);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DIN11_8, 0x1308);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DIN15_12, 0x130C);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DIN19_16, 0x1310);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DIN23_20, 0x1314);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DIN27_24, 0x1318);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DIN31_28, 0x131C);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DIN31_0, 0x1380);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, POLARITY15_0, 0x1390);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, POLARITY31_16, 0x13A0);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, CTL, 0x1400);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, FASTWAKE, 0x1404);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, SUB0CFG, 0x1500);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, FILTEREN15_0, 0x1508);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, FILTEREN31_16, 0x150C);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, DMAMASK, 0x1510);
STATIC_ASSERT_OFFSET(struct hal_gpio_regs, SUB1CFG, 0x1520);

ALWAYS_INLINE void hal_gpio_pin_set_low(const struct hal_gpio_pin *const pin)
{
	HAL_GPIO0->DOUTCLR31_0 |= pin->pin_idx;
}

ALWAYS_INLINE void hal_gpio_pin_set_high(const struct hal_gpio_pin *const pin)
{
	HAL_GPIO0->DOUTSET31_0 |= pin->pin_idx;
}

ALWAYS_INLINE void hal_gpio_pin_toggle(const struct hal_gpio_pin *const pin)
{
	HAL_GPIO0->DOUTTGL31_0 |= pin->pin_idx;
}

extern const struct hal_gpio_pin HAL_GPIO_PIN_PA0;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA1;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA2;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA4;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA6;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA11;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA16;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA17;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA18;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA19;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA20;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA22;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA23;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA24;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA25;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA26;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA27;
extern const struct hal_gpio_pin HAL_GPIO_PIN_PA28;

extern const struct hal_gpio_pin_cfg hal_gpio_cfg_initial[];
extern const uint32_t hal_gpio_cfg_initial_num_entries;

void hal_gpio_init(void);

void hal_gpio_cfg_unused_pins(
	enum hal_gpio_unused_pin_cfg_strategy unused_pin_cfg_strategy);
