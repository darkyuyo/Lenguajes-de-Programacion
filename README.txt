Alfredo Llanos
201804536-5

Para hacer que corra hay que poner "make run"
1 es la primera casilla de la lista
La primera parte de mi tarea va a ser la creacion del escenario,introducimos el tamaño del escenario que va a partir lleno de pisos y si intentamos superar el largo inicial del mapa nos va a printear "se supera el largo",las funciones que se pueden usar en la creacion del escenario son: anadir_elemento (que te va a pedir la posicion de insertado, el tipo del elemento que se desea añadir y los datos del tipo correspondiente) mostrar(que te pide la posicion que desea mostrar)
mostrar_todo(muestra todo el escenario)
borrar_elemento(pide la posicion que se desea eliminar)
borrar_todo(borra todo el escenario)(no usar uwu)

para continuar a la fase de creacion del personaje ingrese "continue",hago que el personaje siempre remplace a la primera casilla del escenario asi que no dejo que que se modifique la primera casilla(con el borrar_todo me produce problemas esto, haciendo que no pueda añadir nada mas debido a lo anterior dicho,quedando solo el personaje en el escenario)

Para las acciones considere que cuando uno moria con un enemigo o en un agujero infinito la casilla donde esta lo que nos mato se vuelve piso normal y uno vuelve a la primera casilla con estado normal y mantiene la cantidad de monedas

Las acciones que se pueden realizar son:
mostrar
mostrar_todo
saltar_encima(solo se puede si no esta mareado,pide casillas por saltar, si es negativo salta hacia atras)
caminar_en(avanza una casilla a la derecha)
taclear_al_frente(si al frente hay un enemigo lo mata y avanza una casilla, si no hay un enemigo, queda en la misma casilla mareado)
rushear(solo se puede si esta en brillante,avanza 3 hacia adelante si no hay algun agujero infinito en su camino, ignora todo en su camino)
ver_plata(muestra tu plata)

Y la funcion choice nos deja usar las ultimas 4 funciones solamente si es que estan en una lista de acciones, si esta la funcion imprime "HICE FUNCION" y hace la funcion en cambio si no esta imprime "OH NO" y no hace nada





