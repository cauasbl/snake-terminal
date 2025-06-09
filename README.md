<h1 align="center">
  🐍 Snake Terminal Game
</h1>

<p align="center">
  <i>Um remake do clássico Snake para terminal Windows, feito em C</i><br>
  <img src="https://img.shields.io/badge/linguagem-C-blue.svg">
  <img src="https://img.shields.io/badge/sistema-Windows-lightgrey.svg">
  <img src="https://img.shields.io/badge/license-MIT-green.svg">
</p>

---

## 🎮 Sobre o Projeto

Um remake moderno do clássico jogo da cobrinha (**Snake**) criado para rodar no terminal do **Windows**.  
O jogo é um projeto acadêmico desenvolvido em **C**, utilizando:

- Tipos Abstratos de Dados (**TAD**)
- Manipulação do terminal via **ANSI Escape Codes**
- Leitura direta do teclado para controle em tempo real

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
