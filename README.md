# LessThan3
Dungeon-crawler RPG/Adventure game with an unusual story.
README by Rionaldi Chandraseta.

![LessThan3 Main Menu](https://raw.githubusercontent.com/rionaldichandraseta/LessThan3/master/img/LT3_1.jpeg "LessThan3 Main Menu")

## Credits
* [Agus Gunawan](https://github.com/agusgun)
* [Felix Limanta](https://github.com/felixlimanta)
* [Holy Lovenia](https://github.com/holylovenia)
* [Oktavianus Handika](https://github.com/handikao29)
* [Rionaldi Chandraseta](https://github.com/rionaldichandraseta)

## Getting Started
The game is written in C and requires the **ncurses** library to run as intended. The ncurses library is, unfortunately, exclusive for Linux and can be installed by using the command `sudo apt-get install libncurses-dev`

_It is possible for Windows 10 users to run this game through Windows Subsystem for Linux (WSL). Simply type the exact command to install the ncurses library through WSL._

To get the intended color that is designed for this game, change the terminal's color palette to match these colors.

| Color Name  | Color Hex   | 
|-------------|-------------| 
| BLACK       | #04252E     | 
| RED         | #A31929     | 
| GREEN       | #00B159     | 
| YELLOW      | #FFC425     | 
| BLUE        | #3B5998     | 
| MAGENTA     | #F799B5     | 
| CYAN        | #66CCCC     | 
| WHITE       | #FFFFFF     | 

Alternatively, using **dconfEditor**, copy and paste this line on the `terminal > settings > palette` menu `#04252E:#A31929:#00B159:#FFC425:#3B5998:#F799B5:#66CCCC:#94A3A5:#46585D:#DC322F:#329F69:#FFCA66:#268BD2:#F799B5:#7FC6C1:#FFFFFF`

Make sure to adjust the **terminal's size** before launching the game. The game will not display texts properly if the terminal is too small. Adjust your terminal to be at least **167 columns x 38 rows wide**.

To start the game, simply navigate to the game's `bin/LessThan3` directory and run the game by using the command `./LessThan3`

_Please do not spam commands while the game is loading or showing animations to avoid further input lags._

## Gameplay
The game controls are mostly by using WASD to navigate, and several other keys to access different menus. The controls are mostly displayed on-screen when they are accessible.

The goal of the game is to defeat the boss of the dungeon (shown as Q in the map). Initially, the boss will be way stronger than the player, so the player would need to level up a lot before having a chance to defeat the boss. The game would be over if at any time the player reached 0 HP.

In battle, there are three different moves. **A for Attract**, **B for Bore**, and **F for Flirt**. Okay, we just mix and match the words to suit the game's story about romance, but that is not important. Each battle is divided into 10 rounds, and the player could do 4 moves in each round. Two out of four of the enemy's move will be shown to make it easier for the player to counter the enemy. See the following move matchup for more details.

### Move Matchup
| Your Move | Enemy's Move | Effect                                                   |
|-----------|--------------|----------------------------------------------------------|
| A         | A            | Both deals normal damage.                                |
| A         | B            | Player deals 0 damage to enemy.                          |
| A         | F            | Player deals normal damage, enemy deals reduced damage.  |
| B         | A            | Player takes 0 damage from enemy.                        |
| B         | B            | Nothing happens.                                         |
| B         | F            | Player takes critical damage from enemy.                 |
| F         | A            | Player deals reduced damage, enemy deals normal damage.  |
| F         | B            | Player deals critical damage to enemy.                   |
| F         | F            | Both deals reduced damage.                               |

### Medicine
The player would not regain any HP after a fight. The only way to regain HP is by taking medicines (shown as M in the map). Keep in mind that the amount of medicine is fixed and no medicine will be added later in the game. Use these medicines wisely.

### Attributes
Player starts with 50 points in all attributes (**Strength, Defense, and Luck**). Strength (STR) increases the damage that your Attracts and Flirts do, defense (DEF) increases the player's total health, and luck (LUC) increases the chance of critical hits in battle.

Player will gain 10 attribute point for leveling up. These points could be distributed freely on any attributes. However, the player could not reallocate the points once the changes have been confirmed. The game will save after the player confirms attribute placement.

### Skills
There are 9 total skills in the game, 7 of which are passive skills, and 2 are active skills. Details about the skills could be read in-game.

## In-game Screenshots
![LessThan3 Map](https://raw.githubusercontent.com/rionaldichandraseta/LessThan3/master/img/LT3_2.jpeg "LessThan3 Map")

![LessThan3 Attribute](https://raw.githubusercontent.com/rionaldichandraseta/LessThan3/master/img/LT3_3.jpeg "LessThan3 Attribute")

![LessThan3 SkillTree](https://raw.githubusercontent.com/rionaldichandraseta/LessThan3/master/img/LT3_4.jpeg "LessThan3 SkillTree")

![LessThan3 Battle](https://raw.githubusercontent.com/rionaldichandraseta/LessThan3/master/img/LT3_5.jpeg "LessThan3 Battle")