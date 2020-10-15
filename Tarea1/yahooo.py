import re
start=re.compile(r"Start Game\n?")
over=re.compile(r"Game Over\n?")
add=re.compile(r"Add Player (?P<name>[A-Za-z][A-Za-z\d]*)\n?")
took=re.compile(r"(?P<name>[A-Za-z][A-Za-z\d]*) took (?P<valor>-?[\d]*)\n?")
power=re.compile(r"(?P<name>[A-Za-z][A-Za-z\d]*) needs a power up\n?")
show=re.compile(r"show (?P<variable>[A-Za-z][A-Za-z\d]*|-?[\d]*)\n?")
jump=re.compile(r"(?P<name>[A-Za-z][A-Za-z\d]*) jumps to (?P<math>\S+)\n?")
#el conditional no sabe si el valor logico es aceptable
conditional=re.compile(r"It's a me a conditional (?P<logic>\S+) Yahoo\n?")
mamma=re.compile(r"Mama Mia...\n?")
let=re.compile(r"Let's Go!\n?")
#el conditional no sabe si el valor es aceptable
ciclo=re.compile(r"YA MA (?P<logic>\S) YAHOO!\n?")
finciclo=re.compile("AH HA!\n?")
secret=re.compile(r"Secret Level (?P<funcion>[A-Za-z]+) (?P<parametros>[A-Za-z][A-Za-z\d]*|\d+)(-[A-Za-z][A-Za-z\d]*|-\d+)*\n?")
retu=re.compile(r"Return to Level (?P<valor>[A-Za-z][A-Za-z\d]*|\d+)\n?")
llama=re.compile(r"(?P<name>[A-Za-z][A-Za-z\d]*) enters (?P<funcion>[A-Za-z]+) (?P<parametros>[A-Za-z][A-Za-z\d]*|\d+)(-[A-Za-z][A-Za-z\d]*|-\d+)*\n?")
#si hay error entrega False y printea los errores y entrega True si no tiene errores, su parametro es el archivod de yahoo
def verificar(arch):
    #cantidad errores
    error=0
    cont1=0
    lineas=arch.readlines()
    lineantes=0
    lisantes=[]
    listades=[]        
    lineadesp=0
    cont1=-1
    flagsecret=False
    flagcond=False
    flagmamma=False
    #lista de ciclos
    cic=[]
    #lista de cosas dentro de secret level
    listsec=[]
    #lista de cosas dentro del if
    listif=[]
    #lista de lineas antes del Start Game
    while start.fullmatch(lineas[lineantes])==None:
        lisantes.append(lineas[lineantes])
        lineantes+=1
        #verificamos que haya Start Game
        if lineantes>=len(lineas):
            print(lisantes)
            return
    #lista de lineas despues del Game Over
    while over.fullmatch(lineas[cont1])==None:
        listades.append(lineas[cont1])
        lineadesp+=1
        cont1-=1
        #verificamos que haya Game Over
        if lineadesp>=len(lineas):
            print(listades.reverse())
            return
    #revertimos lista porque la guardamos al reves
    listades.reverse()
    #Vemos si hay errores antes del Start Game si es que no esta vacio
    if lisantes!=[]:
        for lineacomp in lisantes:
            #si flagsecret es false solo puede haber un secret level
            if flagsecret==False:
                if secret.fullmatch(lineacomp):
                    flagsecret=True
                    listsec.append(lineacomp)
                    continue
                else:
                    error+=1
                    print("woooooooohhh!",error,":",lineacomp)
                    continue
            else:
                if ciclo.fullmatch(lineacomp):
                    #añadimos a la lista la linea de inicio del ciclo
                    cic.append(lineacomp)
                    #añadimos siempre que no sea error la linea a listsec
                    listsec.append(lineacomp)
                    continue
                elif finciclo.fullmatch(lineacomp):
                    #si len=0 significa que no se comenzo un ciclo antes
                    if len(cic)>0:
                        #sacamos el ultimo ciclo añadido a la lista
                        cic.pop()
                        listsec.append(lineacomp)
                        continue
                    else:
                       error+=1
                       print("woooooooohhh!",error,":",lineacomp)
                       continue
                elif retu.fullmatch(lineacomp):
                    #si llego hasta aqui es porque habia un flagsecret abierto, cerramos el flag y reiniciamos la lista de listsec
                    flagsecret=False
                    listsec=[]
                    continue
                elif conditional.fullmatch(lineacomp):
                    #empezamos un conditional
                    if flagcond==False and flagmamma==False:
                        #añadimos la linea a listif
                        listif.append(lineacomp)
                        flagcond=True
                        listsec.append(lineacomp)
                        continue
                    else:
                        error+=1
                        print("woooooooohhh!",error,":",lineacomp)
                        continue
                elif mamma.fullmatch(lineacomp):
                    #flags para verificar
                    if flagcond==True and flagmamma==False:
                        listif.append(lineacomp)
                        flagmamma=True
                        listsec.append(lineacomp)
                        continue
                    else:
                        error+=1
                        print("woooooooohhh!",error,":",lineacomp)
                        continue
                elif let.fullmatch(lineacomp):
                    if flagcond==True and flagmamma==True:
                        #reiniciamos flags y listas
                        flagcond=False
                        flagmamma=False
                        listsec.append(lineacomp)
                        listif=[]
                        continue
                    else:
                        error+=1
                        print("woooooooohhh!",error,":",lineacomp)
                        continue
                elif add.fullmatch(lineacomp):
                    #si esta abierta la flagcond, la linea se agrega a listif
                    if flagcond==True:
                        listif.append(lineacomp)
                    listsec.append(lineacomp)
                    continue
                elif took.fullmatch(lineacomp):
                    if flagcond==True:
                        listif.append(lineacomp)
                    listsec.append(lineacomp)
                    continue
                elif power.fullmatch(lineacomp):
                    if flagcond==True:
                        listif.append(lineacomp)
                    listsec.append(lineacomp)
                    continue
                elif show.fullmatch(lineacomp):
                    if flagcond==True:
                        listif.append(lineacomp)
                    listsec.append(lineacomp)
                    continue
                elif jump.fullmatch(lineacomp):
                    #verificamos que la definicion matematica este correcta
                    if mathexp(jump.fullmatch(lineacomp).group("math")):
                        if flagcond==True:
                            listif.append(lineacomp)
                        listsec.append(lineacomp)
                        continue
                    else:
                        error+=1
                        print("woooooooohhh!",error,":",lineacomp)
                        continue
                else:
                    #no es algo reconocible
                    error+=1
                    print("woooooooohhh!",error,":",lineacomp)
                    continue
    #si no cerramos el secret level imprime lo que habia adentro
    if flagsecret==True:
        for lineacomp in listsec:
            print("woooooooohhh!",error,":",lineacomp)
    #si no cerramos los ciclos imprime los inicios de ciclos sin cerraar
    if len(cic)>0:
        for lineacomp in cic:
            error+=1
            print("woooooooohhh!",error,":",lineacomp)  
    #si no cerramos el if imprime lo de denttro del if 
    if len(listif)>0:
        for lineacomp in listif:
            error+=1
            print("woooooooohhh!",error,":",lineacomp) 
    #se repite casi lo mismo en los demas
    #Reiniciamos los flags
    flagsecret=False
    flagcond=False
    flagmamma=False
    cic=[]
    listif=[]
    #verificamos los errores entre Start y Over
    for lineacomp in lineas[lineantes+1:cont1]:
        if ciclo.fullmatch(lineacomp):
                    cic.append(lineacomp)
                    continue
        elif finciclo.fullmatch(lineacomp):
            if len(cic)>0:
                cic.pop()
                continue
            else:
                    error+=1
                    print("woooooooohhh! ",error,":",lineacomp)
                    continue
        elif conditional.fullmatch(lineacomp):
            if flagcond==False:
                listif.append(lineacomp)
                flagcond=True
                continue
            else:
                error+=1
                print("woooooooohhh!",error,":",lineacomp)
                continue
        elif mamma.fullmatch(lineacomp):
            if flagcond==True and flagmamma==False:
                listif.append(lineacomp)
                flagmamma=True
                continue
            else:
                error+=1
                print("woooooooohhh!",error,":",lineacomp)
                continue
        elif let.fullmatch(lineacomp):
            if flagcond==True and flagmamma==True:
                listif.append(lineacomp)
                flagcond=False
                flagmamma=False
                listif=[]
                continue
            else:
                error+=1
                print("woooooooohhh!",error,":",lineacomp)
                continue
        elif add.fullmatch(lineacomp):
            if flagcond==True:
                listif.append(lineacomp)
            continue
        elif took.fullmatch(lineacomp):
            if flagcond==True:
                listif.append(lineacomp)
            continue
        elif power.fullmatch(lineacomp):
            if flagcond==True:
                listif.append(lineacomp)
            continue
        elif show.fullmatch(lineacomp):
            if flagcond==True:
                listif.append(lineacomp)
            continue
        elif llama.fullmatch(lineacomp):
            if flagcond==True:
                listif.append(lineacomp)
            continue
        elif jump.fullmatch(lineacomp):
            if mathexp(jump.fullmatch(lineacomp).group("math")): 
                if flagcond==True:
                    listif.append(lineacomp)
                continue
            else:
                error+=1
                print("woooooooohhh!",error,":",lineacomp)
                continue
        else:
            error+=1
            print("woooooooohhh!",error,":",lineacomp)
            continue
    if len(cic)>0:
        for lineacomp in cic:
            error+=1
            print("woooooooohhh!",error,":",lineacomp)
    if len(listif)>0:
        for lineacomp in listif:
            error+=1
            print("woooooooohhh!",error,":",lineacomp) 
    #reiniciamos nuevamente los flags
    flagsecret=False
    flagcond=False
    flagmamma=False
    cic=[]
    listsec=[]
    listif=[]
    #Despues del Game Over
    if listades!=[]:
        for lineacomp in listades:
            if flagsecret==False:
                if secret.fullmatch(lineacomp):
                    flagsecret=True
                    listsec.append(lineacomp)
                    continue
                else:
                    error+=1
                    print("woooooooohhh!",error,":",lineacomp)
                    continue
            else:
                if ciclo.fullmatch(lineacomp):
                    cic.append(lineacomp)
                    listsec.append(lineacomp)
                    continue
                elif finciclo.fullmatch(lineacomp):
                    if len(cic)>0:
                        cic.pop()
                        listsec.append(lineacomp)
                        continue
                    else:
                       error+=1
                       print("woooooooohhh!",error,":",lineacomp)
                       continue
                elif retu.fullmatch(lineacomp):
                    flagsecret=False
                    listsec=[]
                    continue
                elif conditional.fullmatch(lineacomp):
                    if flagcond==False and flagmamma==False:
                        listif.append(lineacomp)
                        flagcond=True
                        listsec.append(lineacomp)
                        continue
                    else:
                        error+=1
                        print("woooooooohhh!",error,":",lineacomp)
                        continue
                elif mamma.fullmatch(lineacomp):
                    if flagcond==True and flagmamma==False:
                        listif.append(lineacomp)
                        flagmamma=True
                        listsec.append(lineacomp)
                        continue
                    else:
                        error+=1
                        print("woooooooohhh!",error,":",lineacomp)
                        continue
                elif let.fullmatch(lineacomp):
                    if flagcond==True and flagmamma==True:
                        flagcond=False
                        flagmamma=False
                        listsec.append(lineacomp)
                        listif=[]
                        continue
                    else:
                        error+=1
                        print("woooooooohhh!",error,":",lineacomp)
                        continue
                elif add.fullmatch(lineacomp):
                    if flagcond==True:
                        listif.append(lineacomp)
                    listsec.append(lineacomp)
                    continue
                elif took.fullmatch(lineacomp):
                    if flagcond==True:
                        listif.append(lineacomp)
                    listsec.append(lineacomp)
                    continue
                elif power.fullmatch(lineacomp):
                    if flagcond==True:
                        listif.append(lineacomp)
                    listsec.append(lineacomp)
                    continue
                elif show.fullmatch(lineacomp):
                    if flagcond==True:
                        listif.append(lineacomp)
                    listsec.append(lineacomp)
                    continue
                elif jump.fullmatch(lineacomp):
                    if mathexp(jump.fullmatch(lineacomp).group("math")):
                        if flagcond==True:
                            listif.append(lineacomp)
                        listsec.append(lineacomp)
                        continue
                    else:
                        error+=1
                        print("woooooooohhh!",error,":",lineacomp)
                        continue
                else:
                    error+=1
                    print("woooooooohhh!",error,":",lineacomp)
                    continue
    if flagsecret==True:
        for lineacomp in listsec:
            print("woooooooohhh!",error,":",lineacomp)
    if len(cic)>0:
        for lineacomp in cic:
            error+=1
            print("woooooooohhh!",error,":",lineacomp)   
    if len(listif)>0:
        for lineacomp in listif:
            error+=1
            print("woooooooohhh!",error,":",lineacomp) 
    #Si no hay errores devuelve True
    if error==0:
        return True
    else:
        return False
    #ejecutamos la funcion
