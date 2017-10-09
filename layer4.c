/* handle layer4 header (tcp, udp, icmp) */

#include <stdio.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/igmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include "layer4.h"

/* storing a received packet */
extern char buf[2000];

void layer4(u_int protocol)
{
  printf("L4 | ");
  switch (protocol) {
    case 1:
      disp_icmp4();
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

void disp_icmp4(void)
{
  struct icmphdr *icmp_h;

  icmp_h = (struct icmphdr *)(buf + sizeof(struct ether_header) + sizeof(struct iphdr));

  u_int8_t type = icmp_h->type;
  printf("ICMP Message type = %d (%s)  Code = %d", type, icmp4_type(type), icmp_h->code);
}

char *icmp4_type(u_int8_t type)
{
  char *str;

  switch (type) {
    case 0:
      str = "ECHO REPLY";
      break;

    case 3:
      str = "DESTINATION UNREACHABLE";
      break;

    case 4:
      str = "SOURCE QUENCH";
      break;

    case 5:
      str = "REDIRECT";
      break;

    case 8:
      str = "ECHO REQUEST";
      break;

    case 11:
      str = "TIME EXCEEDED";
      break;

    default:
      str = "UNKNOWN";
      break;
  }
  return str;
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
