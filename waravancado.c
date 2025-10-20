//estrutura de dados - desafio mestre - modularizacao
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define MAX_STRING 25

typedef struct {
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int numero_tropas;
} Territorio;

typedef struct {
    int indice_atacante;
    int indice_defensor;
    int dados_atacante;
    int dados_defensor;
} Ataque;

// Protótipos
void limpar_buffer();
void cadastrar_territorios(Territorio *mapa, int *total_territorios);
void exibir_mapa(Territorio *mapa, int total_territorios);
void batalha(Territorio *mapa, int total_territorios);
void liberar_memoria(Territorio *mapa);
void menu(Territorio *mapa, int total_territorios, char *missao);
void selecionar_missao(Territorio *mapa, int total_territorios, char *missao);
void exibir_missao(const char *missao);

// ----------------------------------------------------------------------------------------------

int main() {
    Territorio *mapa = NULL;
    int total_territorios = 0;
    char missao[200] = "";

    printf("Iniciando Jogo WAR - Desafio Aventureiro...\n");
    srand(time(NULL));

    mapa = (Territorio *)calloc(MAX_TERRITORIOS, sizeof(Territorio));
    if (mapa == NULL) {
        printf("ERRO: Falha na alocação de memória para o mapa (CALLOC).\n");
        return 1;
    }

    printf("Memória alocada com sucesso para %d territórios (CALLOC).\n\n", MAX_TERRITORIOS);

    // Cadastro de territórios
    cadastrar_territorios(mapa, &total_territorios);

  // Exibir mapa
    exibir_mapa(mapa, total_territorios);

    // Seleção de missão
    selecionar_missao(mapa, total_territorios, missao);

    // exibir missao
    exibir_missao(missao);

    // Menu de opções, incluso batalha - case 1, verifica missao e mostra qual missao
    menu(mapa, total_territorios, missao);

    liberar_memoria(mapa);
    return 0;
}

// ----------------------------------------------------------------------------------------------

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ----------------------------------------------------------------------------------------------
void cadastrar_territorios(Territorio *mapa, int *total_territorios) {
    printf("=== CADASTRO DE TERRITÓRIOS ===\n\n");

    while (*total_territorios < MAX_TERRITORIOS) {
        printf("Digite o nome do território: ");
        fgets(mapa[*total_territorios].nome, MAX_STRING, stdin);
        mapa[*total_territorios].nome[strcspn(mapa[*total_territorios].nome, "\n")] = '\0';

        printf("Digite a cor do dono: ");
        fgets(mapa[*total_territorios].cor, MAX_STRING, stdin);
        mapa[*total_territorios].cor[strcspn(mapa[*total_territorios].cor, "\n")] = '\0';

        printf("Digite o número de tropas: ");
        if (scanf("%d", &mapa[*total_territorios].numero_tropas) != 1) {
            printf("Entrada inválida! Digite um número.\n");
            limpar_buffer();
            continue;
        }

        limpar_buffer();
        (*total_territorios)++;

        printf("\nTerritório cadastrado com sucesso! (%d/%d)\n\n",
               *total_territorios, MAX_TERRITORIOS);
    }

    printf("Cadastro de territórios concluído!\n");
}

// ----------------------------------------------------------------------------------------------
void exibir_mapa(Territorio *mapa, int total_territorios) {
    printf("\n=== MAPA MUNDIAL ===\n\n");

    for (int i = 0; i < total_territorios; i++) {
        printf("[%d] Território:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n\n", mapa[i].numero_tropas);
    }
}

// ----------------------------------------------------------------------------------------------
void selecionar_missao(Territorio *mapa, int total_territorios, char *missao) {
    int opcao;
    printf("=== SELECIONE SUA MISSÃO ===\n");
    printf("1 - Iniciante (conquiste 1 território)\n");
    printf("2 - Avançado (conquiste 2 territórios)\n");
    printf("3 - Jogar sem missão\n");
    printf("Escolha uma opção: ");

    if (scanf("%d", &opcao) != 1) {
        printf("Entrada inválida! Jogando sem missão.\n");
        limpar_buffer();
        strcpy(missao, "Jogando sem missão, conquiste os territórios que desejar.");
        return;
    }
    limpar_buffer();

    switch(opcao) {
        case 1: {
            int idx = rand() % total_territorios;
            sprintf(missao, "Sua missão é destruir [%d] - %s", idx + 1, mapa[idx].nome);
            break;
        }
        case 2: {
            int idx1 = rand() % total_territorios;
            int idx2;
            do {
                idx2 = rand() % total_territorios;
            } while (idx2 == idx1);
            sprintf(missao, "Sua missão é destruir [%d] - %s e [%d] - %s",
                    idx1 + 1, mapa[idx1].nome, idx2 + 1, mapa[idx2].nome);
            break;
        }
        case 3:
        default:
            strcpy(missao, "Jogando sem missão, conquiste os territórios que desejar.");
            break;
    }
}

