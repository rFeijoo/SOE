#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VECTOR_SIZE 50000
//#define DEBUG_MODE

volatile long int v[VECTOR_SIZE], av[4], average;

struct thread_args
{
	int ID;
	int start_index;
};

void generate_random_vector(void)
{
  for (int i=0; i<VECTOR_SIZE; i++)
    v[i] = random();

#ifdef DEBUG_MODE
  for (int i=0; i<VECTOR_SIZE; i++)
  {
    printf("%ld", v[i]);
    if (i < VECTOR_SIZE - 1)
      printf(", ");
  }
  printf("\n");
#endif /*DEBUG_MODE*/
}

void get_average(void)
{
  for (int i=0; i<VECTOR_SIZE; i++)
  	average += v[i];
	average /= VECTOR_SIZE;

  printf("Average = %ld\n", average);
}

int comp_values(long int a, long int b)
{
	long int aux1;
	if (average > a)
		aux1 = average - a;
	else
		aux1 = a - average;

	long int aux2;
	if (average > b)
		aux2 = average - b;
	else
		aux2 = b - average;

	if (aux1 <= aux2)
		return 1;

	return 0;
}

void search_for_av_A(void)
{
	long int av_value = 0;
	int pos;

	for (int i=0; i<VECTOR_SIZE; i++)
	{
		if (comp_values(v[i], av_value))
		{
			av_value = v[i];
			pos = i;
		}
	}

	printf("[A]: %ld (pos = %d)\n", av_value, pos);
}

void search_for_av_B(void)
{
	long int av_value = 0;

	for (int i=0; i<4; i++)
	{
		if (comp_values(av[i], av_value))
			av_value = av[i];
	}

	printf("[B]: %ld\n", av_value);
}

void* my_thread(void* params)
{
  struct thread_args* p = (struct thread_args*)params;

  int stop_addr = (p->start_index + (VECTOR_SIZE / 4)) - 1;

  av[p->ID - 1] = v[p->start_index];

  for (int i=p->start_index; i<stop_addr; i++)
  {
    if (comp_values(v[i], av[p->ID - 1]))
      av[p->ID - 1] = v[i];
  }

  printf("\tThread %d - [%d : %d] average = %ld\n", p->ID, p->start_index, stop_addr, av[p->ID - 1]);

	return NULL;
}

int main(int argc, char **argv)
{
  generate_random_vector();

  get_average();

	search_for_av_A();

  pthread_t my_thread_id1;
  struct thread_args thread1_args;
  thread1_args.ID = 1;
  thread1_args.start_index = 0;
	pthread_create(&my_thread_id1, NULL, &my_thread, &thread1_args);

  pthread_t my_thread_id2;
  struct thread_args thread2_args;
  thread2_args.ID = 2;
  thread2_args.start_index = VECTOR_SIZE / 4;
	pthread_create(&my_thread_id2, NULL, &my_thread, &thread2_args);

  pthread_t my_thread_id3;
  struct thread_args thread3_args;
  thread3_args.ID = 3;
  thread3_args.start_index = (2 * VECTOR_SIZE) / 4;
	pthread_create(&my_thread_id3, NULL, &my_thread, &thread3_args);

  pthread_t my_thread_id4;
  struct thread_args thread4_args;
  thread4_args.ID = 4;
  thread4_args.start_index = (3 * VECTOR_SIZE) / 4;
	pthread_create(&my_thread_id4, NULL, &my_thread, &thread4_args);

  pthread_join(my_thread_id1, NULL);
  pthread_join(my_thread_id2, NULL);
  pthread_join(my_thread_id3, NULL);
  pthread_join(my_thread_id4, NULL);

  search_for_av_B();

	return 0;
}
