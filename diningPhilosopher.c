#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/*

# There are two types of semaphores :-

  1.Binary semaphore
  2.Counting semaphore

# The binary semaphore is used when there is only one instance of the resource whereas the counting semaphore is used when there are multiple instances of the resources.
 
# We are using both types of semaphores in the following program.

# Here, the semaphore room is a counting semaphore since there is one dining room which can accommodate 9 philosophers.

# Consider there are 9 chairs in the room and that is the resource. Hence there are multiple instances of the resource in the room. Therefore, room is a counting semaphore.
 
 */

sem_t room;
sem_t Fork[10];

void * Philosopher(void * philo_num);
void Eat(int philo);

int main()
{
	// Taking Input of Number of Philosophers
	int philo_num = 0;
	printf("\nEnter the Number of Philosopher Between 1 - 10 : ");
	scanf("%d", &philo_num);

	// Creating Array of Philosophers
	int Philo[philo_num];
	
	// Initialising Threads for each Philospher
	pthread_t threads[philo_num];

	/*

	 # At the backend the sem_init fuction looks like :-

	 ---->  int sem_init(sem_t * sem, int pshared, unsigned int value); <----

	 # The first parameter is the pointer to the declared semaphore.

         # The second parameter is pshared. If it is zero, the semaphore is shared between threads, else it is shared between processes. In our case it is zero meaning it is shared between threads.

         # The third parameter value is the value with which the semaphore is initialized.
	 
	 */
	sem_init(&room,0,9);
	
	for(int i = 1; i <= philo_num; i++)
	{
		/*

		 # Since there are 10 Forks, we are creating semaphores between 1 - 10 referring to the Forks F0-F[philo_num]
                 
		 # For the Forks, we are using binary semaphores since for every Fork, F0 - F[philo_num] we have only one instance of it.
		 
		 */
		sem_init(&Fork[i],0,1);
	}

	for(int i = 1; i <= philo_num; i++)
	{
		/*

		 # Here we are creating threads 
		 
		 # These threads refer to the number of philosophers i.e(philo_num) sitting around the table.
		 
		 # We have them as threads since we want these to execute simultaneously (i.e. we want multiple philosophers to eat at a time).
                 
		 # Now there can be a situation where all threads start executing i.e. all philosophers enter the room and cause deadlock. Hence, we are allowing {philo_num - 1} philosophers to enter the room first so that at least one of them can finish eating.

		 # We are calling the function Philosopher() from pthread_create and passing it the address of an integer variable which refers to the philosopher number.

		 */
		Philo[i] = i;
		pthread_create(&threads[i],NULL,Philosopher,(void *)&Philo[i]);
	}

	for(int i = 1; i <= philo_num; i++)
	{
		// After all the Philosopher are done, we join the threads back to the main process.
		pthread_join(threads[i],NULL);
	}
	printf("\n");
	return 0;
}

void * Philosopher(void * philo_num)
{
	// First converting the number passed as a void * into integer.
	int philo = * (int *) philo_num;

	/* 
	
	 # Then calling the sem_wait function which first checks if the resource is available and if it is available, the resource is allocated to the philosopher i.e. the semaphore is locked.
	 
	 # At the backend the sem_wait function for counting semaphore looks like :-
	  >--------------------------------------------------------------------<
	  	struct semaphore 
		{
      			int count;
      			queueType queue;
		};
		void sem_wait(semaphore s)
		{		
      			s.count--;
      			if(s.count<0)
      			{
            			// place this process in s.queue
            			// block this process     
      			}
		}
	   >-------------------------------------------------------------------<

	 # So here, the number of semaphores is decremented, meaning one of the semaphores is allocated. If all of the resources are allocated, the thread is placed on waiting queue.

	*/ 
	sem_wait(&room);

	printf("\nPhilosopher %d has Entered the Room", philo);
	
	/*
	
	 # Now, we apply sem_wait on forks which are binary semaphores.

	 # At the backend the sem_wait function for binary semaphore looks like :-
	  >---------------------------------------------------------------------<
		struct binary_semaphore 
		{
      			enum {zero,one} value;
      			queueType queue;
		};	

		void sem_wait(binary_semaphore s)
		{
      			if(s.value == one)
           		{
				s.value = zero;
			}
      			else
      			{
              			// place this process in s.queue 
              			// block this process
      			}
		}
	   >--------------------------------------------------------------------<

	 # Here, according to the prototype, if the value of semaphore is one, it is changed to zero indicating that the semaphore is blocked.

	 # In our case we are blocking the forks towards the left and the right of the philosopher.
	 
	 # For example, for philosopher P0, we are blocking Fork F0 and F4. 	   

	*/ 
	sem_wait(&Fork[philo]);
	sem_wait(&Fork[(philo + 1) % 5]);

	// Then, we are allowing the philosophers to eat.
	Eat(philo);

	sleep(2);

	printf("\nPhilosopher %d has Finished Eating", philo);
	
	/*
	 # Finally, we are freeing the semaphores by calling the sem_post() function so that the other threads that are placed on the queue can use the resources.

	 # At the backend the sem_post function for binary semaphore looks like :-
	  >----------------------------------------------------------------------<
	  	void sem_post(semaphore s)
		{
      			if(s.queue is empty)
			{
           		 	s.value=one;
			}
      			else
      			{
            			// remove a process P from s.queue 
            			// place process P on ready list 
      			}
		}
	  >----------------------------------------------------------------------<
	  
	 # If it returns a positive value, the semaphore is unlocked successfully. 

	 # Using the above functions, we free all the semaphores so that they can be used by other threads.
	 
	 */	
	sem_post(&Fork[(philo + 1) % 5]);
	sem_post(&Fork[philo]);
	sem_post(&room);
}

void Eat(int philo)
{
	printf("\nPhilosopher %d is Eating", philo);
}

