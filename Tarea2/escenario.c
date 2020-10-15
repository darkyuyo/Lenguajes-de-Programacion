#include "escenario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//crea una casilla vacia
casilla* crearcasilla(){
    casilla* casi;
    casi=(casilla*)malloc(sizeof(casilla));
    casi->cosa=(elemento*)malloc(sizeof(elemento));
    casi->cosa->caracteristica1=casi->cosa->caracteristica2=casi->cosa->caracteristica3=NULL;
    casi->next=NULL;
    casi->tipo=0;
    return(casi);
}
//crea escenario vacio
escenario* crearescena(){
    escenario* mapa;
    mapa=(escenario*)malloc(sizeof(escenario));
    mapa->head=crearcasilla();
    mapa->curr=mapa->head;
    mapa->tail=mapa->head;
    mapa->length=0;
    return(mapa);
}
//mueve el cursor a next
void next(escenario* mapa){
    mapa->curr=mapa->curr->next;
    mapa->posCurr++;
}
//mueve el cursor a la numero
void mover( escenario* mapa,int numero){
    if (numero>mapa->length){
        return;
    }
    else{
        mapa->curr=mapa->head;
        mapa->posCurr=1;
        while(mapa->posCurr<numero){
            next(mapa);
        }       
    }
}
//retrocede el cursor
void prev( escenario* mapa){
    casilla* casi;
    if(mapa->curr==mapa->head){
        printf("No se puede retroceder\n");
        return;
    }
    else{
        casi=mapa->head;
        while(casi->next!=mapa->curr){
            casi=casi->next;
        }
        mapa->curr=casi;
        mapa->posCurr--;
    }
}
//crea un escenario de largo numero con pisos normales
escenario* inicio(int numero){
    escenario* mapa;
    int comp;
    mapa=crearescena();
    mapa->head->tipo=5;
    mapa->curr=mapa->head;
    mapa->tail=mapa->head;
    mapa->curr->cosa->caracteristica1=(int*)malloc(sizeof(int));
    *((int*)mapa->curr->cosa->caracteristica1)=0;
    mapa->curr->cosa->caracteristica2=mapa->curr->cosa->caracteristica3=NULL;
    mapa->length++;
    mapa->posCurr++;
    for(comp=2;numero>=comp;comp++){
        mapa->curr->next=crearcasilla();
        mapa->length++;
        next(mapa);
        mapa->curr->tipo=5;
        mapa->curr->cosa->caracteristica1=(int*)malloc(sizeof(int));
        *((int*)mapa->curr->cosa->caracteristica1)=0;
        mapa->curr->cosa->caracteristica2=mapa->curr->cosa->caracteristica3=NULL;
        mapa->tail=mapa->curr;
    }
    mapa->curr=mapa->head;
    mapa->posCurr=1;
    mapa->pospsje=1;
    mapa->largoini=mapa->length;
    return (mapa);
}
//muestra contenido casilla numero
void mostrar( escenario* mapa,int numero){
    mover(mapa,numero);
    if(numero>mapa->length){
        printf("no esta en el escenario\n");
        return;
    }
    else if(mapa->curr->tipo==1){     
        printf("Personaje:\n");
        printf("nombre: %s\n",(char*)mapa->curr->cosa->caracteristica1);
        if(*((int*)mapa->curr->cosa->caracteristica2)==1){
            printf("estado: normal\n");
        }
        else if(*((int*)mapa->curr->cosa->caracteristica2)==2){
            printf("estado: brillante\n");
        }
        else if(*((int*)mapa->curr->cosa->caracteristica2)==3){
            printf("estado: mareado\n");
        }
        else if(*((int*)mapa->curr->cosa->caracteristica2)==4){
            printf("estado: wario\n");
        }
        else{
            printf("No tiene Estado\n");
        }
        printf("cantidad de monedas:%d\n",*((int*)mapa->curr->cosa->caracteristica3));
    }
    else if(mapa->curr->tipo==2){
        printf("Objeto:\n");
        printf("nombre: %s\n",(char*)mapa->curr->cosa->caracteristica1);
        if(*(int*)mapa->curr->cosa->caracteristica2==1){
            printf("estado que otorga: health\n");
        }
        else if(*(int*)mapa->curr->cosa->caracteristica2==2){
            printf("estado que otorga: mareado\n");
        }
        else if(*(int*)mapa->curr->cosa->caracteristica2==3){
            printf("estado que otorga: wario\n");
        }
        else if(*(int*)mapa->curr->cosa->caracteristica2==4){
            printf("estado que otorga: brillante\n");
        }
        else{
            printf("No tiene estado");
        }
    }
    else if(mapa->curr->tipo==3){
        printf("Enemigo:\n");
        printf("nombre: %s\n",(char*)mapa->curr->cosa->caracteristica1);
    }
    else if(mapa->curr->tipo==4){
        if(*(int*)mapa->curr->cosa->caracteristica2==0){
            printf("contenido del bloque: %d\n",*(int*)mapa->curr->cosa->caracteristica1);
            printf("tipo que almacena: monedas\n");
        }
        else if(*(int*)mapa->curr->cosa->caracteristica2==1){
            printf("Nombre: %s\n",(char*)mapa->curr->cosa->caracteristica1);
            if(*(int*)mapa->curr->cosa->caracteristica2==1){
                printf("estado que otorga: health\n");
            }
            else if(*(int*)mapa->curr->cosa->caracteristica2==2){
                printf("estado que otorga: mareado\n");
            }
            else if(*(int*)mapa->curr->cosa->caracteristica2==3){
                printf("estado que otorga: wario\n");
            }
            else if(*(int*)mapa->curr->cosa->caracteristica2==4){
                printf("estado que otorga: brillante\n");
            }
            else{
                printf("No tiene estado");
            }
        }
        else{
            printf("bloque malo\n");
        }
    }
    else if(mapa->curr->tipo==5){
        printf("Suelo:\n");
        if(*(int*)mapa->curr->cosa->caracteristica1==0){
            printf("piso firme\n");
        }
        else if(*(int*)mapa->curr->cosa->caracteristica1==1){
            printf("agujero infinito\n");
        }
        else{
            printf("piso malo\n");
        }
    }
    else{
        printf("tipo malo\n");
    }
}
//muestra todo el escenario
void mostrar_todo( escenario* mapa){
    int comp;
    for(comp=1;mapa->length>=comp;comp++){
        mostrar(mapa,comp);
    }
}
//añade una casilla con elementos en posicion i
void anadir_elementos(escenario* esc, elemento* ele,int i,int tipo){
    casilla* aux;
    aux=crearcasilla();
    aux->tipo=tipo;
    aux->cosa=ele;
    mover(esc,i);
    if(esc->length>=esc->largoini){
        printf("supera el largo inicial del mapa\n");
        return;
    }
    else if(i>esc->length+1){
        return;
    }
    else if(i==1){
        aux->next=esc->head;
        esc->head=esc->curr=aux;
    }
    else if(i==esc->length+1){
        esc->curr=esc->tail;
        esc->tail->next=aux;
        esc->tail=esc->curr=aux;
        esc->posCurr=(esc->length)+1;
    }
    else{
        aux->next=esc->curr;
        prev(esc);
        esc->curr->next=aux;
        next(esc);
    }
    esc->length++;
}
//libera el escenario
void freeesc( escenario* esc){
    free(esc);
}
//libera caracteristicas de la cosa y luego la casilla
void freecasi( casilla* casi){
    if(casi->tipo==1 ||((casi->tipo==4) && (*(int*)casi->cosa->caracteristica2)==1)){
        free(casi->cosa->caracteristica1);
        free(casi->cosa->caracteristica2);
        free(casi->cosa->caracteristica3);
    }
    else if(casi->tipo==2 ||((casi->tipo==4) && (*(int*)casi->cosa->caracteristica2)==0)){
        free(casi->cosa->caracteristica1);
        free(casi->cosa->caracteristica2);
    }
    else if(casi->tipo==2 || casi->tipo==5){
        free(casi->cosa->caracteristica1);
    }
    free(casi->cosa);
    free(casi);
}
//borra elemento en posicion i
void borrar_elemento( escenario* esc,int i){
    casilla* aux;
    mover(esc,i);
    if(esc->length<i){
        printf("no esta esa posicion en el escenario\n");
        return;
    }
    else if(esc->length==1){
        freecasi(esc->head);
    }
    else if(i==1){
        aux=esc->head;
        esc->curr=esc->curr->next;
        esc->head=esc->curr;
        freecasi(aux); 
    }
    else if(i==esc->length){
        aux=esc->tail;
        prev(esc);
        esc->curr->next=NULL;
        esc->tail=esc->curr;
        freecasi(aux); 
    }
    else{
        prev(esc);
        aux=esc->curr;
        next(esc);
        aux->next=esc->curr->next;
        esc->curr->next=NULL;
        freecasi(esc->curr);
        esc->curr=aux->next;
    }   
    esc->length--;
}
//borra todas las casillas
void borrar_todo( escenario* esc){
    int comp,comp2;
    comp2=esc->length;
    for(comp=1;comp2>=comp;comp++){
        borrar_elemento(esc,1);
    }
}
//para crear personaje en posicion pos
void crearpersonaje(escenario* esc){
    elemento* aux;
    borrar_elemento(esc,1);
    aux=(elemento*)malloc(sizeof(elemento));
    aux->caracteristica1=(char*)malloc(sizeof(char)*100);
    aux->caracteristica2=(int*)malloc(sizeof(int));
    aux->caracteristica3=(int*)malloc(sizeof(int));
    printf("Nombre: ");
    scanf("%s",((char*)aux->caracteristica1));
    *((int*)aux->caracteristica2)=1;
    *((int*)aux->caracteristica3)=0;
    anadir_elementos(esc,aux,1,1);
}
//para crear objeto en posicion pos
void crearobjeto(escenario* esc,int pos){
    elemento* aux;
    aux=(elemento*)malloc(sizeof(elemento));
    aux->caracteristica1=(char*)malloc(sizeof(char)*100);
    aux->caracteristica2=(int*)malloc(sizeof(int));
    printf("Nombre objeto: ");
    scanf("%s",(char*)aux->caracteristica1);
    printf("Estado: ");
    scanf("%d",((int*)aux->caracteristica2));
    anadir_elementos(esc,aux,pos,2);
}
//para crear enemigo en posicion pos
void crearenemigo(escenario* esc,int pos){
    elemento* aux;
    aux=(elemento*)malloc(sizeof(elemento));
    aux->caracteristica1=(char*)malloc(sizeof(char)*100);
    printf("Nombre: ");
    scanf("%s",(char*)aux->caracteristica1);
    anadir_elementos(esc,aux,pos,3);
}
//para crear bloque en posicion pos
void crearbloque(escenario* esc,int pos){
    elemento* aux;
    aux=(elemento*)malloc(sizeof(elemento));
    aux->caracteristica2=(int*)malloc(sizeof(int));
    printf("Tipo que almacena: ");
    scanf("%d",((int*)aux->caracteristica2));
    if(*((int*)aux->caracteristica2)==0){
        aux->caracteristica1=(int*)malloc(sizeof(int));
        printf("Cantidad de monedas ");
        scanf("%d",((int*)aux->caracteristica1));
        anadir_elementos(esc,aux,pos,4);
    }
    else if(*((int*)aux->caracteristica2)==1){
        aux->caracteristica1=(char*)malloc(sizeof(char)*100);
        aux->caracteristica3=(int*)malloc(sizeof(int));
        printf("Nombre objeto: ");
        scanf("%s",(char*)aux->caracteristica1);
        printf("Estado: ");
        scanf("%d",((int*)aux->caracteristica3));
        anadir_elementos(esc,aux,pos,4);
    }
    else{
        printf("bloque invalido\n");
    }
}
//para crear piso en posicion pos
void crearpiso(escenario* esc,int pos){
    elemento* aux;
    aux=(elemento*)malloc(sizeof(elemento));
    aux->caracteristica1=(int*)malloc(sizeof(int));
    printf("Firme o agujero: ");
    scanf("%d",((int*)aux->caracteristica1));
    anadir_elementos(esc,aux,pos,5);
}
//crea piso normal en posicion pos
void crearpisonormal(escenario* esc,int pos){
    elemento* aux;
    borrar_elemento(esc,pos);
    aux=(elemento*)malloc(sizeof(elemento));
    aux->caracteristica1=(int*)malloc(sizeof(int));
    (*(int*)aux->caracteristica1)=0;
    anadir_elementos(esc,aux,pos,5);
}