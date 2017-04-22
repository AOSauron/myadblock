CC = -c -Wall -Wextra

main : MyAdBlock.o sockets.o messages.o util.o
	gcc MyAdBlock.o sockets.o messages.o util.o -o MyAdBlock -g
	rm *.o

MyAdBlock.o : MyAdBlock.c sockets.h messages.h util.h
	gcc $(CC) MyAdBlock.c -g

sockets.o : sockets.c sockets.h util.h
	gcc $(CC) sockets.c -g

messages.o : messages.c sockets.h messages.h util.h
	gcc $(CC) messages.c -g

util.o : util.c util.h
	gcc $(CC) util.c -g

clean :
	rm *.o
