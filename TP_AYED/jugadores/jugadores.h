#ifndef JUGADORES_H_INCLUDED
#define JUGADORES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include"../TDA/lista.h"
#define NOMBRE_ARCH "configuracion.txt"

typedef struct {
  char nombre[51];
  int puntuacion;
  int ocupado;
}tPersona;

typedef struct {
  char url[151];
  char codGrup[21];
  int cantPartidas;
}tConfig;

int create_json_file(const char *filename,tLista* pl,accion act);
void grabarArchivoJSON(void* a,void* b);
int devolverConfiguracion(const char *filename,void* dato);
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
void iniciarGET(const char* urlGET);
void ocuparEspacio(void* a,void *b);
int compararFlag(const void* a,const void* b);
void acumularPuntaje(void*a,void*b);
int compararNombre(const void*a,const void*b);
int crearArchivoConFechaYHora(char* nombreFinal,char* nombreArch,char* extension);
void grabarPuntaje(void*a,void*b);
int jugar();

#endif // JUGADORES_H_INCLUDED
