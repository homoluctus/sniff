/* handle layer4 (over IPv4) header (tcp, udp, icmp) */

#include <stdio.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
#include <netinet/igmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include "layer4.h"

/* storing a received packet */
extern char buf[2000];

void layer4(u_int type, u_int8_t protocol)
{
  int size = sizeof(struct ether_header);

  switch (type) {
    case ETHERTYPE_IP:
      size += sizeof(struct iphdr);
      break;

    case ETHERTYPE_IPV6:
      size += sizeof(struct ip6_hdr);
      break;
  }

  switch (protocol) {
    case 1:
      disp_icmp4(size);
      break;

    case 2:
      disp_igmp(size);
      break;

    case 6:
      disp_tcp(size);
      break;

    case 17:
      disp_udp(size);
      break;

    case 58:
      disp_icmp6(size);

    default:
      break;
  }
  putchar('\n');
}

void disp_icmp4(int size)
{
  struct icmphdr *icmp_h;

  icmp_h = (struct icmphdr *)(buf + size);

  u_int8_t type = icmp_h->type;
  printf("[ICMPv4] %s (TYPE = %d)", icmp4_type(type), type);
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

void disp_igmp(int size)
{
  struct igmp *igmp_h;

  igmp_h = (struct igmp *)(buf + size);

  printf("[IGMP] %s", inet_ntoa(igmp_h->igmp_group));
}

void disp_tcp(int size)
{
  struct tcphdr *tcp_h;

  tcp_h = (struct tcphdr *)(buf + size);

  printf("[TCP] %d > %d",
          ntohs(tcp_h->source), ntohs(tcp_h->dest));
  printf("  Seq = %u  Ack = %u  SYN = %d  ACK = %d  FIN = %d", ntohl(tcp_h->seq),
                                                              ntohl(tcp_h->ack_seq),
                                                              tcp_h->syn,
                                                              tcp_h->ack,
                                                              tcp_h->fin);
}

void disp_udp(int size)
{
  struct udphdr *udp_h;

  udp_h = (struct udphdr *)(buf + size);

  printf("[UDP] %d > %d", ntohs(udp_h->source), ntohs(udp_h->dest));
}

void disp_icmp6(int size)
{
  struct icmp6_hdr *icmp6_h;

  icmp6_h = (struct icmp6_hdr *)(buf + size);

  printf("[ICMPv6] %s (TYPE = %d)", (char *)type(icmp6_h->icmp6_type), icmp6_h->icmp6_type);
}

char *type(u_int8_t type)
{
  char *str;

  switch (type) {
    case 1:
      str = "DESTINATION UNREACHABLE";
      break;

    case 2:
      str = "PACKET TOO BIG";
      break;

    case 3:
      str = "TIME EXCEEDED";
      break;

    case 4:
      str = "PARAMETER PROBLEM";
      break;

    case 128:
      str = "ECHO REQUEST";
      break;

    case 129:
      str = "ECHO REPLY";
      break;

    case 133:
      str = "ROUTER SOLICIT";
      break;

    case 134:
      str = "ROUTER ADVERTISEMENT";
      break;

    case 135:
      str = "NEIGHBOR SOLICIT";
      break;

    case 136:
      str = "NEIGHBOR ADVERTISEMENT";
      break;

    case 137:
      str = "REDIRECT";
      break;

    default:
      str = "UNKNOWN";
      break;
  }
  return str;
}
