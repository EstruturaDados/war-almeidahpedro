#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Estrutura que representa um território do jogo
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/*
    Exibe o mapa atual
*/
void exibirMapa(Territorio *mapa, int tamanho) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
}

/*
    Simula um ataque entre dois territórios
*/
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n⚔️ %s ataca %s\n", atacante->nome, defensor->nome);
    printf("Atacante rolou: %d | Defensor rolou: %d\n",
           dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("🏆 Ataque bem-sucedido!\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
    } else {
        printf("🛡️ Defesa bem-sucedida!\n");
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

/*
    Sorteia e atribui uma missão ao jogador
*/
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

/*
    Exibe a missão do jogador (apenas uma vez)
*/
void exibirMissao(char *missao) {
    printf("\n🎯 SUA MISSÃO ESTRATÉGICA 🎯\n");
    printf("%s\n", missao);
}

/*
    Verifica se a missão foi cumprida
    Lógica simples baseada no texto da missão
*/
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {

    // Missão: Conquistar 3 territórios
    if (strstr(missao, "Conquistar 3 territórios")) {
        int controle = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0) {
                controle++;
            }
        }
        return controle >= 3;
    }

    // Missão: Eliminar tropas vermelhas
    if (strstr(missao, "Eliminar todas as tropas vermelhas")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0 &&
                mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }

    // Missão: Possuir território com 10 tropas
    if (strstr(missao, "10 tropas")) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas >= 10) {
                return 1;
            }
        }
    }

    return 0;
}

/*
    Libera toda memória alocada dinamicamente
*/
void liberarMemoria(Territorio *mapa, char *missao) {
    free(mapa);
    free(missao);
}

int main() {
    srand(time(NULL));

    int totalTerritorios;
    int atacante, defensor;

    // Vetor de missões estratégicas
    char *missoes[] = {
        "Conquistar 3 territórios",
        "Eliminar todas as tropas vermelhas",
        "Possuir um território com pelo menos 10 tropas",
        "Controlar a maioria do mapa",
        "Vencer qualquer ataque consecutivo"
    };

    int totalMissoes = 5;

    printf("=== WAR ESTRUTURADO - NIVEL MESTRE ===\n");
    printf("Quantidade de territórios: ");
    scanf("%d", &totalTerritorios);

    // Alocação dinâmica do mapa
    Territorio *mapa = (Territorio *)calloc(totalTerritorios, sizeof(Territorio));

    if (!mapa) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < totalTerritorios; i++) {
        printf("\nTerritório %d\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Cor: ");
        scanf(" %9s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    // Alocação dinâmica da missão do jogador
    char *missaoJogador = (char *)malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    // Loop de turno único (simplificado)
    exibirMapa(mapa, totalTerritorios);

    printf("\nEscolha atacante (indice): ");
    scanf("%d", &atacante);

    printf("Escolha defensor (indice): ");
    scanf("%d", &defensor);

    if (strcmp(mapa[atacante].cor, mapa[defensor].cor) != 0) {
        atacar(&mapa[atacante], &mapa[defensor]);
    } else {
        printf("❌ Ataque inválido (mesma cor).\n");
    }

    exibirMapa(mapa, totalTerritorios);

    // Verificação silenciosa da missão
    if (verificarMissao(missaoJogador, mapa, totalTerritorios)) {
        printf("\n🏆 PARABÉNS! VOCÊ CUMPRIU SUA MISSÃO!\n");
    } else {
        printf("\n⏳ Missão ainda não concluída.\n");
    }

    liberarMemoria(mapa, missaoJogador);

    return 0;
}
