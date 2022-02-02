#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
//#include <GL/glut.h>
#include <stdbool.h>

#include "darwin.h"
//#include "draw.h"

#define MaxWeightBag 500
#define numberItems 20

bool finesse = 1;

int numberPopulation;

float TaxMutation;
float defaultTaxMutation;
float taxPredation;

int mode;

int generation;

char* evolutionMode;

chromosome* individuals = NULL;

chromosome Bestindividuals[10];

float ValueItems[numberItems] = {10.5, 30.2, 72.0, 7.5, 15.7, 
                                182.75, 21.06, 18, 105, 88,
                                2, 0.5, 50, 31.3, 24, 
                                45, 99, 137.02, 77, 20};

float WeightItems[numberItems] = {10.5, 30.2, 72.0, 7.5, 15,
                                  182.75, 1, 90, 18, 10,
                                  100, 0.5, 50, 33, 70,
                                  20, 3, 120, 9, 50};

float ModFloat(float x){
    return (x<0)?-x:x;
}

void setupAG(int new_numberPopulation, float new_TaxMutation, float new_taxPredation){
    numberPopulation = new_numberPopulation;
    TaxMutation = new_TaxMutation;
    defaultTaxMutation = new_TaxMutation;
    taxPredation = new_taxPredation;
    evolutionMode = (char*)malloc(sizeof(char)*20);
    strcpy(evolutionMode,"Elitismo");
    mode = 1;
    generation = 0;
    for(int i = 0; i < 10 ; i++){
        for(int j = 0; j < numberItems ; j++){
            Bestindividuals[i].gen[j] = false;
        }
        
    }
}

float getFitness(chromosome individual){
    float value = 0;
    float weight = 0; 
    for(int i = 0; i < numberItems ; i++){
        if(individual.gen[i]){
            value += ValueItems[i];
            weight += WeightItems[i];
        }
    }
    //printf("Peso %f \n", weight);
    if(weight <= MaxWeightBag)
        return value;

    return -1.0;
}


int getIndividualBiggerFitness(){
    int individualBiggerFitness = 0;
    float biggerFitness = 0.0;
    float tempFitness = 0;
    for(int i = 0; i < numberPopulation ; i++){
        tempFitness = getFitness(individuals[i]);
        if(tempFitness > biggerFitness){
            individualBiggerFitness = i;
            biggerFitness = tempFitness;
        }
    }

    return individualBiggerFitness;
}

void startPopulation(){
    free(individuals);
    individuals = (chromosome*) malloc(sizeof(chromosome)*numberPopulation);
    

    for(int i = 0; i < numberPopulation ; i++){
        for(int j = 0; j < numberItems ; j++){
            //individuals[i].x = minRange_x + ((float)rand()/(float)(RAND_MAX))*(maxRange_x-minRange_x);
            individuals[i].gen[j] = ((bool) rand() % 2); // randbool = rand() & 1;
        }   
    }
    generation = 0;
    int bestIndividual = getIndividualBiggerFitness();
    //printf("Melhor individuo %d", bestIndividual);
    for(int i = 0; i < numberItems; i++){
        Bestindividuals[0].gen[i] = individuals[bestIndividual].gen[i];
    }

}

/*
NumItens: 30;
CapacidadeDoSaco: 20;
Valor[30]; [10, 3,]
Peso[30]: [5, 1]

*/


void bubble_sort_mod(chromosome* individuals){
    chromosome temp;
    for(int i = 0; i < numberPopulation; i++){
        for(int j = i+1 ; j < numberPopulation; j++){
            if(getFitness(individuals[i]) > getFitness(individuals[j])){
                temp = individuals[i];
                individuals[i] = individuals[j];
                individuals[j] = temp;
            }
        }
    }
}

