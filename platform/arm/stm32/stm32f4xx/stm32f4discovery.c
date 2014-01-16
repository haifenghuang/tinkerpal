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
#include "util/debug.h"
#include "util/tstr.h"
#include "platform/platform.h"
#include "platform/arm/cortex-m.h"
#include "platform/arm/stm32/stm32f4xx/stm32f4xx_common.h"
#include "platform/arm/stm32/stm32f4xx/stm32f4discovery.h"
#include "platform/arm/stm32/stm32_usart.h"
#include "platform/arm/stm32/stm32_gpio.h"
#include "platform/arm/stm32/stm32_spi.h"
#include "platform/arm/stm32/stm32.h"
#include "drivers/serial/serial_platform.h"

extern uint32_t SystemCoreClock;

const stm32_gpio_port_t stm32_gpio_ports[] = {
    [GPIO_PORT_A] = { RCC_AHB1Periph_GPIOA, GPIOA },
    [GPIO_PORT_B] = { RCC_AHB1Periph_GPIOB, GPIOB },
    [GPIO_PORT_C] = { RCC_AHB1Periph_GPIOC, GPIOC },
    [GPIO_PORT_D] = { RCC_AHB1Periph_GPIOD, GPIOD },
    [GPIO_PORT_E] = { RCC_AHB1Periph_GPIOE, GPIOE },
    [GPIO_PORT_F] = { RCC_AHB1Periph_GPIOF, GPIOF }
};

#ifdef CONFIG_SPI
const stm32_spi_t stm32_spis[] = {
    [SPI_PORT1] = {
	.spix = SPI1,
	.periph_enable = RCC_APB2PeriphClockCmd,
	.spi_clk = RCC_APB2Periph_SPI1,
	.clk = PA5,
	.miso = PA6,
	.mosi = PA7,
	.af = GPIO_AF_SPI1
    },
    [SPI_PORT2] = {
	.spix = SPI2,
	.periph_enable = RCC_APB1PeriphClockCmd,
	.spi_clk = RCC_APB1Periph_SPI2,
	.clk = PB10,
	.miso = PC2,
	.mosi = PC3,
	.af = GPIO_AF_SPI2 
    },
    [SPI_PORT3] = {
	.spix = SPI3,
	.periph_enable = RCC_APB1PeriphClockCmd,
	.spi_clk = RCC_APB1Periph_SPI3,
	.clk = PC10,
	.miso = PC11,
	.mosi = PC12,
	.af = GPIO_AF_SPI3
    }
};
#endif

static void timers_init(void)
{
    SysTick_Config(SystemCoreClock / 1000);
}

static unsigned long stm32f4discovery_get_system_clock(void)
{
    return SystemCoreClock;
}

static void stm32f4discovery_init(void)
{
    timers_init();
}

const platform_t platform = {
    .serial = {
	.enable = stm32_usart_enable,
	.read = buffered_serial_read,
	.write = stm32_usart_write,
	.irq_enable = stm32_usart_irq_enable,
    },
#ifdef CONFIG_GPIO
    .gpio = {
	.digital_write = stm32_gpio_digital_write,
	.set_pin_mode = stm32_gpio_set_pin_mode,
	.set_port_val = stm32_gpio_set_port_val,
    },
#endif
#ifdef CONFIG_SPI
    .spi = {
	.init = stm32_spi_init,
	.reconf = stm32_spi_reconf,
	.set_max_speed = stm32_spi_set_max_speed,
	.send = stm32_spi_send,
	.receive = stm32_spi_receive,
    },
#endif
    .init = stm32f4discovery_init,
    .meminfo = cortex_m_meminfo,
    .panic = cortex_m_panic,
    .select = stm32_select,
    .get_ticks_from_boot = cortex_m_get_ticks_from_boot,
    .get_system_clock = stm32f4discovery_get_system_clock,
    .msleep = stm32_msleep,
};
