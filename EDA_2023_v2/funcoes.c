/*****************************************************************//**
 * @file   funcoes.c
 * @brief  Conjunto de funções
 *
 * @author Leonardo Araújo
 * @date   February 2023
 *********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include "funcoes.h"
#define MAX_LEN 150


// ---------------------------------------------------------------MENU---------------------------------------------------------------

#pragma region MENU

// Menu inicial do programa. Retorna o valor escolhido pelo utilizador.
int menu()
{
    int escolha;
    printf("O que pretende fazer?\n");
    printf("1 - Menu utilizador.\n");
    printf("2 - Menu Gestor.\n");
    printf("0 - Sair.\n");
    printf("A sua escolha: ");
    (void)scanf("%d", &escolha);
    system("cls");

    return escolha;
}
#pragma endregion 

#pragma region menuGestor

//Menu do gestor. Retorna a opção escolhida pelo gestor, para executar uma tarefa.
int menuGestor()
{
    int escolha;
    printf("\nO que pretende fazer?\n");
    printf("1 - Listar os clientes existentes.\n");
    printf("2 - Listar os gestores existentes.\n");
    printf("3 - Listar os meios existentes.\n");
    printf("4 - Adicionar Clientes.\n");
    printf("5 - Adicionar Meios.\n");
    printf("6 - Adicionar Gestor.\n");
    printf("7 - Remover Meio.\n");
    printf("8 - Remover Cliente.\n");
    printf("9 - Remover Gestor.\n");
    printf("10 - Historico de compras.\n");
    printf("11 - Alterar dados gestor.\n");
    printf("12 - Alterar dados meios.\n");
    printf("13 - Alterar dados cliente.\n");
    printf("14 - Media autonomia.\n");
    printf("15 - Listar transacoes.\n");
    printf("16 - Adicionar Adjacentes.\n");
    printf("0 - Sair.\n");
    printf("A sua escolha: ");
    (void)scanf("%d", &escolha);

    return escolha;
}

#pragma endregion

#pragma region menuUtilizador

//Menu do utilizador. Retorna o valor escolhido, para execução de uma tarefa.
int menuUtilizador()
{
    int escolha;
    printf("\nO que pretende fazer?\n");
    printf("1 - Listar os meios existentes.\n");
    printf("2 - Carregamento de saldo.\n");
    printf("3 - Consulta de saldo.\n");
    printf("4 - Alteracao dos seus dados.\n");
    printf("5 - Alugar algum meio.\n");
    printf("6 - Listar por geocodigo.\n");
    printf("0 - Sair.\n");
    printf("A sua escolha: ");
    scanf("%d", &escolha);
    system("cls");

    return escolha;
}
#pragma endregion

// -------------------------------------------------------------FIM-MENU-------------------------------------------------------------


// -------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAcaO DE MEIOS
// Ler ficheiro de texto, contendo informação sobre os meios.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
/*
*/
Meio* lerFicheiroMeios(Meio* inicioMeios, char fileName[])
{
    FILE* dadosMeios = fopen(fileName, "rt");

    // Definição de variáveis.
    char linha[MAX_LINE_LEN];
    // Usando a função fgets, lemos a partir do ficheiro dadosMeios todo o seu conteúdo, onde é armazenado em cada novoNodo criado
    // Depois é atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    // Contendo assim toda as informações e pointers necessários para criar a lista ligada.
    while (fgets(linha, MAX_LINE_LEN, dadosMeios))
    {
        // Enquanto é possivel obter texto do ficheiro dadosMeios, irá ser criado um novo espaço na memória para a struct meios
        // A cada iteração é atribuido todo o conteudo obtido ao inicioMeios, criando assim uma lista ligada.
        Meio* novoNodo = malloc(sizeof(Meio));
        sscanf(linha, "%d;%[^;];%f;%f;%d;%[^;];%d\n", &novoNodo->codigo, novoNodo->tipo, &novoNodo->bateria, &novoNodo->autonomia, &novoNodo->custo, novoNodo->geocodigo, &novoNodo->ativo);
        // O seguinte valor de memória é igual a inicioMeios que foi inicializado a NULL, para de seguida ser possivel atribuir outro elemento da lista ligada.
        novoNodo->seguinteMeio = inicioMeios;
        // inicioMeios vai obter toda a informação que foi lida por novoNodo
        inicioMeios = novoNodo;
    }
    fclose(dadosMeios);
    return inicioMeios;
}

// Apresenta na consola toda a informação existente sobre os clientes.
ResFuncoes listarMeios(Meio* inicioMeios)
{
    system("cls");
    if (inicioMeios == NULL)
    {
        return MEIOS_NAO_EXISTEM;
    }
    else
    {
        // Enquanto o pointer inicioMeios não for NULL (que esse mesmo está sempre a apontar para um valor de memória diferente na lista ligada)
        // É apresentada a informação dos meios.
        printf("Dados de meios disponiveis:\n------------------------------------------------------------------------------------------------------------------------\n\n");
        while (inicioMeios != NULL)
        {
            printf("Codigo: %d    Tipo: %s  Nivel Bateria: %.2f  Autonomia: %.2f  Custo: %d Geocodigo: %s Ativo: %d\n", inicioMeios->codigo, inicioMeios->tipo,
                inicioMeios->bateria, inicioMeios->autonomia, inicioMeios->custo, inicioMeios->geocodigo, inicioMeios->ativo);
            inicioMeios = inicioMeios->seguinteMeio;
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n\n");
    }
    return SUCESSO;
}

// Escreve todos os dados inseridos sobre os meios, em ficheiro de texto.
int escreverFicheiroMeios(Meio* inicioMeios, char fileName [])
{
    if (inicioMeios == NULL)
    {
        return -1;
    }
    FILE *dadosMeios = fopen(fileName, "wt");

    if (dadosMeios == NULL)
    {
        return -2;
    }
    while (inicioMeios != NULL)
    {
        fprintf(dadosMeios, "%d;%s;%.2f;%.2f;%d;%s;%d\n", inicioMeios->codigo, inicioMeios->tipo, inicioMeios->bateria, inicioMeios->autonomia,
            inicioMeios->custo, inicioMeios->geocodigo, inicioMeios->ativo);
        inicioMeios = inicioMeios->seguinteMeio;
    }
    fclose(dadosMeios);
    return 1;
}

// Escreve todos os dados inseridos sobre os meios, em ficheiro binário.
int escreverFicheiroMeiosBin(Meio* inicioMeios, char fileName[])
{
    if (inicioMeios == NULL)
    {
        return -1;
    }
    FILE *dadosMeios = fopen(fileName, "wb");
    if (dadosMeios == NULL)
    {
        return -2;
    }
    while (inicioMeios != NULL)
    {
        fwrite(inicioMeios, 1, sizeof(Meio), dadosMeios);
        inicioMeios = inicioMeios->seguinteMeio;
    }
    fclose(dadosMeios);
    return 1;
}

// Verifica, consoante o endereço de memória de certo meio, se o seu código é igual ao que foi inserido para um novo meio.
ResFuncoes existeMeio(Meio* inicioMeios, int cod)
{
    if (inicioMeios == NULL)
        return 1; //mudar return
    while (inicioMeios != NULL)
    {
        if (inicioMeios->codigo == cod)
        {
            return 0; //mudar return
        }
        inicioMeios = inicioMeios->seguinteMeio;
    }
    return 1; //mudar return
}

// Verifica cada meio existente, se o seu valor de autonomia do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor decrescente a nivel de autonomia.
Meio* bubbleSortMeios(Meio* inicioMeios)
{
    Meio* atual, * seguinte;
    int b = 1, auxCodigo, auxCusto, auxAtivo;
    float auxBat, auxAut;
    char auxNome[MAX_LEN], auxGeo[MAX_LEN];

    while (b)
    {
        b = 0;
        atual = inicioMeios;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinteMeio != NULL)
        {
            seguinte = atual->seguinteMeio;
            if (atual->autonomia < seguinte->autonomia)
            {
                auxCodigo = atual->codigo;
                auxBat = atual->bateria;
                auxAut = atual->autonomia;
                auxCusto = atual->custo;
                strcpy(auxNome, atual->tipo);
                strcpy(auxGeo, atual->geocodigo);
                auxAtivo = atual->ativo;

                atual->codigo = seguinte->codigo;
                atual->bateria = seguinte->bateria;
                atual->autonomia = seguinte->autonomia;
                atual->custo = seguinte->custo;
                strcpy(atual->tipo, seguinte->tipo);
                strcpy(atual->geocodigo, seguinte->geocodigo);
                atual->ativo = seguinte->ativo;

                seguinte->codigo = auxCodigo;
                seguinte->bateria = auxBat;
                seguinte->autonomia = auxAut;
                seguinte->custo = auxCusto;
                strcpy(seguinte->tipo, auxNome);
                strcpy(seguinte->geocodigo, auxGeo);
                seguinte->ativo = auxAtivo;

                b = 1;
            }
            atual = seguinte;
        }
    }
    inicioMeios = atual;
    return inicioMeios;
}

ResFuncoes mediaAutonomia(Meio* inicioMeios)
{
    int tamanho = 0;
    float resultado = 0;
    if (inicioMeios == NULL)
    {
        return -1;
    }
    while (inicioMeios != NULL)
    {
        resultado += inicioMeios->autonomia;
        inicioMeios = inicioMeios->seguinteMeio;
        tamanho++;
    }
    resultado = resultado / tamanho;
    printf("A media de autonomia de todos os meios e de: %.2f\n", resultado);
}

