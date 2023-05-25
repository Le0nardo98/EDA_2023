/**
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <float.h>
#include <stdbool.h>
#define MAX_LINE_LEN 350
#define MAX_LEN 150

struct RegistoMeios;
typedef struct RegistoMeios Meio;

enum ResultadoFuncoes;
typedef enum ResultadoFuncoes ResFuncoes;

// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------

Meio* lerFicheiroMeios(Meio* inicio, FILE* dados_meios);

ResFuncoes listarMeios(Meio* inicio_meios);

void listarGeocodigo(Meio* inicio_meios);

int escreverFicheiroMeios(Meio* inicio_meios, char fileName[]);

int escreverFicheiroMeiosBin(Meio* inicio_meios, char fileName []);

ResFuncoes existeMeio(Meio* inicio_meios, int cod);

Meio* bubbleSortMeios(Meio* inicio_meios);

