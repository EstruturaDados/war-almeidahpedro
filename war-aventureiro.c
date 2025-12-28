#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Struct que representa um território do jogo WAR
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/*
    Função para cadastrar os territórios
*/
void cadastrarTerritorios(Territorio *mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\nTerritório %d\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %9s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

/*
    Função para exibir os territórios cadastrados
*/
void exibirTerritorios(Territorio *mapa, int total) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < total; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
}

/*
    Função que simula um ataque entre dois territórios
*/
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n⚔️ Ataque iniciado!\n");
    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("🏆 Atacante venceu o ataque!\n");

        // Defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // Transferência de metade das tropas
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    } else {
        printf("🛡️ Defensor resistiu ao ataque!\n");

        // Atacante perde uma tropa
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

/*
    Função para liberar memória alocada dinamicamente
*/
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    int totalTerritorios;
    int atacanteIndex, defensorIndex;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("=== WAR ESTRUTURADO - MODO AVENTUREIRO ===\n");
    printf("Informe o número de territórios: ");
    scanf("%d", &totalTerritorios);

    // Alocação dinâmica dos territórios
    Territorio *mapa = (Territorio *)calloc(totalTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, totalTerritorios);

    // Exibe o mapa inicial
    exibirTerritorios(mapa, totalTerritorios);

    // Escolha do ataque
    printf("\nEscolha o território atacante (índice): ");
    scanf("%d", &atacanteIndex);

    printf("Escolha o território defensor (índice): ");
    scanf("%d", &defensorIndex);

    // Validações básicas
    if (atacanteIndex < 0 || atacanteIndex >= totalTerritorios ||
        defensorIndex < 0 || defensorIndex >= totalTerritorios) {
        printf("Índice inválido.\n");
    } else if (strcmp(mapa[atacanteIndex].cor, mapa[defensorIndex].cor) == 0) {
        printf("❌ Não é permitido atacar um território da mesma cor.\n");
    } else {
        atacar(&mapa[atacanteIndex], &mapa[defensorIndex]);
    }

    // Exibição pós-ataque
    exibirTerritorios(mapa, totalTerritorios);

    // Liberação de memória
    liberarMemoria(mapa);

    return 0;
}
