#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libreria.h"

/*File funzioni.c*/



int menu_principale(int a, char player[10]){	/*Funzione che elenca le scelte possibili che possono essere fatte nel menu*/
	system("clear");
	printf(size); /*Regolo la dimensione del terminale*/
	printf(specialblue"Inserisci il tuo nick\n");
	scanf("%s", player);	/*Prendo in imput il nome del player*/
	while(a>5 || a<1){ /*Ciclo che termina quando ho inserito una scelta tra 1 a 5 */
	system("clear");
	printf(RED"Benvenuto %s in Campo Minato\n\n"reset, player);
	printf(specialcyan"Progetto finale Programmazione Mod.2\n\n\n"reset);
	printf(YELLOW"Scegli:\n\n"reset);
	printf(line"\t\t\t\t _________________________________________________\n"reset);
	printf(specialred"\t\t\t1->\t|              C A R I C A  C A M P O             |\n"reset);
	printf(specialyellow"\t\t\t2->\t|              G E N E R A  C A M P O             |\n"reset);
	printf(specialgreen"\t\t\t3->\t|                   R E C O R D                   |\n"reset);
	printf(specialcyan"\t\t\t4->\t|                   C R E D I T                   |\n"reset);
	printf(specialblue"\t\t\t5->\t|                     E X I T                     |\n"reset);
	printf(line"\t\t\t\t _________________________________________________\n"reset);
	printf(specialcyan"\n");

	char* vett=NULL;	/*Puntatore usato per il funzionamento corretto della getline*/
	size_t byte=1;	/*Variabile richiesta dalla getline*/
	int temp=-1;	/*Flag temporaneo che conttrolla se il valore inserito è un numero o un carattere*/
	getline(&vett,&byte,stdin);
	sscanf(vett,"%d"reset,&temp);
	if(temp!=-1){
		a=temp;
		temp=-1;
	}
	printf("\n");
	}


	return a;	/*Valore di ritorno*/
}

void logo(){										/*Funzione che stampa il logo del gioco*/
	printf(specialred" _____________________\n"reset);
	printf(specialred"|       MINEFIELD     |\n"reset);
	printf(specialred"|_____________________|\n"reset);
	printf("\n");
}

int credit(){	/*Funzione che stampa la scelta 4*/
	printf("\n\n\n\n");
	system("reset");
	printf(specialcyan"\t\t\t\t\tSviluppato da:\n\n\n"reset);
	printf(specialred"\t\t\t\t  M A T T E O  P A S C O N\n");
	printf("\t\t\t       P A S Q U A L E  S O L D A N O\n"reset);
	return 0;
}



void cerca_spazi(int x,int y,char **campo,char **vett, int righe, int colonne, int **back_track){

/*Funzione che prende in imput 3 matrici e le coordinate dell'utente per scoprire in modo ricorsivo tutte le celle che hanno spazi vicino alla cella selezionata*/
	if(vett[x][y]!='/'){
		if (campo[x][y]>'0'&& campo[x][y]<'9'){
			vett[x][y]='&';	/*Assegnamento necessario per l'algoritmo di vittoria*/
			back_track[x][y]=1; /*Assegnamento necessario per la modalità del back_tracking*/
		}
		if (campo[x][y]==' '&& back_track[x][y]==0){
			vett[x][y]='&';
			back_track[x][y]=1;
			if (x-1>-1 && x-1<righe && y>-1 && y<colonne) /*Controllo che non esco fuori dalla matrice*/
				cerca_spazi(x-1,y,campo,vett,righe,colonne,back_track);	/*UP*/

			if (x-1>-1 && x-1<righe && y-1>-1 && y-1<colonne)
				cerca_spazi(x-1,y-1,campo,vett,righe, colonne,back_track);	/*UP LEFT*/

			if (x>-1 && x<righe && y-1>-1 && y-1<colonne)
				cerca_spazi(x,y-1,campo,vett,righe,colonne,back_track);	/*LEFT*/

			if (x+1>-1 && x+1<righe && y-1>-1 && y-1<colonne)
				cerca_spazi(x+1,y-1,campo,vett,righe,colonne,back_track);	/*LEFT DOWN*/

			if (x+1>-1 && x+1<righe && y>-1 && y<colonne)
				cerca_spazi(x+1,y,campo,vett,righe,colonne,back_track);	/*DOWN*/

			if (x+1>-1 && x+1<righe && y+1>-1 && y+1<colonne)
				cerca_spazi(x+1,y+1,campo,vett,righe,colonne,back_track);	/*RIGH DOWN*/

			if (x>-1 && x<righe && y+1>-1 && y+1<colonne)
				cerca_spazi(x,y+1,campo,vett,righe,colonne,back_track);	/*RIGH*/

			if (x-1>-1 && x-1<righe && y+1>-1 && y+1<colonne)
				cerca_spazi(x-1,y+1,campo,vett,righe,colonne,back_track); /*RIGHT UP*/
		}
	}
}/*Chiusura funzione*/

