#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototype.h"

/*Fonction qui parcour le fichier ligne par ligne, appelle les fonction pour executer la ligne en question*/
void lecture(liste a,int nbligne, char* nom){
	FILE* fichier = NULL;
	char* ligne;
	int i,cpt;
	i=0;
	cpt=0;
	liste p;
	p=a;
	vect b,c;
	fichier = fopen(nom, "r");
	if(fichier != NULL){
		ligne = (char*) malloc(sizeof(char)*100);
    	while(fgets(ligne, 100, fichier) != NULL){
    		cpt++;
    		if(nbligne<cpt){
    			if(ligne[i]!='#'){			//Vérifie si la ligne est un commentaire.
					if(strcmp(condition(nom,ligne).tab,"")){ //Si il y a une condition sur la ligne
						//printf("ok");
						exe_condition(cpt,condition(nom,ligne),ligne, a,nom); //fonction qui execute la condition
						return;
					}
					else{
						//parcourl(a);
						expr(nom,ligne,a,p);
						set(a,ligne);
						ls(ligne);
						clear(ligne);
						cat(ligne);
						echo(nom, ligne,a,p);
						b=variable(nom, ligne);
						c=valeur(nom, ligne,a,p);
						if(strstr(ligne,c.tab)){
						//printf("%s %s",b.tab,c.tab);
							insert(a, liste_variable(b,c),p);
						//parcourl(a);
						//printf("\n");
						}
						else if(!strstr(ligne,c.tab) && strstr(ligne,b.tab)){
							insert(a, liste_variable(b,c),p);
						}
					}
				}
			}
     	}
     	free(ligne);
     	free(p);
     	//parcourl(a);
    }
    else
    	printf("Impossible d'ouvrir le fichier \"%s\".\n",nom);
}

