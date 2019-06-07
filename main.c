#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototype.h"
#define FICHIER "test.sh"

int main(int argc, char *argv[]){
	liste a;
	a=(liste)malloc(sizeof(noeud_t));
	if(argc >1){ //Si on met un argument apres l'executable.
		lecture(a,0,argv[1]); //Alors l'argument apres l'executable est le nom du fichier.
	}
	else
		lecture(a,0,FICHIER); //Sinon on ouvre le fichier par default definie dans le DEFINE.
	return 0;
}
