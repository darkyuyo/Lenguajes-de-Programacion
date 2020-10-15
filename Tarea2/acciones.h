#ifndef _ACCIONES_H_
#define _ACCIONES_H_
#include "escenario.h"
typedef struct dun{
    void (*funcion)();
    int identificador;
    struct dun* next;
}dun;
typedef struct acciones{
    dun* curr;
    dun* head;
    dun* tail;
    int length; 
    int posCurr;
}acciones;
void ver_plata(escenario* esc);
void saltar_encima(escenario* esc,int i);
void caminar_en(escenario* esc);
void rushear(escenario* esc);
void taclear_al_frente(escenario* esc);
dun* creardun();
acciones* crearacciones();
void nextacc(acciones* acc);
acciones* inicioacciones();
void moveracc(acciones* acc,int numero);
void freedun(dun* d);
void borraraccion(acciones* acc,int ident);
void anadiraccion(acciones* acc,int ident);
void casos(escenario* esc,acciones* acc);
void choice(int ident,acciones* acc,escenario* esc);
void freeacc(acciones* acc);
void borrar_dun(acciones* acc,int i);
void borrar_acciones(acciones* acc);
#endif