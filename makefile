compile: networkstructure.o client.o server.o
	@gcc -o server server.o networkstructure.o
	@gcc -o client client.o networkstructure.o
networkstructure.o: networkstructure.c networkstructure.h
	@gcc -c networkstructure.c
client.o: client.c networkstructure.h
	@gcc -c client.c
server.o: server.c networkstructure.h shared.h
	@gcc -c server.c
clean:
	@rm *.o client server
