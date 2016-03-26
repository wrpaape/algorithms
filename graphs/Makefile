CC	= gcc
CFLAGS	= -g -I$(MAINDIR) -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

graphs: graphs.o
		$(CC) $(CFLAGS) -o $@ $^

graphs.o: graphs.c graphs.h
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) graphs *.o *~
