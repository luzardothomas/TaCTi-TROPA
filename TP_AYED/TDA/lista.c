#include "lista.h"

void crearLista(tLista* pl) {
  *pl = NULL;
}

int insertarAlComienzo(tLista* pl,const void* dato,unsigned tam)  {
  tNodo* nue;
  nue = malloc(sizeof(tNodo));
  if(nue == NULL)
    return 0;
  nue->dato = malloc(tam);
  if(nue->dato == NULL) {
    free(nue);
    return 0;
  }
  memcpy(nue->dato,dato,tam);
  nue->tam = tam;
  nue->sig = *pl;
  *pl = nue;
  return 1;
}

int sacarAlComienzo(tLista* pl,void* dato,unsigned tam) {
  tNodo* elim = *pl;
  if(!*pl)
    return 0;
  memcpy(dato,elim->dato,MINIMO(elim->tam,tam));
  *pl = elim->sig;
  free(elim->dato);
  free(elim);
  return 1;
}