parcourt lecture_condition(int nbligne, char* nom, liste a){
FILE* fichier = NULL;
	char* ligne;
	int i;
	parcourt e;
	i=0;
	e.cpt=0;
	liste p,aux;
	p=a;
	aux=(liste)malloc(sizeof(noeud_t));
	aux=a;
	vect b,c;
	fichier = fopen(nom, "r");
	if(fichier != NULL){
		ligne = (char*) malloc(sizeof(char)*100);
    	while(fgets(ligne, 100, fichier) != NULL){
    		e.cpt++;
    		if(nbligne<e.cpt){
    			if(strstr(ligne,"fi") || strstr(ligne,"done")){
    				//printf("ok\n");
    				e.a=aux;
    				return e;
    			}
    			if(ligne[i]!='#'){			//Vérifie si la ligne est un commentaire.
					//parcourl(a);
					expr(nom,ligne,a,p);
					set(a,ligne);
					ls(ligne);
					clear(ligne);
					cat(ligne);
					echo(nom, ligne,aux,p);
					b=variable(nom, ligne);
					c=valeur(nom, ligne,aux,p);
					//printf("ici%s %s\n",b.tab,c.tab);
					if(strstr(ligne,c.tab)){
						insert(aux, liste_variable(b,c),p);
					//parcourl(a);
					//printf("\n");
					}
					else if(!strstr(ligne,c.tab) && strstr(ligne,b.tab)){
							insert(a, liste_variable(b,c),p);
						}
				}
			}	
     	}
		free(ligne);
     	free(p);
    }
  	else
 		printf("Impossible d'ouvrir le fichier \"%s\".\n",nom);
}
/*Fonction expr du shell*/
char* expr (char* nom ,char *ligne, liste a, liste p){ //NE PREND PAS L'ORDRE DES PRIORITéS DES SIGNES!
	int i,j,k,l,r;
	r = 0;
	char* variable;
	char* condition;
	int* valeur;
	l=-1;
	for(i=0; i<100; i++){
		if(ligne[i]=='e' && ligne[i+1]=='x' && ligne[i+2]=='p' && ligne[i+3]=='r' && ligne[i+4]==' ')
		{
			condition=(char*)malloc(sizeof(char)*100);
			valeur=(int*)malloc(sizeof(int)*100);
			i=i+5;
			j=-1;
			while(ligne[i]){
   				if(ligne[i]=='$'){ //retourne la valeur de la variable
   	 				i++;
   	 				j++;
   	 				k=0;
   	 				variable=(char*)malloc(sizeof(char)*100);
   	 				while(ligne[i] != ' '){
   	 					if(ligne[i]=='\n' || ligne[i]==EOF)
   	 						break;
   	 					variable[k]=ligne[i];
   	 					i++;
   	 					k++;
   	 				}
   	 				valeur[j]=s2i(search(a,p,variable));
   	 				free(variable);
   	 			}
   	 			else if(ligne[i]==' '){
   	 				i++;
   	 			}
	   	   		else if (ligne[i]== '+'){
	   	   			l++;
					condition[l]='+';
					i++;
		 		}
		 		else if (ligne[i]== '-'){
	   	   			l++;
					condition[l]='-';
					i++;
		 		}
		 		else if (ligne[i]== '/'){
	   	   			l++;
					condition[l]='/';
					i++;
		 		}
		 		else if (ligne[i]== '\\' && ligne[i+1]=='*'){
	   	   			l++;
					condition[l]='*';
					i+=2;
		 		}
		 		else if (ligne[i]== '%'){
	   	   			l++;
					condition[l]='%';
					i++;
		 		}
		 		else if(ligne[i]=='\n' || ligne[i]==EOF)
	   	   			break;
	   	   		else{
	   	   			j++;
	   	   			k=0;
   	 				variable=(char*)malloc(sizeof(char)*100);
   	 				while(ligne[i] != ' '){
   	 					if(ligne[i]=='\n' || ligne[i]==EOF)
   	 						break;
   	 					variable[k]=ligne[i];
   	 					i++;
   	 					k++;
   	 				}
   	 				valeur[j]=s2i(variable);
   	 				free(variable);
	   	   		}
		 	}
		 	//printf("Les valeurs sont:\n");
		 	for(i=0; i<j+1; i++){
		 		//printf("%d\n", valeur[i]);
		 	}
		 	//printf("Les opérateurs sont:\n");
		 	for(i=0; i<l+1; i++){
		 		//printf("%c\n", condition[i]);
		 	}
		 	/*Nb d'opérateur = Nb de valeur -1*/
		 	j=0;
		 	i=0;
		 	//l=0;
		 	while(i<=l){
		 		if(condition[i]=='+'){
		 			r=valeur[j]+valeur[j+1];
		 			valeur[j+1]=r;
		 		}
		 		else if(condition[i]=='-'){
		 			r=valeur[j]-valeur[j+1];
		 			valeur[j+1]=r;
		 		}
		 		else if(condition[i]=='*'){
		 			r=valeur[j]*valeur[j+1];
		 			valeur[j+1]=r;
		 		}
		 		else if(condition[i]=='/'){
		 			r=valeur[j]/valeur[j+1];
		 			valeur[j+1]=r;
		 		}
		 		else if(condition[i]=='%'){
		 			r=valeur[j]%valeur[j+1];
		 			valeur[j+1]=r;
		 		}
		 		//printf("rcourant %d\n", r);
		 		i++;
		 		j++;
		 	}
		 	printf("%d\n", r);
		 	return "";
		}
		else if(ligne[i]== '=' && ligne[i+1]=='e' && ligne[i+2]=='x' && ligne[i+3]=='p' && ligne[i+4]=='r' && ligne[i+5]==' ')
		{
			char* nomdelavariable;
			vect mavaleur, mavariable;
			nomdelavariable=(char*)malloc(sizeof(char)*100);
			condition=(char*)malloc(sizeof(char)*100);
			valeur=(int*)malloc(sizeof(int)*100);
			k=i;
			j=0;
			while(ligne[k] != '$'){
				nomdelavariable[j]=ligne[k];
				k--;
			}
			j=-1;
			i=i+5;
			while(ligne[i]){
   				if(ligne[i]=='$'){ //retourne la valeur de la variable
   	 				i++;
   	 				j++;
   	 				k=0;
   	 				variable=(char*)malloc(sizeof(char)*100);
   	 				while(ligne[i] != ' '){
   	 					if(ligne[i]=='\n' || ligne[i]==EOF)
   	 						break;
   	 					variable[k]=ligne[i];
   	 					i++;
   	 					k++;
   	 				}
   	 				valeur[j]=s2i(search(a,p,variable));
   	 				free(variable);
   	 			}
   	 			else if(ligne[i]==' '){
   	 				i++;
   	 			}
	   	   		else if (ligne[i]== '+'){
	   	   			l++;
					condition[l]='+';
					i++;
		 		}
		 		else if (ligne[i]== '-'){
	   	   			l++;
					condition[l]='-';
					i++;
		 		}
		 		else if (ligne[i]== '/'){
	   	   			l++;
					condition[l]='/';
					i++;
		 		}
		 		else if (ligne[i]== '\\' && ligne[i+1]=='*'){
	   	   			l++;
					condition[l]='*';
					i+=2;
		 		}
		 		else if (ligne[i]== '%'){
	   	   			l++;
					condition[l]='%';
					i++;
				}
		 		else if(ligne[i]=='\n' || ligne[i]==EOF)
	   	   			break;
	   	   		else{
	   	   			j++;
	   	   			k=0;
   	 				variable=(char*)malloc(sizeof(char)*100);
   	 				while(ligne[i] != ' '){
   	 					if(ligne[i]=='\n' || ligne[i]==EOF)
   	 						break;
   	 					variable[k]=ligne[i];
   	 					i++;
   	 					k++;
   	 				}
   	 				valeur[j]=s2i(variable);
   	 				free(variable);
	   	   		}
		 	}
		 	//printf("Les valeurs sont:\n");
		 	for(i=0; i<j+1; i++){
		 	//	printf("%d\n", valeur[i]);
		 	}
		 	//printf("Les opérateurs sont:\n");
		 	for(i=0; i<l+1; i++){
		 	//	printf("%c\n", condition[i]);
		 	}
		 	/*Nb d'opérateur = Nb de valeur -1*/
		 	j=0;
		 	i=0;
		 	//l=0;
		 	while(i<=l){
		 		if(condition[i]=='+'){
		 			r=valeur[j]+valeur[j+1];
		 			valeur[j+1]=r;
		 		}
		 		else if(condition[i]=='-'){
		 			r=valeur[j]-valeur[j+1];
		 			valeur[j+1]=r;
		 		}
		 		else if(condition[i]=='*'){
		 			r=valeur[j]*valeur[j+1];
		 			valeur[j+1]=r;
		 		}
		 		else if(condition[i]=='/'){
		 			r=valeur[j]/valeur[j+1];
		 			valeur[j+1]=r;
		 		}
		 		else if(condition[i]=='%'){
		 			r=valeur[j]%valeur[j+1];
		 			valeur[j+1]=r;
		 		}
		 		//printf("rcourant %d\n", r);
		 		i++;
		 		j++;
		 	}
		 	//printf("valeur: %d\n", r);
		 	//printf("valeur: %s\n", i2s(r));
		 	return i2s(r);
		}
	}
}

