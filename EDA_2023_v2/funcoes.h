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
	char area_responsavel[MAX_LEN];
	struct RegistoGestor* seguinteGestor; // endereço de memória para uma struct registo_gestor
} Gestor;

typedef struct RegistoAluguer
{
	char data_compra[MAX_LEN]; // Data de compra de um certo meio
	char nome_comprador[MAX_LEN]; // Nome do comprador.
	char nome_meio_comprado[MAX_LEN]; // Nome do meio.
	int cod_comprador; // Codigo do comprador.
	struct RegistoAluguer* seguinteCompra;
}Aluguer;

typedef struct RegistoTransacoes
{
	int codigo_utilizador;
	char nome_transacao[MAX_LEN];
	int montante_carregado;
	char data_transacao[MAX_LEN];
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
	struct Grafo* seguinte_vertice;
} Grafo;

#pragma region STACK

typedef struct Stack
{
	char vertice[MAX_LEN];
	bool visitado;
	struct Stack* seguinte_stack;
}Stack;

typedef struct ListaStack
{
	Stack* novaStack;
	struct ListaStack* seguinte_lista;
} ListaStack;

#pragma endregion


int menu();

int menu_utilizador();

int menu_gestor();


// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------


Meio* lerFicheiroMeios(Meio* inicio, FILE* dados_meios);

ResFuncoes listarMeios(Meio* inicio_meios);

void listarGeocodigo(Meio* inicio_meios);

int escreverFicheiroMeios(Meio* inicio_meios, char fileName[]);

int escreverFicheiroMeiosBin(Meio* inicio_meios, char fileName []);

ResFuncoes existeMeio(Meio* inicio_meios, int cod);

Meio* bubbleSortMeios(Meio* inicio_meios);



// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------





// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES-------------------------------------------------

Cliente* lerFicheiroClientes(Cliente* inicio_clientes, FILE* dados_clientes);

ResFuncoes listarClientes(Cliente* inicio_clientes);

int escreverFicheiroClientes(Cliente* inicio_clientes, char fileName[]);

int escreverFicheiroClientesBin(Cliente* inicio_clientes, char fileName[]);

Cliente *carregarSaldo(Cliente* inicio_clientes, Transacao* inicioTransacao);

ResFuncoes consultaSaldo(Cliente * inicio_clientes);

ResFuncoes alterarDadosCliente(Cliente* inicio_clientes, Transacao* inicioTransacao);

int existeClienteCod(Cliente* inicio_clientes, int cod);

int existeClienteNIF(Cliente* inicio_clientes, int NIF);

Cliente* bubbleSortClientes(Cliente* inicio_clientes);


// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES-------------------------------------------------


// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES-------------------------------------------------

Gestor* lerFicheiroGestores(Gestor* inicio_gestor, FILE* dados_gestor);

void listarGestores(Gestor* inicio_gestor);

int escreverFicheiroGestores(Gestor* inicio_gestor, char fileName[]);

int escreverFicheiroGestoresBin(Gestor* inicio_gestor, char fileName[]);

int existeGestor(Gestor* inicio_gestor, int cod);

Gestor* bubbleSortGestores(Gestor* inicio_gestores);


// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES-------------------------------------------------


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

// -------------------------------------------------------------------FUNÇÕES_F-ALUGUER--------------------------------------------------------------------

#pragma region GRAFO
// -------------------------------------------------------------------FUNÇÕES_I-CIDADES--------------------------------------------------------------------
Grafo* lerFicheiroVertices(Grafo* inicio_grafo, Meio* inicio_meios, FILE* dados_vertices);

void testeCLientes(Grafo* inicio_grafo);

Grafo* adicionarClientesGrafo(Grafo* inicio_grafo, Cliente* inicio_clientes);

Grafo* adicionarMeiosGrafo(Grafo* inicio_grafo, Meio* inicio_meios);

Grafo* lerFicheiroAdjacentes(Grafo* inicio_grafo, FILE* dados_adjacentes);

ResFuncoes localizacaoRaio(Grafo* inicio_grafo, Cliente* inicio_cliente, float raio, int codigo);

void printTestGrafo(Grafo* inicio_grafo);

int escreverFicheiroGrafo(Grafo* inicio_grafo, char fileName []);

int existeVertice(Grafo* inicio_grafo, char verticeVerificar[]);

int inserirVertice(Grafo* inicio_grafo, char verticeInserir[]);

int inserirAdjacente(Grafo* inicio_grafo, char verticeInicial[], char verticeFinal[], float peso);

void listarGrafo(Grafo* inicio_grafo);

int totalVertices(Grafo* inicio_grafo);

void listarAdjacentes(Grafo* inicio_grafo);

ListaStack* caminhoTexto(Grafo* inicio_grafo, char verticeAtual[], char verticeDestino[], Stack* inicio_stack, ListaStack* inicio_lista);

bool verticeVisitado(Stack* inicio_stack, char vertice[]);

#pragma endregion

#pragma region STACK

Stack* push(Stack* inicio_stack, char vertice[]);

void mostrarCaminho(ListaStack* inicio_stack);
#pragma endregion
// -------------------------------------------------------------------FUNÇÕES_F-CIDADES--------------------------------------------------------------------


#pragma region TRANSACOES
// -------------------------------------------------------------------FUNÇÕES_I-TRANSACOES--------------------------------------------------------------------

Transacao* lerFicheiroTransacao(Transacao* inicio_transacao, FILE* dados_transacao);

int escreverFicheiroTransacao(Transacao* inicio_transacao, char fileName[]);

int escreverFicheiroTransacaoBin(Transacao* inicio_transacao, char fileName[]);

void listarTransacao(Transacao* inicio_transacao);

int existeClienteTransacao(Transacao* inicio_transacao, int codVerificar);

Transacao* criarTransacao(Transacao* inicio_transacao, int codigoCliente, int saldoCarregar, char nomeCliente[50]);


// -------------------------------------------------------------------FUNÇÕES_F-TRANSACOES--------------------------------------------------------------------
#pragma endregion