/* display packet information in hexadecimal notation */

#include <stdio.h>
#include <sys/types.h>
#include <net/ethernet.h>
#include <netinet/ip.h>

extern char buf[2000];

void ether_hex(void)
{
  int i;

  puts("=============================== HEX ===============================");
  printf("L2 | ");
  for (i = 0; i < ETH_HLEN; i++) {
    printf("%02x%c", (u_int8_t)buf[i], i == ETH_HLEN - 1 ? '\n' : ' ');
  }
}

void ip_hex(void)
{
  int i;
  u_int8_t *p = buf + ETH_HLEN;
  int len = p[0] & 0x0f;    /* header length */

  printf("L3 | ");
  for (i = 0; i < len*4; i++) {
    printf("%02x%c", p[i], i == len*4 - 1 ? '\n' : ' ');
  }
}
