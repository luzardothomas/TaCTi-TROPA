#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#define MINIMO(X,Y) (((X) < (Y)) ? (X) : (Y))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo  {
  void* dato;
  unsigned tam;
  struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* pl);
int insertarAlComienzo(tLista* pl,const void* dato,unsigned tam);
int sacarAlComienzo(tLista* pl,void* dato,unsigned tam);

#endif // LISTA_H_INCLUDED
