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
#ifndef estruturas_h
#include "estruturas.h"
#define estruturas_h
#endif 

// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES-------------------------------------------------

Gestor* lerFicheiroGestores(Gestor* inicio_gestor, FILE* dados_gestor);

void listarGestores(Gestor* inicio_gestor);

int escreverFicheiroGestores(Gestor* inicio_gestor, char fileName[]);

int escreverFicheiroGestoresBin(Gestor* inicio_gestor, char fileName[]);

int existeGestor(Gestor* inicio_gestor, int cod);

Gestor* bubbleSortGestores(Gestor* inicio_gestores);