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

// --- Estrutura do Jogador ---
struct Jogador {
    char cor[TAM_STRING];
    int missao;
    char corAlvo[TAM_STRING];
};

// --- Protótipos das funções ---
void cadastrarTerritorios(struct Territorio *territorios, int *numTerritorios);
void listarTerritorios(struct Territorio *territorios, int total);
void atacar(struct Territorio *atacante, struct Territorio *defensor);
void escolhaCor(struct Territorio *territorios, struct Jogador *jogador, int numTerritorios);
void sortearMissao(struct Jogador *jogador, struct Territorio *territorios, int numTerritorios);
void verificarMissao(struct Territorio *territorios, int numTerritorios, struct Jogador *jogador);
void menu(struct Territorio *territorios, int numTerritorios, struct Jogador *jogador);
void limpaBufferEntrada();

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

    struct Jogador *jogador = (struct Jogador *)calloc(1, sizeof(struct Jogador));
    if (jogador == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }


    // --- Inicia o cadastro dos territórios ---
    cadastrarTerritorios(territorios, &numTerritorios);
    
    // --- Exibe o estado inicial do mapa ---
    listarTerritorios(territorios, numTerritorios);

    // --- Sorteia a cor do jogador ---
    escolhaCor(territorios, jogador, numTerritorios);

    // --- Sorteia a missão ---
    sortearMissao(jogador, territorios, numTerritorios);

    // exibe menu de ataque
    menu(territorios, numTerritorios, jogador);


    printf("\n--- Fim da Guerra ---\n");
    free(territorios);
    free(jogador);
    return 0;
}

//================= IMPLEMENTAÇÃO DAS FUNÇÕES ========================

 // --- Função para cadastrar territórios ---
void cadastrarTerritorios(struct Territorio *territorios, int *numTerritorios) {
    printf("\n=======================");
    printf("\n=   WAR ESTRUTURADO   =\n");
    printf("=======================\n");
    while (*numTerritorios < MAX_TERRITORIOS) {
        int indice = *numTerritorios;
        printf("\n--- Cadastrando o território %d ---\n", indice + 1);
        printf("Digite o nome do território: ");
        fgets(territorios[indice].nome, TAM_STRING, stdin);
        territorios[indice].nome[strcspn(territorios[indice].nome, "\n")] = '\0';

        printf("Digite a cor do exército: ");
        fgets(territorios[indice].cor, TAM_STRING, stdin);
        territorios[indice].cor[strcspn(territorios[indice].cor, "\n")] = '\0';

        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[indice].tropas);
        limpaBufferEntrada();

        (*numTerritorios)++;
    }
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

void loopAtaque(struct Territorio *territorios, int numTerritorios) {
    int iAtacante, iDefensor;
    printf("\n--- Fase de ataques ---\n");
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
        printf("\nPressione Enter para continuar para o proximo turno.\n");
        getchar();

        // --- Exibe o estado atualizado do mapa ---
        listarTerritorios(territorios, numTerritorios);
    } while (iAtacante != 0);
}

// --- Função para escolher a cor do exército ---
void escolhaCor(struct Territorio *territorios,struct Jogador *jogador, int numTerritorios) {

    int indice = rand() % numTerritorios; // sorteia um índice de território existente
    strcpy(jogador->cor, territorios[indice].cor);

    printf("\n-------------------------------------\n");
    printf("  Sua cor de exército foi sorteada!  \n");
    printf("  Você será o exército %s.\n", jogador->cor);
    printf("-------------------------------------\n");
}

// --- Função para sortear a missão ---
void sortearMissao(struct Jogador *jogador, struct Territorio *territorios, int numTerritorios) {
    jogador->missao = rand() % 3;
    int corAleatoria = rand() % numTerritorios;

    printf("\n--- SUA MISSÃO ---\n");
    switch (jogador->missao) {
        case 0:
            printf("Conquistar 2 territórios.\n");
            break;
        case 1:
            do {
            corAleatoria = rand() % numTerritorios;
            strcpy(jogador->corAlvo, territorios[corAleatoria].cor);
            } while (strcmp(jogador->corAlvo, jogador->cor) == 0);
            printf("Destruir o exército %s.\n", jogador->corAlvo);
            break;
        case 2:
            printf("Manter 2 territórios com 3 ou mais tropas.\n");
            break;
    }
}

// --- Função para verificar se a missão foi cumprida ---
void verificarMissao(struct Territorio *territorios, int numTerritorios, struct Jogador *jogador) {
    int cont = 0;
    int cumpriu = 0;

    switch (jogador->missao) {
        case 0: // Conquistar 2 territórios
            for (int i = 0; i < numTerritorios; i++) {
                if (strcmp(territorios[i].cor, jogador->cor) == 0)
                    cont++;
            }
            if (cont >= 2) cumpriu = 1;
            break;

        case 1: // Destruir o exército alvo sorteado
            for (int i = 0; i < numTerritorios; i++) {
            if (strcmp(territorios[i].cor, jogador->corAlvo) == 0)
                cont++;
            }
            if (cont == 0) cumpriu = 1;
            break;

        case 2: // Manter 2 territórios com 3 ou mais tropas
            for (int i = 0; i < numTerritorios; i++) {
                if (strcmp(territorios[i].cor, jogador->cor) == 0 && territorios[i].tropas >= 3)
                    cont++;
            }
            if (cont >= 2) cumpriu = 1;
            break;
    }

    // Mostra resultado dentro da função
    if (cumpriu)
        printf("\nMissão concluída! Parabéns, você venceu!\n");
    else
        printf("\nMissão ainda não concluída.\n");
}

// --- Função para exibir o menu de ataque ---
void menu(struct Territorio *territorios, int numTerritorios, struct Jogador *jogador) {
    int missaoSorteada = jogador->missao;
    int opcao;

    do {
        printf("\n--- MENU DE AÇÕES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua ação: ");
        scanf("%d", &opcao);
        limpaBufferEntrada();

        switch (opcao) {
            case 1: {
                loopAtaque(territorios, numTerritorios);
                printf("\nPressione Enter para continuar...\n");
                getchar();
                break;
            }

            case 2: {
                verificarMissao(territorios, numTerritorios, jogador);

                printf("\nPressione Enter para continuar...\n");
                getchar();
                break;
            }

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);
}

// --- Limpa o buffer do teclado ---
void limpaBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}