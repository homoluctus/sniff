/* Handle ethernet header */

#include <stdio.h>
#include <stdlib.h>
#include "capture.h"
#include "layer2.h"

/* storing a received packet */
extern char buf[2000];

int layer2(void)
{
  u_int type;
  struct ether_header *ether_h;

  ether_h = (struct ether_header *)buf;

  printf("L2 | MAC  ");
  disp_mac(ether_h->ether_shost);
  printf(" > ");
  disp_mac(ether_h->ether_dhost);

  type = ntohs(ether_h->ether_type);
  printf("  TYPE = 0x%04x ", type);
  switch (type) {
    case ETHERTYPE_IP:
      puts("(IPv4)");
      break;

    case ETHERTYPE_ARP:
      puts("(ARP)");
      break;

    case ETHERTYPE_REVARP:
      puts("(Reverse ARP)");
      break;

    case ETHERTYPE_VLAN:
      puts("(VLAN = IEEE802.1Q)");
      break;

    case ETHERTYPE_IPV6:
      puts("(IPv6)");
      break;

    default:
      putchar('\n');
      break;
  }
  return type;
}

void disp_mac(u_int8_t *mac)
{
  int i;
  for (i = 0; i < 6; i++) {
    printf("%02x%s",mac[i], (i != 5) ? ":" : "");
  }
}