void pulisci_campo(char **vett, int colonne, int righe){
int i,j;
 	for (i=0; i<righe; i++){				/*Funzione che inizializza il campo che vedrà l'utente*/
 		for(j=0; j<colonne; j++){
 			vett[i][j]='?';
 		}
		 printf("\n");
 	}
}

void pulisci_campomine(char **vett, int colonne, int righe){
int i,j;
 	for (i=0; i<righe; i++){				/*Funzione che inzializza il campo che conterrà mine,numeri e spazi*/
 		for(j=0; j<colonne; j++){
 			vett[i][j]=' ';
 		}
		 printf("\n");
 	}
}

void set_numeri(char **vett,int colonne, int righe){
int r,c,i,j;
int cont=0;
													/*Funzione che posiziona i numeri in base alla posizione delle mine*/
	for (i=0; i<righe; i++){
		for(j=0; j<colonne; j++) {
				r=i-1; /*R e C sono 2 variabili che girano intorno alla cella per cercare mine */
				c=j;
				if (r>-1 && r<righe && c>-1 && c<colonne  && vett[r][c]=='*')	/*UP*/	/*Negli if faccio dei controlli per non uscire fuori dalla matrice*/
					cont++;

				r=i-1;
				c=j-1;

				if (r>-1 && r<righe && c>-1 && c<colonne  && vett[r][c]=='*') /*UP LEFT*/
					cont++;

				r=i;
				c=j-1;

				if (r>-1 && r<righe && c>-1 && c<colonne  && vett[r][c]=='*')	/*LEFT*/
					cont++;

				r=i+1;
				c=j-1;

				if (r>-1 && r<righe && c>-1 && c<colonne  && vett[r][c]=='*')		/*LEFT DOWN*/
					cont++;

				r=i+1;
				c=j;
				if (r>-1 && r<righe && c>-1 && c<colonne  && vett[r][c]=='*')		/*DOWN*/
					cont++;

				r=i+1;
				c=j+1;

				if (r>-1 && r<righe && c>-1 && c<colonne  && vett[r][c]=='*')		/*RIGHT DOWN*/
					cont++;

				r=i;
					c=j+1;

				if (r>-1 && r<righe && c>-1 && c<colonne  && vett[r][c]=='*')	/*RIGHT*/
					cont++;

				r=i-1;
				c=j+1;
				if (r>-1 && r<righe && c>-1 && c<colonne  && vett[r][c]=='*')		/*RIGHT UP*/
					cont++;

				if (vett[i][j]!='*'&& cont!=0)
					vett[i][j]=cont+'0';	/*Metto nella matrice il numero di bombe che sono state trovare da R e C*/


				cont=0; /*Resetto per ripetre il ciclo su altre celle*/

			}/*close ciclo interno*/

		}/*cloce ciclo esterno*/

	}/*close della funzione*/




void set_mine(char **vett, int colonne, int righe, int cont){
int i,j,k;
											/*Funzione che inserisce le mine in maniera casuale in modo ricorsivo*/
	if(cont!=0){
		k=rand()%(righe*colonne);
		i=k/colonne;
		j=k%colonne;

		if(vett[i][j]=='*')
			set_mine(vett,colonne,righe,cont);

		else {
			vett[i][j]='*';
			set_mine(vett,colonne,righe,--cont);
		}
	}
}

int stampa(char **vett, int righe, int colonne, int **back_track, char **mine){
int i,j;
int cont=0;

printf(specialblue" ||"reset);										/*Funzione che stampa a video il campo dove giocherà l'utente*/
for(i=0; i<colonne; i++){
	printf(specialblue"%d |"reset,i );
}
printf(specialblue"||\n"reset);
for(i=0; i<righe; i++){
		printf(specialblue"%d||"reset,cont++);
		for(j=0; j<colonne; j++){

			if(back_track[i][j]==0 && vett[i][j]!='/'){
				vett[i][j]='?';
				printf(WHITE"%c "reset,vett[i][j]);
				printf("|");
			}
			if(vett[i][j]=='/'){
				printf(WHITE"%c "reset,vett[i][j]);
				printf("|");
			}
			if(back_track[i][j]!=0){
				printf(specialyellow"%c "reset,mine[i][j]);
				printf("|");
			}
		}
		printf(specialblue"||%d\n"reset,cont-1);
	}
return 0;
}

