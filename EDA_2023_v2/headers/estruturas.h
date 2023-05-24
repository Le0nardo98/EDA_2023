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

} ResFuncoes;

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
	char nome[MAX_LEN]; // nome do cliente
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