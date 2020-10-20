#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum Type{
    entier,
    chaine,
    reel};

typedef struct {
    char* nom;
    int code;
    enum Type type;
    char constant;
    int taille_tab;
    struct tuple* next; } tuple;

 const char* types[]={"int","float","String"};

 int cpt=0; //compteur des codes

 struct tuple* table;

 tuple* rechercher(char nom[]){
    tuple* t=table;
    while(t!=NULL && strcmp(t->nom,nom)!=0){
        t=t->next;
    }
    return t;
}

 void inserer(char nom[]){
 	tuple* t=malloc(sizeof(tuple));
 	if(!rechercher(nom)){
        //copie des élements
        t->nom=malloc(strlen(nom)*sizeof(char));
        strcpy(t->nom,nom);
        t->code=cpt++;
        t->type=-1;
        t->constant=' ';
        t->taille_tab=1;
    //insertion
 	t->next = table;
 	table= t;}
 }

 int declarer(char nom[],enum Type type,char constant,int taille_tab){
        tuple* t=rechercher(nom);
        if(t!=NULL && t->type==-1){
            t->type=type;
            t->constant=constant;
            t->taille_tab=taille_tab;
            return 1;
        }
        return 0;
 }

 int compatibilite_type(int t1,int t2){
    if(t1==t2 || (t1==2 && t2==0) )
        return 1;
    return 0;
 }


void afficher(){
    tuple* t=table;
    printf("\n/**********************Table des symboles ************************/\n");
    printf("_______________________________________________________________________\n");
    printf("| NomEntite |  CodeEntite  |  TypeEntite  | TailleEntite  | Constant \n");
    printf("_______________________________________________________________________\n");
    if(t==NULL) printf("Table vide");
    while(t!=NULL){
    	printf("%10s\t%12d\t%12s   \t%10d \t %c \t\n",t->nom,t->code,types[t->type],t->taille_tab,t->constant);
    	t=t->next;
    }
};


int main(){
    tuple *t1,*t2;

    inserer("X");
    inserer("Y");
    inserer("X");
    inserer("Z");

    printf("%s\n",rechercher("X")->nom);

    afficher();

    int i;
    declarer("X",2,'C',1);
    i=declarer("X",1,'C',1);
    if(i) printf("non declare\n");
    else printf("deja declare\n");

    afficher();

}
