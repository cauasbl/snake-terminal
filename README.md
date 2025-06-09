# 🐍 Snake Terminal Game

Um jogo da cobrinha (Snake) feito em linguagem C, jogável diretamente no terminal do Windows. Esse projeto foi desenvolvido como trabalho acadêmico para a disciplina de Programação Estruturada.

## 🎮 Demonstração

![snake-gif](https://media.giphy.com/media/xUA7aZeLE2e0P7Znz2/giphy.gif)  
*Imagem ilustrativa. O jogo roda no terminal do Windows, com controle por teclado.*

---

## 🛠️ Como compilar

Este projeto é feito para Windows e pode ser compilado com o GCC (MinGW):

```bash
gcc main.c snake.c game.c util.c -o output/projeto-snake.exe
```

Após compilar, execute o jogo com:
```
output/projeto-snake.exe
```
## 🚀 Como jogar

- Use as teclas **W**, **A**, **S**, **D** para mover a cobrinha.
- Pressione **P** para pausar o jogo.
- Pressione **Q** para sair durante a partida.
- Coma a comida para crescer e aumentar sua pontuação.
- Evite bater nas paredes ou em você mesmo.

## ⚙️ Funcionalidades

- Interface baseada em texto (modo console).
- Escolha de dificuldade: Fácil, Médio, Difícil.
- Sistema de pontuação e high score salvo em arquivo (`output/scores.txt`).
- Menus estilizados com arte ASCII.
- Código modularizado com separação em arquivos `.c` e `.h`.

## 📜 Licença

- Distribuído sob a licença MIT.
- Confira mais detalhes no arquivo LICENSE.

<p align="center"> Desenvolvido por <strong>Cauã Sanches</strong> </p> ```
<p align="center"> GitHub: <strong>@cauasbl</strong> </p> ```

📌 Observações
Este jogo foi desenvolvido e testado para Windows, usando as bibliotecas <conio.h> e <windows.h>.

A pasta output/ já está pronta para uso com os arquivos gerados automaticamente.
