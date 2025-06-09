#include <stdlib.h> // Declara funções de alocação e liberação de memória (malloc, free)
#include <stdio.h>  // Declara funções de entrada/saída (printf)
#include "snake.h"  // Declara a estrutura Snake, Segment e protótipos

// Inicializa a cobra com um único segmento na posição (start_x, start_y)
void snake_init(Snake *snake, int start_x, int start_y)
{
    Segment *seg = malloc(sizeof(Segment)); // Aloca memória para um novo segmento
    seg->x = start_x;                       // Define a coluna inicial da cabeça
    seg->y = start_y;                       // Define a linha inicial da cabeça
    seg->next = NULL;                       // Ainda não há próximo segmento
    snake->head = snake->tail = seg;        // Cabeça e cauda apontam para este único segmento
    snake->length = 1;                      // Comprimento inicial da cobra é 1
    snake->dir = 1;                         // Direção inicial: 1 = direita
}

// Move a cobra de acordo com snake->dir e retorna 1 se comeu a comida, 0 caso contrário
int snake_move(Snake *snake, int food_x, int food_y)
{
    int nx = snake->head->x; // Começa com a coluna atual da cabeça
    int ny = snake->head->y; // Começa com a linha atual da cabeça
    switch (snake->dir)
    { // Ajusta nx/ny conforme a direção
    case 0:
        ny--;
        break; // 0 = cima (linha -1)
    case 1:
        nx++;
        break; // 1 = direita (coluna +1)
    case 2:
        ny++;
        break; // 2 = baixo (linha +1)
    case 3:
        nx--;
        break; // 3 = esquerda (coluna -1)
    }
    // Cria novo segmento para a nova cabeça
    Segment *new_head = malloc(sizeof(Segment));
    new_head->x = nx;             // Define coluna da nova cabeça
    new_head->y = ny;             // Define linha da nova cabeça
    new_head->next = snake->head; // Aponta next da nova cabeça para a antiga cabeça
    snake->head = new_head;       // Atualiza head para este novo segmento
    snake->length++;              // Incrementa comprimento da cobra

    int ate = (nx == food_x && ny == food_y); // Verifica se a nova cabeça está na comida
    if (!ate)
    { // Se não comeu
        // Remove o segmento da cauda para manter o mesmo comprimento
        Segment *cur = snake->head; // Começa no novo head
        // Avança até o penúltimo segmento (antes da cauda)
        while (cur->next != snake->tail)
            cur = cur->next;
        free(snake->tail);        // Libera a memória da antiga cauda
        snake->tail = cur;        // Atualiza tail para o penúltimo segmento
        snake->tail->next = NULL; // Novo tail não aponta para nada
        snake->length--;          // Decrementa comprimento para compensar
    }
    return ate; // Retorna 1 se comeu, 0 caso contrário
}

// Verifica se a cabeça colidiu com qualquer outro segmento do próprio corpo
int snake_self_collision(const Snake *snake)
{
    Segment *h = snake->head; // Ponteiro para o segmento da cabeça
    Segment *cur = h->next;   // Começa a verificar do segundo segmento em diante
    while (cur)
    {                                         // Para cada segmento no corpo
        if (cur->x == h->x && cur->y == h->y) // Se coordenadas coincidem com a cabeça
            return 1;                         // Colisão detectada
        cur = cur->next;                      // Avança para o próximo segmento
    }
    return 0; // Sem colisão
}

// Desenha a cobra no terminal usando sequências ANSI de posicionamento
void snake_draw(const Snake *snake)
{
    Segment *cur = snake->head; // Começa na cabeça
    while (cur)
    { // Itera por todos os segmentos
        // Move o cursor para a linha (cur->y+1), coluna (cur->x+1)
        // \033[%d;%dH = ESC[linha;colunaH
        printf("\033[%d;%dH#", cur->y + 1, cur->x + 1);
        cur = cur->next; // Passa para o próximo segmento
    }
}

// Libera toda a memória alocada para os segmentos da cobra
void snake_free(Snake *snake)
{
    Segment *cur = snake->head; // Começa na cabeça
    while (cur)
    {                              // Enquanto houver segmento
        Segment *next = cur->next; // Armazena ponteiro para o próximo
        free(cur);                 // Libera o segmento atual
        cur = next;                // Avança para o próximo
    }
    snake->head = snake->tail = NULL; // Limpa ponteiros na struct Snake
}
