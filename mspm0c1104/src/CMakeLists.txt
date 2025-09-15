# SPDX-License-Identifier: MIT
#
# Copyright 2025 dgz
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the “Software”), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

set(SRCS
	hal.c
	hal-gpio.c
	hal-iomux.c
	hal-soft-tim.c
	hal-startup.c
	hal-systick.c
	hal-tim.c
)

set(HDRS
	${CMAKE_SOURCE_DIR}/mspm0c1104/include/mspm0c1104/hal-cfg.h
	${CMAKE_SOURCE_DIR}/mspm0c1104/include/mspm0c1104/hal-clk.h
	${CMAKE_SOURCE_DIR}/mspm0c1104/include/mspm0c1104/hal-compiler.h
	${CMAKE_SOURCE_DIR}/mspm0c1104/include/mspm0c1104/hal-gpio.h
	${CMAKE_SOURCE_DIR}/mspm0c1104/include/mspm0c1104/hal-iomux.h
	${CMAKE_SOURCE_DIR}/mspm0c1104/include/mspm0c1104/hal-irq.h
	${CMAKE_SOURCE_DIR}/mspm0c1104/include/mspm0c1104/hal-soft-tim.h
	${CMAKE_SOURCE_DIR}/mspm0c1104/include/mspm0c1104/hal-systick.h
	${CMAKE_SOURCE_DIR}/mspm0c1104/include/mspm0c1104/hal-tim.h
	${CMAKE_SOURCE_DIR}/mspm0c1104/include/mspm0c1104/hal-types.h
	${CMAKE_SOURCE_DIR}/mspm0c1104/include/mspm0c1104/hal.h
)

add_library(mspm0c1104 OBJECT ${SRCS} ${HDRS})

target_include_directories(
	mspm0c1104
	PUBLIC
	${CMAKE_SOURCE_DIR}/mspm0c1104/include
)
