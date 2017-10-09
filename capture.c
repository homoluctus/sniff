#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "capture.h"

int sock;
/* to store a received packet */
char buf[2000];

int init(void)
{
  if ((sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
    puts("Socket error !!");
    exit(1);
  }
  return 0;
}

int receive_packet(void)
{
  struct sockaddr src_addr;
  socklen_t size = sizeof(src_addr);

  if (recvfrom(sock, buf, sizeof(buf), 0, &src_addr, &size) < 0) {
    puts("Can not capture packet");
    exit(1);
  }
  return 0;
}