/*Retourn x à la puisscance i*/
int puissance(int x, int i){
  int r=1;
  for(; i>0; i--){
    r*=x;
  }
  return r;
}

/*Convertie une chaine de caractère en entier
(contrairement a 'atoi', ne prend pas que les const.)*/
int s2i(char* chaine){ 
	int i,j,r;
	j=0;
	r=0;
	for(i=strlen(chaine)-1; i>=0; i--){
		//printf("%d\n", strlen(chaine));
		if(chaine[i] == '0'){
			r+= 0*(puissance(10,j));
			j++;
		}
		else if(chaine[i] == '1'){
			r+= 1*(puissance(10,j));
			j++;
		}
		else if(chaine[i] == '2'){
			r+= 2*(puissance(10,j));
			j++;
		}
		else if(chaine[i] == '3'){
			r+= 3*(puissance(10,j));
			j++;
		}
		else if(chaine[i] == '4'){
			r+= 4*(puissance(10,j));
			j++;
		}
		else if(chaine[i] == '5'){
			r+= 5*(puissance(10,j));
			j++;
		}
		else if(chaine[i] == '6'){
			r+= 6*(puissance(10,j));
			j++;
		}
		else if(chaine[i] == '7'){
			r+= 7*(puissance(10,j));
			j++;
		}
		else if(chaine[i] == '8'){
			r+= 8*(puissance(10,j));
			j++;
		}
		else if(chaine[i] == '9'){
			r+= 9*(puissance(10,j));
			j++;
		}
	}
	return r;
}

