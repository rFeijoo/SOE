#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void alarm_handler(int sig)
{
  system("date +%H:%M:%S:%N");
  alarm(1);
}

int main(int argc, char **argv)
{
  signal(SIGALRM, alarm_handler);

  alarm(1);

  printf("Press CTRL+C to stop:\n");

  while (1)
    ;

  return 0;
}
