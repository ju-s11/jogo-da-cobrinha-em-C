# Jogo da cobrinha minimalista em C

## Inspiração

Vídeo "Making Minimalist Snake Game in C on Linux" do canal Nir Lichtman - https://www.youtube.com/watch?v=SFtWBVMdAOA&list=WL&index=82

Repositório no GitHub - https://github.com/nir9/welcome/tree/master/lnx/minimalist-snake-game

## Instalação das dependências (Ubuntu/WSL)

É necessário instalar a biblioteca *ncurses* para utilizar *curses.h* usada no projeto. Com isso, deve-se usar os comandos:

- sudo apt update: para atualizar a lista de pacotes disponíveis nos repositórios do Ubuntu. Este comando é opcional, apenas para garantir a instalação da versão mais atualizada e válida do que for instalado posteriormente.

- sudo apt install libncurses5-dev libncursesw5-dev: instala os arquivos de desenvolvimento da biblioteca *ncurses*, que é usada para criar interfaces de texto no terminal em C. *libncurses5-dev* instala os headers e libs padrão da quinta versão da *ncurses* e libncursesw5-dev instala a versão wide-character (Unicode) da ncurses, usada para suportar caracteres especiais como acentos e emojis no terminal. Este comando é obrigatório para a compilação e execução do código. 

## Como compilar e executar o programa

# Compilação

gcc <nome do arquivo>.c -o <nome do executável> -lncurses

Exemplo:

gcc jogo-da-cobrinha.c -o cobrinha -lncurses

# Execução

./<nome do executável>

Exemplo:

./cobrinha

## Como jogar 

Após executar o programa, utilize as teclas de setas para movimentar a cobrinha e tente comer as comidas que aparecerem no terminal. Daí em diante será igual ao joguinho da cobrinha padrão. Divirta-se!

## Explicação do Projeto

### Biblioteca Curses

É usada a biblioteca *curses.h*, a função *initscr* - WINDOW \*initscr(void); - para a criação da janela e a função *endwin* - int endwin(void); - para restaurar o terminal após o uso da janela.

### Definição do comportamento da janela

É usada a função *keypad* - int keypad(WINDOW \*win, bool bf) - que inicializa o teclado, o parâmetro booleano *bf* é quem define se o teclado foi ou não habilitado. E, também, é usada a função *nodelay* - int nodelay(WINDOW \*win, bool bf) - que faz com que a função *getch* - int getch(void); - não bloqueie a chamada da janela ao esperar por inputs do usuário. Caso *bf = true*, a função *getch* não espera o usuário pressionar uma tecla e se não tiver nenhuma tecla pressionada, a função *getch* irá retornar *ERR* (erro). Caso *bf = false* (comportamento padrão), a função *getch* espera o usuário pressionar uma tecla.

### Definição das posições da cobrinha e das comidas na janela

São definidas as variáveis posX e posY para definir a posição da cobrinha na janela e as variáveis comidaX e comidaY para definir as posições onde as comidas irão aparecer na janela. 


## Adições feitas por mim

No código original 