def ejecutar(arch):
    #diccionario con jugadores
    players={}
    for linea in arch:
        if add.fullmatch(linea):
            #añadimos player al diccionario pero sin valor
            players[add.fullmatch(linea).group("name")]=None
            continue
        elif took.fullmatch(linea):
            #asignamos valor a name
            players[took.fullmatch(linea).group("name")]=took.fullmatch(linea).group("valor")
            continue
        elif power.fullmatch(linea):
            #pide numero por comando
            comando = input("> ")
            players[power.fullmatch(linea).group("name")]=comando
            continue
        elif show.fullmatch(linea):
            #muestra el valor de la variable si es player y si no muestra el numero
            x=show.fullmatch(linea).group("variable") 
            if x in players:
                print(players[x])
            else:
                print(x)
            continue
        else:
            continue
    return
#nos retorna false si la expresion matematica es mala y true si es correcta, acepta como parametro la operacion matematica
def mathexp(str):
    #cuenta los ( abiertos
    contpare=0
    #cuando hubo un )
    flagcierre=True
    #cuando hubo un operador
    flagcont=False
    for letra in str:
        if contpare==0:
            #si contpare es 0 solo puede venir un (
            if letra=="(":
                contpare+=1
                continue
            else:
                return False
        else:
            if letra=="(":
                contpare+=1
                continue
            elif letra==")":
                #verificamos que hay un operador entre el parentesis y que haya un ( abierto
                if flagcont==True and contpare>0:
                    #se cierra un ( por eso restamos 1
                    contpare-=1
                    flagcierre=True
                    flagcont=False
                    continue
                else:
                    return False
            elif letra in ("+-/*"):
                #verificamos que no hubo un operador en ese parentesis
                if flagcont==False and flagcierre==True:
                    flagcont=True
                    flagcierre=False
                    continue
                else:
                    return False
            elif letra in ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"):
                continue
            else:
                return False
    #si quedo un ( abierto hubo un error
    if contpare>0:
        return False
    return True
archivo=open("yahooo.txt","r")
archivo2=open("yahooo.txt","r")
#si verificar es true, entonces no hubieron errores y ejecutamos el archivo
if verificar(archivo):
    ejecutar(archivo2)
archivo.close()
archivo2.close()


    