#pragma endregion 

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS--------------------------------------------------------


// --------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES--------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAcaO DE CLIENTES

// Ler ficheiro de texto, contendo informação sobre os clientes.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
Cliente* lerFicheiroClientes(Cliente* inicioClientes, char fileName[])
{
    FILE* dadosClientes = fopen(fileName, "rt");
    // Definição de variáveis.
    char linha[MAX_LINE_LEN];

    //Usando a função fgets, lemos a partir do ficheiro dadosClientes todo o seu conteúdo, onde é armazenado em cada novoNodo criado
    //Depois é atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    //Contendo assim toda as informações e pointers necessários para criar a lista ligada.

    while (fgets(linha, MAX_LINE_LEN, dadosClientes))
    {
        Cliente* novoNodo = malloc(sizeof(struct RegistoClientes));
        sscanf(linha, "%d;%[^;];%d;%d;%s\n", &novoNodo->codigo, novoNodo->nome, &novoNodo->NIF, &novoNodo->saldo, novoNodo->geocodigo);
        novoNodo->seguinteCliente = inicioClientes;
        inicioClientes = novoNodo;
    }
    fclose(dadosClientes);
    return inicioClientes;
}

// Apresenta na consola toda a informação existente sobre os clientes.
ResFuncoes listarClientes(Cliente* inicioClientes)
{
    if (inicioClientes == NULL)
    {
        perror("Nao existem clientes.\n"); //melhorar para perror
        return 0;
    }
    else
    {
        printf("\nDados de Clientes:\n------------------------------------------------------------------------------------------------------------------------\n");
        // Enquanto o pointer inicioClientes não for NULL (que esse mesmo está sempre a apontar para um valor de memória diferente na lista ligada)
        // É apresentada a informação dos clientes.
        while (inicioClientes != NULL)
        {
            printf("Codigo: %d    Nome: %s     NIF: %d      Saldo: %d\n", inicioClientes->codigo, inicioClientes->nome, inicioClientes->NIF, inicioClientes->saldo);
            inicioClientes = inicioClientes->seguinteCliente;
        }
        printf("------------------------------------------------------------------------------------------------------------------------");
    }
}

// Escreve todos os dados inseridos sobre os clientes, em ficheiro de texto.
int escreverFicheiroClientes(Cliente* inicioClientes, char fileName[])
{
    if (inicioClientes == NULL)
    {
        return -1;
    }
    FILE *dadosClientes = fopen(fileName, "wt");
    if (dadosClientes == NULL)
    {
        return -2;
    }
    while (inicioClientes != NULL)
    {
        fprintf(dadosClientes, "%d;%s;%d;%d;%s\n", inicioClientes->codigo, inicioClientes->nome, inicioClientes->NIF, inicioClientes->saldo, inicioClientes->geocodigo);
        inicioClientes = inicioClientes->seguinteCliente;
    }

    fclose(dadosClientes);
    return 1;
}

// Escreve todos os dados inseridos sobre os clientes, em ficheiro binário.
int escreverFicheiroClientesBin(Cliente* inicioClientes, char fileName[])
{
    if (inicioClientes == NULL)
    {
        return -1;
    }
    FILE *dadosClientes = fopen(fileName, "wb");
    if (dadosClientes == NULL)
    {
        return -2;
    }
    while (inicioClientes != NULL)
    {
        fwrite(inicioClientes, 1, sizeof(Cliente), dadosClientes);
        inicioClientes = inicioClientes->seguinteCliente;
    }
    fclose(dadosClientes);
    return 1;
}

