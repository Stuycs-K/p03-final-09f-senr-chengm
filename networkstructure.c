#include "networkstructure.h"

/*Create and bind a socket.
* Place the socket in a listening state.
* returns the socket descriptor
*/
int server_setup(char* add) {
  //setup structs for getaddrinfo
  //use getaddrinfo
  struct addrinfo * hints, * results;//results is allocated in getaddrinfo
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  if (add == NULL) getaddrinfo("127.0.0.1", "6767", hints, &results);
  else getaddrinfo(add, "6767", hints, &results);  //Server sets node to NULL
  //create the socket
  int clientd;//store the socket descriptor here
  clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  err(clientd, "client error");
  //this code should get around the address in use error
  int yes = 1;
  int sockOpt =  setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt,"sockopt  error");

  //bind the socket to address and port
  bind(clientd, results->ai_addr, results->ai_addrlen);
  printf("bind complete\n");
  //set socket to listen state
  listen(clientd, 10);
  printf("server listening for connections.\n");
  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);

  return clientd;
}

/*Accept a connection from a client
 *return the socket descriptor for the new socket connected to the client
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket){
    int client_socket;
    //accept() the client connection
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
    return client_socket;
}


/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int client_tcp_handshake(const char * server_address) {

  //getaddrinfo
  struct addrinfo * hints, * results;//results is allocated in getaddrinfo
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  getaddrinfo(server_address, "6767", hints, &results);  //Server sets node to NULL
  int serverd;//store the socket descriptor here
  serverd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  //connect() to the server
  connect(serverd, results->ai_addr, results->ai_addrlen);
  free(hints);
  freeaddrinfo(results);

  return serverd;
}




void err(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}
