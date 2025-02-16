#include "../TDA/lista.h"
#include "../jugadores/jugadores.h"
#include "../juego/juego.h"


int main(){
  char opcion;
  tConfig config;
  char urlGET[150] = {0};

  if(!cargarConfiguracion(NOMBRE_ARCH,&config))
    return 0;

  generarUrl(urlGET,&config);

  imprimirOpciones();
  escanearOpciones(&opcion);

  while(opcion != 'C'){

    if(opcion == 'A'){
      jugar();
      system("pause");
    }
    else if(opcion == 'B'){
      iniciarGET(urlGET);
      system("pause");
    }
    else{
      puts("Opcion invalida, debera volver a ingresar.");
      system("pause");
    }

    fflush(stdin);
    system("cls");
    imprimirOpciones();
    escanearOpciones(&opcion);
  }
  return 0;
}
