#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arbol.h"
#include "TablaA.h"
#include "Key.h"

#ifndef _LATEX_H_
#define _LATEX_H_

#define NAME_OF_TEX_FILE "Output_document.tex"
#define NAME_OF_PDF_FILE "Output_document.pdf"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define BCK  "\x1B[0m"


//void Latex_ChangeNameFile(char nombre[]){
//    NAME_OF_TEX_FILE = nombre;
//    NAME_OF_PDF_FILE = nombre;
//}

double GetProbabilidad(int n);

void Latex_Table_Start(int N){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\\begin{center} \n", tex_file);          // \begin{center}
    fputs("\\begin{tabular}{", tex_file);
    for (int i=0 ; i<N ; i++) fputs("|c", tex_file);
    fputs("|} \n", tex_file);                       // \begin{tabular}{|c|c|c|c|c|c|c|c|}
    fputs("\\hline \n", tex_file);                  // \hline 
    fclose(tex_file);
}

void Latex_Table_Content(int m, int n){
    
}

void Latex_Table_End(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");   
    fputs("\\end{tabular} \n", tex_file);          // \end{tabular} 
    fputs("\\end{center} \n", tex_file);          // \end{center}
    fclose(tex_file);
}

//void Latex_Table(struct st_tabla_A tabla){
//    Latex_Table_Start(tabla.N);
//    Latex_Table_Content(tabla.N, tabla.N);
//    Latex_Table_End();
//}

//
int Latex_Nodes(nodo * n, short anteriorFuePadre, int ultimoFueIzquierdo){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    if (n->valor == 1){
        fprintf(tex_file, "node [treenode] {$A$  ");
    }else if (n->valor == 2){
        fprintf(tex_file, "node [treenode] {$B$  ");
    }else if (n->valor == 3){
        fprintf(tex_file, "node [treenode] {$C$  ");
    }else if (n->valor == 4){
        fprintf(tex_file, "node [treenode] {$D$  ");
    }else if (n->valor == 5){
        fprintf(tex_file, "node [treenode] {$E$  ");
    }else if (n->valor == 6){
        fprintf(tex_file, "node [treenode] {$F$  ");
    }else{
        fprintf(tex_file, "node [treenode] {$Z$  ");
    }
    fprintf(tex_file, " \\\\ %.3lf}  ", GetProbabilidad((n->valor)-1));
    anteriorFuePadre = 1;
    fclose(tex_file);
    if(n->izquierda){
        tex_file = fopen(NAME_OF_TEX_FILE, "a+");
        fputs("child { \n", tex_file);
        anteriorFuePadre = 0;
        fclose(tex_file);
        
        Latex_Nodes(n->izquierda, anteriorFuePadre, ultimoFueIzquierdo);
        
        tex_file = fopen(NAME_OF_TEX_FILE, "a+");
        if (ultimoFueIzquierdo == 1){
            fputs("child[missing] ", tex_file);
        }
        fputs("} \n", tex_file);
        ultimoFueIzquierdo = 1;
        anteriorFuePadre = 0;
        fclose(tex_file);
    }
    if(n->derecha){
        tex_file = fopen(NAME_OF_TEX_FILE, "a+");
        if (anteriorFuePadre == 1){
            fputs("child[missing] ", tex_file);
        }else{
            if (ultimoFueIzquierdo == 1){
                ultimoFueIzquierdo = 0;                
            }
        }
        fputs("child { ", tex_file);
        anteriorFuePadre = 0;
        fclose(tex_file);
        Latex_Nodes(n->derecha, anteriorFuePadre, ultimoFueIzquierdo);
        tex_file = fopen(NAME_OF_TEX_FILE, "a+");
        if (ultimoFueIzquierdo == 1){
            fputs("child[missing] ", tex_file);
        }
        fputs("} \n", tex_file);
        ultimoFueIzquierdo = 0;
        anteriorFuePadre = 0;
        fclose(tex_file);
    }
    return ultimoFueIzquierdo;
}

