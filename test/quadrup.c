#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char* qd1;
    char* qd2;
    char* qd3;
    char* qd4;
} quadruplet;

typedef struct{
    int num_qd;
    quadruplet* d;
    struct element* next;
}element;

char buffer[20];
element* quadruplets;
int cpt=0;

element* quad(char q1[],char q2[],char q3[],char q4[]){
    element* e = malloc(sizeof(element));
    e->d= malloc(sizeof(quadruplet));
    e->num_qd=++cpt;
    e->d->qd1=malloc(strlen(q1)*sizeof(char));
    strcpy(e->d->qd1,q1);
    e->d->qd2=malloc(strlen(q2)*sizeof(char));
    strcpy(e->d->qd2,q2);
    e->d->qd3=malloc(strlen(q3)*sizeof(char));
    strcpy(e->d->qd3,q3);
    e->d->qd4=malloc(strlen(q4)*sizeof(char));
    strcpy(e->d->qd4,q4);
    e->next=quadruplets;
    quadruplets=e;
  return e;
}


quadruplet* rechercher(int num_quad){
    element* e= quadruplets;
    while(e!=NULL){
        if(e->num_qd == num_quad) return e->d;
        else e=e->next;
    }
    return NULL;
}


void maj_quad(char q[], int num_qd, int num_col){
    quadruplet* d= rechercher(num_qd);
    if(num_col==1){
        d->qd1=malloc(strlen(q)*sizeof(char));
        strcpy(d->qd1,q);}
        else {if(num_col==2){
                d->qd2=malloc(strlen(q)*sizeof(char));
                strcpy(d->qd2,q);}
                else {if(num_col==3){
                        d->qd3=malloc(strlen(q)*sizeof(char));
                        strcpy(d->qd3,q); }
                        else {
                            d->qd4=malloc(strlen(q)*sizeof(char));
                            strcpy(d->qd4,q);
                            }
                    }
            }
}


void inserer1(char q1[], int num_qd){
    quadruplet* d= rechercher(num_qd);
    d->qd1=malloc(strlen(q1)*sizeof(char));
    strcpy(d->qd1,q1);
}

void inserer2(char q2[], int num_qd){
    quadruplet* d= rechercher(num_qd);
    d->qd2=malloc(strlen(q2)*sizeof(char));
    strcpy(d->qd2,q2);
}

void inserer3(char q3[], int num_qd){
    quadruplet* d= rechercher(num_qd);
    d->qd3=malloc(strlen(q3)*sizeof(char));
    strcpy(d->qd3,q3);
}

void inserer4(char q4[], int num_qd){
    quadruplet* d= rechercher(num_qd);
    d->qd4=malloc(strlen(q4)*sizeof(char));
    strcpy(d->qd4,q4);
}

 void afficher_qd(){
    element* e;
    e=quadruplets;
    if(e==NULL) printf("Aucun quadruplet\n");
    else{
        printf(" _________________________________________________\n");
        printf("\n/****************** Quadruplets ******************/\n");
        printf(" _________________________________________________\n");
        while(e!=NULL){
            printf("Quad %d ( %s , %s , %s , %s )\n", e->num_qd, e->d->qd1, e->d->qd2, e->d->qd3, e->d->qd4);
            e=e->next;
        }
    }
 }

/*
void incrementeTemp(char* tmp){
	int nbr=atoi(tmp+1);
	strcpy(tmp+1,itoa(++nbr,buffer,10));
}*/

void incrementeTemp(char* tmp){
	strcpy(tmp+1,itoa(atoi(tmp+1)+1,buffer,10));
}

 void main(){
    quadruplet *d1,*d2,*d3;
    d1=quad("BZ","k+1","_","t1");
    d2=quad("=","","_","A");
    d3=quad("=",itoa(52,buffer,10),"_","A");
    afficher_qd();
    maj_quad("adrdeb",2,2);
    afficher_qd();

    char tmp[3];
    strcpy(tmp,"t1");
    printf("\n%s\n",tmp);
    incrementeTemp(tmp); printf("%s\n",tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    incrementeTemp(tmp);
    printf("%s\n",tmp);
 }

