## Game of Life

The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician [John Horton Conway](https://en.wikipedia.org/wiki/John_Horton_Conway) in 1970.

The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine.

### Installation

##### Build

``` sh
git clone git@github.com:TonyJosi97/game_of_life.git
cd game_of_life
make
```

##### Run

``` sh
game_of_life_sim.exe | mpv --no-correct-pts --record-file=out.avi --fps=60 -
```
