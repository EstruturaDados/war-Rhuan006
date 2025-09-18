// ============================================================================
//              PROJETO SIMPLES - CADASTRO DE TERRITÓRIOS
// ============================================================================

#include <stdio.h>
#include <string.h>

// --- Constantes Globais ---
#define MAX_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR  10

// --- Estrutura de Dados ---
// Cada território terá um nome, uma cor de exército e quantidade de tropas.
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
void cadastrarTerritorios(Territorio territorios[], int tamanho);
void exibirTerritorios(const Territorio territorios[], int tamanho);

// --- Função Principal ---
int main() {
    Territorio territorios[MAX_TERRITORIOS]; // Vetor que armazena 5 territórios

    printf("==============================================\n");
    printf("      WAR ESTRUTURADO - CADASTRO INICIAL    \n");
    printf("==============================================\n");

    // Entrada dos dados
    cadastrarTerritorios(territorios, MAX_TERRITORIOS);

    // Mensagem de confirmaçaõo
    printf("\nCadastro inicial concluído com sucesso!\n\n");

    // Saída dos dados
    exibirTerritorios(territorios, MAX_TERRITORIOS);

    return 0;
}

// --- Implementação das Funções ---

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio territorios[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\nCadastro do Território %d\n", i + 1);

        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, MAX_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove o '\n'

        printf("Digite a cor do exército: ");
        fgets(territorios[i].cor, MAX_COR, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // remove o '\n'

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        getchar(); // consome o '\n' que fica após o scanf de número
    }
}

// Função para exibir todos os territorios
void exibirTerritorios(const Territorio territorios[], int tamanho) {
    printf("==============================================\n");
    printf("      MAPA DO MUNDO - ESTADO ATUAL    \n");
    printf("==============================================\n");

    for(int i = 0; i < tamanho; i++) {
        printf("TERRITÓRIO %d:\n", i + 1);
        printf("- Nome: %s\n", territorios[i].nome);
        printf("- Dominado por: %s\n", territorios[i].cor);
        printf("- Tropas: %d\n\n", territorios[i].tropas);
    }
    printf("==============================================\n");
}