/*Convertie un int en string
Méthode trouvé sur internet car nous etiont bloqué.*/
char* i2s(int x){
	char* montableau;
	montableau=(char*)malloc(sizeof(char)*sizeof(int)* 4 + 1);
	if(montableau){
		sprintf(montableau, "%d", x);
	}
	return montableau;
}


/*Cherche un nom de variable, renvoie la valeur de la variable*/
char* search(liste a, liste p, char* element){
	char * valeur_trouve;
	if(a){
		while(p != NULL){
			if(strcmp(element,p->var) == 0){
				valeur_trouve = p->val;
				return valeur_trouve;
			}
			p = p->nxt;
		}
	}
	else
		return "";
}

/*Creer une liste avec le nom et la valeur de la variable*/
liste liste_variable(vect mavariable, vect mavaleur){
	int i;
	liste new;
	new=(liste)malloc(sizeof(noeud_t));
		for(i=0; i<=mavariable.taille;i++){
			new->var[i]=mavariable.tab[i];
		}
		for(i=0; i<=mavaleur.taille;i++){
			new->val[i]=mavaleur.tab[i];
		}
	return new;
}

/*Insert un élement dans la liste. Si cette element existe, remplace sa valeur*/
liste insert(liste a, liste new, liste p){ //DONE--TO DO: doit pouvoir inserer une nouvelle valeur a une variable, et non en rajouter une du même nom.
	new -> nxt = NULL;
	int etat =0;
	if(p==NULL){
		return new;
	}
	else if(new->val[0] == ' ' && new->var[0] == ' '){ //on test si la variable a inserer est nulle
		return p;
	}
	else{
		while(p->nxt != NULL){
			if(strcmp(new->var,p->var)==0)
			{	
				strcpy(p->val,new->val);
				etat =1;
				//printf("%s new %s\n",p->val,new->val);
			}
			//printf("valeur p->var %s\n",p->var);
			p = p->nxt;
		}
		if(etat==0){
			p->nxt= new;
			//printf("Element different\n");
		}
		return p;
	}
}

/*Affiche la liste*/
void parcourl(liste a){
  if(a){
  	while(a->nxt != NULL){
		a = a->nxt;
		//printf("ok \n");
		printf("%s = %s\n",a->var, a->val);
		//printf("ok \n");
	}
  }
}

/*Récupère la valeur d'une variable*/
vect valeur(char* nom, char* ligne, liste a, liste p){
	vect mavaleur;
	char* aux;
	int i,j,k;
	j=0;  
	i=0;
	mavaleur.taille=0;
	for(i=0; i<100; i++){
		if(strstr(ligne,"=expr ")){
				mavaleur.taille=strlen(expr(nom,ligne,a,p));
				for(i=0;i<mavaleur.taille;i++){
					mavaleur.tab[i]=expr(nom,ligne,a,p)[i];
				}
				//printf("valeur %s", expr(nom,ligne,a,p) );
				//printf("ici %s %d\n", mavaleur.tab, mavaleur.taille );
				return mavaleur;
		}

		else if(ligne[i] != ' ' && ligne[i+2] != ' ' && ligne[i+1] == '='){
			i=i+2;
			for(; i<100; i++){
				if(ligne[i] != '\n'){
					mavaleur.tab[j]=ligne[i];
					j++;
					mavaleur.taille++;
				}
			}
			//printf("%s\n", mavaleur.tab);
			return mavaleur;
		}
	}
	mavaleur.tab[0] = ' '; //On assigne une valeur pour verifier lors de l'insertion
	mavaleur.taille =1;
	return mavaleur;
}

