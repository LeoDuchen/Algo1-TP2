#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "batalla.h"
#include "perfil.h"

const char ROHAN = 'R', ISENGARD = 'I';
const char TERRENO = '-';
const int ENERGIA_INICIAL = 5, ENERGIA_MAX = 10;
const int CANT_LLEGADAS_PARA_GANAR = 3;
const int PARTIDA_CONTRA_ALGUIEN = 2;
const int INTENSIDAD_MAX = 10;
const int NUMERO_ALEATORIO_RANGO_MAX = 6;
const int CANT_ELFO_URUKHAI_INICIALES = 3;
const int ENERGIA_MIN = 0;
const int ENERGIA_COSTO_ELFO_URUKHAI = 8, ENERGIA_COSTO_HOMBRE_ORCO = 3;  
const char ELFO = 'E', URUKHAI = 'U', HOMBRE = 'H', ORCO = 'O';
const int PUNTOS_ATAQUE_ELFO_URUKHAI = 10, PUNTOS_VIDA_ELFO_URUKHAI = 200;
const int PUNTOS_ATAQUE_HOMBRE_ORCO = 50, PUNTOS_VIDA_HOMBRE_ORCO = 100;
const char DECISION_POSITIVA = 'S', DECISION_NEGATIVA = 'N'; 
const int MIN_TERRENO_FIL = 0, MIN_TERRENO_COL = 0;
const int DISTANCIA_ATAQUE_ELFO_URUKHAI = 3, DISTANCIA_ATAQUE_HOMBRE_ORCO = 1;

/* Post: La función devuelve un número aleatorio. */
int numero_aleatorio() {
	int numero_aleatorio = 0;
	numero_aleatorio = rand() % NUMERO_ALEATORIO_RANGO_MAX;
	return numero_aleatorio;
}

/* Pre: El juego debe estar cargado. Recibe el bando 
cargado y la intensidad cargada.
Post: La función calcula y guarda el plus de cada bando. */
void calcular_plus(juego_t* juego) {
	srand ((unsigned)time(NULL));
	if (juego->bando == ROHAN) {
		juego->plus_rohan = juego->intensidad * numero_aleatorio();
		juego->plus_isengard = (INTENSIDAD_MAX - juego->intensidad) * numero_aleatorio();
	} else {
		juego->plus_isengard = juego->intensidad * numero_aleatorio();
		juego->plus_rohan = (INTENSIDAD_MAX - juego->intensidad) * numero_aleatorio();
	}
}

/* Post: Devuelve un número aleatorio para las filas de Rohan. */
int numero_aleatorio_rohan_filas() {
	int numero_aleatorio = 0;
	numero_aleatorio = rand() % ((MAX_TERRENO_FIL / 2) - 1) + (MAX_TERRENO_FIL / 2);
	return numero_aleatorio;
}

/* Post: Devuelve un número aleatorio para las filas de Isengard. */
int numero_aleatorio_isengard_filas() {
	int numero_aleatorio = 0;
	numero_aleatorio = rand() % ((MAX_TERRENO_FIL / 2) - 1) + 1;
	return numero_aleatorio;
}

/* Post: Devuelve un número aleatorio para las columnas de Rohan y Isengard. */
int numero_aleatorio_rohan_isengard_columnas() {
	int numero_aleatorio = 0;
	numero_aleatorio = rand() % (MAX_TERRENO_COL);
	return numero_aleatorio;
}

/* Pre: El juego debe estar cargado. Recibe una fila y una columna.
Post: Devuelve si las posiciones son iguales. */
bool posiciones_rohan_son_iguales(juego_t* juego, int fila_actual, int columna_actual) {
	bool posiciones_son_iguales = false;

	for (int i = 0; i < juego->cantidad_rohan; i++) {
		if (fila_actual == juego->rohan[i].fila && columna_actual == juego->rohan[i].columna) {
			posiciones_son_iguales = true;
		
		}
	}

	return posiciones_son_iguales;
}

/* Pre: El juego debe estar cargado. Recibe una fila y una columna.
Post: Devuelve si las posiciones son iguales. */
bool posiciones_isengard_son_iguales(juego_t* juego, int fila_actual, int columna_actual) {
	bool posiciones_son_iguales = false;

	for (int i = 0; i < juego->cantidad_isengard; i++) {
		if (fila_actual == juego->isengard[i].fila && columna_actual == juego->isengard[i].columna) {
			posiciones_son_iguales = true;
		
		}
	}

	return posiciones_son_iguales;
}

