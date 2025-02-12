#include "lista.h"

void crearLista(tLista* pl) {
  *pl = NULL;
}

int esListaVacia(const tLista* pl) {
  return *pl == NULL;
}

void vaciarLista(tLista* pl) {
  tNodo* elim = *pl;
  while(elim) {
    pl = &elim->sig;
    free(elim->dato);
    free(elim);
    elim = *pl;
  }
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

int insertarAlFinal(tLista* pl,const void* dato,unsigned tam) {
  tNodo* nue;

  while(*pl)
    pl = &(*pl)->sig;


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
  nue->sig = NULL;
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

int devolverElemListaConAccion(tLista* pl,void* dato,unsigned tam,int eleccion,void* param,accion act,cmp comp) {
  while(*pl && eleccion) {
    eleccion--;
    if(eleccion == 0) {
      if(comp((*pl)->dato,param) == 0) {
        act((*pl)->dato,param);
        memcpy(dato,(*pl)->dato,MINIMO((*pl)->tam,tam));
        return 1;
      }
    }
    else
      pl = &(*pl)->sig;
  }
  return 0;
}

int devolverElemLista(tLista* pl,void* dato,unsigned tam,int eleccion) {
  while(*pl && eleccion) {
    eleccion--;
    if(eleccion == 0) {
      memcpy(dato,(*pl)->dato,MINIMO((*pl)->tam,tam));
      return 1;
    }
    else
      pl = &(*pl)->sig;
  }
  return 0;
}

void eliminarNodo(tLista* pl) {
  tNodo* aux = *pl;
  *pl = aux->sig;
  free(aux->dato);
  free(aux);
}

tLista* buscarOcurrencia(tLista* pl,void* dato,cmp comp) {
  while(*pl && comp((*pl)->dato,dato) != 0)
    pl = &(*pl)->sig;
  return pl;
}

int buscarYAcumular(tLista* pl,void* dato,void* acum,accion act,cmp comp) {
  tLista* buscar;
  buscar = buscarOcurrencia(pl,dato,comp);
  if(!*buscar)
    return 0;
  act((*buscar)->dato,acum);
  return 1;
}

tLista* buscarMayorNodo(tLista* pl,cmp comp) {
  tLista* mayor = pl;

  if(!*pl)
    return NULL;

  pl = &(*pl)->sig;

  while(*pl) {
    if(comp((*pl)->dato,(*mayor)->dato) >= 0)
      mayor = pl;
    pl = &(*pl)->sig;
  }
  return mayor;
}

int buscarMayorEnLista(tLista* pl,cmp comp) {
  tLista* mayor;

  if(!*pl)
    return 0;

  mayor = buscarMayorNodo(pl,comp);

  while(*pl) {
    if(comp((*pl)->dato,(*mayor)->dato))
      eliminarNodo(pl);
    else
      pl = &(*pl)->sig;
  }

  return 1;
}

void recorrerLista(tLista* pl,void* param, accion act) {
  while(*pl) {
    act((*pl)->dato,param);
    pl = &(*pl)->sig;
  }
}
