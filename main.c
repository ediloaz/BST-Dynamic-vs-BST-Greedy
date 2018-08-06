#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "Arbol.h"
#include "latex.h"
#include "Key.h"
#include "TablaA.h"
#include "ModoEjemplo.h"
#include "ModoExperimento.h"


void init(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "XE:")) != -1)
    {
        if('X'==opt){
            ModoEjemplo();
            printf("\nPress Enter to close the program.");
            getchar();
            break;
        }
        else if(('E'==opt)&(optarg!=NULL)){
            if (optarg[0] == '='){
                optarg[0] = '0';
                if (isdigit(optarg[1]) != 0){
                    int N = atoi(optarg);
                    if (N!=0){
                        ModoExperimento(N);
                        printf("\nPress Enter to close the program.");
                        getchar();
                    }else{
                        printf("\nWhy you put zero? Bye.\n");
                    }
                }else{
                    printf("\nInvalid parameter.\n");
                }
                break;
            }else if (optarg[0] == 'D'){
                optarg[0] = '0';
                optarg[1] = '0';
                if (isdigit(optarg[1]) != 0){
                    int N = atoi(optarg);
                    if (N!=0){
                        ModoExperimentoDocumentado(N);
                        printf("\nPress Enter to close the program.");
                        getchar();
                    }else{
                        printf("\nWhy do you put zero? Bye.\n");
                    }
                }else{
                    printf("\nInvalid parameter.\n");
                }
                break;
            }
            
        }
        else{
            printf("\nInvalid parameter\n");
        }
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));                                          // Cambiamos la semilla de la función rand() cada vez que iniciamos el programa.
    init(argc,argv);
    return (EXIT_SUCCESS);
}