/*Récupère le nom d'une variable*/
vect variable(char* nom, char* ligne){
	vect mavariable;
	int i,j;
	j=0;  
	i=0;
	mavariable.taille=0;
	if(strstr(ligne,"=")){
		if(!strstr(ligne,"echo ")){
			for(; i<100; i++){
				{
					if(ligne[i] != '\t'){
						mavariable.tab[j]=ligne[i];
						j++;
					}
					if(ligne[i+1] == '=' || ligne[i+1] == ' ' ){
						break;
					}
				}
			}
			mavariable.taille=j;
			return mavariable;
		}
	}
	mavariable.tab[0] = ' '; //On assigne une valeur pour verifier lors de l'insertion
	mavariable.taille =1;
	return mavariable;
}

void ls(char* ligne){
	if(strstr(ligne,"ls\n")){ //LS fonctionne seulement apres avoir tapé entré apres
		system("ls");
	}
}

void clear(char* ligne){
	if(strstr(ligne,"clear\n")){ //Idem LS
		system("clear");
	}
}

void set(liste a, char* ligne){
	if(strstr(ligne,"set\n")){ //Idem LS
		printf("Les variables sont:\n");
		parcourl(a);
	}
}

/*Fonction cat qui affiche le fichier*/
void cat(char*ligne) 
{
	if(strstr(ligne,"cat ")){
		int i,j;
		j=0;
		char* monfichier;
		monfichier=(char*)malloc(sizeof(char)*100);
		for(i=0; i<100; i++){
			if(ligne[i]==' '){
				i++;
				while(ligne[i]){
		   			if(ligne[i]=='\n' || ligne[i]== EOF || ligne[i]== '\0')
	  	 	 		  	break;
	  	 			else{
						monfichier[j]=ligne[i];
		 				i++;
		 				j++;
		 			}
				}
			}
		}
		FILE* fichier = NULL;
		int actuel;
		actuel = 0;
		fichier = fopen(monfichier, "r");

		if(fichier != NULL){
			printf("\n%s:\n", monfichier);
			while ((actuel =  fgetc(fichier)) != EOF) {
				printf("%c",actuel);
			}
			printf("\n\n");
			fclose(fichier);
			free(monfichier);
		}

		else{
			printf("Impossible d'ouvrir le fichier \"%s\".\n",monfichier);
		}
	}
}

/*Fonction qui affiche ce qu'il y a apres echo.
  Si la saisie est faites dans des '', ou des "", affiche ce qu'il y a dedans.
  Si $NomDeLaVariable est saisie dans le echo, affiche sa valeur.*/
void echo(char * nom, char* ligne, liste a, liste p){
	int i;
	vecvt variabletrouvee;
   	int j,k;
    j=-1;
	if(strstr(ligne,"echo ")){	  
	  	for(i=0; i<100; i++){
	    	if(ligne[i]==' '){
	   			i++;
  	 			if(ligne[i]=='"'){
   	 				i++;
    	 			while(ligne[i] != '"'){
	   					if(ligne[i]=='\\'){
  	 						printf("%c", ligne[i+1]);
   	 						i=i+2;
   	 					}
   	 					else if(ligne[i]=='$'){ //retourne la valeur de la variable
   	 						i++;
   	 						j++;
   	 						k=0;
   	 						variabletrouvee.tab[j]=(char*)malloc(sizeof(char)*100);
   	 						while(ligne[i] != ' '){
   	 							if(ligne[i]=='"')
   	 								break;
   	 							variabletrouvee.tab[j][k]=ligne[i];
   	 							i++;
   	 							k++;
   	 						}
   	 						printf("%s", search(a,p,variabletrouvee.tab[j]));
   	 						free(variabletrouvee.tab[j]);
   	 					}
   	 					else{
							printf("%c", ligne[i]);
	 							i++;
	 						}
	 					}
   	   				}
   				else if(ligne[i]=='\''){
   	 				i++;
   	 				while(ligne[i] != '\''){
   	 					if(ligne[i]=='\\'){
   	 						printf("%c", ligne[i+1]);
   	 						i=i+2;
   	 					}
   	 					else if(ligne[i]=='$'){ //retourne la valeur de la variable
   	 						i++;
   	 						j++;
   	 						k=0;
   	 						variabletrouvee.tab[j]=(char*)malloc(sizeof(char)*100);
   	 						while(ligne[i] != ' '){
   	 							if(ligne[i]=='\'')
   	 								break;
   	 							variabletrouvee.tab[j][k]=ligne[i];
   	 							//printf("%c\n",variabletrouvee.tab[j][k]);
   	 							i++;
   	 							k++;
   	 						}
   	 						
   	 						printf("%s", search(a,p,variabletrouvee.tab[j]));
   	 						free(variabletrouvee.tab[j]);
   	 					}
   	 					else{
							printf("%c", ligne[i]);
 							i++;
 						}
 					}
   				}
   				else{
   					while(ligne[i]){
   						if(ligne[i]=='\\'){
   	 						printf("%c", ligne[i+1]);
  	 						i=i+2;
   	 					}
   	 					else if(ligne[i]=='$'){ //retourne la valeur de la variable
   	 						i++;
   	 						j++;
   	 						k=0;
   	 						variabletrouvee.tab[j]=(char*)malloc(sizeof(char)*100);
   	 						while(ligne[i] != ' '){
   	 							if(ligne[i]=='\n' || ligne[i]==EOF)
   	 								break;
   	 							variabletrouvee.tab[j][k]=ligne[i];
   	 							i++;
   	 							k++;
   	 						}
   	 						printf("%s", search(a,p,variabletrouvee.tab[j]));
   	 						free(variabletrouvee.tab[j]);
   	 					}
	   	   				else if(ligne[i]=='\n' || ligne[i]==EOF)
	   	   					break;
	   	   				else{
							printf("%c", ligne[i]);
		 					i++;
		 				}
		 			}
	   	   		}
	   		}
		}
	printf("\n");
	}
}

