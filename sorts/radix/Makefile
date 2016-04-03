CC = gcc
CFLAGS = -g -I. -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

radix: radix.o
	$(CC) $(CFLAGS) -o $@ $^

radix.o: radix.c radix.h
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	$(RM) radix *.o *~

