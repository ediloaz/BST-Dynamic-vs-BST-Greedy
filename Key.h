#ifndef KEY_H
#define KEY_H

#include "latex.h"

struct struct_key;
struct struct_key{
    char caracter;   // Valor 
    int peso;           // Peso: [1,1000]
    double probabilidad;   // Probabilidad: [0.0,1.0]
} keys_temp[100], keys[100], keys_modo_ejemplo[7], keys_modo_experimento[101];                 // Guardamos memoria estática de 100, no perdemos tiempo de ejecución añadiendo o quitando
                                                                                                 // bloques en memoria dinámica (+1 por la celda de seguridad).
double GetProbabilidad(int n);
//objetos[100], objetos_GB[100], objetos_GP[100], objetos_PD[100],                // Guardamos memoria estática de 100, no perdemos tiempo de ejecución añadiendo o quitando
// objetos_solucion_GB[100], objetos_solucion_GP[100], objetos_solucion_PD[100];   // bloques en memoria dinámica.

double GetProbabilidad(int n){
    double probabilidad = keys[n].probabilidad;
    return probabilidad;
}

int GetCantidadKeys(){
    int i = 0;
    for (i=0 ; i<102 ; i++){
        if (keys[i].peso == -99){
            break;
        }
    }
    return i;
}

void CopiarKeysTemp(){
    int N = GetCantidadKeys();
    for (int i=0 ; i<N+1 ; i++){
        keys_temp[i] = keys[i];
//        printf("key copiado %lf\n", keys_temp[i].probabilidad);
    }
}
void CrearKeys_Ejemplo1(){
    keys[0].caracter     = '1';
    keys[0].probabilidad = 0.05;
    
    keys[1].caracter     = '2';
    keys[1].probabilidad = 0.07;
    
    keys[2].caracter     = '3';
    keys[2].probabilidad = 0.01;
    
    keys[3].caracter     = '4';
    keys[3].probabilidad = 0.35;
    
    keys[4].caracter     = '5';
    keys[4].probabilidad = 0.09;
    
    keys[5].caracter     = '6';
    keys[5].probabilidad = 0.23;
    
    keys[6].caracter     = '7';
    keys[6].probabilidad = 0.15;
    
    keys[7].caracter     = '8';
    keys[7].probabilidad = 0.04;
    
    keys[8].caracter     = '9';
    keys[8].probabilidad = 0.01;
    
    keys[9].caracter     = 'Z';               // Dato de seguridad, para indicar que hasta acá llega
    keys[9].peso         = -99;                 
    keys[9].probabilidad = -99.0;                 
}

void CrearKeys_Ejemplo2(){
    keys[0].caracter     = '1';
    keys[0].probabilidad = 0.18;
    
    keys[1].caracter     = '2';
    keys[1].probabilidad = 0.32;
    
    keys[2].caracter     = '3';
    keys[2].probabilidad = 0.39;
    
    keys[3].caracter     = '4';
    keys[3].probabilidad = 0.11;
    
    keys[4].caracter     = 'Z';               // Dato de seguridad, para indicar que hasta acá llega
    keys[4].peso         = -99;                 
    keys[4].probabilidad = -99.0;                 
}

// Crea el array de Objetos para el modo Ejemplo
void CrearKeys_ModoEjemplo(){
    int n           = 6;
    int peso_maximo = 1000;
    int suma_de_pesos = 0;
    char caracteres[6] = "ABCDEF";
    for (int i=0 ; i<n ; i++){                              // Asigna el peso y caracter a cada llave
        keys[i].caracter     = caracteres[i];
        keys[i].peso         = 1 + (rand() %(peso_maximo));
        suma_de_pesos                    += keys[i].peso;
    }
    float unitario = 1.0/(double)suma_de_pesos;
//    printf("unitario: %lf \n", unitario);
    for (int i=0 ; i<n ; i++){                              // Asigna probabilidades a cada llave
        keys[i].probabilidad = keys[i].peso * unitario;
//        printf("Proba: %lf \n", keys_modo_ejemplo[i].peso * unitario);
    }
    keys[n].caracter     = 'Z';               // Dato de seguridad, para indicar que hasta acá llega
    keys[n].peso         = -99;               // el array actual.
    keys[n].probabilidad = -99;               
    
    // return keys_modo_ejemplo;                            // Estamos trabajando con variables globales.
}

