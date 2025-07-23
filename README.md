# Jogo da cobrinha minimalista em C

## Inspiração

Vídeo "Making Minimalist Snake Game in C on Linux" do canal Nir Lichtman - https://www.youtube.com/watch?v=SFtWBVMdAOA&list=WL&index=82

Repositório no GitHub - https://github.com/nir9/welcome/tree/master/lnx/minimalist-snake-game

## Instalação das dependências (Ubuntu/WSL)

É necessário instalar a biblioteca *ncurses* para utilizar *curses.h* usada no projeto. Com isso, deve-se usar os comandos:

- sudo apt update: para atualizar a lista de pacotes disponíveis nos repositórios do Ubuntu. Este comando é opcional, apenas para garantir a instalação da versão mais atualizada e válida do que for instalado posteriormente.

- sudo apt install libncurses5-dev libncursesw5-dev: instala os arquivos de desenvolvimento da biblioteca *ncurses*, que é usada para criar interfaces de texto no terminal em C. *libncurses5-dev* instala os headers e libs padrão da quinta versão da *ncurses* e libncursesw5-dev instala a versão wide-character (Unicode) da ncurses, usada para suportar caracteres especiais como acentos e emojis no terminal. Este comando é obrigatório para a compilação e execução do código. 

## Como compilar e executar o programa

### Compilação

gcc <nome do arquivo>.c -o <nome do executável> -lncurses

Exemplo:

gcc jogo-da-cobrinha.c -o cobrinha -lncurses

### Execução

./<nome do executável>

Exemplo:

./cobrinha

## Como jogar 

Após executar o programa, utilize as teclas de setas para movimentar a cobrinha e tente comer as comidas que aparecerem na janela que aparece dentro do seu terminal. Daí em diante será igual ao joguinho da cobrinha padrão. Divirta-se!

## Regras

- A cobrinha não deve entrar em contato com seu próprio corpo. Caso contrário, o jogo acaba.

- A cobrinha não deve encostar nas bordas da janela. Caso contrário, o jogo acaba.

- Quando o jogo acaba quer dizer que a cobrinha morreu.

- Tente comer o máximo de comidas possíveis antes de morrer.

- Cada comida vale um ponto.

- Então, tente obter a maior pontuação possível!

- Jogo não tem vitória, pois mesmo comendo todas as comidas e ocupando a janela inteira com o corpo da cobrinha, ela irá encostar em si mesma e morrer...

## Explicação do Projeto

### Biblioteca Curses

É usada a biblioteca *curses.h*, a função *initscr* - WINDOW \*initscr(void); - para a criação da janela e a função *endwin* - int endwin(void); - para restaurar o terminal após o uso da janela.

### Definição do comportamento da janela

É usada a função *keypad* - int keypad(WINDOW \*win, bool bf) - que inicializa o teclado, o parâmetro booleano *bf* é quem define se o teclado foi ou não habilitado. E, também, é usada a função *nodelay* - int nodelay(WINDOW \*win, bool bf) - que faz com que a função *getch* - int getch(void); - não bloqueie a chamada da janela ao esperar por inputs do usuário. Caso *bf = true*, a função *getch* não espera o usuário pressionar uma tecla e se não tiver nenhuma tecla pressionada, a função *getch* irá retornar *ERR* (erro). Caso *bf = false* (comportamento padrão), a função *getch* espera o usuário pressionar uma tecla.

### Definição das posições da cobrinha e das comidas na janela

São definidas as variáveis posX e posY para definir a posição da cobrinha na janela e as variáveis comidaX e comidaY para definir as posições onde as comidas irão aparecer na janela. 


--------- Explicação incompleta, continuar depois! ---------

## Joguinho original

O jogo original - que pode ser encontrado no link: https://github.com/nir9/welcome/tree/master/lnx/minimalist-snake-game ou no arquivo jogo-dacobrinha-simplificado.c deste repositório - é bem simples, nele podemos apenas mover um '*' (que representa a cobrinha) e comer as comidas que aparecem de maneira semi-aleatória no terminal. O terminal inteiro se torna a área jogável e a cobrinha pode até sair da parte visível pelo usuário do terminal.

--------- colocar vídeo da gameplay do joguinho original ---------


## Adições feitas por mim

No código original, a cobrinha não cresce ao comer a comidas, não há uma demarcação da área do jogo (o terminal inteiro se torna a área jogável), a cobrinha não morre ao bater nas laterais do terminal ou ao sair da parte visível do terminal, não há a exibição da pontuação do jogador e não há tela de GAME OVER. Todos esses features foram adicionados por mim, após assistir e reproduzir o código original. Também, adicionei uma animação de GAME OVER e a opção de recomeçar o jogo ao clicar na tecla 'r' ou 'R', sem precisar executar novamente o programa.

--------- colocar vídeo da gameplay do meu joguinho ---------

## Bugs

- A pontuação que fica na parte superior da tela pode mudar quando a cobrinha anda perto dela, os números se movem ou mudam. Após o primeiro ponto um '0' aparece antes no número da pontuação e se a cobrinha tocar nesse '0' ele vira um ':'. Mas, esse '0' não é contabilizado na pontuação do jogador.

- As comidas podem aparecer embaixo do corpo da cobrinha.

Tentarei ajustar essas coisas depois!

## Adições futuras

- Não a vitória! Caso o jogador coma todas comidas e ocupe todo o espaço da janela, ele ainda morrerá. Mas, idealmente, ele deveria vencer. E, como na tela de "GAME OVER", deve haver uma tela de "VICTORY".