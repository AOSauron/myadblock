CC = -c -Wall -Wextra
SRC = src/

main : myAdBlock.o sockets.o messages.o util.o
	gcc myAdBlock.o sockets.o messages.o util.o -o myAdBlock -g
	rm *.o

myAdBlock.o : $(SRC)myAdBlock.c $(SRC)sockets.h $(SRC)messages.h $(SRC)util.h
	gcc $(CC) $(SRC)myAdBlock.c -g

sockets.o : $(SRC)sockets.c $(SRC)sockets.h $(SRC)util.h
	gcc $(CC) $(SRC)sockets.c -g

messages.o : $(SRC)messages.c $(SRC)sockets.h $(SRC)messages.h $(SRC)util.h
	gcc $(CC) $(SRC)messages.c -g

util.o : $(SRC)util.c $(SRC)util.h
	gcc $(CC) $(SRC)util.c -g

clean :
	rm *.o
	rm myAdBlock
