/*
 * This is sniffer
 * Display ethernet, ip, tcp and udp header
 */

#include <stdio.h>
#include "capture.h"
#include "layer2.h"
#include "layer3.h"
#include "layer4.h"

int main(void)
{
  /* the number to capture packets (default: 5 packets) */
  int count = 5;
  /* type field of ethernet header */
  u_int type;
  /* protocol field of ipv4 header */
  u_int protocol;

  /* create socket */
  init();

  while (count-- > 0) {
    receive_packet();

    /* for layer 2 protocols */
    type = layer2();

    /* for layer 3 protocols */
    protocol = layer3(type);

    if (protocol > 0) {
      /* for layer 4 protocols */
      layer4(protocol);
    }
    putchar('\n');
  }

  return 0;
}
