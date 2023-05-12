# Contributed by Om Londhe 

# Importing sleep from time package, randint from random package along with Thread and Lock from threading package
from time import sleep
from random import randint
from threading import Thread, Lock


# This function states that a philosopher is doing a particular task
def do(id: int, task: str):
    print(f"Philosopher {id} is {task}ing...")
    # Assuming that the philosopher is doing the task for the random seconds
    sleep(randint(0, 2))


# Function to acquire the fork or release the fork
def doFork(id: int, task: str, leftFork: int, rightFork: int, forks: list[Lock]):
    # If we it is acquire operation
    if task == "acquire":
        # If it is even philosopher, first acquire left fork and then right fork
        if id & 1 == 0:
            forks[leftFork].acquire()
            forks[rightFork].acquire()
        # Else, first acquire right fork and then the left fork
        else:
            forks[rightFork].acquire()
            forks[leftFork].acquire()
    # Else release the forks in any order
    else:
        # Releasing all the forks
        forks[leftFork].release()
        forks[rightFork].release()
    print(f"Philosopher {id} {task}d forks")



# This is how dining philosophers will work together
def diningPhilosopher(id: int, n: int, forks: list[Lock]) -> None:
    leftFork = id 
    rightFork = (id + 1) % n 

    # Adding the code in infinite while loop as this task will be always going on
    while True:
        # Denotes that philosopher is thinking
        do(id, "think")
        # Denotes that philosopher is acquiring the forks
        doFork(id, "acquire", leftFork, rightFork, forks)
        # Denotes that philosopher is eating
        do(id, "eat")
        # Denotes that philosopher is releasing the forks
        doFork(id, "release", leftFork, rightFork, forks)



# These are the number of philosophers around a dining and thus the number of forks
n = 5
# These are the forks which will be acquired or release by a philosopher
forks: list[Lock] = [ Lock() for _ in range(n) ]
# These are the philosophers who will be thinking or eating 
philosophers: list[Thread] = [ Thread(target=diningPhilosopher, args=[id, n, forks]) for id in range(n) ]

# Starting all the threads representing philosophers
for philosopher in philosophers:
    philosopher.start()

# Joining all the philosophers to the main thread
for philosopher in philosophers:
    philosopher.join()