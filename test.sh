#!/bin/bash
#Exemple de programme
a=0
b=expr 5 + 5
c=0
#Affiche les variables
set
echo Table de $b
echo ------------

while [ $a lt $b ]
do
	c=expr $a \* $b
	a=expr $a + 1
	echo '$a x $b = $c'
done

expr 10 % 7

if [ $a != $c ]
then
	echo a != c 
fi

#Affiche le fichier
cat main.c

#Liste les fichier
ls

#Nettoye
#clear
