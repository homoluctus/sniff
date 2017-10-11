/* Handle ethernet header */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include "layer2.h"

/* storing a received packet */
extern char buf[2000];

int layer2(void)
{
  u_int type;
  struct ether_header *ether_h;

  ether_h = (struct ether_header *)buf;

  printf("MAC  | ");
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
      disp_arp();
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

void disp_arp(void)
{
  struct arphdr *arp_h;

  arp_h = (struct arphdr *)(buf + sizeof(struct ether_header));

  int op = ntohs(arp_h->ar_op);

  printf("ARP  | ");
  switch (op) {
    case 1:
      printf("Request  ");
      break;

    case 2:
      printf("Reply  ");
      break;

    default:
      break;
  }
  printf("(Opecode = %d)", op);
}
