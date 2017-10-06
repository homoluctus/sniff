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
  int count = 5;    /* the number to capture packets */
  u_int type;    /* type field of ethernet header */
  u_int protocol;    /* protocol field of ipv4 header */

  init();

  while (count-- > 0) {
    receive_packet();

    type = layer2();

    protocol = layer3(type);

    if (protocol > 0) {
      layer4(protocol);
    }
    putchar('\n');
  }

  return 0;
}
