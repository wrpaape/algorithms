CC	= gcc
CFLAGS	= -g -I. -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

parenths: parenths.o
		$(CC) $(CFLAGS) -o $@ $^

parenths.o: parenths.c parenths.h token.h
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.o *~

