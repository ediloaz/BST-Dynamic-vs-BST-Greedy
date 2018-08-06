/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TablaA.h
 * Author: edisson
 *
 * Created on 8 de abril de 2018, 10:10 AM
 */

#ifndef TABLAA_H
#define TABLAA_H

#include "Key.h"
#include "Arbol.h"
#include "latex.h"

struct st_tabla_A;
struct st_tabla_A{
    int N;
    double celdas[100][100];
} tabla_A;

struct st_tabla_R;
struct st_tabla_R{
    int N;
    int celdas[100][100];
} tabla_R, tabla_R_respaldo;

double costo_promedio_greedy, costo_promedio_pd;

void Latex_PrintTablas();
void Latex_PrintTablaA();
void Latex_PrintTablaR();
void Latex_PrintTablaR_Greedy();
void Latex_Tree(nodo * n);

void ResetearTablaR(){
    tabla_R_respaldo.N = tabla_R.N;
    for (int m=0 ; m<101 ; m++){
        for (int n=0 ; n<101 ; n++){
            tabla_R.celdas[m][n] = 0;
        }
    }
}

void CopiarTablaR(){
    tabla_R_respaldo.N = tabla_R.N;
    for (int m=0 ; m<101 ; m++){
        for (int n=0 ; n<101 ; n++){
            tabla_R_respaldo.celdas[m][n] = tabla_R.celdas[m][n];
        }
    }
}

// Las celdas diagonales con 0s y las Key encima de ésta
void InicializarTablas(int N){
    for (int i = 0 ; i < tabla_A.N ; i++){
        tabla_A.celdas[i][i] = 0;
        tabla_R.celdas[i][i] = 0;
        tabla_A.celdas[i][i+1] = keys[i].probabilidad;
        tabla_R.celdas[i][i+1] = i+1;
    }
    tabla_A.celdas[tabla_A.N][tabla_A.N] = 0;
}


// Las celdas diagonales con 0s y las Key encima de ésta
void InicializarTablaA_ModoEjemplo(int N){
    for (int i = 0 ; i < tabla_A.N ; i++){
        tabla_A.celdas[i][i] = 0;
        tabla_A.celdas[i][i+1] = keys_modo_ejemplo[i].probabilidad;
    }
    tabla_A.celdas[tabla_A.N][tabla_A.N] = 0;
}

// Las celdas diagonales con 0s y las i encima de ésta
void InicializarTablaR(int N){
    for (int i = 0 ; i < tabla_R.N ; i++){
        tabla_R.celdas[i][i] = 0;
        tabla_R.celdas[i][i+1] = i+1;
    }
    tabla_R.celdas[tabla_R.N][tabla_R.N] = 0;
}

void CrearTablas(){
    int N = GetCantidadKeys();
    tabla_A.N = N;
    tabla_R.N = N;
    InicializarTablas(N);
}

void CrearTablas_ModoEjemplo(){
    int N = 6;
    tabla_A.N = N;
    tabla_R.N = N;
    InicializarTablas(N);
}

void CrearTablas_ModoExperimento(){
    int N = 1 + (rand() %(100));
    tabla_A.N = N;
    tabla_R.N = N;
    InicializarTablas(N);
}

void Latex_CalcularCelda_ModoExperimento(int i, int j){
    int k_ganador = -1;
    double min = 9999.0;
    double suma_de_ks = 0.0;
    double actual;
    for (int k=i ; k<j ; k++){
        actual = tabla_A.celdas[i][k] + tabla_A.celdas[k+1][j];
        if (actual < min){
            min = actual;
            k_ganador = k;
        }
        suma_de_ks += keys[k].probabilidad;
    }
    tabla_A.celdas[i][j] = min + (double)suma_de_ks;
    tabla_R.celdas[i][j] = k_ganador+1;
}

