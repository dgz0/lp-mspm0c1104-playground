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

#include <mspm0c1104/hal-clk.h>
#include <mspm0c1104/hal-irq.h>
#include <mspm0c1104/hal-tim.h>

// clang-format off

#define HAL_TIMG14	((struct tim_regs *const)(0x40084000))
#define HAL_TIMG8	((struct tim_regs *const)(0x40090000))
#define HAL_TIMA0	((struct tim_regs *const)(0x40860000))

#define HAL_TIM_PWREN_MASK_KEY_SHIFT	(24)
#define HAL_TIM_PWREN_MASK_KEY		((0x26) << HAL_TIM_PWREN_MASK_KEY_SHIFT)

#define HAL_TIM_PWREN_BIT_ENABLE	(HAL_BIT_0)

#define HAL_TIM_RSTCTL_MASK_KEY		(0xB1 << 24)
#define HAL_TIM_RSTCTL_BIT_RESETASSERT	(HAL_BIT_0)

#define HAL_TIM_CLKDIV_MASK_RATIO	(HAL_BIT_2 | HAL_BIT_1 | HAL_BIT_0)

#define HAL_TIM_CCLKCTL_BIT_CLKEN	(HAL_BIT_0)

#define TIM_INSTANCE_TIMG8 (HAL_TIM_INSTANCE_TIM0)
#define TIM_INSTANCE_TIMG14 (HAL_TIM_INSTANCE_TIM1)
#define TIM_INSTANCE_TIMA0 (HAL_TIM_INSTANCE_TIM2)

enum tim_clk_src {
	HAL_TIM_CLK_SRC_LFCLK	= HAL_BIT_1,
	HAL_TIM_CLK_SRC_MFCLK	= HAL_BIT_2,
	HAL_TIM_CLK_SRC_BUSCLK	= HAL_BIT_3
};

enum tim_clk_div {
	HAL_TIM_CLK_DIV_1	= 0x0,
	HAL_TIM_CLK_DIV_2	= 0x1,
	HAL_TIM_CLK_DIV_3	= 0x2,
	HAL_TIM_CLK_DIV_4	= 0x3,
	HAL_TIM_CLK_DIV_5	= 0x4,
	HAL_TIM_CLK_DIV_6	= 0x5,
	HAL_TIM_CLK_DIV_7	= 0x6,
	HAL_TIM_CLK_DIV_8	= 0x7,
	HAL_TIM_CLK_DIV_MAX
};

// clang-format on

struct hal_tim_reg_intr_group {
	const u32 pad0;

	/** Interrupt index */
	volatile const u32 IIDX;

	const u32 pad1;

	/** Interrupt mask */
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

struct tim_regs {
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

	const u32 pad4[506];

	/** 0x1000 - Clock Divider */
	volatile u32 CLKDIV;

	const u32 pad5;

	/** 0x1008 - Clock Select for Ultra Low Power peripherals */
	volatile u32 CLKSEL;

	const u32 pad6[3];

	/** 0x1018 - Peripheral Debug Control */
	volatile u32 PDBGCTL;

	/** 0x1020 - 0x1048: CPU_INT register group */
	struct hal_tim_reg_intr_group CPU_INT;

	/** 0x1050 - 0x1078: GEN_EVENT0 register group */
	struct hal_tim_reg_intr_group GEN_EVENT0;

	/** 0x1080 - 0x10A8: GEN_EVENT1 register group */
	struct hal_tim_reg_intr_group GEN_EVENT1;

	const u32 pad7[13];

	/** 0x10E0 - Event Mode */
	volatile const u32 EVT_MODE;

	const u32 pad8[6];

	/** 0x10FC - Module Description */
	volatile const u32 DESC;

	/** 0x1100 - CCP Direction */
	volatile u32 CCPD;

	/** 0x1104 - Output Disable */
	volatile u32 ODIS;

	/** 0x1108 - Counter Clock Control Register */
	volatile u32 CCLKCTL;

	/** 0x110C - Clock Prescale Register */
	volatile u32 CPS;

