/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2010 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
*                                                                             *
******************************************************************************/

#include "alt_types.h"
#include "altera_avalon_jtag_uart_regs.h"
#include "altera_avalon_jtag_uart_lwhal.h"


/********************************************************************/

/** @Function Description:  Writes a single character to the JTAG UART.
  * @API Type:              External
  * @param base             JTAG UART base address
  * @param character        Character to be written
  * @return                 None
  *                         
  */
void altera_avalon_jtag_uart_lwhal_putchar(void *base, int character)
{
    do {
        if ((IORD_ALTERA_AVALON_JTAG_UART_CONTROL(base) & ALTERA_AVALON_JTAG_UART_CONTROL_WSPACE_MSK) != 0)
        {
            IOWR_ALTERA_AVALON_JTAG_UART_DATA(base, (character & 0xff));
            return;
        }
    }while(1);
    
    return;
}  
