# Jogo de Xadrez no Terminal

Este é um jogo simples de xadrez implementado em C usando a biblioteca **ncurses** para interface no terminal.

### Requisitos

- GCC (ou outro compilador C)
- Biblioteca **ncurses** instalada

### Como Rodar

1. **Compilação**:
   Para compilar o código, utilize o seguinte comando:

   ```bash
   gcc xadrez.c -lncurses -o xadrez
   ```

2. **Execução**:
   Após compilar, execute o jogo com o seguinte comando:

   ```bash
   ./xadrez
   ```

### Instruções

- **Setas direcionais**: Mover o cursor pelo tabuleiro.
- **ENTER**: Selecionar uma peça ou mover a peça selecionada para a posição atual do cursor.
- **q**: Sair do jogo.

### Regras

Este jogo implementa as regras básicas de movimentação das peças de xadrez, mas não valida todas as regras do jogo (como o xeque e xeque-mate). A movimentação das peças é feita de forma simples, com base na posição atual do cursor.

### Personalizações

Este código pode ser expandido para adicionar mais funcionalidades, como validações de movimentos, regras completas de xadrez, interface gráfica mais avançada, entre outros.
