#ifndef MODOEXPERIMENTO_H
#define MODOEXPERIMENTO_H

#include <time.h>
#include <sys/time.h>
#include "Arbol.h"
#include "latex.h"
#include "Key.h"
#include "TablaA.h"



int tiempos_greedy[10], tiempos_pd[10], esIgualElArbol;
float exitos[10];
struct timeval st, et;

void Inicializar_TablaAdicional();

void Latex_CrearTablaDeTiempo(int * tiempos){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fputs("\\begin{center} \n",tex_file);
    fputs("\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|} \n",tex_file);
    fputs("\\hline  \n",tex_file);
    fputs("\\multicolumn{10}{|c|}{Number of keys} \\\\  \n",tex_file);
    fputs("\\hline  \n",tex_file);
    fputs(" 10 & 20 & 30 & 40 & 50 & 60 & 70 & 80 & 90 & 100 \\\\  \n",tex_file);
    fputs("\\hline  \n",tex_file);
    fprintf(tex_file, " %i ", tiempos[0]);
    for (int i=1 ; i<10 ; i++){
        fprintf(tex_file, "& %i ", tiempos[i]);
    }
    fputs("\\\\  \n",tex_file);
    fputs("\\hline  \n",tex_file);
    fputs("\\end{tabular}  \n",tex_file);
    fputs("\nUnit of measurement: microsegundos ($\\mu s$) \n",tex_file);
    fputs("\\end{center} \n",tex_file);
    fclose(tex_file);
}

void Latex_CrearTablaAdicional(float * exitos){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fputs("\\begin{center} \n",tex_file);
    fputs("\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|} \n",tex_file);
    fputs("\\hline  \n",tex_file);
    fputs("\\multicolumn{10}{|c|}{Number of keys} \\\\  \n",tex_file);
    fputs("\\hline  \n",tex_file);
    fputs(" 10 & 20 & 30 & 40 & 50 & 60 & 70 & 80 & 90 & 100 \\\\  \n",tex_file);
    fputs("\\hline  \n",tex_file);
    fprintf(tex_file, " %.1f ", exitos[0]*100);
    for (int i=1 ; i<10 ; i++){
        fprintf(tex_file, "& %.1f ", exitos[i]*100);
    }
    fputs("\\\\  \n",tex_file);
    fputs("\\hline  \n",tex_file);
    fputs("\\end{tabular}     \n",tex_file);
    fputs("\nUnit of measurement: percentage (\\%) \n",tex_file);
    fputs("\\end{center} \n",tex_file);
    fclose(tex_file);
}

void IntroduccionModoExperimentoDocumentado(int N){
    Inicializar_TablaAdicional();
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fputs("\\part*{\"Experiment\" mode documented} \n",tex_file);
    fprintf(tex_file, "Different \\textbf{%i cases} will be solved with the two algorithms (greedy and dynamic programming). The number of keys varies from 10 to 100 and with weights from 1 to 1000. A time table will be created for each of them, as well as a table showing the percentage of times that the greedy algorithm found the optimal solution. \\\\ \n", 10*N);
    fputs("Each of the following pages will have an N cases with 10 keys \n",tex_file);
    fputs("\\clearpage  \n",tex_file);
    fclose(tex_file);
}
void IntroduccionModoExperimento(int N){
    Inicializar_TablaAdicional();
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fputs("\\section{\"Experiment\" mode} \n",tex_file);
    fputs("\\subsection*{Initial problem} \n",tex_file);
    fprintf(tex_file, "Different \\textbf{%i cases} will be solved with the two algorithms (greedy and dynamic programming). The number of keys varies from 10 to 100 and with weights from 1 to 1000. A time table will be created for each of them, as well as a table showing the percentage of times that the greedy algorithm found the optimal solution. \\\\ \n", 10*N);
    fclose(tex_file);
}

void TiempoPromedio(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fprintf(tex_file, "\\item It was seen that the digital programming algorithm, on average, was %i times slower than the Greedy. \n",(int)tiempos_pd[5]/tiempos_greedy[5]);
    fprintf(tex_file, "\\item The Greedy algorithm has a temporal complexity of n. \n");
    fprintf(tex_file, "\\item The Dynamic Programming algorithm has a temporal complexity of $n^{2}$ and apparently goes up, but without reaching $n^{3}$. \n");
    fprintf(tex_file, "\\item The more the number of keys grows, the Greedy algorithm reduces by far the probability of finding the optimal response. \n");
    fclose(tex_file);
}

void ConclusionesModoExperimento(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fputs("\\subsection*{Conslussions} \n",tex_file);
    fputs("\\begin{itemize}\n",tex_file);
    fclose(tex_file);
    TiempoPromedio();
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\\end{itemize}\n",tex_file);
    fclose(tex_file);
}


void Latex_TablasDeTiempo(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fputs("\\subsection{Table of time for the Greedy algorithm} \n",tex_file);
    fclose(tex_file); 
    Latex_CrearTablaDeTiempo(tiempos_greedy);
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fputs("\\subsection{Table of time for the Dynamic algorithm} \n",tex_file);
    fclose(tex_file); 
    Latex_CrearTablaDeTiempo(tiempos_pd);
}

