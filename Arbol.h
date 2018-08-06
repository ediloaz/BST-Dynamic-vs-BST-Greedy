#ifndef ARBOL_H
#define ARBOL_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TEST_NUMBER 20

typedef struct nodo{
	struct nodo * izquierda, * derecha;
	int     valor;
        char    caracter;
} nodo;

// [ izquierda, visit, derecha ] 
void PrintIn(nodo * n){
	if(n->izquierda) PrintIn(n->izquierda);
	printf("%d ", n->valor);
	if(n->derecha) PrintIn(n->derecha);
}

// [ visit, izquierda, derecha ] 
void PrintPre(nodo * n){
	printf("%d ", n->valor);
	if(n->izquierda) PrintPre(n->izquierda);
	if(n->derecha) PrintPre(n->derecha);
}

// [ izquierda, derecha, visit ] 
void PrintPost(nodo * n){
	if(n->izquierda) PrintPost(n->izquierda);
	if(n->derecha) PrintPost(n->derecha);
	printf("%d ", n->valor);
}

// create a new nodo & set default nodos
nodo * NuevoNodo(int valor){
	nodo * n = malloc(sizeof(nodo));
	n->valor = valor;
	n->izquierda = n->derecha = NULL;
	return n;
}

// recursive insertion from the tree raiz
void InsertarNodo(nodo ** raiz, nodo * hijo){
	if(!*raiz) *raiz = hijo;  // tree raiz not exists
	
	else InsertarNodo( hijo->valor <= (*raiz)->valor ? &(*raiz)->izquierda : &(*raiz)->derecha , hijo );  // recursive call	
}

// recursive insertion from the tree raiz
void InsertarNodoGreedy(nodo ** raiz, nodo * hijo){
	if(!*raiz) *raiz = hijo;  // tree raiz not exists
	
	else InsertarNodo( hijo->valor <= (*raiz)->valor ? &(*raiz)->izquierda : &(*raiz)->derecha , hijo );  // recursive call	
}

// recursive Buscar of a nodo
nodo * Buscar(nodo * raiz, int valor){
	return !raiz ? NULL : raiz->valor == valor ? raiz : Buscar( valor > raiz->valor ? raiz->derecha : raiz->izquierda , valor );
}


void BuscarPorPuntero(nodo * raiz, int valor, nodo ** save){
	*save = Buscar(raiz,valor);
}

//int main(){
//	
//	int test, c, success;
//	test = c = success = 0;
//
//	srand(time(NULL));
//
//	nodo * raiz = NULL;
//
//	// INSERTION TEST 
//
//	while(c++ < TEST_NUMBER)
//		insert(&raiz, new(rand() % 150));	
//
//	// PRINT TEST
//
//	printf("\n > IN ORDER -> ");
//	in(raiz);
//
//	printf("\n\n > PRE ORDER -> ");
//	pre(raiz);
//
//	printf("\n\n > POST ORDER -> ");
//	post(raiz);
//
//	// Buscar TEST
//
//	puts("\n\n > TEST Buscar:");
//
//	while(test++ < TEST_NUMBER)
//		if(Buscar(raiz, test) > 0){
//	 		printf("  - %d\n", test);
//	 		success++;
//		}
//
//	printf("\n <SUCCESS> = %d <FAILED> = %d\n", success, TEST_NUMBER - success);
//
//}


#endif /* ARBOL_H */