	/** 0x1110 - Clock prescale count status register */
	volatile const u32 CPSV;

	/** 0x1114 - Timer Cross Trigger Control Register */
	volatile u32 CTTRIGCTL;

	const u32 pad9;

	/** 0x111C - Timer Cross Trigger Register */
	volatile u32 CTTRIG;

	/** 0x1120 - Fault Source Control */
	volatile u32 FSCTL;

	/** 0x1124 - Global control register */
	volatile u32 GCTL;

	const u32 pad10[438];

	/** 0x1800 - Counter Register */
	volatile u32 CTR;

	/** 0x1804 - Counter Control Register */
	volatile u32 CTRCTL;

	/** 0x1808 - Load Register */
	volatile u32 LOAD;

	const u32 pad11;

	/** 0x1810 - 0x1824: Capture or Compare Register 0-5 */
	volatile u32 CC[6];

	const u32 pad12[2];

	/** 0x1830 - 0x1844: Capture or Compare Control Registers 0-5 */
	volatile u32 CCCTL[6];

	const u32 pad13[2];

	/** 0x1850 - 0x185C: CCP Output Control Registers 0-3 */
	volatile u32 OCTL[4];

	const u32 pad14[4];

	/** 0x1870 - 0x187C: Capture or Compare Action Registers 0-3 */
	volatile u32 CCACT[4];

	/** 0x1880 - 0x188C: Input Filter Control Register 0-3 */
	volatile u32 IFCTL[4];

	const u32 pad15[4];

	/** 0x18A0 - Phase Load Register */
	volatile u32 PL;

	/** 0x18A4 - Dead Band insertion control register */
	volatile u32 DBCTL;

	const u32 pad16[2];

	/** 0x18B0 - Trigger Select Register */
	volatile u32 TSEL;

	/** 0x18B4 - Repeat counter Register */
	volatile const u32 RC;

	/** 0x18B8 - Repeat counter load Register */
	volatile u32 RCLD;

	/** 0x18BC - QEI Count Direction Register */
	volatile const u32 QDIR;

	const u32 pad17[4];

	/** 0x18D0 - Fault Control Register */
	volatile u32 FCTL;

