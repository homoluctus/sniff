/* handle layer3 header (ipv4, ipv6, arp) */

#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip6.h>
#include <net/if_arp.h>
#include "layer2.h"
#include "layer3.h"

/* storing a received packet */
extern char buf[2000];
/* for inet_ntop() */
char addr[30];

int layer3(u_int type)
{
  u_int p;    /* protocol field of ipv4 header */

  printf("L3 | ");
  switch (type) {
    case ETHERTYPE_IP:
      p = disp_ipv4();
      putchar('\n');
      return p;

    case ETHERTYPE_IPV6:
      disp_ipv6();
      break;

    case ETHERTYPE_ARP:
      disp_arp();
      break;

    default:
      break;
  }
  putchar('\n');

  return -1;
}

int disp_ipv4(void)
{
  struct iphdr *ip4_h;

  ip4_h = (struct iphdr *)(buf + sizeof(struct ether_header));

  if (ip4_h->version != 4) {
    puts("IPv4 version error");
    exit(1);
  }

  printf("IPv4 %17s > ", inet_ntop(AF_INET,
                                  (const void *)&(ip4_h->saddr),
                                  addr,
                                  sizeof(addr)));

  printf("%-17s", inet_ntop(AF_INET,
                            (const void *)&(ip4_h->daddr),
                            addr,
                            sizeof(addr)));

  printf("  Upper layer protocol = %d", ip4_h->protocol);

  return ip4_h->protocol;
}

void disp_ipv6(void)
{
  struct ip6_hdr *ip6_h;

  ip6_h = (struct ip6_hdr *)(buf + sizeof(struct ether_header));

  printf("IPv6 %s > ", inet_ntop(AF_INET6,
                                (const void *)ip6_h->ip6_src.s6_addr,
                                addr,
                                sizeof(addr)));

  printf("%s", inet_ntop(AF_INET6,
                        (const void *)ip6_h->ip6_dst.s6_addr,
                        addr,
                        sizeof(addr)));
}

void disp_arp(void)
{
  struct arphdr *arp_h;

  arp_h = (struct arphdr *)(buf + sizeof(struct ether_header));

  int op = ntohs(arp_h->ar_op);

  printf("ARP  ");
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
