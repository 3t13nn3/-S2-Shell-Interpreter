/*Ici sont les prototypes*/
struct noeud {
  char var[100];
  char val[100];
  struct noeud * nxt;
};
typedef struct noeud noeud_t;
typedef struct noeud * liste;

struct vec{
	int taille;
	char tab[100];
};
typedef struct vec vect;

struct vecv{
	int taille;
	char* tab[100];
};
typedef struct vecv vecvt;

struct parcour{
	liste a;
	int cpt;
};
typedef struct parcour parcourt;

/*Parcour le fichier ligne par ligne.
La plus part des fonctions sont appelé dedans
en prenant comme argument generalement la ligne
parcouru.
Prend en argument un compteur pour commencer a une ligne voulu
et la liste de variable actuelle*/
void lecture(liste,int,char*);

/*Affiche le contenue d'un fichier
mis en argument*/
void cat(char*);

/*Fonction qui affiche ce qu'il y a dans le echo
que ca soit sans rien, entre '', ou entre "".
Detecte si on demande la valeur d'une variable
en regardant les '$', si c'est le cas, affiche la
valeur en question.*/
void echo(char*,char*,liste,liste);

/*Retourne la condition a la base entre crochets,
sans ses crochet. Cette condition sera traité par
la fonction opcond();*/
vect condition(char*, char*);

/*Retourne les symboles de comparaison sous
forme de structure qui seront testé lors de
l'execution des condition*/
vecvt opcond(vect);

/*Detecte les variables qu'il y a dans une condition.
Retourne un structure comportant ces variables et leurs tailles.
Utilisée dans l'execution des conditions*/
vecvt detectionvar(vect);

/*Execute les conditions if, while, until
Les conditions else et elif ne sont pas
prise en compte
ATTENTION, pour les comparaison d'entier:
	Il faut au préalable declarer une variable
	avec la valeur du nombre que l'on veut comparer
	pour que cela soit fonctionnel, sinon seg fault.
	(pour tout les cas, on utilise la fonction search();
	il faut donc absolument une variable).
EXEMPLE:
	while[ $a lt $b ] --> bon
	while[ $a lt 10 ] --> segfault
	*/
void exe_condition(int ,vect, char*, liste,char*);

/*Recupère le nom de la variable lors de
son affectation. Renvoie le nom et la taille
du nom sous forme de structure*/
vect variable(char*,char*);

/*Recupère la valeur de la variable lors de
son affectation. Renvoie la valeur et la taille
de la valeur sous forme de structure*/
vect valeur(char*,char*,liste,liste);

/*Fonction qui insert un élement en queue de liste.
Si la variable a inserer est deja presente dans la 
liste, on change seulement la valeur de la variable,
on ne rajoute pas deux fois la même variable dans la liste*/
liste insert(liste,liste,liste);

/*Fonction qui affiche la liste en partant
de la tête de liste jusqu'à la queue.
On affiche le nom puis la valeur de la variable*/
void parcourl(liste);

/*Prend en argument une structure de la valeur d'une variable
puis une structure du nom d'une variable.
Retourne un liste contenant la valeurs et le nom de la variable*/
liste liste_variable(vect,vect);

/*Fonction qui cherche dans une liste la valeur
d'une variable a partir de son nom.
Retourne sa valeur (tout le temps une chaine de caractères*/
char* search(liste,liste, char*);

/*Fonction identique a la fonction lecture,
sauf qu'elle s'arrete des que la ligne signale
la fin de l'execution de la condition (fi ou done).
Retourne une structure avec un compteur et la liste actuelle
pour que la fonction lecture reprenne a la bonne ligne et
avec la bonne liste de variable*/
parcourt lecture_condition(int, char*, liste);

/*Fonction permetant de faire des calculs
soit sans variable, soit en affectant le resultat
à une variable voulue
ATTENTION:
	Peut prendre plusier opération, mais ne respecte
	pas la priorité des signes*/
char* expr(char*,char*,liste,liste);

/*Convertie une chaine de caractère en entier*/
int s2i(char*);

/*Convertie un entier en chaine de caractère*/
char* i2s(int);

/*Met a la puissance désiré un nombre,
Utile pour passer d'une chaine de caractères
à un entier*/
int puissance(int,int);

/*Appel systeme de ls*/
void ls(char*);

/*Appel systeme de clear*/
void clear(char*);

/*Appel la fonction de parcour de liste
pour afficher les variables du fichier*/
void set(liste,char*);