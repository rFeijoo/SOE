#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int counter;

void* my_thread(void* params)
{
	int last_value = -1;

	while (1)
	{
		if (last_value != counter)
		{
			printf("%d\n", counter);
			last_value = counter;
		}

		if (last_value == 10)
			break;
	}

	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t my_thread_id;

	pthread_create(&my_thread_id, NULL, &my_thread, NULL);

	for (int i=0; i<10; i++)
	{
		counter = i + 1;
		sleep(1);
	}

	return 0;
}