void Inicializar_TablaAdicional(int N){
    for (int i=0 ; i<10 ; i++){
        exitos[i] = 0;
    }
}

void Latex_TablaAdicional(int N){
    for (int i=0 ; i<10 ; i++){
        exitos[i] = exitos[i]/N;
    }
    
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\n", tex_file);
    fputs("\\subsection{Aditional table} \n",tex_file);
    fputs("This table shows the percentage of coincidence that the Greedy algorithm and the dynamic programming algorithm had in the final result in the topology of the tree with the optimal solution. \n", tex_file);
    fclose(tex_file); 
    Latex_CrearTablaAdicional(exitos);
}

void ModoExperimento_GreedyDocumentado(){
    CrearTablas();          // Solo vamos a usar la tabla R
    CrearArbol_Greedy_ExperimentoDocumentado();
}

void ModoExperimento_Greedy(){
    CrearTablas();          // Solo vamos a usar la tabla R
    CrearArbol_Greedy_Experimento();
}

void ModoExperimento_PDDocumentado(){
    CrearTablas();
    Latex_CalcularTablaA_ModoExperimento();
    CrearArbolTablaR_ModoExperimentoDocumentado();
}

void ModoExperimento_PD(){
    CrearTablas();
    Latex_CalcularTablaA_ModoExperimento();
    CrearArbolTablaR_ModoExperimento();
}

void PrintTiempos(){
    printf("Time of Dynamic Algorithm \n");
    for (int i=0 ; i<10 ; i++){
        printf("\t%i con %i\n", i+1, tiempos_pd[i]);
    }
    
    printf("Time of Greedy Algorithm \n");
    for (int i=0 ; i<10 ; i++){
        printf("\t%i con %i\n", i+1, tiempos_greedy[i]);
    }
    
}
void PromedioDeTiempos(int N){
    for (int i=0 ; i<10 ; i++){
        tiempos_greedy[i] = tiempos_greedy[i]/N;
        tiempos_pd[i]     = tiempos_pd[i]/N;
    }
}
void AgregarTiempo_Greedy(int i, int tiempo){
    tiempos_greedy[i] = tiempos_greedy[i] + tiempo;
}

void AgregarTiempo_PD(int i, int tiempo){
    tiempos_pd[i] = tiempos_pd[i] + tiempo;
}


void CompararTablasR_ModoExperimentoDocumentado(int N, int CASO, int JJJ){
    esIgualElArbol = 1;
    int me_salgo = 0;
    FILE * tex_file;
    for(int i=0 ; i<tabla_R.N+1; i++){    
        if (me_salgo==1){
            break;
        }
        esIgualElArbol = 1;
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
                    if (JJJ<11){
                        tex_file = fopen(NAME_OF_TEX_FILE, "a+");
                        fputs("\n", tex_file);
                        fprintf(tex_file, "\\subsubsection{N%i CASO%i con i%i j%i Respaldo%i y la R%i} \n", N, CASO, i, j, tabla_R_respaldo.celdas[i][j], tabla_R.celdas[i][j]);
                        fclose(tex_file); 
                    }                    
                    esIgualElArbol = -1;
                    me_salgo = 1;
                    break;
                }
//                printf("Celda[%i][%i] \t",i,j);
//                printf("Greedy: %i | PD: %i \n", tabla_R_respaldo.celdas[i][j], tabla_R.celdas[i][j]);
            }
        }
//        printf("\n");
    }
    if (esIgualElArbol == 1){
        tex_file = fopen(NAME_OF_TEX_FILE, "a+");
        fputs("\n", tex_file);
        fprintf(tex_file, "\\section{Es IGUAL el N%i CASO%i +++++++++} \n", N, CASO);
        fclose(tex_file); 
        exitos[N] += 1;
//        fprintf(tex_file, "\\ Los dos árboles generados (el greedy y el de programación dinámica) comparten la misma topología, por lo cual ambos encontraron la solución óptima. \n");
    }
}
void CompararTablasR_ModoExperimento(int N){
    esIgualElArbol = 1;
    int me_salgo = 0;
    for(int i=0 ; i<tabla_R.N+1; i++){    
        if (me_salgo==1){
            break;
        }
        esIgualElArbol = 1;
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
                    me_salgo = 1;
                    break;
                }
//                printf("Celda[%i][%i] \t",i,j);
//                printf("Greedy: %i | PD: %i \n", tabla_R_respaldo.celdas[i][j], tabla_R.celdas[i][j]);
            }
        }
