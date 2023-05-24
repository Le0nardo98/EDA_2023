/*****************************************************************//**
 * @file   funcoes.h
 * @brief  Conjunto de declarações de funções
 *
 * @author Leonardo Araújo
 * @date   February 2023
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <float.h>
#include <stdbool.h>
#define MAX_LINE_LEN 350
#define MAX_LEN 150

typedef enum ResultadoFuncoes {
	ERRO,
	SUCESSO,
	CLIENTES_NAO_EXISTEM,
	COD_CLIENTE_NAO_EXISTE,
	NIF_CLIENTE_NAO_EXISTE,
	COD_NIF_NAO_EXISTE,
	JA_EXISTE_COD_CLIENTE,
	SALDO_CARR_NEGATIVO,
	SALDO_CARREGADO,
	SALDO_ATUAL,
	MEIOS_NAO_EXISTEM,
	VERTICE_NAO_EXISTE

}ResFuncoes;

typedef struct RegistoMeios
{
	int codigo; // código do meio de mobilidade elétrica
	char tipo[MAX_LEN];
	float bateria;
	float autonomia;
	char geocodigo[MAX_LEN];
	int custo;
	int ativo;
	struct RegistoMeios* seguinteMeio; // endereço de memória para uma struct registo_meio
} Meio;

typedef struct RegistoClientes
{
	int codigo; // código de cliente
	char nome[50]; // nome do cliente
	int NIF; // NIF do cliente
	int saldo; // saldo do cliente
	char geocodigo[MAX_LEN];
	struct RegistoAluguer* comprador;
	struct RegistoClientes* seguinteCliente; // endereço de memória para uma struct registo_clientes
} Cliente;

typedef struct RegistoGestor
{
	int codigo; // Identificação do gestor
	char nome[MAX_LEN]; // nome do gestor
	char senha[MAX_LEN]; // Senha do gestor
	int encriptado; // Se a senha está encriptada.
	char areaResponsavel[MAX_LEN];
	struct RegistoGestor* seguinteGestor; // endereço de memória para uma struct registo_gestor
} Gestor;

typedef struct RegistoAluguer
{
	char dataCompra[MAX_LEN]; // Data de compra de um certo meio
	char nomeComprador[MAX_LEN]; // Nome do comprador.
	char nomeMeioComprado[MAX_LEN]; // Nome do meio.
	int codComprador; // Codigo do comprador.
	struct RegistoAluguer* seguinteCompra;
}Aluguer;

typedef struct RegistoTransacoes
{
	int codigoUtilizador;
	char nomeTransacao[MAX_LEN];
	int montanteCarregado;
	char dataTransacao[MAX_LEN];
	struct RegistoTransacoes* seguinteTransacao;
}Transacao;



typedef struct Adjacente
{
	char vertice[MAX_LEN]; // geocódigo what3words
	float peso;
	struct Adjacente* seguinteAdjacente;
} Adjacente;

typedef struct Grafo
{
	char vertice[MAX_LEN]; // geocódigo what3words
	Adjacente* adjacentes;
	Cliente* clientes;
	Meio* meios; // Lista ligada com os códigos dos meios de transporte existente neste geocódigo
	struct Grafo* seguinteVertice;
} Grafo;

#pragma region STACK

typedef struct Stack
{
	char vertice[MAX_LEN];
	bool visitado;
	struct Stack* seguinteStack;
}Stack;

typedef struct ListaStack
{
	Stack* novaStack;
	struct ListaStack* seguinteLista;
} ListaStack;

#pragma endregion


int menu();

int menuUtilizador();

int menuGestor();


// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------


Meio* lerFicheiroMeios(Meio* inicio, char fileName[]);

ResFuncoes listarMeios(Meio* inicioMeios);

void listarGeocodigo(Meio* inicioMeios);

int escreverFicheiroMeios(Meio* inicioMeios, char fileName[]);

int escreverFicheiroMeiosBin(Meio* inicioMeios, char fileName []);

ResFuncoes existeMeio(Meio* inicioMeios, int cod);

Meio* bubbleSortMeios(Meio* inicioMeios);


// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------


// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES-------------------------------------------------

Cliente* lerFicheiroClientes(Cliente* inicioClientes, char fileName[]);

ResFuncoes listarClientes(Cliente* inicioClientes);

int escreverFicheiroClientes(Cliente* inicioClientes, char fileName[]);

int escreverFicheiroClientesBin(Cliente* inicioClientes, char fileName[]);

Cliente *carregarSaldo(Cliente* inicioClientes, Transacao* inicioTransacao);

ResFuncoes consultaSaldo(Cliente * inicioClientes);

ResFuncoes alterarDadosCliente(Cliente* inicioClientes, Transacao* inicioTransacao);

int existeClienteCod(Cliente* inicioClientes, int cod);

int existeClienteNIF(Cliente* inicioClientes, int NIF);

Cliente* bubbleSortClientes(Cliente* inicioClientes);


// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES-------------------------------------------------


// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES-------------------------------------------------

Gestor* lerFicheiroGestores(Gestor* inicioGestor, char fileName[]);

void listarGestores(Gestor* inicioGestor);

int escreverFicheiroGestores(Gestor* inicioGestor, char fileName[]);

int escreverFicheiroGestoresBin(Gestor* inicioGestor, char fileName[]);

int existeGestor(Gestor* inicioGestor, int cod);

Gestor* bubbleSortGestores(Gestor* inicioGestores);


// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES-------------------------------------------------


// ---------------------------------------------------FUNÇÕES_I-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

Gestor* modoGestor(Gestor* inicioGestores);

Meio* criarMeio(Grafo* inicioGrafo, Meio* inicioMeios, int cod, char nome[], float bat, float aut, int custo, char geo[]);

Meio* inserirMeio(Grafo* inicioGrafo, Meio* inicioMeios, Meio* meio);

Cliente* criarCliente(int cod, char nome[], int NIF, int saldo, char geocodigo[]);

Cliente* inserirCliente(Cliente* inicioClientes, Cliente* cliente);

Gestor* criarGestor(Gestor* inicioGestor, int cod, char nome[], char senha[], char area[]);

Gestor* inserirGestor(Gestor* inicioGestor, Gestor* gestor);

Meio* removerMeio(Meio* inicioMeios, int cod);

Cliente* removerCliente(Cliente* inicioClientes, int cod);

Gestor* removerGestor(Gestor* inicioGestores, int cod);

Meio* alterarMeio(Meio* inicioMeios);

Gestor* alterarGestor(Gestor* inicioGestores);

int encryptSenha(Gestor* inicioGestor, char senha[]);

int decryptSenha(Gestor* inicioGestor, char senha[]);
// ---------------------------------------------------FUNÇÕES_F-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

// -------------------------------------------------------------------FUNÇÕES_I-ALUGUER--------------------------------------------------------------------

void listarAluguer(Aluguer* inicioAluguer);

Aluguer* bubbleSortAluguer(Aluguer* inicioAluguer);

int escreverFicheiroAluguer(Aluguer* inicioAluguer, char fileName[]);

int escreverFicheiroAluguerBin(Aluguer* inicioAluguer, char fileName[]);

Aluguer* realizarAluguer(Cliente* inicioClientes, Aluguer* inicioAluguer, Meio* inicioMeios); //precisa de adaptação

//NOVOS
Aluguer* lerFicheiroAluguer(Aluguer* inicioAluguer, FILE* dadosAluguer);

void listarAluguer(Aluguer* inicioAluguer);

Aluguer* bubbleSortAluguer(Aluguer* inicioAluguer);

Aluguer* realizarAluguer(Cliente* inicioClientes, Aluguer* inicioAluguer, Meio* inicioMeios);

// -------------------------------------------------------------------FUNÇÕES_F-ALUGUER--------------------------------------------------------------------

#pragma region GRAFO
// -------------------------------------------------------------------FUNÇÕES_I-CIDADES--------------------------------------------------------------------
Grafo* lerFicheiroVertices(Grafo* inicioGrafo, Meio* inicioMeios, char fileName[]);

void testeCLientes(Grafo* inicioGrafo);

Grafo* adicionarClientesGrafo(Grafo* inicioGrafo, Cliente* inicioClientes);

Grafo* adicionarMeiosGrafo(Grafo* inicioGrafo, Meio* inicioMeios);

Grafo* lerFicheiroAdjacentes(Grafo* inicioGrafo, char fileName[]);

ResFuncoes localizacaoRaio(Grafo* inicioGrafo, Cliente* inicio_cliente, float raio, int codigo);

void printTestGrafo(Grafo* inicioGrafo);

int escreverFicheiroGrafo(Grafo* inicioGrafo, char fileName []);

int existeVertice(Grafo* inicioGrafo, char verticeVerificar[]);

int inserirVertice(Grafo* inicioGrafo, char verticeInserir[]);

int inserirAdjacente(Grafo* inicioGrafo, char verticeInicial[], char verticeFinal[], float peso);

void listarGrafo(Grafo* inicioGrafo);

int totalVertices(Grafo* inicioGrafo);

void listarAdjacentes(Grafo* inicioGrafo);

ListaStack* caminhoTexto(Grafo* inicioGrafo, char verticeAtual[], Stack* inicioStack, ListaStack* inicioLista);

bool verticeVisitado(Stack* inicioStack, char vertice[]);

#pragma endregion

#pragma region STACK

Stack* push(Stack* inicioStack, char vertice[]);

void mostrarCaminho(ListaStack* inicioStack);
#pragma endregion
// -------------------------------------------------------------------FUNÇÕES_F-CIDADES--------------------------------------------------------------------


#pragma region TRANSACOES
// -------------------------------------------------------------------FUNÇÕES_I-TRANSACOES--------------------------------------------------------------------

Transacao* lerFicheiroTransacao(Transacao* inicioTransacao, char fileName[]);

int escreverFicheiroTransacao(Transacao* inicioTransacao, char fileName[]);

int escreverFicheiroTransacaoBin(Transacao* inicioTransacao, char fileName[]);

void listarTransacao(Transacao* inicioTransacao);

int existeClienteTransacao(Transacao* inicioTransacao, int codVerificar);

Transacao* criarTransacao(Transacao* inicioTransacao, int codigoCliente, int saldoCarregar, char nomeCliente[]);


// -------------------------------------------------------------------FUNÇÕES_F-TRANSACOES--------------------------------------------------------------------
#pragma endregion