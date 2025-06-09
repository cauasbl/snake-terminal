#include <windows.h> // Inclui a API do Windows para controle avançado do console (cores, cursor, etc.)
#include <conio.h>   // Inclui funções de console, especialmente _getch() e _kbhit() para leitura de teclas sem bloqueio
#include <stdio.h>   // Inclui funções padrão de entrada/saída (printf, snprintf, putchar)
#include <string.h>  // Inclui funções de manipulação de strings (strlen, memcpy, etc.)

#include "util.h" // Cabeçalho próprio com utilidades (sleep, kbhit, getch, highscore)
#include "game.h" // Cabeçalho próprio que declara init_game, update_game, render_game, cleanup_game

#define TL '\xC9' // ╔ canto superior esquerdo de caixa
#define TR '\xBB' // ╗ canto superior direito de caixa
#define BL '\xC8' // ╚ canto inferior esquerdo de caixa
#define BR '\xBC' // ╝ canto inferior direito de caixa
#define HR '\xCD' // ═ linha horizontal de caixa
#define VT '\xBA' // ║ linha vertical de caixa

static HANDLE hCon;   // Handle para o console atual (usado nas chamadas da API Windows)
static WORD origAttr; // Armazena atributos originais de cor do texto
static int CW, CH;    // Largura (CW) e altura (CH) do console em caracteres

// Limpa toda a tela sem piscar, usando a API do Windows
static void clear_screen(void)
{
  DWORD written;      // Recebe quantos caracteres foram processados
  COORD top = {0, 0}; // Coordenada inicial (linha 0, coluna 0)
  // Preenche CW*CH células com espaço ' '
  FillConsoleOutputCharacterA(hCon, ' ', CW * CH, top, &written);
  // Restaura o atributo de cor original em CW*CH células
  FillConsoleOutputAttribute(hCon, origAttr, CW * CH, top, &written);
  // Move o cursor de volta para a posição (0,0)
  SetConsoleCursorPosition(hCon, top);
}

// Retorna o tamanho da maior string em arr[0..n-1]
static int max_strlen(const char *arr[], int n)
{
  int m = 0; // Guarda o comprimento máximo encontrado
  for (int i = 0; i < n; i++)
  {
    int L = (int)strlen(arr[i]); // Comprimento da string atual
    if (L > m)
      m = L; // Atualiza se for maior que m
  }
  return m; // Retorna o maior comprimento
}

// Desenha uma caixa centralizada contendo n linhas de texto
static void drawBox(const char *lines[], int n, int padY)
{
  int w = max_strlen(lines, n);           // Largura interna da caixa (sem margens)
  int padX = (CW - (w + 2)) / 2;          // Espaço à esquerda para centralizar
  COORD pos = {(SHORT)padX, (SHORT)padY}; // Posição inicial de desenho

  // Desenha a borda superior: TL + HR*w + TR
  SetConsoleCursorPosition(hCon, pos);
  putchar(TL);
  for (int i = 0; i < w; i++)
    putchar(HR);
  putchar(TR);

  // Desenha cada linha: VT + texto + preenchimento + VT
  for (int i = 0; i < n; i++)
  {
    pos.Y = padY + 1 + i; // Ajusta linha vertical
    SetConsoleCursorPosition(hCon, pos);
    printf("%c%s%*s%c",
           VT,                            // caractere vertical esquerdo
           lines[i],                      // texto da linha
           w - (int)strlen(lines[i]), "", // preenche o restante com espaços
           VT);                           // caractere vertical direito
  }

  // Desenha a borda inferior: BL + HR*w + BR
  pos.Y = padY + 1 + n; // Posição da base da caixa
  SetConsoleCursorPosition(hCon, pos);
  putchar(BL);
  for (int i = 0; i < w; i++)
    putchar(HR);
  putchar(BR);
}

