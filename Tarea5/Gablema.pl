arcos(s,c,1).
arcos(s,g,4).
arcos(c,i,1).
arcos(c,f,8).
arcos(i,f,5).
arcos(i,e,2).
arcos(g,i,1).
arcos(g,d,13).
arcos(d,j,7).
arcos(j,e,1).
arcos(f,e,2).

camino(De,Hasta,Costo):-arcos(De,Hasta,Costo).

camino(De,Hasta,Costo):-arcos(De,Int,C),camino(Int,Hasta,Valor),Costo is C+Valor.

todos(X,Y,L):-todos(X,Y,[],L),!.

todos(X,Y,Temp,L):-camino(X,Y,P),not(member(P,Temp)),append([P],Temp,Temp2),todos(X,Y,Temp2,L).

todos(_,_,Temp,Temp).
%todos me hace una lista con el valor de todos los caminos
vida(V,M,Limite,[Actual|Resto]):-Actual>Limite,vida(V2,M,Limite,Resto),V is V2+1.
vida(V,M,Limite,[Actual|Resto]):-Actual<Limite,vida(V,M2,Limite,Resto),M is M2+1.
vida(V,M,Limite,[Actual|Resto]):-Actual=Limite,vida(V2,M,Limite,Resto),V is V2+1.
vida(0,0,_,_).
%vida me suma los contadores de V y M dependiendo de la lista que tira todos
suenopeligroso(Lim,V,M,De,Hasta):-todos(De,Hasta,Lista),vida(V,M,Lim,Lista).
