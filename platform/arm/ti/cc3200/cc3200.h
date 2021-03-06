/* Copyright (c) 2013, Eyal Birger
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * The name of the author may not be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __CC3200_CONSTS_H__
#define __CC3200_CONSTS_H__

#define GPIO(port, pin) (((port) << 3) + (pin))
#define GPIO_BIT(p) (1 << ((p) & 0x7))
#define GPIO_PORT(p) ((p) >> 3)
#define GPIO_NUM_PORT_PINS 8

typedef char gpio_port_t;

#define UART0 0
#define UART1 1
#define NUM_UARTS 2

#define PA0 0x00 
#define PA1 0x01 
#define PA2 0x02 
#define PA3 0x03 
#define PA4 0x04 
#define PA5 0x05 
#define PA6 0x06 
#define PA7 0x07
#define PB0 0x08
#define PB1 0x09
#define PB2 0x0a
#define PB3 0x0b
#define PB4 0x0c
#define PB5 0x0d
#define PB6 0x0e
#define PB7 0x0f
#define PC0 0x10
#define PC1 0x11
#define PC2 0x12
#define PC3 0x13
#define PC4 0x14
#define PC5 0x15
#define PC6 0x16
#define PC7 0x17
#define PD0 0x18
#define PD1 0x19
#define PD2 0x1a
#define PD3 0x1b
#define PD4 0x1c
#define PD5 0x1d
#define PD6 0x1e
#define PD7 0x1f

#define GPIO_PORT_A 0
#define GPIO_PORT_B 1
#define GPIO_PORT_C 2
#define GPIO_PORT_D 3
#define NUM_GPIO_PORTS 4

#endif
