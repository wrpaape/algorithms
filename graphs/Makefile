CC	= gcc
CFLAGS	= -g -I$(MAINDIR) -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

graphs: graphs.o builder.o
		$(CC) $(CFLAGS) -o $@ $^

graphs.o: graphs.c graphs.h builder.h
		$(CC) $(CFLAGS) -c -o $@ $<

builder.o: builder.c builder.h graphs.h
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) graphs *.o *~
