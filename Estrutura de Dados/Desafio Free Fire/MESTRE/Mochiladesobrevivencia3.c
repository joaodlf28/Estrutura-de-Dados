#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis globais para controle de estado
int ordenadoPorNome = 0; // 0 = NÃO ORDENADO, 1 = ORDENADO

// Protótipos
void adicionar(Componente lista[], int *n);
void descartar(Componente lista[], int *n);
void listar(Componente lista[], int n);
void organizar(Componente lista[], int n);
void bubbleSortNome(Componente lista[], int n, int *comps);
void insertionSortTipo(Componente lista[], int n, int *comps);
void selectionSortPrioridade(Componente lista[], int n, int *comps);
void buscaBinaria(Componente lista[], int n);
void limparBuffer();

int main() {
    Componente mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        // Interface idêntica à imagem fornecida
        printf("\n===========================================================\n");
        printf("  PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("===========================================================\n");
        printf("Itens na Mochila: %d/%d\n", totalItens, MAX_ITENS);
        printf("Status da Ordenacao por Nome: %s\n\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("-----------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: adicionar(mochila, &totalItens); break;
            case 2: descartar(mochila, &totalItens); break;
            case 3: listar(mochila, totalItens); break;
            case 4: organizar(mochila, totalItens); break;
            case 5: buscaBinaria(mochila, totalItens); break;
            case 0: printf("\nAtivando torre... Boa sorte na fuga, recruta!\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- FUNÇÕES DE GERENCIAMENTO ---

void adicionar(Componente lista[], int *n) {
    if (*n >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }
    printf("Nome do componente: ");
    fgets(lista[*n].nome, 30, stdin);
    lista[*n].nome[strcspn(lista[*n].nome, "\n")] = 0;
    
    printf("Tipo (controle/suporte/propulsao): ");
    fgets(lista[*n].tipo, 20, stdin);
    lista[*n].tipo[strcspn(lista[*n].tipo, "\n")] = 0;
    
    printf("Prioridade (1-10): ");
    scanf("%d", &lista[*n].prioridade);
    limparBuffer();
    
    (*n)++;
    ordenadoPorNome = 0; // Nova inserção quebra a ordenação
    printf("\nComponente adicionado com sucesso!\n");
}

void descartar(Componente lista[], int *n) {
    if (*n == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    listar(lista, *n);
    int idx;
    printf("\nDigite o numero do item para descartar (1-%d): ", *n);
    scanf("%d", &idx);
    limparBuffer();

    if (idx >= 1 && idx <= *n) {
        for (int i = idx - 1; i < *n - 1; i++) {
            lista[i] = lista[i + 1];
        }
        (*n)--;
        printf("\nComponente descartado!\n");
    }
}

void listar(Componente lista[], int n) {
    printf("\n--- INVENTARIO ATUAL ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. [%s] Tipo: %s | Prio: %d\n", i + 1, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}

// --- MÓDULO DE ORDENAÇÃO E PERFORMANCE ---

void organizar(Componente lista[], int n) {
    int escolha, comps = 0;
    clock_t inicio, fim;

    printf("\nEscolha o Algoritmo:\n1. Bubble (Nome)\n2. Insertion (Tipo)\n3. Selection (Prio)\nOpcao: ");
    scanf("%d", &escolha);

    inicio = clock();
    if (escolha == 1) {
        bubbleSortNome(lista, n, &comps);
        ordenadoPorNome = 1;
    } else if (escolha == 2) {
        insertionSortTipo(lista, n, &comps);
        ordenadoPorNome = 0;
    } else if (escolha == 3) {
        selectionSortPrioridade(lista, n, &comps);
        ordenadoPorNome = 0;
    }
    fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nOrdenacao concluida!\nComparacoes: %d | Tempo: %.6f s\n", comps, tempo);
}

void bubbleSortNome(Componente lista[], int n, int *comps) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comps)++;
            if (strcmp(lista[j].nome, lista[j+1].nome) > 0) {
                Componente temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

void insertionSortTipo(Componente lista[], int n, int *comps) {
    for (int i = 1; i < n; i++) {
        Componente pivo = lista[i];
        int j = i - 1;
        while (j >= 0 && strcmp(lista[j].tipo, pivo.tipo) > 0) {
            (*comps)++;
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = pivo;
    }
}

void selectionSortPrioridade(Componente lista[], int n, int *comps) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*comps)++;
            if (lista[j].prioridade < lista[min].prioridade) min = j;
        }
        Componente temp = lista[min];
        lista[min] = lista[i];
        lista[i] = temp;
    }
}

// --- BUSCA BINÁRIA ---

void buscaBinaria(Componente lista[], int n) {
    if (!ordenadoPorNome) {
        printf("\n[ALERTA] Ordene por NOME (Opcao 4 -> 1) antes de buscar!\n");
        return;
    }

    char alvo[30];
    printf("Nome do componente-chave: ");
    fgets(alvo, 30, stdin);
    alvo[strcspn(alvo, "\n")] = 0;

    int esq = 0, dir = n - 1, achou = -1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int res = strcmp(lista[meio].nome, alvo);
        if (res == 0) { achou = meio; break; }
        if (res < 0) esq = meio + 1;
        else dir = meio - 1;
    }

    if (achou != -1) printf("\n[OK] Encontrado: %s na posicao %d.\n", lista[achou].nome, achou + 1);
    else printf("\n[ERRO] Componente nao encontrado.\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}