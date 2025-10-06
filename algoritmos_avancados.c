#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-----------------------------------------
// Estrutura que representa uma sala da mansão
//-----------------------------------------
typedef struct Sala {
    char nome[50];            // Nome da sala (ex: "Cozinha", "Jardim")
    struct Sala *esq;         // Caminho à esquerda
    struct Sala *dir;         // Caminho à direita
} Sala;

//-----------------------------------------
// Função: criarSala
// Cria dinamicamente uma sala e retorna seu ponteiro
//-----------------------------------------
Sala* criarSala(const char *nome) {
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));  // Aloca memória
    strcpy(novaSala->nome, nome);                   // Copia o nome da sala
    novaSala->esq = NULL;                           // Nenhum caminho ainda
    novaSala->dir = NULL;
    return novaSala;                                // Retorna o endereço da sala criada
}

//-----------------------------------------
// Função: explorarSalas
// Permite ao jogador navegar pela mansão
//-----------------------------------------
void explorarSalas(Sala *atual) {
    char escolha;

    // Enquanto houver uma sala para explorar
    while (atual != NULL) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        // Caso a sala seja um nó-folha (sem saídas)
        if (atual->esq == NULL && atual->dir == NULL) {
            printf("Você chegou ao fim! Não há mais caminhos a seguir.\n");
            break;
        }

        // Exibe opções disponíveis
        printf("Escolha seu caminho:\n");
        if (atual->esq != NULL)
            printf("  (e) Ir para a esquerda (%s)\n", atual->esq->nome);
        if (atual->dir != NULL)
            printf("  (d) Ir para a direita (%s)\n", atual->dir->nome);
        printf("  (s) Sair do jogo\n");

        // Lê a escolha do jogador
        printf(">>> ");
        scanf(" %c", &escolha);

        // Verifica a escolha
        if (escolha == 'e' || escolha == 'E') {
            if (atual->esq != NULL) {
                atual = atual->esq; // Move para a esquerda
            } else {
                printf("Não há caminho à esquerda!\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            if (atual->dir != NULL) {
                atual = atual->dir; // Move para a direita
            } else {
                printf("Não há caminho à direita!\n");
            }
        } else if (escolha == 's' || escolha == 'S') {
            printf("\nVocê decidiu encerrar a exploração. Até a próxima, detetive!\n");
            break;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

//-----------------------------------------
// Função: liberarSalas
// Libera toda a memória alocada pela árvore
//-----------------------------------------
void liberarSalas(Sala *raiz) {
    if (raiz != NULL) {
        liberarSalas(raiz->esq);
        liberarSalas(raiz->dir);
        free(raiz);
    }
}

//-----------------------------------------
// Função principal (main)
// Monta o mapa da mansão e inicia o jogo
//-----------------------------------------
int main() {
    // Criação das salas (nós da árvore)
    Sala *hall = criarSala("Hall de Entrada");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *jardim = criarSala("Jardim");
    Sala *porao = criarSala("Porão Misterioso");
    Sala *laboratorio = criarSala("Laboratório Secreto");

    // Conexões (montagem da árvore)
    hall->esq = biblioteca;
    hall->dir = salaEstar;
    biblioteca->esq = cozinha;
    biblioteca->dir = jardim;
    salaEstar->esq = porao;
    salaEstar->dir = laboratorio;

    // Introdução
    printf("========================================\n");
    printf("      🕵️‍♂️  DETECTIVE QUEST - MANSÃO ENIGMA\n");
    printf("========================================\n");
    printf("Você está prestes a explorar a misteriosa mansão.\n");
    printf("Comece sua investigação a partir do Hall de Entrada.\n");

    // Inicia a exploração
    explorarSalas(hall);

    // Libera a memória
    liberarSalas(hall);

    return 0;
}
