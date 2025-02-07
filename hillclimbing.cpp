#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Objective function to maximize
int objectiveFunction(int x) {
    return -1 * (x * x - 10 * x + 25); // Example: f(x) = -(x^2 - 10x + 25)
}

// Generate neighboring solutions
int generateNeighbor(int current) {
    return current + (rand() % 3 - 1); // Randomly move -1, 0, or +1
}

// Hill Climbing algorithm
int hillClimbing(int initialSolution) {
    int currentSolution = initialSolution;
    int currentFitness = objectiveFunction(currentSolution);
    
    while (true) {
        int neighbor = generateNeighbor(currentSolution);
        int neighborFitness = objectiveFunction(neighbor);

        // If the neighbor is better, move to it
        if (neighborFitness > currentFitness) {
            currentSolution = neighbor;
            currentFitness = neighborFitness;
        } else {
            break; // No better neighbors found, exit
        }
    }
    
    return currentSolution;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
    int initialSolution = rand() % 20; // Random initial solution between 0 and 19
    int bestSolution = hillClimbing(initialSolution);

    std::cout << "Best Solution: " << bestSolution << std::endl;
    std::cout << "Best Fitness: " << objectiveFunction(bestSolution) << std::endl;

    return 0;
}

