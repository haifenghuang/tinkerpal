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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doc/print.h"
#include "util/tp_misc.h"
#include "version_data.h"

#define PLATFORM_CHIPSET_H "doc/chips.h"

static void print_header(void)
{
    P("---");
    P("title: Chipset Guide | Tinkerpal " TINKERPAL_VERSION);
    P("markdown2extras: tables, wiki-tables, code-friendly");
    P("---");
    P("#Pin Mappings");
    P("Chipsets Pin mappings detailed below");
    P("");
}

struct chip {
    const char *name;
    struct res {
        enum res_type {
            RES_NONE = 0,
            RES_UART = 1,
            RES_I2C = 2,
            RES_SSI = 3,
            RES_SPI = 4,
            RES_LAST,
        } type;
        union {
            struct {
                const char *uart_name;
                const char *uart_rx;
                const char *uart_tx;
            };
            struct {
                const char *i2c_name;
                const char *i2c_scl;
                const char *i2c_sda;
            };
            struct {
                const char *ssi_name;
                const char *ssi_clk;
                const char *ssi_fss;
                const char *ssi_rx;
                const char *ssi_tx;
            };
            struct {
                const char *spi_name;
                const char *spi_clk;
                const char *spi_miso;
                const char *spi_mosi;
            };
        };
    } *res;
} chips[] = {
#define CHIPSET_START(chip) { .name = #chip, .res = (struct res []){
#define CHIPSET_END() {} } },
#define UART_DEF(num, rx, tx) { \
    .type = RES_UART, \
    .uart_name = "UART" #num, \
    .uart_rx = #rx, \
    .uart_tx = #tx \
},
#define USART_DEF(num, type_name, rx, tx, afsig, apb) { \
    .type = RES_UART, \
    .uart_name = #type_name #num, \
    .uart_rx = #rx, \
    .uart_tx = #tx \
},
#define I2C_DEF(num, scl, sda) { \
    .type = RES_I2C, \
    .i2c_name = "I2C" #num, \
    .i2c_scl = #scl, \
    .i2c_sda = #sda \
},
#define SSI_DEF(num, clkpin, fsspin, rxpin, txpin) { \
    .type = RES_SSI, \
    .ssi_name = "SSI" #num, \
    .ssi_clk = #clkpin, \
    .ssi_fss = #fsspin, \
    .ssi_rx = #rxpin, \
    .ssi_tx = #txpin \
},
#define SPI_DEF(num, apb, clkpin, misopin, mosipin, afsig) { \
    .type = RES_SPI, \
    .spi_name = "SPI" #num, \
    .spi_clk = #clkpin, \
    .spi_miso = #misopin, \
    .spi_mosi = #mosipin, \
},

#include "platform/chipset.h"

    {}
};

static void uart_print_headers(void)
{
    print_table_header("UART", "RX Pin", "TX Pin");
}

static void uart_print_row(struct res *r)
{
    print_table_row(r->uart_name, r->uart_rx, r->uart_tx);
}

static void i2c_print_headers(void)
{
    print_table_header("I2C", "SCL Pin", "SDA Pin");
}

static void i2c_print_row(struct res *r)
{
    print_table_row(r->i2c_name, r->i2c_scl, r->i2c_sda);
}

static void ssi_print_headers(void)
{
    print_table_header("SSI", "FSS Pin", "CLK Pin", "RX Pin", "TX Pin");
}

static void ssi_print_row(struct res *r)
{
    print_table_row(r->ssi_name, r->ssi_fss, r->ssi_clk, r->ssi_rx,
        r->ssi_tx);
}

static void spi_print_headers(void)
{
    print_table_header("SPI", "CLK Pin", "MISO Pin", "MOSI Pin");
}

static void spi_print_row(struct res *r)
{
    print_table_row(r->spi_name, r->spi_clk, r->spi_miso, r->spi_mosi);
}

static struct res_ops {
    const char *name;
    void (*print_headers)(void);
    void (*print_row)(struct res *res);
} res_ops[] = {
    [RES_UART] = {
        .name = "UART",
        .print_headers = uart_print_headers,
        .print_row = uart_print_row
    },
    [RES_I2C] = {
        .name = "I2C",
        .print_headers = i2c_print_headers,
        .print_row = i2c_print_row
    },
    [RES_SSI] = {
        .name = "SSI",
        .print_headers = ssi_print_headers,
        .print_row = ssi_print_row
    },
    [RES_SPI] = {
        .name = "SPI",
        .print_headers = spi_print_headers,
        .print_row = spi_print_row
    }
};

static void print_res_by_type(struct res *list, enum res_type type)
{
    struct res_ops *ops = &res_ops[type];
    struct res *r;

    for (r = list; r->type && r->type != type; r++);
    if (!r->type)
        return;

    print_subsection("%s", ops->name);

    ops->print_headers();
    for (r = list; r->type; r++)
    {
        if (r->type != type)
            continue;

        ops->print_row(r);
    }
}

static void print_pin_mappings(void)
{
    struct chip *c;

    for (c = chips; c->name; c++)
    {
        enum res_type t;

        print_section("%s", c->name);

        for (t = RES_NONE + 1; t != RES_LAST; t++)
            print_res_by_type(c->res, t);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    if (!(fp = fopen(argv[1], "w")))
        exit(1);

    print_header();

    print_pin_mappings();

    fclose(fp);
    return 0;
}