void CrearKeys_ModoExperimento(int n){
//    int n           = 10 + (rand() %(90));
    int peso_maximo = 1000;
    int suma_de_pesos = 0;
    for (int i=0 ; i<n ; i++){                              // Asigna el peso y caracter a cada llave
        // El caracter se omite
        keys[i].peso     = 1 + (rand() %(peso_maximo));
        suma_de_pesos   += keys[i].peso;
    }
    float unitario = 1.0/(double)suma_de_pesos;
    for (int i=0 ; i<n ; i++){                              // Asigna probabilidades a cada llave
        keys[i].probabilidad = keys[i].peso * unitario;
    }
    keys[n].peso         = -99;               // Dato de seguridad, para indicar que hasta acá llega
    keys[n].probabilidad = -99;               // el array actual.
    
    // return keys_modo_ejemplo;                            // Estamos trabajando con variables globales.
}


// Deja el arreglo con -1s
void PrintKeys_ModoEjemplo(){
    int n           = 6;
    printf("Keys: \n");
    for (int i=0 ; i<n ; i++){                              // Asigna el peso y caracter a cada llave
        printf("Key%i: %lf ; ", i+1, keys[i].probabilidad);
    }
    printf("\n");
}

void PrintKeys_Ejemplos(){
    int n           = GetCantidadKeys();
    printf("Keys: \n");
    for (int i=0 ; i<n ; i++){                              // Asigna el peso y caracter a cada llave
        printf("Key%i: %lf ; ", i+1, keys[i].probabilidad);
    }
    printf("\n");
}

void Latex_PrintKeys_ModoEjemplo(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    int n           = GetCantidadKeys();
    fputs("Keys generated: \\\\ \n", tex_file);
    fputs("\\tab Key \\minitab Weight \\minitab Probability \\\\ \n", tex_file);
    for (int i=0 ; i<n ; i++){                              // Asigna el peso y caracter a cada llave
        fprintf(tex_file, "\\tab Key");
        if (i == 0){
            fprintf(tex_file, "A");
        }else if (i == 1){
            fprintf(tex_file, "B");
        }else if (i == 2){
            fprintf(tex_file, "C");
        }else if (i == 3){
            fprintf(tex_file, "D");
        }else if (i == 4){
            fprintf(tex_file, "E");
        }else if (i == 5){
            fprintf(tex_file, "F");
        }else{
            fprintf(tex_file, "Z");
        }
        fprintf(tex_file, " \\minitab  %i \\tab %lf \\\\ \n ", keys[i].peso, keys[i].probabilidad);
    }
    fputs("\n", tex_file);
    fputs("Forced sum of the probability of the keys: 1.0 \\\\ \n", tex_file);
//    fprintf(tex_file,"Se generaron %i llaves, con éstas se procede a crear la tabla A con sus valores iniciales \\\\ \n", n);
//    fputs("\n", tex_file);
    fclose(tex_file);
}
void Latex_PrintKeys(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    int n           = GetCantidadKeys();
    fputs("Keys generated: \\\\ \n", tex_file);
    fputs("\\tab Key \\minitab Weight \\minitab Probability \\\\ \n", tex_file);
    for (int i=0 ; i<n ; i++){                              // Asigna el peso y caracter a cada llave
        fprintf(tex_file, "\\tab Key%i \\minitab  %i \\tab %lf \\\\ \n ", i+1, keys[i].peso, keys[i].probabilidad);
    }
    fputs("\n", tex_file);
    fputs("Forced sum of the probability of the keys: 1.0 \\\\ \n", tex_file);
//    fprintf(tex_file,"Se generaron %i llaves, con éstas se procede a crear la tabla A con sus valores iniciales \\\\ \n", n);
//    fputs("\n", tex_file);
    fclose(tex_file);
}
void Latex_PrintKeys_Ejemplos(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    int n           = GetCantidadKeys();
    fputs("Keys generated: \\\\ \n", tex_file);
    for (int i=0 ; i<n ; i++){                              // Asigna el peso y caracter a cada llave
        fprintf(tex_file, "\\tab Key%i: %lf \\\\ \n ", i+1, keys[i].probabilidad);
    }
    fputs("Forced sum of the probability of the keys: 1.0 \\\\ \n", tex_file);
//    fprintf(tex_file,"Se generaron %i llaves, con éstas se procede a crear la tabla A con sus valores iniciales \\\\ \n", n);
//    fputs("\n", tex_file);
    fclose(tex_file);
}


// Deja el arreglo con -1s
void ResetearKeys_ModoEjemplo(){
    int n           = 6;
    for (int i=0 ; i<n ; i++){                              // Asigna el peso y caracter a cada llave
        keys[i].caracter     = 'M';
        keys[i].peso         = -99;
        keys[i].probabilidad = -99;
    }
}


// Deja el arreglo con -1s
void ResetearKeys_ModoExperimento(){
    int n           = 1000;
    for (int i=0 ; i<n ; i++){                              // Asigna el peso y caracter a cada llave
        // El caracter se omite
        keys_modo_ejemplo[i].peso         = -1;
        keys_modo_ejemplo[i].probabilidad = -1;
    }
}

#endif /* KEY_H */