	/** 0x18D4 - Fault input Filter control register */
	volatile u32 FIFCTL;
};

hal_static_assert_offset(struct tim_regs, FSUB_0, 0x400);
hal_static_assert_offset(struct tim_regs, FSUB_1, 0x404);
hal_static_assert_offset(struct tim_regs, FPUB_0, 0x444);
hal_static_assert_offset(struct tim_regs, FPUB_1, 0x448);
hal_static_assert_offset(struct tim_regs, PWREN, 0x800);
hal_static_assert_offset(struct tim_regs, RSTCTL, 0x804);
hal_static_assert_offset(struct tim_regs, STAT, 0x814);
hal_static_assert_offset(struct tim_regs, CLKDIV, 0x1000);
hal_static_assert_offset(struct tim_regs, CLKSEL, 0x1008);
hal_static_assert_offset(struct tim_regs, PDBGCTL, 0x1018);
hal_static_assert_offset(struct tim_regs, CPU_INT.IIDX, 0x1020);
hal_static_assert_offset(struct tim_regs, CPU_INT.IMASK, 0x1028);
hal_static_assert_offset(struct tim_regs, CPU_INT.RIS, 0x1030);
hal_static_assert_offset(struct tim_regs, CPU_INT.MIS, 0x1038);
hal_static_assert_offset(struct tim_regs, CPU_INT.ISET, 0x1040);
hal_static_assert_offset(struct tim_regs, CPU_INT.ICLR, 0x1048);
hal_static_assert_offset(struct tim_regs, GEN_EVENT0.IIDX, 0x1050);
hal_static_assert_offset(struct tim_regs, GEN_EVENT0.IMASK, 0x1058);
hal_static_assert_offset(struct tim_regs, GEN_EVENT0.RIS, 0x1060);
hal_static_assert_offset(struct tim_regs, GEN_EVENT0.MIS, 0x1068);
hal_static_assert_offset(struct tim_regs, GEN_EVENT0.ISET, 0x1070);
hal_static_assert_offset(struct tim_regs, GEN_EVENT0.ICLR, 0x1078);
hal_static_assert_offset(struct tim_regs, GEN_EVENT1.IIDX, 0x1080);
hal_static_assert_offset(struct tim_regs, GEN_EVENT1.IMASK, 0x1088);
hal_static_assert_offset(struct tim_regs, GEN_EVENT1.RIS, 0x1090);
hal_static_assert_offset(struct tim_regs, GEN_EVENT1.MIS, 0x1098);
hal_static_assert_offset(struct tim_regs, GEN_EVENT1.ISET, 0x10A0);
hal_static_assert_offset(struct tim_regs, GEN_EVENT1.ICLR, 0x10A8);
hal_static_assert_offset(struct tim_regs, EVT_MODE, 0x10E0);
hal_static_assert_offset(struct tim_regs, DESC, 0x10FC);
hal_static_assert_offset(struct tim_regs, CCPD, 0x1100);
hal_static_assert_offset(struct tim_regs, ODIS, 0x1104);
hal_static_assert_offset(struct tim_regs, CCLKCTL, 0x1108);
hal_static_assert_offset(struct tim_regs, CPS, 0x110C);
hal_static_assert_offset(struct tim_regs, CPSV, 0x1110);
hal_static_assert_offset(struct tim_regs, CTTRIGCTL, 0x1114);
hal_static_assert_offset(struct tim_regs, CTTRIG, 0x111C);
hal_static_assert_offset(struct tim_regs, FSCTL, 0x1120);
hal_static_assert_offset(struct tim_regs, GCTL, 0x1124);
hal_static_assert_offset(struct tim_regs, CTR, 0x1800);
hal_static_assert_offset(struct tim_regs, CTRCTL, 0x1804);
hal_static_assert_offset(struct tim_regs, LOAD, 0x1808);
hal_static_assert_offset(struct tim_regs, CC[0], 0x1810);
hal_static_assert_offset(struct tim_regs, CC[1], 0x1814);
hal_static_assert_offset(struct tim_regs, CC[2], 0x1818);
hal_static_assert_offset(struct tim_regs, CC[3], 0x181C);
hal_static_assert_offset(struct tim_regs, CC[4], 0x1820);
hal_static_assert_offset(struct tim_regs, CC[5], 0x1824);
hal_static_assert_offset(struct tim_regs, CCCTL[0], 0x1830);
hal_static_assert_offset(struct tim_regs, CCCTL[1], 0x1834);
hal_static_assert_offset(struct tim_regs, CCCTL[2], 0x1838);
hal_static_assert_offset(struct tim_regs, CCCTL[3], 0x183C);
hal_static_assert_offset(struct tim_regs, CCCTL[4], 0x1840);
hal_static_assert_offset(struct tim_regs, CCCTL[5], 0x1844);
hal_static_assert_offset(struct tim_regs, OCTL[0], 0x1850);
hal_static_assert_offset(struct tim_regs, OCTL[1], 0x1854);
hal_static_assert_offset(struct tim_regs, OCTL[2], 0x1858);
hal_static_assert_offset(struct tim_regs, OCTL[3], 0x185C);
hal_static_assert_offset(struct tim_regs, CCACT[0], 0x1870);
hal_static_assert_offset(struct tim_regs, CCACT[1], 0x1874);
hal_static_assert_offset(struct tim_regs, CCACT[2], 0x1878);
hal_static_assert_offset(struct tim_regs, CCACT[3], 0x187C);
hal_static_assert_offset(struct tim_regs, IFCTL[0], 0x1880);
hal_static_assert_offset(struct tim_regs, IFCTL[1], 0x1884);
hal_static_assert_offset(struct tim_regs, IFCTL[2], 0x1888);
hal_static_assert_offset(struct tim_regs, IFCTL[3], 0x188C);
hal_static_assert_offset(struct tim_regs, PL, 0x18A0);
hal_static_assert_offset(struct tim_regs, DBCTL, 0x18A4);
hal_static_assert_offset(struct tim_regs, TSEL, 0x18B0);
hal_static_assert_offset(struct tim_regs, RC, 0x18B4);
hal_static_assert_offset(struct tim_regs, RCLD, 0x18B8);
hal_static_assert_offset(struct tim_regs, QDIR, 0x18BC);
hal_static_assert_offset(struct tim_regs, FCTL, 0x18D0);
hal_static_assert_offset(struct tim_regs, FIFCTL, 0x18D4);

static struct tim_instance {
	const enum hal_tim_instance id;
	const enum hal_irq irq;
	struct tim_regs *const regs;
	void (*cb)(void);
} tim_list[] = {
	// clang-format off

	[HAL_TIM_INSTANCE_TIM0] = {
		.id		= HAL_TIM_INSTANCE_TIM0,
		.irq		= HAL_IRQ_TIMG8,
		.regs		= HAL_TIMG8
	},

	[HAL_TIM_INSTANCE_TIM1] = {
		.id		= HAL_TIM_INSTANCE_TIM1,
		.irq		= HAL_IRQ_TIMG14,
		.regs		= HAL_TIMG14
	},

	[HAL_TIM_INSTANCE_TIM2] = {
		.id		= HAL_TIM_INSTANCE_TIM2,
		.irq		= HAL_IRQ_TIMA0,
		.regs		= HAL_TIMA0
	}

	// clang-format on
};

struct tim_clk_cfg {
	u16 psc;
	u16 divider;
	enum tim_clk_src clk_src;
	u32 clk_freq;
};

void hal_isr_TIMG8(void)
{
	tim_list[TIM_INSTANCE_TIMG8].cb();
}

void hal_isr_TIMG14(void)
{
	tim_list[TIM_INSTANCE_TIMG14].cb();
}

void hal_isr_TIMA0(void)
{
	tim_list[TIM_INSTANCE_TIMA0].cb();
}

static bool tim_pwr_enabled(const struct tim_regs *const regs)
{
	return regs->PWREN & HAL_TIM_PWREN_BIT_ENABLE;
}

static void tim_pwr_enable(struct tim_regs *const regs)
{
	regs->PWREN = HAL_TIM_PWREN_MASK_KEY | HAL_TIM_PWREN_BIT_ENABLE;
}

static void tim_rst(struct tim_regs *const regs)
{
	regs->RSTCTL = HAL_TIM_RSTCTL_MASK_KEY | HAL_TIM_RSTCTL_BIT_RESETASSERT;
}

static void tim_clk_src_set(struct tim_regs *const regs,
			    const enum tim_clk_src clk_src)
{
	hal_assert(tim_pwr_enabled(regs));

	regs->CLKSEL &= ~(HAL_TIM_CLK_SRC_LFCLK | HAL_TIM_CLK_SRC_MFCLK |
			  HAL_TIM_CLK_SRC_BUSCLK);

	regs->CLKSEL |= clk_src;
}

static void tim_clk_div_set(struct tim_regs *const regs,
			    const enum tim_clk_div clk_div)
{
	hal_assert(tim_pwr_enabled(regs));
	hal_assert(clk_div < HAL_TIM_CLK_DIV_MAX);

	hal_set_val_by_mask(regs->CLKDIV, HAL_TIM_CLKDIV_MASK_RATIO, clk_div);
}

static void tim_prescaler_set(struct tim_regs *const regs, const u8 prescaler)
{
	regs->CPS = prescaler;
}

static bool calc_prescaler_and_divider(const u32 clk_freq_hz,
				       const u64 timeout_ns,
				       struct tim_clk_cfg *const cfg)
{
	const u64 tmp = timeout_ns * clk_freq_hz;
	u32 psc_mul_div =
		(uint32_t)((tmp + (UINT16_MAX + 1) * hal_sec_to_ns(1) - 1) /
			   ((UINT16_MAX + 1) * hal_sec_to_ns(1)));

