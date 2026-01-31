#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <array>
#include <unordered_set>

//Hard constraints: student cant have >1 test on at a time
//Soft constraint: minimize the consecutive tests for a student

// TODO: implement the new genome representation: 
// Genome: [3, 1, 2, 1, 4, 2, 3, 4, 1, 2]
// The index is the exam index 0 = exam 0;


const int GENOME_SIZE = 8;
const int totalGenerations = 10;
const int POPULATION_SIZE = 100;
const int tournament_Size = 3;
// Specific to timetabling:

const int EXAMS_TO_BE_SCHEDULED = 5;
const int AVAILABLE_TIME_SLOTS = 10;
const int NUMBER_OF_STUDENTS = 5;

using GENOME = std::array<int, GENOME_SIZE>;

std::vector<GENOME> generatePopulation(){
    
    std::vector<GENOME> population;

    for(int i = 0; i < POPULATION_SIZE; i++){

        GENOME geno;

        for(int j = 0; j < GENOME_SIZE; j++){

            geno[j] = rand() % AVAILABLE_TIME_SLOTS;
    
        }
        population.push_back(geno);
    }
    
    return population;
    
}
// returns 0 if hard constraints violated
int caculateFitness(GENOME geno){
    // Hard constraints: set the fitness to 0 if the there are 2 of the same numbers.

    // find a duplicate in a string:

    std::unordered_set<int> seen; 

    for(int i = 0; i < geno.size(); i++){
        if(seen.find(geno[i]) != seen.end()){
            return 0;
        }
        seen.insert(geno[i]);
    }
    // test the soft constaints here!


    return 2;
}

GENOME findParentTournament(std::vector<GENOME>){

    


}


int main(){

    std::vector<GENOME> randPOP = generatePopulation();
    int index = 1;

    for(const auto GENO : randPOP){
        
        
        std::cout << index << " ";
        
        for(auto it = GENO.begin(); it != GENO.end(); ++it) {
           std::cout <<  *it;       
        }

        std::cout << " " << "Fitness: " << caculateFitness(GENO); 

        std::cout << "\n";
        ++index;
    }

    return 0;
}