// ----------------------------------------------------------------------------------------------
void exibir_missao(const char *missao) {
    printf("\n=== MISSÃO DO JOGADOR ===\n");
    printf("%s\n\n", missao);
}

// ----------------------------------------------------------------------------------------------
void menu(Territorio *mapa, int total_territorios, char *missao) {
    int opcao;
    int conquistado;

    do {
        printf("=== MENU ===\n");
        printf("1 - Realizar ataque\n");
        printf("2 - Verificar territórios conquistados\n");
        printf("3 - Sair do jogo\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) { 
            printf("Entrada inválida!\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();

        switch (opcao) {
            case 1:
                batalha(mapa, total_territorios);
                exibir_missao(missao); // mostra missão após ataque
                break;

            case 2:
                conquistado = 0;
                for (int i = 0; i < total_territorios; i++) {
                    if (mapa[i].numero_tropas == 0) {
                        printf("O território '%s' foi conquistado!\n", mapa[i].nome);
                        conquistado = 1;
                    }
                }
                if (!conquistado) {
                    printf("Ainda não há territórios conquistados.\n");
                }
                exibir_mapa(mapa, total_territorios);
                break;

            case 3:
                printf("Jogo finalizado.\n");
                return;

            default:
                printf("Opção inválida, tente novamente.\n");
        }

    } while (1);
}

// ----------------------------------------------------------------------------------------------
// Função batalha
void batalha(Territorio *mapa, int total_territorios) {
    int atacante_idx, defensor_idx;
    int dado_atacante, dado_defensor;

    // Seleção de territórios
    printf("Selecione o território atacante (1-%d): ", total_territorios);
    if (scanf("%d", &atacante_idx) != 1 || atacante_idx < 1 || atacante_idx > total_territorios) {
        printf("Entrada inválida!\n");
        limpar_buffer();
        return;
    }
    atacante_idx--;

    printf("Selecione o território defensor (1-%d): ", total_territorios);
    if (scanf("%d", &defensor_idx) != 1 || defensor_idx < 1 || defensor_idx > total_territorios) {
        printf("Entrada inválida!\n");
        limpar_buffer();
        return;
    }
    defensor_idx--;

    limpar_buffer();

    // Validações de tropa
    if (mapa[atacante_idx].numero_tropas <= 0) {
        printf("Território atacante não tem tropas suficientes.\n");
        return;
    }
    if (mapa[defensor_idx].numero_tropas <= 0) {
        printf("Território já conquistado, insira território válido.\n");
        return;
    }

    // Simulação de dados (não permite empate)
    do {
        dado_atacante = rand() % 6 + 1;
        dado_defensor = rand() % 6 + 1;
    } while (dado_atacante == dado_defensor);

    // Resultado da batalha
    printf("\nResultado da batalha:\n");
    printf("Atacante (%s) rolou: %d\n", mapa[atacante_idx].nome, dado_atacante);
    printf("Defensor (%s) rolou: %d\n", mapa[defensor_idx].nome, dado_defensor);

    if (dado_atacante > dado_defensor) {
        mapa[defensor_idx].numero_tropas--;
        printf("Atacante venceu! %s perde 1 tropa.\n", mapa[defensor_idx].nome);
    } else {
        mapa[atacante_idx].numero_tropas--;
        printf("Defensor venceu! %s perde 1 tropa.\n", mapa[atacante_idx].nome);
    }

    exibir_mapa(mapa, total_territorios);
}

// ----------------------------------------------------------------------------------------------
void liberar_memoria(Territorio *mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}
 