	if (psc_mul_div == 0)
		psc_mul_div = 1;

	u32 div = (psc_mul_div + UINT8_MAX) / (UINT8_MAX + 1);
	if (div < 1)
		div = 1;
	else if (div > 8)
		return false;

	u32 prescaler = (psc_mul_div + div - 1) / div;
	if (prescaler < 1)
		prescaler = 1;
	else if (prescaler > 256)
		return false;

	cfg->psc = (uint16_t)prescaler;
	cfg->divider = (uint16_t)div;

	return true;
}

/** Calculates the correct clock source, clock divider, and prescaler. */
static bool calc_tim_clk_cfg(const u64 timeout, struct tim_clk_cfg *const cfg)
{
	static const struct clk_data {
		const enum hal_clk_freq freq;
		const enum tim_clk_src src;
	} clk_list[] = {
		// clang-format off

		[0] = {
			.freq	= HAL_CLK_FREQ_ULPCLK_HZ,
			.src	= HAL_TIM_CLK_SRC_BUSCLK
		},

		[1] = {
			.freq	= HAL_CLK_FREQ_LFCLK_HZ,
			.src	= HAL_TIM_CLK_SRC_LFCLK
		}

		// clang-format on
	};

	for (u32 i = 0; i < hal_array_size(clk_list); ++i) {
		const struct clk_data *const clk = &clk_list[i];

		if (calc_prescaler_and_divider(clk->freq, timeout, cfg)) {
			cfg->clk_src = clk->src;
			cfg->clk_freq = clk->freq / cfg->psc / cfg->divider;

			return true;
		}
	}
	return false;
}

HAL_NODISCARD static struct tim_instance *find_unused_tim(void)
{
	for (uint32_t i = 0; i < hal_array_size(tim_list); ++i) {
		struct tim_instance *const tim = &tim_list[i];

		if (!tim_pwr_enabled(tim->regs))
			return tim;
	}
	return NULL;
}

void hal_tim_init(void)
{
	for (u32 i = 0; i < hal_array_size(tim_list); ++i)
		tim_rst(tim_list[i].regs);
}

void hal_tim_start(const enum hal_tim_instance tim)
{
	// This timer was not initialized by the application.
	hal_assert(tim_pwr_enabled(tim_list[tim].regs) == true);

	hal_irq_en(tim_list[tim].irq);
	tim_list[tim].regs->CTRCTL |= (1 << 0);
}

HAL_NODISCARD enum hal_tim_instance
hal_tim_init_basic(const struct hal_tim_cfg_basic *const cfg)
{
	struct tim_clk_cfg clk_cfg;
	struct tim_instance *tim = NULL;

	for (uint32_t i = 0; i < hal_array_size(tim_list); ++i) {
		tim = find_unused_tim();

		if ((tim) && calc_tim_clk_cfg(cfg->timeout, &clk_cfg))
			break;
	}

	// Either all the hardware timers are in use, or none of the available
	// timers can accommodate the desired configuration.
	hal_assert(tim != NULL);

	tim_rst(tim->regs);
	tim_pwr_enable(tim->regs);

	tim_prescaler_set(tim->regs, clk_cfg.psc);
	tim_clk_src_set(tim->regs, clk_cfg.clk_src);
	tim_clk_div_set(tim->regs, clk_cfg.divider - 1);

	tim->regs->CTRCTL = 0;
	tim->regs->LOAD =
		((cfg->timeout * clk_cfg.clk_freq) / hal_sec_to_ns(1)) - 1;

	tim->regs->CPU_INT.IMASK |= (1 << 0);

	if (cfg->repeating)
		hal_set_val_by_mask(tim->regs->CTRCTL, 0x0000000E, 1);

	tim->regs->CCLKCTL |= HAL_TIM_CCLKCTL_BIT_CLKEN;

	tim->cb = cfg->cb;
	return tim->id;
}
