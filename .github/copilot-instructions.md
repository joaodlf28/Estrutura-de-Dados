# Copilot Instructions - Estrutura de Dados

## Project Overview
Educational data structures repository in C, focusing on practical implementations using static arrays and structs. Two main applications teach fundamental concepts: array-based collections and menu-driven CLI systems.

## Architecture & Key Patterns

### Static Array Data Management
- **Array-based storage**: All data structures use static arrays (`MAX_ITENS`, `MAX_LIVROS` constants)
- **Counter pattern**: Maintain a `total` or `totalXXX` variable tracking filled positions
- **Access pattern**: Index items as `array[position]` only up to the counter value
- **Example**: `Mochila de Sobrevivencia` stores up to 10 `Item` structs in array with `totalItens` counter

### Struct Convention
```c
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;
```
- Use `typedef` for cleaner declarations
- Fixed-size string fields with buffer sizes (not dynamic strings)
- Place struct definition before main for clarity

### Input/Output - Critical Buffer Management
**Essential pattern that must not be skipped:**
```c
scanf("%d", &opcao);
getchar();  // or limparBufferEntrada() - ALWAYS call this after scanf()
```

**String input requires `fgets()` + cleanup:**
```c
fgets(mochila[*total].nome, 30, stdin);
mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = 0;
```
The `strcspn()` removes the trailing newline that `fgets()` captures.

### Pointer Parameters for Modification
When a function must modify a counter or array position:
```c
void inserirItem(Item mochila[], int *total)  // *total is pointer
{
    (*total)++;  // Dereference to modify original variable
}
```

## Development Workflow

### Build Process
- **Compiler**: GCC with debugging flags (`-g`)
- **Task**: Run "C/C++: gcc arquivo de build ativo" from tasks
- **Output location**: Binary created in same directory as source file
- **Example**: `Estrutura de Dados/MOD01-*.c → Estrutura de Dados/MOD01-*` (no extension)

### File Organization
```
Estrutura de Dados/
├── MOD01-Prática - Sistema de Biblioteca.c
├── Desafio/Novato/MochiladeSobrevivencia.c
└── output/  (compiled binaries)
```

## Code Style & Conventions

- **Portuguese-named functions and variables** (educational style): `limparBufferEntrada()`, `totalLivros`
- **Descriptive main loop**: `do...while(opcao != 0)` for menu-driven programs
- **Switch statements**: Route user choices to specific operations
- **Comments**: Heavy documentation explaining data structure concepts
- **Menu display**: Show counters (e.g., "Itens na Mochila: 5/10") before option prompt

## Common Pitfalls to Avoid

1. **Forgetting buffer cleanup** after `scanf()` → causes input to be skipped
2. **Direct array assignment for strings** → use `fgets()`, not `scanf("%s")`
3. **Not checking array bounds** → verify `total < MAX_SIZE` before inserting
4. **Modifying original variables in functions** → use pointers and dereference them

## Integration Points

- **No external libraries**: Uses only `stdio.h`, `string.h`, `stdlib.h`
- **Single-threaded CLI**: No concurrency, all synchronous input/menu operations
- **Persistent data**: Only in-memory (program runtime); no file persistence
