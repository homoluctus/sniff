# sniffer
guaranteed OS is only Ubuntu 16.04.3 LTS (maybe, it works normally on Linux)

# Description
This is CUI application

### Supported protocols
- Ethernet
- IPv4
- IPv6
- ARP
- TCP
- UDP
- ICMPv4/v6
- IGMP

By defalut, this sniffer captures 5 packets

If you want to continue capturing packets infinitely, you change argument of while function on main.c from default to 1

# Usage
```
$ git clone https://github.com/homoluctus/sniffer.git
$ make
$ sudo ./main
executed....
```
