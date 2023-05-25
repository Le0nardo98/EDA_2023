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

struct RegistoGestores;
typedef struct RegistoGestores Gestor;

struct Grafo;
typedef struct Grafo Grafo;

struct RegistoMeios;
typedef struct RegistoMeios Meio;

struct RegistoAlugueres;
typedef struct RegistoAlugueres Aluguer;

struct RegistoClientes;
typedef struct RegistoClientes Cliente;

// ---------------------------------------------------FUNÇÕES_I-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

Gestor* modoGestor(Gestor* inicio_gestores);

Meio* criarMeio(Grafo* inicioGrafo, Meio* inicioMeios, int cod, char nome[], float bat, float aut, int custo, char geo[]);

Meio* inserirMeio(Grafo* inicioGrafo, Meio* inicioMeios, Meio* meio);

Cliente* criarCliente(int cod, char nome[], int NIF, int saldo, char geocodigo[]);

Cliente* inserirCliente(Cliente* inicioClientes, Cliente* cliente);

Gestor* criarGestor(Gestor* inicioGestor, int cod, char nome[], char senha[], char area[]);

Gestor* inserirGestor(Gestor* inicioGestor, Gestor* gestor);

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