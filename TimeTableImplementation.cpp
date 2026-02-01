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
using enrolementMatrix = std::vector<std::vector<int>>;

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

int caculateFitness(const GENOME& geno, enrolementMatrix enrolementMatrix){
    int hardViolations = 0;
    int softViolations = 0;

    int score;

    for(const auto& student : enrolementMatrix){
        std::vector<int> studentsExamTime;
        int examID = 0;

        for(const auto& takesExam: student){
            if(takesExam == 1){
                int timeSlot = geno[examID];
                studentsExamTime.push_back(timeSlot);
            }
            ++examID;
        }
    

    // check for hard constraints:
        std::unordered_set<int> seen;

        for(const auto& slot : studentsExamTime){
            if(seen.find(slot) != seen.end()){
                hardViolations++;
                break;
            }
            seen.insert(slot);
        }
        //soft constraints
        if(studentsExamTime.size() > 1){
            std::sort(studentsExamTime.begin(), studentsExamTime.end());

            for(int i = 0; i < studentsExamTime.size() -1; i++){
                if(studentsExamTime[i] == studentsExamTime[i+1]){
                    softViolations++;
                }
            }
        }
        //else no soft violations as there is just 1 exam scheduled

    }

    if(hardViolations > 1){
        score = -1000;
        // std::cout <<" " << score;
        return score;
    }
    else{
        score = 10 - softViolations;
        // std::cout <<" " << score;
        return score;
    }

}

int main(){
    std::vector<GENOME> randPOP = generatePopulation();
    int index = 1;
        
    for(const auto GENO : randPOP){
        
        
        std::cout << index << " ";
        
        for(auto it = GENO.begin(); it != GENO.end(); ++it) {
           std::cout <<  *it;       
        }

        enrolementMatrix testMatrix{
            {1, 0, 0, 1, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {1, 0, 0, 0, 1}
        };
        

        std::cout << " " << "Fitness: " << caculateFitness(GENO, testMatrix); 

        std::cout << "\n";
        ++index;
    }
    
    return 0;
}