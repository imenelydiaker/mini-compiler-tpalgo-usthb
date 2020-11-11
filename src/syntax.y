%{
	#include "tablesymboles.h"
	#include "quadruplets.h"
	#include "pile.h"
	
	tuple*  t; 
	quadruplet *d;
	int nbligne=1, typesave, operateur=0, typevar=0, adr_qc=1, adr_deb, adr_fin, adr_op;
	char *ch, *opsave; 
	char tmp[3];
	int bibsave[3]={0,0,0}; //tableau de 0 et de 1 : 1=>bib declarée & 0=>bib non déclarée

%}

%union{
	char* str;
	int entier;
	float reel;
}

%token mc_lang mc_fin <str>id mc_dec mc_findec mc_deb bib_tab bib_arithm bib_inout mc_chaine affect pvg exparithm <entier>nbr def typeint typef typestr '[' ']' ',' '(' ')' mc_cnst mc_boucle mc_faire mc_finboucle ifinstructions ifcond '<' '>' '=' '!' mc_input mc_output '*' '-' '/' '+' '"'

%left '+' '-'
%left '*' '/'


%%

S: LANG id mc_dec BIB DEC mc_findec mc_deb INSTRUCTION mc_fin {
	declarer_sy($2,-1,' ',0);
	printf("Le programme est syntaxiquement correcte\n");}
;

LANG: mc_lang { strcpy(tmp,"t0"); };

									/************DECLARATION DES VARIABLES************/
PVG: pvg
	| {printf("Ligne %d : ';' manquant\n",nbligne-2); YYABORT;}
;

DEC: TYPE def DECS PVG DEC;
	| 
;

DECS: VAR //déclaration de variables ou tableaux
	 |mc_cnst VARC //déclaration de constantes
;

TYPE: typeint {typesave=0;}
	|typestr {typesave=2;}
	|typef {typesave=1;}
;

VARC: id '=' nbr SUITEC { if(!declarer_sy($1,typesave,'C',1)) printf("Ligne %d: double declaration de %s\n",nbligne,$1);} //constantes
;

SUITEC: ',' VARC 
	  |
;

VAR: id SUITEV {if(!declarer_sy($1,typesave,'V',1)) printf("Ligne %d: double declaration de %s\n",nbligne,$1);;} //variable
	|id '[' nbr ']' SUITEV {
					 if(!bibsave[0]) {printf("Bibliotheque #TAB manquante\n");}
					 if(!declarer_sy($1,typesave,'V',$3)) printf("Ligne %d: double declaration de %s\n",nbligne,$1);
					 quad("Bounds", "1", itoa($3,buffer,10), "_");
					 adr_qc++;
				  	 quad("ADEC", $1, "_", "_");
					 adr_qc++;
					} 
;

SUITEV: ',' VAR 
	  |
;

BIB: bib_tab BIB {bibsave[0]=1;} 
	|bib_arithm BIB {bibsave[1]=1;} 
	|bib_inout BIB {bibsave[2]=1;}
	|
;

											/***************INSTRUCTIONS*****************/

INSTRUCTION: AFFECTATION INSTRUCTION 
			|BOUCLE INSTRUCTION 
			|CONDITION INSTRUCTION 
			|INPUT INSTRUCTION 
			|OUTPUT INSTRUCTION  
			|
;

VARIABLE: id { t=rechercher_sy($1);  
			   if(t->type>typevar) typevar=t->type;
               empiler($1);
			   if(t->type==-1) printf("Ligne %d: %s non declare\n",nbligne,$1);
			   else typevar=t->type;}
		|nbr { if(operateur && !$1) printf("Ligne %d: division par 0\n",nbligne); 
			   operateur=0; typevar=0; 
			   if(typevar==2) typevar=2;
			   else if(typevar==1) typevar=1;
			   empiler(itoa($1,buffer,10));}
		|id '[' EXPR ']' { t=rechercher_sy($1); 
						   if(t->type>typevar) typevar=t->type;
		                   empiler($1);
					       if(t->type==-1) printf("Ligne %d: idf non declare\n",nbligne);
						   else typevar=t->type;	 
						 }
;