void torneioDe2(chromosome* individuals){
    chromosome* tempPopulation = (chromosome*)malloc(sizeof(chromosome)*numberPopulation);
    int individual1, individual2;

    int individualBiggerFitness = getIndividualBiggerFitness();

    for(int i = 0 ; i < numberPopulation ; i++){

        if(i == individualBiggerFitness){
            printf("posição do melhor: %d, valor do melhor %f\n", i, getFitness(individuals[individualBiggerFitness]));
            tempPopulation[i] = individuals[individualBiggerFitness]; 
        }
        else{
            individual1 = rand()%numberPopulation;
            individual2 = rand()%numberPopulation;
            while(individual1 == individual2){
                individual2 = rand()%numberPopulation;
            }
            
            int father;
            if(getFitness(individuals[individual1]) > getFitness(individuals[individual2])){
                father = individual1;
            } else {
                father = individual2;
            }
            /////
            individual1 = rand()%numberPopulation;
            individual2 = rand()%numberPopulation;
            while(individual1 == individual2){
                individual2 = rand()%numberPopulation;
            }
            
            int mother;
            if(getFitness(individuals[individual1]) > getFitness(individuals[individual2])){
                mother = individual1;
            } else {
                mother = individual2;
            }

            //novo individuo recebe metade dos genes do pai
            for (int j = 0; j < numberItems/2; j++) 
            {
                tempPopulation[i].gen[j] = individuals[father].gen[j];
            }
            //novo individuo recebe metade dos genes da mae
            for (int j = numberItems/2; j < numberItems; j++) 
            {
                tempPopulation[i].gen[j] = individuals[mother].gen[j];
            }

            
            //sorteia a mutacao dos genes
            for (int j = 0; j < numberItems; j++)
            {
                if(rand()%100 < TaxMutation){
                    tempPopulation[i].gen[j] = !(tempPopulation[i].gen[j]);
                }
            }
        }
        
    }

   
    //free(individuals);

    
    for (int i = 0; i < numberPopulation; i++)
    {
        individuals[i] = tempPopulation[i];
    }
    
    bubble_sort_mod(individuals);
   
    free(tempPopulation);
    tempPopulation = NULL;

    /*
    free(individuals);

    individuals = tempPopulation;

    bubble_sort_mod(individuals);
    */
}

//void elitismo(chromosome* individuals);
//void roleta(chromosome* individuals);

float getPopulationAverage(){
    float average = 0;
    for (int i = 0 ; i < numberPopulation ; i++){
        average += getFitness(individuals[i]);
    }
    average /= numberPopulation;
    return average;
}

void predation(){
    chromosome *prey;
    for(int i = 0; i < numberPopulation*taxPredation; i++){
        prey = &individuals[i];
        for(int j = 0; j < numberItems ; j++){
                //individuals[i].x = minRange_x + ((float)rand()/(float)(RAND_MAX))*(maxRange_x-minRange_x);
                prey->gen[j] = ((bool) rand() % 2); // randbool = rand() & 1;
        }
    }    
}

void evolve(){
    torneioDe2(individuals);
    predation();
    generation++;

    chromosome temp;
    for(int i = 0; i < 9 ; i++){
        temp = Bestindividuals[i];
        Bestindividuals[i] = Bestindividuals[i+1];
        Bestindividuals[i+1] = temp;
    }
    Bestindividuals[9] = individuals[getIndividualBiggerFitness()];

    mutationController();
    
}

void mutationController(){
    float fitnessBestIndividual; 
    fitnessBestIndividual = getFitness(Bestindividuals[0]);

    if(finesse){
        if(ModFloat(getFitness(Bestindividuals[9]) - getFitness(Bestindividuals[5])) < 0.001 && fitnessBestIndividual > 0){
            TaxMutation *= 0.5;
        } else {
            TaxMutation = defaultTaxMutation;
        }

        if(TaxMutation < 0.01){
            TaxMutation = defaultTaxMutation;
            finesse = false;
        }  
    }
    else{
        if(ModFloat(getFitness(Bestindividuals[9]) - getFitness(Bestindividuals[5])) < 0.001){
            TaxMutation *= 1.2;
        } else {
            TaxMutation = defaultTaxMutation;
        }

        if(TaxMutation > 50){
            TaxMutation = defaultTaxMutation;
            finesse = true;
        }
    }
}

void printGenerationInfo(){

    printf("Geração %d \n", generation);
    printf("Taxa de Mutação %f \n", TaxMutation);
    //printf("----------------------População---------------");
    // for(int i=0; i<numberPopulation; i++){
    //     printf("Fitness %f \n", getFitness(individuals[i]));
    // }
    //printf("----------------------População---------------");
    printf("Fitness do Melhor Indivíduo %f \n", getFitness(Bestindividuals[9]));
    printf("Media da População %f \n", getPopulationAverage());
    printf("-------------------------------------- \n");
}

void printBestIndividuals(){
    
    for(int i=0; i<10; i++){
        printf("Melhor Fitness, Posição: %d         Valor: %f\n", i, getFitness(Bestindividuals[i]));
    }
}

// void freedom(){
//     free(individuals);
//     individuals = NULL;
// }
