#include "gpio_sysfs.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

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
    if (argc != 2)
    {
        puts("Modo de uso:");

        printf("%s FREQUENCIA (em uS)\n", argv[0]);

        exit(1);
    }

    signal(SIGINT, unset_GPIO);

    int freq = atoi(argv[1]);

    if (setGPIOdirection(pin, "out") < 0)
    {
        printf("ERROR - unable to set GPIO %d\n", pin);
        return -1;
    }

    for (;;)
    {
        if (GPIOwrite(pin, 1) < 0)
            return -2;

        usleep(freq);

        if (GPIOwrite(pin, 0) < 0)
            return -3;

        usleep(freq);
    }

    return 0;
}