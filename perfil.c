#include <stdio.h>
#include <stdbool.h>
#include "perfil.h"

const int ARIES = 1, TAURO = 2, GEMINIS = 3, CANCER = 4, LEO = 5, VIRGO = 6;
const int LIBRA = 7, ESCORPIO = 8, SAGITARIO = 9, CAPRICORNIO = 10, ACUARIO = 11, PISCIS = 12;

const int FUEGO = 1, TIERRA = 2, AIRE = 3, AGUA = 4;

const char ACCION = 'A', COMEDIA = 'C', DRAMA = 'D', TERROR = 'T';

const int MALDADES_HECHAS_MIN = 0, MALDADES_HECHAS_MAX = 99;

const int CANTIDAD_MASCOTAS_MIN = 0, CANTIDAD_MASCOTAS_MAX = 5;

const int MALDADES_HECHAS_MIN_SEGUNDO_RANGO_UN_PUNTO = 50;
const char OFENSIVO = 'I', DEFENSIVO = 'R';

const int MALDADES_HECHAS_MAX_PRIMER_RANGO_UN_PUNTO = 9, MALDADES_HECHAS_MAX_SEGUNDO_RANGO_UN_PUNTO = 59;
const int MALDADES_HECHAS_MIN_PRIMER_RANGO_DOS_PUNTOS = 10, MALDADES_HECHAS_MAX_PRIMER_RANGO_DOS_PUNTOS = 19;
const int MALDADES_HECHAS_MIN_PRIMER_RANGO_TRES_PUNTOS = 20, MALDADES_HECHAS_MAX_PRIMER_RANGO_TRES_PUNTOS = 29;
const int MALDADES_HECHAS_MIN_PRIMER_RANGO_CUATRO_PUNTOS = 30, MALDADES_HECHAS_MAX_PRIMER_RANGO_CUATRO_PUNTOS = 39;
const int MALDADES_HECHAS_MIN_SEGUNDO_RANGO_DOS_PUNTOS = 60, MALDADES_HECHAS_MAX_SEGUNDO_RANGO_DOS_PUNTOS = 69;
const int MALDADES_HECHAS_MIN_SEGUNDO_RANGO_TRES_PUNTOS = 70, MALDADES_HECHAS_MAX_SEGUNDO_RANGO_TRES_PUNTOS = 79;
const int MALDADES_HECHAS_MIN_SEGUNDO_RANGO_CUATRO_PUNTOS = 80, MALDADES_HECHAS_MAX_SEGUNDO_RANGO_CUATRO_PUNTOS = 89;

const int UN_PUNTO_MALDAD = 1, DOS_PUNTOS_MALDAD = 2, TRES_PUNTOS_MALDAD = 3;
const int CUATRO_PUNTOS_MALDAD = 4, CINCO_PUNTOS_MALDAD = 5;

const int VALOR_DE_INICIALIZACION_NULO_PARA_ENTEROS = 0;
const char VALOR_DE_INICIALIZACION_NULO_PARA_CARACTERES = ' '; 

/* 
Pre: La función solo recibe enteros entre 1 y 12, ambos inclusive.
Post: La función guarda el signo zodiacal. 
*/
void preguntar_signo_zodiaco(int *signo_zodiaco) {
//	printf("¿Cuál es tu signo zodiacal? Por favor, ingrese uno de los siguientes números.\n1) Aries.\n2) Tauro.\n3) Géminis.\n4) Cáncer.\n5) Leo.\n6) Virgo.\n7) Libra.\n8) Escorpio.\n9) Sagitario.\n10) Capricornio.\n11) Acuario.\n12) Piscis.\n");
	scanf("%i", signo_zodiaco);
	while (*signo_zodiaco < ARIES || *signo_zodiaco > PISCIS) {
		printf("El número ingresado es erróneo, por favor ingrese un número entre 1 y 12.\n1) Aries.\n2) Tauro.\n3) Géminis.\n4) Cáncer.\n5) Leo.\n6) Virgo.\n7) Libra.\n8) Escorpio.\n9) Sagitario.\n10) Capricornio.\n11) Acuario.\n12) Piscis.\n");
		scanf("%i", signo_zodiaco);
	}
}