//        printf("\n");
    }
    if (esIgualElArbol == 1){
        exitos[N] += 1;
//        fprintf(tex_file, "\\ Los dos árboles generados (el greedy y el de programación dinámica) comparten la misma topología, por lo cual ambos encontraron la solución óptima. \n");
    }
}
//
//void CompararTablasR_ModoExperimento(int N){
//    esIgualElArbol = 1;
//    FILE * tex_file;
//    for(int i=0 ; i<tabla_R.N+1; i++){    
//        for(int j=0 ; j<tabla_R.N+1 ; j++){
//            if (i>j){
//                // Por debajo de la diagonal
//            }else if (i<j && tabla_R_respaldo.celdas[i][j]==0){
//                // Por encima de la diagonal, pero con 0s
//            }else if (i==j || i==j-1){
//                // Diagonal y encima de ella
//            }else{
//                // Donde el greedy (tabla_R_respaldo) sí tiene nodos
//                if (tabla_R_respaldo.celdas[i][j] != tabla_R.celdas[i][j]){
//                    esIgualElArbol = -1;
//                    break;
//                }
////                printf("Celda[%i][%i] \t",i,j);
////                printf("Greedy: %i | PD: %i \n", tabla_R_respaldo.celdas[i][j], tabla_R.celdas[i][j]);
//            }
//        }
////        printf("\n");
//    }
//    if (esIgualElArbol == 1){
//        exitos[N] += 1;
////        fprintf(tex_file, "\\ Los dos árboles generados (el greedy y el de programación dinámica) comparten la misma topología, por lo cual ambos encontraron la solución óptima. \n");
//    }
//}

void EjecucionesDocumentado(int N){
    int tiempo_greedy, tiempo_pd;
    int greedy_listo=0, pd_listo=0;
    FILE * tex_file;
    for (int i=0 ; i<N ; i++){
        int loops = 100;
        for (int j=10 ; j<loops+1 ; j+=10){
            ResetearTablaR();
            CrearKeys_ModoExperimento(j);
//            Latex_PrintKeys();

            // Greedy
            if (j<11){
                tex_file = fopen(NAME_OF_TEX_FILE, "a+");
                fprintf(tex_file, "\\subsection*{Caso %i}",i );
                fclose(tex_file);
            }
            
            gettimeofday(&st,NULL);                                             // INICIO DEL CONTADOR 
            ModoExperimento_GreedyDocumentado();
            gettimeofday(&et,NULL);                                             // FIN DEL CONTADOR
            tiempo_greedy = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);   // tiempo: cantidad de microseconds
            AgregarTiempo_Greedy(j/10-1, tiempo_greedy);                        // Se añade el tiempo al array de tiempos
            
            CopiarTablaR();
                    
            // Programación Dinámica
            gettimeofday(&st,NULL);                                             // INICIO DEL CONTADOR 
            ModoExperimento_PDDocumentado();
            gettimeofday(&et,NULL);                                             // FIN DEL CONTADOR
            tiempo_pd = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);   // tiempo: cantidad de microseconds
            AgregarTiempo_PD(j/10-1, tiempo_pd);                        // Se añade el tiempo al array de tiempos
            
            CompararTablasR_ModoExperimentoDocumentado(j/10-1,i,j);               // Para la tabla de éxitos
            
            if (j<11){
                tex_file = fopen(NAME_OF_TEX_FILE, "a+");
                fprintf(tex_file, "\\clearpage \n" );
                fclose(tex_file);
            }
        }
    }
    PromedioDeTiempos(N);
}


void Ejecuciones(int N){
    int tiempo_greedy, tiempo_pd;
    
    for (int i=0 ; i<N ; i++){
        int loops = 100;
        for (int j=10 ; j<loops+1 ; j+=10){
            ResetearTablaR();
            CrearKeys_ModoExperimento(j);
//            Latex_PrintKeys();

            // Greedy
            gettimeofday(&st,NULL);                                             // INICIO DEL CONTADOR 
            ModoExperimento_Greedy();
            gettimeofday(&et,NULL);                                             // FIN DEL CONTADOR
            tiempo_greedy = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);   // tiempo: cantidad de microseconds
            AgregarTiempo_Greedy(j/10-1, tiempo_greedy);                        // Se añade el tiempo al array de tiempos
            
            CopiarTablaR();
                    
            // Programación Dinámica
            gettimeofday(&st,NULL);                                             // INICIO DEL CONTADOR 
            ModoExperimento_PD();
            gettimeofday(&et,NULL);                                             // FIN DEL CONTADOR
            tiempo_pd = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);   // tiempo: cantidad de microsegundos
            AgregarTiempo_PD(j/10-1, tiempo_pd);                        // Se añade el tiempo al array de tiempos
            
            CompararTablasR_ModoExperimento(j/10-1);               // Para la tabla de éxitos
        }
    }
    PromedioDeTiempos(N);
}

void ModoExperimentoDocumentado(int N){
    Latex_Start();
    IntroduccionModoExperimentoDocumentado(N);
    EjecucionesDocumentado(N);
    Latex_TablasDeTiempo();
    Latex_TablaAdicional(N);
    Latex_End();
    GeneratePDF();
    OpenPDF();
}

void ModoExperimento(int N){
    Latex_Start();
    IntroduccionModoExperimento(N);
    Ejecuciones(N);
    Latex_TablasDeTiempo();
    Latex_TablaAdicional(N);
    ConclusionesModoExperimento();
    Latex_End();
    GeneratePDF();
    OpenPDF();
}
#endif /* MODOEXPERIMENTO_H */

