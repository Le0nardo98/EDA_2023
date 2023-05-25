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

struct RegistoClientes;
typedef struct RegistoClientes Cliente;

struct RegistoTransacoes;
typedef struct RegistoTransacoes Transacao;

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