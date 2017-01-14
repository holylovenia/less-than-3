#ifndef interface_H
#define interface_H

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "../../ADT/Boolean/boolean.h"

#define MaxX 167
#define MaxY 38

#define MaxSpeed 1000
#define SuperFast 800
#define Fast 100
#define Normal 50
#define Slow 20
#define SuperSlow 10

// EXTERNAL VARIABLE
extern int TextSpeed;		// [5..20] for optimal output
/////////////////////

void InitializeNcurses();
// I.S.: Random
// F.S.: Ncurses initialized

void ClearScreen (int Type);
// I.S. : Type defined
// F.S. : Screen cleared

void Pause (long int miliSec);
// I.S. : miliSec defined
// F.S. : Pause system according to miliSec

void InitializeColor(void);
// I.S. : None
// F.S. : Initiazte Color Pairs

WINDOW* CreateWindow(int height, int width, int starty, int startx);
// Create new ncurses window with specific height, width, and starting point for y and x

void DeleteWindow (WINDOW *local_win);
// Delete an ncurses window and clean up the screen leftover by it.

void PrintText (WINDOW* win, int y, int x, char* Text, boolean isCentered, int TextSpeed);
// I.S. : win, y, x, indicates poistion, Text defined, isCentered defined, TextSpeed defined.
// F.S. : Output Text to specific win at y and x with delay according to TextSpeed, optional attributes Centered and COlored
  // Color Combination
    // Pink on black        1
    // Red on black         2
    // Green on black       3
    // Yellow on black      4
    // Blue on black        5
    // Cyan on black        6
    // Blue on white        7
    // Red on white         8

void GameLogo (WINDOW* win, boolean Lit);
// I.S. : win defined, Lit defined
// F.S. : Print LessThan3 logo, 2 variants (Lit and not Lit)

void FillHalfGameLogo (WINDOW* win, boolean isFill);
// I.S.: win defined and allocated, isFill defined
// F.S.: Print LessThan3 logo, only half filled

void AnimateLogo (WINDOW* win);
// I.S. : GameLogo has been printed
// F.S. : Animated, only half of the logo is filled

void PrintHint (WINDOW* win, int Num);
// I.S. : Num defined
// F.S. : A random "hint" has been printed as output

void LoadingScreen (int DurLevel, boolean showHint);
// I.S. : DurLevel defined [1..4], StartUp defined.
// F.S. : Loading Screen, duration determined by DurLevel,

void EndGameScreen (WINDOW* win, boolean isWinner);
// I.S. : win defined and allocated, isWinner defined.
// F.S. : End Game Screen.
            // Show The End if isWinner
            // Show Game Over if not isWinner

void ShowCredits (WINDOW* win);
// I.S.: In ncurses mode, nodelay for win is available and declared.
// F.S.: Show credits until the key Enter or Q is pressed.

#endif
