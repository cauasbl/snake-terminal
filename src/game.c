#include <windows.h> // Importa funções da API do Windows para manipular console (cores, cursor, etc.)
#include <stdio.h>   // Importa funções padrão de entrada/saída, como printf, sprintf, putchar
#include <stdlib.h>  // Importa funções utilitárias como malloc, free, rand, srand
#include <string.h>  // Importa funções de manipulação de strings, como strlen, strcpy
#include <time.h>    // Importa funções de tempo, como time para semente de rand

#include "util.h"  // Cabeçalho próprio: declara util_kbhit, util_getch, util_sleep_ms, etc.
#include "game.h"  // Cabeçalho próprio: declara init_game, update_game, render_game, cleanup_game
#include "snake.h" // Cabeçalho próprio: declara estruturas e funções da cobra

#define TL '\xC9' // Caractere CP437 para canto superior esquerdo de caixa (╔)
#define TR '\xBB' // Caractere CP437 para canto superior direito de caixa (╗)
#define BL '\xC8' // Caractere CP437 para canto inferior esquerdo de caixa (╚)
#define BR '\xBC' // Caractere CP437 para canto inferior direito de caixa (╝)
#define HR '\xCD' // Caractere CP437 para linha horizontal de caixa (═)
#define VT '\xBA' // Caractere CP437 para linha vertical de caixa (║)

// Elementos visuais do jogo
#define CHAR_BORDER '\xDB' // Caractere CP437 para borda do campo (█)
#define CHAR_SNAKE '\xDB'  // Caractere CP437 para representar cada segmento da cobra (█)
#define CHAR_FOOD '\xB2'   // Caractere CP437 para representar a comida (▒)

static HANDLE hCon;   // Handle do console para chamar funções da API do Windows
static WORD origAttr, // Guarda os atributos originais de cor do console
    brdAttr,          // Atributo de cor para a borda do campo
    snkAttr,          // Atributo de cor para a cobra
    fodAttr;          // Atributo de cor para a comida
static int CW, CH;    // Dimensões do console: CW = largura em colunas, CH = altura em linhas

static Snake snake;        // Estrutura que representa a cobra (lista ligada de segmentos)
static int food_x, food_y; // Coordenadas atuais da comida
static int score,          // Pontuação atual
    highscore;             // Recorde lido de arquivo
static int over,           // Flag que indica fim de jogo (1 = game over)
    speed_ms;              // Velocidade do jogo (milissegundos de delay entre frames)

// Função interna: limpa toda a tela sem causar flicker
static void clear_screen(void)
{
  DWORD written;      // Recebe número de caracteres escritos
  COORD top = {0, 0}; // Coordenada (0,0) no canto superior esquerdo
  // Preenche com espaço ' ' por CW*CH células
  FillConsoleOutputCharacterA(hCon, ' ', CW * CH, top, &written);
  // Restaura atributos de cor originais em todo o buffer
  FillConsoleOutputAttribute(hCon, origAttr, CW * CH, top, &written);
  // Move o cursor de volta para o topo
  SetConsoleCursorPosition(hCon, top);
}

// Função interna: configura cores, cursor invisível e obtém tamanho do console
static void setup_console(void)
{
  hCon = GetStdHandle(STD_OUTPUT_HANDLE);  // Obtém handle padrão do console
  CONSOLE_SCREEN_BUFFER_INFO csbi;         // Estrutura para receber info do console
  GetConsoleScreenBufferInfo(hCon, &csbi); // Preenche csbi com info atual
  origAttr = csbi.wAttributes;             // Salva cor original
  CW = csbi.dwSize.X;                      // Define CW como largura em caracteres
  CH = csbi.dwSize.Y;                      // Define CH como altura em linhas

  // Define cores: borda em branco intenso, cobra em verde, comida em vermelho
  brdAttr = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
  snkAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
  fodAttr = FOREGROUND_RED | FOREGROUND_INTENSITY;

  // Configura cursor invisível
  CONSOLE_CURSOR_INFO ci;
  GetConsoleCursorInfo(hCon, &ci);
  ci.bVisible = FALSE;
  SetConsoleCursorInfo(hCon, &ci);
}

