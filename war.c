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
#define MAX_MISSAO 200

// --- Estrutura de Dados ---
// Cada território terá um nome, uma cor de exército e quantidade de tropas.
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    char* missao; // alocado dinamicamente
} Jogador;

// --- Protótipos das Funções ---
Territorio* alocarMapa(int n);
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirMapa(const Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa, Jogador* jogadores, int qtdJogadores);

// Funções de missão
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(const char* missao, const Territorio* mapa, int n);
void exibirMissao(const char* missao);

// --- Função Principal ---
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // --- cadastro de Jogadores ---
    int qtdJogadores;
    printf("==================================\n");
    printf("Digite o número de jogadores: ");
    scanf("%d", &qtdJogadores);
    getchar(); // limpa o '\n'

    Jogador* jogadores = (Jogador*) calloc(qtdJogadores, sizeof(Jogador));

    // Missões pré-definidas
    char* missoes[] = {
        "Consquitar pelo menos 3 territórios",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar 2 territorios seguidos",
        "Ter pelo menos 10 tropas em um unico territorio",
        "Ser dono de todos os territorios"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    for (int i = 0; i < qtdJogadores; i++) {
        printf("\n--- Cadastro Jogador %d ---\n", i + 1);
        printf("Nome: ");
        fgets(jogadores[i].nome, MAX_NOME, stdin);
        jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0'; // remove o '\n'

        printf("Cor: ");
        fgets(jogadores[i].cor, MAX_COR, stdin);
        jogadores[i].cor[strcspn(jogadores[i].cor, "\n")] = '\0';
        
        // aloca espaço para a missão
        jogadores[i].missao = (char*) malloc(MAX_MISSAO);
        if (jogadores[i].missao == NULL) {
            printf("Erro na alocação de memória para missão!\n");
            return 1;
        }

        //orteia uma missão
        atribuirMissao(jogadores[i].missao, missoes, totalMissoes);
        printf("Missão atribuída: %s\n", jogadores[i].missao);
    }

    // --- cadastro de territórios ---
    int n;
    printf("==================================\n");
    printf("Digite o número de territorios: ");
    scanf("%d", &n);
    getchar(); // limpa o '\n'

    // Alocação dinâmica do mapa
    Territorio* mapa = alocarMapa(n);
    if (!mapa) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }

    // Cadastro Inicial
    cadastrarTerritorios(mapa, n);
    exibirMapa(mapa, n);
    printf("\nCadastro inicial concluído com sucesso!\n\n");

    // --- Menu Principal ---
    int opcao;
    do {
        printf("\n================= MENU PRINCIPAL ================\n");
        printf("1 - Exibir Mapa\n");
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
            idAtacante --; idDefensor --;

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

            // verifica Missões
            for (int i = 0; i < qtdJogadores; i++) {
                if (verificarMissao(jogadores[i].missao, mapa, n)) {
                    printf("\n🎉 Jogador %s cumpriu a missão e venceu o jogo!\n", jogadores[i].nome);
                    liberarMemoria(mapa, jogadores, qtdJogadores);
                    return 0;
                }
            }

        }
    } while (opcao != 0);

    // Liberação da memória
    liberarMemoria(mapa, jogadores, qtdJogadores);
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

        printf("Nome: ");
        fgets(mapa[i].nome, MAX_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove o '\n'

        printf("Cor: ");
        fgets(mapa[i].cor, MAX_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0'; // remove o '\n'

        printf("Tropas: ");
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

// --- Missões ---
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

int verificarMissao(const char* missao, const Territorio* mapa, int n) {
    if (strstr(missao, "10 tropas")) {
        for (int i = 0; i < n; i++) {
            if (mapa[i].tropas >= 10) 
                return 1;
        }
    }
    if (strstr(missao, "todos os territorios")) {
        const char* cor = mapa[0].cor;
        for (int i = 1; i < n; i++) {
            if (strcmp(mapa[i].cor, cor) != 0)
                return 0;
        }
        return 1;
    }
    return 0;
}

// Libera a memória alocada para o mapa
void liberarMemoria(Territorio* mapa, Jogador* jogadores, int qtdJogadores) {
    free(mapa);
    for (int i = 0; i < qtdJogadores; i++) {
        free(jogadores[i].missao);
    }
    free(jogadores);
}