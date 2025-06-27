#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "forca.h"

int main() {
    srand(time(NULL));
    Estatistica_t stats = {"", 0, 0, 0};  

    Palavra_t fase1[] = {
        {"bronze", "Cor"}, {"verde", "Cor"}, {"amarelo", "Cor"}, {"nude", "Cor"}, {"roxo", "Cor"}
    };
    Palavra_t fase2[] = {
        {"cachorro", "Animal"}, {"gato", "Animal"}, {"elefante", "Animal"}, {"tigre", "Animal"}, {"coelho", "Animal"}
    };
    Palavra_t fase3[] = {
        {"cadeira", "Objeto"}, {"espelho", "Objeto"}, {"garrafa", "Objeto"}, {"mochila", "Objeto"}, {"telefone", "Objeto"}
    };
    Palavra_t fase4[] = {
        {"detetive", "Profissao"}, {"engenheiro", "Profissao"}, {"medico", "Profissao"}, {"mergulhador", "Profissao"}, {"geologo", "Profissao"}
    };
    Palavra_t fase5[] = {
        {"planeta", "Conhecimento geral"}, {"historia", "Conhecimento geral"}, {"cultura", "Conhecimento geral"}, {"natureza", "Conhecimento geral"}, {"energia", "Conhecimento geral"}
    };
    Palavra_t fase6[] = {
        {"cousin", "English word"}, {"stadium", "English word"}, {"difficult", "English word"}, {"language", "English word"}, {"computer", "English word"}
    };

    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        while (getchar() != '\n'); 

        switch(opcao) {
            case 1:
                for (int fase = 1; fase <= 6; fase++) {
                    printf("\nFase %d\n", fase);
                    int perdeu = 0;
                    switch (fase) {
                        case 1: perdeu = jogarFase(fase1, &stats); break;
                        case 2: perdeu = jogarFase(fase2, &stats); break;
                        case 3: perdeu = jogarFase(fase3, &stats); break;
                        case 4: perdeu = jogarFase(fase4, &stats); break;
                        case 5: perdeu = jogarFase(fase5, &stats); break;
                        case 6: perdeu = jogarFase(fase6, &stats); break;
                    }
                    if (perdeu) {
                        printf("Voce perdeu a fase. Voltando ao menu principal.\n");
                        break;
                    }
                    printf("-----------------------------\n");
                }
                break;
            case 2:
                mostrarEstatisticas(&stats);
                break;
            case 3:
                printf("Saindo do jogo.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 3);

    return 0;
}