// Verifica, consoante o endereço de memória de um certo utilizador, se o seu código é igual ao que foi inserido para um novo utilizador.
int existeClienteCod(Cliente* inicioClientes, int cod)
{
    while (inicioClientes != NULL)
    {
        if (inicioClientes->codigo == cod)
        {
            return 0;
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
    if (inicioClientes == NULL)
        return 1;
}

// Verifica, consoante o endereço de memória de um certo utilizador, se o seu NIF é igual ao que foi inserido para um novo utilizador.
int existeClienteNIF(Cliente* inicioClientes, int NIF)
{
    while (inicioClientes != NULL)
    {
        if (inicioClientes->NIF == NIF)
        {
            return 0;
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
    if (inicioClientes == NULL)
        return 1;
}

// Verifica cada cliente existente, se o seu codigo do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor crescente.
Cliente* bubbleSortClientes(Cliente* inicioClientes) {
    Cliente* atual, * seguinte;
    int b = 1, auxCodigo, auxNIF, auxSaldo;
    char auxNome[MAX_LEN], auxGeocodigo[MAX_LEN];
    while (b)
    {
        b = 0;
        atual = inicioClientes;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinteCliente != NULL)
        {
            seguinte = atual->seguinteCliente;
            if (atual->codigo > seguinte->codigo)
            {
                auxCodigo = atual->codigo;
                strcpy(auxNome, atual->nome);
                auxNIF = atual->NIF;
                auxSaldo = atual->saldo;
                strcpy(auxGeocodigo, atual->geocodigo);

                atual->codigo = seguinte->codigo;
                strcpy(atual->nome, seguinte->nome);
                atual->NIF = seguinte->NIF;
                atual->saldo = seguinte->saldo;
                strcpy(atual->geocodigo, seguinte->geocodigo);

                seguinte->codigo = auxCodigo;
                strcpy(seguinte->nome, auxNome);
                seguinte->NIF = auxNIF;
                seguinte->saldo = auxSaldo;
                strcpy(seguinte->geocodigo, auxGeocodigo);

                b = 1;
            }
            atual = seguinte;
        }
    }
    inicioClientes = atual;
    return inicioClientes;
}
#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAcaO DE GESTORES

// Ler ficheiro de texto, contendo informação sobre os gestores.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
Gestor* lerFicheiroGestores(Gestor* inicioGestor, char fileName[])
{
    FILE *dadosGestor = fopen("gestores.txt", "rt");

    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dadosGestor))
    {
        Gestor* novoNodo = malloc(sizeof(struct RegistoGestor));
        sscanf(linha, "%d;%[^;];%[^;];%d;%s\n", &novoNodo->codigo, novoNodo->nome, novoNodo->senha, &novoNodo->encriptado, novoNodo->areaResponsavel);
        novoNodo->seguinteGestor = inicioGestor;
        inicioGestor = novoNodo;
    }
    fclose(dadosGestor);
    return inicioGestor;
}

// Apresenta na consola toda a informação existente sobre os gestores.
void listarGestores(Gestor* inicioGestor)
{
    system("cls");
    if (inicioGestor == NULL)
    {
        printf("Nao existem gestores, por favor registe-se.\n");
        return 0;
    }
    else
    {
        printf("Dados de Gestores:\n------------------------------------------------------------------------------------------------------------------------\n");
        while (inicioGestor != NULL)
        {
            printf("Codigo:%d        Nome:%s    Area:%s\n", inicioGestor->codigo, inicioGestor->nome, inicioGestor->areaResponsavel);
            inicioGestor = inicioGestor->seguinteGestor;
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n");
    }

}

// Escreve todos os dados inseridos sobre os gestores, em ficheiro de texto.
int escreverFicheiroGestores(Gestor* inicioGestores, char fileName[])
{
    if (inicioGestores == NULL)
    {
        return -1;
    }
    FILE *dadosGestores = fopen(fileName, "wt");
    if (dadosGestores == NULL)
    {
        return -2;
    }
    while (inicioGestores != NULL)
    {
        fprintf(dadosGestores, "%d;%s;%s;%d;%s\n", inicioGestores->codigo, inicioGestores->nome, inicioGestores->senha, inicioGestores->encriptado, inicioGestores->areaResponsavel);       
        inicioGestores = inicioGestores->seguinteGestor;
    }

    fclose(dadosGestores);
    return 1;
}

// Escreve todos os dados inseridos sobre os gestores, em ficheiro binário.
int escreverFicheiroGestoresBin(Gestor* inicioGestores, char fileName[])
{
    if (inicioGestores == NULL)
    {
        return -1;
    }
    FILE *dadosGestores = fopen(fileName, "wb");
    if (dadosGestores == NULL)
    {
        return -2;
    }
    while (inicioGestores != NULL)
    {
        fwrite(inicioGestores, 1, sizeof(Gestor), dadosGestores);
        inicioGestores = inicioGestores->seguinteGestor;
    }
    fclose(dadosGestores);
    return 1;
}

// Verifica, consoante o endereço de memória de um certo gestor, se o seu código é igual ao que foi inserido para um novo gestor.
int existeGestor(Gestor* inicioGestores, int cod)
{
    while (inicioGestores != NULL)
    {
        if (inicioGestores->codigo == cod)
        {
            return 0;
        }
        inicioGestores = inicioGestores->seguinteGestor;
    }
    if (inicioGestores == NULL)
        return 1;
}

// Verifica cada gestor existente, se o seu codigo do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor crescente.
Gestor* bubbleSortGestores(Gestor* inicioGestor) {
    Gestor* atual, * seguinte;
    int auxCodigo, b = 1, auxEncriptado;
    char auxSenha[MAX_LEN], auxNome[MAX_LEN], auxAreaResponsavel[MAX_LEN];
    while (b)
    {
        b = 0;
        atual = inicioGestor;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinteGestor != NULL)
        {
            seguinte = atual->seguinteGestor;
            if (atual->codigo > seguinte->codigo)
            {
                auxCodigo = atual->codigo;
                strcpy(auxNome, atual->nome);
                strcpy(auxSenha, atual->senha);
                auxEncriptado = atual->encriptado;
                strcpy(auxAreaResponsavel, atual->areaResponsavel);

                atual->codigo = seguinte->codigo;
                strcpy(atual->nome, seguinte->nome);
                strcpy(atual->senha, seguinte->senha);
                atual->encriptado = seguinte->encriptado;
                strcpy(atual->areaResponsavel, seguinte->areaResponsavel);

                seguinte->codigo = auxCodigo;
                strcpy(seguinte->nome, auxNome);
                strcpy(seguinte->senha, auxSenha);
                seguinte->encriptado = auxEncriptado;
                strcpy(seguinte->areaResponsavel, auxAreaResponsavel);

                b = 1;
            }
            atual = seguinte;
        }
    }
    inicioGestor = atual;
    return inicioGestor;
}
#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES----------------------------------------------------


// ---------------------------------------------------INICIO-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------
#pragma region INSERIR

// Função para entrar em modo gestor, no qual é pedido um codigo e uma senha. Caso sejam iguais ao que está no ficheiro é garantido o acesso
// a funções de gestor.
Gestor* modoGestor(Gestor* inicioGestores) {
    int codigoInserido;
    char senha[20];
    if (inicioGestores == NULL)
    {
        printf("Ficheiro nao lido.\n");
        return 0;
    }
    printf("Insira o codigo de utilizador: ");
    scanf("%d", &codigoInserido);
    printf("Insira a senha: ");
    scanf("%s", senha);
    while (inicioGestores != NULL)
    {
        if (inicioGestores->codigo == codigoInserido && strcmp(inicioGestores->senha, senha) == 0 && inicioGestores->encriptado == 0)
        {
            printf("Bem-vindo %s\n", inicioGestores->nome);
            return 1;
        }
        else if (inicioGestores->codigo == codigoInserido && inicioGestores->encriptado == 1)
        {
            decryptSenha(inicioGestores, inicioGestores->senha);
            if (strcmp(senha, inicioGestores->senha) == 0)
            {
                printf("Bem-vindo %s\n", inicioGestores->nome);
                encryptSenha(inicioGestores, inicioGestores->senha);
                return 1;
            }
            else
            {
                printf("Senha errada.\n");
                return 0;
            }
        }
        else
        {
            inicioGestores = inicioGestores->seguinteGestor;
        }
    }
    if (inicioGestores == NULL)
    {
        printf("Codigo ou senha errados.\n");
        return 0;
    }
}

Meio* inserirMeio(Grafo* inicioGrafo, Meio* inicioMeios, Meio* meio)
{
    Meio* aux = inicioMeios;
    Grafo* auxGrafo = inicioGrafo;

    if (aux == NULL) {
        return meio;
    }
    else {
        // Percorre até o último cliente da lista
        Meio* atual = aux;
        while (atual->seguinteMeio != NULL) {
            atual = atual->seguinteMeio;
        }
        if (!existeVertice(auxGrafo, meio->geocodigo))
        {
            int auxVertice, escolhaAdjacente, inserido = 1;
            auxVertice = inserirVertice(auxGrafo, meio->geocodigo);
            if (auxVertice == 1)
            {
                printf("A %s tem algum destino? 1-Sim/0-Nao\n", meio->geocodigo);
                printf("A sua escolha: ");
                scanf("%d", &escolhaAdjacente);
                while (inserido != 0)
                {
                    char novoAdjacente[50];
                    float novoPeso;
                    printf("Nome do novo adjacente a %s: ", meio->geocodigo);
                    scanf("%s", novoAdjacente);
                    printf("Distancia em km: ");
                    scanf("%f", &novoPeso);
                    if (inserirAdjacente(auxGrafo, meio->geocodigo, novoAdjacente, novoPeso))
                    {
                        printf("Adjacente inserido com sucesso.\n");
                        printf("Deseja inserir mais adjacentes ao geocodigo %s?\n 1-Sim/0-Nao\n", meio->geocodigo);
                        printf("A sua escolha: ");
                        scanf("%d", &inserido);
                    }
                }
            }
        }
        // Insere o novo meio no final
        atual->seguinteMeio = meio;
    }

    return aux;
}

// Função para inserir um novo meio elétrico, é pedido ao gestor na função main, um novo codigo, nome, nivel bateria, autonomia, o seu custo 
// e a sua geolocalização. De seguida é inserido no ultimo lugar da lista ligada dos meios, quando é o ultimo endereço NULL.
Meio* criarMeio(Grafo* inicioGrafo, Meio* inicioMeios, int cod, char nome[], float bat, float aut, int custo, char geo[])
{
    Grafo* aux = inicioGrafo;

        Meio* novoMeio = malloc(sizeof(Meio));
        novoMeio->codigo = cod;
        strcpy(novoMeio->tipo, nome);
        novoMeio->bateria = bat;
        novoMeio->autonomia = aut;
        novoMeio->custo = custo;
        strcpy(novoMeio->geocodigo, geo);
        if (!existeVertice(aux, novoMeio->geocodigo))
        {
            inserirVertice(aux, novoMeio->geocodigo);
        }
        novoMeio->ativo = 0;
        novoMeio->seguinteMeio = NULL;

    return novoMeio;
}

// Função para inserir um novo cliente, é pedido ao gestor na função main, um novo codigo, nome, NIF e saldo.  
// De seguida é inserido no ultimo lugar da lista ligada dos clientes, quando é o ultimo endereço NULL.
Cliente* criarCliente(int cod, char nome[], int NIF, int saldo, char geocodigo[])
{
    Cliente* novoCliente = malloc(sizeof(Cliente));
    novoCliente->codigo = cod;
    strcpy(novoCliente->nome, nome);
    novoCliente->NIF = NIF;
    novoCliente->saldo = saldo;
    strcpy(novoCliente->geocodigo, geocodigo);
    novoCliente->seguinteCliente = NULL;

    return novoCliente;
}

Cliente* inserirCliente(Cliente* inicioClientes, Cliente* cliente)
{
    Cliente* aux = inicioClientes;

    if (aux == NULL) {
        return cliente;
    }
    else {
        // Percorre até o último cliente da lista
        Cliente* atual = aux;
        while (atual->seguinteCliente != NULL) {
            atual = atual->seguinteCliente;
        }
        // Insere o novo cliente no final
        atual->seguinteCliente = cliente;
    }

    return aux;
}

// Função para inserir um novo gestor, é pedido ao gestor na função main, um novo codigo, nome e senha.  
// De seguida é inserido no ultimo lugar da lista ligada dos gestores, quando é o ultimo endereço NULL.
Gestor* inserirGestor(Gestor* inicioGestor, Gestor* gestor)
{
    Gestor* aux = inicioGestor;

    if (aux == NULL) {
        return gestor;
    }
    else {
        // Percorre até o último gestor da lista
        Gestor* atual = aux;
        while (atual->seguinteGestor != NULL) {
            atual = atual->seguinteGestor;
        }
        // Insere o novo gestor no final
        atual->seguinteGestor = gestor;
    }

    return aux;
}

Gestor* criarGestor(Gestor* inicioGestor, int cod, char nome[], char senha[], char area[])
{
    Gestor* gestor = malloc(sizeof(Gestor));
    gestor->codigo = cod;
    strcpy(gestor->nome, nome);
    strcpy(gestor->senha, senha);
    strcpy(gestor->areaResponsavel, area);
    gestor->encriptado = 1;
    encryptSenha(gestor, gestor->senha);
    gestor->seguinteGestor = NULL;
    return gestor;
}

// Pequena função para encriptação da senha do gestor.
int encryptSenha(Gestor* inicioGestor, char senha[])
{
    for (int i = 0; i < strlen(senha); i++)
    {
        senha[i] = senha[i] + 5;
    }
    return 1;
}

// Pequena função para desencriptação da senha do gestor.
int decryptSenha(Gestor* inicioGestor, char senha[])
{
    for (int i = 0; i < strlen(senha); i++)
    {
        senha[i] = senha[i] - 5;
    }
    return 1;
}
#pragma endregion 

#pragma region REMOVER

// Função para remover algum meio, a partir do código inserido pelo gestor. É removido o meio e de seguida é retornada toda a lista ligada
// com o meio removido.
Meio* removerMeio(Meio* inicioMeios, int cod)
{
    Meio* anterior = inicioMeios, * atual = inicioMeios, * aux;

    if (atual == NULL) return(NULL); // Lista vazia.
    else if (atual->codigo == cod) // remoção do 1º registo
    {
        aux = atual->seguinteMeio;
        free(atual);
        printf("Meio com cod %d removido com sucesso.\n", cod);
        Sleep(2000);
        system("cls");
        return(aux);
    }
    else
    {
        while ((atual != NULL) && (atual->codigo != cod)) // Iteração até ser igual.
        {
            anterior = atual;
            atual = atual->seguinteMeio;
        }
        if (atual == NULL) return(inicioMeios);
        else // Remoção do meio com cod introduzido.
        {
            anterior->seguinteMeio = atual->seguinteMeio;
            free(atual);
            printf("Meio com cod %d removido com sucesso.\n", cod);
            Sleep(2000);
            system("cls");
            return(inicioMeios);
        }
    }
}

// Função para remover algum cliente, a partir do código inserido pelo gestor. É removido o cliente e de seguida é retornada toda a lista ligada
// com o meio removido.
Cliente* removerCliente(Cliente* inicioClientes, int cod)
{
    Cliente* anterior = inicioClientes, * atual = inicioClientes, * aux;

    if (atual == NULL) return(NULL); // Lista vazia.
    else if (atual->codigo == cod) // remoção do 1º registo
    {
        aux = atual->seguinteCliente;
        free(atual);
        printf("Cliente com cod %d removido com sucesso.\n", cod);
        Sleep(2000);
        system("cls");
        return(aux);
    }
    else
    {
        while ((atual != NULL) && (atual->codigo != cod)) // Iteração até ser igual.
        {
            anterior = atual;
            atual = atual->seguinteCliente;
        }
        if (atual == NULL) return(inicioClientes);
        else // Remoção do cliente com cod introduzido.
        {
            anterior->seguinteCliente = atual->seguinteCliente;
            free(atual);
            printf("Cliente com cod %d removido com sucesso.\n", cod);
            Sleep(2000);
            system("cls");
            return(inicioClientes);
        }
    }
}

// Função para remover algum gestor, a partir do código inserido pelo gestor. É removido o gestor e de seguida é retornada toda a lista ligada
// com o meio removido.
Gestor* removerGestor(Gestor* inicioGestores, int cod)
{
    Gestor* anterior = inicioGestores, * atual = inicioGestores, * aux;

    if (atual == NULL) return(NULL); // Lista vazia.
    else if (atual->codigo == cod) // remoção do 1º registo
    {
        aux = atual->seguinteGestor;
        free(atual);
        printf("Gestor com cod %d removido com sucesso.\n", cod);
        return(aux);
    }
    else
    {
        while ((atual != NULL) && (atual->codigo != cod)) // Iteração até ser igual.
        {
            anterior = atual;
            atual = atual->seguinteGestor;
        }
        if (atual == NULL) return(inicioGestores); // Lista ligada toda percorrida, nao foi encontrado nenhum gestor com o codigo inserido.
        else // Remoção do gestor com cod introduzido.
        {
            anterior->seguinteGestor = atual->seguinteGestor;
            free(atual);
            printf("Gestor com cod %d removido com sucesso.\n", cod);
            return(inicioGestores);
        }
    }
}
#pragma endregion

#pragma region ALTERAR

// Função para alteração de dados de algum gestor.
// Apenas é pedido o codigo de gestor. É possivel alterar codigo, nome, senha, area responsavel.
Gestor* alterarGestor(Gestor* inicioGestores)
{
    int cod, escolha, novoCod, encriptar, acabadoAlterar = 1;
    char novaSenha[50], novoNome[50], senha[50], novaAreaResponsavel[50];
    Gestor* aux = inicioGestores;
    if (inicioGestores == NULL)
    {
        printf("Nao existem gestores, por favor faca o registo de um.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    printf("Introduza o seu codigo de gestor: ");
    scanf("%d", &cod);
    if (existeGestor(aux, cod) == 1)
    {
        printf("O codigo %d nao existe.\n", cod);
        Sleep(2000);
        system("cls");
        return 0;
    }
    system("cls");
    while (inicioGestores != NULL)
    {
        if (inicioGestores->codigo == cod)
        {
            do
            {
                printf("Este sao os seus dados.\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("Nome:%s     Codigo:%d       Area:%s\n", inicioGestores->nome, inicioGestores->codigo, inicioGestores->areaResponsavel);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("O que deseja alterar?\n");
                printf("1 - Codigo.\n");
                printf("2 - Nome.\n");
                printf("3 - Area responsavel.\n");
                printf("4 - Senha.\n");
                printf("0 - Sair.\n");
                printf("A sua escolha: ");
                scanf("%d", &escolha);
                switch (escolha)
                {
                case 1:
                    printf("Introduza um novo codigo: ");
                    scanf("%d", &novoCod);
                    if (!existeGestor(aux, novoCod))
                    {
                        printf("Ja existe alguem com esse codigo.\n");
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        inicioGestores->codigo = novoCod;
                        printf("Codigo alterado com sucesso. O seu novo codigo %d\n", inicioGestores->codigo);
                        Sleep(2000);
                        system("cls");
                    }
                    break;
                case 2:
                    printf("Introduza um novo nome: ");
                    scanf("%s", novoNome);
                    strcpy(inicioGestores->nome, novoNome);
                    Sleep(2000);
                    system("cls");
                    break;
                case 3:
                    printf("Introduza a nova area para ser responsavel: ");
                    scanf("%s", novaAreaResponsavel);
                    strcpy(inicioGestores->areaResponsavel, novaAreaResponsavel);
                    printf("A sua area responsavel foi alterada com sucesso.\n");
                    printf("A sua nova area e a seguinte: %s\n", inicioGestores->areaResponsavel);
                    Sleep(2000);
                    system("cls");
                    break;
                case 4:
                    printf("Introduza a sua nova senha: ");
                    scanf("%s", novaSenha);
                    printf("Deseja encriptar? 1-Sim/0-Nao\n");
                    printf("A sua escolha: ");
                    scanf("%d", &encriptar);
                    if (encriptar == 0)
                    {
                        printf("Senha alterada com sucesso.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    else
                    {
                        inicioGestores->encriptado = 1;
                        encryptSenha(inicioGestores, novaSenha);
                        strcpy(inicioGestores->senha, novaSenha);
                        printf("Senha encriptada e alterada com sucesso.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                case 0:
                    break;
                default:
                    printf("Insira uma opcao.\n");
                    break;
                }
            } while (escolha != 0);
        }
        inicioGestores = inicioGestores->seguinteGestor;
    }
}

// Função para alteração de dados do cliente.
// É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel fazer alteração de nome, codigo e NIF.
ResFuncoes alterarDadosCliente(Cliente* inicioClientes, Transacao* inicioTransacao) {
    int codigo, NIF, novoCodigo, novoNIF, inserir = 1, escolha, codigoAux;
    char novoNome[50], novoGeocodigo[100];
    Cliente* aux = inicioClientes;
    Transacao* auxTrans = inicioTransacao;
    if (inicioClientes == NULL)
    {
        return CLIENTES_NAO_EXISTEM;
    }
    printf("Introduza o seu codigo: ");
    scanf("%d", &codigo);
    printf("Introduza o seu NIF: ");
    scanf("%d", &NIF);
    if (existeClienteCod(aux, codigo) == 1)
    {
        return COD_CLIENTE_NAO_EXISTE;
    }
    else if (existeClienteNIF(aux, NIF) == 1)
    {
        return NIF_CLIENTE_NAO_EXISTE;
    }
    while (inicioClientes != NULL)
    {
        if (inicioClientes->codigo == codigo && inicioClientes->NIF == NIF)
        {
            do
            {
                printf("Este sao os seus dados, %s.\n", inicioClientes->nome);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("Nome: %s     Codigo: %d       NIF: %d      Localizacao: %s\n", inicioClientes->nome, inicioClientes->codigo, inicioClientes->NIF, inicioClientes->geocodigo);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("O que deseja alterar?\n");
                printf("1 - Nome.\n");
                printf("2 - Codigo.\n");
                printf("3 - NIF.\n");
                printf("4 - Localizacao.\n");
                printf("0 - Sair.\n");
                printf("A sua escolha: ");
                scanf("%d", &escolha);
                switch (escolha)
                {
                case 1:
                    getchar();
                    printf("Insira o seu novo nome: ");
                    scanf("%[^\n]", novoNome);
                    strcpy(inicioClientes->nome, novoNome);
                    printf("Nome alterado com sucesso para %s.\n", inicioClientes->nome);
                    Sleep(2000);
                    system("cls");
                    break;
                case 2:
                    printf("Insira o seu novo codigo: ");
                    scanf("%d", &novoCodigo);
                    if (existeClienteCod(aux, novoCodigo))
                    {
                        codigoAux = inicioClientes->codigo;
                        inicioClientes->codigo = novoCodigo;
                        printf("O seu novo codigo %d\n", inicioClientes->codigo);
                        if (existeClienteTransacao(auxTrans, codigoAux))
                        {
                            while (auxTrans != NULL)
                            {
                                if (auxTrans->codigoUtilizador == codigoAux)
                                {
                                    auxTrans->codigoUtilizador = novoCodigo;
                                }
                                auxTrans = auxTrans->seguinteTransacao;
                            }
                        }
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        printf("O codigo %d ja existe.\n", novoCodigo);
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    break;
                case 3:
                    printf("Insira o seu novo NIF(deve conter 9 numeros e comecar por 192): ");
                    scanf("%d", &novoNIF);
                    if (novoNIF <= 192000000 || novoNIF >= 193000000)
                    {
                        printf("Por favor tente de novo.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    else
                    {
                        if (existeClienteNIF(aux, novoNIF))
                        {
                            inicioClientes->NIF = novoNIF;
                            printf("O seu novo NIF %d\n", inicioClientes->NIF);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        else
                        {
                            printf("Ja existe alguem com o NIF inserido %d.\n", novoNIF);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    }
                    break;
                case 4:
                    printf("Insira o seu novo geocodigo/localizacao: ");
                    scanf("%s", novoGeocodigo);
                    strcpy(inicioClientes->geocodigo, novoGeocodigo);
                    printf("Geocodigo alterado com sucesso para %s.\n", inicioClientes->geocodigo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 0:
                    return 1;
                    break;
                }
            } while (escolha != 0);
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
}

// Função para alteração de dados de algum meio.
// É pedido o codigo do meio a alterar. É possivel alterar o seu codigo, tipo, se está ativo, custo, bat, aut, etc...
Meio* alterarMeio(Meio* inicioMeios)
{
    int cod, codAlterar, ativoAlterar, custoAlterar, escolha;
    float batAlterar, autAlterar;
    char meioNomeAlterar[50], geocodigoAlterar[50];
    Meio* aux = inicioMeios;
    if (inicioMeios == NULL)
    {
        printf("Nao existem meios.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    printf("Introduza o codigo do meio que pretende alterar: ");
    scanf("%d", &cod);
    if (existeMeio(inicioMeios, cod))
    {
        printf("O meio com o codigo %d nao existe.\n", cod);
        Sleep(2000);
        system("cls");
        return 0;
    }
    system("cls");
    while (inicioMeios != NULL)
    {
        if (inicioMeios->codigo == cod)
        {
            do
            {
                printf("Este sao os dados do meio cod %d.\n", inicioMeios->codigo);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("Codigo:%d\nTipo:%s\nBateria:%.2f\nAut:%.2f\nCusto:%d\nGeo:%s\nAtivo:%d\n", inicioMeios->codigo, inicioMeios->tipo, inicioMeios->bateria, inicioMeios->autonomia, inicioMeios->custo, inicioMeios->geocodigo, inicioMeios->ativo);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("O que deseja alterar?\n");
                printf("1 - Codigo.\n");
                printf("2 - Tipo.\n");
                printf("3 - Bateria.\n");
                printf("4 - Autonomia.\n");
                printf("5 - Custo.\n");
                printf("6 - Geocodigo.\n");
                printf("7 - Ativo.\n");
                printf("A sua escolha: ");
                scanf("%d", &escolha);
                switch (escolha)
                {
                case 1:
                    printf("Insira o novo codigo: ");
                    scanf("%d", &codAlterar);
                    if (!existeMeio(aux, codAlterar))
                    {
                        printf("Ja existe um meio com esse codigo.\n");
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        inicioMeios->codigo = codAlterar;
                        printf("Codigo alterado com sucesso. Novo codigo %d.\n", inicioMeios->codigo);
                        Sleep(2000);
                        system("cls");
                    }
                    break;
                case 2:
                    printf("Insira o novo tipo de meio: ");
                    scanf("%s", meioNomeAlterar);
                    strcpy(inicioMeios->tipo, meioNomeAlterar);
                    printf("Nome alterado com sucesso para %s.\n", inicioMeios->tipo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 3:
                    printf("Insira o novo nivel de bateria: ");
                    scanf("%f", &batAlterar);
                    if (batAlterar > 100.0001 || batAlterar < 0)
                    {
                        printf("Insira um nivel de bateria, entre 0 e 100.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    inicioMeios->bateria = batAlterar;
                    printf("Novo nivel de bateria %.2f\n", inicioMeios->bateria);
                    Sleep(2000);
                    system("cls");
                    break;
                case 4:
                    printf("Insira o novo nivel de autonomia: ");
                    scanf("%f", &autAlterar);
                    if (autAlterar > 100.0001 || autAlterar < 0)
                    {
                        printf("Insira um nivel de autonomia, entre 0 e 100.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    inicioMeios->autonomia = autAlterar;
                    printf("Novo nivel de autonomia %.2f\n", inicioMeios->autonomia);
                    Sleep(2000);
                    system("cls");
                    break;
                case 5:
                    printf("Insira o novo custo: ");
                    scanf("%d", &custoAlterar);
                    inicioMeios->custo = custoAlterar;
                    printf("Novo custo do meio %d\n", inicioMeios->custo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 6:
                    printf("Insira um novo geocodigo: ");
                    scanf("%s", geocodigoAlterar);
                    strcpy(inicioMeios->geocodigo, geocodigoAlterar);
                    printf("Novo geocodigo %s\n", inicioMeios->geocodigo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 7:
                    printf("Este veiculo esta ativo?1-Sim/0-Nao\n");
                    printf("A sua escolha: ");
                    scanf("%d", &ativoAlterar);
                    if (ativoAlterar == 1)
                    {
                        if (inicioMeios->ativo == 1)
                        {
                            printf("Meio ja esta ativo.\n");
                            Sleep(2000);
                            system("cls");
                        }
                        else
                        {
                            inicioMeios->ativo = 1;
                            system("cls");
                        }
                    }
                    else
                    {
                        if (inicioMeios->ativo == 0)
                        {
                            printf("Meio ja nao estava ativo.\n");
                            Sleep(2000);
                            system("cls");
                        }
                        else
                        {
                            inicioMeios->ativo = 0;

                        }
                    }
                    break;
                case 0:
                    break;
                default:
                    printf("Introduza alguma opcao.\n");
                    break;
                }
            } while (escolha != 0);
        }
        inicioMeios = inicioMeios->seguinteMeio;
    }
}
#pragma endregion
// ---------------------------------------------------FIM-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------


// ---------------------------------------------------------------INICIO_OP_UTILIZADOR-----------------------------------------------------------------
#pragma region OP_Utilizador
// Função para carregamento de saldo, de um certo utilizador.
// É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel carregar o saldo desse mesmo utilizador.
Cliente* carregarSaldo(Cliente* inicioClientes, Transacao* inicioTransacao) {
    if (inicioClientes == NULL)
    {
        return CLIENTES_NAO_EXISTEM;
    }
    Transacao* auxTrans = inicioTransacao;
    int codigo, NIF, inserir = 1;
    printf("Introduza o seu codigo: ");
    scanf("%d", &codigo);
    printf("Introduza o seu NIF: ");
    scanf("%d", &NIF);
    while (inicioClientes != NULL)
    {
        if (inicioClientes->codigo == codigo && inicioClientes->NIF == NIF)
        {
            int saldoCarregar;
            printf("O seu saldo: %d\n", inicioClientes->saldo);
            printf("Quanto saldo deseja carregar?\n");
            printf("Digite: ");
            scanf("%d", &saldoCarregar);
            if (saldoCarregar < 0)
            {
                return SALDO_CARR_NEGATIVO;
            }
            inicioClientes->saldo = saldoCarregar + inicioClientes->saldo;
            printf("%d carregado com sucesso. Tem agora %d de saldo.\n", saldoCarregar, inicioClientes->saldo);
            if (inicioTransacao == NULL)
            {
                if (inicioTransacao = criarTransacao(inicioTransacao, inicioClientes->codigo, saldoCarregar, inicioClientes->nome))
                    return inicioTransacao;
            }
            while (inserir == 1)
            {
                if (inicioTransacao->seguinteTransacao == NULL)
                {
                    if (criarTransacao(auxTrans, inicioClientes->codigo, saldoCarregar, inicioClientes->nome))
                        inserir = 0;
                }
                inicioTransacao = inicioTransacao->seguinteTransacao;
                if (inserir == 0)
                {
                    return SUCESSO;
                }
            }
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
    if (inicioClientes == NULL)
    {
        return COD_NIF_NAO_EXISTE;
    }
    Sleep(2000);
    system("cls");
}

// Função para consulta de saldo, de um certo utilizador.
// É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel visualizar quando saldo está disponível.
ResFuncoes consultaSaldo(Cliente* inicioClientes) {
    int codigo, NIF;
    printf("Introduza o seu codigo: ");
    scanf("%d", &codigo);
    //printf("Introduza o seu NIF: ");
    //scanf("%d", &NIF);
    if (inicioClientes == NULL)
    {
        return CLIENTES_NAO_EXISTEM;
    }
    while (inicioClientes != NULL)
    {
        if (inicioClientes->codigo == codigo /*&& inicioClientes->NIF == NIF*/)
        {
            printf("Voce tem %d de saldo.\n", inicioClientes->saldo);
            return SALDO_ATUAL;
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
    if (inicioClientes == NULL)
    {
        //printf("Nao existe o cliente com o cod %d.\n", codigo);
        return COD_NIF_NAO_EXISTE;
    }
}

// Funçáo para realização de aluguer de qualquer meio existente, que não esteja ativo.
// É pedido o codigo de utilizador, é verificado se existe esse mesmo utilizador. De seguida é perguntado qual o meio que deseja alugar. 
// São apresentados dados, tais como o tipo de meio, o seu custo e o saldo do utilizador. Caso o utilizador, decida comprar o meio
// É criado um novo registo na lista ligada de alugueres.
Aluguer* realizarAluguer(Cliente* inicioClientes, Aluguer* inicioAluguer, Meio* inicioMeios)
{
    int meioAlugar, codigoUtilizador, NIF;
    printf("Insira o seu codigo: ");
    scanf("%d", &codigoUtilizador);
    if (existeClienteCod(inicioClientes, codigoUtilizador) == 0)
    {
        while (inicioClientes->codigo != codigoUtilizador)
            inicioClientes = inicioClientes->seguinteCliente;
        printf("Qual meio deseja alugar? ");
        scanf("%d", &meioAlugar);
        if (existeMeio(inicioMeios, meioAlugar) == 0)
        {
            while (inicioMeios->codigo != meioAlugar)
            {
                inicioMeios = inicioMeios->seguinteMeio;
            }
            printf("Nome do meio: %s\n", inicioMeios->tipo);
            printf("O meio custa: %d\n", inicioMeios->custo);
            printf("Voce tem: %d\n", inicioClientes->saldo);
            int escolhaCompra;
            printf("Deseja comprar? 1-Sim/2-Nao\n");
            printf("A sua escolha: ");
            scanf("%d", &escolhaCompra);
            if (escolhaCompra != 1)
            {
                return 0;
            }
            else
            {
                if (inicioClientes->saldo < inicioMeios->custo)
                {
                    printf("Nao tem saldo suficiente para efetuar a compra.\n");
                    Sleep(2000);
                    system("cls");
                    return 0;
                }
                else if (inicioMeios->ativo == 1)
                {
                    printf("Nao pode alugar esse meio, pois ja esta alugado.\n");
                    Sleep(2000);
                    system("cls");
                }
                else
                {
                    time_t dataCompra;
                    time(&dataCompra);
                    char auxDataCompra[50];
                    strcpy(auxDataCompra, ctime(&dataCompra));
                    for (int i = 0; i < strlen(auxDataCompra); i++)
                    {
                        if (auxDataCompra[i] == '\n')
                            auxDataCompra[i] = '\0';
                    }
                    printf("Data da compra: %s\n", ctime(&dataCompra));
                    int inserir = 0;
                    inicioClientes->saldo = inicioClientes->saldo - inicioMeios->custo;
                    printf("O seu novo saldo %d\n", inicioClientes->saldo);
                    while (inserir != 1)
                    {
                        if (inicioAluguer == NULL)
                        {
                            Aluguer* novoNodo = malloc(sizeof(Aluguer));
                            novoNodo->seguinteCompra = NULL;
                            inicioAluguer = novoNodo;
                        }
                        if (inicioAluguer->seguinteCompra == NULL)
                        {
                            Aluguer* novoNodo = malloc(sizeof(Aluguer));
                            novoNodo->codComprador = inicioClientes->codigo;
                            strcpy(novoNodo->nomeComprador, inicioClientes->nome);
                            strcpy(novoNodo->dataCompra, auxDataCompra);
                            strcpy(novoNodo->nomeMeioComprado, inicioMeios->tipo);
                            inicioMeios->ativo = 1;
                            inicioAluguer->seguinteCompra = novoNodo;
                            novoNodo->seguinteCompra = NULL;
                            inicioAluguer = novoNodo;
                            printf("Compra efetuada com sucesso.\n");
                            Sleep(2000);
                            system("cls");
                            inserir = 1;
                            return inicioAluguer;
                        }
                        inicioAluguer = inicioAluguer->seguinteCompra;
                    }
                }
            }
        }
        else
        {
            //printf("O meio introduzido, nao existe.\n");
            //Sleep(2000);
            //system("cls");
            return 0;
        }
    }
    else
    {
        printf("Nao existe esse codigo de cliente.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
}

// Função para listar na consola, todos os meios existentes com um certo geocodigo.
void listarGeocodigo(Meio* inicioMeios)
{
    system("cls");
    int verificado = 0, existe = 0;
    char verificarGeocodigo[50];
    Meio* auxPrint = inicioMeios;
    printf("Introduza o geocodigo que pretende verificar: ");
    scanf("%s", verificarGeocodigo);
    getchar();

    if (inicioMeios == NULL)
        return 0;
    while (auxPrint != NULL && existe == 0)
    {
        if (strcmp(verificarGeocodigo, auxPrint->geocodigo) == 0)
        {
            existe = 1;
        }
        auxPrint = auxPrint->seguinteMeio;
    }
    if (existe)
    {
        printf("Estes sao os meios com o geocodigo %s\n------------------------------------------------------------------------------------------------------------------------\n", verificarGeocodigo);
    }
    else
    {
        printf("Nao existe o geocodigo inserido.\n");
        Sleep(2000);
        system("cls");
    }
    while (inicioMeios != NULL)
    {
        if (strcmp(verificarGeocodigo, inicioMeios->geocodigo) == 0)
        {
            printf("Codigo: %d      Tipo: %s      Bat: %.2f      Aut: %.2f      Custo: %d\n", inicioMeios->codigo, inicioMeios->tipo, inicioMeios->bateria, inicioMeios->autonomia, inicioMeios->custo);
        }
        inicioMeios = inicioMeios->seguinteMeio;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}
#pragma endregion
// -----------------------------------------------------------------FIM_OP_UTILIZADOR-------------------------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE ALUGUER----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAcaO DE ALUGUER
// Ler ficheiro de texto, contendo informação sobre os alugueres.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
Aluguer* lerFicheiroAluguer(Aluguer* inicioAluguer, char fileName[])
{
    FILE *dadosAluguer = fopen(fileName, "rt");
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dadosAluguer))
    {
        Aluguer* novoNodo = malloc(sizeof(Aluguer));
        sscanf(linha, "%d;%[^;];%[^;];%[^\n]\n", &novoNodo->codComprador, novoNodo->dataCompra, novoNodo->nomeComprador, novoNodo->nomeMeioComprado);
        novoNodo->seguinteCompra = inicioAluguer;
        inicioAluguer = novoNodo;
    }
    fclose(dadosAluguer);
    return inicioAluguer;
}

// Função para listar na consola, o historico dos alugueres já feitos.
void listarAluguer(Aluguer* inicioAluguer)
{
    system("cls");
    if (inicioAluguer == NULL)
    {
        printf("Nao existem alugueres.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    printf("Dados de Alugueres:\n------------------------------------------------------------------------------------------------------------------------\n");
    while (inicioAluguer != NULL)
    {
        printf("Codigo: %d   Data de compra: %s       Nome: %s Meio: %s\n", inicioAluguer->codComprador, inicioAluguer->dataCompra, inicioAluguer->nomeComprador, inicioAluguer->nomeMeioComprado);
        inicioAluguer = inicioAluguer->seguinteCompra;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

// Verifica cada aluguer existente, se a sua data for maior que a do seguinte elemento, irá ser feita uma troca
// para ordenar todos os elementos por ordem de compra.
Aluguer* bubbleSortAluguer(Aluguer* inicioAluguer) {
    Aluguer* atual, * seguinte;
    int auxCodigo, b = 1;
    char auxData[MAX_LEN], auxComprador[MAX_LEN], auxMeioComprado[MAX_LEN];
    while (b)
    {
        b = 0;
        atual = inicioAluguer;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinteCompra != NULL)
        {
            seguinte = atual->seguinteCompra;
            if (strcmp(atual->dataCompra, seguinte->dataCompra) > 0)
            {
                auxCodigo = atual->codComprador;
                strcpy(auxComprador, atual->nomeComprador);
                strcpy(auxData, atual->dataCompra);
                strcpy(auxMeioComprado, atual->nomeMeioComprado);

                atual->codComprador = seguinte->codComprador;
                strcpy(atual->nomeComprador, seguinte->nomeComprador);
                strcpy(atual->dataCompra, seguinte->dataCompra);
                strcpy(atual->nomeMeioComprado, seguinte->nomeMeioComprado);

                seguinte->codComprador = auxCodigo;
                strcpy(seguinte->nomeComprador, auxComprador);
                strcpy(seguinte->dataCompra, auxData);
                strcpy(seguinte->nomeMeioComprado, auxMeioComprado);
                b = 1;
            }
            atual = seguinte;
        }
    }
    inicioAluguer = atual;
    return inicioAluguer;
}

// Escreve todos os dados sobre os alugueres, em ficheiro de texto.
int escreverFicheiroAluguer(Aluguer* inicioAluguer, char fileName[])
{
    if (inicioAluguer == NULL)
    {
        return -1;
    }
    FILE *dadosAluguer = fopen(fileName, "wt");
    if (dadosAluguer == NULL)
    {
        return -2;
    }
    while (inicioAluguer != NULL)
    {
        fprintf(dadosAluguer, "%d;%s;%s;%s\n", inicioAluguer->codComprador, inicioAluguer->dataCompra, inicioAluguer->nomeComprador, inicioAluguer->nomeMeioComprado);
        inicioAluguer = inicioAluguer->seguinteCompra;
    }
    fclose(dadosAluguer);
    return 1;
}

//Escreve todos os dados sobre os alugueres, em ficheiro binário.
int escreverFicheiroAluguerBin(Aluguer* inicioAluguer, char fileName[])
{
    if (inicioAluguer == NULL)
    {
        return -1;
    }
    FILE *dadosAluguer = fopen(fileName, "wb");
    if (dadosAluguer == NULL)
    {
        return -2;
    }
    while (inicioAluguer != NULL)
    {
        fwrite(inicioAluguer, 1, sizeof(Aluguer), dadosAluguer);
        inicioAluguer = inicioAluguer->seguinteCompra;
    }
    fclose(dadosAluguer);
    return 1;
}

int existeClienteTransacao(Transacao* inicioTransacao, int codVerificar)
{
    int teste = 0;
    Transacao* aux = inicioTransacao;
    while (aux != NULL)
    {
        if (aux->codigoUtilizador == codVerificar)
            return 1;
        aux = aux->seguinteTransacao;
    }
    return 0;
}
#pragma endregion
// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE ALUGUER----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE TRANSACOES----------------------------------------------------
#pragma region LEITURA/ESCRITA/REPRESENTAcaO DE TRANSACOES
Transacao* lerFicheiroTransacao(Transacao* inicioTransacao, char fileName[])
{
    FILE *dadosTransacao = fopen(fileName, "rt");
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dadosTransacao))
    {
        Transacao* novoNodo = malloc(sizeof(Transacao));
        sscanf(linha, "%d;%[^;];%d;%[^\n]", &novoNodo->codigoUtilizador, novoNodo->nomeTransacao, &novoNodo->montanteCarregado, novoNodo->dataTransacao);
        novoNodo->seguinteTransacao = inicioTransacao;
        inicioTransacao = novoNodo;
    }
    fclose(dadosTransacao);
    return inicioTransacao;
}

int escreverFicheiroTransacao(Transacao* inicioTransacao, char fileName[])
{
    if (inicioTransacao == NULL)
    {
        return -1;
    }
    FILE *dadosTransacao = fopen(fileName, "wt");
    if (dadosTransacao == NULL)
    {
        return -2;
    }
    while (inicioTransacao != NULL)
    {
        fprintf(dadosTransacao, "%d;%s;%d;%s\n", inicioTransacao->codigoUtilizador, inicioTransacao->nomeTransacao, inicioTransacao->montanteCarregado, inicioTransacao->dataTransacao);
        inicioTransacao = inicioTransacao->seguinteTransacao;
    }
    fclose(dadosTransacao);
    return 1;
}

int escreverFicheiroTransacaoBin(Transacao* inicioTransacao, char fileName[])
{
    if (inicioTransacao == NULL)
    {
        return -1;
    }
    FILE *dadosTransacao = fopen(fileName, "wb");
    if (dadosTransacao == NULL)
    {
        return -2;
    }
    while (inicioTransacao != NULL)
    {
        fwrite(inicioTransacao, 1, sizeof(Transacao), dadosTransacao);
        inicioTransacao = inicioTransacao->seguinteTransacao;
    }
    fclose(dadosTransacao);
    return 1;
}

void listarTransacao(Transacao* inicioTransacao)
{
    system("cls");
    if (inicioTransacao == NULL)
    {
        printf("Nao existem registos de transacoes.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    printf("Dados de transacoes:\n------------------------------------------------------------------------------------------------------------------------\n");
    while (inicioTransacao != NULL)
    {
        printf("Codigo: %d   Nome: %s     Mont.Carregado: %d Eur   Data: %s \n", inicioTransacao->codigoUtilizador, inicioTransacao->nomeTransacao, inicioTransacao->montanteCarregado, inicioTransacao->dataTransacao);
        inicioTransacao = inicioTransacao->seguinteTransacao;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

Transacao* criarTransacao(Transacao* inicioTransacao, int codigoCliente, int saldoCarregar, char nomeCliente[])
{
    Transacao* novaTransacao = malloc(sizeof(Transacao));
    novaTransacao->codigoUtilizador = codigoCliente;
    novaTransacao->montanteCarregado = saldoCarregar;
    strcpy(novaTransacao->nomeTransacao, nomeCliente);
    time_t dataTransacao;
    time(&dataTransacao);
    char auxDataTransacao[50];
    strcpy(auxDataTransacao, ctime(&dataTransacao));
    for (int i = 0; i < strlen(auxDataTransacao); i++)
    {
        if (auxDataTransacao[i] == '\n')
            auxDataTransacao[i] = '\0';
    }
    strcpy(novaTransacao->dataTransacao, auxDataTransacao);

    if (inicioTransacao == NULL) {
        inicioTransacao = novaTransacao;
    }
    else {
        Transacao* currentTransacao = inicioTransacao;
        while (currentTransacao->seguinteTransacao != NULL) {
            currentTransacao = currentTransacao->seguinteTransacao;
        }
        currentTransacao->seguinteTransacao = novaTransacao;
    }
    novaTransacao->seguinteTransacao = NULL;
    inicioTransacao = novaTransacao;
    return inicioTransacao;
}
#pragma endregion
// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE TRANSACOES----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE CIDADES----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAcaO DE CIDADES
Grafo* lerFicheiroVertices(Grafo* inicioGrafo, Meio* inicioMeios, char fileName[])
{
    FILE *dadosGrafo = fopen(fileName, "rt");
    char* tokenVertice;
    if (dadosGrafo == NULL)
    {
        printf("O ficheiro nao existe.\n");
        return 0;
    }
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dadosGrafo))
    {
        tokenVertice = strtok(linha, ";");
        while (tokenVertice != NULL)
        {
            int pos = strcspn(tokenVertice, "\n");
            tokenVertice[pos] = '\0';
            Grafo* novoNodo = malloc(sizeof(Grafo));
            strcpy(novoNodo->vertice, tokenVertice);
            novoNodo->meios = NULL;
            novoNodo->adjacentes = NULL;
            novoNodo->seguinteVertice = inicioGrafo;
            inicioGrafo = novoNodo;
            tokenVertice = strtok(NULL, ";");
        }
    }
    return inicioGrafo;
}

Grafo* lerFicheiroAdjacentes(Grafo* inicioGrafo, char fileName[])
{
    FILE *dadosAdjacentes = fopen(fileName, "rt");
    Adjacente* novoAdj = NULL;
    Grafo* aux = inicioGrafo;
    int inserido = 0;
    char* vertice, * adjacente, * peso, linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dadosAdjacentes))
    {
        inserido = 0;
        vertice = strtok(linha, ";");
        aux = inicioGrafo;
        while (inserido != 1)
        {
            while (aux != NULL)
            {
                if (strcmp(aux->vertice, vertice) == 0)
                {
                    while (vertice != NULL)
                    {
                        if (novoAdj == NULL)
                        {
                            novoAdj = malloc(sizeof(Adjacente));
                            adjacente = strtok(NULL, "/");
                            peso = strtok(NULL, ";");
                            strcpy(novoAdj->vertice, adjacente);
                            novoAdj->peso = atof(peso);
                            novoAdj->seguinteAdjacente = aux->adjacentes;
                            aux->adjacentes = novoAdj;
                        }
                        else
                        {
                            if (vertice != NULL) {
                                adjacente = strtok(NULL, "/");
                                peso = strtok(NULL, ";");
                                if (adjacente == NULL || peso == NULL)
                                {
                                    vertice = NULL;
                                    inserido = 1;
                                    break;
                                }
                                novoAdj = malloc(sizeof(Adjacente));
                                strcpy(novoAdj->vertice, adjacente);
                                novoAdj->peso = atof(peso);
                                if (aux->adjacentes == NULL)
                                {
                                    aux->adjacentes = novoAdj;
                                    novoAdj->seguinteAdjacente = NULL;
                                }
                                else
                                {
                                    novoAdj->seguinteAdjacente = aux->adjacentes->seguinteAdjacente;
                                    aux->adjacentes->seguinteAdjacente = novoAdj;
                                }
                            }
                        }
                    }
                }
                aux = aux->seguinteVertice;
                if (inserido == 1)
                    break;
            }
        }
    }
    return inicioGrafo;
}

void testeCLientes(Grafo* inicioGrafo)
{
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        if (aux->clientes == NULL)
        {
            printf("Nao existem clientes registados com a cidade: %s\n", aux->vertice);
        }
        else if (aux->clientes != NULL)
        {
            printf("Nome: %s    Cod: %d\n", aux->clientes->nome, aux->clientes->codigo);
        }
        aux = aux->seguinteVertice;
    }
}

Grafo* adicionarClientesGrafo(Grafo* inicioGrafo, Cliente* inicioClientes)
{
    int teste = 0;
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        teste = 0;
        Cliente* auxClientes = inicioClientes;
        while (auxClientes != NULL)
        {
            if (strcmp(auxClientes->geocodigo, aux->vertice) == 0)
            {
                aux->clientes = auxClientes;
                teste = 1;
            }
            auxClientes = auxClientes->seguinteCliente;
        }
        if (teste == 0)
        {
            aux->clientes = NULL;
        }
        aux = aux->seguinteVertice;
    }
    return inicioGrafo->clientes;
}

Grafo* adicionarMeiosGrafo(Grafo* inicioGrafo, Meio* inicioMeios)
{
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        Meio* auxMeio = inicioMeios;
        while (auxMeio != NULL)
        {
            if (strcmp(auxMeio->geocodigo, aux->vertice) == 0)
            {
                aux->meios = auxMeio;
            }
            auxMeio = auxMeio->seguinteMeio;
        }
        aux = aux->seguinteVertice;
    }
    return inicioGrafo->meios;
}

ResFuncoes localizacaoRaio(Grafo* inicioGrafo, Cliente* inicioClientes, float raio, int codigo)
{
    Grafo* aux = inicioGrafo;
    Cliente* auxClientes = inicioClientes;
    char geocodigoProcurar[100];
    int print = 0;
    if (!existeClienteCod(auxClientes, codigo))
    {
        while (auxClientes->codigo != codigo)
            auxClientes = auxClientes->seguinteCliente;
    }
    else
    {
        return CLIENTES_NAO_EXISTEM;
    }
    strcpy(geocodigoProcurar, auxClientes->geocodigo);
    while (strcmp(geocodigoProcurar, aux->vertice) != 0)
    {
        aux = aux->seguinteVertice;
    }
    Adjacente* auxAdj = aux->adjacentes;
    while (auxAdj != NULL)
    {
        if (raio > auxAdj->peso)
        {
            printf("Pode ir para %s com uma distancia de %.2f\n", auxAdj->vertice, auxAdj->peso);
            print = 1;
        }
        auxAdj = auxAdj->seguinteAdjacente;
    }
    if (print == 0)
    {
        printf("Nao e possivel ir para nenhuma localizacao com a distancia definida.\n");
        return ERRO;
    }
    return SUCESSO;
}

void printTestGrafo(Grafo* inicioGrafo)
{
    Grafo* aux = inicioGrafo;
    while (aux->clientes != NULL)
    {
        printf("Cliente: %s \n", aux->clientes->nome);
        aux->clientes = aux->clientes->seguinteCliente;
    }
    while (aux->meios != NULL)
    {
        printf("Meios: %s \n", aux->meios->tipo);
        aux->meios = aux->meios->seguinteMeio;
    }
}
void listarGrafo(Grafo* inicioGrafo)
{
    char aux[100];
    char continuar = 0;
    printf("Localizacoes existentes:\n");
    while (inicioGrafo != NULL)
    {
        printf("->");
        strcpy(aux, inicioGrafo->vertice);
        int pos = strcspn(inicioGrafo->vertice, "\n");
        inicioGrafo->vertice[pos] = '\0';
        printf("%s\n", inicioGrafo->vertice);
        inicioGrafo = inicioGrafo->seguinteVertice;
    }
    printf("Prima espaco e de seguida enter para sair.");
    while (continuar != " ")
    {
        scanf("%c", &continuar);
        if (continuar == ' ')
        {
            printf("Voltando ao menu.\n");
            Sleep(2000);
            system("cls");
            return 0;
        }
    }
}

void listarAdjacentes(Grafo* inicioGrafo)
{
    char continuar = 0;
    while (inicioGrafo != NULL)
    {
        printf("Dados de %s:\n------------------------------------------------------------------------------------------------------------------------\n", inicioGrafo->vertice);
        printf("Esta localizacao pode ir para:\n");
        if (inicioGrafo->adjacentes == NULL)
        {
            printf("A localizacao %s nao tem destinos.\n", inicioGrafo->vertice);
        }
        while (inicioGrafo->adjacentes != NULL)
        {
            printf("%s com distancia de %.2f km; \n", inicioGrafo->adjacentes->vertice, inicioGrafo->adjacentes->peso);
            inicioGrafo->adjacentes = inicioGrafo->adjacentes->seguinteAdjacente;
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n");
        inicioGrafo = inicioGrafo->seguinteVertice;
    }
    printf("Prima espaco e enter para sair.");
    while (continuar != " ")
    {
        scanf("%c", &continuar);
        if (continuar == ' ')
        {
            printf("Voltando ao menu.\n");
            Sleep(2000);
            system("cls");
            return 0;
        }
    }
}

int existeVertice(Grafo* inicioGrafo, char verticeVerificar[])
{
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        if (strcmp(verticeVerificar, aux->vertice) == 0)
        {
            return 1;
        }
        aux = aux->seguinteVertice;
    }
    return 0;
}

int inserirVertice(Grafo* inicioGrafo, char verticeInserir[])
{
    while (inicioGrafo != NULL)
    {
        if (inicioGrafo->seguinteVertice == NULL)
        {
            Grafo* novoVertice = malloc(sizeof(Grafo));
            strcpy(novoVertice->vertice, verticeInserir);
            novoVertice->adjacentes = NULL;
            novoVertice->meios = NULL;
            inicioGrafo->seguinteVertice = novoVertice;
            novoVertice->seguinteVertice = NULL;
            inicioGrafo = novoVertice;
        }
        inicioGrafo = inicioGrafo->seguinteVertice;
    }
    return inicioGrafo, 1;
}

int escreverFicheiroGrafo(Grafo* inicioGrafo, char fileName[])
{
    Grafo* aux = inicioGrafo;
    if (inicioGrafo == NULL)
    {
        return -1;
    }
    FILE *dadosGrafo = fopen(fileName, "wt");
    if (dadosGrafo == NULL)
    {
        return -2;
    }
    char listaCopiada[20][50];
    int iterador = 0;
    while (aux != NULL)
    {
        strcpy(listaCopiada[iterador], aux->vertice);
        aux = aux->seguinteVertice;
        iterador++;
    }
    for (int i = iterador; i > 0; i--)
    {
        fprintf(dadosGrafo, "%s;", listaCopiada[iterador - 1]);
        iterador--;
    }
    fclose(dadosGrafo);
    return 1;
}

int existeAdjacente(Grafo* inicioGrafo, char verticeFinal[])
{
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        if (strcmp(aux->vertice, verticeFinal) == 0)
        {
            return 1;
        }
        aux = aux->seguinteVertice;
    }
    return 0;
}

int inserirAdjacente(Grafo* inicioGrafo, char verticeInicial[], char verticeFinal[], float peso)
{
    Grafo* aux = inicioGrafo;
    int existeVert = 0, existeAdj = 0;
    existeVert = existeVertice(aux, verticeInicial);
    existeAdj = existeAdjacente(aux, verticeFinal);
    if (existeVert)
    {
        while (!strcmp(aux->vertice, verticeInicial) == 0)
            aux = aux->seguinteVertice;
        if (!existeAdj)
        {
            Adjacente* novoAdj = malloc(sizeof(Adjacente));
            strcpy(novoAdj->vertice, verticeFinal);
            novoAdj->peso = peso;
            novoAdj->seguinteAdjacente = aux->adjacentes;
            aux->adjacentes = novoAdj;
            inicioGrafo = aux;
            return inicioGrafo, 1;
        }
        else
        {
            return 2;
        }
    }
    return 0;
}

int totalVertices(Grafo* inicioGrafo)
{
    int total = 0;
    Grafo* aux = inicioGrafo;
    while (aux != NULL && aux->seguinteVertice != NULL)
    {
        aux = aux->seguinteVertice;
        total++;
    }
    return total;
}

ListaStack* caminhoTexto(Grafo* inicioGrafo, char verticeAtual[], char verticeDestino[], Stack* inicioStack, ListaStack* inicioLista)
{
    Grafo* aux = inicioGrafo;
    Stack* auxStack = inicioStack;
    Adjacente* auxAdj = NULL;
    if (existeVertice(aux, verticeAtual))
    {
        while (aux != NULL)
        {
            if (strcmp(aux->vertice, verticeAtual) == 0)
            {
                auxStack = push(auxStack, aux->vertice);
                inicioStack = auxStack;
                break;
            }
            aux = aux->seguinteVertice;
        }
    }
    else
        return;

    if (strcmp(aux->vertice, verticeDestino) == 0)
    {
        ListaStack* novaListaStack = malloc(sizeof(ListaStack));
        novaListaStack->novaStack = inicioStack;
        novaListaStack->seguinteLista = inicioLista;
        inicioLista = novaListaStack;
        mostrarCaminho(inicioLista);
        return;
    }

    auxAdj = aux->adjacentes;
    while (auxAdj != NULL)
    {
        if (!verticeVisitado(inicioStack, auxAdj->vertice))
        {
            Stack* novaStack = NULL;
            Stack* auxStack2 = inicioStack;
            while (auxStack2 != NULL)
            {
                novaStack = push(novaStack, auxStack2->vertice);
                auxStack2 = auxStack2->seguinteStack;
            }

            inicioStack->visitado = true;
            caminhoTexto(inicioGrafo, auxAdj->vertice, verticeDestino, novaStack, inicioLista);
        }
        auxAdj = auxAdj->seguinteAdjacente;
    }
    return inicioLista;
}

bool verticeVisitado(Stack* inicioStack, char vertice[])
{
    Stack* auxStack = inicioStack;
    while (auxStack != NULL)
    {
        if (strcmp(auxStack->vertice, vertice) == 0)
        {
            return true;
        }
        auxStack = auxStack->seguinteStack;
    }
    return false;
}
#pragma endregion

#pragma region STACK

Stack* push(Stack* inicioStack, char vertice[])
{
    Stack* aux = inicioStack;
    if (inicioStack == NULL)
    {
        Stack* novaStack = malloc(sizeof(Stack));
        strcpy(novaStack->vertice, vertice);
        novaStack->visitado = true;
        novaStack->seguinteStack = inicioStack;
        return novaStack;
    }
    else
    {
        while (inicioStack->seguinteStack != NULL)
        {
            inicioStack = inicioStack->seguinteStack;
        }
        Stack* novaStack = malloc(sizeof(Stack));
        strcpy(novaStack->vertice, vertice);
        novaStack->seguinteStack = NULL;
        inicioStack->seguinteStack = novaStack;
    }
    return aux;
}



void mostrarCaminho(ListaStack* inicioLista) {
    if (inicioLista == NULL)
    {
        printf("Caminho nao encontrado.\n");
        return;
    }

    ListaStack* auxLista = inicioLista;
    while (auxLista != NULL)
    {
        Stack* auxStack = auxLista->novaStack;

        while (auxStack != NULL)
        {
            printf("%s", auxStack->vertice);
            if (auxStack->seguinteStack != NULL)
            {
                printf(" -> ");
            }
            auxStack = auxStack->seguinteStack;
        }
        printf("\n");
        auxLista = auxLista->seguinteLista;
    }
}
#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE CIDADES----------------------------------------------------
