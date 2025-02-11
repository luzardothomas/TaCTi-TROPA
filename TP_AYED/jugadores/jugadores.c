#include "jugadores.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Función que maneja la respuesta de la solicitud HTTP


size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)  {
  size_t realsize = size * nmemb;
  char* linea = (char *)contents;
  char* aux;
  int puntaje;
  int a,b,c,a1,b1,c1;

  int contador = 0;

  while(contador != 20) {
    //printf("%.*s", (int)realsize, (char *)contents);
    aux = strchr(linea,',');
    //printf("%s\n",aux);
    *(aux-1) = '\0';
    linea = strrchr(linea,':');
    printf("El nombre es %s\n",linea+2);
    aux = strchr(aux,':');
    //printf("%s\n",aux);
    sscanf(aux+1,"%d",&puntaje);
    printf("El puntaje es %d\n",puntaje);
    aux++;
    aux = strchr(aux,':');
    //printf("%s\n",aux);
    sscanf(aux+2,"%2d/%2d/%4d %2d:%2d:%2d",&a,&b,&c,&a1,&b1,&c1);
    printf("La fecha es %02d/%02d/%d %02d:%02d:%02d",a,b,c,a1,b1,c1);
    aux++;
    aux = strchr(aux,',');
    aux++;
    linea = aux;
    puts("");
    contador++;
  }

  return realsize;
}

void iniciarGET(){
  CURL *curl;
  CURLcode res;
  // Inicializar el manejo de curl
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl){
    // Establecer la URL de la solicitud GET
    curl_easy_setopt(curl, CURLOPT_URL, "https://algoritmos-api.azurewebsites.net/api/TaCTi/TROPICAL");
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
