#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>


#ifndef NETWORKSTRUCTURE_H
#define NETWORKSTRUCTURE_H
void err(int i, char*message);
int server_setup(char*add);
int client_tcp_handshake( const char*server_address);
int server_tcp_handshake(int listen_socket);
void view();
#endif
