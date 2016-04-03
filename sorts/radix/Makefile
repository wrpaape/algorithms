CC = gcc
CFLAGS = -g -I. -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

radix: radix.c radix.h
	$(gcc) $(CFLAGS) -o $@ $^
clean:
	$(RM) radix *.o *~

