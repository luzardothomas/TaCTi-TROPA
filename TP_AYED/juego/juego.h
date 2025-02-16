#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#define FILAS 3
#define COLUMNAS 3
#define A_MAYUS(X) (((X) >= 'A' && (X) <= 'Z') ? (X) : ((X) - ('a'-'A')))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void imprimirOpciones();
void escanearOpciones(char* dato);
void imprimirMensaje();
void imprimirTablero(char tablero[FILAS][COLUMNAS]);
int verificarGanador(char tablero[FILAS][COLUMNAS]);
int verificarFilasIA(char tablero[FILAS][COLUMNAS],int car1,int car2);
int verificarColumnasIA(char tablero[FILAS][COLUMNAS], int car1,int car2);
int verificarDiagonalesIA(char tablero[FILAS][COLUMNAS], int car1,int car2);
void ataqueAleatorioIA(char tablero[FILAS][COLUMNAS],int cpu);
int iniciarJuego(const char* nombre);

#endif // JUEGO_H_INCLUDED
