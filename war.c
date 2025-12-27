#include <stdio.h>
#include <string.h>

#define TOTAL_TERRITORIOS 5

// Definição da struct Territorio
// Essa estrutura agrupa informações relacionadas a um território
struct Territorio {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército
    int tropas;        // Quantidade de tropas
};

int main() {

    // Declaração de um vetor de structs para armazenar 5 territórios
    struct Territorio territorios[TOTAL_TERRITORIOS];

    printf("=== Cadastro de Territórios ===\n\n");

    // Laço para entrada dos dados
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Território %d\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do território: ");
        scanf(" %29[^\n]", territorios[i].nome);

        // Leitura da cor do exército
        printf("Digite a cor do exército: ");
        scanf(" %9s", territorios[i].cor);

        // Leitura da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("=== Territórios Cadastrados ===\n\n");

    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
