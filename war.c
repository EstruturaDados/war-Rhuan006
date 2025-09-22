// ============================================================================
//              PROJETO SIMPLES - CADASTRO DE TERRITÓRIOS
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
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
Territorio* alocarMapa(int n);
void cadastrarTerritorios(Territorio* mapa, int);
void exibirMapa(const Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

// --- Função Principal ---
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    int n;
    printf("==================================\n");
    printf("Digite o número de territorios: ");
    scanf("%d", &n);
    getchar(); // limpa o '\n'

    // Alocação dinâmica do mapa
    Territorio* mapa = alocarMapa(n);
    if (mapa == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }

    // Cadastro Inicial
    cadastrarTerritorios(mapa, n);
    printf("\nCadastro inicial concluído com sucesso!\n\n");

    int opcao;
    do {
        printf("\n================= MENU PRINCIPAL ================\n");
        printf("1 - Exibir Territórios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("==================================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o '\n'

        if (opcao == 1) {
            exibirMapa(mapa, n);
        } else if (opcao == 2) {
            int idAtacante, idDefensor;
            exibirMapa(mapa, n);

            printf("\nEscolha o território atacante (1 a %d): ", n);
            scanf("%d", &idAtacante);
            printf("Escolha o território defensor (1 a %d): ", n);
            scanf("%d", &idDefensor);

            // ajusta para indice do vetor
            idAtacante -= 1;
            idDefensor -= 1;

            if (idAtacante < 0 || idAtacante >= n || idDefensor < 0 || idDefensor >= n) {
                printf("\nIDs inválidos!\n");
                continue;
            }
            if (idAtacante == idDefensor) {
                printf("\nUm território não pode atacar a si mesmo!\n");
                continue;
            }

            atacar(&mapa[idAtacante], &mapa[idDefensor]);
            exibirMapa(mapa, n);

        }
        else if (opcao == 0) {
            printf("\nSaindo do jogo... Até a próxima!\n");
        } else {
            printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    // Liberação da memória
    liberarMemoria(mapa);

    return 0;
}
// --- Implementação das Funções ---

// Aloca dinamicamente memória para os territórios
Territorio* alocarMapa(int n) {
    return (Territorio*) calloc(n, sizeof(Territorio));
}

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        fgets(mapa[i].nome, MAX_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove o '\n'

        printf("Digite a cor do exército: ");
        fgets(mapa[i].cor, MAX_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0'; // remove o '\n'

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        getchar(); // consome o '\n' que fica após o scanf de número
    }
}

// Função para exibir todos os territorios
void exibirMapa(const Territorio* mapa, int n) {
    printf("==============================================\n");
    printf("      MAPA DO MUNDO - ESTADO ATUAL    \n");
    printf("==============================================\n");

    for(int i = 0; i < n; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n", 
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("==============================================\n");
}

// Simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if(strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nNão é possível atacar um território com a mesma cor de exército!\n");
        return;
    }

    if (atacante->tropas < 2) {
        printf("\nO território precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1; // Dado de 1 a 6
    int dadoDefensor = rand() % 6 + 1; 

    printf("\n================= BATALHA ================\n");
    printf("Atacante (%s - %s) rolou: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("Defensor (%s - %s) rolou: %d\n", defensor->nome, defensor->cor, dadoDefensor);
    printf("==========================================\n");

    if (dadoAtacante > dadoDefensor) {
        printf("Vitória atacante!\n");
        strcpy(defensor->cor, atacante->cor); // Muda o dono do território
        defensor->tropas = atacante->tropas / 2; // transfere metade das tropas
        atacante->tropas -= defensor->tropas; // remove tropas do atacante
    } else {
        printf("Defensor resistiu!\n");
        atacante->tropas--; // Perde 1 tropa
    }
}

// Libera a memória alocada para o mapa
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}