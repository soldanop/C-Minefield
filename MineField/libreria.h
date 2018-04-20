#ifndef progetto_H
#define progetto_H
#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define WHITE "\x1b[97m"
#define YELLOW "\x1b[33m"
#define REDC "\x1b[41m"
#define specialred "\x1b[1;31m"
#define specialblue "\x1b[1;34m"
#define specialyellow "\x1b[1;33m"
#define specialgreen "\x1b[1;32m"
#define specialcyan "\x1b[1;96m"
#define lampred "\x1b[7;31m"
#define lampyellow "\x1b[7;33m"
#define lampblue "\x1b[7;34m"
#define line "\x1b[5;30m"
#define size "\x1b[8;20;150t"
#define size10 "\x1b[8;100;120t"
#define reverse "\x1b[7;32m"
#define reset "\x1b[0m"


int menu_principale(int a, char player[10]);

void logo();

void cerca_spazi(int x,int y,char **campo,char **vett, int righe, int colonne, int **back_track);

void pulisci_campo(char **vett, int colonne, int righe);

void pulisci_campomine(char **vett, int colonne, int righe);

void set_numeri(char **vett,int colonne, int righe);

void set_mine(char **vett, int colonne, int righe, int cont);

int stampa(char **vett, int righe, int colonne, int **back_track, char **mine);

int stampa1(int **vett, int righe, int colonne);

int stampa_bombe(char **mine, int colonne, int righe);

void inserisci_mine(char **vett,FILE *f,int righe, int colonne,int *sommabombe);

int esci(char **vett,int righe,int colonne, int* flag, int sommabombe);

void nuovoturno(int **back,int righe, int colonne);

int stampa_mine(char **vett, int righe, int colonne);

void come_back(char** vett, int **back_track, int colonne, int righe, int turni);

void salva_automatico(char **mine, FILE *f, int righe, int colonne);

int credit();

void intro();

int check(char *zol,int temp,int *parametro,int max,int segno);

#endif
