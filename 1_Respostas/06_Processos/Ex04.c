#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int v_global = 0; // Variavel global para este exemplo
void Incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n", v_global);
}

void fork_process(void)
{
  pid_t child_pid = fork();

  if (child_pid == 0)
  {
    Incrementa_Variavel_Global(getpid());

    printf("Fim de execução [PID = %d]\n", (int)getpid());

    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char **argv)
{
  printf("PID do processo principal: %d\n", (int)getpid());

  for (int i=0; i<3; i++)
    fork_process();

  sleep(1);

  printf("Fim de execução do processo principal [PID = %d]\n", (int)getpid());

  return 0;
}
