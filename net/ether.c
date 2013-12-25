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
#include "util/tp_misc.h"
#include "net/packet.h"
#include "net/ether.h"
#include "net/net_debug.h"
#include "mem/tmalloc.h"

static void ethernet_packet_received(event_t *e, u32 resource_id)
{
    etherif_t *ethif;
    eth_hdr_t *eth_hdr;
    int len;

    ethif = etherif_get_by_id(RES_MAJ(resource_id));

    tp_debug(("Packet received\n"));

    packet_reset(&g_packet, PACKET_RESET_HEAD);
    len = etherif_packet_recv(ethif, g_packet.ptr, g_packet.length);
    if (len < 0)
    {
	tp_err(("Error receiving packet %d\n", len));
	return;
    }

    g_packet.length = len;
    eth_hdr = (eth_hdr_t *)g_packet.ptr;
    eth_hdr_dump(eth_hdr);
}

static event_t ethernet_packet_received_event = {
    .trigger = ethernet_packet_received,
};

void ethernet_detach_etherif(etherif_t *ethif)
{
    etherif_on_packet_received_event_clear(ethif);
}

void ethernet_attach_etherif(etherif_t *ethif)
{
    etherif_on_packet_received_event_set(ethif,
	&ethernet_packet_received_event);
}