/* Pre: Recibe un personaje por referencia.
Post: Cambia los valores del personaje. */
void cargar_datos_elfo(juego_t* juego, personaje_t* personaje) {
	personaje->codigo = ELFO;
	personaje->ataque = PUNTOS_ATAQUE_ELFO_URUKHAI + juego->plus_rohan;
	personaje->vida = PUNTOS_VIDA_ELFO_URUKHAI - juego->plus_rohan;
}

/* Pre: Recibe un personaje por referencia.
Post: Cambia los valores del personaje. */
void cargar_datos_urukhai(juego_t* juego, personaje_t* personaje) {
	personaje->codigo = URUKHAI;
	personaje->ataque = PUNTOS_ATAQUE_ELFO_URUKHAI + juego->plus_isengard;
	personaje->vida = PUNTOS_VIDA_ELFO_URUKHAI - juego->plus_isengard;
}

/* Pre: El juego debe estar cargado.
Post: Carga un determinado número de elfos iniciales, 
con sus respectivas características.*/
void cargar_elfos_iniciales(juego_t* juego) {
	personaje_t personaje;
	juego->cantidad_rohan = 0;
	srand ((unsigned)time(NULL));

	for (int i = 0; i < CANT_ELFO_URUKHAI_INICIALES; i++) {
		cargar_datos_elfo(juego, &personaje);
		do {
			personaje.fila = numero_aleatorio_rohan_filas();
			personaje.columna = numero_aleatorio_rohan_isengard_columnas();
		} while (posiciones_rohan_son_iguales(juego, personaje.fila, personaje.columna));
		juego->terreno[personaje.fila][personaje.columna] = personaje.codigo;
		posicionar_personaje(juego, personaje);
	}
}

/* Pre: El juego debe estar cargado.
Post: Carga un determinado número de urukhai iniciales, 
con sus respectivas características.*/
void cargar_urukhai_iniciales(juego_t* juego) {
	personaje_t personaje;
	juego->cantidad_isengard = 0;

	for (int i = 0; i < CANT_ELFO_URUKHAI_INICIALES; i++) {
		cargar_datos_urukhai(juego, &personaje);
		do {
			personaje.fila = numero_aleatorio_isengard_filas();
			personaje.columna = numero_aleatorio_rohan_isengard_columnas();
		} while (posiciones_isengard_son_iguales(juego, personaje.fila, personaje.columna));
		juego->terreno[personaje.fila][personaje.columna] = personaje.codigo;
		posicionar_personaje(juego, personaje);
	}
}

/* Pre: El juego debe estar cargado.
Post: La función carga el terreno inicial. */
void cargar_terreno(juego_t* juego) {
	for (int i = 0; i < MAX_TERRENO_FIL; i++) {
		for (int j = 0; j < MAX_TERRENO_COL; j++) {
			juego->terreno[i][j] = TERRENO;
		}
	}
}

void inicializar_juego(juego_t* juego) {
	char bando = ' ';
	int intensidad = 0;
 	perfil(&bando, &intensidad);

	juego->energia_rohan = ENERGIA_INICIAL;
	juego->energia_isengard = ENERGIA_INICIAL;
	juego->bando = bando;
	juego->intensidad = intensidad;
	juego->tipo_de_partida = 0;
	juego->llegadas_rohan = 0;
	juego->llegadas_isengard = 0;
	juego->posicion_personaje = 0;

	printf("Elige el tipo de partida.\n1) Jugar contra la máquina.\n2) Jugar contra otra persona.\n");
	scanf("%i", &juego->tipo_de_partida);
	while (juego->tipo_de_partida != 1 && juego->tipo_de_partida != 2) {
		printf("Ingrese un número entre 1 y 2.\n");
		scanf("%i", &juego->tipo_de_partida);
	}	

 	calcular_plus(juego);
 	cargar_terreno(juego);
 	cargar_elfos_iniciales(juego);
 	cargar_urukhai_iniciales(juego);
}

