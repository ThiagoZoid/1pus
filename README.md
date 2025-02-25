# Bem-vindo à 1pus!
1pus é uma Engine 2D simples em C. Junto com ela está incluído o projeto de teste "O Mundo de Wumpus",
um jogo onde você precisa roubar o ouro da caverna e não deixar que o temido Wumpus te pegue.

## IDE recomendada
O **Code::Blocks** é a IDE recomendada para compilar esta engine, uma vez que os arquivos já estão
como um projeto do Code::Blocks. Entretanto, se for de sua preferência utilizar outra IDE, aí vão
as instruções:

Na sua IDE, inclua os argumentos no linker: "-lmingw32 -lSDL2main -lSDL2 -lSDL2_image".
Também inclua os seguintes diretórios de pesquisa no linker:
- obj/sdl2/lib
- obj/sdl2_image/lib

Por fim, inclua os seguintes diretórios no compilador:
- obj/sdl2/include/SDL2
- obj/sdl2_image/include/SDL2

Pronto! Deve ser tudo o que é preciso para rodar a engine na sua IDE preferida.

Download do Code::Blocks: http://www.codeblocks.org/downloads

Download do Code::Blocks portátil (não requer instalação nem direitos de administrador): http://codeblocks.codecutter.org/

## Editor de imagens recomendado
O **Paint.NET** é o editor de imagens recomendado para criar sprites pixeladas, no estilo do jogo
exemplo. Lembre-se de criar sprites pixeladas no seu tamanho real e redimensioná-las dentro da engine.

Download do Paint.NET: https://www.getpaint.net/download.html

Download do Paint.NET portátil (não requer instalação nem direitos de administrador): https://www.portablefreeware.com/index.php?id=2904
