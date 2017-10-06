#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "capture.h"

int packet;
/* to store a received packet */
char buf[2000];

int init(void)
{
  packet = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if ((packet) == -1) {
    puts("Socket error !!");
    exit(1);
  }
  return 0;
}

int receive_packet(void)
{
  struct sockaddr src_addr;
  socklen_t size = sizeof(src_addr);

  if (recvfrom(packet, buf, sizeof(buf), 0, &src_addr, &size) == -1) {
    puts("Can not capture packet");
    exit(1);
  }
  return 0;
}
