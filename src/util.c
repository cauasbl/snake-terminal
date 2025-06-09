#include "util.h"    // Inclui o cabeçalho que declara as funções utilitárias
#include <stdio.h>   // Inclui funções de E/S em arquivo (fopen, fscanf, fprintf, fclose)
#include <conio.h>   // Inclui _kbhit() e _getch() para leitura de teclado sem bloquear
#include <windows.h> // Inclui Sleep() para pausar a execução em milissegundos

// Nas versões Unix, habilitaríamos o “raw mode” do terminal aqui.
// No Windows, essa função não precisa fazer nada.
void util_enable_raw_mode(void)
{
    // não usado no Windows
}

// Restaura o modo de terminal original (desabilita raw mode).
// No Windows, também não faz nada.
void util_disable_raw_mode(void)
{
    // não usado no Windows
}

// Retorna não-zero se uma tecla estiver disponível no buffer de entrada,
// sem bloquear a execução. Em Windows, _kbhit() faz exatamente isso.
int util_kbhit(void)
{
    return _kbhit();
}

// Lê um caractere do teclado imediatamente (sem eco no terminal).
// Retorna o código ASCII da tecla pressionada.
int util_getch(void)
{
    return _getch();
}

// Pausa a execução do programa por 'ms' milissegundos.
// Em Windows, Sleep() recebe o tempo em milissegundos.
void util_sleep_ms(int ms)
{
    Sleep(ms);
}

// Carrega o recorde de pontuação a partir do arquivo em 'path'.
// Tenta abrir em modo leitura ("r"); se existir, lê um inteiro.
// Se o arquivo não existir, retorna 0.
int util_load_highscore(const char *path)
{
    FILE *f = fopen(path, "r"); // Abre o arquivo para leitura
    int sc = 0;                 // Valor padrão caso o arquivo não exista
    if (f)
    {                         // Se abriu com sucesso
        fscanf(f, "%d", &sc); // Lê um inteiro para sc
        fclose(f);            // Fecha o arquivo
    }
    return sc; // Retorna o score lido (ou 0)
}

// Salva o recorde de pontuação 'score' no arquivo em 'path'.
// Abre em modo escrita ("w"), sobrescrevendo o conteúdo anterior.
void util_save_highscore(const char *path, int score)
{
    FILE *f = fopen(path, "w"); // Abre ou cria o arquivo para escrita
    if (f)
    {                            // Se abriu com sucesso
        fprintf(f, "%d", score); // Escreve o inteiro score no arquivo
        fclose(f);               // Fecha o arquivo
    }
}
