CC = -c -Wall -Wextra
SRC = src/

main : MyAdBlock.o sockets.o messages.o util.o
	gcc MyAdBlock.o sockets.o messages.o util.o -o MyAdBlock -g
	rm *.o

MyAdBlock.o : $(SRC)MyAdBlock.c $(SRC)sockets.h $(SRC)messages.h $(SRC)util.h
	gcc $(CC) $(SRC)MyAdBlock.c -g

sockets.o : $(SRC)sockets.c $(SRC)sockets.h $(SRC)util.h
	gcc $(CC) $(SRC)sockets.c -g

messages.o : $(SRC)messages.c $(SRC)sockets.h $(SRC)messages.h $(SRC)util.h
	gcc $(CC) $(SRC)messages.c -g

util.o : $(SRC)util.c $(SRC)util.h
	gcc $(CC) $(SRC)util.c -g

clean :
	rm *.o
	rm MyAdBlock
