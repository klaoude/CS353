COMP = gcc
#OPTIONS = -lm
OPTIONS_CC = -g -Wall

main: store.o
	$(COMP) -o main main.o store.o $(OPTIONS)

main.o: main.c
	$(COMP) -o main.o -c main.c $(OPTIONS_CC)

store.o: store.c
	$(COMP) -o store.o -c store.c $(OPTIONS_CC)

main-test.o: test.c 
	$(COMP) -o $@  -c $< $(OPTIONS_CC)

main-test:	main-test.o store.o
	$(COMP) -o $@ $+ $(OPTIONS)
	
test: 	main-test
	./main-test 

archive: 
	tar cvzf CS353-TP3.tar.gz store.c store.h main.c Makefile CS353-TP3-4.pdf

clean :
	rm -f *.o 
	rm -f main-test main 
	

