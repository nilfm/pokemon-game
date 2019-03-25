# Pokegame

Pokemon Battles style game for terminal: Advance through trainers until you lose. You can pick a Pokemon from every trainer you defeat.

## Installation (Linux)

+ `git clone https://github.com/nilfm/PokemonGame` to clone the repo on a folder on your PC.  
+ `cd PokemonGame` to enter the directory.
+ `make` to compile the source code and produce `Pokegame` and `Cleaner`
+ `./Pokegame` to execute the game.  

## Cleaning up gamesaves

After executing `make`, there will be a `Cleaner` executable in the folder, which you can execute with the command `./Cleaner` and follow its steps to clean up one or all of the gamesave data. This process is irreversible.

## Updating the game

This game is being updated constantly, adding new Pokemon and fixing bugs. To update:  
+ `git pull` will update the files to the newest version.  
+ `make` will update the executable.  

### TODO

+ Make txt files for every Pokemon  
+ AI choices need work
+ Add permanent unlocks for reaching certain levels
+ Change the stats calculation to the standard one
+ nerf sandslash lol 

### BUGS

+ Sometimes the assertion that PP has run out pops up even though the move has 20+ PP
