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
    signal(SIGINT, unset_GPIO);

    if (setGPIOdirection(pin, "out") < 0)
    {
        printf("ERROR - unable to set GPIO %d\n", pin);
        return -1;
    }

    for (;;)
    {
        if (GPIOwrite(pin, 1) < 0)
            return -2;

        usleep(500000);

        if (GPIOwrite(pin, 0) < 0)
            return -3;

        usleep(500000);
    }

    return 0;
}