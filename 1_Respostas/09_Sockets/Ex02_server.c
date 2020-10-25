#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>

char socket_name[] = "mySocket";
int socket_id;
char msg2[] = "Não façais nada violento, praticai somente aquilo que é justo e equilibrado.";
char msg4[] = "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...";

void end_server(int signum)
{
	fprintf(stderr, "Closing socket\n");

	unlink(socket_name);

	close(socket_id);

	exit(0);
}

int main(int argc, char **argv)
{
	struct 		sockaddr server, client;
	int    		socket_id_client;
	int       read_size;
	socklen_t client_len;
	char      client_message[500];

	socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);

	server.sa_family = AF_LOCAL;
	strcpy(server.sa_data, "mySocket");

	bind(socket_id, &server, sizeof(server));

	listen(socket_id, 10);

	socket_id_client = accept(socket_id, &client, &client_len);

	while ((read_size = recv(socket_id_client, client_message, 500, 0)) > 0)
	{
		if (!strcmp(client_message, "Pai, qual é a verdadeira essência da sabedoria?"))
			write(socket_id_client, msg2, strlen(msg2));
		else
			write(socket_id_client, msg4, strlen(msg4));
	}

	if (read_size == 0)
	{
		close(socket_id_client);

		end_server(0);
	}

	return 0;
}