// Objetos en Latex 
//
void Latex_Tree(nodo * n){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\\begin{figure}[H] \n", tex_file);
    fputs("\\begin{center} \n", tex_file);
    fputs("Optimal tree created from table R \\\\ \n", tex_file);
    fputs("{ \n", tex_file);
    fputs("\\begin{tikzpicture}[->,>=stealth',level/.style={sibling distance = 5cm/#1, level distance = 1.5cm},scale=0.6, transform shape] \n", tex_file);
    fputs("\\", tex_file);
    fclose(tex_file);
    
    int ultimoFueIzquierdo = Latex_Nodes(n, 0, 0);
    if (ultimoFueIzquierdo == 1){
        fputs("child[missing] ", tex_file);
    }
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("; \n", tex_file);
    fputs("\\end{tikzpicture}  \n", tex_file);
    fputs("}  \n", tex_file);
    fputs("\\end{center} \n", tex_file);
    fputs("\\end{figure} \n", tex_file);
    fclose(tex_file);
}



void Latex_Start(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "w");
    fputs("% A.B.B. Dynamic vs. A.B.B. Greedy \n", tex_file);
    fputs("% Written by Edisson López \n", tex_file);
    fputs("% Contact: ediloaz@gmail.com \n", tex_file);
    fputs("% Cartago, Costa Rica \n", tex_file);
    fputs("  \n", tex_file);
    fputs("% For the course: \n", tex_file);
    fputs("% 	Operations Research (of Costa Rica Institute of Technology) \n", tex_file);
    fputs("% 	Teacher: Dr. Jose Francisco Torres \n", tex_file);
    fputs(" \n", tex_file);
    fputs("% HEADER { \n", tex_file);
    fputs("\\documentclass[a4paper,twocolumn,10pt]{article} \n", tex_file);
    fputs("\\usepackage{tikz} \n", tex_file);
    fputs("\\usepackage{pgfplots} \n", tex_file);
    fputs("\\pgfplotsset{compat=1.10} \n", tex_file);
    fputs("\\usetikzlibrary{shapes.geometric,arrows,fit,matrix,positioning} \n", tex_file);
    fputs("\\tikzset \n", tex_file);
    fputs("{ \n", tex_file);
    fputs("    treenode/.style = {circle, draw=black, align=center, minimum size=1cm} \n", tex_file);
    fputs("} \n", tex_file);
    fputs("\\usepackage{lmodern} \n", tex_file);
    fputs("\\usepackage{float} \n", tex_file);
    fputs("\\usepackage[T1]{fontenc} \n", tex_file);
    fputs("%\\usepackage[spanish]{babel} \n", tex_file);
    fputs("\\usepackage[utf8]{inputenc} \n", tex_file);
    fputs("\\usepackage[left=0.7cm, top=1.5cm, right=0.7cm, bottom=2cm]{geometry} \n", tex_file);
    fputs("\\newcommand\\tab[1][1cm]{\\hspace*{#1}} \n", tex_file);
    fputs("\\newcommand\\minitab[1][0.5cm]{\\hspace*{#1}} \n", tex_file);
    fputs("\\title{A.B.B. Dynamic vs. A.B.B. Greedy} \n", tex_file);
    fputs("\\author{Edisson López Díaz} \n", tex_file);
    fputs("\\date{\\today}  \n", tex_file);
    fputs("% } HEADER \n", tex_file);
    
    fputs("% DOCUMENT { \n", tex_file);
    fputs("\\begin{document} \n", tex_file);
    fputs("\\maketitle \n", tex_file);
    fclose(tex_file);
}


void Latex_End(){
    FILE * tex_file;
    tex_file = fopen(NAME_OF_TEX_FILE, "a+");
    fputs("\\end{document}\n", tex_file);
    fputs("% } DOCUMENT \n", tex_file);
    fputs("% Last line of the document", tex_file);
    fclose(tex_file);
}


void GeneratePDF(){
    char command[] = "pdflatex ";
    strcat(command, NAME_OF_TEX_FILE);
    system(command);
}

void OpenPDF(){
    char command[] = "xdg-open ";
    strcat(command, NAME_OF_PDF_FILE);
    system(command);
}

void MoveFiles(){
    system("mv -v ./LATEX.pdf ./Output/LATEX.pdf");
    system("mv -v ./LATEX.tex ./Output/LATEX.tex");
    system("mv -v ./LATEX.log ./Output/LATEX.log");
    system("mv -v ./LATEX.aux ./Output/LATEX.aux");
    system("mv -v ./LATEX.nav ./Output/LATEX.nav");
    system("mv -v ./LATEX.out ./Output/LATEX.out");
    system("mv -v ./LATEX.snm ./Output/LATEX.snm");
    system("mv -v ./LATEX.toc ./Output/LATEX.toc");
}

void Latex(){
    Latex_Start();
    Latex_End();
    GeneratePDF();
    OpenPDF();
    
}
#endif /* _LATEX_H_ */

