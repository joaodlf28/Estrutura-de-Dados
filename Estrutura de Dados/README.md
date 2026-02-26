Para explicar como esse código funciona, imagine que estamos construindo um fichário físico para uma biblioteca. 
O código segue uma lógica de entrada, processamento e saída.

Aqui está a explicação dividida por partes:

==================================
1. A Estrutura (O molde do livro)

struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edição;
};
=============================================

A linguagem C não possui um tipo de dado "Livro". 
Por isso, usamos uma struct (estrutura) para criar nosso próprio tipo de dado que agrupa diferentes informações (strings e inteiros) sob um único nome.

==================================
2. O Buffer e a Limpeza (O "faxineiro")

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
============================================

Quando você digita um número e aperta "Enter", o número vai para a variável, mas o "Enter" (\n) fica sobrando no teclado. 
Se não limparmos isso, a próxima pergunta (como "Qual o nome do livro?") será pulada automaticamente porque o programa acha que o "Enter" que sobrou já é a resposta.

==================================
3. O Vetor de Livros (A estante)
Dentro da main, temos:
biblioteca[MAX_LIVROS]: É um array (vetor) que guarda até 50 estruturas do tipo Livro.
totalLivros: Um contador que começa em 0 e nos diz quantos livros já foram guardados.

============================================
4. O Menu e o Fluxo (O recepcionista)
O programa usa um laço do...while para que o menu apareça repetidamente até que o usuário digite 0. O switch(opcao) funciona como um direcionador:
  
  Caso 1 (Cadastro):
  Verifica se ainda há espaço (totalLivros < MAX_LIVROS).
  Usa fgets para ler nomes compostos (com espaços).
  O truque do strcspn: O fgets salva o "Enter" que você deu no final do nome. Essa linha remove esse "Enter" e coloca um terminador de texto (0 ou \0) no lugar, para que o texto não fique quebrado ao imprimir.
  Incrementa o totalLivros++ para que o próximo livro seja salvo na posição seguinte.

  Caso 2 (Listagem):
  Verifica se existem livros cadastrados.
  Usa um laço for que vai de 0 até o totalLivros.
  Imprime cada campo da struct acessando biblioteca[i].nome, biblioteca[i].autor, etc.


Resumo do Funcionamento

1. O programa inicia e cria uma "estante vazia" para 50 livros.
2. O usuário escolhe uma opção.
3. Se for Cadastrar, ele preenche os dados na posição atual do contador e depois soma +1 nesse contador.
4. Se for Listar, ele percorre a estante do início até onde o contador parou, exibindo os dados.
5. O programa limpa o buffer e aguarda um novo comando.
