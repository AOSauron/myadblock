main : MyAdBlock.o sockets.o messages.o util.o
	gcc MyAdBlock.o sockets.o messages.o util.o -o MyAdBlock -g
	
MyAdBlock.o : MyAdBlock.c sockets.h messages.h util.h
	gcc -c -Wall MyAdBlock.c -g

sockets.o : sockets.c sockets.h util.h
	gcc -c -Wall sockets.c -g

messages.o : messages.c sockets.h messages.h util.h
	gcc -c -Wall messages.c -g

util.o : util.c util.h
	gcc -c -Wall util.c -g
clean :
	rm*.o
