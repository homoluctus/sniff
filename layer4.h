#ifndef __LAYER4_H
#define __LAYER4_H

void layer4(u_int, u_int8_t);
void disp_icmp4(int);
char *icmp4_type(u_int8_t);
void disp_igmp(int);
void disp_tcp(int);
void disp_udp(int);
void disp_icmp6(int);
char *type(u_int8_t);

#endif
