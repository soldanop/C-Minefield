#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "minefieldHelper.h"

void intro()
{
	time_t now = time(NULL);
	system("clear");
	printf(screenSize);
	printf(blue1 "\n\n\n\n\t\t\t\t\t\t\tFinal Project course Programming Module.2\n\n" reset);
	printf(red1 "\n\t\t\t\t\t\t\t  Ca'Foscari Univerisity 2016/2017\n\n" reset);
	printf(green1 "\n\t\t\t\t\t\t\t\tPasquale Soldano\n\n" reset);
	while (difftime(time(NULL), now) != 10);
	now = time(NULL);
	system("clear");
	printf(red1 "\n *   \t \t \t * \t \t \t \t *\t \t * \t * \t \t * \t \t  * \t * \t * \n" reset);
	printf(green1 "\n\n\n\n\t\t\t\t\t\t\t\t       M I N E F I E L D \n\n\n" reset);
	printf(red1 "\n *   \t \t \t * \t \t \t \t *\t \t * \t * \t \t * \t \t  * \t * \t * \n" reset);
	while (difftime(time(NULL), now) != 5);
}

int playerModality(char player[10])
{
	system("clear");
	printf(screenSize);
	printf(blue1 "Inserisci il tuo nick\n");
	scanf("%s", player);
	int modality = -1;
	while (modality > 5 || modality < 1)
	{
		system("clear");
		printf(red "Welcome %s to MineField\n\n" reset, player);
		printf(cyan "Final Project course Programming Module.2\n\n\n" reset);
		printf(yellow "Please choose:\n\n" reset);
		printf(lime "\t\t\t\t _________________________________________________\n" reset);
		printf(red1 "\t\t\t1->\t|           LOAD FIELD FROM FILE          |\n" reset);
		printf(yellow1 "\t\t\t2->\t|               GENERATE FIELD            |\n" reset);
		printf(green1 "\t\t\t3->\t|                 RECORD                  |\n" reset);
		printf(cyan "\t\t\t4->\t|                 CREDIT                  |\n" reset);
		printf(blue1 "\t\t\t5->\t|                  EXIT                   |\n" reset);
		printf(lime "\t\t\t\t _________________________________________________\n" reset);
		printf(cyan "\n");

		char *vett = NULL;
		size_t byte = 1;
		int modalityFromUser = -1;
		getline(&vett, &byte, stdin);
		sscanf(vett, "%d" reset, &modalityFromUser);
		modality = modalityFromUser != -1 ? modalityFromUser : -1;
		printf("\n");
	}

	return modality;
}

void logo()
{
	printf(red1 " _____________________\n" reset);
	printf(red1 "|       MINEFIELD     |\n" reset);
	printf(red1 "|_____________________|\n" reset);
	printf("\n");
}

int credit()
{
	printf("\n\n\n\n");
	system("reset");
	printf(cyan "\t\t\t\t\tDeveloper:\n\n\n" reset);
	printf("\t\t\t    P A S Q U A L E  S O L D A N O\n" reset);
	return 0;
}

void space_finder(int x, int y, char **gameFieldMatrix, char **vett, int righe, int colonne, int **back_track)
{
	if (vett[x][y] != '/')
	{
		if (gameFieldMatrix[x][y] > '0' && gameFieldMatrix[x][y] < '9')
		{
			vett[x][y] = '&';
			back_track[x][y] = 1; /*for array back_tracking*/
		}
		if (gameFieldMatrix[x][y] == ' ' && back_track[x][y] == 0)
		{
			vett[x][y] = '&';
			back_track[x][y] = 1;
			if (x - 1 > -1 && x - 1 < righe && y > -1 && y < colonne)
				space_finder(x - 1, y, gameFieldMatrix, vett, righe, colonne, back_track); /*UP*/

			if (x - 1 > -1 && x - 1 < righe && y - 1 > -1 && y - 1 < colonne)
				space_finder(x - 1, y - 1, gameFieldMatrix, vett, righe, colonne, back_track); /*UP LEFT*/

			if (x > -1 && x < righe && y - 1 > -1 && y - 1 < colonne)
				space_finder(x, y - 1, gameFieldMatrix, vett, righe, colonne, back_track); /*LEFT*/

			if (x + 1 > -1 && x + 1 < righe && y - 1 > -1 && y - 1 < colonne)
				space_finder(x + 1, y - 1, gameFieldMatrix, vett, righe, colonne, back_track); /*LEFT DOWN*/

			if (x + 1 > -1 && x + 1 < righe && y > -1 && y < colonne)
				space_finder(x + 1, y, gameFieldMatrix, vett, righe, colonne, back_track); /*DOWN*/

			if (x + 1 > -1 && x + 1 < righe && y + 1 > -1 && y + 1 < colonne)
				space_finder(x + 1, y + 1, gameFieldMatrix, vett, righe, colonne, back_track); /*RIGH DOWN*/

			if (x > -1 && x < righe && y + 1 > -1 && y + 1 < colonne)
				space_finder(x, y + 1, gameFieldMatrix, vett, righe, colonne, back_track); /*RIGH*/

			if (x - 1 > -1 && x - 1 < righe && y + 1 > -1 && y + 1 < colonne)
				space_finder(x - 1, y + 1, gameFieldMatrix, vett, righe, colonne, back_track); /*RIGHT UP*/
		}
	}
}

