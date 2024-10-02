# so_long

so_long is one of the projects from the 42 Curriculum. It consists on creating a 2D game entirely in C, using the mlx library for graphics management.

![Alt GameplayExample](so_long_gameplay.gif)

## Project rules
The program must take a configuration file as input, in which a map is represented. It must make sure the map is valid and should then parse it in order to run it accordingly.
It consists of a top-down view 2D game where the player must pick up all collectables before reaching the exit.

## Specific Features
- Player is a climber who must save all npcs from falling before leaving;
- Player grows tired the longer it moves, signaled by his color, ranging from green (full energy) to red (no energy, which triggers a game over);
- Game runs at 10FPS, which allows for tileset, collectable and player animation;
- Player animations in all four directions, placing hands and feet at the location of the rocks, creating simple, but smooth and fairly realistic movement;
- Special effects, like rain and thunder.

## Get started
Clone the repository and do `make` in root. You can then run the executable in the terminal with the path to one of the maps in the ./maps folder or create your own map.

## Controls
Arrow keys or ASDW to move.

## Contact
nunoventuradesousa@gmail.com
