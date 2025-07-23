# Jogo da cobrinha minimalista em C

## Inspiração

Vídeo "Making Minimalist Snake Game in C on Linux" do canal Nir Lichtman - https://www.youtube.com/watch?v=SFtWBVMdAOA&list=WL&index=82

## Explicação do Projeto

### Biblioteca Curses

É usada a biblioteca *curses.h*, a função *initscr* - WINDOW \*initscr(void); - para a criação da janela e a função *endwin* - int endwin(void); - para restaurar o terminal após o uso da janela.

### Definição do comportamento da janela

É usada a função *keypad* - int keypad(WINDOW \*win, bool bf) - que inicializa o teclado, o parâmetro booleano *bf* é quem define se o teclado foi ou não habilitado. E, também, é usada a função *nodelay* - int nodelay(WINDOW \*win, bool bf) - que faz com que a função *getch* - int getch(void); - não bloqueie a chamada da janela ao esperar por inputs do usuário. Caso *bf = true*, a função *getch* não espera o usuário pressionar uma tecla e se não tiver nenhuma tecla pressionada, a função *getch* irá retornar *ERR* (erro). Caso *bf = false* (comportamento padrão), a função *getch* espera o usuário pressionar uma tecla.

### Definição das posições da cobrinha e das comidas na janela

São definidas as variáveis posX e posY para definir a posição da cobrinha na janela e as variáveis foodX e foodY para definir as posições onde as comidas irão aparecer na janela. 



