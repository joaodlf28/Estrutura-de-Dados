// ======================================================
// Prática -Sistema de Biblioteca -Parte 1
//
// Objetivo: Implementar o cadastro e a listagem de livros usando um array estático.
// Foco: Structs, entrada/saída de dados e organização básica do código.
//
//
// ======================================================

#include <stdio.h>
#include <string.h> //
#include <string.h> // Para strcspn()

// --- Constantes Globais ---
#define MAX_LIVROS 50
#define TAM_STRING 100

// --- Definição da Struct Livro ---
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edição;
};

// --- Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
int main() {
    struct Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;      

    // --- Laço Principal do Menu ---
    do {

        // Exibe o menu de opções.
        printf("=================================\n");
        printf("   BIBLIOTECA - PARTE 1\n");
        printf("=================================\n");
        printf("1. Cadastrar Livro\n");
        printf("2. Listar Livros\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        // Lê a opção do usuário.
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf.

        // --- Processa a opção escolhida ---
        switch (opcao) {
            case 1: // CADASTRO DE LIVRO
                printf("----- Cadastro de novo livro -----\n");

                if (totalLivros < MAX_LIVROS) {
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o autor do livro: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                    printf("Digite a editora do livro: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);
                    
                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = 0;
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = 0;
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = 0;

                    printf("Digite a edicao do livro: ");
                    scanf("%d", &biblioteca[totalLivros].edição);
                    limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf.

                    totalLivros++;
                    // totalLivros = totalLivros + 1;

                    printf("\nLivro cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia! Não é possível cadastrar mais livros.\n");
                }
                printf("\n Pressione Enter para continuar...");
                getchar(); // Aguarda o usuário pressionar Enter.
                break;

            case 2: // LISTAGEM DE LIVROS
                printf("----- Lista de Livros Cadastrados -----\n\n");

                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("Livro %d:\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edição: %d\n", biblioteca[i].edição);
                    }
                     printf("-------------------------\n");
                    }
                    // A pasta é crucial para que o usuário veja a lista antes
                    // do próximo loop limpart a tela.
                    printf("\n Pressione Enter para continuar...");
                    getchar(); // Aguarda o usuário pressionar Enter.
                    break;  

            case 0: // SAIR
                printf("\nSaindo do programa. Até logo!\n");
                break;

            default: // OPÇÃO INVÁLIDA
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("\n Pressione Enter para continuar...");
                getchar(); // Aguarda o usuário pressionar Enter.
                break;
        }   
    } while (opcao != 0); 
}
