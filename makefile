CC=gcc
TARGET=main
SRCS=main.c layer2.c layer3.c layer4.c capture.c
OBJS=$(SRCS:.c=.o)
CFLAGS=-Wall
RM=rm -f

$(TARGET): $(SRCS)
	$(CC) -c $(SRCS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	$(RM) $(TARGET) $(OBJS)
