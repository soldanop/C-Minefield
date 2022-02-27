#ifndef progetto_H
#define progetto_H
#define red "\x1b[31m"
#define white "\x1b[97m"
#define yellow "\x1b[33m"
#define red1 "\x1b[1;31m"
#define blue1 "\x1b[1;34m"
#define yellow1 "\x1b[1;33m"
#define green1 "\x1b[1;32m"
#define cyan "\x1b[1;96m"
#define lime "\x1b[5;30m"
#define screenSize "\x1b[8;20;150t"
#define screenSize10 "\x1b[8;100;120t"
#define reset "\x1b[0m"

int playerModality(char player[10]);

void logo();

void space_finder(int x, int y, char **gameFieldMatrix, char **vett, int righe, int colonne, int **back_track);

void pulisci_campo(char **vett, int colonne, int righe);

void pulisci_campomine(char **vett, int colonne, int righe);

void set_numeri(char **vett, int colonne, int righe);

void set_mine(char **vett, int colonne, int righe, int cont);

int stampa(char **vett, int righe, int colonne, int **back_track, char **mine);

int stampa1(int **vett, int righe, int colonne);

int stampa_bombe(char **mine, int colonne, int righe);

void inserisci_mine(char **vett, FILE *f, int righe, int colonne, int *sommabombe);

int esci(char **vett, int righe, int colonne, int *flag, int sommabombe);

void nuovoturno(int **back, int righe, int colonne);

int stampa_mine(char **vett, int righe, int colonne);

void come_back(char **vett, int **back_track, int colonne, int righe, int turni);

void salva_automatico(char **mine, FILE *f, int righe, int colonne);

int credit();

void intro();

int check(char *zol, int temp, int *parametro, int max, int segno);

#endif