/* 
Pre: La función recibe el número de signo zodiacal cargado.
Post: La función evalua de que elemento es cada signo zodiacal 
y guarda el elemento del signo zodiacal. 
*/
void verificar_elemento_zodiaco(int *signo_zodiaco, int *elemento) {
	if (*signo_zodiaco == ARIES || *signo_zodiaco == LEO || *signo_zodiaco == SAGITARIO) {
		(*elemento) = FUEGO;
	} else if (*signo_zodiaco == TAURO || *signo_zodiaco == VIRGO || *signo_zodiaco == CAPRICORNIO) {
		(*elemento) = TIERRA;
	} else if (*signo_zodiaco == GEMINIS || *signo_zodiaco == LIBRA || *signo_zodiaco == ACUARIO) {
		(*elemento) = AIRE;
	} else {
		(*elemento) = AGUA;
	}
}

/* 
Pre: La función solo recibe los caracteres (todos en mayúscula): A, C, D o T.
Post: La función guarda el género de cine. 
*/
void preguntar_genero_cine(char *genero_cine) {
//	printf("¿Cuál es tu género de cine preferido? Por favor, ingrese una de las siguientes letras en mayúscula.\nA) Acción.\nC) Comedia.\nD) Drama.\nT) Terror.\n");
	scanf(" %c", genero_cine);
	while (*genero_cine != ACCION && *genero_cine != COMEDIA && *genero_cine != DRAMA && *genero_cine != TERROR) {
		printf("La letra ingresada es errónea, por favor ingrese una letra válida (asegurese de que sea mayúscula).\nA) Acción.\nC) Comedia.\nD) Drama.\nT) Terror.\n");
		scanf(" %c", genero_cine);
	}
}

/* 
Pre: La función solo recibe enteros entre 0 y 99, ambos inclusive.
Post: La función guarda el número de maldades hechas. 
*/
void preguntar_maldades_hechas(int *maldades_hechas) {
//	printf("¿Cuántas maldades hiciste en el último mes (sin mentir)? Elige un número entre 0 y 99.\n");
	scanf("%i", maldades_hechas);
	while (*maldades_hechas < MALDADES_HECHAS_MIN || *maldades_hechas > MALDADES_HECHAS_MAX) {
		printf("El número ingresado es erróneo (o estas mintiendo), por favor ingrese un número entre 0 y 99.\n");
		scanf("%i", maldades_hechas);		
	}
}

/* 
Pre: La función solo recibe enteros entre 0 y 5, ambos inclusive.
Post: La función guarda el número de mascotas. 
*/
void preguntar_cantidad_mascotas(int *cantidad_mascotas) {
//	printf("¿Cuántas mascotas posees? Elige un número entre 0 y 5. Elige 5 si tienes más mascotas.\n");
	scanf("%i", cantidad_mascotas);
	while (*cantidad_mascotas < CANTIDAD_MASCOTAS_MIN || *cantidad_mascotas > CANTIDAD_MASCOTAS_MAX) {
		printf("El número ingresado es erróneo, por favor ingrese un número entre 0 y 5.\n");
		scanf("%i", cantidad_mascotas);
	}
}

/* 
Pre: Recibe las variables cargadas de las preguntas respondidas.
Post: Si el jugador es encasillado, avanza a las siguientes 
funciones. Sino, vuelve a empezar todo de nuevo desde la primer función. 
*/
void determinar_bando(char *bando, int elemento, char genero_cine, int maldades_hechas, bool *error_encasillar) {
	if (elemento == FUEGO || elemento == AIRE) {
		if (genero_cine == COMEDIA || genero_cine == TERROR) {
			if (maldades_hechas >= MALDADES_HECHAS_MIN_SEGUNDO_RANGO_UN_PUNTO) {
				(*bando) = OFENSIVO;
				(*error_encasillar) = false;
			}
		}
	} else {
		if (genero_cine == ACCION || genero_cine == DRAMA) {
			if (maldades_hechas < MALDADES_HECHAS_MIN_SEGUNDO_RANGO_UN_PUNTO) {
				(*bando) = DEFENSIVO;
				(*error_encasillar) = false;
			}
		}
	}
	if (*error_encasillar == true) {
		printf("No pudo ser encasillado. Deberá responder todos los atributos nuevamente, pero esta vez intente responder diferente.\n");
	}
}


