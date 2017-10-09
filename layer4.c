/* handle layer4 header (tcp, udp, icmp) */

#include <stdio.h>
#include <netinet/ip_icmp.h>
#include <netinet/igmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include "layer3.h"
#include "layer4.h"

/* storing a received packet */
extern char buf[2000];

void layer4(u_int protocol)
{
  printf("L4 | ");
  switch (protocol) {
    case 1:
      disp_icmp();
      break;

    case 2:
      disp_igmp();
      break;

    case 6:
      disp_tcp();
      break;

    case 17:
      disp_udp();
      break;

    default:
      break;
  }
  putchar('\n');
}

void disp_icmp(void)
{
  struct icmphdr *icmp_h;

  icmp_h = (struct icmphdr *)(buf + sizeof(struct ether_header) + sizeof(struct iphdr));

  printf("ICMP Message type = %d  Code = %d", icmp_h->type, icmp_h->code);
}

void disp_igmp(void)
{
  struct igmp *igmp_h;

  igmp_h = (struct igmp *)(buf + sizeof(struct ether_header) + sizeof(struct iphdr));

  printf("IGMP  %s", inet_ntoa(igmp_h->igmp_group));
}

void disp_tcp(void)
{
  struct tcphdr *tcp_h;

  tcp_h = (struct tcphdr *)(buf + sizeof(struct ether_header) + sizeof(struct iphdr));

  printf("TCP  %17d > %-17d",
          ntohs(tcp_h->source), ntohs(tcp_h->dest));
  printf("  Seq = %u  Ack = %u  SYN = %d  ACK = %d  FIN = %d", ntohl(tcp_h->seq),
                                                              ntohl(tcp_h->ack_seq),
                                                              tcp_h->syn,
                                                              tcp_h->ack,
                                                              tcp_h->fin);
}

void disp_udp(void)
{
  struct udphdr *udp_h;

  udp_h = (struct udphdr *)(buf + sizeof(struct ether_header) + sizeof(struct iphdr));

  printf("UDP  %17d > %-17d", ntohs(udp_h->source), ntohs(udp_h->dest));
}
