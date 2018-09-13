# Pokegame

Clone of a Pokemon game for terminal: Advance through trainers until you lose. You can pick a Pokemon from every trainer you defeat.

## Installation (Linux)

+ `git clone https://github.com/nilfm/PokemonGame` to clone the repo on a folder on your PC.  
+ `cd PokemonGame` to enter the directory.
+ `make` to compile the source code and produce `Pokegame`
+ `./Pokegame` to execute the game.  

## Cleaning up gamesaves

There is a `Cleaner` executable included in the folder, which you can execute with the command `./Cleaner` and follow its steps to clean up one or all of the gamesave data. This process is irreversible.

## Updating the game

This game is being updated constantly, adding new Pokemon and fixing many, many bugs. To update, execute `git pull` and it will update to the newest version.

### TODO

+ Make txt files for every Pokemon  
+ AI choices need work

### BUGS

+ Sometimes the assertion that PP has run out pops up even though the move has 20+ PP