void pulisci_campo(char **vett, int colonne, int righe)
{
	int i, j;
	for (i = 0; i < righe; i++)
	{ /*Funzione che inizializza il gameFieldMatrix che vedrà l'utente*/
		for (j = 0; j < colonne; j++)
		{
			vett[i][j] = '?';
		}
		printf("\n");
	}
}

void pulisci_campomine(char **vett, int colonne, int righe)
{
	int i, j;
	for (i = 0; i < righe; i++)
	{ /*Funzione che inzializza il gameFieldMatrix che conterrà mine,numeri e spazi*/
		for (j = 0; j < colonne; j++)
		{
			vett[i][j] = ' ';
		}
		printf("\n");
	}
}

void set_numeri(char **vett, int colonne, int righe)
{
	int r, c, i, j;
	int cont = 0;
	/*Funzione che posiziona i numeri in base alla posizione delle mine*/
	for (i = 0; i < righe; i++)
	{
		for (j = 0; j < colonne; j++)
		{
			r = i - 1; /*R e C sono 2 variabili che girano intorno alla cella per cercare mine */
			c = j;
			if (r > -1 && r < righe && c > -1 && c < colonne && vett[r][c] == '*') /*UP*/ /*Negli if faccio dei controlli per non uscire fuori dalla matrice*/
				cont++;

			r = i - 1;
			c = j - 1;

			if (r > -1 && r < righe && c > -1 && c < colonne && vett[r][c] == '*') /*UP LEFT*/
				cont++;

			r = i;
			c = j - 1;

			if (r > -1 && r < righe && c > -1 && c < colonne && vett[r][c] == '*') /*LEFT*/
				cont++;

			r = i + 1;
			c = j - 1;

			if (r > -1 && r < righe && c > -1 && c < colonne && vett[r][c] == '*') /*LEFT DOWN*/
				cont++;

			r = i + 1;
			c = j;
			if (r > -1 && r < righe && c > -1 && c < colonne && vett[r][c] == '*') /*DOWN*/
				cont++;

			r = i + 1;
			c = j + 1;

			if (r > -1 && r < righe && c > -1 && c < colonne && vett[r][c] == '*') /*RIGHT DOWN*/
				cont++;

			r = i;
			c = j + 1;

			if (r > -1 && r < righe && c > -1 && c < colonne && vett[r][c] == '*') /*RIGHT*/
				cont++;

			r = i - 1;
			c = j + 1;
			if (r > -1 && r < righe && c > -1 && c < colonne && vett[r][c] == '*') /*RIGHT UP*/
				cont++;

			if (vett[i][j] != '*' && cont != 0)
				vett[i][j] = cont + '0'; /*Metto nella matrice il numero di bombe che sono state trovare da R e C*/

			cont = 0; /*Resetto per ripetre il ciclo su altre celle*/

		} /*close ciclo interno*/

	} /*cloce ciclo esterno*/

} /*close della funzione*/

void set_mine(char **vett, int colonne, int righe, int cont)
{
	int i, j, k;
	/*Funzione che inserisce le mine in maniera casuale in modo ricorsivo*/
	if (cont != 0)
	{
		k = rand() % (righe * colonne);
		i = k / colonne;
		j = k % colonne;

		if (vett[i][j] == '*')
			set_mine(vett, colonne, righe, cont);

		else
		{
			vett[i][j] = '*';
			set_mine(vett, colonne, righe, --cont);
		}
	}
}

