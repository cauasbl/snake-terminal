#ifndef SNAKE_H // Se SNAKE_H ainda não foi definido...
#define SNAKE_H // Define SNAKE_H para evitar incluir este cabeçalho mais de uma vez

// Define o segmento individual da cobra, como um nó de lista encadeada
typedef struct Segment
{
    int x, y;             // Coordenadas do segmento no grid de jogo
    struct Segment *next; // Ponteiro para o próximo segmento (NULL se for o rabo)
} Segment;

typedef struct
{
    Segment *head; // Ponteiro para o primeiro segmento (cabeça)
    Segment *tail; // Ponteiro para o último segmento (rabo)
    int length;    // Comprimento atual da cobra (número de segmentos)
    int dir;       // Direção atual: 0=Cima, 1=Direita, 2=Baixo, 3=Esquerda
} Snake;

// Prototipo: inicializa a cobra
// snake: ponteiro para a struct Snake que será configurada
// start_x, start_y: posição inicial da cabeça no centro do campo
void snake_init(Snake *snake, int start_x, int start_y);

// Prototipo: move a cobra na direção 'snake->dir'
// snake: ponteiro para struct Snake
// food_x, food_y: posição da comida
// Retorna 1 se a cabeça alcançar a comida (para o game saber que deve crescer)
int snake_move(Snake *snake, int food_x, int food_y);

// Prototipo: testa colisão da cabeça com qualquer outro segmento
// Retorna !=0 se houver colisão, zero caso contrário
int snake_self_collision(const Snake *snake);

// Prototipo: libera a memória de todos os segmentos da cobra
// Deve ser chamado ao final do jogo para evitar vazamento de memória
void snake_free(Snake *snake);

// Prototipo opcional: desenha cada segmento da cobra no terminal
// Pode ser usado para debugar ou modularizar o render
void snake_draw(const Snake *snake);

#endif // Fim do guarda de inclusão SNAKE_H
