CC	= gcc
LIBS	= $(LIBRARY_PATH)/librand.a
CFLAGS	= -g -I. -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

exercises: exercises.o
	$(CC) $(LIBS) $(CFLAGS) -o $@ $^

exercises.o: exercises.c exercises.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) exercises *.o *~


