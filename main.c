/*
 * This is sniffer
 * Display ethernet, ip, tcp and udp header
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include "init.h"
#include "layer2.h"
#include "layer3.h"
#include "layer4.h"

int get_option(int argc, char **argv)
{
  int option, ret;

  while ((option = getopt(argc, argv, "hn:")) != -1) {
    switch (option) {
      case 'h':    /* display help */
        fprintf(stdout, "Usage:\t./main [OPTION]\n\nOption:\n\t-n [NUMBER]:\tthe nubmer of captured packet (default is 5)\n\t-h:\t\tdisplay information\n");
        ret = 0;
        break;
      case 'n':    /* set the number of captured packet */
        ret = atoi(optarg);
        break;
      case '?':
        if (optopt == 'n') {
          fprintf(stderr, "Format: ./main -n [NUMBER]\n");
        } else if (isprint(optopt)) {
          fprintf(stderr, "[!] Error: Unkown option is %c\n", optopt);
        } else {
          fprintf(stderr, "[!] Error: Unkown option\n");
        }
        ret = -1;
        break;
      default:
        fprintf(stderr, "[!] Error: Unknown error occurred\n");
        ret = -2;
    }
  }
  return ret;
}

int main(int argc, char **argv)
{
  /* type field of ethernet header */
  int type;
  /* protocol field of ipv4 header */
  int protocol;
  /* the number to capture packets (default: 5 packets) */
  int count;

  /* option is none if argc equal 1 */
  if (argc == 1) {
    /* default the number of captured packets is 5 */
    count =  5;
  } else if ((count = get_option(argc, argv)) < 0) {
    exit(EXIT_FAILURE);
  } else if (count == 0) {
    exit(EXIT_SUCCESS);
  }

  /* create socket */
  init();

  while (count-- > 0) {
    receive_packet();

    puts("============================= HEADER ==============================");
    /*
     * for layer 2 protocol
     * type that is less than 0 is not supported
     */
    if ((type = layer2()) < 0) continue;

    /* for layer 3 protocol */
    protocol = layer3((u_int)type);

    /* protocol that is less than 0 is not supported */
    if (protocol < 0) continue;

    /* for layer 4 protocol */
    layer4((u_int16_t)type, (u_int8_t)protocol);
    putchar('\n');
  }
  return 0;
}
