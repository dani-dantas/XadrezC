#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <stdbool.h>

#define TAMANHO_TABULEIRO 8

wchar_t tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {
    {L'♖', L'♘', L'♗', L'♕', L'♔', L'♗', L'♘', L'♖'},
    {L'♙', L'♙', L'♙', L'♙', L'♙', L'♙', L'♙', L'♙'},
    {L' ', L' ', L' ', L' ', L' ', L' ', L' ', L' '},
    {L' ', L' ', L' ', L' ', L' ', L' ', L' ', L' '},
    {L' ', L' ', L' ', L' ', L' ', L' ', L' ', L' '},
    {L' ', L' ', L' ', L' ', L' ', L' ', L' ', L' '},
    {L'♟', L'♟', L'♟', L'♟', L'♟', L'♟', L'♟', L'♟'},
    {L'♜', L'♞', L'♝', L'♛', L'♚', L'♝', L'♞', L'♜'}
};

int cursor_x = 0, cursor_y = 0;
bool selecionando = false;
int selecionado_x = -1, selecionado_y = -1;

void exibir_tutorial() {
    clear();
    mvprintw(5, 10, "Bem-vindo ao Jogo de Xadrez!");
    mvprintw(7, 10, "Use as setas do teclado para mover o cursor.");
    mvprintw(8, 10, "Pressione ENTER para selecionar uma peca.");
    mvprintw(9, 10, "Pressione ENTER novamente para mover a peca.");
    mvprintw(10, 10, "Pressione 'q' para sair do jogo.");
    mvprintw(12, 10, "Voce esta pronto? Aperte qualquer tecla para comecar.");
    refresh();
    getch();
}

void desenhar_tabuleiro(WINDOW *janela) {
    werase(janela);
    box(janela, 0, 0);
    for (int y = 0; y < TAMANHO_TABULEIRO; y++) {
        for (int x = 0; x < TAMANHO_TABULEIRO; x++) {
            if ((y + x) % 2 == 0) {
                wattron(janela, COLOR_PAIR(1));
            } else {
                wattron(janela, COLOR_PAIR(2));
            }
            if (y == cursor_y && x == cursor_x) {
                wattron(janela, A_REVERSE);
            }
            if (selecionando && y == selecionado_y && x == selecionado_x) {
                wattron(janela, A_BOLD);
            }
            mvwprintw(janela, y + 1, x * 4 + 2, "%lc", tabuleiro[y][x]);
            wattroff(janela, A_REVERSE);
            wattroff(janela, A_BOLD);
            wattroff(janela, COLOR_PAIR(1));
            wattroff(janela, COLOR_PAIR(2));
        }
    }
    wrefresh(janela);
}

void mover_cursor(int dy, int dx) {
    cursor_y = (cursor_y + dy + TAMANHO_TABULEIRO) % TAMANHO_TABULEIRO;
    cursor_x = (cursor_x + dx + TAMANHO_TABULEIRO) % TAMANHO_TABULEIRO;
}

void selecionar_ou_mover() {
    if (!selecionando) {
        if (tabuleiro[cursor_y][cursor_x] != L' ') {
            selecionando = true;
            selecionado_x = cursor_x;
            selecionado_y = cursor_y;
        }
    } else {
        tabuleiro[cursor_y][cursor_x] = tabuleiro[selecionado_y][selecionado_x];
        tabuleiro[selecionado_y][selecionado_x] = L' ';
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
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
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
