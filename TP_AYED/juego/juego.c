#include "juego.h"

void imprimirTablero(char tablero[FILAS][COLUMNAS]) {
  puts("");
  for(int i = 0; i < FILAS; i++) {
    for(int j = 0; j < COLUMNAS; j++)
      printf("%c ", tablero[i][j]);
    puts("");
  }
}

int verificarGanador(char tablero[FILAS][COLUMNAS]) {
  int i;

  // Verificar filas

  for(i = 0; i < FILAS; i++)  {
    if(tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2])  {
      return tablero[i][0];
    }
  }

  // Verificar columnas

  for(i = 0; i < COLUMNAS; i++) {
    if(tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i])  {
      return tablero[0][i];
    }
  }

  // Verificar diagonales

  if(tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2])  {
    return tablero[0][0];
  }
  if(tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0])  {
    return tablero[1][1];
  }
  return 0;
}

int verificarFilasIA(char tablero[FILAS][COLUMNAS],int car1,int car2) {
  int i;

  for(i = 0; i < 3; i++) {
    if(tablero[i][0] == car1 && tablero[i][1] == car1)  {
      if(tablero[i][2] != 'O' && tablero[i][2] != 'X')  {
        tablero[i][2] = car2;
        return 1;
      }
    }
    if(tablero[i][1] == car1 && tablero[i][2] == car1)  {
      if(tablero[i][0] != 'O' && tablero[i][0] != 'X')  {
        tablero[i][0] = car2;
        return 1;
      }
    }
    if(tablero[i][0] == car1 && tablero[i][2] == car1)  {
      if(tablero[i][1] != 'O' && tablero[i][1] != 'X')  {
        tablero[i][1] = car2;
        return 1;
      }
    }
  }

  return 0;
}

int verificarColumnasIA(char tablero[FILAS][COLUMNAS],int car1,int car2)  {
  int i;

  for(i = 0; i < 3; i++) {
    if(tablero[0][i] == car1 && tablero[1][i] == car1)  {
      if(tablero[2][i] != 'O' && tablero[2][i] != 'X')  {
        tablero[2][i] = car2;
        return 1;
      }
    }
    if(tablero[1][i] == car1 && tablero[2][i] == car1)  {
      if(tablero[0][i] != 'O' && tablero[0][i] != 'X')  {
        tablero[0][i] = car2;
        return 1;
      }
    }
    if(tablero[0][i] == car1 && tablero[2][i] == car1)  {
      if(tablero[1][i] != 'O' && tablero[1][i] != 'X')  {
        tablero[1][i] = car2;
        return 1;
      }
    }
  }

  return 0;
}

int verificarDiagonalesIA(char tablero[FILAS][COLUMNAS],int car1,int car2)  {

  // Diagonal principal

  if(tablero[0][0] == car1 && tablero[1][1] == car1)  {
    if(tablero[2][2] != 'O' && tablero[2][2] != 'X')  {
      tablero[2][2] = car2;
      return 1;
    }
  }
  if(tablero[1][1] == car1 && tablero[2][2] == car1)  {
    if(tablero[0][0] != 'O' && tablero[0][0] != 'X')  {
      tablero[0][0] = car2;
      return 1;
    }
  }
  if(tablero[0][0] == car1 && tablero[2][2] == car1)  {
    if(tablero[1][1] != 'O' && tablero[1][1] != 'X')  {
      tablero[1][1] = car2;
      return 1;
    }
  }

  // Diagonal inversa

  if(tablero[2][0] == car1 && tablero[1][1] == car1)  {
    if(tablero[0][2] != 'O' && tablero[0][2] != 'X')  {
      tablero[0][2] = car2;
      return 1;
    }
  }
  if(tablero[1][1] == car1 && tablero[0][2] == car1) {
    if (tablero[2][0] != 'O' && tablero[2][0] != 'X') {
      tablero[2][0] = car2;
      return 1;
    }
  }
  if(tablero[2][0] == car1 && tablero[0][2] == car1)  {
    if(tablero[1][1] != 'O' && tablero[1][1] != 'X')  {
      tablero[1][1] = car2;
      return 1;
    }
  }

  return 0;
}

void ataqueAleatorioIA(char tablero[FILAS][COLUMNAS],int cpu) {
  int fila, columna, eleccion;

  srand(time(NULL));
  eleccion = (rand() % 9) + 1;
  fila = --eleccion / FILAS;
  columna = eleccion % COLUMNAS;

  while(tablero[fila][columna] == 'O' || tablero[fila][columna] == 'X') {
    eleccion = (rand() % 9) + 1;
    fila = --eleccion / FILAS;
    columna = eleccion % COLUMNAS;
  }

  tablero[fila][columna] = cpu;
}

void IA(char tablero[FILAS][COLUMNAS],int cpu)  {
  char jugador = (cpu == 1) ? 'O' : 'X';
  cpu = (cpu == 1) ? 'X' : 'O';

  if(verificarFilasIA(tablero,cpu,cpu)) return;
  if(verificarColumnasIA(tablero,cpu,cpu)) return;
  if(verificarDiagonalesIA(tablero,cpu,cpu)) return;

  if(verificarFilasIA(tablero,jugador,cpu)) return;
  if(verificarColumnasIA(tablero,jugador,cpu)) return;
  if(verificarDiagonalesIA(tablero,jugador,cpu)) return;

  ataqueAleatorioIA(tablero, cpu);
}

int iniciarJuego()  {
  char tablero[FILAS][COLUMNAS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
  };
  int eleccion, jugador,cpu,turno;
  int fila, columna,ganador;
  int movimientos = 0;

  srand(time(NULL));
  cpu = (rand() % 2) + 1;
  turno = cpu == 2;
  jugador = (turno == 1) ? 'X' : 'O';

  if(turno)
    imprimirTablero(tablero);

  while(movimientos != 9) {
    if(turno) {

      do  {
        printf("Le toca ser '%c' \nIngrese un numero: ",jugador);
        scanf("%d", &eleccion);
        fila = --eleccion / FILAS;
        columna = eleccion % COLUMNAS;
        if(eleccion >= 0 && eleccion <= 8)  {
          if(tablero[fila][columna] != 'X' && tablero[fila][columna] != 'O')  {
            tablero[fila][columna] = jugador;
            turno = 0;
          } else  {
            puts("Casilla ocupada");
          }
        }
        else
          puts("Numero fuera de rango [1-9]");

      } while(turno == 1);

    } else  {
      IA(tablero,cpu);
      turno = 1;
    }

    system("cls");
    imprimirTablero(tablero);
    movimientos++;

    ganador = verificarGanador(tablero);
    if(ganador) {
      cpu = (cpu == 1) ? 'X' : 'O';

      if(cpu == ganador) {
        puts("Gano la CPU");
        system("pause");
        return 2;
      }
      else {
        puts("Gano el jugador");
        system("pause");
        return 1;
      }
    }
  }

  puts("Empate");
  system("pause");
  return 0;
}