/*Detecte les variable dans une chaine de caractère (dans chaine.tab)
  Les stocks dans un vecteur a deux dimension */
vecvt detectionvar(vect chaine){
	int i,j,k;
	j=-1;
	vecvt tableau;
	for(i=0; i<100 ; i++){
		if(chaine.tab[i]=='$'){
			i++;
   	 		j++;
   	 		k=0;
   	 		tableau.tab[j]=(char*)malloc(sizeof(char)*100);
   	 		while(chaine.tab[i] != ' '){
   	 			if(chaine.tab[i]=='\0')
   	 				break;
   	 			tableau.tab[j][k]=chaine.tab[i];
   	 			i++;
   	 			k++;
   	 		}
   	 		//printf("%s\n", tableau.tab[j] );
   	 	}
	}
	//printf("%s\n", tableau );
	tableau.taille=j+1;
	return tableau;
}

/*Fonction permettant de récupérer la condition*/
vect condition(char* nom, char* ligne){
	vect condition;
	int i, j;
	i=0;
	j=0;
	condition.taille=0;
	for(i=0; i<100; i++){
		if(ligne[i] == '['){
			i+= 2;
			while(ligne[i+1] != '\0'){
				if(ligne[i] == '[' || ligne[i] == ']')
					i++;
				else{
					condition.tab[j]=ligne[i];
	 				i++;
					j++;
					condition.taille++;
	 			}
	  		}
	  		return condition;	
		}
	}	
	strcpy(condition.tab,"");
	return condition;			
}

