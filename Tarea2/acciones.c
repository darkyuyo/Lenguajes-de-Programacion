#include "escenario.h"
#include "acciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//muestra la plata del personaje
void ver_plata(escenario* esc){
    mover(esc,esc->pospsje);
    printf("cantidad de monedas:%d\n",*((int*)esc->curr->cosa->caracteristica3));
}
void saltar_encima(escenario* esc,int i){
    //si salta muy atras se queda en la casilla 1
    if(esc->pospsje+i<=1){
        mover(esc,1);
        copiarpersonaje(esc,1);
        if(esc->pospsje!=1){
            //si no estaba en casilla 1, dejamos la antigua casilla que estaba el personaje como piso normal
            crearpisonormal(esc,esc->pospsje);
        }
    esc->pospsje=1;
    }
    //si salta mas alla del limite del escenario, gana el juego
    else if(esc->pospsje+i>esc->length){
        printf("Gracias alumnos de lp por ayudarme a recuperar la memoria pero tu 100 esta en otra tarea\n");
        esc->largoini=0;
    }
    else{
        //dependiendo de donde caiga vemos que pasa
        mover(esc,esc->pospsje+i);
        //mata al enemigo
        if(esc->curr->tipo==3){
            copiarpersonaje(esc,esc->pospsje+i);
            crearpisonormal(esc,esc->pospsje);
            esc->pospsje+=i;
        }
        //se come el objeto
        else if(esc->curr->tipo==2){
            int tipe;
            if(*(int*)esc->curr->cosa->caracteristica2==1){
                tipe=1;
            }
            else if(*(int*)esc->curr->cosa->caracteristica2==2){
                tipe=3;
                }
            else if(*(int*)esc->curr->cosa->caracteristica2==3){
                tipe=4;
            }
            else if(*(int*)esc->curr->cosa->caracteristica2==4){
                tipe=2;
            }
            mover(esc,esc->pospsje);
            *((int*)esc->curr->cosa->caracteristica2)=tipe;
            copiarpersonaje(esc,esc->pospsje+i);
            crearpisonormal(esc,esc->pospsje);
            esc->pospsje+=i;
        }
        //rompe el bloque
        else if(esc->curr->tipo==4){
            //si es tipo 0 el bloque, se queda las monedas
            if(*(int*)esc->curr->cosa->caracteristica2==0){
                int monedas;
                monedas=*(int*)esc->curr->cosa->caracteristica1;
                mover(esc,esc->pospsje);
                //si esta modo wario, doble monedas
                if(*((int*)esc->curr->cosa->caracteristica2)==4){
                    *((int*)esc->curr->cosa->caracteristica3)+=monedas;
                }
                *((int*)esc->curr->cosa->caracteristica3)+=monedas;
                copiarpersonaje(esc,esc->pospsje+i);
                crearpisonormal(esc,esc->pospsje);
                esc->pospsje+=i;
            }
            else{
                //se come el objeto
                int tipe;
                if(*(int*)esc->curr->cosa->caracteristica3==1){
                    tipe=1;
                }
                else if(*(int*)esc->curr->cosa->caracteristica3==2){
                    tipe=3;
                }
                else if(*(int*)esc->curr->cosa->caracteristica3==3){
                    tipe=4;
                }
                else if(*(int*)esc->curr->cosa->caracteristica3==4){
                    tipe=2;
                }
                mover(esc,esc->pospsje);
                *((int*)esc->curr->cosa->caracteristica2)=tipe;
                copiarpersonaje(esc,esc->pospsje+i);
                crearpisonormal(esc,esc->pospsje);
                esc->pospsje+=i;
            }
        }
        else if(esc->curr->tipo==5){
            //si piso con agujero muere y vuelve al inicio
            if(*(int*)esc->curr->cosa->caracteristica1==1){
                mover(esc,esc->pospsje);
                *((int*)esc->curr->cosa->caracteristica2)=1;
                if(esc->pospsje==1){
                    crearpisonormal(esc,esc->pospsje+i);
                    return;
                }
                crearpisonormal(esc,esc->pospsje+i);
                copiarpersonaje(esc,1);
                crearpisonormal(esc,esc->pospsje);
                esc->pospsje=1;
            }
            else{
                copiarpersonaje(esc,esc->pospsje+i);
                crearpisonormal(esc,esc->pospsje);
                esc->pospsje+=i;
            }
        }
        //otros casos
        else{
            copiarpersonaje(esc,esc->pospsje+i);
            crearpisonormal(esc,esc->pospsje);
            esc->pospsje+=i;
        }
    }
}
void caminar_en(escenario* esc){
    //si pasa el largo del mapa gana
    if(esc->pospsje+1>esc->length){
        printf("Gracias alumnos de lp por ayudarme a recuperar la memoria pero tu 100 esta en otra tarea\n");
        esc->largoini=0;
    }
    else{
        mover(esc,esc->pospsje+1);
        //lo mata el enemigo y vuelve al inicio
        if(esc->curr->tipo==3){
            crearpisonormal(esc,esc->pospsje+1);
            copiarpersonaje(esc,1);
            mover(esc,1);
            *((int*)esc->curr->cosa->caracteristica2)=1;
            if(esc->pospsje!=1){
                crearpisonormal(esc,esc->pospsje);
            }
        esc->pospsje=1;
        }
        //cae en un agujero y vuelve al inicio
        else if(esc->curr->tipo==5 && *((int*)esc->curr->cosa->caracteristica1)==1){
            mover(esc,esc->pospsje);
            *(int*)esc->curr->cosa->caracteristica2=1;
            crearpisonormal(esc,esc->pospsje+1);
            copiarpersonaje(esc,1);
            if(esc->pospsje!=1){
                crearpisonormal(esc,esc->pospsje);
            }
        esc->pospsje=1;
        }
        //toma el objeto
        else if(esc->curr->tipo==2){
            int tipe;
            if(*(int*)esc->curr->cosa->caracteristica2==1){
                tipe=1;
            }
            else if(*(int*)esc->curr->cosa->caracteristica2==2){
                tipe=3;
                }
            else if(*(int*)esc->curr->cosa->caracteristica2==3){
                tipe=4;
            }
            else if(*(int*)esc->curr->cosa->caracteristica2==4){
                tipe=2;
            }
            mover(esc,esc->pospsje);
            *((int*)esc->curr->cosa->caracteristica2)=tipe;
            copiarpersonaje(esc,esc->pospsje+1);
            crearpisonormal(esc,esc->pospsje);
            esc->pospsje++;
        }
        //avanza una casilla
        else{
            copiarpersonaje(esc,esc->pospsje+1);
            crearpisonormal(esc,esc->pospsje);
            esc->pospsje++;
        }
    }
}
void rushear(escenario* esc){
    //mueve a la casilla siguiente
    mover(esc,esc->pospsje+1);
    //si hay agujero en la casilla siguiente, se muere
    if(esc->curr->tipo==5){
        if(*(int*)esc->curr->cosa->caracteristica1==1){
            crearpisonormal(esc,esc->pospsje+1);
            mover(esc,esc->pospsje);
            *(int*)esc->curr->cosa->caracteristica2=1;
            copiarpersonaje(esc,1);
            if(esc->pospsje!=1){
                crearpisonormal(esc,esc->pospsje);
            }
            esc->pospsje=1;
            return;
        }
    }
    //deja piso normal la casilla siguiente
    crearpisonormal(esc,esc->pospsje+1);
    //ve la siguiente+2 y si es agujero muere
    mover(esc,esc->pospsje+2);
    if(esc->curr->tipo==5){
        if(*(int*)esc->curr->cosa->caracteristica1==1){
            crearpisonormal(esc,esc->pospsje+2);
            mover(esc,esc->pospsje);
            *(int*)esc->curr->cosa->caracteristica2=1;
            copiarpersonaje(esc,1);
            if(esc->pospsje!=1){
                crearpisonormal(esc,esc->pospsje);
            }
            esc->pospsje=1;
            return;
        }
    }
    //la deja piso normal
    crearpisonormal(esc,esc->pospsje+2);
    mover(esc,esc->pospsje+3);
    //ve la casilla +3 si es agujero
    if(esc->curr->tipo==5){
        if(*(int*)esc->curr->cosa->caracteristica1==1){
            crearpisonormal(esc,esc->pospsje+3);
            mover(esc,esc->pospsje);
            *(int*)esc->curr->cosa->caracteristica2=1;
            copiarpersonaje(esc,1);
            if(esc->pospsje!=1){
                crearpisonormal(esc,esc->pospsje);
            }
            esc->pospsje=1;
            return;
        }
    }
    //si supera el largo, gana
    if(esc->pospsje+3>esc->length){
        printf("Gracias alumnos de lp por ayudarme a recuperar la memoria pero tu 100 esta en otra tarea\n");
        esc->largoini=0;
        return;
    }
    mover(esc,esc->pospsje);
    *(int*)esc->curr->cosa->caracteristica2=1;
    //deja al personaje mas 3 casillas
    copiarpersonaje(esc,esc->pospsje+3); 
    crearpisonormal(esc,esc->pospsje);
    esc->pospsje+=3;
}
void taclear_al_frente(escenario* esc){
    mover(esc,esc->pospsje+1);
    //mata al enemigo y toma su lugar
    if(esc->curr->tipo==3){
        copiarpersonaje(esc,esc->pospsje+1);
        crearpisonormal(esc,esc->pospsje);
        esc->pospsje++;
    }
    //queda mareado en su lugar
    else{
        mover(esc,esc->pospsje);
        *((int*)esc->curr->cosa->caracteristica2)=3;
    }
}
//copia al personaje en otra casilla
void copiarpersonaje(escenario* esc,int pos){
    elemento* aux;
    aux=(elemento*)malloc(sizeof(elemento));
    mover(esc,esc->pospsje); 
    aux->caracteristica1=(char*)malloc(sizeof(char)*100);
    aux->caracteristica2=(int*)malloc(sizeof(int));
    aux->caracteristica3=(int*)malloc(sizeof(int));
    (*(char**)aux->caracteristica1)=(*(char**)esc->curr->cosa->caracteristica1);
    (*(int*)aux->caracteristica2)=(*(int*)esc->curr->cosa->caracteristica2);
    (*(char*)aux->caracteristica3)=(*(int*)esc->curr->cosa->caracteristica3);
    borrar_elemento(esc,pos);
    anadir_elementos(esc,aux,pos,1);
}
//crea un dun
dun* creardun(){
    dun* aux;
    aux=(dun*)malloc(sizeof(dun));
    aux->next=NULL;
    aux->identificador=0;
    aux->funcion=NULL;
    return(aux);
}
//crea una lista de acciones
acciones* crearacciones(){
    acciones* acc;
    acc=(acciones*)malloc(sizeof(acciones));
    acc->head=creardun();
    acc->curr=acc->head;
    acc->tail=acc->head;
    acc->posCurr=1;
    acc->length=1;
    return(acc);
}
//apunta a la accion next
void nextacc(acciones* acc){
    acc->curr=acc->curr->next;
    acc->posCurr++;
}
//lista de acciones inicial
acciones* inicioacciones(){
    acciones* acc;
    acc=crearacciones();
    acc->curr->funcion=&saltar_encima;
    acc->curr->identificador=1;
    acc->head=acc->curr;
    acc->curr->next=creardun();
    nextacc(acc);
    acc->curr->funcion=&caminar_en;
    acc->curr->identificador=2;
    acc->curr->next=creardun();
    nextacc(acc);
    acc->curr->funcion=&taclear_al_frente;
    acc->curr->identificador=3;
    acc->curr->next=creardun();
    nextacc(acc);
    acc->curr->funcion=&ver_plata;
    acc->curr->identificador=5;
    acc->tail=acc->curr;
    acc->length=4;
    return acc;
}
//mueve el curr
void moveracc(acciones* acc,int numero){
    if (numero>acc->length){
        return;
    }
    else{
        acc->curr=acc->head;
        acc->posCurr=1;
        while(acc->posCurr<numero){
            nextacc(acc);
        }       
    }
}
//free dun  
void freedun(dun* d){
    d->funcion=NULL;
    free(d);
}
//borra accion de la lista
void borraraccion(acciones* acc,int ident){
    int cont;
    for(cont=1;acc->length>=cont;cont++){
        moveracc(acc,cont);
        if(acc->curr->identificador==ident){
            dun* aux;
            if(cont==1){
                aux=acc->head;
                acc->curr=acc->curr->next;
                acc->head=acc->curr;
                aux->next=NULL;
                freedun(aux);
                acc->length--;
                return;
            }
            else if(cont==acc->length){
                aux=acc->tail;
                moveracc(acc,cont-1);
                acc->curr->next=NULL;
                acc->tail=acc->curr;
                freedun(aux);
                acc->posCurr--;
                acc->length--;
                return;
            }
            else{
                moveracc(acc,cont-1);
                aux=acc->curr;
                nextacc(acc);
                aux->next=acc->curr->next;
                acc->curr->next=NULL;
                freedun(acc->curr);
                acc->curr=aux->next;
                acc->length--;
                return;
            }
        }
    }
}
//anade accion a la lista por su identificadr
void anadiraccion(acciones* acc,int ident){
    int cont;
    for(cont=1;acc->length>=cont;cont++){
        moveracc(acc,cont);
        if(acc->curr->identificador==ident){
            return;
        }
    }
    if(ident==1){
        dun* aux;
        aux=creardun();
        aux->identificador=1;
        aux->funcion=&saltar_encima;
        acc->tail->next=aux;
        acc->tail=acc->curr=aux;
        acc->posCurr=(acc->length)+1;
        acc->length++;
    }
    else if(ident==4){
        acc->curr=acc->tail;
        acc->tail->next=creardun();
        nextacc(acc);
        acc->curr->funcion=&rushear;
        acc->curr->identificador=4;
        acc->tail=acc->curr;
        acc->length++;
        acc->posCurr=acc->length;
    }
}
//ve que acciones hay que anadir y cuales sacar
void casos(escenario* esc,acciones* acc){
    mover(esc,esc->pospsje);
    if(*(int*)esc->curr->cosa->caracteristica2==3){
        borraraccion(acc,1);
    }
    else{
        anadiraccion(acc,1);
    }
    if(*(int*)esc->curr->cosa->caracteristica2==2){
        anadiraccion(acc,4);
    }
    else{
        borraraccion(acc,4); 
    }
}
//ejecuta las acciones de la lista
void choice(int ident,acciones* acc,escenario* esc){
    int cont;
    moveracc(acc,1);
    for(cont=1;acc->length>=cont;cont++,nextacc(acc)){
        if(acc->curr->identificador==ident){
            printf("HICE FUNCION\n");
            if(acc->curr->identificador==1){
                int salto;
                printf("casillas que desea saltar: ");
                scanf("%d",&salto);
                (acc->curr->funcion)(esc,salto);
                return;
            }
            (acc->curr->funcion)(esc);
            return;
        }
    }
    //si no esta la accion imprime oh no
    printf("OH OH\n");
}
//free acciones
void freeacc(acciones* acc){
    free(acc);
}
//borra posicion de acciones
void borrar_dun(acciones* acc,int i){
    dun* aux;
    moveracc(acc,i);
    if(acc->length<i){
        printf("no esta esa posicion en el escenario\n");
        return;
    }
    else if(acc->length==1){
        freedun(acc->head);
    }
    else if(i==1){
        aux=acc->head;
        acc->curr=acc->curr->next;
        acc->head=acc->curr;
        freedun(aux); 
    }
    else if(i==acc->length){
        aux=acc->tail;
        moveracc(acc,acc->length-1);
        acc->curr->next=NULL;
        acc->tail=acc->curr;
        freedun(aux); 
    }
    else{
        moveracc(acc,acc->length-1);
        aux=acc->curr;
        nextacc(acc);
        aux->next=acc->curr->next;
        acc->curr->next=NULL;
        freedun(acc->curr);
        acc->curr=aux->next;
    }   
    acc->length--;
}
//borra todas las acciones
void borrar_acciones(acciones* acc){
    int comp,comp2;
    comp2=acc->length;
    for(comp=1;comp2>=comp;comp++){
        borrar_dun(acc,1);
    }
    freeacc(acc);
}