void mostrar_energia(juego_t* juego) {
	printf("Energía Rohan: %i\n", juego->energia_rohan);
	printf("Energía Isengard: %i\n", juego->energia_isengard);
}

bool juego_aun_no_termino(juego_t* juego) {
	bool juego_aun_no_termino = false;

	if (juego->llegadas_rohan != CANT_LLEGADAS_PARA_GANAR && juego->llegadas_isengard != CANT_LLEGADAS_PARA_GANAR) {
		juego_aun_no_termino = true;
	}

	return juego_aun_no_termino;
}

void mostrar_mensaje_ganador(juego_t* juego) {
	if (juego->llegadas_rohan == CANT_LLEGADAS_PARA_GANAR) {
		printf("Rohan, te defendiste bien y ganaste. Felicidades.\n");
	} else {
		printf("Isengard, tus ataques te llevaron a la victoria. Felicidades.\n");
	}
}

void aumentar_energia(juego_t* juego) {
	if (juego->energia_rohan < ENERGIA_MAX) {
		juego->energia_rohan++;
	}

	if (juego->energia_isengard < ENERGIA_MAX) {
		juego->energia_isengard++;
	}
}

void limpiar_pantalla() {
	system("clear");
}

/* Post: Devuelve un número aleatorio. */
int columna_aleatoria() {
	int numero_aleatorio = 0;
	numero_aleatorio = rand() % MAX_TERRENO_COL;
	return numero_aleatorio;
}

/* Pre: Recibe un personaje por referencia.
Post: Cambia los valores del personaje. */
void cargar_datos_hombre(juego_t* juego, personaje_t* personaje) {
	personaje->fila = (MAX_TERRENO_FIL - 1);
	personaje->codigo = HOMBRE;
	personaje->ataque = PUNTOS_ATAQUE_HOMBRE_ORCO + juego->plus_rohan;
	personaje->vida = PUNTOS_VIDA_HOMBRE_ORCO - juego->plus_rohan;
}

/* Pre: Recibe un personaje por referencia.
Post: Cambia los valores del personaje. */
void cargar_datos_orco(juego_t* juego, personaje_t* personaje) {
	personaje->fila = MIN_TERRENO_FIL;
	personaje->codigo = ORCO;
	personaje->ataque = PUNTOS_ATAQUE_HOMBRE_ORCO + juego->plus_isengard;
	personaje->vida = PUNTOS_VIDA_HOMBRE_ORCO - juego->plus_isengard;
}

/* Pre: El juego debe estar cargado.
Post: Carga y posiciona un orco. */
void maquina_juega_contra_rohan(juego_t* juego) {
	personaje_t personaje;

	if (juego->energia_isengard >= ENERGIA_COSTO_HOMBRE_ORCO) {
		personaje.columna = columna_aleatoria();
		cargar_datos_orco(juego, &personaje);
		juego->energia_isengard -= ENERGIA_COSTO_HOMBRE_ORCO;
		posicionar_personaje(juego, personaje);
	}
}

/* Pre: El juego debe estar cargado.
Post: Carga y posiciona un hombre. */
void maquina_juega_contra_isengard(juego_t* juego) {
	personaje_t personaje;

	if (juego->energia_rohan >= ENERGIA_COSTO_HOMBRE_ORCO) {
		personaje.columna = columna_aleatoria();
		cargar_datos_hombre(juego, &personaje);
		juego->energia_rohan -= ENERGIA_COSTO_HOMBRE_ORCO;
		posicionar_personaje(juego, personaje);
	}
}

/* Pre: Recibe una fila y un personaje elegido cargados.
Post: Devuelve si la fila es valida para el personaje elegido. */
bool es_fila_valida (int fila, char personaje_elegido) {
	bool es_fila_valida = false;

	if (personaje_elegido == ELFO) {
		if (fila < (MAX_TERRENO_FIL / 2) || fila > (MAX_TERRENO_FIL - 2)) {
			es_fila_valida = true;
		}	
	} else {
		if (fila < (MIN_TERRENO_FIL + 1) || fila > ((MAX_TERRENO_FIL / 2) - 1)) {
			es_fila_valida = true;
		}
	}

	return es_fila_valida;
}

