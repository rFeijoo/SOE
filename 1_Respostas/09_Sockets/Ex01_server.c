#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>

int print_client_message(int client_socket)
{
	int length, end_server_ok;
	char *msg;

	read(client_socket, &length, sizeof(int));

	msg = (char*) malloc(length);

	read(client_socket, msg, length);

	fprintf(stderr, "%s\n", msg);

	end_server_ok = !strcmp(msg, "10");

	free(msg);

	return (end_server_ok);
}

int main (int argc, char **argv)
{
  struct sockaddr name;
	char *socket_name;
	int  socket_id;

  socket_name = "mySocket";
  socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);

	name.sa_family = AF_LOCAL;
	strcpy(name.sa_data, socket_name);

	bind(socket_id, &name, sizeof(name));

	listen(socket_id, 10);

	while (1)
	{
		struct sockaddr client;
		int socket_id_client, end_server_ok;
		socklen_t client_len;

		socket_id_client = accept(socket_id, &client, &client_len);

		end_server_ok = print_client_message(socket_id_client);

		close(socket_id_client);

		if (end_server_ok)
    {
      unlink(socket_name);

	    close(socket_id);

			break;
    }
	}

	return 0;
}
