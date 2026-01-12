compile: networkstructure.o client.o #server.o
#	@gcc -o server server.o networkstructure.o
	@gcc $(shell pkg-config --cflags gtk4) -o client client.o $(shell pkg-config --libs gtk4)
#	@gcc -o client client.o networkstructure.o
networkstructure.o: networkstructure.c networkstructure.h
	@gcc -c networkstructure.c
client.o: client.c networkstructure.h
	@gcc $(shell pkg-config --cflags gtk4) -c client.c $(shell pkg-config --libs gtk4)
server.o: server.c networkstructure.h shared.h
	@gcc -c server.c
clean:
	@rm *.o client server

 
