#ifndef UTIL_H
#define UTIL_H

// Habilita o “raw mode” no terminal (modo cru), desativando edição de linha
// e eco de caracteres, permitindo ler tecla a tecla sem precisar de ENTER.
void util_enable_raw_mode(void);

// Restaura o terminal ao modo original (sai do raw mode), reativando
// edição de linha e eco de caracteres.
void util_disable_raw_mode(void);

// Retorna não-zero se houver alguma tecla pressionada no buffer de entrada,
// sem bloquear a execução. Útil para checar entrada antes de chamar util_getch().
int util_kbhit(void);

// Lê um único caractere do teclado imediatamente (raw mode), retornando
// o código ASCII da tecla ou código especial (setas, etc.).
int util_getch(void);

// Pausa a execução do programa pelo número de milissegundos especificado.
// Internamente, pode usar Sleep() no Windows ou usleep()/nanosleep() em POSIX.
void util_sleep_ms(int ms);

// Carrega o recorde de pontuação (highscore) de um arquivo cujo caminho
// é apontado por `path`. Se o arquivo não existir ou estiver vazio,
// geralmente retorna 0.
int util_load_highscore(const char *path);

// Salva a pontuação `score` no arquivo indicado por `path`, geralmente
// sobrescrevendo o valor antigo ou criando o arquivo se não existir.
void util_save_highscore(const char *path, int score);

#endif // Fim do guarda de inclusão UTIL_H
