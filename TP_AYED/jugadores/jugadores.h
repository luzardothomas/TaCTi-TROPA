#ifndef JUGADORES_H_INCLUDED
#define JUGADORES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include"../TDA/lista.h"
#define CONFIGURACION_ARCH "configuracion.txt"
#define INFORME_ARCH "informe-juego_"
#define TXT_ARCH ".txt"
#define DATA_ARCH "data_post_"
#define JSON_ARCH ".json"
#define TAM_NOMBRE 51
#define TAM_URL 151
#define TAM_CODGRUP 21
#define TAM_LINEA 100
#define TAM_TIEMPO 31

typedef struct {
  char nombre[TAM_NOMBRE];
  int puntuacion;
  int ocupado;
}tPersona;

typedef struct {
  char url[TAM_URL];
  char codGrup[TAM_CODGRUP];
  int cantPartidas;
}tConfig;

int create_json_file(const char *filename,tLista* pl,accion act);
void grabarArchivoJSON(void* a,void* b);
int cargarConfiguracion(const char *filename,void* dato);
void generarUrl(char* cadena,void* dato);
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
void iniciarGET(const char* urlGET);
void ocuparEspacio(void* a,void *b);
int compararFlag(const void* a,const void* b);
void acumularPuntaje(void*a,void*b);
int compararNombre(const void*a,const void*b);
void formatearNombreArchivo(char* nombreFinal,char* nombreArch,char* extension);
void grabarPuntaje(void*a,void*b);
int jugar(const tConfig* config);

#endif // JUGADORES_H_INCLUDED