/* Pre: Recibe una columna y un personaje elegido cargados.
Post: Devuelve si la columna es valida para el personaje elegido. */
bool es_columna_valida (int columna, char personaje_elegido) {
	bool es_columna_valida = false;

	if (personaje_elegido == ELFO) {
		if (columna < MIN_TERRENO_COL || columna > (MAX_TERRENO_COL - 1)) {
			es_columna_valida = true;
		}
	} else if (personaje_elegido == URUKHAI) {
		if (columna < MIN_TERRENO_COL || columna > (MAX_TERRENO_COL - 1)) {
			es_columna_valida = true;
		}
	} else if (personaje_elegido == HOMBRE) {
		if (columna < MIN_TERRENO_COL || columna > (MAX_TERRENO_COL - 1)) {
			es_columna_valida = true;
		}
	} else {
		if (columna < MIN_TERRENO_COL || columna > (MAX_TERRENO_COL - 1)) {
			es_columna_valida = true;
		}
	}

	return es_columna_valida;
}

/* Pre: El juego debe estar cargado. Recibe una fila y una columna cargadas.
Post: Devuelve si hay elfos en esa posición. */
bool hay_elfos_esa_posicion(juego_t* juego, int personaje_fila, int personaje_columna) {
	bool hay_elfos_esa_posicion = false;

	for (int i = 0; i < juego->cantidad_rohan; i++) {
		if (juego->rohan[i].fila == personaje_fila) {
			if (juego->rohan[i].columna == personaje_columna) {
				if (juego->rohan[i].codigo == ELFO) {
					hay_elfos_esa_posicion = true;
				}
			}
		}
	}

	return hay_elfos_esa_posicion;
}

/* Pre: El juego debe estar cargado. Recibe una fila y una columna cargadas.
Post: Devuelve si hay urukhai en esa posición. */
bool hay_urukhai_esa_posicion(juego_t* juego, int personaje_fila, int personaje_columna) {
	bool hay_urukhai_esa_posicion = false;

	for (int i = 0; i < juego->cantidad_isengard; i++) {
		if (juego->isengard[i].fila == personaje_fila) {
			if (juego->isengard[i].columna == personaje_columna) {
				if (juego->isengard[i].codigo == URUKHAI) {
					hay_urukhai_esa_posicion = true;
				}
			}
		}
	}

	return hay_urukhai_esa_posicion;
}

/* Pre: El juego debe estar cargado.
Post: Guarda el personaje seleccionado por Rohan.*/
void preguntar_personaje_rohan(juego_t* juego) {
	char personaje_elegido = ' ';
	personaje_t personaje;

	if (juego->energia_rohan < ENERGIA_COSTO_ELFO_URUKHAI) {
		printf("Tienes %i de energía. Solo puedes posicionar un hombre.\n", juego->energia_rohan);
		personaje_elegido = HOMBRE;
	} else {
		printf("¿Qué personaje quieres posicionar, Rohan?\nE) Elfo. Cuesta %i puntos de energía.\nH) Hombre. Cuesta %i puntos de energía.\n", ENERGIA_COSTO_ELFO_URUKHAI, ENERGIA_COSTO_HOMBRE_ORCO);
		scanf(" %c", &personaje_elegido);
			while (personaje_elegido != ELFO && personaje_elegido != HOMBRE) {
				printf("Ingrese E o H.\n");
				scanf(" %c", &personaje_elegido);
			}
	}

	if (personaje_elegido == ELFO) {
		do {
			printf("Recuerda no posicionar un elfo en la posición de otro elfo.\n¿En qué fila quieres posicionar al elfo?\n");
			scanf("%i", &personaje.fila);
			while (es_fila_valida(personaje.fila, personaje_elegido)) {
				printf("Tienes que elegir una fila de tu lado de la arena. No puede ser la última fila.\n");
				scanf("%i", &personaje.fila);
			}

			printf("¿En qué columna quieres posicionar al elfo?\n");
			scanf("%i", &personaje.columna);
			while (es_columna_valida(personaje.columna, personaje_elegido)) {
				printf("Tienes que elegir una columna que este en la arena.\n");
				scanf("%i", &personaje.columna);
			}
		} while (hay_elfos_esa_posicion(juego, personaje.fila, personaje.columna));

		cargar_datos_elfo(juego, &personaje);
		juego->energia_rohan -= ENERGIA_COSTO_ELFO_URUKHAI;
	} else {
		printf("¿En qué columna quieres posicionar al hombre?\n");
		scanf("%i", &personaje.columna);
		while (es_columna_valida(personaje.columna, personaje_elegido)) {
			printf("Tienes que elegir una columna que este en la arena.\n");
			scanf("%i", &personaje.columna);
		}
		cargar_datos_hombre(juego, &personaje);
		juego->energia_rohan -= ENERGIA_COSTO_HOMBRE_ORCO;
	}
	posicionar_personaje(juego, personaje);
}

