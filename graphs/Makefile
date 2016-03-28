CC	= gcc
CFLAGS	= -g -I. -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

graphs: graphs.o builder.o inspect.o bheap.o generator.o printer.o pcg_basic.o
		$(CC) $(CFLAGS) -o $@ $^

graphs.o: graphs.c graphs.h builder.h inspect.h utils.h
		$(CC) $(CFLAGS) -c -o $@ $<

builder.o: builder.c builder.h graphs.h utils.h
		$(CC) $(CFLAGS) -c -o $@ $<

inspect.o: inspect.c inspect.h graphs.h bheap.h
		$(CC) $(CFLAGS) -c -o $@ $<

bheap.o: bheap.c bheap.h utils.h
		$(CC) $(CFLAGS) -c -o $@ $<

printer.o: maps/printer.c maps/printer.h maps/generator.h utils.h
		$(CC) $(CFLAGS) -c -o $@ $<

generator.o: maps/generator.c maps/generator.h utils.h
		$(CC) $(CFLAGS) -c -o $@ $<

pcg_basic.o: pcg_basic.c pcg_basic.h
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) graphs *.o *~
