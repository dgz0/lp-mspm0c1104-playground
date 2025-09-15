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

/** @file main.c Defines a simple blinky. */

#include <stdlib.h>
#include "cfg.h"

static void isr_on_user_button_pressed(void)
{
	hal_gpio_pin_toggle(APP_GPIO_PIN_RED_LED);
}

int main(void)
{
	hal_init();

	hal_gpio_pin_edge_detect_mode_set(APP_GPIO_PIN_BUTTON_USER,
					  HAL_GPIO_EDGE_DETECT_RISING,
					  isr_on_user_button_pressed);

	for (;;) {
		hal_no_op();
	}
	return EXIT_FAILURE;
}
