
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void inserirItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void removerItem(Item mochila[], int *total);

int main() {
    Item mochila[MAX_ITENS];
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
        printf("0. Sair\n");
        printf("--------------------------------------------\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch(opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}

void inserirItem(Item mochila[], int *total) {
    if (*total < MAX_ITENS) {
        printf("\n--- Adicionar Novo Item ---\n");
        printf("Nome do item: ");
        fgets(mochila[*total].nome, 30, stdin);
        mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = 0;

        printf("Tipo: ");
        fgets(mochila[*total].tipo, 20, stdin);
        mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = 0;

        printf("Quantidade: ");
        scanf("%d", &mochila[*total].quantidade);
        getchar();

        (*total)++;
        printf("\nItem adicionado com sucesso!\n");
    } else {
        printf("\nMochila cheia!\n");
    }
}

void listarItens(Item mochila[], int total) {
    printf("\n--- Lista de Itens ---\n");
    if (total == 0) {
        printf("Mochila vazia.\n");
    } else {
        for (int i = 0; i < total; i++) {
            printf("%d. %s (%s) - Qtd: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("----------------------\n");
}

void removerItem(Item mochila[], int *total) {
    char busca[30];
    printf("\nDigite o nome do item para remover: ");
    fgets(busca, 30, stdin);
    busca[strcspn(busca, "\n")] = 0;

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, busca) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}