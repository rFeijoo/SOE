#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

void send_message(char *msg)
{
  struct sockaddr name;
	char *socket_name;
	int  socket_id;
  int length;

	socket_name = "mySocket";
  socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);

	name.sa_family = AF_LOCAL;
	strcpy(name.sa_data, socket_name);

  connect(socket_id, &name, sizeof(name));

  length = strlen(msg) + 1;

	write(socket_id, &length, sizeof(int));
	write(socket_id, msg, length);

  close(socket_id);
}

int main(int argc, char **argv)
{
  char buffer[5];
  char stop = '\0';

  for (int i=1; i<=10; i++)
  {
    sprintf(buffer, "%d%c", i, stop);

    send_message(buffer);

    sleep(1);
  }

	return 0;
}
