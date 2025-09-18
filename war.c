// ============================================================================
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de string.
#define Max_Territorios 5
#define Max_Nome 30
#define Max_Cor 10
// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct {
    char nome[Max_Nome];
    char cor[Max_Cor];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
void cadastrarTerritorios(Territorio territorios[], int tamanho);
void exibirTerritorios(const Territorio territorios[], int tamanho);

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    Territorio territorios[Max_Territorios];
    printf("==============================================\n");
    printf("      WAR ESTRUTURADO - CADASTRO INICIAL      \n");
    printf("==============================================\n\n");
    
    // Entrada de dados
    cadastrarTerritorios(territorios, Max_Territorios);
    // Sáida de dados
    exibirTerritorios(territorios, Max_Territorios);

    return 0;
}

// --- Implementaçaõ das funções

// funçaõ para cadastrar os territórios
void cadastrarTerritorios(Territorio territorios[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\nCadastro do Territorio %d\n", i + 1);
        printf("Digite o nome do território: ");
        scanf(" %29[^\n]", territorios[i].nome);// lê string com espaços
        
        printf("Digite a cor do exército: ");
        scanf("%9s", territorios[i].cor);


    }
}
                                                                    