/* Pre: El juego debe estar cargado.
Post: Guarda el personaje seleccionado por Isengard.*/
void preguntar_personaje_isengard(juego_t* juego) {
	char personaje_elegido = ' ';
	personaje_t personaje;

	if (juego->energia_isengard < ENERGIA_COSTO_ELFO_URUKHAI) {
		printf("Tienes %i de energía. Solo puedes posicionar un orco.\n", juego->energia_isengard);
		personaje_elegido = ORCO;
	} else {
		printf("¿Qué personaje quieres posicionar, Isengard?\nU) Urukhai. Cuesta %i puntos de energía.\nO) Orco. Cuesta %i puntos de energía.\n", ENERGIA_COSTO_ELFO_URUKHAI, ENERGIA_COSTO_HOMBRE_ORCO);
		scanf("%c", &personaje_elegido);
		while (personaje_elegido != URUKHAI && personaje_elegido != ORCO) {
			printf("Ingrese U u O.\n");
			scanf("%c", &personaje_elegido);
		}
	}

	if (personaje_elegido == URUKHAI) {
		do {
			printf("Recuerda no posicionar un urukhai en la posición de otro urukhai.\n¿En qué fila quieres posicionar al urukhai?\n");
			scanf("%i", &personaje.fila);
			while (es_fila_valida(personaje.fila, personaje_elegido)) {
				printf("Tienes que elegir una fila de tu lado de la arena. No puede ser la última fila.\n");
				scanf("%i", &personaje.fila);
			}

			printf("¿En qué columna quieres posicionar al urukhai?\n");
			scanf("%i", &personaje.columna);
			while (es_columna_valida(personaje.columna, personaje_elegido)) {
				printf("Tienes que elegir una columna que este en la arena.\n");
				scanf("%i", &personaje.columna);
			}
		} while (hay_urukhai_esa_posicion(juego, juego->isengard[juego->cantidad_isengard].fila, juego->isengard[juego->cantidad_isengard].columna));

		cargar_datos_urukhai(juego, &personaje);
		juego->energia_isengard -= ENERGIA_COSTO_ELFO_URUKHAI;
	} else {
		printf("¿En qué columna quieres posicionar al orco?\n");
		scanf("%i", &personaje.columna);	
		while (es_columna_valida(personaje.columna, personaje_elegido)) {
			printf("Tienes que elegir una columna que este en la arena.\n");
			scanf("%i", &personaje.columna);
		}
		cargar_datos_orco(juego, &personaje);
		juego->energia_isengard -= ENERGIA_COSTO_HOMBRE_ORCO;
	}
	posicionar_personaje(juego, personaje);
}

/* Pre: El juego debe estar cargado. Recibe un char decision por referencia.
Post: La función cambia la decision. */
void tomar_decision_rohan(juego_t* juego, char* decision) {
	if (juego->energia_rohan >= ENERGIA_COSTO_HOMBRE_ORCO) {
		printf("Rohan, ¿Quieres posicionar un personaje? Ingresa S o N.\n");
		scanf("%c", decision);
		while (*decision != DECISION_POSITIVA && *decision != DECISION_NEGATIVA) {
			printf("Ingrese S o N.\n");
			scanf("%c", decision);
		}

		if (*decision == DECISION_POSITIVA) {
			preguntar_personaje_rohan(juego);
		} else {
			printf("Rohan no posicionará un personaje.\n");
		}
	} else {
		printf("Rohan no tiene suficiente energía para posicionar un personaje.\n");
	}
}

