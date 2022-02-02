#ifndef __DARWIN__
#define __DARWIN__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
//#include <GL/glut.h>
#include <stdbool.h>


typedef struct{
    bool gen[20];
}chromosome;

void setupAG(int new_numberPopulation, float new_TaxMutation, float new_taxPredation);
void startPopulation();
void evolve();
void freedom();
void printBestIndividuals();
void printGenerationInfo();
void mutationController();

#endif