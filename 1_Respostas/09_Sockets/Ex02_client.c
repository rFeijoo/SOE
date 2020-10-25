#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

char msg1[] = "Pai, qual é a verdadeira essência da sabedoria?";
char msg3[] = "Mas até uma criança de três anos sabe disso!";

int main(int argc, char **argv)
{
  struct sockaddr server;
	int    socket_id;
	char   msg2[1000], msg4[1000];

	socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);

  server.sa_family = AF_LOCAL;
	strcpy(server.sa_data, "mySocket");

  connect(socket_id, &server, sizeof(server));

  // Send message 1
  fprintf(stderr,"CLIENTE: %s\n", msg1);
	if (send(socket_id, msg1, strlen(msg1), 0) < 0)
    return 1;

  sleep(1);

  // Receive message 2
	if (recv(socket_id, msg2, 1000, 0) < 0)
		puts("ERROR - can't receive message.");

  printf("SERVER: %s\n", msg2);

  // Send message 3
  fprintf(stderr,"CLIENTE: %s\n", msg3);
	if (send(socket_id, msg3, strlen(msg3), 0) < 0)
    return 1;

  sleep(1);

  // Receive message 4
	if (recv(socket_id, msg4, 1000, 0) < 0)
		puts("ERROR - can't receive message.");

  printf("SERVER: %s\n", msg4);

	close(socket_id);

	return 0;
}
