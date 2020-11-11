typedef struct{
    char* str;
    struct structure* next;
}structure;

structure *pile; // *pile_type;

void empiler(char s[]){
    structure* e = malloc(sizeof(structure));
    e->str = malloc(strlen(s)*sizeof(char));
    strcpy(e->str,s);
    e->next=pile;
    pile=e;
}

char* desempiler(){
    if(pile!=NULL){
        char* s;
        s=pile->str;
        pile=pile->next;
        return s;
    }
    return NULL;
}
/*
void empiler_type(int t){
    structure* e = malloc(sizeof(structure));
    char* s=itoa(t,buffer,10);
    e->str = malloc(strlen(s)*sizeof(char));
    strcpy(e->str,s);
    e->next=pile_type;
    pile_type=e;
}

char* desempiler_type(){
    if(pile_type!=NULL){
        char* s;
        s=pile_type->str;
        pile_type=pile_type->next;
        return s;
    }
    return NULL;
}*/


