#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define VECTOR_SIZE 50000
#define QNT_THREADS 4
//#define DEBUG_MODE

#define MULTIPLIER	(2.00)

long double v[VECTOR_SIZE];

struct thread_args {
	int ID;
	long double *ptr;
	double x;
};

void generate_random_vector(void)
{
	srand(time(NULL));

  for (int i=0; i<VECTOR_SIZE; i++)
		v[i] = (rand() & 0x64) * ((double)i + 0.84); // PSEUDO-RANDOM GENERATOR

	#ifdef DEBUG_MODE
		printf("V[50000] = ");
	  for (int i=0; i<VECTOR_SIZE; i++)
	  {
	    printf("%.2Lf", v[i]);
	    if (i < VECTOR_SIZE - 1)
	      printf(", ");
	  }
	  printf("\n");
	#endif /*DEBUG_MODE*/
}

void* my_thread(void* params)
{
  struct thread_args* p = (struct thread_args*)params;

	for (int i=0; i<(VECTOR_SIZE / QNT_THREADS); i++)
		p->ptr[i] *= p->x;

	#ifdef DEBUG_MODE
		printf("[Thread %d]: ", p->ID);
	  for (int i=0; i<(VECTOR_SIZE / QNT_THREADS); i++)
	  {
	    printf("%.2Lf", p->ptr[i]);
	    if (i < (VECTOR_SIZE / QNT_THREADS) - 1)
	      printf(", ");
	  }
	  printf("\n");
	#endif /*DEBUG_MODE*/

  return NULL;
}

void copy_to_vector(int start, int stop, long double *ptr)
{
	int index = 0;

	for (int i=start; i<stop; i++)
		v[i] = ptr[index++];
}

int main()
{
  generate_random_vector();

  pthread_t my_threads[QNT_THREADS];
	struct thread_args args[QNT_THREADS];

	for (int i=0; i<QNT_THREADS; i++)
	{
		args[i].ID  = i + 1;
		args[i].ptr = &(v[i * (VECTOR_SIZE / QNT_THREADS)]);
		args[i].x   = MULTIPLIER;

		pthread_create(&my_threads[i], NULL, &my_thread, &args[i]);
		pthread_join(my_threads[i], NULL);
	}

	for (int i=0; i<QNT_THREADS; i++)
		copy_to_vector(i * (VECTOR_SIZE / QNT_THREADS),
											(i + 1) * (VECTOR_SIZE / QNT_THREADS),
													args[i].ptr);

	#ifdef DEBUG_MODE
		printf("V[50000] = ");
	  for (int i=0; i<VECTOR_SIZE; i++)
	  {
	    printf("%.2Lf", v[i]);
	    if (i < VECTOR_SIZE - 1)
	      printf(", ");
	  }
	  printf("\n");
	#endif /*DEBUG_MODE*/

	return 0;
}