int stampa_bombe(char **mine, int colonne, int righe){
int i,j;
int cont=0;
															/*Funzione stampa le mine che ci sono nel campo, usata nel Gameover*/
printf(specialblue" ||"reset);
for(i=0; i<colonne; i++){
	printf(specialblue"%d |"reset,i );
}
printf(specialblue"||\n"reset);
for(i=0; i<righe; i++){
		printf(specialblue"%d||"reset,cont++);
		for(j=0; j<colonne; j++){
			if(mine[i][j]=='*'){
			printf(specialred"%c "reset,mine[i][j]);
			printf(specialblue"|"reset);
		}
			else {
					printf("  ");
					printf(specialblue"|"reset);
						}
		}
		printf(specialblue"||%d\n"reset,cont-1);
}

return 0;
}

void inserisci_mine(char **vett,FILE *f,int righe, int colonne,int *sommabombe){
int x,y;
int i,j;																	/*Funzione che inserisce le mine in base ai valori presi da file*/

/*Funzione che prende da FILE la posizione delle mine e inserisce le mine nella matrice */
		while(fscanf(f,"%d, %d",&x,&y) && !feof(f)){
			(*sommabombe)++;
			vett[x][y]='*';
		}
	fclose(f);
}

void nuovoturno(int **back,int righe, int colonne){
int i,j;
	for (i = 0; i < righe; ++i){
		for (j = 0; j < colonne; ++j){				/*Funzione che aggorna il back_tracking ad ogni turno incrementando i valori delle celle*/
			if (back[i][j]!=0){
			(back[i][j])++;
			}
		}
	}

}/*Chiusura della funzione*/

void come_back(char** vett, int **back_track, int colonne, int righe, int turni){
int i,j;														/*Funzione che torna indietro di n mosse in base alla vita del giocatore*/

for (i = 0; i < righe; ++i){
	for (j = 0; j < colonne; ++j){
		if (vett[i][j]!='/'){
			if(back_track[i][j]!=0){
				if (back_track[i][j]<=turni){
					vett[i][j]='?';
					back_track[i][j]=(back_track[i][j]-turni);
					if (back_track[i][j]<0){
						back_track[i][j]=0;
					}
				}
				else
					back_track[i][j]=(back_track[i][j]-turni);
			}
		}
	}
}

}

void salva_automatico(char **mine, FILE *f, int righe, int colonne){
int i,j;
fprintf(f,"%d,%d\n\n",righe,colonne);
for(i=0; i<righe; i++){									/*Funzione che salva le mine della partita corrente nel file output.txt*/
	for (j=0; j<colonne; ++j){
		if(mine[i][j]=='*')
			fprintf(f,"%d,%d\n",i,j);
	}
}

fclose(f);
}

int check(char *zol,int temp,int *parametro,int max,int segno){
size_t byte=1;
free(zol);
zol=NULL;
	if (segno==-1){ /*segno <*/
		do{
			getline(&zol,&byte,stdin);					/*Funzione utilizzata per il controllo del input dall'utente con getline*/
			sscanf(zol,"%d",&temp);
			if(temp!=-1 ){
				*parametro=temp;
				temp=-1;
			}
		}while(*parametro<max && temp==-1); /*Parametro inserito dall'utente che vuole controllare*/
	}
	if (segno==1){ /*Segno >*/
		do{
			getline(&zol,&byte,stdin);
			sscanf(zol,"%d",&temp);
			if(temp!=-1 ){
				*parametro=temp;
				temp=-1;
			}
		}while(*parametro>max && temp==-1);
	}
}

void intro(){
	time_t now = time(NULL);						/*Stampa a video con timer le scritte del gioco prima del caricamento del menu*/
	system("clear");
	printf(size); /*Regola la dimensione del terminale*/
	printf(specialblue"\n\n\n\n\t\t\t\t\t   P R O G E T T O  P R O G R A M M A Z I O N E\n\n"reset);
	printf(specialred"\n\t\t\t\t\t\t  A n n o  2 0 1 6 / 2 0 1 7 \n\n"reset);
	while(difftime(time(NULL), now)!=2); /*secondi*/
	now = time(NULL);
	system("clear");
	printf(specialred"\n *   \t \t \t * \t \t \t \t *\t \t * \t * \t \t * \t \t  * \t * \t * \n"reset);
	printf(specialgreen"\n\n\n\n\t\t\t\t\t\t       M I N E F I E L D \n\n\n"reset);
	printf(specialred"\n *   \t \t \t * \t \t \t \t *\t \t * \t * \t \t * \t \t  * \t * \t * \n"reset);
	while(difftime(time(NULL), now)!=2);
}