// Função interna: redesenha o buffer 2D passado, centralizado no console
static void draw_frame(char buf[HEIGHT][WIDTH])
{
  int padX = (CW - (WIDTH + 2)) / 2; // Calcula margem horizontal para centralizar
  int padY = 1;                      // Margem vertical fixa (uma linha abaixo do topo)

  // Desenha borda superior
  SetConsoleCursorPosition(hCon, (COORD){(SHORT)padX, (SHORT)padY});
  SetConsoleTextAttribute(hCon, brdAttr); // Ajusta cor para borda
  for (int i = 0; i < WIDTH + 2; i++)
    putchar(CHAR_BORDER); // Caractere de borda
  putchar('\n');          // Nova linha

  // Desenha cada linha interna: borda + conteúdo + borda
  for (int y = 0; y < HEIGHT; y++)
  {
    // Posiciona cursor no início da linha y
    SetConsoleCursorPosition(hCon, (COORD){(SHORT)padX, (SHORT)(padY + 1 + y)});
    SetConsoleTextAttribute(hCon, brdAttr);
    putchar(CHAR_BORDER); // Borda esquerda

    // Cada coluna x da área de jogo
    for (int x = 0; x < WIDTH; x++)
    {
      char c = buf[y][x]; // Caractere a ser desenhado: espaço, cobra ou comida
      if (c == CHAR_SNAKE)
        SetConsoleTextAttribute(hCon, snkAttr); // Cor da cobra
      else if (c == CHAR_FOOD)
        SetConsoleTextAttribute(hCon, fodAttr); // Cor da comida
      else
        SetConsoleTextAttribute(hCon, origAttr); // Cor padrão
      putchar(c);                                // Desenha caractere
    }

    SetConsoleTextAttribute(hCon, brdAttr);
    putchar(CHAR_BORDER); // Borda direita
  }

  // Desenha borda inferior
  SetConsoleCursorPosition(hCon, (COORD){(SHORT)padX, (SHORT)(padY + 1 + HEIGHT)});
  SetConsoleTextAttribute(hCon, brdAttr);
  for (int i = 0; i < WIDTH + 2; i++)
    putchar(CHAR_BORDER);

  // Exibe placar abaixo do quadro
  SetConsoleCursorPosition(hCon, (COORD){(SHORT)padX, (SHORT)(padY + 2 + HEIGHT)});
  SetConsoleTextAttribute(hCon, origAttr);
  printf(" SCORE:%03d  HIGH:%03d", score, highscore);

  // Pausa o loop pelo valor speed_ms para controlar velocidade
  util_sleep_ms(speed_ms);
}

// Inicializa o jogo com a dificuldade escolhida
void init_game(int difficulty)
{
  setup_console();                               // Configura console (cores, cursor, tamanho)
  clear_screen();                                // Limpa a tela antes de começar
  srand((unsigned)time(NULL));                   // Semente aleatória para rand()
  highscore = util_load_highscore("scores.txt"); // Carrega recorde de arquivo
  score = 0;
  over = 0; // Zera pontuação e flag de game over
  // Define velocidade: 120 ms fácil, 80 ms médio, 50 ms difícil
  speed_ms = (difficulty == 0 ? 120 : (difficulty == 1 ? 80 : 50));
  snake_init(&snake, WIDTH / 2, HEIGHT / 2); // Cria cobra no centro
  food_x = rand() % WIDTH;                   // Posiciona comida em X aleatório
  food_y = rand() % HEIGHT;                  // Posiciona comida em Y aleatório
}

