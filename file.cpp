#include <alloca.h>
#include <math.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>

packet_cache
*packet_cache_new (int num_packets, int pkt_size, int mtu)
{
    int fragment_payload_size = mtu - sizeof (jacknet_packet_header);
    int i, fragment_number;

    if( pkt_size == sizeof(jacknet_packet_header) )
        fragment_number = 1;
    else
        fragment_number = (pkt_size - sizeof (jacknet_packet_header) - 1) / fragment_payload_size + 1;

    packet_cache *pcache = malloc (sizeof (packet_cache));
    if (pcache == NULL) {
        jack_error ("could not allocate packet cache (1)");
        return NULL;
    }

    pcache->size = num_packets;
    pcache->packets = malloc (sizeof (cache_packet) * num_packets);
    pcache->master_address_valid = 0;
    pcache->last_framecnt_retreived = 0;
    pcache->last_framecnt_retreived_valid = 0;

    if (pcache->packets == NULL) {
        jack_error ("could not allocate packet cache (2)");
        return NULL;
    }

    for (i = 0; i < num_packets; i++) {
        pcache->packets[i].valid = 0;
        pcache->packets[i].num_fragments = fragment_number;
        pcache->packets[i].packet_size = pkt_size;
        pcache->packets[i].mtu = mtu;
        pcache->packets[i].framecnt = 0;
        pcache->packets[i].fragment_array = malloc (sizeof (char) * fragment_number);
        pcache->packets[i].packet_buf = malloc (pkt_size);
        if ((pcache->packets[i].fragment_array == NULL) || (pcache->packets[i].packet_buf == NULL)) {
            jack_error ("could not allocate packet cache (3)");
            return NULL;
        }
    }
    pcache->mtu = mtu;

    return pcache;
}
