/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2017 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SIFIVE_ARTY_BOARDS_DEFINES_H_
#define SIFIVE_ARTY_BOARDS_DEFINES_H_

// ----------------------------------------------------------------------------

#if defined(SIFIVE_E31ARTY_BOARD)
#elif defined(SIFIVE_E51ARTY_BOARD)
#else
#error "Only SIFIVE_E31ARTY_BOARD and SIFIVE_E51ARTY_BOARD are supported."
#endif /* _BOARD */

// ----------------------------------------------------------------------------

#define RISCV_BOARD_RTC_FREQUENCY_HZ		(32768)

// ----------------------------------------------------------------------------
// Definitions from SiFive bsp/env/coreplexip-arty.h

// TODO: possibly rework, to make them consistent with device definitions.

/****************************************************************************
 * GPIO Connections
 *****************************************************************************/

// These are the GPIO bit offsets for the directly driven
// RGB LEDs on the Freedom Exx Core Complex IP Evaluation Arty FPGA Dev Kit.
// Additional RGB LEDs are driven by the 3 PWM outputs.

// The LEDs are active high.
#define RED_LED_OFFSET   0
#define GREEN_LED_OFFSET 1
#define BLUE_LED_OFFSET  2

// Switch 3 is used as a GPIO input. (Switch 0 is used to set
// the reset vector, the other switches are unused).

#define SW_3_OFFSET      3

// These are the buttons which are mapped as inputs.

#define HAS_BOARD_BUTTONS

// The buttons are active high.
#define BUTTON_0_OFFSET  4
#define BUTTON_1_OFFSET  5
#define BUTTON_2_OFFSET  6
#define BUTTON_3_OFFSET  7

// These are the bit offsets for the different GPIO pins
// mapped onto the PMOD A header.

#define JA_0_OFFSET 8
#define JA_1_OFFSET 9
#define JA_2_OFFSET 10
#define JA_3_OFFSET 11
#define JA_4_OFFSET 12
#define JA_5_OFFSET 13
#define JA_6_OFFSET 14
#define JA_7_OFFSET 15

// The below gives a mapping between global interrupt
// sources and their number. Note that on the core complex
// deliverable, the io_global_interrupts go directly into
// the PLIC. The evaluation image on the FPGA mimics a
// system with peripheral devices which are driving the
// global interrupt lines.
// So, on this image, in order to get an interrupt from
// e.g. pressing BUTTON_0:
// 1) Steps which are external to the delivery coreplex:
//   a) The corresponding GPIO pin must be configured as in input
//   b) The "interrupt on fall" bit must be set for the GPIO pin
// 2) Steps which would also need to be performed for the delivery coreplex:
//   a) The corresponding global interrupt, priority, and threshold must be configured in the PLIC.
//   b) The external interrupt bit must be enabled in MSTATUS
//   c) Interrupts must be enabled globally in the core.

// Any of the above GPIO pins can be used as global interrupt
// sources by adding their offset to the INT_GPIO_BASE.
// For example, the buttons are shown here:

#if defined(SIFIVE_E31ARTY_BOARD)

#define INT_DEVICE_BUTTON_0 (sifive_e31arty_interrupt_global_gpio0 + BUTTON_0_OFFSET)
#define INT_DEVICE_BUTTON_1 (sifive_e31arty_interrupt_global_gpio0 + BUTTON_1_OFFSET)
#define INT_DEVICE_BUTTON_2 (sifive_e31arty_interrupt_global_gpio0 + BUTTON_2_OFFSET)
#define INT_DEVICE_BUTTON_3 (sifive_e31arty_interrupt_global_gpio0 + BUTTON_3_OFFSET)

#elif defined(SIFIVE_E51ARTY_BOARD)

#define INT_DEVICE_BUTTON_0 (sifive_e51arty_interrupt_global_gpio0 + BUTTON_0_OFFSET)
#define INT_DEVICE_BUTTON_1 (sifive_e51arty_interrupt_global_gpio0 + BUTTON_1_OFFSET)
#define INT_DEVICE_BUTTON_2 (sifive_e51arty_interrupt_global_gpio0 + BUTTON_2_OFFSET)
#define INT_DEVICE_BUTTON_3 (sifive_e51arty_interrupt_global_gpio0 + BUTTON_3_OFFSET)

#endif

// In addition, the Switches are mapped directly to
// the PLIC (without going through the GPIO Peripheral).

#if defined(SIFIVE_E31ARTY_BOARD)

#define INT_EXT_DEVICE_SW_0 (sifive_e31arty_interrupt_global_switch0)
#define INT_EXT_DEVICE_SW_1 (sifive_e31arty_interrupt_global_switch1)
#define INT_EXT_DEVICE_SW_2 (sifive_e31arty_interrupt_global_switch2)
#define INT_EXT_DEVICE_SW_3 (sifive_e31arty_interrupt_global_switch3)

#elif defined(SIFIVE_E51ARTY_BOARD)

#define INT_EXT_DEVICE_SW_0 (sifive_e51arty_interrupt_global_switch0)
#define INT_EXT_DEVICE_SW_1 (sifive_e51arty_interrupt_global_switch1)
#define INT_EXT_DEVICE_SW_2 (sifive_e51arty_interrupt_global_switch2)
#define INT_EXT_DEVICE_SW_3 (sifive_e51arty_interrupt_global_switch3)

#endif

// This gives the mapping from inputs to LOCAL interrupts.

#define LOCAL_INT_SW_0   0
#define LOCAL_INT_SW_1   1
#define LOCAL_INT_SW_2   2
#define LOCAL_INT_SW_3   3
#define LOCAL_INT_BTN_0  4
#define LOCAL_INT_BTN_1  5
#define LOCAL_INT_BTN_2  6
#define LOCAL_INT_BTN_3  7
#define LOCAL_INT_JA_0   8
#define LOCAL_INT_JA_1   9
#define LOCAL_INT_JA_2   10
#define LOCAL_INT_JA_3   11
#define LOCAL_INT_JA_4   12
#define LOCAL_INT_JA_5   13
#define LOCAL_INT_JA_6   14
#define LOCAL_INT_JA_7   15

// #define RTC_FREQ 32768

// ----------------------------------------------------------------------------

#endif /* SIFIVE_ARTY_BOARDS_DEFINES_H_ */
