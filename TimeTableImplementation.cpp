#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <array>
#include <unordered_set>
#include <iostream>
#include <fstream>
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

using GENOME = std::vector<int>;


struct FileData {
    enrolementMatrix matrix;
    int numExams;
    int numTimeSlots;
    int numStudents;
};

FileData readMatrixFileAndMakeMatrix(const std::string& fileName) {
    FileData data;
    std::ifstream file(fileName);
    
    file >> data.numExams >> data.numTimeSlots >> data.numStudents;
    
    data.matrix = enrolementMatrix(data.numStudents, std::vector<int>(data.numExams));
    
    for(int i = 0; i < data.numStudents; i++) {
        for(int j = 0; j < data.numExams; j++) {
            file >> data.matrix[i][j];
        }
    }
    return data;
}



std::vector<GENOME> generatePopulation(int popSize, int numExams, int numTimeSlots) {
    std::vector<GENOME> population;
    
    for(int i = 0; i < popSize; i++) {
        GENOME geno(numExams);
        
        for(int exam = 0; exam < numExams; exam++) {
            geno[exam] = (rand() % numTimeSlots) + 1;
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
                if(studentsExamTime[i] + 1 == studentsExamTime[i+1]){
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

GENOME tournamentSelection(const std::vector<GENOME>& pop, const std::vector<int> scores, int tournament_Size){
    int bestIndex = rand() % pop.size();
    int bestFitness = scores[bestIndex];

    for(int i = 0; i < tournament_Size; i++){
        int randomIndex = rand() % pop.size();
        if(scores[randomIndex] > bestFitness){
            bestFitness = scores[randomIndex];
            bestIndex = randomIndex;
        }        
    }

    return pop[bestIndex];
}

int main(){
    srand(time(0));

    //read in the data from the file
    FileData fileStruct = readMatrixFileAndMakeMatrix("Matrix.txt");

    int numExams = fileStruct.numExams;
    int numStudents = fileStruct.numStudents;
    int numTimeSlots = fileStruct.numTimeSlots;

    enrolementMatrix matrix = fileStruct.matrix;

    // to print the matrix
    for(const auto& student: matrix){
        for(const auto& exam : student){
            std::cout << matrix[student.size()][exam] << " ";
        }
        std::cout << "\n";
    }

    // generate the rand population
    std::vector<GENOME> randPOP = generatePopulation(POPULATION_SIZE, numExams, numTimeSlots);
    
    int index = 1;
    for(const auto& genome : randPOP){
        std::cout << index << " ";
        for(const auto& num : genome){
            std::cout << num;
        }
        std::cout << "\n";
        index++;
    }

    std::vector<int> scores;

    for(const auto& geno : randPOP){
        scores.push_back(caculateFitness(geno, matrix));
    }

    GENOME TPC = tournamentSelection(randPOP, scores, tournament_Size);

    std::cout << "\n" << "fitness chosen: " << caculateFitness(TPC, matrix);

    return 0;
}