// Atualiza estado do jogo: entradas, movimento, colisões e comida
void update_game(void)
{
  if (util_kbhit()) // Se alguma tecla foi pressionada
  {
    int c = util_getch(); // Lê o código da tecla
    if (c == 'q')         // 'q' para sair
      over = 1;
    else if (c == 'p') // 'p' para pausar até pressionar 'p' de novo
      while (util_getch() != 'p')
        ;
    else if (c == 'w' && snake.dir != 2)
      snake.dir = 0; // Cima (não oposto)
    else if (c == 'd' && snake.dir != 3)
      snake.dir = 1; // Direita
    else if (c == 's' && snake.dir != 0)
      snake.dir = 2; // Baixo
    else if (c == 'a' && snake.dir != 1)
      snake.dir = 3; // Esquerda
  }

  int ate = snake_move(&snake, food_x, food_y); // Move cobra e verifica se comeu
  if (ate)
  {
    score++;               // Incrementa pontuação
    if (score > highscore) // Atualiza recorde
      highscore = score;
    if (score % 5 == 0 && speed_ms > 20) // Aumenta velocidade a cada 5 pontos
      speed_ms -= 5;
    // Gera nova posição de comida aleatória
    food_x = rand() % WIDTH;
    food_y = rand() % HEIGHT;
  }

  // Verifica colisão com paredes (fora dos limites)
  if (snake.head->x < 0 || snake.head->x >= WIDTH ||
      snake.head->y < 0 || snake.head->y >= HEIGHT)
    over = 1;
  // Verifica colisão da cabeça com o próprio corpo
  if (snake_self_collision(&snake))
    over = 1;
}

// Prepara buffer com espaços, comida e cobra, e chama draw_frame
void render_game(void)
{
  static char buf[HEIGHT][WIDTH]; // Buffer temporário 2D
  // Preenche todo o buffer com espaço
  for (int y = 0; y < HEIGHT; y++)
    for (int x = 0; x < WIDTH; x++)
      buf[y][x] = ' ';
  buf[food_y][food_x] = CHAR_FOOD; // Marca comida no buffer
  // Marca cada segmento da cobra
  for (Segment *s = snake.head; s; s = s->next)
    if (s->x >= 0 && s->x < WIDTH && s->y >= 0 && s->y < HEIGHT)
      buf[s->y][s->x] = CHAR_SNAKE;
  draw_frame(buf); // Desenha o buffer na tela
}

// Retorna 1 se o jogo terminou, 0 caso contrário
int game_over(void)
{
  return over;
}

// Rotina de final de jogo: libera cobra, salva recorde, e exibe tela de Game Over
void cleanup_game(void)
{
  snake_free(&snake);                           // Libera memória alocada para cobra
  util_save_highscore("scores.txt", highscore); // Salva recorde em arquivo

  clear_screen(); // Limpa a tela para mostrar Game Over

  // Prepara texto do Game Over e das pontuações
  char title[] = "*** GAME OVER ***";
  char L1[32], L2[32];
  sprintf(L1, "SCORE     : %03d", score);     // Formata pontuação atual
  sprintf(L2, "HIGHSCORE : %03d", highscore); // Formata recorde

  // Calcula largura da caixa com base na string mais longa
  size_t w = strlen(title), l1 = strlen(L1), l2 = strlen(L2);
  if (l1 > w)
    w = l1;
  if (l2 > w)
    w = l2;

  int padX = (CW - (int)(w + 2)) / 2; // Centraliza horizontalmente
  int padY = 2;                       // Espaço vertical antes da caixa

  // Pula linhas para ajustar verticalmente
  for (int i = 0; i < padY; i++)
    putchar('\n');

  // Desenha topo da caixa
  printf("%*s%c", padX, "", TL);
  for (size_t i = 0; i < w; i++)
    putchar(HR);
  putchar(TR);
  putchar('\n');

  // Desenha título e linhas de pontuação dentro da caixa
  printf("%*s%c%s%*s%c\n", padX, "", VT, title, (int)(w - strlen(title)), "", VT);
  printf("%*s%c%s%*s%c\n", padX, "", VT, L1, (int)(w - strlen(L1)), "", VT);
  printf("%*s%c%s%*s%c\n", padX, "", VT, L2, (int)(w - strlen(L2)), "", VT);

  // Desenha base da caixa
  printf("%*s%c", padX, "", BL);
  for (size_t i = 0; i < w; i++)
    putchar(HR);
  putchar(BR);
  putchar('\n');

  // Mensagem de retorno
  printf("%*sPress ENTER to return\n", padX, "");
  // Aguarda ENTER para prosseguir
  while (util_getch() != '\r')
    ;

  clear_screen(); // Limpa tela antes de voltar ao menu
}
