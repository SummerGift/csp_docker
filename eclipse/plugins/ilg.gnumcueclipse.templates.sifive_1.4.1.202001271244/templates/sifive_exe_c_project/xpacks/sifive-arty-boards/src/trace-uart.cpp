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

#if defined(TRACE)

#if defined(OS_USE_TRACE_UART0)

#include <micro-os-plus/device.h>
#include <micro-os-plus/diag/trace.h>

#define OS_INTEGER_TRACE_UART0_BAUD_RATE	(115200)

#if defined (SIFIVE_E31ARTY)
#define UART_TXCTRL_TXEN SIFIVE_E31ARTY_UART_TXCTRL_TXEN
#define UART_TXDATA_FULL SIFIVE_E31ARTY_UART_TXDATA_FULL
#elif defined (SIFIVE_E51ARTY)
#define UART_TXCTRL_TXEN SIFIVE_E51ARTY_UART_TXCTRL_TXEN
#define UART_TXDATA_FULL SIFIVE_E51ARTY_UART_TXDATA_FULL
#else
#error "Unsupported device"
#endif

// ----------------------------------------------------------------------------

namespace os
{
  namespace trace
  {
    // ------------------------------------------------------------------------

    void
    initialize (void)
    {
      // Set baud rate.
      // Arty boards have the peripheral clock at half the core clock.
      UART0->div = (riscv::core::running_frequency_hz () / 2
          / OS_INTEGER_TRACE_UART0_BAUD_RATE) - 1;
      // Enable transmitter.
      UART0->txctrl |= UART_TXCTRL_TXEN;

      // Wait a bit to avoid corruption on the UART.
      // (In some cases, switching to the IOF can lead
      // to output glitches, so need to let the UART
      // receiver time out and resynchronize to the real
      // start of the stream.
      volatile int i = 0;
      while (i < 10000)
        {
          i++;
        }
    }

    // ------------------------------------------------------------------------

    ssize_t
    write (const void* buf, std::size_t nbyte)
    {
      if (buf == nullptr || nbyte == 0)
        {
          return 0;
        }

      const char* cbuf = (const char*) buf;

      for (size_t i = 0; i < nbyte; i++)
        {
          uint8_t ch = (*cbuf++);

          if (ch == '\n')
            {
              // Wait until FIFO is ready...
              // Without handshake, should not block.
              while ((UART0->txdata & UART_TXDATA_FULL) != 0)
                ;
              UART0->txdata = '\r';
            }

          // Wait until FIFO is ready...
          while ((UART0->txdata & UART_TXDATA_FULL) != 0)
            ;
          UART0->txdata = ch;
        }

      // All characters successfully sent.
      return (ssize_t) nbyte;
    }

    // ------------------------------------------------------------------------

    void
    flush (void)
    {
      ; // TODO flush port
    }

  // --------------------------------------------------------------------------
  } /* namespace trace */
} /* namespace os */

#endif /* defined(OS_USE_TRACE_UART0) */
#endif /* defined(TRACE) */

// ----------------------------------------------------------------------------

