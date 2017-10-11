/* handle layer3 header (ipv4, ipv6, arp) */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include "layer3.h"

/* storing a received packet */
extern char buf[2000];
/* for inet_ntop() */
char addr[30];

int layer3(u_int type)
{
  switch (type) {
    case ETHERTYPE_IP:
      return disp_ipv4();

    case ETHERTYPE_IPV6:
      return disp_ipv6();

    default:
      putchar('\n');
      break;
  }
  /* return -1 to avoid duplication with protocol number */
  return -1;
}

u_int8_t disp_ipv4(void)
{
  u_int8_t protocol;
  struct iphdr *ip4_h;

  ip4_h = (struct iphdr *)(buf + sizeof(struct ether_header));

  if (ip4_h->version != 4) {
    puts("IPv4 version error");
    exit(1);
  }

  printf("[IPv4] %s > ", inet_ntop(AF_INET,
                                  (const void *)&(ip4_h->saddr),
                                  addr,
                                  sizeof(addr)));

  printf("%s", inet_ntop(AF_INET,
                            (const void *)&(ip4_h->daddr),
                            addr,
                            sizeof(addr)));

  protocol = ip4_h->protocol;

  printf(" Upper-layer-protocol = %d", protocol);
  putchar('\n');

  return protocol;
}

u_int8_t disp_ipv6(void)
{
  u_int8_t next_h;
  struct ip6_hdr *ip6_h;

  ip6_h = (struct ip6_hdr *)(buf + sizeof(struct ether_header));

  printf("[IPv6] %s > ", inet_ntop(AF_INET6,
                                (const void *)ip6_h->ip6_src.s6_addr,
                                addr,
                                sizeof(addr)));

  printf("%s", inet_ntop(AF_INET6,
                        (const void *)ip6_h->ip6_dst.s6_addr,
                        addr,
                        sizeof(addr)));

  next_h = ip6_h->ip6_ctlun.ip6_un1.ip6_un1_nxt;

  printf("  Next-header = %d", next_h);
  putchar('\n');

  return next_h;
}
