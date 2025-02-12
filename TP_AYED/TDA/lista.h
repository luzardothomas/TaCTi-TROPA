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

typedef void (*accion)(void*,void*);
typedef int (*cmp)(const void*,const void*);

void crearLista(tLista* pl);
int esListaVacia(const tLista* pl);
void vaciarLista(tLista* pl);
int insertarAlComienzo(tLista* pl,const void* dato,unsigned tam);
int insertarAlFinal(tLista* pl,const void* dato,unsigned tam);
int sacarAlComienzo(tLista* pl,void* dato,unsigned tam);
int devolverElemListaConAccion(tLista* pl,void* dato,unsigned tam,int eleccion,void* param,accion act,cmp comp);
int devolverElemLista(tLista* pl,void* dato,unsigned tam,int eleccion);
tLista* buscarOcurrencia(tLista* pl,void* dato,cmp comp);
int buscarYAcumular(tLista* pl,void* dato,void* acum,accion act,cmp comp);
void eliminarNodo(tLista* pl);
tLista* buscarMayorNodo(tLista* pl,cmp comp);
int buscarMayorEnLista(tLista* pl,cmp comp);
void recorrerLista(tLista* pl,void* param, accion act);

#endif // LISTA_H_INCLUDED
