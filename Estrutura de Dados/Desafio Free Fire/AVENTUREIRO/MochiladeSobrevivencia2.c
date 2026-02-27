#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// 1. Definição das Structs
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// --- FUNÇÕES DE SUPORTE ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ordenarVetor(Item vetor[], int total) {
    Item temp;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

// --- OPERAÇÕES ---

void inserirItem(Item vetor[], int *totalV, No** cabecaL) {
    if (*totalV < MAX_ITENS) {
        Item novo;
        printf("\n--- Adicionar Novo Item ---\n");
        printf("Nome do item: ");
        fgets(novo.nome, 30, stdin);
        novo.nome[strcspn(novo.nome, "\n")] = 0;

        printf("Tipo: ");
        fgets(novo.tipo, 20, stdin);
        novo.tipo[strcspn(novo.tipo, "\n")] = 0;

        printf("Quantidade: ");
        scanf("%d", &novo.quantidade);
        limparBuffer();

        // Insere no Vetor
        vetor[*totalV] = novo;
        (*totalV)++;

        // Insere na Lista Encadeada
        No* novoNo = (No*)malloc(sizeof(No));
        novoNo->dados = novo;
        novoNo->proximo = *cabecaL;
        *cabecaL = novoNo;

        printf("\nItem adicionado com sucesso em ambas estruturas!\n");
    } else {
        printf("\nMochila cheia!\n");
    }
}

void realizarBusca(Item vetor[], int totalV, No* cabecaL) {
    char busca[30];
    int compBin = 0, compSeqL = 0;

    printf("\nDigite o nome do item para buscar: ");
    fgets(busca, 30, stdin);
    busca[strcspn(busca, "\n")] = 0;

    // Busca Binária no Vetor (Requisito: Ordenar antes)
    ordenarVetor(vetor, totalV);
    int inicio = 0, fim = totalV - 1, achouV = -1;
    while (inicio <= fim) {
        compBin++;
        int meio = (inicio + fim) / 2;
        int res = strcmp(vetor[meio].nome, busca);
        if (res == 0) { achouV = meio; break; }
        if (res < 0) inicio = meio + 1;
        else fim = meio - 1;
    }

    // Busca Sequencial na Lista
    No* atual = cabecaL;
    int achouL = 0;
    while (atual != NULL) {
        compSeqL++;
        if (strcmp(atual->dados.nome, busca) == 0) { achouL = 1; break; }
        atual = atual->proximo;
    }

    printf("\n============================================\n");
    printf("        RELATORIO DE PERFORMANCE\n");
    printf("============================================\n");
    printf("Busca Binaria (Vetor): %d comparacoes\n", compBin);
    printf("Busca Sequencial (Lista): %d comparacoes\n", compSeqL);
    if (achouV != -1) printf("Resultado: Item encontrado!\n");
    else printf("Resultado: Item nao encontrado.\n");
    printf("--------------------------------------------\n");
}

int main() {
    Item mochilaV[MAX_ITENS];
    No* mochilaL = NULL;
    int totalItens = 0;
    int opcao;

    do {
        printf("\n============================================\n");
        printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("============================================\n");
        printf("Itens na Mochila: %d/%d\n\n", totalItens, MAX_ITENS);
        
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome\n");
        printf("0. Sair\n");
        printf("--------------------------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }
        limparBuffer();

        switch(opcao) {
            case 1: inserirItem(mochilaV, &totalItens, &mochilaL); break;
            case 3: 
                printf("\n--- Lista de Itens (Vetor) ---\n");
                for(int i=0; i<totalItens; i++) printf("%d. %s (%s) - Qtd: %d\n", i+1, mochilaV[i].nome, mochilaV[i].tipo, mochilaV[i].quantidade);
                break;
            case 4: realizarBusca(mochilaV, totalItens, mochilaL); break;
            case 0: printf("Saindo do sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}