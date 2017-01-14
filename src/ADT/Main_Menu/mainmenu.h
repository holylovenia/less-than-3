#ifndef mainmenu_H
#define mainmenu_H

#include <stdio.h>
#include <string.h>

#include "../../ADT/Boolean/boolean.h"
#include "../../Modul/Interface/interface.h"
#include "../../ADT/Character/character.h"
#include "../../Modul/Statistic/statistic.h"
#include "../../ADT/Binary_Tree/bintree.h"
typedef struct {
    char* Sub;
    int Choice;
} State;

typedef struct {
    State S;
    boolean NewPlayer;
    boolean NoName;
    boolean EndMenu;
} Menu;

// Selector
#define Sub(M) (M).S.Sub
#define Choice(M) (M).S.Choice
#define NewPlayer(M) (M).NewPlayer
#define NoName(M) (M).NoName
#define EndMenu(M) (M).EndMenu

void PrintTreeToWindow (WINDOW* window, BinTree P);

void LoadMainMenu (Menu *MM, boolean *StartGame);
// I.S. : On startup menu, P, MM defined, StartGame to indicate the state of program, EndProgram to end it for good.
// F.S. : Select sub-menu and switch state
//        Start game by choosing either New Game or Load Game and Starting the game
//        User might choose exit to end program

void InitializeMenu (Menu *MM);
// I.S. : *P and *P random, *StartGame will be determined later
// F.S. : MM initialized, enter LoadMenu


#endif
