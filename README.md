Code Structure


Functions:

readMatrixFileAndMakeMatrix(filename): Reads input file and returns enrollment matrix and problem dimensions

generatePopulation(popSize, numExams, numTimeSlots): Creates initial random population of exam schedules

calculateFitness(genome, matrix): Evaluates fitness: returns -1000 if hard constraints violated, else 1000 minus soft violations

tournamentSelection(population, scores, tournamentSize): Selects parent by randomly picking 3 individuals and returning the best

singlePointCrossover(parent1, parent2): Splits parents at midpoint and swaps halves to create two offspring

calculateAverage(fitnessScores): Computes average fitness across the population

runGA(population, matrix, numTimeSlots): Main GA loop: selection, crossover, mutation, and summary stats