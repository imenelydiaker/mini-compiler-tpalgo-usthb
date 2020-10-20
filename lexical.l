%{
#include "syntax.tab.h"
extern YYSTYPE yylval;
extern int nbligne;
%}

lettre [A-Za-z]
chiffre [0-9]
idf [A-Z]({lettre}|{chiffre})*
nombre {chiffre}+(\.{chiffre}+)?


%%

LANGAGE return mc_lang;
FIN return mc_fin;
DEC return mc_dec;
FINDEC return mc_findec;
DEBUT return mc_deb;
#TAB[ \t]*[\n] {nbligne++; return bib_tab;}
#ARITHM[ \t]*[\n] {nbligne++; return bib_arithm;}
#INOUT[ \t]*[\n] {nbligne++; return bib_inout;}
int return typeint;
float return typef;
String return typestr;
CONST return mc_cnst;
While return mc_boucle;
Faire return mc_faire; 
Fait return mc_finboucle;
EXECUT return ifinstructions;
IF return ifcond;
input return mc_input;
output return mc_output;
{idf} {if(yyleng<=12){
       yylval.str=strdup(yytext);
       inserer_sy(yytext);
       return id;}
       else printf("Erreur lexicale: Identificateur trop long\n");}
{nombre} {yylval.entier=atoi(yytext);
          return nbr;}
[-+/*] return yytext[0];
:= return affect;
; return pvg;
:: return def;
\{\{([^\}]+\})*\} {int i=0; while(yytext[i]!='\0') if(yytext[i++]=='\n') nbligne++;}
\"[^\"]*\" return mc_chaine;
[,\[\]\(\)<>=!"] return yytext[0]; 
[\t ] 
[\n] nbligne++; 
. printf("Erreur lexicale a la ligne %d : %s\n",nbligne,yytext);