void Latex_CalcularCelda(int i, int j){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    
    int k_ganador = -1;
    double min = 9999.0;
    double suma_de_ks = 0.0;
    double actual;
    fputs(" \n", tex_file);
    fprintf(tex_file, "Calculation for the cell \\textbf{[%i][%i]}: \\\\ \n", i+1, j);
    for (int k=i ; k<j ; k++){
        actual = tabla_A.celdas[i][k] + tabla_A.celdas[k+1][j];
        fprintf(tex_file, "\\tab A[%i][%i] + A[%i][%i] = %.3lf + %.3lf = %.3lf", i+1,k-1+1, k+1+1,j, tabla_A.celdas[i][k], tabla_A.celdas[k+1][j], actual);
        if (actual < min){
            fputs(" *min*", tex_file);
            min = actual;
            k_ganador = k;
        }
        suma_de_ks += keys[k].probabilidad;
        fputs("\\\\ \n", tex_file);
    }
    fprintf(tex_file, "\\minitab K winner: %i \\\\ \n",k_ganador+1);
    fprintf(tex_file, "\\minitab Selected: [%i][%i] + [%i][%i] + Ks = \\textbf{%lf} \\\\ \n",i+1,k_ganador-1+1,k_ganador+1+1,j,min+(double)suma_de_ks);
    tabla_A.celdas[i][j] = min + (double)suma_de_ks;
    tabla_R.celdas[i][j] = k_ganador+1;
    
    fclose(tex_file);
}

void CalcularCelda(int i, int j){
    int k_ganador = -1;
    double min = 9999.0;
    double suma_de_ks = 0.0;
    double actual;
    printf("\n");
    printf("\tCalculated cells: \n");
    for (int k=i ; k<j ; k++){
        printf("\t\tWith the value:  [%i][%i](%lf) y [%i][%i](%lf) ", i+1,k-1+1,tabla_A.celdas[i][k], k+1+1,j,tabla_A.celdas[k+1][j]);
        actual = tabla_A.celdas[i][k] + tabla_A.celdas[k+1][j];
        if (actual < min){
            printf(" *");
            min = actual;
            k_ganador = k;
        }
        suma_de_ks += keys[k].probabilidad;
        printf("\n");
    }
    printf("\tK winner: %i \n",k_ganador+1);
    printf("\tMinimum: %lf \n",min);
    printf("\t\tOf the cells: [%i][%i] y [%i][%i] \n",i+1,k_ganador-1+1,k_ganador+1+1,j);
    printf("\t\tWith the value:  [%lf] y [%lf] \n", tabla_A.celdas[i][k_ganador], tabla_A.celdas[k_ganador+1+1][j]);
    tabla_A.celdas[i][j] = min + (double)suma_de_ks;
    tabla_R.celdas[i][j] = k_ganador+1;
}

void Latex_CalcularTablaA(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("Now proceed to complete Tabla A and R, calculating and choosing the value of each cell of said tables. \\\\ \n",tex_file);
    fclose(tex_file);
    int N = tabla_A.N;
    int i_temp;
    for (int i = N-2 ; i>=0 ; i--){          // Sería -1 si las filas inician en 0
        i_temp = i;
        for (int j=N ; i>=0 ; i-- & j--){
//            fprintf(tex_file, "\n Calculating the cell [%i][%i] -> ",i+1,j);
            Latex_CalcularCelda(i, j);
        }
        i = i_temp;
        fputs("\n", tex_file);
    }
}


void Latex_CalcularTablaA_ModoExperimento(){
    int N = tabla_A.N;
    int i_temp;
    for (int i = N-2 ; i>=0 ; i--){          // Sería -1 si las filas inician en 0
        i_temp = i;
        for (int j=N ; i>=0 ; i-- & j--){
            Latex_CalcularCelda_ModoExperimento(i, j);
        }
        i = i_temp;
    }
}

void CalcularTablaA(){
    printf("\n + Calculating the cells in the tables \n");
    int N = tabla_A.N;
    int i_temp;
    for (int i = N-2 ; i>=0 ; i--){          // Sería -1 si las filas inician en 0
        i_temp = i;
        for (int j=N ; i>=0 ; i-- & j--){
            printf("\n Calculating the cell [%i][%i] -> ",i+1,j);
            CalcularCelda(i, j);
        }
        i = i_temp;
        printf("\n");
    }
}

