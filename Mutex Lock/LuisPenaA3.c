/*
 *This program implements a critical section using the mutex lock
 *primitive for two separate threads.
 *
 *@author Luis Pena (PID 6300130)
 *@version 6/30/2023
 *
 *Proof that code satisfies the critical section problem:
 *
 *The pthread_mutex_trylock() function and mutex lock ensure
 *that only one thread may enter the critical section at a
 *time, preventing race conditions that can lead to a corruption
 *of counter->value. Specifically, this satisfies the mutual 
 *exclusion requirement, while the ability of each thread to
 *acquire the lock when it is not in use satisfies the progress
 *requirement, and, finally, bounded waiting is satisfied indirectly
 *through the mutex lock primitive through FIFO.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_UPDATES 2000000

//Shared variable struct to store result
struct shared_data
{
    int value;  
};

//Intanstiating global shared variable
struct shared_data *counter;

// Mutex lock
pthread_mutex_t mutex;

//Thread 1 function
void *thread1()
{
	//Instantiating and initializing variables
	int i = 0;
	int bonus = 0;
		
	while (i < MAX_UPDATES)
       	{
		//Entry section
		if (pthread_mutex_trylock(&mutex) == 0)
		{
            
			//Critical section
			counter->value += 1;
			
			//Remainder section
			if(counter->value % 100 == 0)
			{
				counter->value += 100;
				bonus += 1;
			}
		}

		//Exit section
		pthread_mutex_unlock(&mutex);
		i++;
	}
    
	//Printing output
    	printf("%s %d %s %d %s %d\n","I'm Thread 1, I did", MAX_UPDATES,"updates and I got bonus for", bonus, "times, counter =", counter->value);
    
	//Returning NULL for void function
    	return NULL;
}

//Thread 2 function
void *thread2()
{
	//Instantiating and initializing variables
	int i = 0;
	
	while (i < MAX_UPDATES)
	{
        	//Entry section 
        	if (pthread_mutex_trylock(&mutex) == 0)
		{
            
			/* Critical section */
          		counter->value += 1;
            	}

		//Exit section
		pthread_mutex_unlock(&mutex); 
    
		i++;
	}

    	//Printing output
        printf("%s %d %s %d\n", "I'm Thread 2, I did", MAX_UPDATES, "updates, count =", counter->value);
   	
	//Returning NULL for void function
	return NULL;
}

//Main function
int main()
{
	//Instantiating threads and variables
	pthread_t tid[2];
    	int rc;

    	//Allocating memory for shared data
    	counter = (struct shared_data *) malloc(sizeof(struct shared_data));
    	counter->value = 0;

    	//Initializing mutex lock
    	if((pthread_mutex_init(&mutex, NULL)))
	{
		//Informing user of error
		printf("Error occured when initialize mutex lock.");
		exit(0);
    	}

    	//Thread scheduler
    	pthread_attr_t attr;
   	
	//Independent thread scheduler
	if((pthread_attr_init(&attr)))
       	{
       		printf("Error occured when initialize pthread_attr_t.");
        	exit(0);
    	}
   	
       	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    	//Creating thread1
    	if((rc = pthread_create(&tid[0], &attr, thread1, NULL)))
	{
        	fprintf(stderr, "ERROR: pthread_create, rc: %d\n", rc);
        	exit(0);
    	}
    
	//Creating thread2
    	if((rc = pthread_create(&tid[1], &attr, thread2, NULL)))
	{
        	fprintf(stderr, "ERROR: pthread_create, rc: %d\n", rc);
        	exit(0);
	}

    	//Waiting for threads to finish
   	 pthread_join(tid[0], NULL);
   	 pthread_join(tid[1], NULL);


	 //Printing parent counter
	 printf("%s %d\n", "From parent counter =", counter->value);

    	//Cleaning up
    	pthread_mutex_destroy(&mutex);
    	free(counter);
    	pthread_exit(NULL);

    	//Returning 0 for INT function
    	return 0;
}
