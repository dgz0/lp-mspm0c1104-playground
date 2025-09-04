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

# The minimum required CMake version should be tied to the latest CMake version
# distributed in the package repositories of the oldest currently supported
# Ubuntu LTS release. This is done for several reasons:
#
# a) Ubuntu LTS releases are guaranteed standard support for 5 years. It is
#    reasonable to align ourselves with minimum versions from a specific
#    distribution due to the various permutations of the Linux ecosystem. We
#    cannot support every configuration, and since Ubuntu is widely used, we've
#    chosen to align ourselves with it. We do not want to fall into a rabbit
#    hole of trying to support system configurations from 10 years ago; 5 years
#    is a reasonable timeframe.
#
#    At the time of this writing, the oldest currently supported Ubuntu LTS
#    release is Ubuntu 22.04 LTS (Jammy Jellyfish). The CMake version should be
#    bumped to whatever is in the Ubuntu 24.04 (Noble Numbat) package
#    repositories once 22.04 reaches the end of standard support.
#
# b) Some IDEs (e.g., JetBrains CLion) ship their own bundled version of CMake,
#    and we want to support those out of the box as best as we possibly can.
#
# The FATAL_ERROR option is accepted but ignored by CMake 2.6 and higher. It
# should be specified so CMake versions 2.4 and lower fail with an error instead
# of just a warning.
cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

if (NOT CMAKE_TOOLCHAIN_FILE)
	message(FATAL_ERROR "A toolchain file is required to be specified")
endif()

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR
		"In-tree builds are not supported. Please create a "
		"separate build directory and run CMake from there.")
endif()

if (CMAKE_VERSION LESS "3.26")
	# CMake versions >=3.26 set this property to ON by default.
	set(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

project(
	lp-mspm0c1104-playground
	VERSION 1.0.0.0
	DESCRIPTION "LP-MSPM0C1104 Playground"
	HOMEPAGE_URL "https://github.com/dgz0/lp-mspm0c1104-playground"
	LANGUAGES C
)

# Build the MSPM0C1104 support library first; examples of course rely on it.
add_subdirectory(mspm0c1104)
add_subdirectory(examples)
