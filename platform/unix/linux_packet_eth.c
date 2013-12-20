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
#include "util/tp_misc.h"
#include "mem/tmalloc.h"
#include "platform/unix/linux_packet_eth.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>

typedef struct {
    etherif_t ethif;
    int packet_socket;
} linux_packet_eth_t;

#define ETHIF_TO_PACKET_ETH(x) container_of(x, linux_packet_eth_t, ethif)

int packet_eth_link_status(etherif_t *e)
{
    return 1;
}

int packet_eth_packet_size(etherif_t *e)
{
    return 0;
}

int packet_eth_packet_recv(etherif_t *e, u8 *buf, int size)
{
    return 0;
}

void packet_eth_packet_xmit(etherif_t *e, u8 *buf, int size)
{
}

static const etherif_ops_t linux_packet_eth_ops = {
    .link_status = packet_eth_link_status,
    .packet_size = packet_eth_packet_size,
    .packet_recv = packet_eth_packet_recv,
    .packet_xmit = packet_eth_packet_xmit,
};

void linux_packet_eth_free(etherif_t *ethif)
{
    linux_packet_eth_t *lpe = ETHIF_TO_PACKET_ETH(ethif);

    close(lpe->packet_socket);
    tfree(lpe);
}

etherif_t *linux_packet_eth_new(void)
{
    linux_packet_eth_t *lpe = tmalloc_type(linux_packet_eth_t);

    lpe->packet_socket = socket(AF_PACKET, SOCK_RAW, ETH_P_ALL);
    etherif_init(&lpe->ethif, &linux_packet_eth_ops);
    return &lpe->ethif;
}