/* display packet information in hexadecimal notation */

#include <stdio.h>
#include <sys/types.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <net/if_arp.h>

extern char buf[2000];

void disp_hex(int len, char *p)
{
  int i;

  for (i = 0; i < len; i++) {
    printf("%02x%c", (u_int8_t)p[i], i == len - 1 ? '\n' : ' ');
  }
}

void ether_hex(void)
{
  char *p;
  struct ether_header *ether_h = (struct ether_header *)buf;

  puts("=============================== HEX ===============================");
  disp_hex(sizeof(struct ether_header), buf);

  if (ntohs(ether_h->ether_type) == ETHERTYPE_ARP) {
    p = buf + sizeof(struct ether_header);
    disp_hex(sizeof(struct arphdr), p);
  }
}

void l3_hex(u_int type)
{
  char *p = buf + ETH_HLEN;

  switch (type) {
    case ETHERTYPE_IP:
      disp_hex(sizeof(struct iphdr), p);    /* header length */
      break;

    case ETHERTYPE_IPV6:
      disp_hex(sizeof(struct ip6_hdr), p);
      break;
  }
}
