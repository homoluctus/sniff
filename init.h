#ifndef __CAPTURE_H
#define __CAPTURE_H

#include <arpa/inet.h>
#include <net/ethernet.h>

int init(void);
int receive_packet(void);

#endif
