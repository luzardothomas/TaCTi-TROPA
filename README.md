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

[Ir a Lotes de prueba](LOTES-DE-PRUEBA.md)