EXPR: VARIABLE 
	|EXPR '*' EXPR {operateur=0; 
					if(!bibsave[1]) printf("Bibliotheque #ARITHM manquante\n"); 
					incrementeTemp(tmp);
					quad("*",desempiler(),desempiler(),tmp);  empiler(tmp);
					adr_qc++;}
	|EXPR '/' EXPR {operateur=1;  
					if(!bibsave[1]) printf("Bibliotheque #ARITHM manquante\n"); 
					incrementeTemp(tmp);
					quad("/",desempiler(),desempiler(),tmp);  empiler(tmp);
					adr_qc++;}
	|EXPR '+' EXPR {operateur=0; 
					if(!bibsave[1]) printf("Bibliotheque #ARITHM manquante\n"); 
					incrementeTemp(tmp);
					quad("+",desempiler(),desempiler(),tmp);  empiler(tmp);
					adr_qc++;}
	|EXPR '-' EXPR {operateur=0; 
					if(!bibsave[1]) printf("Bibliotheque #ARITHM manquante\n"); 
					incrementeTemp(tmp);
					quad("-",desempiler(),desempiler(),tmp);  empiler(tmp);
					adr_qc++;}
	|'(' EXPR ')'  
;

AFFECTATION: id affect EXPR PVG { t=rechercher_sy($1);
								  if(t->type==-1) printf("Ligne %d: %s non declare\n",nbligne,$1);
								  else {
										if(t->constant=='C') printf("Ligne %d: impossible de modifier une constante\n",nbligne);
										if(!compatibilite_type(t->type,typevar)) printf("Ligne %d: type incompatible\n",nbligne);
										else{
											if(t->constant=='V'){
												quad("=",desempiler(),"_",$1);
												adr_qc++;}
											}
									   }
								  
								  typevar=0;
								}
			|id '[' nbr ']' affect EXPR PVG { t=rechercher_sy($1); 
											  if(t->type==-1) printf("Ligne %d: %s non declare\n",nbligne,$1);
											  else { 
												    if(t->taille_tab<$3) printf("Ligne %d: taille du tableau %s depassee\n",nbligne,$1);
													if(!compatibilite_type(t->type,typevar)) printf("Ligne %d: type incompatible\n",nbligne);
													else {
														quad("=",desempiler(),"_",$1);
														adr_qc++;
														}
													} 
											  typevar=0;
											} 
;


INPUT: mc_input '(' mc_chaine ')' PVG {if(!bibsave[2]) {printf("Bibliotheque #INOUT manquante\n");}}
;

OUTPUT: mc_output '(' SORTIE ')' PVG {if(!bibsave[2]) {printf("Bibliotheque #INOUT manquante\n");}}
;

SORTIE: VARIABLE
		|VARIABLE ',' SORTIE
;

BOUCLE: mc_boucle COND mc_faire INSTRUCTION mc_finboucle { inserer2(itoa(adr_qc+1,buffer,10),adr_op);
													  adr_qc++;	
													  quad("BR", itoa(adr_deb,buffer,10),"_","_");
													  adr_qc++;
													}
;

COND : '(' ARGS ')' { quad("BZ","","_","temp_cond"); 
					  adr_op=adr_qc; adr_deb=adr_qc;
					  adr_qc++;   
					}
;

CONDITION: DINST INSTRUCTION ifcond '(' ARGS ')' { quad("BR",itoa(adr_qc+2,buffer,10),"_","_");
												   adr_qc++;
												   quad("BNZ", itoa(adr_op,buffer,10), "_", "temp_cond"); 
												   inserer2(itoa(adr_qc,buffer,10),adr_deb);
												   adr_qc++;
												 }
;

DINST: ifinstructions {adr_deb=adr_qc;
					   quad("BR","","_","_");
					   adr_qc++; adr_op=adr_qc;
					  }
; 

ARGS: EXPR COMPARAISON EXPR {//quad(opsave,"_",desempiler(),desempiler()); 
							//adr_qc++;
							desempiler(); desempiler();
					  		}
;

COMPARAISON: '<'  {opsave="BL";}
			|'>' {opsave="BG";}
			|'!''=' {opsave="BNE";}
			|'<''=' {opsave="BEL";}
			|'>''=' {opsave="BEG";}
			|'=''=' {opsave="BE";}
;


%%


main(){
	yyparse();
	afficher_ts();
	afficher_qd();
}
yywrap()
{}