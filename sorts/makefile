../sorts : sorts.o tester.o
				gcc -o $@ $^

sorts.o : sorts.c sorts.h tester.h
				gcc -c sorts.c

tester.o : tester.c tester.h
				gcc -c tester.c

clean :
				rm sorts sorts.o tester.o

