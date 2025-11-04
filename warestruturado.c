#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Projeto War Estruturado ---

#define MAX_TERRITORIOS 5
#define TAM_STRING 30

// --- Estrutura do Território ---
struct Territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

// --- Limpa o buffer do teclado ---
void limpaBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função para listar territórios ---
void listarTerritorios(struct Territorio *territorio, int total) {
    printf("\n====================================\n");
    printf("    MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("====================================\n\n");

    for (int i = 0; i < total; i++) {
        printf("%d. %s (Exército %s, Tropas: %d)\n",
               i + 1, territorio[i].nome, territorio[i].cor, territorio[i].tropas);
    }
}

// --- Função que simula o ataque ---
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    printf("\n--- Simulação de Ataque ---\n");
    printf("%s (%s) atacando %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    // Simulação de rolagem de dados
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf(">>> Ataque bem-sucedido!\n");
        defensor->tropas -= 1;

        if (defensor->tropas <= 0) {
            printf(">>> O território %s foi conquistado!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);
            // transfere metade das tropas
            defensor->tropas = atacante->tropas / 2;
            atacante->tropas /= 2;
        }
    } else {
        printf(">>> O ataque falhou. Tropas do atacante foram reduzidas.\n");
        atacante->tropas -= 1;
    }
}

// --- Função principal ---
int main() {
    srand(time(NULL));

    int numTerritorios = 0;

    // --- Alocação dinâmica ---
    struct Territorio *territorios = (struct Territorio *)calloc(MAX_TERRITORIOS, sizeof(struct Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // --- Cadastro dos territórios ---
    while (numTerritorios < MAX_TERRITORIOS) {
        printf("\n--- Cadastrando o território %d ---\n", numTerritorios + 1);
        printf("Digite o nome do território: ");
        fgets(territorios[numTerritorios].nome, TAM_STRING, stdin);
        territorios[numTerritorios].nome[strcspn(territorios[numTerritorios].nome, "\n")] = '\0';

        printf("Digite a cor do exército: ");
        fgets(territorios[numTerritorios].cor, TAM_STRING, stdin);
        territorios[numTerritorios].cor[strcspn(territorios[numTerritorios].cor, "\n")] = '\0';

        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[numTerritorios].tropas);
        limpaBufferEntrada();

        numTerritorios++;
    }

    // --- Exibe o estado inicial do mapa ---
    listarTerritorios(territorios, numTerritorios);

    int iAtacante, iDefensor;

    // --- Loop de ataques ---
    do {
        printf("\nEscolha o número do território atacante (1 a %d) ou 0 para sair: ", numTerritorios);
        scanf("%d", &iAtacante);
        if (iAtacante == 0) break;

        printf("Escolha o número do território defensor (1 a %d): ", numTerritorios);
        scanf("%d", &iDefensor);
        limpaBufferEntrada();

        if (iAtacante < 1 || iAtacante > numTerritorios ||
            iDefensor < 1 || iDefensor > numTerritorios) {
            printf("Escolha inválida! Índices fora do intervalo.\n");
            continue;
        }
        if (iAtacante == iDefensor) {
            printf("Escolha inválida! Um território não pode atacar a si mesmo.\n");
            continue;
        }

        if (strcmp(territorios[iAtacante - 1].cor, territorios[iDefensor - 1].cor) == 0) {
            printf("Operação inválida: o exército '%s' não pode atacar outro território do mesmo exército '%s'.\n",
                   territorios[iAtacante - 1].cor, territorios[iDefensor - 1].cor);
            continue;
        }

        if (territorios[iAtacante - 1].tropas <= 1) {
            printf("O território atacante precisa ter mais de 1 tropa para atacar.\n");
            continue;
        }
        // --- Execução do ataque ---
        atacar(&territorios[iAtacante - 1], &territorios[iDefensor - 1]);
        
        // --- Pausa para leitura do ataque---
        printf("\nPrecione Enter para continuar para o proximo turno.\n");
        getchar();

        // --- Exibe o estado atualizado do mapa ---
        listarTerritorios(territorios, numTerritorios);
    } while (iAtacante != 0);
    printf("\n--- Fim da Guerra ---\n");
    free(territorios);
    return 0;
}