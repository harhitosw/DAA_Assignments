# Importing randint function from random package
from random import randint


N = 5 # Number of cities
INT_MAX = 2 ** 31 # INT_MAX is the max value possible which is infinite basically 
POPULATION_SIZE = 10 # POPULATION_SIZE defines the size of the population


# Creating the class called as Gnome 
# It has data members as gnome and fitness
class Gnome:
    # A constructor to create data members
    def __init__(self) -> None:
        self.gnome = ""
        self.fitness = 0
    
    # Below two are the functions for default comparator of sort method
    def __lt__(self, other):
        return self.fitness < other.fitness
    
    def __gt__(self, other):
        return self.fitness > other.fitness


# A function to create a gnome
def createGnome() -> str:
    # Initializing gnome with "0" denoting that we are starting from city "0"
    gnome: str = "0"
    # Trying to build combinations of different paths
    while True:
        # If we have added all the cities, we add the "0th" city again and break the loop
        if gnome.__len__() == N:
            gnome += gnome[0]
            break
        # We get the random city
        city = chr(randint(1, N - 1) + 48)
        # We add that city to the gnome if and only if it does not exist in the gnome
        if gnome.find(city) == -1:
            gnome += city
    # we are returning the gnome
    return gnome


# This is the function to calculate the fitness of the gnome
def calculateFitness(gnome: str, matrix: tuple[tuple[int]]) -> int:
    fitness: int = 0
    # Looping over each city in gnome
    for i in range(1, N):
        # If the 
        if matrix[ord(gnome[i]) - 48][ord(gnome[i + 1]) - 48] == INT_MAX:
            return INT_MAX
        fitness += matrix[ord(gnome[i]) - 48][ord(gnome[i + 1]) - 48]
    return fitness


# This function is to mutate the gnome already created
def mutate(gnome: str) -> str:
    gnome = list(gnome)
    # Looping till we do not mutate
    while True:
        # Getting a random index 1
        r1 = randint(1, N - 1)
        # Getting a random index 2
        r2 = randint(1, N - 1)
        # If both the indices are not same, replace the cities(chars) at that position
        if r1 != r2:
            gnome[r1], gnome[r2] = gnome[r2], gnome[r1]
            break
    # return the mutated gnome
    return "".join(gnome)


def travelingSalesmanProblem(matrix: tuple[tuple[int]]):
    # Initializing the generation
    generation = 1
    # These are the max number of generation possible
    generationThreshold = 5
    # Population list will contain all the gnomes
    population: list[Gnome] = []

    # Creating a gnome to add to the population and make it as initial configuration
    gnome = Gnome()
    print("----------------------------")
    print("Initial configuration")
    print("GNOME\t\tFITNESS")
    print("----------------------------")
    # For every population, we are creating initial gnome configuration
    for _ in range(POPULATION_SIZE):
        # Creating a gnome
        gnome.gnome = createGnome()
        # Calculating fitness for gnome
        gnome.fitness = calculateFitness(gnome.gnome, matrix)
        # Appending gnome to the population
        population.append(gnome)
        print(f"{gnome.gnome}\t\t{gnome.fitness}")
    print()

    # Defining the temperature
    temperature = 10000
    # Looping till temperature is greater than 1000 we have not gone through generationThreshold generations.
    while temperature >= 1000 and generation <= generationThreshold:
        # Sorting the population in ascending order
        population.sort()
        # Defining new population list
        newPopulation: list[Gnome] = []
        # Printing
        print("----------------------------")
        print(f"Current temperature: {temperature}")
        print(f"Generation: {generation}")
        print("GNOME\t\tFITNESS")
        print("----------------------------")

        # Looping through all the gnomes of population
        for gnome in population:
            # Creating a new Gnome for new Population list
            newGnome = Gnome()
            while True:
                # mutating the original gnome to get a new gnome
                newGnome.gnome = mutate(gnome.gnome)
                # calculating the fitness of the new gnome
                newGnome.fitness = calculateFitness(newGnome.gnome, matrix)

                # If the fitness of new Gnome is less than the previous Gnome or
                # The probability is reached, then
                # add it to the new population
                if newGnome.fitness <= gnome.fitness or pow(2.7, -((newGnome.fitness - gnome.fitness) / temperature)) > 0.5:
                    # Adding to the population
                    newPopulation.append(newGnome)
                    break

        # Updating the temperature
        temperature = (90 * temperature) / 100
        # Assigning population to newPopulation
        population = newPopulation
        # Incrementing the generation
        generation += 1

        # Printing the gnome
        for gnome in population:
            print(f"{gnome.gnome}\t\t{gnome.fitness}")
        print()


matrix = [
    [0, 2, INT_MAX, 12, 5],
    [2, 0, 4, 8, INT_MAX],
    [INT_MAX, 4, 0, 3, 3],
    [12, 8, 3, 0, 10],
    [5, INT_MAX, 3, 10, 0],
]
travelingSalesmanProblem(matrix)




    
