#include <stdio.h>
#include <stdlib.h>
#include "batalla.h"

int main() {
	juego_t juego;

	inicializar_juego(&juego);
	do {
		mostrar_terreno(&juego);
		mostrar_energia(&juego);
		turno_jugar (&juego);
		decidir_posicionar_personaje(&juego);
		contar_llegadas(&juego);
		aumentar_energia(&juego);
		limpiar_pantalla();
	} while (juego_aun_no_termino(&juego));

	mostrar_mensaje_ganador(&juego);

	return 0;
}