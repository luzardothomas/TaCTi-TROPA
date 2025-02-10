#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#define FILAS 3
#define COLUMNAS 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void imprimirTablero(char tablero[FILAS][COLUMNAS]);
int verificarGanador(char tablero[FILAS][COLUMNAS]);
int verificarFilasIA(char tablero[FILAS][COLUMNAS],int car1,int car2);
int verificarColumnasIA(char tablero[FILAS][COLUMNAS], int car1,int car2);
int verificarDiagonalesIA(char tablero[FILAS][COLUMNAS], int car1,int car2);
void ataqueAleatorioIA(char tablero[FILAS][COLUMNAS],int cpu);
int iniciarJuego();

#endif // JUEGO_H_INCLUDED
