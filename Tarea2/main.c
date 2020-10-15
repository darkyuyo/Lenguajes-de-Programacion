#include "acciones.h"
#include "escenario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//selecionar escenario main
void funmain(escenario* esc){
    char* linea;
    int tipo,pos;
    linea=(char*)malloc(sizeof(char)*100);
    printf("ingrese una funcion, para continuar ingrese 'continue': ");
    scanf("%s",linea);
    if((strcmp(linea,"anadir_elemento")==0)){
        printf("inserte el tipo: ");
        scanf("%d",&tipo);
        if (tipo==1){
            printf("crear personaje despues de crear escenario\n");
        }
        else if(tipo==2){
            printf("Ingresar posicion: ");
            scanf("%d",&pos);
            if(pos==1){
                printf("Solo personaje en primera casilla\n");
            }
            else{
            crearobjeto(esc,pos);
            }
        }
        else if(tipo==3){
            printf("Ingresar posicion: ");
            scanf("%d",&pos);
            if(pos==1){
                printf("Solo personaje en primera casilla\n");
            }
            else{
                crearenemigo(esc,pos);
            }
        }
        else if(tipo==4){
            printf("Ingresar posicion: ");
            scanf("%d",&pos);
            if(pos==1){
                printf("Solo personaje en primera casilla\n");
            }
            else{
                crearbloque(esc,pos);
            }
        }
        else if(tipo==5){
            printf("Ingresar posicion: ");
            scanf("%d",&pos);
            if(pos==1){
                printf("Solo personaje en primera casilla\n");
            }
            else{
                crearpiso(esc,pos);
            }
        }
    }
    else if((strcmp(linea,"mostrar")==0)){
        printf("Ingresar posicion: ");
        scanf("%d",&pos);
        mostrar(esc,pos);
    }
    else if((strcmp(linea,"mostrar_todo")==0)){
        mostrar_todo(esc);
    }
    else if((strcmp(linea,"borrar_elemento")==0)){
        printf("Ingresar posicion: ");
        scanf("%d",&pos);
        borrar_elemento(esc,pos);
    }
    else if((strcmp(linea,"borrar_todo")==0)){
        borrar_todo(esc);
    }
    while(strcmp(linea,"continue")!=0){
        printf("ingrese una funcion, para continuar ingrese 'continue': ");
        scanf("%s",linea);
        if((strcmp(linea,"anadir_elemento")==0)){
            printf("inserte el tipo: ");
            scanf("%d",&tipo);
            if (tipo==1){
            printf("crear personaje despues de crear escenario\n");
            }
            else if(tipo==2){
                printf("Ingresar posicion: ");
                scanf("%d",&pos);
                if(pos==1){
                    printf("Solo personaje en primera casilla\n");
                }
                else{
                crearobjeto(esc,pos);
                }
            }
            else if(tipo==3){
                printf("Ingresar posicion: ");
                scanf("%d",&pos);
                if(pos==1){
                    printf("Solo personaje en primera casilla\n");
                }
                else{
                crearenemigo(esc,pos);
                }
            }
            else if(tipo==4){
                printf("Ingresar posicion: ");
                scanf("%d",&pos);
                if(pos==1){
                    printf("Solo personaje en primera casilla\n");
                }
                else{
                crearbloque(esc,pos);
                }
            }
            else if(tipo==5){
            printf("Ingresar posicion: ");
            scanf("%d",&pos);
                if(pos==1){
                    printf("Solo personaje en primera casilla\n");
                }
                else{
                    crearpiso(esc,pos);
                }
        }
    }
        else if((strcmp(linea,"mostrar")==0)){
            printf("Ingresar posicion: ");
            scanf("%d",&pos);
            mostrar(esc,pos);
        }
        else if((strcmp(linea,"mostrar_todo")==0)){
            mostrar_todo(esc);
        }
        else if((strcmp(linea,"borrar_elemento")==0)){
            printf("Ingresar posicion: ");
            scanf("%d",&pos);
            borrar_elemento(esc,pos);
        }
        else if((strcmp(linea,"borrar_todo")==0)){
            borrar_todo(esc);
        }
        
    }
crearpersonaje(esc);
}
//funcion ara elegir acciones
void funmain2(escenario* esc,acciones* acc){
    char* linea;  
    linea=(char*)malloc(sizeof(char)*100);
    while(esc->largoini!=0){
       printf("ingrese una funcion: ");
       scanf("%s",linea);
       if((strcmp(linea,"mostrar_todo")==0)){
           mostrar_todo(esc);
        }
        else if((strcmp(linea,"mostrar")==0)){
            int pos;
            printf("Ingresar posicion: ");
            scanf("%d",&pos);
            mostrar(esc,pos);
        }
        else if((strcmp(linea,"saltar_encima")==0)){
            choice(1,acc,esc);
        }
        else if((strcmp(linea,"caminar_en")==0)){
            choice(2,acc,esc);
        }
        else if((strcmp(linea,"taclear_al_frente")==0)){
            choice(3,acc,esc);
        }
        else if((strcmp(linea,"rushear")==0)){
            choice(4,acc,esc);
        }
        else if((strcmp(linea,"ver_plata")==0)){
            choice(5,acc,esc);
        }
        casos(esc,acc);
    }  
}
//borra acciones y escenario
void borrar_final(escenario* esc,acciones* acc){
    borrar_acciones(acc);
    borrar_todo(esc);
    freeesc(esc);
}
int main(){
    int tamano; 
    struct escenario* escena;
    struct acciones* acc;
    printf("Introduzca tamaño: ");
    scanf("%d", &tamano);
    escena=inicio(tamano);
    funmain(escena);
    acc=inicioacciones();
    printf("Ahora introduzca las acciones\n");
    funmain2(escena,acc);
    borrar_final(escena,acc);
    return 0;
}