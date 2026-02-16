TimeTableImplementation.cpp is main file to compile and run. can just run Test.exe if needed.

To Compile
 g++ TimeTableImplementation.cpp -o Test

To Run
./Test

Test matrices are included

Functions:
readMatrixFileAndMakeMatrix(filename): Reads input file and returns enrollment matrix and problem dimensions


generatePopulation(popSize, numExams, numTimeSlots): Creates initial random population of exam schedules


calculateFitness(genome, matrix): Evaluates fitness: returns -1000 if hard constraints violated, else 1000 minus soft violations


tournamentSelection(population, scores, tournamentSize): Selects parent by randomly picking 3 individuals and returning the best


singlePointCrossover(parent1, parent2): Splits parents at midpoint and swaps halves to create two offspring


calculateAverage(fitnessScores): Computes average fitness across the population


runGA(population, matrix, numTimeSlots): Main GA loop implementing elitism (preserves best solution each generation), followed by selection, crossover, mutation (5% rate applied to both offspring), and replacement for 100 generations