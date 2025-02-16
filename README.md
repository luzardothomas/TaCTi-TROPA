# TaCTi-TROPA

Para **Jugar**, se deberá ingresar al programa y se imprimirá en pantalla un menú con opciones:

[A] Jugar 

[B] Ver ranking equipo 

[C] Salir

Si alguien ingresa a “Jugar”, primero se le pedirá que cargue los nombres de las personas que van a jugar. Puede ingresar la cantidad de nombres que desee. Una vez que termine de ingresarlos, aparecerá por pantalla el orden en el que jugarán los jugadores, y se le preguntará al primer jugador si está listo. En caso de que sí, inicia el juego. Cada jugador va a jugar X cantidad de partidas, determinado en la configuración del programa. En cada partida, le tocará aleatoriamente ser la X o el O. Se mostrará el tablero, cada casillero se corresponde con un número y el jugador tiene que ingresar en que número de casillero quiere hacer su movimiento. La máquina responde con su jugada. Se repite el proceso hasta que uno de los dos gane o se empate. Cuando el jugador termine con sus partidas, pasará al siguiente jugador. Y así sucesivamente hasta terminar todas las partidas de todos los jugadores. Por cada partida que se termine, se sumaran +3 puntos si gana el jugador, +2 puntos si empata con la maquina y -1 punto si pierde. 
Una vez finalizadas las partidas, se mostrará por pantalla un informe con el detalle de las partidas, quien ganó, el puntaje de cada una, el puntaje total por jugador y el resultado final.

**Reglas del juego** 

El usuario y la máquina juegan por turnos en un tablero de 3x3. Para ganar, un jugador debe colocar tres de sus símbolos en una línea horizontal, vertical o diagonal. Si el tablero se llena sin que haya un ganador, la partida se considera un empate.

**Configuración del juego**

El juego toma la configuración desde un archivo txt (TP_AYED/TP_AYED/configuracion.txt) con el siguiente formato:

![image](https://github.com/user-attachments/assets/6ff90c3d-afd8-4a3f-a658-905b80a8c07f)

Se puede cambiar manualmente el número de “Cantidad de partidas” para definir cuantas partidas se juegan por jugador.

# LOTES DE PRUEBA

| N°  | Descripción | Salida esperada | Salida obtenida | Captura |
|----|-------------|----------------|----------------|---------|
| 1  | Se quiere probar qué pasaría si elegimos dos casilleros consecutivos alineados, para ganar con el tercer casillero alienado. | Se espera que la CPU elija el tercer casillero alineado para bloquear la línea. | La CPU en su segundo turno eligió el casillero para bloquear la línea satisfactoriamente. | ![image](https://github.com/user-attachments/assets/b03dbf4f-82c0-4d4d-9824-20f200b39518)|
| 2  | Se quiere probar qué pasaría si le dejamos a la CPU la posibilidad de ganar, eligiendo casilleros no alineados. | Se espera que la CPU gane la ronda. | La CPU eligió los casilleros 2, 5 y 8, formando la línea. | ![image](https://github.com/user-attachments/assets/94cf6ccf-c6ff-4ca8-b328-6d068239780a)|
| 3  | Se quiere probar qué pasaría si elegimos un número fuera del rango 1-9. | Se espera que el programa muestre el error y te vuelva a pedir el número dentro del rango. | El programa notificó el error y que debemos volver a ingresar un número dentro del rango. | ![image](https://github.com/user-attachments/assets/605e43c3-857a-49c6-9d61-263064eba151)|
| 4  | Se quiere probar qué funcione la posibilidad de que la CPU inicie la ronda y elija un casillero al azar. | Se espera que la CPU comience la ronda y elija un casillero al azar. | A la CPU le tocó ser ‘X’ y arrancó la ronda correctamente eligiendo el casillero 6. | ![image](https://github.com/user-attachments/assets/31f058a1-85cb-4564-9db6-7956c170535e)|
| 5  | Se quiere probar qué pasaría si elegimos un casillero ya seleccionado. | Se espera que el programa muestre el error y te vuelva a pedir el número dentro del rango. | El programa notificó que el casillero está ocupado y que debemos volver a ingresar un número dentro del rango. | ![image](https://github.com/user-attachments/assets/ee96981b-0f85-4956-bb06-63b14999220a)|
| 6  | Se quiere probar qué pasaría si empatamos la partida, es decir, ninguno consigue formar la línea. | Se espera que el programa determine que la ronda terminó empatada. | El programa notificó que la partida finalizó en empate. | ![image](https://github.com/user-attachments/assets/a2daeac6-2f9a-44fa-b87d-01f5d1ef23f8)|
| 7  | Se quiere probar qué pasaría si ganamos la ronda. | Se espera que el programa determine que la ronda terminó en victoria para el usuario. | El programa notificó que la partida finalizó en empate. | ![image](https://github.com/user-attachments/assets/17b6fbb2-3aa5-46dd-86e8-23eb0b40e745)|
| 8  | Se quiere probar qué pasaría si jugamos a bloquearle las opciones a la CPU. | Se espera que la CPU juegue de manera inteligente y busque la posibilidad de ganar. | La CPU arranco con el 6, se bloqueó su juego eligiendo el 9, la CPU optó por continuar con el 7, se bloqueó su juego con el 4, en la siguiente ronda la CPU eligió el 3 y el usuario el 2, finalmente la CPU analizó que con el 5 formaba la línea y lo escogió, ganó la CPU. | ![image](https://github.com/user-attachments/assets/914f48c0-6d91-405f-84d6-e78eaa469152)|