/* Pre: El juego debe estar cargado. Recibe un char decision por referencia.
Post: La función cambia la decision. */
void tomar_decision_isengard(juego_t* juego, char* decision) {
	if (juego->energia_isengard >= ENERGIA_COSTO_HOMBRE_ORCO) {
		printf("Isengard, ¿Quieres posicionar un personaje? Ingresa S o N.\n");
		scanf("%c", decision);
		while (*decision != DECISION_POSITIVA && *decision != DECISION_NEGATIVA) {
			printf("Ingrese S o N.\n");
			scanf("%c", decision);
		}

	if (*decision == DECISION_POSITIVA) {
		preguntar_personaje_isengard(juego);
	} else {
		printf("Isengard no posicionará un personaje.\n");
		}		
	} else {
		printf("Isengard no tiene suficiente energía para posicionar un personaje.\n");
	}
}

void decidir_posicionar_personaje(juego_t* juego) {
	char decision = ' ';

	if (juego->tipo_de_partida == PARTIDA_CONTRA_ALGUIEN) {
		tomar_decision_rohan(juego, &decision);
		decision = ' ';
		tomar_decision_isengard(juego, &decision);
	} else {
		if (juego->bando == ROHAN) {
			tomar_decision_rohan(juego, &decision);
			maquina_juega_contra_rohan(juego);
		} else {
			maquina_juega_contra_isengard(juego);
			tomar_decision_isengard(juego, &decision);
		}
	}
}

void contar_llegadas(juego_t* juego) {
	for (int i = 0; i < juego->cantidad_rohan; i++) {
		if (juego->rohan[i].fila == MIN_TERRENO_FIL) {
			juego->rohan[i].vida = 0;
			if (juego->llegadas_rohan < CANT_LLEGADAS_PARA_GANAR) {
				juego->llegadas_rohan++;
			}
		}
	}

	for (int i = 0; i < juego->cantidad_isengard; i++) {
		if (juego->isengard[i].fila == (MAX_TERRENO_FIL - 1)) {
			juego->isengard[i].vida = 0;
			if (juego->llegadas_isengard < CANT_LLEGADAS_PARA_GANAR) {
				juego->llegadas_isengard++;		
			}
		}
	}
}

/* Pre: Recibe 2 filas y 2 columnas.
Post: Devuele la distancia entre los puntos. */
int distancia_manhattan(int rohan_fila, int rohan_columna, int isengard_fila, int isengard_columna) {
	int distancia_manhattan = 0;
	distancia_manhattan = abs(rohan_fila - isengard_fila) + abs(rohan_columna - isengard_columna);
	return distancia_manhattan;
}

/* Pre: El juego debe estar cargado.
Post: Elimina un personaje del vector correspondiente. */
void eliminar_personaje_muerto(juego_t* juego) {
	for (int i = 0; i < juego->cantidad_rohan; i++) {
		if (juego->rohan[i].vida <= 0) {
			juego->terreno[juego->rohan[i].fila][juego->rohan[i].columna] = TERRENO;
			juego->rohan[i] = juego->rohan[juego->cantidad_rohan - 1];
			juego->cantidad_rohan--;
			i--;
		}
	}
	
	for (int i = 0; i < juego->cantidad_isengard; i++) {
		if (juego->isengard[i].vida <= 0) {
			juego->terreno[juego->isengard[i].fila][juego->isengard[i].columna] = TERRENO;
			juego->isengard[i] = juego->isengard[juego->cantidad_isengard - 1];
			juego->cantidad_isengard--;
			i--;
		}
	}
}

void posicionar_personaje(juego_t* juego, personaje_t personaje) {
	if (personaje.codigo == ELFO || personaje.codigo == HOMBRE) {
		juego->terreno[personaje.fila][personaje.columna] = personaje.codigo;
		juego->rohan[juego->cantidad_rohan] = personaje;
		juego->cantidad_rohan++;
	}

	if (personaje.codigo == URUKHAI || personaje.codigo == ORCO) {
		juego->terreno[personaje.fila][personaje.columna] = personaje.codigo;				
		juego->isengard[juego->cantidad_isengard] = personaje;
		juego->cantidad_isengard++;
	}
}

