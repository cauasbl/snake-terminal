# 🐍 Snake Terminal Game

Um jogo da cobrinha (Snake) feito em linguagem C, jogável diretamente no terminal do Windows. Esse projeto foi desenvolvido como trabalho acadêmico para a disciplina de Programação Estruturada.

## 🎮 Demonstração

![snake-gif](https://media.giphy.com/media/xUA7aZeLE2e0P7Znz2/giphy.gif)  
*Imagem ilustrativa. O jogo roda no terminal do Windows, com controle por teclado.*

---

## 📁 Estrutura do Projeto


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

### 🛠️ Como Compilar

Abra o terminal no diretório do projeto e execute:

```bash
make
Isso irá compilar os arquivos e gerar o executável projeto-snake.exe dentro da pasta output/.
```

▶️ Como Jogar
Após compilar, execute o jogo com:

```
bash
Copiar
Editar
output/projeto-snake.exe

```

Controles:
W - Cima

A - Esquerda

S - Baixo

D - Direita

P - Pausar o jogo

Q - Sair do jogo

✨ Funcionalidades
✅ Interface leve e responsiva via terminal
✅ Pontuação com salvamento automático em scores.txt
✅ Detecção de colisões (paredes e corpo da cobra)
✅ Código modular usando TAD Snake

📜 Licença
Distribuído sob a licença MIT.
Confira mais detalhes no arquivo LICENSE.

<p align="center"> Desenvolvido com ❤️ por <strong>Cauã Sanches</strong> </p> ```

GitHub: @cauasbl

📌 Observações
Este jogo foi desenvolvido e testado para Windows, usando as bibliotecas <conio.h> e <windows.h>.

A pasta output/ já está pronta para uso com os arquivos gerados automaticamente.
