#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

void main() {
    WINDOW *janela = initscr(); //inicializando a janela
    keypad(janela, true); //habilitando o teclado
    nodelay(janela, true); //para não esperar por input para a abertura da janela

    //definindo a posição do personagem na janela
    int posX = 0;
    int posY = 0;

    //definindo a posição da comida na janela, usando valores aleatórios
    int comidaX = rand() % 20;
    int comidaY = rand() % 20;

    //definindo a direção inicial do personagem
    int dirX = 1;
    int dirY = 0;

    while(true) {
        int tecla = wgetch(janela); //capturando a tecla pressionada

        //redefinindo a direção com base na tecla pressionada pelo usuário
        if (tecla == KEY_LEFT) {
            dirX = -1;
            dirY = 0;
        }
        if (tecla == KEY_RIGHT) {
            dirX = 1;
            dirY = 0;
        }
        if (tecla == KEY_UP) {
            dirX = 0;
            dirY = -1;
        }
        if (tecla == KEY_DOWN) {
            dirX = 0;
            dirY = 1;
        }

        posX += dirX;
        posY += dirY;

        //limpando a tela
        erase();

        //desenhando o personagem na nova posição
        mvaddstr(posY, posX, "*"); 
        mvaddstr(comidaY, comidaX, "O");

        //verificando se o personagem saiu da tela
        if (comidaX == posX && comidaY == posY) {
            comidaX = rand() % 20;
            comidaY = rand() % 20;
        }

        //pausa para o controle da velocidade do jogo
        usleep(100000);
    }

    endwin(); //finalizando a janela
}