void CrearArbolTablaR_ModoExperimento(){
    nodo * root = NULL;
    CopiarKeysTemp();
    int i, j, N, nodo_a_agregar;
    N = GetCantidadKeys();
    for (int nodos_procesados=0 ; nodos_procesados<N ; nodos_procesados++){
        i = -1;
        j = -1;
        for (int n=0 ; j==-1 ; n++){
            if (keys_temp[n].probabilidad==-1.0 && i!=-1){
                j = n-1;
            }else if(keys_temp[n].probabilidad==-1.0 && i==-1){
                // ignora
            }else if(keys_temp[n].probabilidad!=-1.0 && i==-1){
                i = n;
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else if(keys_temp[n].probabilidad!=-1.0 && i!=-1){
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else{
                printf("NO ENCONTRÓ KEYS = -1 NI I=-1 ----");
            }
        }
        nodo_a_agregar = tabla_R.celdas[i][j+1];
        InsertarNodo(&root, NuevoNodo(nodo_a_agregar));
        keys_temp[nodo_a_agregar-1].probabilidad = -1.0;
    }
}


void CrearArbolTablaR_ModoExperimentoDocumentado(){
    nodo * root = NULL;
    CopiarKeysTemp();
    int i, j, N, nodo_a_agregar;
    N = GetCantidadKeys();
    for (int nodos_procesados=0 ; nodos_procesados<N ; nodos_procesados++){
        i = -1;
        j = -1;
        for (int n=0 ; j==-1 ; n++){
            if (keys_temp[n].probabilidad==-1.0 && i!=-1){
                j = n-1;
            }else if(keys_temp[n].probabilidad==-1.0 && i==-1){
                // ignora
            }else if(keys_temp[n].probabilidad!=-1.0 && i==-1){
                i = n;
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else if(keys_temp[n].probabilidad!=-1.0 && i!=-1){
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else{
                printf("NO ENCONTRÓ KEYS = -1 NI I=-1 ----");
            }
        }
        nodo_a_agregar = tabla_R.celdas[i][j+1];
        InsertarNodo(&root, NuevoNodo(nodo_a_agregar));
        keys_temp[nodo_a_agregar-1].probabilidad = -1.0;
    }
    if (tabla_R.N <11){
         FILE * tex_file;
        tex_file = fopen(NAME_OF_TEX_FILE, "a+");
        fprintf(tex_file, "\\subsubsection*{Solution of Dynamic Algorithm with %i keys}", tabla_R.N );
        fclose(tex_file);
        Latex_PrintTablaR_Greedy();
        Latex_Tree(root);        
    }
}

int MayorProbabilidad(int i, int j){
    double mayor = 0;
    int    i_mayor = -1;
    for (i ; i<j+1 ; i++){
        if(keys_temp[i].probabilidad>mayor){
            mayor = keys_temp[i].probabilidad;
            i_mayor = i;
        }
    }
    return i_mayor;
}

void CrearArbol_Greedy_Experimento(){
    nodo * root = NULL;
    CopiarKeysTemp();
    int i, j, N, nodo_a_agregar;
    N = GetCantidadKeys();
//    printf("Cantidad de keys: %i\n", N);
    for (int nodos_procesados=0 ; nodos_procesados<N ; nodos_procesados++){
//        printf("Procesando el nodo: %i \n", nodos_procesados);
        i = -1;
        j = -1;
        for (int n=0 ; j==-1 ; n++){                                // Encuentra el i y el j de las keys que hacen falta
//            printf("\tLeyendo key[%i] con peso %lf \n", n+1, keys_temp[n].probabilidad);
            if (keys_temp[n].probabilidad==-1.0 && i!=-1){
                j = n-1;
            }else if(keys_temp[n].probabilidad==-1.0 && i==-1){
                // ignora
            }else if(keys_temp[n].probabilidad!=-1.0 && i==-1){
                i = n;
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else if(keys_temp[n].probabilidad!=-1.0 && i!=-1){
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else{
                printf("NO ENCONTRÓ KEYS = -1 NI I=-1 ----");
            }
        }
//        printf("Árbol desde i=%i hasta j=%i\n",i+1,j+1);
        
        nodo_a_agregar = MayorProbabilidad(i,j)+1;
        tabla_R.celdas[i][j+1] = nodo_a_agregar;
//        AgregarNodo(keys_temp[nodo_a_agregar]);
        InsertarNodo(&root, NuevoNodo(nodo_a_agregar));
//        printf("Se escogió el nodo %i con probabilidad: %lf \n",nodo_a_agregar,keys_temp[nodo_a_agregar-1].probabilidad);
        keys_temp[nodo_a_agregar-1].probabilidad = -1.0;
    }
}
void CrearArbol_Greedy_ExperimentoDocumentado(){
    nodo * root = NULL;
    CopiarKeysTemp();
    int i, j, N, nodo_a_agregar;
    N = GetCantidadKeys();
//    printf("Cantidad de keys: %i\n", N);
    for (int nodos_procesados=0 ; nodos_procesados<N ; nodos_procesados++){
//        printf("Procesando el nodo: %i \n", nodos_procesados);
        i = -1;
        j = -1;
        for (int n=0 ; j==-1 ; n++){                                // Encuentra el i y el j de las keys que hacen falta
//            printf("\tLeyendo key[%i] con peso %lf \n", n+1, keys_temp[n].probabilidad);
            if (keys_temp[n].probabilidad==-1.0 && i!=-1){
                j = n-1;
            }else if(keys_temp[n].probabilidad==-1.0 && i==-1){
                // ignora
            }else if(keys_temp[n].probabilidad!=-1.0 && i==-1){
                i = n;
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else if(keys_temp[n].probabilidad!=-1.0 && i!=-1){
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else{
                printf("NO ENCONTRÓ KEYS = -1 NI I=-1 ----");
            }
        }
//        printf("Árbol desde i=%i hasta j=%i\n",i+1,j+1);
        
        nodo_a_agregar = MayorProbabilidad(i,j)+1;
        tabla_R.celdas[i][j+1] = nodo_a_agregar;
//        AgregarNodo(keys_temp[nodo_a_agregar]);
        InsertarNodo(&root, NuevoNodo(nodo_a_agregar));
//        printf("Se escogió el nodo %i con probabilidad: %lf \n",nodo_a_agregar,keys_temp[nodo_a_agregar-1].probabilidad);
        keys_temp[nodo_a_agregar-1].probabilidad = -1.0;
    }
    if (tabla_R.N <11){
         FILE * tex_file;
        tex_file = fopen(NAME_OF_TEX_FILE, "a+");
        fprintf(tex_file, "\\subsubsection*{Solution of Greedy Algorithm with %i keys}", tabla_R.N );
        fclose(tex_file);
        Latex_PrintTablaR_Greedy();
        Latex_Tree(root);        
    }

}


void CrearArbol_Greedy(){
    nodo * root = NULL;
    CopiarKeysTemp();
    int i, j, N, nodo_a_agregar;
    N = GetCantidadKeys();
//    printf("Cantidad de keys: %i\n", N);
    for (int nodos_procesados=0 ; nodos_procesados<N ; nodos_procesados++){
//        printf("Procesando el nodo: %i \n", nodos_procesados);
        i = -1;
        j = -1;
        for (int n=0 ; j==-1 ; n++){                                // Encuentra el i y el j de las keys que hacen falta
//            printf("\tLeyendo key[%i] con peso %lf \n", n+1, keys_temp[n].probabilidad);
            if (keys_temp[n].probabilidad==-1.0 && i!=-1){
                j = n-1;
            }else if(keys_temp[n].probabilidad==-1.0 && i==-1){
                // ignora
            }else if(keys_temp[n].probabilidad!=-1.0 && i==-1){
                i = n;
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else if(keys_temp[n].probabilidad!=-1.0 && i!=-1){
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else{
                printf("NO ENCONTRÓ KEYS = -1 NI I=-1 ----");
            }
        }
//        printf("Árbol desde i=%i hasta j=%i\n",i+1,j+1);
        
        nodo_a_agregar = MayorProbabilidad(i,j)+1;
        tabla_R.celdas[i][j+1] = nodo_a_agregar;
//        AgregarNodo(keys_temp[nodo_a_agregar]);
        InsertarNodo(&root, NuevoNodo(nodo_a_agregar));
//        printf("Se escogió el nodo %i con probabilidad: %lf \n",nodo_a_agregar,keys_temp[nodo_a_agregar-1].probabilidad);
        keys_temp[nodo_a_agregar-1].probabilidad = -1.0;
    }
    Latex_PrintTablaR_Greedy();
    Latex_Tree(root);
}

void CrearArbolTablaR(){
    nodo * root = NULL;
    CopiarKeysTemp();
    int i, j, N, nodo_a_agregar;
    N = GetCantidadKeys();
//    printf("Cantidad de keys: %i\n", N);
    for (int nodos_procesados=0 ; nodos_procesados<N ; nodos_procesados++){
//        printf("Procesando el nodo: %i \n", nodos_procesados);
        i = -1;
        j = -1;
        for (int n=0 ; j==-1 ; n++){                                // Encuentra el i y el j de las keys que hacen falta
//            printf("\tLeyendo key[%i] con peso %lf \n", n+1, keys_temp[n].probabilidad);
            if (keys_temp[n].probabilidad==-1.0 && i!=-1){
                j = n-1;
            }else if(keys_temp[n].probabilidad==-1.0 && i==-1){
                // ignora
            }else if(keys_temp[n].probabilidad!=-1.0 && i==-1){
                i = n;
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else if(keys_temp[n].probabilidad!=-1.0 && i!=-1){
                if (keys_temp[n+1].probabilidad==-99.0 || keys_temp[n+1].probabilidad==-1.0){
                    j = n;
                }
            }else{
                printf("NO ENCONTRÓ KEYS = -1 NI I=-1 ----");
            }
        }
//        printf("Árbol desde i=%i hasta j=%i\n",i+1,j+1);
        nodo_a_agregar = tabla_R.celdas[i][j+1];
//        AgregarNodo(keys_temp[nodo_a_agregar]);
        InsertarNodo(&root, NuevoNodo(nodo_a_agregar));
//        printf("Se escogió el nodo %i con probabilidad: %lf \n",nodo_a_agregar,keys_temp[nodo_a_agregar-1].probabilidad);
        keys_temp[nodo_a_agregar-1].probabilidad = -1.0;
    }
    Latex_Tree(root);
}

void Latex_PrintTablas(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n After the calculation process, the following tables are obtained: \n", tex_file);
    fclose(tex_file);
    
    Latex_PrintTablaA();
    Latex_PrintTablaR();
}

void Latex_PrintTablaA(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\\begin{center} \n", tex_file);
    fputs("\\textbf{Tabla A} \\\\ \n", tex_file);
    fputs("\\begin{tabular}{|", tex_file);
    for(int i=0 ; i<tabla_A.N+2 ; i++){    
        fputs("c|", tex_file);
    }
    fputs("}\n", tex_file);
    fputs("\\hline ", tex_file);
    fputs("\\textbf{•} ", tex_file);
    for(int i=0 ; i<tabla_A.N+1 ; i++){     // Imprime las columnas 0-N
        fprintf(tex_file, "& \\textbf{%i}", i);
    }
    fputs("\\\\ ", tex_file);
    fputs("\\hline \n", tex_file);
    for(int i=0 ; i<tabla_A.N+1; i++){    
        fprintf(tex_file, "\\textbf{%i} " , i+1);
        for(int j=0 ; j<tabla_A.N+1 ; j++){
            if (i>j){
                fputs("&  ", tex_file);
            }else{
            fprintf(tex_file, "& %.3f " , tabla_A.celdas[i][j]);
            }
        }
        fputs("\\\\ \n", tex_file);
        fputs("\\hline \n", tex_file);
    }
    fputs("\\end{tabular} \n", tex_file);
    fputs("\\end{center} \n", tex_file);
    fclose(tex_file);
}

void Latex_PrintTablaR_respaldo(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\\begin{center} \n", tex_file);
    fputs("\\textbf{Tabla R} \\\\ \n", tex_file);
    fputs("\\begin{tabular}{|", tex_file);
    for(int i=0 ; i<tabla_R_respaldo.N+2 ; i++){    
        fputs("c|", tex_file);
    }
    fputs("}\n", tex_file);
    fputs("\\hline ", tex_file);
    fputs("\\textbf{•} ", tex_file);
    for(int i=0 ; i<tabla_R_respaldo.N+1 ; i++){     // Imprime las columnas 0-N
        fprintf(tex_file, "& \\textbf{%i}", i);
    }
    fputs("\\\\ ", tex_file);
    fputs("\\hline \n", tex_file);
    for(int i=0 ; i<tabla_R_respaldo.N+1; i++){    
        fprintf(tex_file, "\\textbf{%i} " , i+1);
        for(int j=0 ; j<tabla_R_respaldo.N+1 ; j++){
            if (i>j){
                fputs("&  ", tex_file);
            }else{
            fprintf(tex_file, "& %i " , tabla_R_respaldo.celdas[i][j]);
            }
        }
        fputs("\\\\ \n", tex_file);
        fputs("\\hline \n", tex_file);
    }
    fputs("\\end{tabular} \n", tex_file);
    fputs("\\end{center} \n", tex_file);
    fclose(tex_file);
}

void Latex_PrintTablaR(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\\begin{center} \n", tex_file);
    fputs("\\textbf{Tabla R} \\\\ \n", tex_file);
    fputs("\\begin{tabular}{|", tex_file);
    for(int i=0 ; i<tabla_R.N+2 ; i++){    
        fputs("c|", tex_file);
    }
    fputs("}\n", tex_file);
    fputs("\\hline ", tex_file);
    fputs("\\textbf{•} ", tex_file);
    for(int i=0 ; i<tabla_R.N+1 ; i++){     // Imprime las columnas 0-N
        fprintf(tex_file, "& \\textbf{%i}", i);
    }
    fputs("\\\\ ", tex_file);
    fputs("\\hline \n", tex_file);
    for(int i=0 ; i<tabla_R.N+1; i++){    
        fprintf(tex_file, "\\textbf{%i} " , i+1);
        for(int j=0 ; j<tabla_R.N+1 ; j++){
            if (i>j){
                fputs("&  ", tex_file);
            }else{
            fprintf(tex_file, "& %i " , tabla_R.celdas[i][j]);
            }
        }
        fputs("\\\\ \n", tex_file);
        fputs("\\hline \n", tex_file);
    }
    fputs("\\end{tabular} \n", tex_file);
    fputs("\\end{center} \n", tex_file);
    fclose(tex_file);
}


void Latex_PrintTablaR_Greedy(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\\begin{center} \n", tex_file);
    fputs("\\textbf{Tabla R} \\\\ \n", tex_file);
    fputs("\\begin{tabular}{|", tex_file);
    for(int i=0 ; i<tabla_R.N+2 ; i++){    
        fputs("c|", tex_file);
    }
    fputs("}\n", tex_file);
    fputs("\\hline ", tex_file);
    fputs("\\textbf{•} ", tex_file);
    for(int i=0 ; i<tabla_R.N+1 ; i++){     // Imprime las columnas 0-N
        fprintf(tex_file, "& \\textbf{%i}", i);
    }
    fputs("\\\\ ", tex_file);
    fputs("\\hline \n", tex_file);
    for(int i=0 ; i<tabla_R.N+1; i++){    
        fprintf(tex_file, "\\textbf{%i} " , i+1);
        for(int j=0 ; j<tabla_R.N+1 ; j++){
            if (i>j){
                fputs("&  ", tex_file);
            }else if (i<j && tabla_R.celdas[i][j]==0.0){
                fputs("&  ", tex_file);
            }else if (i==j || i==j-1){
                fprintf(tex_file, "& %i " , tabla_R.celdas[i][j]);
            }else{
                fprintf(tex_file, "& \\textbf{%i} " , tabla_R.celdas[i][j]);
            }
        }
        fputs("\\\\ \n", tex_file);
        fputs("\\hline \n", tex_file);
    }
    fputs("\\end{tabular} \n", tex_file);
    fputs("\\end{center} \n", tex_file);
    fclose(tex_file);
}

void PrintTablaA(){
    printf("\nTabla R:");
    printf("\t");
    for(int j=0 ; j<tabla_A.N+1 ; j++){     // Imprime las columnas
        printf("\033[1m\033[30m[%i]\t\t", j);
    }
    printf("\n");
    for(int i=0 ; i<tabla_A.N+1; i++){    
        printf("\033[1m\033[30m[%i]\t\033[0m", i+1);
        for(int j=0 ; j<tabla_A.N+1 ; j++){
            printf("(%f)\t" , tabla_A.celdas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PrintTablaR(){
    printf("\nTabla R:\n");
    printf("\t");
    for(int j=0 ; j<tabla_R.N+1 ; j++){     // Imprime las columnas
        printf("\033[1m\033[30m[%i]\t", j);
    }
    printf("\n");
    for(int i=0 ; i<tabla_R.N+1; i++){    
        printf("\033[1m\033[30m[%i]\t\033[0m", i+1);
        for(int j=0 ; j<tabla_R.N+1 ; j++){
            printf("(%i)\t" , tabla_R.celdas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


#endif /* TABLAA_H */

