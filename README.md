
# 🐍 Snake Terminal Game (Projeto em C)

Um remake clássico do jogo da cobrinha (Snake), desenvolvido totalmente em C para rodar no terminal do Windows.  
Idealizado como projeto acadêmico, o jogo utiliza conceitos de TAD (Tipo Abstrato de Dado), controle de input direto do teclado e manipulação da tela via ANSI escape codes.

---

### 📁 Estrutura do Projeto

projeto-snake1/
│
├── include/ # Arquivos de cabeçalho (.h)
│ ├── snake.h
│ └── util.h
│
├── src/ # Código-fonte principal (.c)
│ ├── main.c
│ ├── snake.c
│ └── util.c
│
├── output/ # Arquivos gerados na execução
│ ├── projeto-snake.exe
│ └── scores.txt
│
├── .gitignore
├── LICENSE
├── Makefile
└── README.md

yaml
Copiar
Editar

---

### 🛠️ Como Compilar

Abra o terminal no diretório do projeto e execute:

```bash
make
Isso irá compilar os arquivos e gerar o executável projeto-snake.exe dentro da pasta output/.

▶️ Como Jogar
Após compilar, execute o jogo com:

bash
Copiar
Editar
output/projeto-snake.exe
Controles:
W - Cima

A - Esquerda

S - Baixo

D - Direita

ESC - Sair do jogo

🧠 Funcionalidades
Modo terminal simples e leve

Sistema de pontuação com salvamento automático (scores.txt)

Detecção de colisões (paredes e corpo da cobra)

Código modular com TAD Snake

Interface minimalista com ANSI escape codes

🧾 Licença
Este projeto está licenciado sob os termos da MIT License.

🙋‍♂️ Autor
Desenvolvido por Cauã Sanches

GitHub: @cauasbl

📌 Observações
Este jogo foi desenvolvido e testado para Windows, usando as bibliotecas <conio.h> e <windows.h>.

A pasta output/ já está pronta para uso com os arquivos gerados automaticamente.

>>>>>>> 89ecab1 (Adiciona .gitignore, LICENSE, Makefile e atualiza README.md)
