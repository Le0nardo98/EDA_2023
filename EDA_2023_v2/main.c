/*****************************************************************//**
 * @file   main.c
 * @brief  Execução
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
#include "estruturas.h"
#include "clientes.h"
#include "crud.h"
#include "gestores.h"
#include "grafo.h"
#include "meios.h"


int main() {
    // Definição de variáveis.
    Meio* inicioMeios = NULL;
    Cliente* inicioClientes = NULL;
    Gestor* inicioGestor = NULL;
    Aluguer* inicioAluguer = NULL;
    Transacao* inicioTransacao = NULL;
    Grafo* inicioGrafo = NULL;
    ResFuncoes resFunc;
    Stack* inicioStack = NULL;
    ListaStack* inicioLista = NULL;
    FILE* dadosMeios, * dadosClientes, * dadosGestor, * dadosAluguer, * dadosTransacao, * dadosGrafo, * dadosAdjacentes;
    int op, opUtilizador, utilizadorLogin = 0, gestor_login = 0, op_gestor, retFunc;
    int novoCliente_codigo, novoCliente_NIF, novoCliente_saldo, novo_meio_codigo, novo_meio_custo, novo_gestor_codigo, codigo_meio_remover
        , codigo_cliente_remover, codigo_gestor_remover, codigo_login_utilizador;
    float novo_meio_bateria, novo_meio_autonomia, novopesoAdjacente, tamanhoAdj, tamanhoTotal = 0, tamanhoIda = 0, tamanhoVolta = 0;
    char novoCliente_nome[MAX_LEN], novo_meio_nome[MAX_LEN], novo_meio_geocodigo[MAX_LEN], novo_gestor_nome[MAX_LEN], novo_gestor_senha[MAX_LEN],
        novo_gestor_area[MAX_LEN], novoverticeinicial[MAX_LEN], novoverticeFinal[MAX_LEN]
        , verticeInicial[MAX_LEN], verticeDestino[MAX_LEN], novoCliente_geocodigo[MAX_LEN], verticePartida[MAX_LEN];;


    // No arranque é feito de imediato a leitura dos ficheiros.
    
    inicioMeios = lerFicheiroMeios(inicioMeios, "meios.txt");

    inicioClientes = lerFicheiroClientes(inicioClientes, "clientes.txt");
    
    inicioGestor = lerFicheiroGestores(inicioGestor, "gestores.txt");
    
    inicioAluguer = lerFicheiroAluguer(inicioAluguer, "historico_compras.txt");
    
    inicioTransacao = lerFicheiroTransacao(inicioTransacao, "historico_transacoes.txt");
    
    inicioGrafo = lerFicheiroVertices(inicioGrafo, inicioMeios, "vertices.txt");
    
    inicioGrafo = lerFicheiroAdjacentes(inicioGrafo, "adjacentes.txt");

    bubbleSortMeios(inicioMeios);
    bubbleSortClientes(inicioClientes);
    bubbleSortGestores(inicioGestor);
    bubbleSortAluguer(inicioAluguer);
    inicioGrafo->clientes = adicionarClientesGrafo(inicioGrafo, inicioClientes);
    inicioGrafo->meios = adicionarMeiosGrafo(inicioGrafo, inicioMeios);
    //testeCLientes(inicioGrafo);
    // Criação de Menu.
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            if (inicioClientes == NULL)
            {
                printf("Nao existem utilizadores, por favor registe-se.\n");
                break;
            }
            utilizadorLogin = 1;
            while (utilizadorLogin > 0)
            {
                opUtilizador = menuUtilizador();
                switch (opUtilizador) {
                case 1:
                    resFunc = listarMeios(inicioMeios);
                    switch (resFunc)
                    {
                    case SUCESSO:
                        printf("sucesso.\n");
                        break;
                    case CLIENTES_NAO_EXISTEM:
                        printf("Nao existem clientes.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    default:
                        break;
                    }
                    break;
                case 2:
                    if (inicioTransacao == NULL)
                    {
                        inicioTransacao = carregarSaldo(inicioClientes, inicioTransacao);
                        break;
                    }
                    retFunc = carregarSaldo(inicioClientes, inicioTransacao);
                    switch (retFunc)
                    {
                    case SUCESSO:
                        Sleep(2000);
                        system("cls");
                        break;
                    case COD_NIF_NAO_EXISTE:
                        printf("Nao existe o cliente com o codigo/NIF inserido.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    case CLIENTES_NAO_EXISTEM:
                        printf("Nao existem clientes.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    case SALDO_CARR_NEGATIVO:
                        printf("Nao pode carregar saldo negativo.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    break;
                case 3:
                    resFunc = consultaSaldo(inicioClientes);
                    switch (resFunc)
                    {
                    case CLIENTES_NAO_EXISTEM:
                        printf("Nao existem clientes.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    case COD_NIF_NAO_EXISTE:
                        printf("Nao existe o cliente com o codigo/NIF inserido.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    case SALDO_ATUAL:
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    break;
                case 4:
                    resFunc = alterarDadosCliente(inicioClientes, inicioTransacao);
                    switch (resFunc)
                    {
                    case SUCESSO:
                        break;
                    case COD_CLIENTE_NAO_EXISTE:
                    {
                        printf("Nao existe nenhum cliente registado com o cod inserido.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    case NIF_CLIENTE_NAO_EXISTE:
                    {
                        printf("O codigo inserido nao esta registado com o NIF inserido.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    case CLIENTES_NAO_EXISTEM:
                    {
                        printf("Nao existem clientes registados.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    }
                    break;
                case 5:
                    resFunc = listarMeios(inicioMeios);
                    switch (resFunc)
                    {
                    case CLIENTES_NAO_EXISTEM:
                        printf("Nao existem meios para alugar.\n");
                        break;
                    }
                    if (inicioAluguer == NULL)
                    {
                        inicioAluguer = realizarAluguer(inicioClientes, inicioAluguer, inicioMeios);
                    }
                    else
                    {
                        realizarAluguer(inicioClientes, inicioAluguer, inicioMeios);
                    }
                    break;
                case 6:
                    listarGeocodigo(inicioMeios);
                    break;
                case 7:
                    printf("Qual pretende saber:\n");
                    printf("1- Distancia de uma cidade a outra.\n");
                    int escolhaDist;
                    printf("A sua escolha: ");
                    scanf("%d", &escolhaDist);
                    switch (escolhaDist)
                    {
                    case 1:
                        printf("Insira a partida: ");
                        scanf("%s", verticePartida);
                        //strcpy(verticePartida, "fagocitose.crestar.esperanca");
                        inicioLista = NULL;
                        inicioLista = mostrarCaminhoIda(inicioGrafo, verticePartida, inicioStack, inicioLista, tamanhoIda);
                        if (inicioLista == NULL)
                        {
                            printf("Nao existe caminho/Ponto Partida.\n");
                            break;
                        }
                        inicioLista = retirarStackMaior(inicioLista);
                        printf("Caminho de ida: ");
                        mostrarCaminho(inicioLista);
                        tamanhoTotal = inicioLista->tamanho;
                        obterUltimoVertice(inicioLista, verticeInicial);

                        printf("\nCaminho de volta: ");
                        inicioLista = mostrarCaminhoVolta(inicioGrafo, verticeInicial, verticePartida, inicioStack, inicioLista, tamanhoVolta);
                        inicioLista = retirarStackMaior(inicioLista);
                        mostrarCaminho(inicioLista);
                        tamanhoTotal += inicioLista->tamanho;

                        printf("\nKm's percorridos: %.2f\n", tamanhoTotal);
                        free(inicioLista);
                        break;
                    }
                    break;
                case 8:
                    listarAdjacentes(inicioGrafo);
                    break;
                case 9:
                    printf("Introduza em km's, a distancia pela qual pretende verificar a existencia de meios: ");
                    float raioVerificar;
                    int codigoCliente;
                    char tipoMeio[20];
                    scanf("%f", &raioVerificar);
                    printf("Introduza o seu codigo: ");
                    scanf("%d", &codigoCliente);
                    printf("Introduza o nome do meio a procurar: ");
                    scanf("%s", tipoMeio);
                    localizacaoRaio(inicioGrafo, inicioClientes, raioVerificar, codigoCliente, tipoMeio);
                case 0:
                    utilizadorLogin = 0;
                    break;
                }
            }

            break;
        case 2:
            if (inicioGestor == NULL)
            {
                printf("Insira os dados de um novo gestor:\n");
                printf("Codigo: ");
                scanf("%d", &novo_gestor_codigo);
                getchar();
                printf("Nome: ");
                scanf("%[^\n]", novo_gestor_nome);
                getchar();
                printf("Senha: ");
                scanf("%[^\n]", novo_gestor_senha);
                getchar();
                printf("Area: ");
                scanf("%[^\n]", novo_gestor_area);
                if (existeGestor(inicioGestor, novo_gestor_codigo) == 1)
                {
                    Gestor* gestor = criarGestor(inicioGestor, novo_gestor_codigo, novo_gestor_nome, novo_gestor_senha, novo_gestor_area);
                    inicioGestor = inserirGestor(inicioGestor, gestor);
                    break;
                }
                else
                {
                    printf("Ja existe um gestor com o codigo %d", novo_gestor_codigo);
                    break;
                }
                break;
            }
            else if (!modoGestor(inicioGestor))
            {
                break;
            }
            else
            {
                gestor_login = 1;
                while (gestor_login > 0)
                {
                    op_gestor = menuGestor();
                    switch (op_gestor)
                    {
                    case 1:
                        listarClientes(inicioClientes);
                        break;
                    case 2:
                        listarGestores(inicioGestor);
                        break;
                    case 3:
                        listarMeios(inicioMeios);
                        break;
                    case 4:
                        printf("Insira os novos dados de cliente:\n");
                        printf("Codigo: ");
                        scanf("%d", &novoCliente_codigo);
                        getchar();
                        printf("Nome: ");
                        scanf("%[^\n]", novoCliente_nome);
                        printf("NIF(Entre 192 e 193 com 9 digitos ex:192999999): ");
                        scanf("%d", &novoCliente_NIF);
                        if (novoCliente_NIF <= 192000000 || novoCliente_NIF >= 193000000)
                        {
                            printf("Tente de novo.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        printf("Saldo: ");
                        scanf("%d", &novoCliente_saldo);
                        printf("Localizacao: ");
                        scanf("%s", novoCliente_geocodigo);
                        if (inicioClientes == NULL)
                        {
                            Cliente* cliente = criarCliente(novoCliente_codigo, novoCliente_nome, novoCliente_NIF, novoCliente_saldo, novoCliente_geocodigo);
                            inicioClientes = inserirCliente(inicioClientes, cliente);
                            break;
                        }
                        else if (existeClienteCod(inicioClientes, novoCliente_codigo) == 1 && existeClienteNIF(inicioClientes, novoCliente_NIF) == 1)
                        {
                            Cliente* cliente = criarCliente(novoCliente_codigo, novoCliente_nome, novoCliente_NIF, novoCliente_saldo, novoCliente_geocodigo);
                            inserirCliente(inicioClientes, cliente);
                            break;
                        }
                        else
                        {
                            printf("Ja existe algum cliente com os dados inseridos.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    case 5:
                        printf("Insira os novos dados de um meio:\n");
                        printf("Codigo: ");
                        scanf("%d", &novo_meio_codigo);
                        getchar();
                        printf("Nome Meio: ");
                        scanf("%[^\n]", novo_meio_nome);
                        printf("Bateria(0.00 - 100.00): ");
                        scanf("%f", &novo_meio_bateria);
                        printf("nivel:%f\n", novo_meio_bateria);
                        if (novo_meio_bateria <= 0.00 || novo_meio_bateria > 100.0001)
                        {
                            printf("Tente de novo.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        printf("Autonomia(0.00 - 100.00): ");
                        scanf("%f", &novo_meio_autonomia);
                        printf("nivel:%f\n", novo_meio_autonomia);
                        if (novo_meio_autonomia <= 0.00 || novo_meio_autonomia >= 100.0001)
                        {
                            printf("Tente de novo.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        printf("Custo: ");
                        scanf("%d", &novo_meio_custo);
                        getchar();
                        printf("Geocodigo: ");
                        scanf("%[^\n]", novo_meio_geocodigo);
                        if (inicioMeios == NULL)
                        {
                            Meio* meio = criarMeio (inicioGrafo, inicioMeios, novo_meio_codigo, novo_meio_nome, novo_meio_bateria, novo_meio_autonomia, novo_meio_custo, novo_meio_geocodigo);
                            inicioMeios = inserirMeio(inicioGrafo, inicioMeios, meio);
                            break;
                        }
                        if (existeMeio(inicioMeios, novo_meio_codigo) == 1)
                        {
                            Meio* meio = criarMeio(inicioGrafo, inicioMeios, novo_meio_codigo, novo_meio_nome, novo_meio_bateria, novo_meio_autonomia, novo_meio_custo, novo_meio_geocodigo);
                            inserirMeio(inicioGrafo, inicioMeios, meio);
                            break;
                        }
                        else
                        {
                            printf("Ja existe um meio com o cod %d.\n", novo_meio_codigo);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        break;
                    case 6:
                        printf("Insira os dados de um novo gestor:\n");
                        printf("Codigo: ");
                        scanf("%d", &novo_gestor_codigo);
                        getchar();
                        printf("Nome: ");
                        scanf("%[^\n]", novo_gestor_nome);
                        getchar();
                        printf("Senha: ");
                        scanf("%[^\n]", novo_gestor_senha);
                        getchar();
                        printf("Area: ");
                        scanf("%[^\n]", novo_gestor_area);
                        if (existeGestor(inicioGestor, novo_gestor_codigo) == 1)
                        {
                            Gestor* gestor = criarGestor(inicioGestor, novo_gestor_codigo, novo_gestor_nome, novo_gestor_senha, novo_gestor_area);
                            inserirGestor(inicioGestor, gestor);
                            break;
                        }
                        else
                        {
                            printf("Ja existe um gestor com o codigo %d.\n", novo_gestor_codigo);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        break;
                    case 7:
                        printf("Insira o codigo de meio a remover: ");
                        scanf("%d", &codigo_meio_remover);
                        if (existeMeio(inicioMeios, codigo_meio_remover) == 0)
                        {
                            inicioMeios = removerMeio(inicioMeios, codigo_meio_remover);
                            break;
                        }
                        else
                        {
                            printf("O meio com cod %d nao existe.\n", codigo_meio_remover);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    case 8:
                        printf("Insira o codigo de cliente a remover: ");
                        scanf("%d", &codigo_cliente_remover);
                        if (existeClienteCod(inicioClientes, codigo_cliente_remover) == 0)
                        {
                            inicioClientes = removerCliente(inicioClientes, codigo_cliente_remover);
                            break;
                        }
                        else
                        {
                            printf("O cliente com cod %d nao existe.\n", codigo_cliente_remover);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    case 9:
                        printf("Insira o codigo de gestor a remover: ");
                        scanf("%d", &codigo_gestor_remover);
                        if (existeGestor(inicioGestor, codigo_gestor_remover) == 0)
                        {
                            inicioGestor = removerGestor(inicioGestor, codigo_gestor_remover);
                            gestor_login = 0;
                            printf("Terminando sessao.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        else
                        {
                            printf("O gestor com cod %d nao existe.\n", codigo_gestor_remover);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    case 10:
                        listarAluguer(inicioAluguer);
                        break;
                    case 11:
                        alterarGestor(inicioGestor);
                        break;
                    case 12:
                        alterarMeio(inicioMeios);
                        break;
                    case 13:
                        alterarDadosCliente(inicioClientes, inicioTransacao);
                        break;
                    case 14:
                        mediaAutonomia(inicioMeios);
                        break;
                    case 15:
                        listarTransacao(inicioTransacao);
                        break;
                    case 16:
                        printf("Insira os seguintes dados: Vertice inicial, vertice final e distancia em km.\n");
                        printf("Vertice inicial: ");
                        scanf("%s", novoverticeinicial);
                        printf("Vertice Final: ");
                        scanf("%s", novoverticeFinal);
                        printf("Distancia em km: ");
                        scanf("%f", &novopesoAdjacente);
                        int resultado = inserirAdjacente(inicioGrafo, novoverticeinicial, novoverticeFinal, novopesoAdjacente);
                        if (resultado == 1)
                        {
                            printf("Adjacente de %s, adicionado com sucesso.\n", novoverticeinicial);
                            Sleep(2000);
                            system("cls");
                        }
                        else if (resultado == 2)
                        {
                            printf("O Adjacente %s ja existe, no vertice %s.\n", novoverticeFinal, novoverticeinicial);
                            Sleep(2000);
                            system("cls");
                        }
                        break;
                    case 0:
                        gestor_login = 0;
                        system("cls");
                        break;
                    default:
                        getchar();
                        printf("\nInsira uma das opcoes mostradas.\n");
                        break;
                    }
                }
            }
            break;
        case 0:
            // No encerramento do programa é escrito tudo que foi adicionado/removido/alterado de novo para os seus respetivos ficheiros.
            escreverFicheiroMeios(inicioMeios, "meios.txt");
            escreverFicheiroMeiosBin(inicioMeios, "meios.bin");

            escreverFicheiroClientes(inicioClientes, "clientes.txt");
            escreverFicheiroClientesBin(inicioClientes, "clientes.bin");

            escreverFicheiroGestores(inicioGestor, "gestores.txt");
            escreverFicheiroGestoresBin(inicioGestor, "gestores.bin");

            escreverFicheiroAluguer(inicioAluguer, "historico_compras.txt");
            escreverFicheiroAluguerBin(inicioAluguer, "historico_compras.bin");

            escreverFicheiroTransacao(inicioTransacao, "historico_transacoes.txt");
            escreverFicheiroTransacaoBin(inicioTransacao, "historico_transacoes.bin");

            escreverFicheiroGrafo(inicioGrafo, "vertices.txt");

            printf("O programa ira ser encerrado.\n");
            return 0;
        default:
            printf("Insira uma opcao.\n");
            break;
        }
    } while (op != 0);
}