int stampa(char **vett, int righe, int colonne, int **back_track, char **mine)
{
	int i, j;
	int cont = 0;

	printf(blue1 " ||" reset); /*Funzione che stampa a video il gameFieldMatrix dove giocherà l'utente*/
	for (i = 0; i < colonne; i++)
	{
		printf(blue1 "%d |" reset, i);
	}
	printf(blue1 "||\n" reset);
	for (i = 0; i < righe; i++)
	{
		printf(blue1 "%d||" reset, cont++);
		for (j = 0; j < colonne; j++)
		{

			if (back_track[i][j] == 0 && vett[i][j] != '/')
			{
				vett[i][j] = '?';
				printf(white "%c " reset, vett[i][j]);
				printf("|");
			}
			if (vett[i][j] == '/')
			{
				printf(white "%c " reset, vett[i][j]);
				printf("|");
			}
			if (back_track[i][j] != 0)
			{
				printf(yellow1 "%c " reset, mine[i][j]);
				printf("|");
			}
		}
		printf(blue1 "||%d\n" reset, cont - 1);
	}
	return 0;
}

int stampa_bombe(char **mine, int colonne, int righe)
{
	int i, j;
	int cont = 0;
	/*Funzione stampa le mine che ci sono nel gameFieldMatrix, usata nel Gameover*/
	printf(blue1 " ||" reset);
	for (i = 0; i < colonne; i++)
	{
		printf(blue1 "%d |" reset, i);
	}
	printf(blue1 "||\n" reset);
	for (i = 0; i < righe; i++)
	{
		printf(blue1 "%d||" reset, cont++);
		for (j = 0; j < colonne; j++)
		{
			if (mine[i][j] == '*')
			{
				printf(red1 "%c " reset, mine[i][j]);
				printf(blue1 "|" reset);
			}
			else
			{
				printf("  ");
				printf(blue1 "|" reset);
			}
		}
		printf(blue1 "||%d\n" reset, cont - 1);
	}

	return 0;
}

void inserisci_mine(char **vett, FILE *f, int righe, int colonne, int *sommabombe)
{
	int x, y;
	int i, j; /*Funzione che inserisce le mine in base ai valori presi da file*/

	/*Funzione che prende da FILE la posizione delle mine e inserisce le mine nella matrice */
	while (fscanf(f, "%d, %d", &x, &y) && !feof(f))
	{
		(*sommabombe)++;
		vett[x][y] = '*';
	}
	fclose(f);
}

void nuovoturno(int **back, int righe, int colonne)
{
	int i, j;
	for (i = 0; i < righe; ++i)
	{
		for (j = 0; j < colonne; ++j)
		{ /*Funzione che aggorna il back_tracking ad ogni turno incrementando i valori delle celle*/
			if (back[i][j] != 0)
			{
				(back[i][j])++;
			}
		}
	}

} /*Chiusura della funzione*/

void come_back(char **vett, int **back_track, int colonne, int righe, int turni)
{
	int i, j; /*Funzione che torna indietro di n mosse in base alla vita del giocatore*/

	for (i = 0; i < righe; ++i)
	{
		for (j = 0; j < colonne; ++j)
		{
			if (vett[i][j] != '/')
			{
				if (back_track[i][j] != 0)
				{
					if (back_track[i][j] <= turni)
					{
						vett[i][j] = '?';
						back_track[i][j] = (back_track[i][j] - turni);
						if (back_track[i][j] < 0)
						{
							back_track[i][j] = 0;
						}
					}
					else
						back_track[i][j] = (back_track[i][j] - turni);
				}
			}
		}
	}
}

void salva_automatico(char **mine, FILE *f, int righe, int colonne)
{
	int i, j;
	fprintf(f, "%d,%d\n\n", righe, colonne);
	for (i = 0; i < righe; i++)
	{ /*Funzione che salva le mine della partita corrente nel file output.txt*/
		for (j = 0; j < colonne; ++j)
		{
			if (mine[i][j] == '*')
				fprintf(f, "%d,%d\n", i, j);
		}
	}

	fclose(f);
}

int check(char *zol, int temp, int *parametro, int max, int segno)
{
	size_t byte = 1;
	free(zol);
	zol = NULL;
	if (segno == -1)
	{ /*segno <*/
		do
		{
			getline(&zol, &byte, stdin); /*Funzione utilizzata per il controllo del input dall'utente con getline*/
			sscanf(zol, "%d", &temp);
			if (temp != -1)
			{
				*parametro = temp;
				temp = -1;
			}
		} while (*parametro < max && temp == -1); /*Parametro inserito dall'utente che vuole controllare*/
	}
	if (segno == 1)
	{ /*Segno >*/
		do
		{
			getline(&zol, &byte, stdin);
			sscanf(zol, "%d", &temp);
			if (temp != -1)
			{
				*parametro = temp;
				temp = -1;
			}
		} while (*parametro > max && temp == -1);
	}
}
