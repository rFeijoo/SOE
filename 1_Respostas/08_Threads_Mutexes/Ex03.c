#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VECTOR_SIZE 50000
//#define DEBUG_MODE

volatile long int v[VECTOR_SIZE], max[4];

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

void search_for_max_A(void)
{
  long int max = 0;
  int pos;

  for (int i=0; i<VECTOR_SIZE; i++)
  {
    if (v[i] > max)
    {
      max = v[i];
      pos = i;
    }
  }

  printf("[A]: %ld (pos = %d)\n", max, pos);
}

void search_for_max_B(void)
{
  long int aux = 0;

  for (int i=0; i<4; i++)
  {
    if (max[i] > aux)
      aux = max[i];
  }

  printf("[B]: %ld\n", aux);
}

void* my_thread(void* params)
{
  struct thread_args* p = (struct thread_args*)params;

  int stop_addr = (p->start_index + (VECTOR_SIZE / 4)) - 1;

  max[p->ID - 1] = v[p->start_index];

  for (int i=p->start_index; i<stop_addr; i++)
  {
    if (v[i] > max[p->ID - 1])
      max[p->ID - 1] = v[i];
  }

  printf("\tThread %d - [%d : %d] max = %ld\n", p->ID, p->start_index, stop_addr, max[p->ID - 1]);

	return NULL;
}

int main(int argc, char **argv)
{
  generate_random_vector();

  search_for_max_A();

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

  search_for_max_B();

	return 0;
}
