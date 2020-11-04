#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

int main(void)
{
	char user_inputs[100], i;
	unsigned char slave_addrs[2] = {0x80, 0x81};
	
    int i2c_fd = open("/dev/i2c-1", O_RDWR);

	for (i=1; i<5; i++)
	{
		puts("Digite os 4 caracteres para mostrar"
			" nos 4 displays de 7 segmentos.");

		scanf("%s", user_inputs);

		ioctl(i2c_fd, I2C_SLAVE, slave_addrs[0]);
		write(i2c_fd, user_inputs, 4);

		printf("oi\n");

        puts("Digite o texto para mostrar no"
			" display LCD.");

		scanf("%s", user_inputs);

		ioctl(i2c_fd, I2C_SLAVE, slave_addrs[1]);
		write(i2c_fd, user_inputs,
			strlen(user_inputs)+1);
	}

	close(i2c_fd);

	return 0;
}