tester : tester.o sorts.o
				gcc -o $@ $^

tester.o : tester.c tester.h sorts.h
				gcc -c tester.c

sorts.o : sorts.c sorts.h
				gcc -c sorts.c

clean :
				rm tester tester.o sorts.o

