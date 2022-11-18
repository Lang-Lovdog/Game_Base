#include "GameBase.h"
#include <stdlib.h>


// Definicion de elementos
ELEMENTO* nueva_entidad(char ancho,char alto,char pos_x,char pos_y){
  ELEMENTO* leNew=(ELEMENTO*)malloc(sizeof(ELEMENTO));
  leNew->dimensiones[0]=ancho;
  leNew->dimensiones[1]=alto;
  leNew->posicion[0]=pos_x;
  leNew->posicion[1]=pos_y;
  return leNew;
}
void elimina_entidad(ELEMENTO* a){
  if(a==NULL){
    free(a);
    a=NULL;
  }
}
void elimina_entidades(ELEMENTO** a,char n){
  if(a){
    char q=0;
    while(q<n){
      if((*(a+q))==NULL)
        free(*(a+q));
      ++q;
    }
    free(a);
    a=NULL;
  }
}
// Comportamiento de elementos
ELEMENTO* trayectoria(const ELEMENTO* objeto,char pasoX,char pasoY){
  ELEMENTO* siguiente=nueva_entidad(objeto->dimensiones[0],objeto->dimensiones[1],objeto->posicion[0],objeto->posicion[1]);
  ntrayectoria(siguiente,pasoX,pasoY);
  return siguiente;
}

void ntrayectoria(ELEMENTO* objeto,char pasoX,char pasoY){
  objeto->dimensiones[0]=objeto->dimensiones[0];
  objeto->dimensiones[1]=objeto->dimensiones[1];
  objeto->posicion[0]=objeto->posicion[0]+pasoX;
  objeto->posicion[1]=objeto->posicion[1]+pasoY;
}

// Identidad de posición
char arriba_de(const ELEMENTO* a,const ELEMENTO* b){
  if(a->posicion[1]+a->dimensiones[1]-1 < b->posicion[1]) return 1;
  else return 0;
}
char a_izquierda_de(const ELEMENTO* a,const ELEMENTO* b){
  if(a->posicion[0]+a->dimensiones[0]-1 < b->posicion[0]) return 1;
  else return 0;
}
char solapado(const ELEMENTO* a,const ELEMENTO* b){
  char A[2];
  char B[2];

  for(*(A+0)=0;*(A+0)<*(a->dimensiones+0);++*(A+0))
    for(*(A+1)=0;*(A+1)<*(a->dimensiones+1);++*(A+1))
      for(*(B+0)=0;*(B+0)<*(b->dimensiones+0);++*(B+0))
        for(*(B+1)=0;*(B+1)<*(b->dimensiones+1);++*(B+1))
          if(*(a->posicion+0)+*(A+0)==*(b->posicion+0)+*(B+0) &&
             *(a->posicion+1)+*(A+1)==*(b->posicion+1)+*(B+1)) return 1;
  return 0;
}

