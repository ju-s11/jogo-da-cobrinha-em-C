#include <curses.h>
#include <stdlib.h>

void main() {
    WINDOW *janela = initscr(); //inicializando a janela
    keypad(janela, true); //habilitando o teclado
    nodelay(janela, true); //para não esperar por input para a abertura da janela

    //definindo a posição do personagem na janela
    int posX = 0;
    int posY = 0;

    //definindo a posição da comida na janela, usando valores aleatórios
    int foodX = rand() % 20;
    int foodY = rand() % 20;

    endwin(); //finalizando a janela
}
