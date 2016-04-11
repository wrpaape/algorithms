CC	= gcc
CFLAGS	= -g -I. -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

bin/analyze: obj/analyze.o obj/tree_compare.o obj/rand.o obj/pcg_basic.o
		$(CC) $(CFLAGS) -o $@ $^

obj/analyze.o: analyze.c analyze.h tree_compare.h utils/utils.h utils/rand.h
		$(CC) $(CFLAGS) -c -o $@ $<

obj/tree_compare.o: tree_compare.c tree_compare.h utils/utils.h utils/rand.h
		$(CC) $(CFLAGS) -c -o $@ $<

obj/rand.o: utils/rand.c utils/rand.h utils/utils.h utils/rand.h
		$(CC) $(CFLAGS) -c -o $@ $<

obj/pcg_basic.o: utils/pcg_basic.c utils/pcg_basic.h
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) bin/* obj/* **/*~