// Interaccion de elementos
char colisiona (const ELEMENTO* pelota,const ELEMENTO* elementos,char pasoX,char pasoY){
    char salida=0,pasox,pasoy,cambio[2];
    ELEMENTO* pelota_siguiente;
    *cambio    =pasoX<0? -1:1;
    *(cambio+1)=pasoY<0? -1:1; 

    pasox=0;pasoy=0;
    if(pasoX<0){
      BUCLE1XNeg:
        BUCLE1YNeg:
          pelota_siguiente=trayectoria(pelota,pasox,pasoy);
          // Llega con direccion en X
          if( solapado(pelota,elementos)||
              (a_izquierda_de(elementos,pelota)&&
              (a_izquierda_de(pelota_siguiente,elementos)||solapado(pelota_siguiente,elementos)))
          ){ salida+=1; pasox=pasoX; pasoy=pasoY; }
          if(pelota_siguiente)
            elimina_entidad(pelota_siguiente);
        if(pasoY!=pasoy){ --pasoy; goto BUCLE1YNeg; }
      if(pasoX!=pasox){ --pasox; goto BUCLE1XNeg; }
    }else if(pasoX>0){
      BUCLE1XPos:
        BUCLE1YPos:
          pelota_siguiente=trayectoria(pelota,pasox,pasoy);
          if( solapado(pelota,elementos)||
              (a_izquierda_de(pelota,elementos)&&
              (a_izquierda_de(elementos,pelota_siguiente)||solapado(pelota_siguiente,elementos)))
          ){ salida+=2; pasox=pasoX; pasoy=pasoY; }
          if(pelota_siguiente)
            elimina_entidad(pelota_siguiente);
        if(pasoY!=pasoy){ ++pasoy; goto BUCLE1YPos; }
      if(pasoX!=pasox){ ++pasox; goto BUCLE1XPos; }
    }
    pasox=0;pasoy=0; 
    if(pasoY<0){
      BUCLE2XNeg:
        BUCLE2YNeg:
          pelota_siguiente=trayectoria(pelota,pasox,pasoy);
          // Llega con direccion en Y
          if( solapado(pelota,elementos)||
              (arriba_de(elementos,pelota)&&
              (arriba_de(pelota_siguiente,elementos)||solapado(pelota_siguiente,elementos)))
          ){ salida+=4; pasox=pasoX; pasoy=pasoY; }
          if(pelota_siguiente)
            elimina_entidad(pelota_siguiente);
        if(pasoY!=pasoy){ --pasoy; goto BUCLE2YNeg; }
      if(pasoX!=pasox){ --pasox; goto BUCLE2XNeg; }
    }else if(pasoY>0){ 
      BUCLE2XPos:
        BUCLE2YPos:
          pelota_siguiente=trayectoria(pelota,pasox,pasoy);
          if( solapado(pelota,elementos)||
              (arriba_de(pelota,elementos)&&
              (arriba_de(elementos,pelota_siguiente)||solapado(pelota_siguiente,elementos)))
          ){ salida+=8; pasox=pasoX; pasoy=pasoY; }
          if(pelota_siguiente)
            elimina_entidad(pelota_siguiente);
        if(pasoY!=pasoy){ ++pasoy; goto BUCLE2YPos; }
      if(pasoX!=pasox){ ++pasox; goto BUCLE2XPos; }
    }
    // Comprueba que exista el elemento en su camino
    switch(salida){
    case 1: ; case 2:
        // Fuera del rango, no rebota salida=0;
        if( !(pelota->posicion[1]>elementos->posicion[1]-1 &&
            pelota->posicion[1]<elementos->posicion[1]+elementos->dimensiones[1]))
                salida*=0;
        break;
    case 4: ; case 8:
        // Fuera del rango, no rebota salida=0;
        if( !(pelota->posicion[0]>elementos->posicion[0]-1 &&
            pelota->posicion[0]<elementos->posicion[0]+elementos->dimensiones[0]))
                 salida*=0;
        break;
    }
    return salida;
}

// Informacion de elementos
void selemento_datos(const ELEMENTO* objeto,char x,char y,const char* etiqueta){
  if(objeto==NULL) return;
    move(y,x);
    printw("%s",etiqueta);
    elemento_datos(objeto,x,y+1);
}
void elemento_datos(const ELEMENTO* objeto,char x,char y){
  if(objeto==NULL) return;
    move(y,x);
    printw("Coordenadas: (%3i, %3i)",objeto->posicion[0],objeto->posicion[1]);
    move(y+1,x);
    printw("Dimensiones: %3i x %3i",objeto->dimensiones[0],objeto->dimensiones[1]);
}

// Utilidades
void dibujar_elemento(const ELEMENTO* cosa,const char base,const char cuerpo){
  if(cosa==NULL) return;
  long int a=0,b;
  while(a<cosa->dimensiones[0]){
    b=0;
    while(b<cosa->dimensiones[1]){
      if((long int)cosa->posicion[0]+a>-1 && (long int)cosa->posicion[1]+b>-1){
        //Posiciona cursor en la coordenada x,y
        //Imprime partícula del elemento
        move((int)(cosa->posicion[1]+b),(int)(cosa->posicion[0]+a));
        printw("%c",cuerpo);
      }
      ++b;
    }
    ++a;
  }
}

void dibujar_elementos(const ELEMENTO** cosa,const char base,const char cuerpo,int n){
  for(int q=0;(int)q<n;++q)
    dibujar_elemento(*(cosa+q),base,cuerpo);
}
