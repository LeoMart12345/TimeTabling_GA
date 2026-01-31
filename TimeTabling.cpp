// starting with the ONEMAX solution i made:

#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <random>
#include <cstdlib>
// Note to self for what to do
// Implemnt the tournament function 
// Implement some notion of eliteism aka (top 5 chromosomes with highest fitness go though)
// 

const int chromosomeSize = 8;
const int totalGenerations = 20;
const int POPULATION_SIZE = 100;
const int tournament_Size = 3;

using chromosome = std::bitset<chromosomeSize>; 

std::vector<std::bitset<chromosomeSize>> GeneratePopulation(int popSize) 
{
    std::vector<std::bitset<chromosomeSize>> population;
    //generate population
    
    for(int i = 0; i < popSize; i++){
        std::bitset<chromosomeSize> singleBitset;

        for(int bit = 0; bit < chromosomeSize; bit++){
            singleBitset[bit] = rand() % 2;
        }

        population.push_back(singleBitset);
    }
    return population;
}

int evaluationFitness(const chromosome& chr1){
    // bitset has .count that counts the # of 1s in the bitstring
    return chr1.count();
}

// takes in the population and then returns next generation of parents that have been though tournament selection

chromosome tournamentSelection(const std::vector<chromosome>& population, int tourNamentSize)
{
    // std::vector<std::bitset<chromosomeSize>> chosenParents;

    int bestFitness = -1;
    chromosome bestChromosome;

    for(int i = 0; i < tourNamentSize; i++){
        int randomIndex = rand() % population.size();

        chromosome currentChrom = population[randomIndex];
        int currentFitness = currentChrom.count();

        if(currentFitness > bestFitness){
            bestFitness = currentFitness;
            bestChromosome = currentChrom;
        }
    }
    return bestChromosome;
}

//single point crossover. 
std::pair<chromosome, chromosome> singlePointCrossover(chromosome& parent1, chromosome& parent2){
    
    std::pair<chromosome, chromosome> Children;
    //crossover logic

    for(int i = 0; i < chromosomeSize; i++){
        // making the first child
        if(i < chromosomeSize / 2){
            // to set the first half if the first child
            Children.first[i] = parent1[i]; 
            // to set the first half if the second child
            Children.second[i] = parent2[i];
        }else{
            // to set the second half of the first child
            Children.first[i] = parent2[i];
            // to set the second half of the second child
            Children.second[i] = parent1[i];
        }
       // making the second child.
    }

    return Children;
}

int main(){

    srand(time(NULL));

    // Generate starting population
    std::vector<std::bitset<chromosomeSize>> population = GeneratePopulation(POPULATION_SIZE);

    //make the initial population
    for(int generation = 0; generation < totalGenerations; generation++){
        
        //evaluate fitness

        std::vector<int> fitnesses;
        for(const auto& chrom : population){
            fitnesses.push_back(evaluationFitness(chrom));    
        }

        //select parents
        std::vector<chromosome> parents;

        for(int i = 0; i < POPULATION_SIZE; i++){
            chromosome parent = tournamentSelection(population, tournament_Size);
            parents.push_back(parent);
        }
        
        size_t index = 1;

        // for(auto& parent : parents){
        //     std::cout << index << " " << parent.to_string() << std::endl;
        //     ++index; 
        // }

        std::vector<chromosome> offspring;

        //crossover of these parents for crossover.
        for(int i =0; i < POPULATION_SIZE / 2; i++){
            chromosome parent1 = parents[i*2];
            chromosome parent2 = parents[i * 2 + 1];

            auto children = singlePointCrossover(parent1, parent2);

            offspring.push_back(children.first);
            offspring.push_back(children.second);

        }

        // can have mutation (leaving this out for now.)

        // new generation replaces old one.
        population = offspring;

        // track progress.
        int bestFitness = *std::max_element(fitnesses.begin(), fitnesses.end());
        int worstFitness = *std::min_element(fitnesses.begin(), fitnesses.end());
        // average
        double averageFitness = std::accumulate(fitnesses.begin(), fitnesses.end(), 0.0) / fitnesses.size();

        std::cout << "Gen " << generation 
                << ": Best=" << bestFitness 
                << ", Avg=" << averageFitness 
                << ", Worst=" << worstFitness << std::endl;
            }

    return 0;
}