/*Retourne un tableau a 2 dimension comportant les condition dans l'ordre ou elle sont dans la chaine*/
vecvt opcond(vect condition){
	int i,j;
	i=0;
	j=-1;
	vecvt tabcond;
	tabcond.taille = 0;
	//printf("%s",condition.tab);
	for(i=0; i<100; i++){
		if((condition.tab[i]== '=') && (condition.tab[i-1] == ' ') && (condition.tab[i+1] == ' ')){
			j++;
			tabcond.tab[j]=(char*)malloc(sizeof(char)*2); 
			tabcond.tab[j][0]='=';
			tabcond.tab[j][1]='=';
		}

		if((condition.tab[i] == 'e') && (condition.tab[i+1] == 'q') && (condition.tab[i-1] == ' ') && (condition.tab[i+2] == ' ')){
			j++;
			tabcond.tab[j]=(char*)malloc(sizeof(char)*2); 
			tabcond.tab[j][0]='=';
			tabcond.tab[j][1]='=';
		}

		if((condition.tab[i] == ' ') && (condition.tab[i+1] == '!') && (condition.tab[i+2] == '=') && (condition.tab[i+3] == ' ')){
				j++;
				tabcond.tab[j]=(char*)malloc(sizeof(char)*2);
				tabcond.tab[j][0]='!';
				tabcond.tab[j][1]='=';
			}

		if((condition.tab[i] == 'n') && (condition.tab[i+1] == 'e') && (condition.tab[i-1] == ' ') && (condition.tab[i+2] == ' ')){
				j++;
				tabcond.tab[j]=(char*)malloc(sizeof(char)*2); 
				tabcond.tab[j][0]='!';
				tabcond.tab[j][1]='=';
			}

		if((condition.tab[i] == 'l') && (condition.tab[i+1] == 't') && (condition.tab[i-1] == ' ') && (condition.tab[i+2] == ' ')){
			j++;
			tabcond.tab[j]=(char*)malloc(sizeof(char)); 
			tabcond.tab[j][0]='<';
		}

		if((condition.tab[i] == 'l') && (condition.tab[i+1] == 'e') && (condition.tab[i-1] == ' ') && (condition.tab[i+2] == ' ')){
			j++;
			tabcond.tab[j]=(char*)malloc(sizeof(char)*2); 
			tabcond.tab[j][0]='<';
			tabcond.tab[j][1]='=';
		}

		if((condition.tab[i] == 'g') && (condition.tab[i+1] == 't') && (condition.tab[i-1] == ' ') && (condition.tab[i+2] == ' ')){
			j++;
			tabcond.tab[j]=(char*)malloc(sizeof(char)); 
			tabcond.tab[j][0]='>';
		}

		if((condition.tab[i] == 'g') && (condition.tab[i+1] == 'e') && (condition.tab[i-1] == ' ') && (condition.tab[i+2] == ' ')){
			j++;
			tabcond.tab[j]=(char*)malloc(sizeof(char)*2); 
			tabcond.tab[j][0]='>';
			tabcond.tab[j][1]='=';
		}
	}
	//printf("%s \n", tabcond.tab[0]);
	tabcond.taille = j+1;
	return tabcond;
}

/*Fonction qui execute la condition selon le type
Problème de cette fonction:
	-Execute le else et le elif a la suite du if, comme un simple "continue" en C.
  Nous pouvons donc les ecrires dans le fichier, mais cela sera bêtement ignoré entre
  le if et le fi ou encore le while et le done.*/
