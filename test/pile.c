#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char* str;
    struct element* next;
}element;

element* pile;

void empiler(char s[]){
    element* e = malloc(sizeof(element));
    e->str = malloc(strlen(s)*sizeof(char));
    strcpy(e->str,s);
    e->next=pile;
    pile=e;
}

char* desempiler(){
    char* s;
    s=pile->str;
    pile=pile->next;
    return s;
}

// test
void main(){
    empiler("Bonjour");
    empiler("Hey");
    element* t;
    t=pile;
    while(t!=NULL){
        printf("%s\n",t->str);
        t=t->next;
        }
    printf("%s\n",desempiler());
    t=pile;
    while(t!=NULL){
        printf("%s\n",t->str);
        t=t->next;
        }

}
