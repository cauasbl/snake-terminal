# 🐍 Snake Terminal Game

Um jogo da cobrinha (Snake) feito em linguagem C, jogável diretamente no terminal do Windows. Esse projeto foi desenvolvido como trabalho acadêmico para a disciplina de Programação Estruturada.

## 🎮 Demonstração

![snake-gif](https://media.giphy.com/media/xUA7aZeLE2e0P7Znz2/giphy.gif)  
*Imagem ilustrativa. O jogo roda no terminal do Windows, com controle por teclado.*

---

🛠️ Como Compilar e Executar (Windows)
✅ Pré-requisitos
Você precisa ter o MinGW instalado, com o compilador gcc funcionando (como já está no seu caso).

Não é necessário instalar bibliotecas adicionais. O jogo usa apenas recursos nativos do Windows (windows.h, conio.h) e a biblioteca padrão do C.

📌 Se quiser usar make, será necessário instalar o make via MSYS2, WSL ou outro ambiente com suporte a Unix-like tools. Mas não é obrigatório.

📦 Compilação manual (recomendada no Windows)
Abra o Prompt de Comando (CMD) na raiz do projeto e digite:
```bash
gcc -I include src\*.c -o output\projeto-snake.exe -Wall -Wextra -O2
```
▶️ Execução
Depois de compilar, rode o jogo com:
```bash
output\projeto-snake.exe
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
