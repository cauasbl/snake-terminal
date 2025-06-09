#ifndef GAME_H // Se GAME_H ainda não foi definido...
#define GAME_H // Define GAME_H para evitar múltiplas inclusões deste cabeçalho

#define WIDTH 40  // Define a largura do campo de jogo como 40 colunas
#define HEIGHT 20 // Define a altura do campo de jogo como 20 linhas

// Protótipos das funções que controlam o ciclo principal do jogo Snake:
// dificuldade: 0=Fácil, 1=Médio, 2=Difícil
void init_game(int difficulty); // Inicializa o jogo com o nível de dificuldade especificado
void update_game(void);         // Atualiza o estado do jogo (movimenta cobra, verifica entradas e colisões)
void render_game(void);         // Desenha o estado atual do jogo na tela
int game_over(void);            // Retorna não-zero se o jogo terminou, zero caso contrário
void cleanup_game(void);        // Executa rotina de fim de jogo (salva pontuação, exibe tela de Game Over)

#endif // Fim do guarda de inclusão GAME_H
