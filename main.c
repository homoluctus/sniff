/*
 * This is sniffer
 * Display ethernet, ip, tcp and udp header
 */

#include <stdio.h>
#include <sys/types.h>
#include "init.h"
#include "layer2.h"
#include "layer3.h"
#include "layer4.h"

int main(void)
{
  /* the number to capture packets (default: 5 packets) */
  int count = 5;
  /* type field of ethernet header */
  int type;
  /* protocol field of ipv4 header */
  int protocol;

  /* create socket */
  init();

  while (count-- > 0) {
    receive_packet();

    puts("============================= HEADER ==============================");
    /*
     * for layer 2 protocol
     * type that is less than 0 is not supported
     */
    if ((type = layer2()) < 0) continue;

    /* for layer 3 protocol */
    protocol = layer3((u_int)type);

    /* protocol that is less than 0 is not supported */
    if (protocol < 0) continue;

    /* for layer 4 protocol */
    layer4((u_int16_t)type, (u_int8_t)protocol);
    putchar('\n');
  }
  return 0;
}
