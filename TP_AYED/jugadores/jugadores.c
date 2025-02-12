#include "jugadores.h"
#include "../juego/juego.h"
#include "../TDA/lista.h"
#include <curl/curl.h>

int create_json_file(const char *filename,tLista* pl,accion act) {
    FILE *file = fopen(filename, "wt");
    if (!file) {
        perror("Error al crear el archivo");
        return 0;
    }

    if(!*pl) {
      fclose(file);
      return 0;
    }

    fprintf(file, "{\n \"CodigoGrupo\": \"TROPICAL\",\n");
    fprintf(file, "    \"Jugadores\": [\n");

    act((*pl)->dato,file);
    pl = &(*pl)->sig;

    while(*pl) {
      fprintf(file,",\n");
      act((*pl)->dato,file);
      pl = &(*pl)->sig;

    }

    fprintf(file, "\n]\n}");

    fclose(file);
    return 1;
}

void grabarArchivoJSON(void* a,void* b) {
  tPersona* pa = (tPersona*)a;
  FILE* pb = (FILE*)b;
  fprintf(pb, "    {\"nombre\": \"%s\",\n",pa->nombre);
  fprintf(pb, "    \"puntos\": %d}",pa->puntuacion);
}

char *read_file(const char *filename) {
    char linea[100] = {0};

    char* content;

    FILE *file = fopen(filename,"rt");
    if (!file) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    fseek(file,0,SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    content = malloc(file_size);
    if(!content) return NULL;

    *content = '\0';

    while(fgets(linea,100,file)) {
      strcat(content,linea);
    }


    fclose(file);
    return content;
}
int devolverConfiguracion(const char *filename,void* dato) {
  char linea[100];
  char* aux;
  tConfig config;
  FILE* pf;
  pf = fopen(filename,"rt");

  if(!pf)
    return 0;

  fgets(linea,100,pf);

  aux = strchr(linea,'|');
  strcpy(config.codGrup,aux+1);
  *(aux-1) = '\0';

  strcpy(config.url,linea);

  fgets(linea,100,pf);

  sscanf(linea,"%d",&config.cantPartidas);

  memcpy(dato,&config,sizeof(tConfig));
  return 1;
}
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)  {
  size_t realsize = size * nmemb;
  char* linea = (char *)contents;
  char* aux;
  char nombre[51];
  char chequearVacio[3] = {0};
  int puntaje;
  int dia,mes,anio,hs,min,seg;

  memcpy(chequearVacio,linea,2);

  if(strcmp(chequearVacio,"[]") == 0) {
    printf("Aun no ha jugado nadie\n");
    return 0;
  }

  puts("=================== RANKING ===================");
  puts("-----------------------------------------------");

  while(aux) {

    aux = strchr(linea,',');

    *(aux-1) = '\0';
    linea = strrchr(linea,':');
    sscanf(linea + 2,"%s",nombre);
    printf("NOMBRE JUGADOR: %s | ",nombre);
    aux = strchr(aux,':');

    sscanf(aux+1,"%d",&puntaje);
    printf("PUNTAJE: %d\n",puntaje);
    aux++;
    aux = strchr(aux,':');

    sscanf(aux+2,"%2d/%2d/%4d %2d:%2d:%2d",&dia,&mes,&anio,&hs,&min,&seg);
    printf("ULTIMA PARTIDA JUGADA: %02d/%02d/%d %02d:%02d:%02d\n",dia,mes,anio,hs,min,seg);

    printf("-----------------------------------------------");


    aux++;
    aux = strchr(aux,',');

    if(aux) {
      aux++;
      linea = aux;
    }

    puts("");
  }



  return realsize;
}
void iniciarGET(const char* urlGET){
  CURL *curl;
  CURLcode res;
  // Inicializar el manejo de curl
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl){
    // Establecer la URL de la solicitud GET
    curl_easy_setopt(curl, CURLOPT_URL, urlGET);
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "X-Secret: FADSFAS");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // Establecer la función de retorno de llamada para manejar la respuesta
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    // Realizar la solicitud HTTP GET
    res = curl_easy_perform(curl);
    // Verificar si la solicitud fue exitosa
    if (res != CURLE_OK)
      fprintf(stderr, "Error en la solicitud: %s\n",

    curl_easy_strerror(res));
    // Limpiar y cerrar el manejo de curl
    curl_easy_cleanup(curl);
    // Finalizar el manejo global de curl
    curl_global_cleanup();
  }

}
int iniciarPOST(const char *filename,tLista* pl,accion act,const char* urlPOST) {
    CURL *curl;
    CURLcode res;
    create_json_file(filename,pl,act);

    // Leer el JSON desde el archivo

    char *json_data = read_file(filename);

    if (!json_data) {
        fprintf(stderr, "Error al leer el archivo JSON\n");
        return 1;
    }

    printf("JSON enviado:\n%s\n", json_data);  // Verificar JSON antes de enviarlo
    puts("");
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Expect:");  // Evitar problemas con "100-continue"

        curl_easy_setopt(curl, CURLOPT_URL, urlPOST);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(json_data));  // Asegurar tamaño correcto
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // Desactivar verificación SSL
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Error en POST: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    free(json_data);
    curl_global_cleanup();

    return 0;
}
void ocuparEspacio(void* a,void *b) {
  tPersona* pa = (tPersona*)a;
  pa->ocupado = 1;
}
int compararFlag(const void* a,const void* b) {
  tPersona* pa = (tPersona*)a;
  return pa->ocupado == 1;
}
void acumularPuntaje(void*a,void*b) {
  tPersona* pa = (tPersona*)a;
  int* pb = (int*)b;
  pa->puntuacion += *pb;
}
int compararNombre(const void*a,const void*b) {
  tPersona* pa = (tPersona*)a;
  tPersona* pb = (tPersona*)b;
  return strcmp(pa->nombre,pb->nombre);
}
int compararPuntaje(const void*a,const void*b) {
  tPersona* pa = (tPersona*)a;
  tPersona* pb = (tPersona*)b;
  return pa->puntuacion - pb->puntuacion;
}
int crearArchivoConFechaYHora(char* nombreFinal,char* nombreArch,char* extension) {
  time_t t;
  struct tm *tm_info;
  char buffer[51]; // Espacio suficiente para "YYYY-MM-DD-HH-mm"
  FILE* pf;

  time(&t);               // Obtener el tiempo actual
  tm_info = localtime(&t); // Convertir a tiempo local

  // Formatear la fecha y hora
  strftime(buffer, sizeof(buffer), "%Y-%m-%d-%H-%M", tm_info);

  *nombreFinal = '\0';

  strcat(nombreFinal,nombreArch);
  strcat(nombreFinal,buffer);
  strcat(nombreFinal,extension);

  pf = fopen(nombreFinal,"wt");

  if(!pf)
    return 0;

  fclose(pf);

  return 1;
}
void grabarPuntaje(void*a,void*b) {
  tPersona* pa = (tPersona*)a;
  FILE* pb = (FILE*)b;
  fprintf(pb,"Nombre %s Puntuacion %d\n",pa->nombre,pa->puntuacion);
}
int jugar() {

  char nombre[51];
  tLista lista,listaRandom;
  tPersona dato;
  int cantUsuarios = 0;
  int randomizar;
  int eleccion;
  int puntaje;
  int resultado;
  int partidas = 0;
  int i;
  tConfig config;
  FILE* pInforme;

  if(!devolverConfiguracion(NOMBRE_ARCH,&config))
    return 0;

  crearLista(&lista);
  crearLista(&listaRandom);

  printf("Ingrese los nombres [0 para salir]:");
  scanf("%s",nombre);

  srand(time(NULL));

  while(strcmp(nombre,"0") != 0) {
    cantUsuarios++;
    strcpy(dato.nombre,nombre);
    dato.puntuacion = 0;
    dato.ocupado = 0;
    insertarAlComienzo(&lista,&dato,sizeof(dato));

    fflush(stdin);
    system("cls");
    printf("Ingrese los nombres [0 para salir]:");
    scanf("%s",nombre);
  }

  if(!cantUsuarios)
    return 0;

  puts("Van a jugar en este orden:");

  randomizar = cantUsuarios;

  while(cantUsuarios) {
    eleccion = rand() % randomizar + 1;

    if(devolverElemListaConAccion(&lista,&dato,sizeof(dato),eleccion,NULL,ocuparEspacio,compararFlag)) {
      // informo el orden de los jugadores
      printf("%d- Nombre: %s\n",partidas,dato.nombre);
      partidas++;
      cantUsuarios--;
      insertarAlFinal(&listaRandom,&dato,sizeof(dato));
    }
  }

  partidas*=config.cantPartidas;
  eleccion = 1;

  crearArchivoConFechaYHora(nombre,"informe-juego_",".txt");
  pInforme = fopen(nombre,"wt");

  if(!pInforme)
    return 0;


  while(partidas) {

    puntaje = 0;

    devolverElemLista(&listaRandom,&dato,sizeof(dato),eleccion);

    fprintf(pInforme,"Partida de %s\n",dato.nombre);

    for(i = 0 ; i < config.cantPartidas ; i++) {
      resultado = iniciarJuego();

      if(resultado == 0) {
        puntaje += 2;
        fprintf(pInforme,"%d- Empato +2\n",i+1);
      }
      else if(resultado == 1) {
        puntaje += 3;
        fprintf(pInforme,"%d- Gano +3\n",i+1);
      }
      else {
        puntaje -= 1;
        fprintf(pInforme,"%d- Perdio -1\n",i+1);
      }

    }

    resultado++;

    fprintf(pInforme,"Puntaje total: %d\n",puntaje);
    fprintf(pInforme,"==============================\n");

    eleccion++;
    buscarYAcumular(&listaRandom,&dato,&puntaje,acumularPuntaje,compararNombre);
    partidas -= config.cantPartidas;
  }

  crearArchivoConFechaYHora(nombre,"data_post_",".json");
  iniciarPOST(nombre,&listaRandom,grabarArchivoJSON,config.url);

  fprintf(pInforme,"##############################\n");
  fprintf(pInforme,"MAYOR/MAYORES PUNTAJES\n");
  buscarMayorEnLista(&listaRandom,compararPuntaje);
  recorrerLista(&listaRandom,pInforme,grabarPuntaje);

  vaciarLista(&lista);
  vaciarLista(&listaRandom);
  fclose(pInforme);

  return 0;

}