void mostrar_terreno(juego_t* juego) {
	printf("Isengard\n");
	for (int i = 0; i < MAX_TERRENO_FIL / 2; i++) {
		for (int j = 0; j < MAX_TERRENO_COL; j++) {
			printf("%c ", juego->terreno[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < MAX_TERRENO_COL; i++) {
		printf("%c%c", TERRENO, TERRENO);
	}
	printf("\n");

	for (int i = MAX_TERRENO_FIL / 2; i < MAX_TERRENO_FIL; i++) {
		for (int j = 0; j < MAX_TERRENO_COL; j++) {
			printf("%c ", juego->terreno[i][j]);
		}
		printf("\n");
	}
	printf("Rohan\n");
}

void turno_jugar(juego_t* juego) {
	char bando = ROHAN;

	for (int i = 0; i < juego->cantidad_rohan; i++) {
		jugar(juego, bando, i);
	}

	bando = ISENGARD;

	for (int i = 0; i < juego->cantidad_isengard; i++) {
		jugar(juego, bando, i);
	}
}

/* Pre: Recibe 2 filas y 2 columnas.
Post: Devuelve si hay enemigos cerca. */
bool hay_enemigos_cerca_elfo_urukhai(int fila_personaje, int columna_personaje, int fila_enemigo, int columna_enemigo) {
	bool hay_enemigos_cerca = false;

	if (distancia_manhattan(fila_personaje, columna_personaje, fila_enemigo, columna_enemigo) <= DISTANCIA_ATAQUE_ELFO_URUKHAI) {
		hay_enemigos_cerca = true;
	}

	return hay_enemigos_cerca;
}

/* Pre: El juego debe estar cargado. Recibe la posición de un personaje.
Post: Le disminuye la vida a un personaje de Isengard si esta en el rango. */
void elfo_ataca(juego_t* juego, int posicion_personaje) {
	for (int i = 0; i < juego->cantidad_isengard; i++) {
		if (hay_enemigos_cerca_elfo_urukhai(juego->rohan[posicion_personaje].fila, juego->rohan[posicion_personaje].columna, juego->isengard[i].fila, juego->isengard[i].columna)) {
			juego->isengard[i].vida -= juego->rohan[posicion_personaje].ataque;
		}
	}
}

/* Pre: El juego debe estar cargado. Recibe la posición de un personaje.
Post: Le disminuye la vida a un personaje de Rohan si esta en el rango. */
void urukhai_ataca(juego_t* juego, int posicion_personaje) {
	for (int i = 0; i < juego->cantidad_rohan; i++) {
		if (hay_enemigos_cerca_elfo_urukhai(juego->isengard[posicion_personaje].fila, juego->isengard[posicion_personaje].columna, juego->rohan[i].fila, juego->rohan[i].columna)) {
			juego->rohan[i].vida -= juego->isengard[posicion_personaje].ataque;
		}
	}
}

/* Pre: Recibe 2 filas y 2 columnas.
Post: Devuelve si hay enemigos cerca. */
bool hay_enemigos_cerca_hombre_orco(int fila_personaje, int columna_personaje, int fila_enemigo, int columna_enemigo) {
	bool hay_enemigos_cerca = false;

	if (distancia_manhattan(fila_personaje, columna_personaje, fila_enemigo, columna_enemigo) <= DISTANCIA_ATAQUE_HOMBRE_ORCO || (((fila_personaje - 1) == fila_enemigo) && (columna_personaje - 1) == columna_enemigo) || (((fila_personaje - 1) == fila_enemigo) && (columna_personaje + 1) == columna_enemigo) || (((fila_personaje + 1) == fila_enemigo) && (columna_personaje - 1) == columna_enemigo)|| (((fila_personaje + 1) == fila_enemigo) && (columna_personaje + 1) == columna_enemigo)) {
		hay_enemigos_cerca = true;
	}

	return hay_enemigos_cerca;
}

/* Pre: El juego debe estar cargado. Recibe la posición de un personaje, 
un bool por referencia y la posicion del enemigo por referencia.
Post: Cambia el valor de si atacara y la posicion del enemigo. */
void verificar_personajes_alrededor_hombre(juego_t* juego, int posicion_personaje, bool* atacara, int* posicion_enemigo) {
	int i = 0;

	while (i < juego->cantidad_isengard && *atacara == false) {
		if (hay_enemigos_cerca_hombre_orco(juego->rohan[posicion_personaje].fila, juego->rohan[posicion_personaje].columna, juego->isengard[i].fila, juego->isengard[i].columna)) {
			*atacara = true;
			*posicion_enemigo = i;
		}
		i++;
	}
}

/* Pre: El juego debe estar cargado. Recibe la posicion de un personaje
y la posición de un enemigo.
Post: Le disminuye la vida a un personaje de Isengard. */
void hombre_ataca(juego_t* juego, int posicion_personaje, int posicion_enemigo) {
	juego->isengard[posicion_enemigo].vida -= juego->rohan[posicion_personaje].ataque;
}

/* Pre: El juego debe estar cargado. Recibe la posicion de un personaje.
Post: Mueve al hombre elegido. */
void hombre_se_mueve(juego_t* juego, int posicion_personaje) {
	juego->terreno[juego->rohan[posicion_personaje].fila][juego->rohan[posicion_personaje].columna] = TERRENO;
	juego->rohan[posicion_personaje].fila--;
	juego->terreno[juego->rohan[posicion_personaje].fila][juego->rohan[posicion_personaje].columna] = HOMBRE;
}

/* Pre: El juego debe estar cargado. Recibe la posición de un personaje, 
un bool por referencia y la posicion del enemigo por referencia.
Post: Cambia el valor de si atacara y la posicion del enemigo. */
void verificar_personajes_alrededor_orco(juego_t* juego, int posicion_personaje, bool* atacara, int* posicion_enemigo) {
	int i = 0;

	while (i < juego->cantidad_rohan && *atacara == false) {
		if (hay_enemigos_cerca_hombre_orco(juego->isengard[posicion_personaje].fila, juego->isengard[posicion_personaje].columna, juego->rohan[i].fila, juego->rohan[i].columna)) {
			*atacara = true;
			*posicion_enemigo = i;
		}
		i++;
	}
}

/* Pre: El juego debe estar cargado. Recibe la posicion de un personaje
y la posición de un enemigo.
Post: Le disminuye la vida a un personaje de Rohan. */
void orco_ataca(juego_t* juego, int posicion_personaje, int posicion_enemigo) {
	juego->rohan[posicion_enemigo].vida -= juego->isengard[posicion_personaje].ataque;
}

/* Pre: El juego debe estar cargado. Recibe la posicion de un personaje.
Post: Mueve al orco elegido. */
void orco_se_mueve(juego_t* juego, int posicion_personaje) {
	juego->terreno[juego->isengard[posicion_personaje].fila][juego->isengard[posicion_personaje].columna] = TERRENO;
	juego->isengard[posicion_personaje].fila++;
	juego->terreno[juego->isengard[posicion_personaje].fila][juego->isengard[posicion_personaje].columna] = ORCO;
}

void actualizar_terreno(juego_t* juego) {
	for (int i = 0; i < juego->cantidad_rohan; i++) {
		juego->terreno[juego->rohan[i].fila][juego->rohan[i].columna] = juego->rohan[i].codigo;
	}

	for (int i = 0; i < juego->cantidad_isengard; i++) {
		juego->terreno[juego->isengard[i].fila][juego->isengard[i].columna] = juego->isengard[i].codigo;				
	}
}

void jugar(juego_t* juego, char bando, int posicion_personaje) {
	bool atacara = false;
	int posicion_enemigo = 0;

	if (bando == ROHAN) {
		if (juego->rohan[posicion_personaje].codigo == ELFO) {
			elfo_ataca(juego, posicion_personaje);
		} else {
			verificar_personajes_alrededor_hombre(juego, posicion_personaje, &atacara, &posicion_enemigo);
			if (atacara == true) {
				hombre_ataca(juego, posicion_personaje, posicion_enemigo);
			} else {
				hombre_se_mueve(juego, posicion_personaje);
				actualizar_terreno(juego);
			}
		}
	} else {
		if (juego->isengard[posicion_personaje].codigo == URUKHAI) {
			urukhai_ataca(juego, posicion_personaje);
		} else {
		verificar_personajes_alrededor_orco(juego, posicion_personaje, &atacara, &posicion_enemigo);			
			if (atacara == true) {
				orco_ataca(juego, posicion_personaje, posicion_enemigo);
			} else {
				orco_se_mueve(juego, posicion_personaje);
				actualizar_terreno(juego);
			}
		}
	}

	eliminar_personaje_muerto(juego);
}