#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "darwin.h"
#define SIZE_POPULATION 100
#define MUTATION_TAX 2 //taxa de mutacao em porcentagem

int main(int argc, char *argv[]){

    srand(time(NULL)); //seed para reproducao dos resultados

    setupAG(SIZE_POPULATION, MUTATION_TAX, 0.05);
    startPopulation();

    char tecla = 'a';
    int generationJump = 1500;
    //printf("Opções Disponiveis: \n");
    //printf("Enter - Avança uma Geração \n");
    //printf("d - Avança 10 gerações\n");
    //printf("f - Avança 100 gerações\n");
    //tecla = getchar();
    //if(tecla == 'd') generationJump = 9;
    //if(tecla == 'f') generationJump = 99;
    //if(tecla == 'p') generationJump = 999;
    for(int i=0; i<generationJump; i++){
        evolve();
        printGenerationInfo();
    }


    return 0;
}