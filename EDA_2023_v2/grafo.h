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

struct Grafo;
typedef struct Grafo Grafo;

struct RegistoMeios;
typedef struct RegistoMeios Meio;

struct RegistoClientes;
typedef struct RegistoClientes Cliente;

struct RegistoTransacoes;
typedef struct RegistoTransacoes Transacao;

struct Stack;
typedef struct Stack Stack;

struct ListaStack;
typedef struct ListaStack ListaStack;

#pragma region GRAFO
// -------------------------------------------------------------------FUN��ES_I-CIDADES--------------------------------------------------------------------
Grafo* lerFicheiroVertices(Grafo* inicio_grafo, Meio* inicio_meios, FILE* dados_vertices);

void testeCLientes(Grafo* inicio_grafo);

Grafo* adicionarClientesGrafo(Grafo* inicio_grafo, Cliente* inicio_clientes);

Grafo* adicionarMeiosGrafo(Grafo* inicio_grafo, Meio* inicio_meios);

Grafo* lerFicheiroAdjacentes(Grafo* inicio_grafo, FILE* dados_adjacentes);

int localizacaoRaio(Grafo* inicio_grafo, Cliente* inicio_cliente, float raio, int codigo, char tipoMeio[]);

void printTestGrafo(Grafo* inicio_grafo);

int escreverFicheiroGrafo(Grafo* inicio_grafo, char fileName []);

int existeVertice(Grafo* inicio_grafo, char verticeVerificar[]);

int inserirVertice(Grafo* inicio_grafo, char verticeInserir[]);

int inserirAdjacente(Grafo* inicio_grafo, char verticeInicial[], char verticeFinal[], float peso);

void listarGrafo(Grafo* inicio_grafo);

int totalVertices(Grafo* inicio_grafo);

void listarAdjacentes(Grafo* inicio_grafo);

ListaStack* caminhoTexto(Grafo* inicioGrafo, char verticeAtual[], Stack* inicioStack, ListaStack* inicioLista);

bool verticeVisitado(Stack* inicio_stack, char vertice[]);

#pragma endregion

#pragma region STACK

Stack* inserirStack(Stack* inicioStack, char vertice[]);

Stack* push(Stack* inicio_stack, char vertice[]);

void mostrarCaminho(ListaStack* inicio_stack);
#pragma endregion
// -------------------------------------------------------------------FUN��ES_F-CIDADES--------------------------------------------------------------------


#pragma region TRANSACOES
// -------------------------------------------------------------------FUN��ES_I-TRANSACOES--------------------------------------------------------------------

Transacao* lerFicheiroTransacao(Transacao* inicio_transacao, FILE* dados_transacao);

int escreverFicheiroTransacao(Transacao* inicio_transacao, char fileName[]);

int escreverFicheiroTransacaoBin(Transacao* inicio_transacao, char fileName[]);

void listarTransacao(Transacao* inicio_transacao);

int existeClienteTransacao(Transacao* inicio_transacao, int codVerificar);

Transacao* criarTransacao(Transacao* inicio_transacao, int codigoCliente, int saldoCarregar, char nomeCliente[]);

ListaStack* mostrarTeste(Grafo* inicioGrafo, char verticeAtual[], Stack* inicioStack, ListaStack* inicioLista, float tamanho);

ListaStack* retirarStackMaior(ListaStack* inicioLista);

ListaStack* mostrarCaminhoIda(Grafo* inicioGrafo, char verticeAtual[], Stack* inicioStack, ListaStack* inicioLista, float tamanho);

ListaStack* mostrarCaminhoVolta(Grafo* inicioGrafo, char verticeAtual[], char verticeDestino[], Stack* inicioStack, ListaStack* inicioLista, float tamanho);

ListaStack* mostrarCaminhoCamiao(Grafo* inicioGrafo, char verticeAtual[], Stack* inicioStack, ListaStack* inicioLista, float tamanho);

ListaStack* adicionarCaminho(Stack* caminho, ListaStack* listaCaminhos, float tamanho);

void obterUltimoVertice(ListaStack* inicioLista, char* vertice);

// -------------------------------------------------------------------FUN��ES_F-TRANSACOES--------------------------------------------------------------------
#pragma endregion