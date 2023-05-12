from threading import Thread


# Calculating a dot product of row of matrix A and column of matrix B
def dotProduct(N: int, A: tuple[int], B: tuple[int]) -> int:
    result: int = 0
    # Calculating the result
    for i in range(N):
        result += (A[i] * B[i])
    return result


# This function is working as  a thread and it multiplies two matrices A and B
def multiply(N: int, A: tuple[tuple[int]], B: tuple[tuple[int]], C: list[list[int]], start: int, end: int) -> None:
    # Looping over a section of matrix A
    for i in range(start, end):
        # Looping over each row of matrix B
        for j in range(N):
            # Updating a matrix C using dot product
            C[i][j] = dotProduct(N, A[i], [ row[j] for row in B ])


# Function to take user input for size of matrix N, elements of matrix A, elements of matrix B
def takeUserInput() -> list[int, list[list[int]], list[list[int]]]:
    # Taking input of size of matrix
    N: int = int(input("Enter the size of N*N matrices:\t"))
    print()
    # Taking input of matrix A
    A: list[list[int]] = [ [ int(num) for num in input(f"Enter the numbers for row {i + 1} of matrix A:\t").split(" ") ] for i in range(N) ]
    print()
    # Taking input of matrix B
    B: list[list[int]] = [ [ int(num) for num in input(f"Enter the numbers for row {i + 1} of matrix B:\t").split(" ") ] for i in range(N) ]
    # returning all the user inputs
    print()
    return N, A, B


# Function to start multithreaded multiplication
def multiThreadedMultiplication(N: int, A: tuple[tuple[int]], B: tuple[tuple[int]], C: list[list[int]]) -> None:
    # The thread threshold to fire less than or equal to threadCount threads
    threadCount = 4
    # A list to store all the threads shoot
    threads: list[Thread] = []
    # These are the number of partitions that can be formed for given configuration
    partitions = N // threadCount

    # Looping to create a thread for each partition
    for i in range(threadCount):
        # This is a start of a partition 
        start = i * partitions
        # This is an end of a partition
        end = N if i == threadCount - 1 else (i + 1) * partitions
        # Creating thread for specified partition
        thread = Thread(target=multiply, args=[N, A, B, C, start, end])
        # Adding recently created thread to the threads is
        threads.append(thread)
        # Starting the current thread
        thread.start()
    
    # Joining all the threads to the main thread to get rid of orphan threads
    for thread in threads:
        thread.join()


# Printing the answer from answer matrix C
def printMatrix(C: tuple[tuple[int]]) -> None:
    print("Product of matrix A and matrix B:")
    for row in C:
        print(" ".join(str(value) for value in row))


# Taking user input from a function
N, A, B = takeUserInput()
# Initializing an answer matrix
C: list[list[int]] = [ [ 0 for _ in range(N) ] for _ in range(N) ]
multiThreadedMultiplication(N, A, B, C)
printMatrix(C)

