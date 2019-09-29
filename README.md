# Projeto Final de EA872 K (Laboratório de Programação de Software Básico)

O objetivo desta primeira versão do projeto é desenvolver um jogo de plataforma
no estilo Bomberman no qual um jogador deve ser capaz de
* se mover num mapa composto por blocos de "chão" e de "pilares"
   (instransponíveis)
* spawnar bombas e chutá-las 
* morrer com a explosão da própria bomba

Apesar de não haver nenhum desafio nesta versão, as funcionalidades acima sustentarão a
versão final do jogo, que será *MMO (massive multiplayer online)*.

## Planejamento

### Semana 1: 19/09 -> 25/09

- [x] fixar um tamanho de tela
- [x] fixar um tamanho de bloco 
- [ ] fixar um tamanho de mapa
- [x] definir um formato de especificação de blocos em arquivos
- [x] "desenhar" bloco do chão e do pilar (em arquivo .csv)
- [ ] renderizar mapa

### Semana 2: 26/09 -> 02/10

- [x] "desenhar" bloco do chão com um jogador nas 4 possíveis orientações
- [ ] "desenhar" bloco do chão com uma bomba
- [ ] spawnar bomba no bloco dado pela orientação do jogador e fazer ela sumir
  após n (definir) ticks (por enqt. sem interação jogador - bomba)

### Semana 3: 03/10 -> 09/10 

- [ ] implementar o chute (interação jogador - bomba)
- [ ] "desenhar" bloco de explosão
- [ ] implementar a explosão em área (se o jogador estiver dentro da área,
  morre)