// Exibe um menu de opções e retorna o índice selecionado
static int selectMenu(const char *opts[], int n)
{
  int cur = 0;            // Índice da opção atualmente destacada
  const int titleY = 1,   // Linha onde o título será desenhado
      menuY = titleY + 3; // Linha onde o menu começará

  clear_screen();                         // Limpa tela antes de desenhar
  const char *title[] = {" SNAKE GAME "}; // Título fixo
  drawBox(title, 1, titleY);              // Desenha a caixa do título

  while (1)
  {
    static char buf[16][64]; // Buffer temporário para cada linha do menu
    const char *lines[16];   // Ponteiros para as strings formatadas
    for (int i = 0; i < n; i++)
    {
      // Preenche buf[i] com "> Opcao" ou "  Opcao"
      snprintf(buf[i], sizeof buf[i], "%s%s",
               (i == cur ? "> " : "  "),
               opts[i]);
      lines[i] = buf[i]; // Armazena ponteiro para a linha formatada
    }
    drawBox(lines, n, menuY); // Desenha caixa com as opções

    int c = _getch();       // Lê caractere (espera até ter tecla)
    if (c == 0 || c == 224) // Códigos especiais (setas)
    {
      int a = _getch(); // Lê código da seta
      if (a == 72 && cur > 0)
        cur--; // Seta cima: decrementa índice se possível
      else if (a == 80 && cur < n - 1)
        cur++; // Seta baixo: incrementa índice
    }
    else if (c == '\r') // Enter confirma seleção
    {
      return cur; // Retorna índice da opção escolhida
    }
  }
}

int main(void)
{
  // Inicialização do console para capturar tamanho e desativar cursor
  hCon = GetStdHandle(STD_OUTPUT_HANDLE);  // Obtém handle do console
  CONSOLE_SCREEN_BUFFER_INFO csbi;         // Estrutura para info do console
  GetConsoleScreenBufferInfo(hCon, &csbi); // Preenche csbi
  origAttr = csbi.wAttributes;             // Salva cor original
  CW = csbi.dwSize.X;                      // Armazena largura do console
  CH = csbi.dwSize.Y;                      // Armazena altura do console
  CONSOLE_CURSOR_INFO ci;                  // Estrutura para info do cursor
  GetConsoleCursorInfo(hCon, &ci);         // Lê status atual do cursor
  ci.bVisible = FALSE;                     // Faz o cursor ficar invisível
  SetConsoleCursorInfo(hCon, &ci);         // Aplica mudança no cursor

  const char *mainOpts[] = {"Play", "Settings", "Exit"}; // Opções do menu principal
  while (1)
  {
    int sel = selectMenu(mainOpts, 3); // Exibe menu e obtém escolha
    if (sel == 0)                      // Se escolheu “Play”
    {
      const char *diffOpts[] = {"Back", "Facil", "Medio", "Dificil"};
      int d = selectMenu(diffOpts, 4) - 1; // Submenu de dificuldade (retorna index-1)
      if (d >= 0)                          // 0=Facil,1=Medio,2=Dificil
      {
        clear_screen();      // Limpa tela antes de iniciar
        init_game(d);        // Chama init_game com dificuldade d
        while (!game_over()) // Enquanto o jogo não tiver acabado
        {
          update_game(); // Atualiza lógica (movimento, colisões)
          render_game(); // Desenha estado atual na tela
        }
        cleanup_game(); // Exibe Game Over e limpa cobra
        clear_screen(); // Limpa para voltar ao menu
      }
    }
    else if (sel == 1) // Se escolheu “Settings”
    {
      const char *settings[] = {
          "Move  : W A S D", // Instruções de movimento
          "Pause : P",       // Instrução de pausa
          "Quit  : Q"        // Instrução para sair
      };
      clear_screen();                                            // Limpa tela
      drawBox(settings, 3, (CH - 5) / 2);                        // Desenha caixa centralizada com instruções
      COORD m = {(SHORT)((CW - 22) / 2), (SHORT)((CH + 5) / 2)}; // Posição do texto abaixo
      SetConsoleCursorPosition(hCon, m);                         // Posiciona cursor para mensagem
      printf("Press ENTER to return");                           // Mensagem de retorno
      while (_getch() != '\r')
        ;             // Aguarda ENTER
      clear_screen(); // Limpa tela antes de voltar
    }
    else // Se escolheu “Exit”
    {
      break; // Sai do loop e termina o programa
    }
  }
  return 0; // Retorna 0 ao sistema (sem erros)
}
