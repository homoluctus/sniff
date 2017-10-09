#ifndef __LAYER4_H
#define __LAYER4_H

#include "layer3.h"

void layer4(u_int);
void disp_icmp(void);
char *icmp_type(u_int8_t type);
void disp_igmp(void);
void disp_tcp(void);
void disp_udp(void);

#endif