/* 
Pre: La función recibe las maldades hechas cargadas.
Post: Determina y guarda los puntos de maldad equivalentes a las maldades hechas. 
*/
void determinar_puntos_maldades(int *puntos_maldades, int maldades_hechas) {
	if ((maldades_hechas >= MALDADES_HECHAS_MIN && maldades_hechas <=  MALDADES_HECHAS_MAX_PRIMER_RANGO_UN_PUNTO) || (maldades_hechas >= MALDADES_HECHAS_MIN_SEGUNDO_RANGO_UN_PUNTO && maldades_hechas <= MALDADES_HECHAS_MAX_SEGUNDO_RANGO_UN_PUNTO)) {
		(*puntos_maldades) = UN_PUNTO_MALDAD;
	} else if ((maldades_hechas >= MALDADES_HECHAS_MIN_PRIMER_RANGO_DOS_PUNTOS && maldades_hechas <= MALDADES_HECHAS_MAX_PRIMER_RANGO_DOS_PUNTOS) || (maldades_hechas >= MALDADES_HECHAS_MIN_SEGUNDO_RANGO_DOS_PUNTOS && maldades_hechas <= MALDADES_HECHAS_MAX_SEGUNDO_RANGO_DOS_PUNTOS)) {
		(*puntos_maldades) = DOS_PUNTOS_MALDAD;
	} else if ((maldades_hechas >= MALDADES_HECHAS_MIN_PRIMER_RANGO_TRES_PUNTOS && maldades_hechas <= MALDADES_HECHAS_MAX_PRIMER_RANGO_TRES_PUNTOS) || (maldades_hechas >= MALDADES_HECHAS_MIN_SEGUNDO_RANGO_TRES_PUNTOS && maldades_hechas <= MALDADES_HECHAS_MAX_SEGUNDO_RANGO_TRES_PUNTOS)) {
		(*puntos_maldades) = TRES_PUNTOS_MALDAD;
	} else if ((maldades_hechas >= MALDADES_HECHAS_MIN_PRIMER_RANGO_CUATRO_PUNTOS && maldades_hechas <= MALDADES_HECHAS_MIN_PRIMER_RANGO_CUATRO_PUNTOS) || (maldades_hechas >= MALDADES_HECHAS_MIN_SEGUNDO_RANGO_CUATRO_PUNTOS && maldades_hechas <= MALDADES_HECHAS_MAX_SEGUNDO_RANGO_CUATRO_PUNTOS)) {
		(*puntos_maldades) = CUATRO_PUNTOS_MALDAD;
	} else {
		(*puntos_maldades) = CINCO_PUNTOS_MALDAD;
	}
}

/* 
Pre: La función recibe los puntos de maldad y la cantidad de mascotas cargadas.
Post: Suma y devuelve la suma de las dos variables ya mencionadas. 
*/
int suma_intensidad(int puntos_maldades, int cantidad_mascotas) {
	return (puntos_maldades + cantidad_mascotas);
}

/* 
Pre: La función recibe el bando y la intensidad.
Post: Muestra un mensaje con la intensidad dependiendo el número de bando. 
*/
void mensaje_a_mostrar(char bando, int intensidad) {
	if (bando == OFENSIVO) {
		printf("Usted nació para la guerra, tu espíritu ofensivo de poder %i te llevara a la victoria!\n", intensidad);
	} else {
		printf("Tienes un espíritu defensivo de poder %i, no dejes que el enemigo te pisotee!\n", intensidad);
	}
}

void perfil(char* bando, int* intensidad) {
	int signo_zodiaco = 0;
	int elemento = 0;
	char genero_cine = ' ';
	int maldades_hechas = 0;
	int cantidad_mascotas = 0;
	bool error_encasillar = true;
	int puntos_maldades = 0;

	do {
		preguntar_signo_zodiaco(&signo_zodiaco);
		verificar_elemento_zodiaco(&signo_zodiaco, &elemento);
		preguntar_genero_cine(&genero_cine);
		preguntar_maldades_hechas(&maldades_hechas);
		preguntar_cantidad_mascotas(&cantidad_mascotas);
		determinar_bando(bando, elemento, genero_cine, maldades_hechas, &error_encasillar);
	} while (error_encasillar == true);

	determinar_puntos_maldades(&puntos_maldades, maldades_hechas);
	*intensidad = suma_intensidad(puntos_maldades, cantidad_mascotas);
	mensaje_a_mostrar(*bando, *intensidad);
}