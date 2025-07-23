#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TAMANHO_COBRINHA 1000  //tamanho máximo do personagem
#define LARGURA 40
#define ALTURA 20

void animacao_game_over(WINDOW *janela, int pontuacao) {
    const char *texto = "GAME OVER";
    int len = strlen(texto);

    int linha_animacao = ALTURA / 2;
    int coluna_animacao = (LARGURA - len) / 2;

    //etapa 1: mostrando "game over" letra por letra
    for (int i = 0; i < len; i++) {
        mvwprintw(janela, linha_animacao, coluna_animacao + i, "%c", texto[i]);
        box(janela, 0, 0);
        wrefresh(janela);
        usleep(200000);
    }

    usleep(500000);

    //etapa 2: animação com moldura de estrelinhas
    const char *estrelinhas[] = {
        "  *     *     *  ",
        "*   GAME OVER   *",
        "  *     *     *  "
    };

    const char *vazio[] = {
        "                 ",
        "                 ",
        "                 "
    };

    for (int i = 0; i < 6; i++) {
        const char **frame = (i % 2 == 0) ? estrelinhas : vazio;

        int linha_base = ALTURA / 2 - 1;
        int coluna_base = (LARGURA - strlen(estrelinhas[1])) / 2;

        for (int j = 0; j < 3; j++) {
            mvwprintw(janela, linha_base + j, coluna_base, "%s", frame[j]);
        }

        //mostrando pontuação
        mvwprintw(janela, ALTURA - 3, (LARGURA - 20) / 2, "Pontuação: %d", pontuacao);

        box(janela, 0, 0);
        wrefresh(janela);
        usleep(400000);
    }
}

void main() {
    initscr(); //inicializando a janela de ncurses
    noecho();  //para não mostrar teclas pressionadas
    curs_set(FALSE); //para não mostrar cursor no terminal

    WINDOW *janela = newwin(ALTURA, LARGURA, 0, 0); //cria nova janela com tamanho específico
    keypad(janela, true); //habilitando o teclado
    nodelay(janela, true); //para não esperar por input para a abertura da janela
    box(janela, 0, 0); //desenhando a borda da janela

    //definindo a posição do personagem na janela, cobrinha irá aparecer no meio da janela    
    int posX = LARGURA / 2;
    int posY = ALTURA / 2;
    
    //definindo a posição da comida na janela usando valores aleatórios, mas dentro da janela  
    int comidaX = rand() % (LARGURA - 2) + 1;
    int comidaY = rand() % (LARGURA - 2) + 1;
    
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
            goto game_over; //perde o jogo! :(
        }

        //verifica se houve colisão com corpo da cobrinha
        for (int i = 1; i < tamanho; i++) {
            if (posX == cobrinhaX[i] && posY == cobrinhaY[i]) {
                goto game_over;
            }
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

        //desenhando a janela de novo
        box(janela, 0, 0);

        //desenhando a comida na nova posição
        mvwaddch(janela, comidaY, comidaX, 'O');

        //desenhando o personagem na nova posição
        for (int i = 0; i < tamanho; i++) {
            mvwaddch(janela, cobrinhaY[i], cobrinhaX[i], '*');
        }

        //mostra pontuação do jogador
        mvwprintw(janela, 0, 2, " Pontuação: %d ", tamanho - 1);

        //atualizando a janela
        wrefresh(janela);

        //pausa para o controle da velocidade do jogo
        usleep(100000);
    }

    game_over:
        werase(janela); //limpando a tela
        box(janela, 0, 0); //desenhando a janela
        animacao_game_over(janela, tamanho - 1); //animação de game over
        nodelay(janela, false); //esperando por input para a abertura da janela

        //exibindo na tela a mensagem de game over
        mvwprintw(janela, ALTURA/2 - 1, (LARGURA - 10)/2, "GAME OVER :(");
        mvwprintw(janela, ALTURA/2, (LARGURA - 24)/2, "Pressione 'r' para reiniciar");
        mvwprintw(janela, ALTURA/2 + 1, (LARGURA - 32)/2, "ou qualquer outra tecla para sair");
        wrefresh(janela);

        //caso o usuário pressione a tecla r, o jogo recomeça. caso clique em qualquer outra tecla, o programa para.
        int tecla_fim = wgetch(janela);
        if (tecla_fim == 'r' || tecla_fim == 'R') {
            endwin();
            main();
        }

    endwin(); //finalizando a janela
}
