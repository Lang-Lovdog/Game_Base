#ifndef __LANG_GAMEBASE__
#define	__LANG_GAMEBASE__

#include <stdlib.h>

#ifdef __linux__ 
#include <ncurses.h>
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define printf printw
#include <windows.h>
void move(int y, int x){ 
  HANDLE hCon; 
  COORD dwPos; 
  dwPos.X = x; 
  dwPos.Y = y; 
  hCon = GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleCursorPosition(hCon,dwPos);
}
#else
#    error "No Compatible Con El Compilador"
#endif

// Definición de elemento
typedef struct ELEMENTO{
    char dimensiones[2];  // Ancho Largo _,|
    char posicion[2];     // x,y
}ELEMENTO;

ELEMENTO* nueva_entidad(char ancho,char alto,char pos_x,char pos_y);
void elimina_entidad(ELEMENTO* a);
void elimina_entidades(ELEMENTO** a,char n);

// Comportamiento de elementoGameBase.c
ELEMENTO* trayectoria(const ELEMENTO*,char pasoX,char pasoY);
void ntrayectoria(ELEMENTO* objeto,char pasoX,char pasoY);
void mueve_jugador(void);

// InteracciÃ³n de elementos
char colisiona (const ELEMENTO* pelota,const ELEMENTO* cosa,const char pasoX,const char pasoY);

// Identidad de posición
char arriba_de(const ELEMENTO* a,const ELEMENTO* b);
char a_izquierda_de(const ELEMENTO* a,const ELEMENTO* b);
char solapado(const ELEMENTO* a,const ELEMENTO* b);

// Información de elemento
void selemento_datos(const ELEMENTO* objeto,char x,char y,const char* etiqueta);
void elemento_datos(const ELEMENTO* objeto,char pos_x,char pos_y);

// Utilidades
void dibujar_elemento(const ELEMENTO* cosa,const char base,const char cuerpo);
void dibujar_elementos(const ELEMENTO** cosa,const char base,const char cuerpo,int n);

#endif
