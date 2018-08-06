#ifndef TABLAPROGRAMACIONDINAMICA_H
#define TABLAPROGRAMACIONDINAMICA_H
#include "Key.h"

struct struct_tabla_PD;
struct struct_tabla_PD{
    int N;
    struct struct_celda_tabla_PD * celdas_tabla_PD;
}tabla_PsD;

struct struct_celda_tabla_PD;
struct struct_celda_tabla_PD{
    float A;
    int   R;
}celdas_tabla_PD[100][100];


struct struct_celda_tabla_PD * CrearCeldasPD(){
    for (int i = 0 ; i < tabla_PD.N ; i++){
        celdas_tabla_PD[i][i].A = 0;
        celdas_tabla_PD[i][i].R = 0;
        printf("%i ",keys_modo_ejemplo[i].peso);
        celdas_tabla_PD[i][i+1].A = keys_modo_ejemplo[i].probabilidad;
        celdas_tabla_PD[i][i+1].R = i+1;
    }
    celdas_tabla_PD[tabla_PD.N][tabla_PD.N].A = 0;
    celdas_tabla_PD[tabla_PD.N][tabla_PD.N].R = 0;
    return celdas_tabla_PD;
}

// Recordar que:
//  Las filas comiezan desde 1 y llegan hasta N+1
//  Las columnas comiezan desde 0 y llegan hasta N
//  El tamaño de la tabla es de N+1xN+1
void CrearTablaPD_ModoEjemplo(){
    tabla_PD.N = 6;
    tabla_PD.celdas_tabla_PD = malloc(101);
    tabla_PD.celdas_tabla_PD = CrearCeldasPD();
}


void CrearTablaPD_ModoExperimento(){
    tabla_PD.N = 1 + (rand() %(100));
    tabla_PD.celdas_tabla_PD = malloc(101);
    tabla_PD.celdas_tabla_PD = CrearCeldasPD();
}

void PrintTablaPD(){
    for(int i=0 ; i<tabla_PD.N ; i++){    
        for(int j=0 ; j<tabla_PD.N ; j++){
            printf("[%i][%i] \t|" , i,j);
            printf("R: %f \n" , celdas_tabla_PD[i][j].A);
        }
    }
}
//
//void LlenarTablaPD_ModoExperimento(){
//    for (int i = 0 ; i < tabla_PD.N ; i++){
//        tabla_PD.celdas_tabla_PD[i][i].A = 0;
//        tabla_PD.celdas_tabla_PD[i][i].R = 0;
//        tabla_PD.celdas_tabla_PD[i][i+1].A = keys_modo_experimento[i].probabilidad;
//        tabla_PD.celdas_tabla_PD[i][i+1].R = i+1;
//    }
//    tabla_PD.celdas_tabla_PD[tabla_PD.N][tabla_PD.N].A = 0;
//    tabla_PD.celdas_tabla_PD[tabla_PD.N][tabla_PD.N].R = 0;
//}



#endif /* TABLAPROGRAMACIONDINAMICA_H */

