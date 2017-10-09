/*
 * This is sniffer
 * Display ethernet, ip, tcp and udp header
 */

#include <stdio.h>
#include "init.h"
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

    /* for layer 2 protocol */
    type = layer2();

    /* for layer 3 protocol */
    protocol = layer3(type);

    if (protocol == -1) {
      putchar('\n');
      continue;
    }

    /* for layer 4 protocol */
    layer4(protocol);

    putchar('\n');
  }

  return 0;
}