void exe_condition(int cpt, vect condition, char* ligne, liste a,char* nom){
	int i, type;
	parcourt e;
	liste p;
	p = a;

	/*Retourn un entier (ID) qui correspond au type de la condition qui est saisie (ex=if/else/while...)*/
	if(strstr(ligne,"if ") != NULL)
		type = 1;
	else if(strstr(ligne,"else ") != NULL)
		type = 2;
	else if(strstr(ligne, "while ") != NULL)
		type = 3;
	else if(strstr(ligne ,"until ") != NULL)
		type = 4;
	else if(strstr(ligne ,"elif ") != NULL)
		type = 5;
	else
		type = 0;
	/*Fin de la recupération de l'ID*/
	//printf("%d", type);
	if(type != 0){
		vecvt mesvariables= detectionvar(condition);
		vecvt mes_conditions= opcond(condition);
		char* mesconditions;
		mesconditions=(char*)malloc(sizeof(char)*2);
		strcpy(mesconditions,mes_conditions.tab[0]); //copie la variable dans un nouveau tableau dynamique
		free(mes_conditions.tab[0]); //vide l'ancien, on evite le seg fault.
		if(mes_conditions.taille == 0){ //Si il n'y a qu'une variable
			switch(type){
				case 1: //if
					if(search(a,p,mesvariables.tab[0])){
						e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
				case 2: //else
					if(!search(a,p,mesvariables.tab[0])){
						e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
				case 3: //while
					while(search(a,p,mesvariables.tab[0])){
						e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
				case 4: //until
					while(!search(a,p,mesvariables.tab[0])){
						e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
				case 5: //elif
					if(search(a,p,mesvariables.tab[0])){
						e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
				default:
					break;
			}
		}
		else if(mes_conditions.taille == 1){ //Si il y a deux variables.
			//printf("%s\n", mesconditions.tab[0]);

			/*Ici pour le = et le !=, on compare les chaines de caractères
			  et non les valeurs, question de facilité, et de pouvoir comparer
			  des chaines de caractères entre elles*/
			if(strstr(mesconditions,"!=")){
				//printf("a\n");
				switch(type){
					case 1: //if
						if(strcmp(search(a,p,mesvariables.tab[0]),search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 2: //else
						if(!strcmp(search(a,p,mesvariables.tab[0]),search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 3: //while
						while(strcmp(search(a,p,mesvariables.tab[0]),search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 4: //until
						while(!strcmp(search(a,p,mesvariables.tab[0]),search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 5: //elif
						if(strcmp(search(a,p,mesvariables.tab[0]),search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					default:
						break;
				}
			}

			else if(strstr(mesconditions,"==")){
				switch(type){
					case 1: //if
						if(!strcmp(search(a,p,mesvariables.tab[0]),search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 2: //else
						if(strcmp(search(a,p,mesvariables.tab[0]),search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 3: //while
						while(!strcmp(search(a,p,mesvariables.tab[0]),search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 4: //until
						while(strcmp(search(a,p,mesvariables.tab[0]),search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 5: //elif
						if(!strcmp(search(a,p,mesvariables.tab[0]),search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					default:
						break;
				}
			}

			/*A partir d'ici, on compare la valeur de la variable
			  Nous ne pouvons donc pas ecrire directement un chiffre
			  dans la condtions, cela donnera logiquement un seg fault*/
			else if(strstr(mesconditions,"<")){
				switch(type){
					case 1: //if
						if(s2i(search(a,p,mesvariables.tab[0])) < s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 2: //else
						if(s2i(search(a,p,mesvariables.tab[0])) >= s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 3: //while
						while(s2i(search(a,p,mesvariables.tab[0])) < s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 4: //until
						while(s2i(search(a,p,mesvariables.tab[0])) >= s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 5: //elif
						if(s2i(search(a,p,mesvariables.tab[0])) < s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					default:
						break;
				}
			}

			else if(strstr(mesconditions,"<=")){
				switch(type){
					case 1: //if
						if(s2i(search(a,p,mesvariables.tab[0])) <= s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 2: //else
						if(s2i(search(a,p,mesvariables.tab[0])) > s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 3: //while
						while(s2i(search(a,p,mesvariables.tab[0])) <= s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 4: //until
						while(s2i(search(a,p,mesvariables.tab[0])) > s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 5: //elif
						if(s2i(search(a,p,mesvariables.tab[0])) <= s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					default:
						break;
				}
			}

			else if(strstr(mesconditions,">")){
				switch(type){
					case 1: //if
						if(s2i(search(a,p,mesvariables.tab[0])) > s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 2: //else
						if(s2i(search(a,p,mesvariables.tab[0])) <= s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 3: //while
						while(s2i(search(a,p,mesvariables.tab[0])) > s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 4: //until
						while(s2i(search(a,p,mesvariables.tab[0])) <= s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 5: //elif
						if(s2i(search(a,p,mesvariables.tab[0])) > s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					default:
						break;
				}
			}

			else if(strstr(mesconditions,">=")){
				switch(type){
					case 1: //if
						if(s2i(search(a,p,mesvariables.tab[0])) >= s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 2: //else
						if(s2i(search(a,p,mesvariables.tab[0])) < s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 3: //while
						while(s2i(search(a,p,mesvariables.tab[0])) >= s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 4: //until
						while(s2i(search(a,p,mesvariables.tab[0])) < s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					case 5: //elif
						if(s2i(search(a,p,mesvariables.tab[0])) >= s2i(search(a,p,mesvariables.tab[1]))){
							e=lecture_condition(cpt,nom, a);
					}
					lecture(e.a,e.cpt,nom);
					break;
					default:
						break;
				}
			}
		}
	}
	else
		return;
}