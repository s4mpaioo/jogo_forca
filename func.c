#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h"

void desenharForca(int erros) {
    printf("\n +---+\n");
    printf(" |   %c\n", (erros >= 1) ? 'O' : ' ');
    printf(" |  %c%c%c\n",
           (erros >= 3) ? '/' : ' ',
           (erros >= 2) ? '|' : ' ',
           (erros >= 4) ? '\\' : ' ');
    printf(" |  %c %c\n",
           (erros >= 5) ? '/' : ' ',
           (erros >= 6) ? '\\' : ' ');
    printf(" |\n");
    printf("===\n");
}

void iniciarJogo(Forca_t* jogo, const char* palavra) {
    strcpy(jogo->palavraSecreta, palavra);
    jogo->tamanho = strlen(palavra);
    jogo->letrasAcertadas = (int*) malloc(sizeof(int) * jogo->tamanho);
    jogo->erros = 0;
    jogo->acertos = 0;
    jogo->letrasUsadas[0] = '\0';
    for (int i = 0; i < jogo->tamanho; i++) {
        jogo->letrasAcertadas[i] = 0;
    }
}

void liberarJogo(Forca_t* jogo) {
    free(jogo->letrasAcertadas);
}

void mostrarPalavra(Forca_t* jogo) {
    for (int i = 0; i < jogo->tamanho; i++) {
        if (jogo->letrasAcertadas[i]) {
            printf("%c ", jogo->palavraSecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int letraJaUsada(Forca_t* jogo, char letra) {
    for (int i = 0; jogo->letrasUsadas[i] != '\0'; i++) {
        if (jogo->letrasUsadas[i] == letra) {
            return 1;
        }
    }
    return 0;
}

void adicionarLetraUsada(Forca_t* jogo, char letra) {
    int len = strlen(jogo->letrasUsadas);
    jogo->letrasUsadas[len] = letra;
    jogo->letrasUsadas[len + 1] = '\0';
}

void tentarLetra(Forca_t* jogo, char letra) {
    if (letraJaUsada(jogo, letra)) {
        printf("Esta letra '%c' ja foi usada!\n", letra);
        return;
    }

    adicionarLetraUsada(jogo, letra);
    int acertou = 0;

    for (int i = 0; i < jogo->tamanho; i++) {
        if (jogo->palavraSecreta[i] == letra) {
            if (!jogo->letrasAcertadas[i]) {
                jogo->letrasAcertadas[i] = 1;
                jogo->acertos++;
                acertou = 1;
            }
        }
    }

    if (!acertou) {
        jogo->erros++;
    }
}

int jogoGanho(Forca_t* jogo) {
    return jogo->acertos == jogo->tamanho;
}

int jogoPerdido(Forca_t* jogo) {
    return jogo->erros >= 6;
}

int jogarFase(Palavra_t fase[], Estatistica_t* stats) {
    Forca_t jogo;
    int indice = rand() % 5;
    Palavra_t escolhida = fase[indice];

    printf("\nDica: %s\n", escolhida.dica);
    iniciarJogo(&jogo, escolhida.palavra);
    stats->partidas++;  

    while (!jogoGanho(&jogo) && !jogoPerdido(&jogo)) {
        desenharForca(jogo.erros);
        mostrarPalavra(&jogo);
        printf("Letras usadas: %s\n", jogo.letrasUsadas);
        printf("Digite uma letra: ");

        char buffer[100];
        fgets(buffer, sizeof(buffer), stdin);

        if (buffer[0] == '\n') {
            printf("Entrada invalida! Digite uma letra.\n");
            continue;
        }

        char tentativa = buffer[0];
        tentarLetra(&jogo, tentativa);
    }

    desenharForca(jogo.erros);

    if (jogoGanho(&jogo)) {
        printf("Parabens! Voce acertou: %s\n", jogo.palavraSecreta);
        stats->vitorias++;
        liberarJogo(&jogo);
        return 0;
    } else {
        printf("Game Over! A palavra era: %s\n", jogo.palavraSecreta);
        stats->derrotas++;
        liberarJogo(&jogo);
        return 1;
    }
}

void mostrarEstatisticas(Estatistica_t* stats) {
    printf("\n==== | ESTATISTICAS | ====\n"
           "Fases jogadas: %d\n"
           "Fases vencidas: %d\n"
           "Fases perdidas: %d\n",
           stats->partidas, stats->vitorias, stats->derrotas);
}

void salvarEstatisticas(int partidas, int vitorias, int derrotas) {
    FILE *arquivo = fopen("estatisticas.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "Partidas: %d\n", partidas);
    fprintf(arquivo, "Vitórias: %d\n", vitorias);
    fprintf(arquivo, "Derrotas: %d\n", derrotas);
    fprintf(arquivo, "---------------------------\n");

    fclose(arquivo);
}

void menu() {
    printf("\n==== | JOGO DA FORCA | ====\n");
    printf("Escolha uma opcao\n");
    printf("1 - Iniciar Jogo\n");
    printf("2 - Ver Estatisticas\n");
    printf("3 - Sair\n\n");
}
