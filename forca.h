#ifndef JOGO_H
#define JOGO_H

#define TAM_MAX 20
#define TAM_USADAS 30

typedef struct {
    char palavra[20];
    char dica[100];
} Palavra_t;

typedef struct {
    char palavraSecreta[TAM_MAX];
    int tamanho;
    int* letrasAcertadas;
    char letrasUsadas[TAM_USADAS];
    int erros;
    int acertos;
} Forca_t;


typedef struct {
    char nome[100];
    int partidas;
    int vitorias;
    int derrotas;
} Estatistica_t;

void desenharForca(int erros);
void iniciarJogo(Forca_t* jogo, const char* palavra);
void liberarJogo(Forca_t* jogo);
void mostrarPalavra(Forca_t* jogo);
int letraJaUsada(Forca_t* jogo, char letra);
void adicionarLetraUsada(Forca_t* jogo, char letra);
void tentarLetra(Forca_t* jogo, char letra);
int jogoGanho(Forca_t* jogo);
int jogoPerdido(Forca_t* jogo);
int jogarFase(Palavra_t fase[], Estatistica_t* stats);
void mostrarEstatisticas(Estatistica_t* stats);
void menu();

#endif
