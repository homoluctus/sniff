#ifndef __LAYER3_H
#define __LAYER3_H

#include <netinet/ip.h>
#include "layer2.h"

int layer3(u_int);
int disp_ipv4(void);
void disp_ipv6(void);
void disp_arp(void);

#endif
