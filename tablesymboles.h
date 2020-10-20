#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum Type{
    entier,
    reel,
    chaine };

typedef struct {
    char* nom;
    int code;
    enum Type type;
    char constant;
    int taille_tab;
    struct tuple* next; } tuple;

const char* types[]={"int","float","String"};

 int cpt=0; //compteur des codes

tuple* table;

tuple* rechercher_sy(char* nom){
    tuple* t=table;
    while( t!=NULL && strcmp(t->nom,nom)!=0){
        t=t->next;
    }
    return t;
}

 void inserer_sy(char nom[]){
 	tuple* t=malloc(sizeof(tuple));
 	if(!rechercher_sy(nom)){
        //copie des élements
        t->nom=malloc(strlen(nom)*sizeof(char));
        strcpy(t->nom,nom);
        t->code=cpt++;
        t->type=-1;
        t->constant=' ';
        t->taille_tab=0;
        //insertion
        t->next = table;
        table= t;
        }
 }

 int declarer_sy(char nom[],enum Type type,char constant,int taille_tab){
        tuple* t=rechercher_sy(nom);
        if(t!=NULL && t->type==-1){
            t->type=type;
            t->constant=constant;
            t->taille_tab=taille_tab;
            return 1;
        }
        return 0;
 }
 
int compatibilite_type(int t1,int t2){
    if ( t1==t2 || ( t1==1 && t2==0 ) )
        return 1;
    return 0;
}


void afficher_ts(){
    tuple* t=table;
    if(t==NULL) printf("Table vide\n");
    else{
        printf("\n/**********************Table des symboles ************************/\n");
        printf("_________________________________________________________________________\n");
        printf("  NomEntite |  CodeEntite  |  TypeEntite  | TailleEntite  | Constant \n");
        printf("_________________________________________________________________________\n");
        while(t!=NULL){
            printf("%10s  |\t%10d |%10s\t  |%10d\t  |\t\t%c\n",t->nom,t->code,types[t->type],t->taille_tab,t->constant);
            t=t->next;
        }
        printf("_________________________________________________________________________\n");
    }
}
