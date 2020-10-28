#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "gpio_sysfs.h"

// const int led_pin = 4;
// const int btn_pin = 4;//17;

// void parent_process(int *fd)
// {
//   int state;
//   char msg[30];

//   setup_io();

//   INP_GPIO(btn_pin);

//   // printf("ESTADO = %d\n", GET_GPIO(btn_pin));

//   while (1)
//   {
//     puts("Pressione o botao");
//     while (GET_GPIO(btn_pin));
//     puts("Botao pressionado");
//     while (GET_GPIO(btn_pin)==0);
//     puts("Botao solto");
//   }

//   // for (int i=1; i<=10; i++)
//   // {
//   //   sprintf(msg, "%d", i);

//   //   if (write(fd[1], msg, sizeof(msg)) < 0)
//   //   {
//   //     printf("Erro na escrita da mensagem\n");
//   //     wait(&state);
//   //   }

//   //   sleep(1);
//   // }

//   // printf("Fim de execução do processo pai [PID = %d]\n", (int)getpid());

//   exit(1);

// }

// void son_process(int *fd)
// {
//   char msg[30];
//   int n = 0;

//   // while (n != 10)
//   // {
//   //   if (read(fd[0], msg, 30) < 0)
//   //     printf("Erro na leitura da mensagem\n");
//   //   else
//   //     printf("Mensagem recebida [PID = %d] = %s\n", (int)getpid(), msg);

//   //   n = atoi(msg);
//   // }

//   printf("Fim de execução do processo filho [PID = %d]\n", (int)getpid());

//   exit(1);
// }

// // int main(int argc, char **argv)
// // {
// //   setup_io();
// //   INP_GPIO(4);
// //   puts("Pressione o botao");
// //   while (GET_GPIO(4));
// //   return 0;



// //   // int pid, fd[2];

// //   // printf("Processo principal [PID = %d]\n", (int)getpid());

// //   // pipe(fd);

// //   // pid = fork();

// //   // if (pid == 0)
// //   //   son_process(fd);
// //   // else
// //   // if (pid != 0)
// //   //   parent_process(fd);

// //   return 0;
// // }




int pin = 4;

void unset_GPIO(int signum)
{
    fprintf(stderr, "\nGPIO unset\n");

    if (unsetGPIO(pin) < 0)
        exit(-3);

    exit(0);
}

int main(int argc, char **argv)
{
    signal(SIGINT, unset_GPIO);

    if (setGPIOdirection(pin, "in") < 0)
    {
        printf("ERROR - unable to set GPIO %d\n", pin);
        return -1;
    }

    for (;;)
    {
        printf("STATE = %d\n", GPIOread(pin));

        sleep(1);
    }

    return 0;
}