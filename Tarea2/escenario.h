#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _ESCENARIO_H_
#define _ESCENARIO_H_
typedef struct elemento{
    void* caracteristica1;
    void* caracteristica2;
    void* caracteristica3;
}elemento;     
typedef struct casilla{
    elemento* cosa;
    int tipo;
    struct casilla* next;
}casilla;
typedef struct escenario{
    casilla* curr;
    casilla* head;
    casilla* tail;
    int length;
    int posCurr;
    int largoini;
    int pospsje;
}escenario;
casilla* crearcasilla();
escenario* crearescena();
void next(escenario* mapa);
void mover( escenario* mapa,int numero);
void prev( escenario* mapa);
escenario* inicio(int numero);
void mostrar( escenario* mapa,int numero);
void mostrar_todo( escenario* mapa);
void anadir_elementos(escenario* esc, elemento* ele,int i,int tipo);
void freeesc( escenario* esc);
void freecasi( casilla* casi);
void borrar_elemento( escenario* esc,int i);
void borrar_todo( escenario* esc);
void crearpersonaje(escenario* esc);
void crearobjeto(escenario* esc,int pos);
void crearenemigo(escenario* esc,int pos);
void crearbloque(escenario* esc,int pos);
void crearpiso(escenario* esc,int pos);
void crearpisonormal(escenario* esc,int pos);
void copiarpersonaje(escenario* esc,int pos);
#endif