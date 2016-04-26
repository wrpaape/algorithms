CC	= gcc
LIB_NAMES = rand bheap
LIBS	= $(addprefix $(LIBRARY_PATH)/, $(addprefix lib, $(addsuffix .a, $(LIB_NAMES))))
CFLAGS	= -g -I. -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

exercises: exercises.o
	$(CC) $(LIBS) $(CFLAGS) -o $@ $^

exercises.o: exercises.c exercises.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) exercises *.o *~


