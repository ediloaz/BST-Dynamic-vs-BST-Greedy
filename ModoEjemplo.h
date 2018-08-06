#ifndef MODOEJEMPLO_H
#define MODOEJEMPLO_H

#include <time.h>
#include <sys/time.h>
#include "Arbol.h"
#include "latex.h"
#include "Key.h"
#include "TablaA.h"

int tiempo_greedy, tiempo_pd, esIgualElArbol;
struct timeval st, et;

void IntroduccionModoEjemplo(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fputs("\\section{\"Example\" mode} \n",tex_file);
    fputs("\\subsection*{Initial problem} \n",tex_file);
    fputs("\\textbf{Six keys} random were generated, with these we proceed to find the optimal solution with the Greedy algorithm and the dynamic programming algorithm.\\\\ \n",tex_file);
    fclose(tex_file);
}

void ModoEjemplo_Greedy(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\\subsection{Greedy Aagorithm} \n",tex_file);
    fputs("From the previous keys we create an equivalent to the R table used in the dynamic programming algorithm. ",tex_file);
    fputs("Choosing each time the key of maximum probability to be the root of the tree, separating the rest of the keys into two groups: ",tex_file);
    fputs("the minor ones that the selected root and the majors that this root. This recursively. \n",tex_file);
    fclose(tex_file);
    
    gettimeofday(&st,NULL);                                             // INICIO DEL CONTADOR 
    CrearTablas();          // Solo vamos a usar la tabla R
    gettimeofday(&et,NULL);                                             // FIN DEL CONTADOR
    tiempo_greedy = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);   // tiempo: cantidad de microsegundos
    
    CrearArbol_Greedy();
}

void ModoEjemplo_CrearTablaA(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fputs("From the previous keys the following table is created: \\\\ \n",tex_file);
    fclose(tex_file);
}
void ModoEjemplo_PD(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\\subsection{Dynamic algorithm} \n",tex_file);
    fclose(tex_file);
    gettimeofday(&st,NULL);                                             // INICIO DEL CONTADOR 
    CrearTablas();
    ModoEjemplo_CrearTablaA();
    gettimeofday(&et,NULL);                                             // FIN DEL CONTADOR
    tiempo_pd = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);   // tiempo: cantidad de microsegundos
    Latex_PrintTablaA();
    Latex_CalcularTablaA();
    Latex_PrintTablas();   
    gettimeofday(&st,NULL);                                             // INICIO DEL CONTADOR 
    CrearArbolTablaR();
    gettimeofday(&et,NULL);                                             // FIN DEL CONTADOR
    tiempo_pd += ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);   // tiempo: cantidad de microsegundos
}

void Latex_PrintTiempo(int tiempo){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fprintf(tex_file, "\\textbf{Computing time: } %i microseconds \n", tiempo);
    fclose(tex_file);
}

void CompararTablasR(){
    esIgualElArbol = 1;
    for(int i=0 ; i<tabla_R.N+1; i++){    
        for(int j=0 ; j<tabla_R.N+1 ; j++){
            if (i>j){
                // Por debajo de la diagonal
            }else if (i<j && tabla_R_respaldo.celdas[i][j]==0){
                // Por encima de la diagonal, pero con 0s
            }else if (i==j || i==j-1){
                // Diagonal y encima de ella
            }else{
                // Donde el greedy (tabla_R_respaldo) sí tiene nodos
                if (tabla_R_respaldo.celdas[i][j] != tabla_R.celdas[i][j]){
                    esIgualElArbol = -1;
                    break;
                }
//                printf("Celda[%i][%i] \t",i,j);
//                printf("Greedy: %i | PD: %i \n", tabla_R_respaldo.celdas[i][j], tabla_R.celdas[i][j]);
            }
        }
        printf("\n");
    }
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    if (esIgualElArbol == 1){
        fprintf(tex_file, "\\item The two generated trees (greedy and dynamic programming) share the same topology, so both found the optimal solution. \n");
    }else{
        fprintf(tex_file, "\\item The Greedy algorithm did not arrive at the optimal solution. This is appreciated when comparing the topology of the two trees. \n");
    }
    fclose(tex_file);
    
}

void TiempoDeCalculo(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fprintf(tex_file, "\\item The computing time of the dynamic algorithm was %i was less fast than the Greedy algorithm. \n",(int)tiempo_pd/tiempo_greedy);
    fputs("\\item With six keys the Greedy algorithm approximately the 32\\% of the time finds the optimal solution. \n", tex_file);
    fclose(tex_file);
}

void Conclusiones(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fputs("\\subsection*{Conclusions} \n",tex_file);
    fputs("\\begin{itemize}\n",tex_file);
    fclose(tex_file);
    CompararTablasR();
    TiempoDeCalculo();
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\\end{itemize}\n",tex_file);
    fclose(tex_file);
}

void ModoEjemplo(){
    
    Latex_Start();
    IntroduccionModoEjemplo();
    //Laves
    CrearKeys_ModoEjemplo();
//    Latex_PrintKeys();
    Latex_PrintKeys_ModoEjemplo();
    
    // Greedy
    
    ModoEjemplo_Greedy();
    Latex_PrintTiempo(tiempo_greedy);
    
    CopiarTablaR();         // Tabla R del Greedy quedó en tabla_R_respaldo
    
    // Programación Dinámica
    ModoEjemplo_PD();       // Aquí dentro se registra el tiempo
    Latex_PrintTiempo(tiempo_pd);
    
    Conclusiones();
    
    
    Latex_End();
//    
    GeneratePDF();
    OpenPDF();
    MoveFiles();
}

#endif /* MODOEJEMPLO_H */

