CC	= gcc
CFLAGS	= -g -I. -std=gnu99 -Wall -D__USE_FIXED_PROTOTYPES__

all: binary_tree

binary_tree: binary_tree.o
	$(CC) $(CFLAGS) $^ -o $@

binary_tree.o: binary_tree.c binary_tree.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) binary_tree *.o
