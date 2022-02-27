#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "minefieldHelper.h"


int main()
{
	intro();
	int pilot;						 /*Variabile che permette di tornare indietro nel playerModality quando si perde o quando si vince*/
	char player[10];				 /*Vettore per contenere il nome del player*/
	pilot = playerModality(player); /*Variabile che contiene la scelta che l'utente fa nel playerModality*/
	while (pilot != 5)
	{
		int a = pilot; /*Variabile che salva la scelta dell'utente nella funzione playerModality principale*/
		pilot = 0;
		FILE *f;				 /*Variabile per il file */
		char **vett = NULL;		 /*gameFieldMatrix della matrice visibile al player*/
		char **mine = NULL;		 /*gameFieldMatrix della matrice dove sono situati le bombe, gli spazi e i numeri*/
		char nomefile[10];		 /*Vettore per contenere il nome del file*/
		int **back_track = NULL; /*gameFieldMatrix per la funzionalità del back_track*/
		int x, y;				 /*Variabili per le coordinate che inserisce l'utente*/
		int sommabombe = 0;		 /*Variabile che contiene la somma delle mine che l'utente inserisce*/
		int colonne = -1;		 /*Variabile per le colonne della matrice*/
		int righe = -1;			 /*Variabile per le righe della matrice, **Inizializzo a -1 per la seconda scelta nelle getline*/
		int i, j;				 /*Indici delle matrici*/
		int back = 1;			 /*Turni per la funzione del back track*/
		char *zol = NULL;		 /*Puntatore utilizzato per tutte le getline*/
		size_t byte = 1;
		int temp = -1;
		int temp1 = -1; /*Variabili utilizzate esclusivamente per tutte le getline*/
		int scelta;		/*Variabile che contiene la scelta di aprire una cella o inserire una bandierina o di uscire*/
		int aiuti = -1; /*Numero di aiuti che l'utente vuole (viene decrementato ogni volta che l'utente utilizza questa funzione (back_tracking))*/

		if (a == 1)
		{ /*Se scelgo di CARICARE una PARTITA*/
			system("clear");
			printf("%s Inserisci il nome del FILE da caricare\n", player); /*scelta del nome del file (il file deve essere nella stessa cartella*/
			scanf("%s", nomefile);										   /*Salvo in un vettore il nome del file, essendo un char la scanf funziona quasi tutti i casi*/
			f = fopen(nomefile, "r");									   /*Apro il file in modalita di lettura*/
			if (f == NULL)
			{ /*Controllo se il file è stato aperto corretamente*/
				printf("\n%s Ce stato un errore nell'apertura del file \t\t Riprova\n", player);
				return 0; /*Se cè un errore nell'apertura il programma si chiude*/
			}
			fscanf(f, "%d,%d", &righe, &colonne); /*Salvo le righe e le colonne dalla prima riga del file*/
			free(zol);							  /*Libero la memoria per cancellare il contenuto di Zol*/
			zol = NULL;							  /*Inizializzo Zol a NULL */
		}

		if (a == 2)
		{ /*Se scelgo di GENERARE un gameFieldMatrix*/
			system("clear");
			printf("Inserisci numero di righe\n");
			check(zol, -1, &righe, 2, -1); /*Funzione per il controllo degli input da parte del'utente*/
			printf("Inserisci numero di colonne\n");
			check(zol, -1, &colonne, 2, -1);
			sommabombe = ((righe * colonne) + 1); /*Numero inferiore alla quantita di mine massime*/
			printf("Inserisci numero di bombe\n");
			do
			{
				check(zol, -1, &sommabombe, righe * colonne, 1);
			} while (sommabombe < 1);
		} /*Chiusura scelta 2*/

		if (a == 1 || a == 2)
		{
			printf("Inserisci numero di aiuti \n");
			check(zol, -1, &aiuti, 0, -1);

			vett = (char **)malloc(righe * sizeof(char *)); /*Allocazione dimanica di tutti gli array*/
			for (i = 0; i < righe; i++)
				vett[i] = malloc(colonne * sizeof(char));
			mine = (char **)malloc(righe * sizeof(char *));
			for (i = 0; i < righe; i++)
				mine[i] = malloc(colonne * sizeof(char));
			back_track = (int **)malloc(righe * sizeof(int *));
			for (i = 0; i < righe; i++)
				back_track[i] = malloc(colonne * sizeof(int));
		}

		if (a == 2)
		{											 /*SCelta di generare un gameFieldMatrix*/
			pulisci_campo(vett, colonne, righe);	 /*Prepara il gameFieldMatrix mettendo in tutte le celle dei punti interrogativi*/
			pulisci_campomine(mine, colonne, righe); /*Prepara il gameFieldMatrix delle mine mettendo in tutte le celle degli spazi vuoti*/
			srand(time(NULL));						 /*SRAND pe per la funzione set_mine*/
			for (i = 0; i < righe; i++)
				for (j = 0; j < colonne; j++)
					back_track[i][j] = 0; /*Inizializzo il back_track*/

			set_mine(mine, colonne, righe, sommabombe); /*Inserisce le mine in maniera casuale*/
			set_numeri(mine, colonne, righe);			/*Inserisci i numeri in base alla posizione delle mine*/
			system("clear");
			logo();
			if (righe > 29 || colonne > 29)
				printf(screenSize10);
			stampa(vett, righe, colonne, back_track, mine);
			f = fopen("output.txt", "w");
			if (f == NULL)
			{
				printf("%s Ce stato un errore nel salvataggio del file \t\t Riprova\n", player); /*Salvo la partita in un file di nome output */
				return 0;
			}
			salva_automatico(mine, f, righe, colonne);
		} /*chiusura scelta  2 sist*/

		if (f != NULL && a == 1)
		{ /*Preparativi per la scelta 1 (CARICA gameFieldMatrix) */
			pulisci_campo(vett, colonne, righe);
			pulisci_campomine(mine, colonne, righe);
			inserisci_mine(mine, f, righe, colonne, &sommabombe);
			set_numeri(mine, colonne, righe);
			system("clear");
			logo();
			stampa(vett, righe, colonne, back_track, mine);
			f = fopen("output.txt", "w");
			salva_automatico(mine, f, righe, colonne);
		}

		int exit = 1;
		int sommaflag = sommabombe; /*Contiene il numero massimo di bandiere che posso inserire*/
		if (a == 1 || a == 2)
		{
			while (exit != 0 && pilot == 0)
			{ /*while della partita -> esce quando il giocatore ha vinto o quando il giocatore vuole tornare nel playerModality*/
				exit = 0;
				do
				{
					printf(red1 "\n(1) SHOW \t (2) PUT FLAG\t (3) EXIT\t FLAG:%d AIUTI:%d\n", sommaflag, aiuti);
					scelta = -1;
					do
					{
						check(zol, -1, &scelta, 0, -1);
					} while (scelta != 1 && scelta != 2 && scelta != 3);

					if (scelta == 3)
					{
						printf(yellow1 "\n\nEnd\n" reset);
						free(vett);
						free(mine);
						free(back_track);
						return 0;
					}

					printf(red1 "Inserisci le coordinate\n"); /*Coordinate che inserisce l'utente*/
					x = righe + 1;
					y = colonne + 1;
					free(zol);
					zol = NULL;
					byte = 1;
					do
					{
						getline(&zol, &byte, stdin);
						sscanf(zol, "%d, %d", &temp, &temp1);
						if (temp != -1 && temp1 != -1)
						{
							x = temp;
							y = temp1;
							temp = -1;
							temp1 = -1;
						}
					} while (x > righe - 1 || y > colonne - 1);
					free(zol);
					zol = NULL;

					if (back_track[x][y] != 0)
					{ /*Nel caso l'utente tenta di scoprire una cella già scoperta*/
						system("clear");
						stampa(vett, righe, colonne, back_track, mine);
						printf("Questa cella e stata gia scoperta\n");
						printf("Reinserisci le coordinate\n");
					}
				} while (back_track[x][y] != 0);

				if (scelta == 1 && pilot == 0)
				{ /*Caso se l'utente ha deciso di scoprire una cella*/
					nuovoturno(back_track, righe, colonne);
					if (mine[x][y] == '*' && vett[x][y] == '?')
					{ /*Caso se l'utente ha preso una bomba*/
						system("reset");
						stampa_bombe(mine, colonne, righe);
						printf(red1 "\nGAME OVER " reset);
						if (aiuti > 0)
						{
							printf(yellow1 "1 per tornare indietro\t2 per uscire dalla partita\n" reset);
							scanf("%d", &i);
							if (i == 1)
							{
								come_back(vett, back_track, colonne, righe, back); /*Attivazione del back_tracking*/
								back = back + 1;
								sommaflag = sommabombe;
								aiuti--;
								scelta = -3;
							}
							else
							{
								f = fopen("record.txt", "a"); /*Salvo il risultato della partita*/
								if (f != NULL)
								{
									fprintf(f, "%s %s\n", player, "LOSE");
								}
								fclose(f);
								a = -1;
								pilot = playerModality(player);
							}
						}
						else
						{
							f = fopen("record.txt", "a"); /*Salvo il risultato della partita nel caso l'utente ha terminato gli aiuti*/
							if (f != NULL)
								fprintf(f, "%s %s\n", player, "LOSE");

							fclose(f);
							a = -1;
							pilot = playerModality(player);
						}
					}

					if (mine[x][y] == ' ' && vett[x][y] == '?' && pilot == 0) /*Se l'utente scopre una cella dove cè uno spazio*/
						space_finder(x, y, mine, vett, righe, colonne, back_track);

					if (mine[x][y] > '0' && mine[x][y] < '9' && vett[x][y] == '?' && pilot == 0)
					{
						vett[x][y] = mine[x][y]; /*Se l'utente scopre una cella dove cè un numero*/
						back_track[x][y] = 1;	 /*Salvo la coordinata che ho scoperto per il brack_tracking*/
					}
				}			   /*Chiusura scelta 1*/
				int check = 0; /*Variabile che gestisce una bandiera gia scoperta */
				if (scelta == 2 && pilot == 0)
				{ /*Inserisco la bandiera nella coordinata che ha deciso l'utente*/
					if (vett[x][y] == '?' && sommaflag > 0)
					{
						vett[x][y] = '/';
						check = 1;
						sommaflag--;
					}
					if (vett[x][y] == '/' && check != 1)
					{ /*Rimuovo la bandiera nella coordinata che ha deciso l'utente*/
						vett[x][y] = '?';
						sommaflag++;
					}
				}

				for (i = 0; i < righe; ++i)
				{ /*Ciclo che controlla se ho vinto*/
					for (j = 0; j < colonne; ++j)
					{
						if (vett[i][j] == '?')
						{
							exit = 1;
						}
					}
				}
				if (exit == 0 && pilot == 0)
				{ /*Caso quando l'utente vince*/
					printf(red1 "Hai vinto\t \t \t " reset);
					f = fopen("record.txt", "a");
					if (f != NULL)
						fprintf(f, "%s %s\n", player, "WIN");
					fclose(f);
					a = -1;
					pilot = playerModality(player);
				}

				system("clear");
				logo();
				stampa(vett, righe, colonne, back_track, mine);
				check = 0; /*resetto il check per le bandierine*/

			} /*CHIUSURA DEL WHILE*/
			free(vett);
			free(mine);
			free(back_track);
		}

		if (a == 3)
		{					  /*Scelta del Record*/
			char testo[100];  /*Vettore che salva i nomi dei players*/
			char testo1[100]; /*Vettore che salva il risultato della partita */
			int b;			  /*Salvo la scelta di resettare i record o meno*/
			f = fopen("record.txt", "r");
			if (f != NULL)
			{
				system("reset");
				printf(red "\n");
				while (fscanf(f, "%s %s", testo, testo1) > 0)
				{
					printf(red "%s, %s\n" reset, testo, testo1); /*Stampo a video i risultati*/
				}
				printf(blue1 "\n\n\nRESET tutti i record\t(0) or (1) ?\n" reset);
				do
				{
					check(zol, -1, &b, -1, -1);
				} while (b != 0 && b != 1);
				if (b == 0)
				{
					fclose(f);
					remove("record.txt"); /*Rimuovo tutti i record salvati*/
				}
				else
					fclose(f);
			}
			else
				printf(green1 "ERRORE NEL CARICAMENTO DEL FILE\n" reset); /*Caso se il file non è statpo aperto correttamente*/

			pilot = playerModality(player);
		}

		if (a == 4)
		{ /*Scelta 4  Record*/
			int credits = -1;
			credit();
			printf(blue1 "\nplayerModality (1) EXIT (2)\n" reset);
			do
			{
				check(zol, -1, &credits, 0, -1);
			} while (credits != 1 && credits != 2);
			if (credits == 1)
				pilot = playerModality(player);
			if (credits == 2)
				return 0;
		}
	}
	system("reset");
	printf(yellow1 "\n\nEnd\n\n" reset);
	return 0;
}
