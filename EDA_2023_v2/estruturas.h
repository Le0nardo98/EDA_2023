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
	int codigo; // c�digo do meio de mobilidade el�trica
	char tipo[MAX_LEN];
	float bateria;
	float autonomia;
	char geocodigo[MAX_LEN];
	int custo;
	int ativo;
	struct RegistoMeios* seguinteMeio; // endere�o de mem�ria para uma struct registo_meio
} Meio;

typedef struct RegistoClientes
{
	int codigo; // c�digo de cliente
	char nome[50]; // nome do cliente
	int NIF; // NIF do cliente
	int saldo; // saldo do cliente
	char geocodigo[MAX_LEN];
	struct RegistoAlugueres* comprador;
	struct RegistoClientes* seguinteCliente; // endere�o de mem�ria para uma struct registo_clientes
} Cliente;

typedef struct RegistoGestores
{
	int codigo; // Identifica��o do gestor
	char nome[MAX_LEN]; // nome do gestor
	char senha[MAX_LEN]; // Senha do gestor
	int encriptado; // Se a senha est� encriptada.
	char areaResponsavel[MAX_LEN];
	struct RegistoGestores* seguinteGestor; // endere�o de mem�ria para uma struct registo_gestor
} Gestor;

typedef struct RegistoAlugueres
{
	char dataCompra[MAX_LEN]; // Data de compra de um certo meio
	char nomeComprador[MAX_LEN]; // Nome do comprador.
	char nomeMeioComprado[MAX_LEN]; // Nome do meio.
	int codComprador; // Codigo do comprador.
	struct RegistoAlugueres* seguinteCompra;
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
	char vertice[MAX_LEN]; // geoc�digo what3words
	float peso;
	Meio* meios;
	struct Adjacente* seguinteAdjacente;
} Adjacente;

typedef struct Grafo
{
	char vertice[MAX_LEN]; // geoc�digo what3words
	Adjacente* adjacentes;
	Cliente* clientes;
	Meio* meios; // Lista ligada com os c�digos dos meios de transporte existente neste geoc�digo
	struct Grafo* seguinteVertice;
} Grafo;

#pragma region STACK

typedef struct Stack
{
	char vertice[MAX_LEN];
	bool visitado;
	float dist;
	bool veiculo;
	struct Stack* seguinteStack;
}Stack;

typedef struct ListaStack
{
	Stack* novaStack;
	float tamanho;
	struct ListaStack* seguinteLista;
} ListaStack;

#pragma endregion

int menu();

int menu_utilizador();

int menu_gestor();