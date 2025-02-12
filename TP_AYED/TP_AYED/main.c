#include "../TDA/lista.h"
#include "../jugadores/jugadores.h"
#include "../juego/juego.h"
#define A_MINUS(X) (((X) >= 'A' && (X) <= 'Z') ? (X) : ((X) - ('a'-'A')))

int main() {
  char opcion;
  tConfig config;
  char urlGET[150] = {0};

  if(!devolverConfiguracion(NOMBRE_ARCH,&config))
    return 0;

  strcat(urlGET,config.url);
  strcat(urlGET,"/");
  strcat(urlGET,config.codGrup + 1);
  *(urlGET + strlen(urlGET) - 1) = '\0';

  printf("A- JUGAR\n");
  printf("B- RANKING\n");
  printf("C SALIR\n");
  printf("OPCION: ");
  scanf("%c", &opcion);

  opcion = A_MINUS(opcion);

  while(opcion != 'C') {

    if(opcion == 'A') {
      jugar();
      system("pause");
    }
    else if(opcion == 'B') {
      iniciarGET(urlGET);
      system("pause");
    }
    else if(opcion == 'C') {
      return 1;
    }
    else {
      puts("Opcion invalida");
      system("pause");
    }

    fflush(stdin);
    system("cls");
    printf("A- JUGAR\n");
    printf("B- RANKING\n");
    printf("C SALIR\n");
    printf("OPCION: ");
    scanf("%c", &opcion);
    opcion = A_MINUS(opcion);
  }

  return 0;
}
