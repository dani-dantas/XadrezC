#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <stdbool.h>

#define TAMANHO_TABULEIRO 8

// Alterar para representar peças com letras
char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
};

int posicao_x = 0, posicao_y = 0;
bool selecionando = false;
int posicao_selecionada_x = -1, posicao_selecionada_y = -1;

void exibir_tutorial() {
    clear();
    mvprintw(5, 10, "Bem-vindo ao Jogo de Xadrez!");
    mvprintw(7, 10, "Use as setas do teclado para mover o cursor.");
    mvprintw(8, 10, "Pressione ENTER para selecionar uma peça.");
    mvprintw(9, 10, "Pressione ENTER novamente para mover a peça.");
    mvprintw(10, 10, "Pressione 'q' para sair do jogo.");
    mvprintw(12, 10, "Você está pronto? Aperte qualquer tecla para começar.");
    refresh();
    getch();
}

void desenhar_tabuleiro(WINDOW *janela) {
    werase(janela);
    box(janela, 0, 0);
    for (int y = 0; y < TAMANHO_TABULEIRO; y++) {
        for (int x = 0; x < TAMANHO_TABULEIRO; x++) {
            // Casas alternadas
            if ((y + x) % 2 == 0) {
                wattron(janela, COLOR_PAIR(1)); // Casa branca
            } else {
                wattron(janela, COLOR_PAIR(2)); // Casa preta
            }

            if (y == posicao_y && x == posicao_x) {
                wattron(janela, A_REVERSE); // Destacar o cursor
            }

            if (selecionando && y == posicao_selecionada_y && x == posicao_selecionada_x) {
                wattron(janela, A_BOLD); // Destacar a peça selecionada
            }

            mvwprintw(janela, y + 1, x * 4 + 2, "%c", tabuleiro[y][x]);
            wattroff(janela, A_REVERSE);
            wattroff(janela, A_BOLD);
            wattroff(janela, COLOR_PAIR(1));
            wattroff(janela, COLOR_PAIR(2));
        }
    }
    wrefresh(janela);
}

void mover_cursor(int dy, int dx) {
    posicao_y = (posicao_y + dy + TAMANHO_TABULEIRO) % TAMANHO_TABULEIRO;
    posicao_x = (posicao_x + dx + TAMANHO_TABULEIRO) % TAMANHO_TABULEIRO;
}

void selecionar_ou_mover() {
    if (!selecionando) {
        if (tabuleiro[posicao_y][posicao_x] != ' ') {
            selecionando = true;
            posicao_selecionada_x = posicao_x;
            posicao_selecionada_y = posicao_y;
        }
    } else {
        tabuleiro[posicao_y][posicao_x] = tabuleiro[posicao_selecionada_y][posicao_selecionada_x];
        tabuleiro[posicao_selecionada_y][posicao_selecionada_x] = ' ';
        selecionando = false;
    }
}

void inicializar_ncurses() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);  // Casa branca
    init_pair(2, COLOR_BLACK, COLOR_YELLOW); // Casa preta
}

void jogar() {
    inicializar_ncurses();
    exibir_tutorial();
    
    WINDOW *janela = newwin(10, 35, 1, 1);
    refresh();

    while (1) {
        desenhar_tabuleiro(janela);
        int tecla = getch();

        switch (tecla) {
            case 'q':
                delwin(janela);
                endwin();
                return;
            case KEY_UP:
                mover_cursor(-1, 0);
                break;
            case KEY_DOWN:
                mover_cursor(1, 0);
                break;
            case KEY_LEFT:
                mover_cursor(0, -1);
                break;
            case KEY_RIGHT:
                mover_cursor(0, 1);
                break;
            case 10:
                selecionar_ou_mover();
                break;
        }
    }
}

int main() {
    jogar();
    return 0;
}
