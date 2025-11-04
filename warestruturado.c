#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Projeto War Estruturado ---

// --- Contantes Globais --- 
#define MAX_TERRIRORIOS 5
#define TAM_STRING 50

// --- Definição da Estrutura do Território ---
struct Territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

void limpaBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Territorio territorio[MAX_TERRIRORIOS];
    int numTerritorios = 0;

    while (numTerritorios < MAX_TERRIRORIOS) {
        printf("\n---Cadastrando o território %d ---\n", numTerritorios + 1);
        printf("Digite o nome do território: ");
        fgets(territorio[numTerritorios].nome, TAM_STRING, stdin);
        territorio[numTerritorios].nome[strcspn(territorio[numTerritorios].nome, "\n")] = '\0';

        printf("Digite a cor do Exercito: ");
        fgets(territorio[numTerritorios].cor, TAM_STRING, stdin);
        territorio[numTerritorios].cor[strcspn(territorio[numTerritorios].cor, "\n")] = '\0';

        printf("Digite o número de tropas: ");
        scanf("%d", &territorio[numTerritorios].tropas);
        limpaBufferEntrada(); // Limpa o '\n' deixado pelo scanf.

        numTerritorios++;
    }

    printf("\nInformações dos territórios:\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorio[i].nome);
        printf("Cor: %s\n", territorio[i].cor);
        printf("Tropas: %d\n", territorio[i].tropas);
        printf("\n");
    }

    return 0;
}