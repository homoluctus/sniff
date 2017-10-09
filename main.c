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
#include "buffer.h"

int main(void)
{
  /* the number to capture packets (default: 5 packets) */
  int count = 5;
  /* type field of ethernet header */
  u_int type;
  /* protocol field of ipv4 header */
  u_int protocol;
  u_int len;

  /* create socket */
  init();

  while (count-- > 0) {
    receive_packet();

    puts("============================= HEADER ==============================");
    /* for layer 2 protocol */
    type = layer2();

    /* for layer 3 protocol */
    protocol = layer3(type);

    if (protocol == -1) {
      ether_hex();
      putchar('\n');
      continue;
    }

    /* for layer 4 protocol */
    layer4(protocol);

    ether_hex();
    ip_hex();

    putchar('\n');
  }

  return 0;
}
