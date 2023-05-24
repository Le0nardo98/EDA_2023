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

// ---------------------------------------------------FUNÇÕES_I-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

Gestor* modoGestor(Gestor* inicio_gestores);

Meio* inserirMeio(Grafo* inicio_grafo, Meio* inicio_meios, int cod, char nome[], float bat, float aut, int custo, char geo[]);

Cliente* inserirCliente(Cliente* inicio_clientes, int cod, char nome[], int NIF, int saldo, char geocodigo[]);

Gestor* inserirGestor(Gestor* inicio_gestor, int cod, char nome[], char senha[], char area[]);

Meio* removerMeio(Meio* inicio_meios, int cod);

Cliente* removerCliente(Cliente* inicio_clientes, int cod);

Gestor* removerGestor(Gestor* inicio_gestores, int cod);

Meio* alterarMeio(Meio* inicio_meios);

Gestor* alterarGestor(Gestor* inicio_gestores);

int encryptSenha(Gestor* inicio_gestor, char senha[]);

int decryptSenha(Gestor* inicio_gestor, char senha[]);
// ---------------------------------------------------FUNÇÕES_F-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

// -------------------------------------------------------------------FUNÇÕES_I-ALUGUER--------------------------------------------------------------------

void listarAluguer(Aluguer* inicio_aluguer);

Aluguer* bubbleSortAluguer(Aluguer* inicio_aluguer);

int escreverFicheiroAluguer(Aluguer* inicio_aluguer, char fileName[]);

int escreverFicheiroAluguerBin(Aluguer* inicio_aluguer, char fileName[]);

Aluguer* realizarAluguer(Cliente* inicio_clientes, Aluguer* inicio_aluguer, Meio* inicio_meios); //precisa de adaptação

//NOVOS
Aluguer* lerFicheiroAluguer(Aluguer* inicio_aluguer, FILE* dados_aluguer);

void listarAluguer(Aluguer* inicio_aluguer);

Aluguer* bubbleSortAluguer(Aluguer* inicio_aluguer);

Aluguer* realizarAluguer(Cliente* inicio_clientes, Aluguer* inicio_aluguer, Meio* inicio_meios);