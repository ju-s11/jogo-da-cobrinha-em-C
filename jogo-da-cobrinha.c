#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#define TAMANHO_COBRINHA 1000  //tamanho máximo do personagem
#define LARGURA 40
#define ALTURA 20

void main() {
    initscr(); //inicializando a janela de ncurses
    noecho();  //para não mostrar teclas pressionadas
    curs_set(FALSE); //para não mostrar cursor

    WINDOW *janela = newwin(ALTURA, LARGURA, 0, 0); //cria nova janela com tamanho específico
    keypad(janela, true); //habilitando o teclado
    nodelay(janela, true); //para não esperar por input para a abertura da janela
    box(janela, 0, 0); //desenhando a borda da janela

    //definindo a posição do personagem na janela
    int posX = 0;
    int posY = 0;

    /*
    int posX = WIDTH / 2;
    int posY = HEIGHT / 2;
    */

    //definindo a posição da comida na janela, usando valores aleatórios
    int comidaX = rand() % 20;
    int comidaY = rand() % 20;
    /*
    int comidaX = rand() % (WIDTH - 2) + 1;
    int comidaY = rand() % (HEIGHT - 2) + 1;
    */

    //definindo a direção inicial do personagem
    int dirX = 1;
    int dirY = 0;

    //definindo o corpo da cobrinha e sua posição
    int cobrinhaX[TAMANHO_COBRINHA];
    int cobrinhaY[TAMANHO_COBRINHA];
    int tamanho = 1;

    cobrinhaX[0] = posX;
    cobrinhaY[0] = posY;

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

        //verifica se houve colisão com a borda da janela
        if (posX <= 0 || posX >= LARGURA - 1 || posY <= 0 || posY >= ALTURA - 1) {
            break; //perde o jogo! :(
        }

        //movendo o corpo da cobrinha
        for (int i = tamanho; i > 0; i--) {
            cobrinhaX[i] = cobrinhaX[i - 1];
            cobrinhaY[i] = cobrinhaY[i - 1];
        }
        cobrinhaX[0] = posX;
        cobrinhaY[0] = posY;

        //lógica da cobrinha comendo as comidas, tamanho da cobrinha aumenta e comida aparece em outro lugar
        if (posX == comidaX && posY == comidaY) {
            tamanho++;
            comidaX = rand() % (LARGURA - 2) + 1;
            comidaY = rand() % (ALTURA - 2) + 1;
        }

        //limpando a tela
        werase(janela);
        box(janela, 0, 0);

        //desenhando a comida na nova posição
        mvwaddch(janela, comidaY, comidaX, '0');

        //desenhando o personagem na nova posição
        for (int i = 0; i < tamanho; i++) {
            mvwaddch(janela, cobrinhaY[i], cobrinhaX[i], '*');
        }

        //atualizando a janela
        wrefresh(janela);

        //pausa para o controle da velocidade do jogo
        usleep(100000);
    }

    endwin(); //finalizando a janela
}
