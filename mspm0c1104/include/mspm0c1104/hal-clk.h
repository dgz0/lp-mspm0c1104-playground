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

/**
 * @file hal-clk.h Defines the clock frequencies of the LP-MSPM0C1104.
 *
 * The default operating configuration of the device provides basic
 * functionality which can be suitable for many applications without
 * modification.
 *
 * MSPM0Cxx devices power up and release reset for execution of application code
 * when the external supply (VDD and VSS) reaches 1.62V. When the application
 * code is released for execution, the device is in RUN mode with MCLK, which is
 * sourced from the internal SYSOSC at the max operating frequency. The CPUCLK
 * and ULPCLK are also at the max operating frequency, derived from MCLK. LFCLK
 * starts automatically, sourced from the internal LFOSC. In RUN mode with the
 * default configuration, all peripherals are available to be enabled.
 * Peripherals such as the DMA and CRC run directly from MCLK at the MCLK rate.
 * Other peripherals, such as timers and serial interfaces, can run from the bus
 * clock or from the low-frequency 32kHz clock (LFCLK) based on their peripheral
 * clock selection.
 */

#pragma once

#include "util.h"

#define HAL_FREQ_CPUCLK_HZ (MHZ_TO_HZ(24))
#define HAL_FREQ_ULPCLK_HZ (HAL_FREQ_CPUCLK_HZ)
#define HAL_FREQ_LFCLK_HZ (32770)
