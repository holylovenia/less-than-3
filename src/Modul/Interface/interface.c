#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "../../ADT/Boolean/boolean.h"
#include "../../Modul/Interface/interface.h"

void InitializeNcurses()
// I.S.: Random
// F.S.: Ncurses initialized
{
    initscr();
    curs_set(false);
    noecho();
    InitializeColor();
    timeout(-1);
}

void ClearScreen(int Type)
// I.S. : Type defined (1 is for ncurses, 0 for standard)
// F.S. : Screen cleared
{
    if (Type == 1) {
        clear();
    }
    else {
        system("clear");
    }
}

void Pause (long int miliSec)
// I.S. : miliSec defined
// F.S. : Pause system according to miliSec
{
    struct timespec req, rem;

    if (miliSec >= 1000) {
        req.tv_sec = (int) miliSec/1000;
        req.tv_nsec = (miliSec - ((long) req.tv_sec * 1000)) * 1000000;
    }
    else {
        req.tv_sec = 0;
        req.tv_nsec = miliSec * 1000000;
    }
    nanosleep(&req, &rem);
}

void InitializeColor(void)
// I.S. : None
// F.S. : Initiate Color Pairs
  // Available colors
    // COLOR_BLACK
    // COLOR_RED
    // COLOR_GREEN
    // COLOR_YELLOW
    // COLOR_BLUE
    // COLOR_MAGENTA
    // COLOR_CYAN
    // COLOR_WHITE
{
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_BLUE, COLOR_WHITE);
    init_pair(8, COLOR_RED, COLOR_WHITE);
}

WINDOW* CreateWindow(int height, int width, int starty, int startx)
// Create new ncurses window with specific height, width, and starting point for y and x
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);      /* 0, 0 gives default characters
                     * for the vertical and horizontal
                     * lines            */
    wrefresh(local_win);        /* Show that box        */

    return local_win;
}

void DeleteWindow (WINDOW *local_win)
// Delete an ncurses window and clean up the screen leftover by it.
{
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    /* The parameters taken are
     * 1. win: the window on which to operate
     * 2. ls: character to be used for the left side of the window
     * 3. rs: character to be used for the right side of the window
     * 4. ts: character to be used for the top side of the window
     * 5. bs: character to be used for the bottom side of the window
     * 6. tl: character to be used for the top left corner of the window
     * 7. tr: character to be used for the top right corner of the window
     * 8. bl: character to be used for the bottom left corner of the window
     * 9. br: character to be used for the bottom right corner of the window
     */
    wclear(local_win);
    wrefresh(local_win);
    delwin(local_win);
}

int textWidth (char * Text)
// Returns the width of a given string (which may include \n) in chars
{
    int i=0,j=0,k=0;

    while (Text[i]!='\0')
    {
        if (Text[i]=='\n')
        {
            if (j>k) {
                k = j;
            }
            j = 0;
        }
        else j++;
        i++;
    }
    if (j > k) {
        k = j;
    }

    return k;
}

void PrintText (WINDOW* win, int y, int x, char* Text, boolean isCentered, int TextSpeed)
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

{
    int i = 0;

    if (isCentered) {
        int maxy, maxx;
        getmaxyx(win, maxy, maxx);
        x = (maxx/2) - textWidth(Text)/2;
    }

    int xi = x;
    while(Text[i] != '\0') {
        mvwprintw(win, y, xi, "%c", Text[i]);
        fflush(stdout);
        xi++;
        i++;
        Pause(1000/TextSpeed);
        wrefresh(win);
    }
}

void GameLogo (WINDOW* win, boolean Lit)
// I.S. : In ncurses mode (initscr() enabled) win defined, Lit defined
// F.S. : Print LessThan3 logo, 2 variants (Lit and not Lit)
{
    if (!Lit) {
        PrintText(win, 1, 0, "     _____                                                                                  ", true, SuperFast);
        PrintText(win, 2, 0, "    |    ||                        ________________                                         ", true, SuperFast);
        PrintText(win, 3, 0, "    |    ||                       |               ||                       __________       ", true, SuperFast);
        PrintText(win, 4, 0, "    |    ||                       |_____     _____||                      /  _____   \\\\     ", true, SuperFast);
        PrintText(win, 5, 0, "    |    ||     _______  ______________|    ||  ||                       |__|     |   ||    ", true, SuperFast);
        PrintText(win, 6, 0, "    |    ||    /  __  \\\\/  ____|| ___|||    ||  ||                                |   ||    ", true, SuperFast);
        PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, SuperFast);
        PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |    ||   ___   |/  ____ ||   ___   \\\\|____  ||      ", true, SuperFast);
        PrintText(win, 9, 0, "    |          || \\\\_______/  ||_/  || |    ||  ||  |  || |   | ||  ||  |  ||     \\  \\\\     ", true, SuperFast);
        PrintText(win, 10, 0, "    |__________||______||____//____//  |    ||  ||  |  || |___| ||  ||  |  ||     |   ||    ", true, SuperFast);
        PrintText(win, 11, 0, "                                       |____||__||  |__||_____|_||__||  |_|  |____/   ||    ", true, SuperFast);
        PrintText(win, 12, 0, "                                                                           \\_________//     ", true, SuperFast);
    }
    else {
        PrintText(win, 12, 0, "                                                                           \\@@@@@@@@@//     ", true, SuperFast);
        PrintText(win, 11, 0, "                                       |@@@@||@@||  |@@||@@@@@|@||@@||  |@|@@|____/@@@||    ", true, SuperFast);
        PrintText(win, 10, 0, "    |@@@@@@@@@@||@@@@@@||@@@@//@@@@//  |@@@@||@@||  |@@||@|___|@||@@||  |@@||     |@@@||    ", true, SuperFast);
        PrintText(win, 9, 0, "    |@@@@@@@@@@||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, SuperFast);
        PrintText(win, 8, 0, "    |@@@@||___|@@@@@@@@||@@@@@\\\\@@@@\\\\ |@@@@||@@@@@@@@@|/@@@@@@@||@@@@@@@@\\\\|@@@@@@@||       ", true, SuperFast);
        PrintText(win, 7, 0, "    |@@@@||   |@@/__\\@@||@//__/@@//__  |@@@@||@@||_____  __________________   ___/@@@//     ", true, SuperFast);
        PrintText(win, 6, 0, "    |@@@@||    /@@@@@@\\\\/@@@@@@||@@@@|||@@@@||@@||                                |@@@||    ", true, SuperFast);
        PrintText(win, 5, 0, "    |@@@@||     _______  ______________|@@@@||@@||                       |@@|     |@@@||    ", true, SuperFast);
        PrintText(win, 4, 0, "    |@@@@||                       |@@@@@@@@@@@@@@@||                      /@@@@@@@@@@\\\\     ", true, SuperFast);
        PrintText(win, 3, 0, "    |@@@@||                       |@@@@@@@@@@@@@@@||                       __________       ", true, SuperFast);
        PrintText(win, 2, 0, "    |@@@@||                        ________________                                         ", true, SuperFast);
        PrintText(win, 1, 0, "     _____                                                                                  ", true, SuperFast);
    }
}

void FillHalfGameLogo (WINDOW* win, boolean isFill)
// I.S.: win defined and allocated, isFill defined
// F.S.: Print LessThan3 logo, only half filled
{
    if (isFill) {
        PrintText(win, 12, 0, "                                                                           \\@@@@@@@@@//     ", true, SuperFast);
        PrintText(win, 11, 0, "                                       |@@@@||@@||  |@@||@@@@@|@||@@||  |@|@@|____/@@@||    ", true, SuperFast);
        PrintText(win, 10, 0, "    |@@@@@@@@@@||@@@@@@||@@@@//@@@@//  |@@@@||@@||  |@@||@|___|@||@@||  |@@||     |@@@||    ", true, SuperFast);
        PrintText(win, 9, 0, "    |@@@@@@@@@@||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, SuperFast);
        PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |    ||   ___   |/  ____ ||   ___   \\\\|____  ||      ", true, SuperFast);
        PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, SuperFast);
        PrintText(win, 6, 0, "    |    ||    /  __  \\\\/  ____|| ___|||    ||  ||                                |   ||    ", true, SuperFast);
        PrintText(win, 5, 0, "    |    ||     _______  ______________|    ||  ||                       |__|     |   ||    ", true, SuperFast);
        PrintText(win, 4, 0, "    |    ||                       |_____     _____||                      /  _____   \\\\     ", true, SuperFast);
        PrintText(win, 3, 0, "    |    ||                       |               ||                       __________       ", true, SuperFast);
        PrintText(win, 2, 0, "    |    ||                        ________________                                         ", true, SuperFast);
        PrintText(win, 1, 0, "     _____                                                                                  ", true, SuperFast);
    }
    else {
        PrintText(win, 1, 0, "     _____                                                                                  ", true, SuperFast);
        PrintText(win, 2, 0, "    |    ||                        ________________                                         ", true, SuperFast);
        PrintText(win, 3, 0, "    |    ||                       |               ||                       __________       ", true, SuperFast);
        PrintText(win, 4, 0, "    |    ||                       |_____     _____||                      /  _____   \\\\     ", true, SuperFast);
        PrintText(win, 5, 0, "    |    ||     _______  ______________|    ||  ||                       |__|     |   ||    ", true, SuperFast);
        PrintText(win, 6, 0, "    |    ||    /  __  \\\\/  ____|| ___|||    ||  ||                                |   ||    ", true, SuperFast);
        PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, SuperFast);
        PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |    ||   ___   |/  ____ ||   ___   \\\\|____  ||      ", true, SuperFast);
        PrintText(win, 9, 0, "    |@@@@@@@@@@||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, SuperFast);
        PrintText(win, 10, 0, "    |@@@@@@@@@@||@@@@@@||@@@@//@@@@//  |@@@@||@@||  |@@||@|___|@||@@||  |@@||     |@@@||    ", true, SuperFast);
        PrintText(win, 11, 0, "                                       |@@@@||@@||  |@@||@@@@@|@||@@||  |@|@@|____/@@@||    ", true, SuperFast);
        PrintText(win, 12, 0, "                                                                           \\@@@@@@@@@//     ", true, SuperFast);
    }
}

void AnimateLogo(WINDOW* win)
// I.S. : GameLogo has been printed
// F.S> : Animated, only half of the logo is filled
{
    PrintText(win, 1, 0, "     _____                                                                                  ", true, SuperFast);
    PrintText(win, 2, 0, "    |@@@@||                        ________________                                         ", true, SuperFast);
    PrintText(win, 3, 0, "    |@@@@||                       |@@@@@@@@@@@@@@@||                       __________       ", true, SuperFast);
    PrintText(win, 4, 0, "    |@@@@||                       |@@@@@@@@@@@@@@@||                      /@@@@@@@@@@\\\\     ", true, SuperFast);
    PrintText(win, 5, 0, "    |@@@@||     _______  ______________|@@@@||@@||                       |@@|     |@@@||    ", true, SuperFast);
    PrintText(win, 6, 0, "    |@@@@||    /@@@@@@\\\\/@@@@@@||@@@@|||@@@@||@@||                                |@@@||    ", true, SuperFast);
    PrintText(win, 7, 0, "    |@@@@||   |@@/__\\@@||@//__/@@//__  |@@@@||@@||_____  __________________   ___/@@@//     ", true, SuperFast);
    PrintText(win, 8, 0, "    |@@@@||___|@@@@@@@@||@@@@@\\\\@@@@\\\\ |@@@@||@@@@@@@@@|/@@@@@@@||@@@@@@@@\\\\|@@@@@@@||       ", true, SuperFast);
    PrintText(win, 9, 0, "    |@@@@@@@@@@||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, SuperFast);
    PrintText(win, 10, 0, "    |@@@@@@@@@@||@@@@@@||@@@@//@@@@//  |@@@@||@@||  |@@||@|___|@||@@||  |@@||     |@@@||    ", true, SuperFast);
    PrintText(win, 11, 0, "                                       |@@@@||@@||  |@@||@@@@@|@||@@||  |@|@@|____/@@@||    ", true, SuperFast);
    PrintText(win, 12, 0, "                                                                           \\@@@@@@@@@//     ", true, SuperFast);

    // Partial Delete
    PrintText(win, 1, 0, "     _____                                                                                  ", true, SuperFast);
    PrintText(win, 2, 0, "    |    ||                        ________________                                         ", true, SuperFast);
    PrintText(win, 3, 0, "    |    ||                       |               ||                       __________       ", true, SuperFast);
    PrintText(win, 4, 0, "    |    ||                       |_____     _____||                      /  _____   \\\\     ", true, SuperFast);
    PrintText(win, 5, 0, "    |    ||     _______  ______________|    ||  ||                       |__|     |   ||    ", true, SuperFast);
    PrintText(win, 6, 0, "    |    ||    /  __  \\\\/  ____|| ___|||    ||  ||                                |   ||    ", true, SuperFast);

    // Phase 1
    PrintText(win, 7, 0, "    |@@  ||   |  /__\\  || //__/@ //__  |    ||  ||_____  __________________   ___/   //     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |@@@@||___|_  _____||__@@@\\\\@@@ \\\\ |    ||   @@@@@@|/  ____ ||  @@@@@  \\\\|__@@@@||      ", true, MaxSpeed);
    //PrintText(win, 9, 0, "    |@@@@@@@@  || \\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   | || @||  |@@||     \\@@\\\\     ", true, SuperFast);

    // Phase 2
    PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/@@@//     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |@@  ||___|_  _____||__   \\\\ @@@\\\\ |@@  ||   ___ @@|/@@@___ ||   ___@@@\\\\|@@@@@@||      ", true, MaxSpeed);
    //PrintText(win, 9, 0, "    |@@@@@@@@@@||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, SuperFast);

    // Phase 3
    PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/  @//     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |    ||___|@@@_____||__   \\\\__  \\\\ |@@@@||@  ___   |/  ___@@||@@ ___  @\\\\|@@@@@@||      ", true, MaxSpeed);
    //PrintText(win, 9, 0, "    |@@@@@@@@@@||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, SuperFast);

    // Phase 4
    PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |    ||___|_  _____||_@@@@\\\\__  \\\\ |    ||@@@@@_   |/  ____ ||  @@@@@@@\\\\|@@@@@@||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |   @@@@@@@||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // Phase 5
    //PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/ @@//     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |    ||___|_  _____||___ @\\\\@@@ \\\\ |    ||   ___@@@|/@ ____ ||@@@@@@@@@\\\\|@@@@@@||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |       @@@||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // Phase 6
    //PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |@@@@||   ____  |/  @@@@@||@@@@@@@@@\\\\|@@@@@@||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |          || \\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // Phase 7
    //PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |    || @@@@@_  |/@@@@@@@||@@@@@@@@@\\\\|@@@@@@||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |          || \\\\_______/  ||_/ @|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // Phase 8
    //PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |    ||@@@@@@@@@|/@@@@@@@||@@@@@@@@@\\\\|@@@@@@||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |          || \\\\_______/  ||_/  || |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // Phase 9
    //PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |  @@||@@@@@@@@@|/@@@@@@@||@@@@@@@@@\\\\|@@@@@@||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |          || \\\\_______/  ||_/ @|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // InterMezzo
    PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |  @@||@@@@@@@@@|/@@@@@@@||@@@@@@@@@\\\\|@@@@@@||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |          || \\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // Phase 10
    //PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |    ||  @@@@@@@|/@@@@@@@||@@@@@@@@@\\\\|@@@@@@||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |          || \\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // Phase 11
    //PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |    ||   ___   |/  @@@@@||@@@@@@@@@\\\\|@@@@@@||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |          ||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // Phase 12
    //PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |    ||   ___   |/  ____ ||   ___@@@\\\\|@@@@@@||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |        @@||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // Phase 13
    //PrintText(win, 7, 0, "    |    ||   |  /__\\  || //__/  //__  |    ||  ||_____  __________________   ___/   //     ", true, MaxSpeed);
    PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |    ||   ___   |/  ____ ||   ___   \\\\|___@@@||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |     @@@@@||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // Phase 14
    PrintText(win, 8, 0, "    |    ||___|_  _____||___  \\\\__  \\\\ |    ||   ___   |/  ____ ||   ___   \\\\|____  ||      ", true, MaxSpeed);
    PrintText(win, 9, 0, "    |@@@@@@@@@@||@\\\\_______/@@||_/@@|| |@@@@||@@||  |@@||@|   |@||@@||  |@@||     \\@@\\\\     ", true, MaxSpeed);

    // Cleanup
    Pause(500);
}

/*void PrintDamage (WINDOW* win, int y, int x, int damage, boolean isColored)
// I.S. : win, y, x, indicates poistion, Text defined, isCentered and isColored defined, TextSpeed defined.
// F.S. : Output Text to specific win at y and x with delay according to TextSpeed, optional attributes Centered and COlored
{
    int xi = x;
    char* Text =
    while(Text[i] != '\0') {
        mvwprintw(win, y, xi, "%c", Text[i]);
        fflush(stdout);
        xi++;
        //i++;
        Pause(1000/20);
        wrefresh(win);
    }
}*/

void PrintHint (WINDOW* win, int Num)
// I.S. : Num defined
// F.S. : A random "hint" has been printed as output
{
    if (Num == 0) {
        PrintText(win, 5, 0, "Is the game too hard for you? Don't worry, press Ctrl+C to activate the easy mode!", true, Normal);
    }
    else if (Num == 1) {
        PrintText(win, 4, 0, "If you get the title of this game, then you have spent too much time on the internet", true, Normal);
        Pause(500);
        PrintText(win, 6, 0, "If you don't, you must have spent too much time on the internet, on the wrong side that is", true, Normal);
    }
    else if (Num == 2) {
        PrintText(win, 4, 0, "Disclaimer: This game does not help you get any better in romancing anybody IRL", true, Normal);
        Pause(500);
        PrintText(win, 6, 0, "IRL = In Real Life, dummy", true, Normal);
    }
    else if (Num == 3) {
        PrintText(win, 4, 0, "A stands for attract, B stands for bore, and F stands for flirt", true, Normal);
        Pause(500);
        PrintText(win, 6, 0, "Don't ask why, just accept the reality", true, Normal);
    }
    else if (Num == 4) {
        PrintText(win, 4, 0, "Warning: Side effect of playing this game includes, but not limited to, mental breakdown, partial amnesia, ...", true, Normal);
        Pause(500);
        PrintText(win, 6, 0, "Uh..., I forgot the rest of the line", true, Slow);
    }
    else if (Num == 5) {
        PrintText(win, 4, 0, "Have you tried loading up the developers' saved game?", true, Normal);
        Pause(500);
        PrintText(win, 6, 0, "Yeah, we are that good at this game", true, Normal);
    }
    else if (Num == 6) {
        PrintText(win, 5, 0, "This game is a work of fiction, any resemblance to real life characters are fully intentional", true, Normal);
    }
    else if (Num == 7) {
        PrintText(win, 4, 0, "Fun fact: This loading screen takes up 1.23% of your total gameplay time", true, Normal);
        Pause(1000);
        PrintText(win, 6, 0, "Another fun fact: Reading this line takes up another 0.37% of your total gameplay time", true, Normal);
        PrintText(win, 4, 0, "Fun fact: This loading screen takes up 1.24% of your total gameplay time", true, SuperFast);
    }
    else if (Num == 8) {
        PrintText(win, 3, 0, "Hours of sleep sacrificed = 0xff", true, Fast);
        Pause(100);
        PrintText(win, 4, 0, "Compilation failure count = exited with code 1", true, Fast);
        Pause(100);
        PrintText(win, 5, 0, "Segmentation fault encountered = 13515", true, Fast);
        Pause(100);
        PrintText(win, 6, 0, "Price of this game = FREE (currently) (seriously, we accept donations)", true, Fast);
        Pause(200);
        PrintText(win, 8, 0, "Your expression reading this = Priceless", true, Normal);
    }
    else if (Num == 9) {
        PrintText(win, 3, 0, "Fun fact: One of our biggest laughs while making this game was because of the following code", true, Normal);
        Pause(500);
        PrintText(win, 5, 0, "Dealokasi(address P) {", true, Slow);
        Pause(250);
        PrintText(win, 6, 0, "    Dealokasi(P)      ", true, Slow);
        PrintText(win, 7, 0, "}                     ", true, Fast);
    }
    else if (Num == 10) {
        PrintText(win, 5, 0, "<3 <3 <3 <3 <3", true, Slow);
    }
    else if (Num == 11) {
        PrintText(win, 3, 0, "Love overflow!", true, Normal);
        PrintText(win, 4, 0, ":3", true, Normal);
        Pause(500);
        PrintText(win, 6, 0, "I'm just kidding, I only had little love as it is", true, Normal);
        PrintText(win, 7, 0, ":(", true, Normal);
    }
    else if (Num == 12) {
        PrintText(win, 4, 0, "Every words in this game is designed for your pleasure", true, Normal);
        Pause(500);
        PrintText(win, 6, 0, "And also our pleasure, well, mostly ours though...", true, Normal);
    }
    else if (Num == 13) {
        PrintText(win, 3, 0, "I can't stop the loading ~", true, Normal);
        PrintText(win, 4, 0, "So just dance, dance, dance ~", true, Normal);
        Pause(500);
        PrintText(win, 8, 0, "Everybody!", true, Normal);
    }
    else if (Num == 14) {
        PrintText(win, 4, 0, "Tip: Type UP UP DOWN DOWN A B A B in game", true, Normal);
        Pause(1000);
        PrintText(win, 6, 0, "It will do absolutely nothing", true, Normal);
    }
    else if (Num == 15) {
        PrintText(win, 3, 0, "Bad jokes time!", true, Normal);
        Pause(250);
        PrintText(win, 5, 0, "A woman said to a man, 'Whisper something sweet and made of 3 words to my ear'", true, Normal);
        Pause(250);
        PrintText(win, 6, 0, "The man came closer and whispered, 'Lemon meringue pie'", true, Normal);
    }
    else if (Num == 16) {
        PrintText(win, 4, 0, "'Do you have a date for Valentine's Day?'", true, Normal);
        Pause(500);
        PrintText(win, 6, 0, "'Yes, February 14th'", true, Normal);
    }
    else if (Num == 17) {
        PrintText(win, 3, 0, "If you play the game of love, you win or you die...", true, Normal);
        PrintText(win, 4, 0, "...slowly...", true, 25);
        PrintText(win, 5, 0, "...from all the rejections", true, Normal);
        Pause(250);
        PrintText(win, 7, 0, "-Tyrion Lannister", true, Normal);
        PrintText(win, 8, 0, "(paraphrased)", true, Normal);
    }
    else if (Num == 18) {
        PrintText(win, 3, 0, "Love hurts", true, Normal);
        Pause(500);
        PrintText(win, 5, 0, "a lot", true, Normal);
        Pause(1000);
        PrintText(win, 7, 0, "especially in this game", true, Normal);
    }
    else if (Num == 19) {
        PrintText(win, 5, 0, "Please refrain from restarting the game to try and read all these lines in the game", true, Normal);
    }
    else if (Num == 20) {
        Pause(5000);
        PrintText(win, 5, 0, "I can read minds you know, I knew you thought the game just froze", true, Normal);
    }
}

void LoadingScreen (int DurLevel, boolean showHint)
// I.S. : DurLevel defined [1..4], StartUp defined.
// F.S. : Loading Screen, duration determined by DurLevel,
{
    int Progress = 0;
    srand(time(NULL));
    int RandomHint = rand() % 21;
    int RandomProg = (rand() % 3) + 2;

    WINDOW* Background = CreateWindow(MaxY, MaxX, 0, 0);
    wbkgd(Background, COLOR_PAIR(1));
    wrefresh(Background);

    WINDOW* Loading = newwin(15, 160, 4, 4);
    wbkgd(Loading, COLOR_PAIR(1));
    wrefresh(Loading);

    WINDOW* Hint = newwin(12, 160, 22, 4);

    if (!showHint) {
        Loading = newwin(15, 160, 8, 0);
    }
    else {
        wbkgd(Hint, COLOR_PAIR(1));
        wrefresh(Hint);
    }




    while (Progress <= 9) {
        /**/mvwprintw(Loading, 2, 74, "_____   _____");
        if (Progress >= 8) {
            mvwprintw(Loading, 3, 73, "/@ @ @\\ /@ @ @\\");
        }
        else {
            mvwprintw(Loading, 3, 73, "/     \\ /     \\");
        }

        if (Progress >= 7) {
            mvwprintw(Loading, 4, 72, "|@ @ @ @ @ @ @ @|");
        }
        else {
            mvwprintw(Loading, 4, 72, "|               |");
        }

        if (Progress >= 6) {
            mvwprintw(Loading, 5, 73, "\\@ @ @ @ @ @ @/");
        }
        else {
            mvwprintw(Loading, 5, 73, "\\             /");
        }

        if (Progress >= 5) {
            mvwprintw(Loading, 6, 74, "\\@ @ @ @ @ @/");
        }
        else {
            mvwprintw(Loading, 6, 74, "\\           /");
        }

        if (Progress >= 4) {
            mvwprintw(Loading, 7, 75, "\\@ @ @ @ @/");
        }
        else {
            mvwprintw(Loading, 7, 75, "\\         /");
        }

        if (Progress >= 3) {
            mvwprintw(Loading, 8, 76, "\\@ @ @ @/");
        }
        else {
            mvwprintw(Loading, 8, 76, "\\       /");
        }

        if (Progress >= 2) {
            mvwprintw(Loading, 9, 77, "\\@ @ @/");
        }
        else {
            mvwprintw(Loading, 9, 77, "\\     /");
        }

        if (Progress >= 1) {
            mvwprintw(Loading, 10, 78, "\\@_@/");
        }
        else {
            mvwprintw(Loading, 10, 78, "\\___/");
        }

        if (Progress < 9) {
            mvwprintw(Loading, 13, 76, "Loading...\n");
        }
        else {
            if (Progress == 9) {
                PrintText(Loading, 13, 0, "Press any key to start", true, Slow);
            }
        }

        if (showHint) {
            if (Progress == RandomProg) {
                PrintHint(Hint, RandomHint);
            }
        }

        if (Progress <= 3) {
            Pause(DurLevel*200);
        }
        else {
            if (Progress == 5) {
                Pause(DurLevel*600);
            }
            else if (Progress == 9) {
                Pause(0);
            }
            else {
                Pause(DurLevel*400);
            }
        }
        Progress++;
        wrefresh(Loading);
    }
    chtype buffer = wgetch(Loading);

    DeleteWindow(Loading);
    DeleteWindow(Hint);
    DeleteWindow(Background);
}

void EndGameScreen (WINDOW* win, boolean isWinner)
// I.S. : win defined and allocated, isWinner defined.
// F.S. : End Game Screen.
            // Show The End if isWinner
            // Show Game Over if not isWinner
{
    if (isWinner) {
        wbkgd(win, COLOR_PAIR(1));
    }
    else {
        wbkgd(win, COLOR_PAIR(2));
    }

    for (int i=1; i<=8; i++) {
        PrintText(win, i, 1, "                                                                                                                                                                     ", true, SuperFast);
    }

    if (!isWinner) {
        PrintText(win,  9,1, "                        _________________                                                                                                                            ", true, SuperFast);
        PrintText(win, 10,1, "                       //               /                                               ________________                                                             ", true, SuperFast);
        PrintText(win, 11,1, "                      //      _________/                                               //               \\                                                            ", true, SuperFast);
        PrintText(win, 12,1, "                     //      /                                                        //      _______    \\                                                           ", true, SuperFast);
        PrintText(win, 13,1, "                     ||     /                                                         ||     /      \\\\    |                                                          ", true, SuperFast);
        PrintText(win, 14,1, "                     ||    |                                                          ||    |       ||    |                                                          ", true, SuperFast);
        PrintText(win, 15,1, "                     ||    |  _________   __________  ________________  _________     ||    |       ||    |                                                          ", true, SuperFast);
        PrintText(win, 16,1, "                     ||    | ||        \\//   _____  |/   ___    ___   |//  ____  \\    ||    |       ||    |___          _____________   _________                    ", true, SuperFast);
        PrintText(win, 17,1, "                     ||    | ||______   ||  /   ||  ||  /  ||  /  ||  |/  /    \\\\ \\   ||    |       ||    |   \\        //  //  ____  \\ //  _____/                    ", true, SuperFast);
        PrintText(win, 18,1, "                     ||    |       ||   ||  |   ||  ||  |  ||  |  ||  ||  |____|| |   ||    |       ||    |\\   \\      //  //  /    \\\\ \\|  /                          ", true, SuperFast);
        PrintText(win, 19,1, "                     ||     \\      //   ||  |   ||  ||  |  ||  |  ||  ||   _______|   ||    |       ||    |\\\\   \\    //  /||  |____|| ||  |                          ", true, SuperFast);
        PrintText(win, 20,1, "                     \\\\      \\____//    /|  |   ||  ||  |  ||  |  ||  ||  |           ||    |       ||    | \\\\   \\  //  / ||   _______||  |                          ", true, SuperFast);
        PrintText(win, 21,1, "                      \\\\               /||   \\__||  ||  |  ||  |  ||  |\\\\  \\______    ||     \\______//    |  \\\\   \\//  /  ||  |       ||  |                          ", true, SuperFast);
        PrintText(win, 22,1, "                       \\\\_____________/  \\\\______|__||__|  ||__|  ||__| \\\\________|    \\\\                /    \\\\      /    \\\\  \\______||  |                          ", true, SuperFast);
        PrintText(win, 23,1, "                                                                                        \\\\______________/      \\\\____/      \\\\________||__|                          ", true, SuperFast);
    }
    else {
        PrintText(win,  9,1, "                                       _____________________                                                                                                         ", true, SuperFast);
        PrintText(win, 10,1, "                                      ||                   |                           _________________                                                             ", true, SuperFast);
        PrintText(win, 11,1, "                                      ||_______      ______|_                         ||                |                                                            ", true, SuperFast);
        PrintText(win, 12,1, "                                              ||    |    ||  |                        ||     ___________|                                                            ", true, SuperFast);
        PrintText(win, 13,1, "                                              ||    |    ||  |                        ||    |                                 ___                                    ", true, SuperFast);
        PrintText(win, 14,1, "                                              ||    |    ||  |                        ||    |                                ||  |                                   ", true, SuperFast);
        PrintText(win, 15,1, "                                              ||    |    ||  |________  _________     ||    |                                ||  |                                   ", true, SuperFast);
        PrintText(win, 16,1, "                                              ||    |    ||   _____  \\\\//  ____  \\    ||    |__________   ___________  ______||  |                                   ", true, SuperFast);
        PrintText(win, 17,1, "                                              ||    |    ||  |    \\\\  |/  /    \\\\ \\   ||               | ||   ____   \\/   _____  |                                   ", true, SuperFast);
        PrintText(win, 18,1, "                                              ||    |    ||  |    ||  ||  |____|| |   ||     __________| ||  |   \\\\  ||  /   ||  |                                   ", true, SuperFast);
        PrintText(win, 19,1, "                                              ||    |    ||  |    ||  ||   _______|   ||    |            ||  |   ||  ||  |   ||  |                                   ", true, SuperFast);
        PrintText(win, 20,1, "                                              ||    |    ||  |    ||  ||  |           ||    |            ||  |   ||  ||  |   ||  |                                   ", true, SuperFast);
        PrintText(win, 21,1, "                                              ||    |    ||  |    ||  |\\\\  \\______    ||    |___________ ||  |   ||  ||  |   ||  |                                   ", true, SuperFast);
        PrintText(win, 22,1, "                                              ||____|    ||__|    ||__| \\\\________|   ||                |||  |   ||  ||  \\___||  |                                   ", true, SuperFast);
        PrintText(win, 23,1, "                                                                                      ||________________|||__|   ||__| \\_________|                                   ", true, SuperFast);
    }

    for (int i=24; i<=36; i++) {
        PrintText(win, i, 1, "                                                                                                                                                                     ", true, SuperFast);
    }

    if (!isWinner) {
        PrintText(win,  9,1, "                        _________________                                                                                                                            ", true, SuperFast);
        PrintText(win, 10,1, "                       //@@@@@@@@@@@@@@@/                                               ________________                                                             ", true, SuperFast);
        PrintText(win, 11,1, "                      //@@@@@@@@@@@@@@@/                                               //@@@@@@@@@@@@@@@\\                                                            ", true, SuperFast);
        PrintText(win, 12,1, "                     //@@@@@@/                                                        //@@@@@@@@@@@@@@@@@\\                                                           ", true, SuperFast);
        PrintText(win, 13,1, "                     ||@@@@@/                                                         ||@@@@@/      \\\\@@@@|                                                          ", true, SuperFast);
        PrintText(win, 14,1, "                     ||@@@@|                                                          ||@@@@|       ||@@@@|                                                          ", true, SuperFast);
        PrintText(win, 15,1, "                     ||@@@@|  _________   __________  ________________  _________     ||@@@@|       ||@@@@|                                                          ", true, SuperFast);
        PrintText(win, 16,1, "                     ||@@@@| ||@@@@@@@@\\//@@@@@@@@@@|/@@@@@@@@@@@@@@@@|//@@@@@@@@\\    ||@@@@|       ||@@@@|___          _____________   _________                    ", true, SuperFast);
        PrintText(win, 17,1, "                     ||@@@@| ||@@@@@@@@@||@@/   ||@@||@@/  ||@@/  ||@@|/@@/    \\\\@\\   ||@@@@|       ||@@@@|@@@\\        //@@//@@@@@@@@\\ //@@@@@@@/                    ", true, SuperFast);
        PrintText(win, 18,1, "                     ||@@@@|       ||@@@||@@|   ||@@||@@|  ||@@|  ||@@||@@|____||@|   ||@@@@|       ||@@@@|\\@@@\\      //@@//@@/    \\\\@\\|@@/                          ", true, SuperFast);
        PrintText(win, 19,1, "                     ||@@@@@\\      //@@@||@@|   ||@@||@@|  ||@@|  ||@@||@@@@@@@@@@|   ||@@@@|       ||@@@@|\\\\@@@\\    //@@/||@@|____||@||@@|                          ", true, SuperFast);
        PrintText(win, 20,1, "                     \\\\@@@@@@\\____//@@@@/|@@|   ||@@||@@|  ||@@|  ||@@||@@|           ||@@@@|       ||@@@@| \\\\@@@\\  //@@/ ||@@@@@@@@@@||@@|                          ", true, SuperFast);
        PrintText(win, 21,1, "                      \\\\@@@@@@@@@@@@@@@/||@@@\\__||@@||@@|  ||@@|  ||@@|\\\\@@\\______    ||@@@@@\\______//@@@@|  \\\\@@@\\//@@/  ||@@|       ||@@|                          ", true, SuperFast);
        PrintText(win, 22,1, "                       \\\\@@@@@@@@@@@@@/  \\\\@@@@@@|@@||@@|  ||@@|  ||@@| \\\\@@@@@@@@|    \\\\@@@@@@@@@@@@@@@@/    \\\\@@@@@@/    \\\\@@\\______||@@|                          ", true, SuperFast);
        PrintText(win, 23,1, "                                                                                        \\\\@@@@@@@@@@@@@@/      \\\\@@@@/      \\\\@@@@@@@@||@@|                          ", true, SuperFast);
    }
    else {
        PrintText(win,  9,1, "                                       _____________________                                                                                                         ", true, SuperFast);
        PrintText(win, 10,1, "                                      ||@@@@@@@@@@@@@@@@@@@|                           _________________                                                             ", true, SuperFast);
        PrintText(win, 11,1, "                                      ||@@@@@@@@@@@@@@@@@@@|_                         ||@@@@@@@@@@@@@@@@|                                                            ", true, SuperFast);
        PrintText(win, 12,1, "                                              ||@@@@|    ||@@|                        ||@@@@@@@@@@@@@@@@|                                                            ", true, SuperFast);
        PrintText(win, 13,1, "                                              ||@@@@|    ||@@|                        ||@@@@|                                 ___                                    ", true, SuperFast);
        PrintText(win, 14,1, "                                              ||@@@@|    ||@@|                        ||@@@@|                                ||@@|                                   ", true, SuperFast);
        PrintText(win, 15,1, "                                              ||@@@@|    ||@@|________  _________     ||@@@@|                                ||@@|                                   ", true, SuperFast);
        PrintText(win, 16,1, "                                              ||@@@@|    ||@@@@@@@@@@\\\\//@@@@@@@@\\    ||@@@@|__________   ___________  ______||@@|                                   ", true, SuperFast);
        PrintText(win, 17,1, "                                              ||@@@@|    ||@@|    \\\\@@|/@@/    \\\\@\\   ||@@@@@@@@@@@@@@@| ||@@@@@@@@@@\\/@@@@@@@@@@|                                   ", true, SuperFast);
        PrintText(win, 18,1, "                                              ||@@@@|    ||@@|    ||@@||@@|____||@|   ||@@@@@@@@@@@@@@@| ||@@|   \\\\@@||@@/   ||@@|                                   ", true, SuperFast);
        PrintText(win, 19,1, "                                              ||@@@@|    ||@@|    ||@@||@@@@@@@@@@|   ||@@@@|            ||@@|   ||@@||@@|   ||@@|                                   ", true, SuperFast);
        PrintText(win, 20,1, "                                              ||@@@@|    ||@@|    ||@@||@@|           ||@@@@|            ||@@|   ||@@||@@|   ||@@|                                   ", true, SuperFast);
        PrintText(win, 21,1, "                                              ||@@@@|    ||@@|    ||@@|\\\\@@\\______    ||@@@@|___________ ||@@|   ||@@||@@|   ||@@|                                   ", true, SuperFast);
        PrintText(win, 22,1, "                                              ||@@@@|    ||@@|    ||@@| \\\\@@@@@@@@|   ||@@@@@@@@@@@@@@@@|||@@|   ||@@||@@\\___||@@|                                   ", true, SuperFast);
        PrintText(win, 23,1, "                                                                                      ||@@@@@@@@@@@@@@@@|||@@|   ||@@| \\@@@@@@@@@|                                   ", true, SuperFast);
    }

    if (!isWinner) {
        PrintText(win,  9,1, "                        _________________                                                                                                                            ", true, SuperFast);
        PrintText(win, 10,1, "                       //               /                                               ________________                                                             ", true, SuperFast);
        PrintText(win, 11,1, "                      //      _________/                                               //               \\                                                            ", true, SuperFast);
        PrintText(win, 12,1, "                     //      /                                                        //      _______    \\                                                           ", true, SuperFast);
        PrintText(win, 13,1, "                     ||     /                                                         ||     /      \\\\    |                                                          ", true, SuperFast);
        PrintText(win, 14,1, "                     ||    |                                                          ||    |       ||    |                                                          ", true, SuperFast);
        PrintText(win, 15,1, "                     ||    |  _________   __________  ________________  _________     ||    |       ||    |                                                          ", true, SuperFast);
        PrintText(win, 16,1, "                     ||    | ||        \\//   _____  |/   ___    ___   |//  ____  \\    ||    |       ||    |___          _____________   _________                    ", true, SuperFast);
        PrintText(win, 17,1, "                     ||    | ||______   ||  /   ||  ||  /  ||  /  ||  |/  /    \\\\ \\   ||    |       ||    |   \\        //  //  ____  \\ //  _____/                    ", true, SuperFast);
        PrintText(win, 18,1, "                     ||    |       ||   ||  |   ||  ||  |  ||  |  ||  ||  |____|| |   ||    |       ||    |\\   \\      //  //  /    \\\\ \\|  /                          ", true, SuperFast);
        PrintText(win, 19,1, "                     ||     \\      //   ||  |   ||  ||  |  ||  |  ||  ||   _______|   ||    |       ||    |\\\\   \\    //  /||  |____|| ||  |                          ", true, SuperFast);
        PrintText(win, 20,1, "                     \\\\      \\____//    /|  |   ||  ||  |  ||  |  ||  ||  |           ||    |       ||    | \\\\   \\  //  / ||   _______||  |                          ", true, SuperFast);
        PrintText(win, 21,1, "                      \\\\               /||   \\__||  ||  |  ||  |  ||  |\\\\  \\______    ||     \\______//    |  \\\\   \\//  /  ||  |       ||  |                          ", true, SuperFast);
        PrintText(win, 22,1, "                       \\\\_____________/  \\\\______|__||__|  ||__|  ||__| \\\\________|    \\\\                /    \\\\      /    \\\\  \\______||  |                          ", true, SuperFast);
        PrintText(win, 23,1, "                                                                                        \\\\______________/      \\\\____/      \\\\________||__|                          ", true, SuperFast);
    }
    else {
        PrintText(win,  9,1, "                                       _____________________                                                                                                         ", true, SuperFast);
        PrintText(win, 10,1, "                                      ||                   |                           _________________                                                             ", true, SuperFast);
        PrintText(win, 11,1, "                                      ||_______      ______|_                         ||                |                                                            ", true, SuperFast);
        PrintText(win, 12,1, "                                              ||    |    ||  |                        ||     ___________|                                                            ", true, SuperFast);
        PrintText(win, 13,1, "                                              ||    |    ||  |                        ||    |                                 ___                                    ", true, SuperFast);
        PrintText(win, 14,1, "                                              ||    |    ||  |                        ||    |                                ||  |                                   ", true, SuperFast);
        PrintText(win, 15,1, "                                              ||    |    ||  |________  _________     ||    |                                ||  |                                   ", true, SuperFast);
        PrintText(win, 16,1, "                                              ||    |    ||   _____  \\\\//  ____  \\    ||    |__________   ___________  ______||  |                                   ", true, SuperFast);
        PrintText(win, 17,1, "                                              ||    |    ||  |    \\\\  |/  /    \\\\ \\   ||               | ||   ____   \\/   _____  |                                   ", true, SuperFast);
        PrintText(win, 18,1, "                                              ||    |    ||  |    ||  ||  |____|| |   ||     __________| ||  |   \\\\  ||  /   ||  |                                   ", true, SuperFast);
        PrintText(win, 19,1, "                                              ||    |    ||  |    ||  ||   _______|   ||    |            ||  |   ||  ||  |   ||  |                                   ", true, SuperFast);
        PrintText(win, 20,1, "                                              ||    |    ||  |    ||  ||  |           ||    |            ||  |   ||  ||  |   ||  |                                   ", true, SuperFast);
        PrintText(win, 21,1, "                                              ||    |    ||  |    ||  |\\\\  \\______    ||    |___________ ||  |   ||  ||  |   ||  |                                   ", true, SuperFast);
        PrintText(win, 22,1, "                                              ||____|    ||__|    ||__| \\\\________|   ||                |||  |   ||  ||  \\___||  |                                   ", true, SuperFast);
        PrintText(win, 23,1, "                                                                                      ||________________|||__|   ||__| \\_________|                                   ", true, SuperFast);
    }
    Pause(500);

    PrintText(win, 25, 0, "Press any key to continue", true, Slow);
    char buffer = wgetch(win);

    wclear(win);
    wrefresh(win);

    ShowCredits(win);
}

void ShowCredits(WINDOW* win)
// I.S.: In ncurses mode, nodelay for win is available and declared.
// F.S.: Show credits until the key Enter or Q is pressed.
{
    WINDOW* CreditCentral = newwin(12, 50, (MaxY-12)/2-1, (MaxX-50)/2);
    wbkgd(CreditCentral, COLOR_PAIR(1));

    WINDOW* CreditBottom = newwin(11, 50, ((MaxY-12)/2 + 12), (MaxX-50)/2);
    wbkgd(CreditBottom, COLOR_PAIR(6));

    WINDOW* Credit1 = newwin(9, 28, 2, 4);
    wbkgd(Credit1, COLOR_PAIR(6));

    WINDOW* Credit2 = newwin(9, 28, 2, 36);
    wbkgd(Credit2, COLOR_PAIR(6));

    WINDOW* Credit3 = newwin(9, 28, 2, 69);
    wbkgd(Credit3, COLOR_PAIR(6));

    WINDOW* Credit4 = newwin(9, 28, 2, 102);
    wbkgd(Credit4, COLOR_PAIR(6));

    WINDOW* Credit5 = newwin(9, 28, 2, 134);
    wbkgd(Credit5, COLOR_PAIR(6));

    WINDOW* CreditLeft = newwin(23, 50, (MaxY-16)/2, 4);
    wbkgd(CreditLeft, COLOR_PAIR(6));

    WINDOW* CreditRight = newwin(23, 50, (MaxY-16)/2, (MaxX-55));
    wbkgd(CreditRight, COLOR_PAIR(6));

    // initiate
    PrintText(CreditCentral, 1, 0, "                      @@@  @@@@@@               ", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "                    @@@       @@@@              ", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "                  @@@           @@@             ", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "                @@@             @@@             ", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "              @@@              @@@              ", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "            @@@             @@@@@@              ", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "              @@@              @@@@             ", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "                @@@              @@@            ", true, SuperFast);
    PrintText(CreditCentral, 9, 0, "                  @@@            @@@            ", true, SuperFast);
    PrintText(CreditCentral, 10,0, "                    @@@        @@@@             ", true, SuperFast);
    PrintText(CreditCentral, 11,0, "                      @@@   @@@@@@              ", true, SuperFast);
    Pause(3000);
    for (int i = 1; i<9; i++) {
        wbkgd(CreditCentral, COLOR_PAIR(i%7));
        wrefresh(CreditCentral);
        Pause(200);
    }
    Pause(1000);

    PrintText(CreditCentral, 6, 0, "Less Than 3", true, Slow);
    Pause(2000);

    PrintText(CreditCentral, 1, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 9, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 10,0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    box(CreditCentral, 0, 0);
    PrintText(CreditCentral, 11,0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);

    // PHASE 1
    PrintText(CreditCentral, 1, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "                    The Devs                    ", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "   13515035 - Oktavianus Handika                ", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "   13515065 - Felix Limanta                     ", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "   13515077 - Rionaldi Chandraseta              ", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "   13515113 - Holy Lovenia                      ", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "   13515143 - Agus Gunawan                      ", true, SuperFast);
    PrintText(CreditCentral, 9, 0, "                                                ", true, SuperFast);
    Pause(1000);

    PrintText(Credit1, 2, 0, "Character Developer", true, Normal);
    PrintText(Credit1, 5, 0, "Oktavianus Handika", true, Normal);

    PrintText(Credit2, 2, 0, "External File Specialist", true, Normal);
    PrintText(Credit2, 5, 0, "Felix Limanta", true, Normal);

    PrintText(Credit3, 2, 0, "Game Interface Designer", true, Normal);
    PrintText(Credit3, 5, 0, "Rionaldi Chandraseta", true, Normal);

    PrintText(Credit4, 2, 0, "Battle and Skill Manager", true, Normal);
    PrintText(Credit4, 5, 0, "Holy Lovenia", true, Normal);

    PrintText(Credit5, 2, 0, "Map and Exploration Engineer", true, Normal);
    PrintText(Credit5, 5, 0, "Agus Gunawan", true, Normal);

    // PHASE 2
    PrintText(CreditCentral, 9, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 1, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);

    PrintText(CreditCentral, 1, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "                    CREDITS                     ", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 9, 0, "                                                ", true, SuperFast);
    Pause(500);

    PrintText(CreditLeft, 0, 0, "Segmentation Faults Specialist", true, Normal);
    PrintText(CreditLeft, 2, 0, "Agus Gunawan", true, Normal);
    Pause(500);

    PrintText(CreditLeft, 5, 0, "Professional Stack Smasher", true, Normal);
    PrintText(CreditLeft, 7, 0, "Felix Limanta", true, Normal);
    Pause(500);

    PrintText(CreditLeft, 10, 0, "Undefined References Referencer", true, Normal);
    PrintText(CreditLeft, 12, 0, "Holy Lovenia", true, Normal);
    Pause(500);

    PrintText(CreditLeft, 15, 0, "Waifu Plot Maker", true, Normal);
    PrintText(CreditLeft, 17, 0, "Oktavianus Handika", true, Normal);
    Pause(500);

    PrintText(CreditLeft, 20, 0, "NCurses Curser", true, Normal);
    PrintText(CreditLeft, 22, 0, "Rionaldi Chandraseta", true, Normal);
    Pause(500);

    // Phase 3
    PrintText(CreditCentral, 9, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 1, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);

    PrintText(CreditCentral, 1, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "                     AWARDS                     ", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 9, 0, "                                                ", true, SuperFast);
    Pause(500);

    PrintText(CreditRight, 0, 0, "Most Lines Coded (3000+)", true, Normal);
    PrintText(CreditRight, 2, 0, "Rionaldi Chandraseta", true, Normal);
    Pause(500);

    PrintText(CreditRight, 5, 0, "Most Multi-lingual Terminal (4)", true, Normal);
    PrintText(CreditRight, 7, 0, "Holy Lovenia", true, Normal);
    Pause(500);

    PrintText(CreditRight, 10, 0, "Most Segmentation Fault (200+)", true, Normal);
    PrintText(CreditRight, 12, 0, "Agus Gunawan", true, Normal);
    Pause(500);

    PrintText(CreditRight, 15, 0, "Most Increased Workload Curve (2^n)", true, Normal);
    PrintText(CreditRight, 17, 0, "Felix Limanta", true, Normal);
    Pause(500);

    PrintText(CreditRight, 20, 0, "Most Decreased Workload Curve (2^(-n))", true, Normal);
    PrintText(CreditRight, 22, 0, "Oktavianus Handika", true, Normal);
    Pause(500);

    // Phase 4
    PrintText(CreditCentral, 9, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 1, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);

    PrintText(CreditCentral, 1, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "                 SPECIAL THANKS                 ", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 9, 0, "                                                ", true, SuperFast);
    Pause(500);

    PrintText(CreditBottom, 2, 0, "Special Thanks to", true, Normal);
    Pause(500);
    PrintText(CreditBottom, 5, 0, "William Sentosa", true, Normal);
    PrintText(CreditBottom, 6, 0, "Jordhy Fernando", true, Normal);

    // Phase 5
    PrintText(CreditCentral, 1, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 9, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 10,0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    PrintText(CreditCentral, 11,0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, SuperFast);
    wborder(CreditCentral, ' ', ' ', ' ',' ',' ',' ',' ',' ');

    PrintText(CreditCentral, 1, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "                                     @@@ @@@    ", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "                                    @   @   @   ", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "                                    @       @   ", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "       Thanks for Playing!           @     @    ", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "                                      @   @     ", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "                                       @ @      ", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "                                        @       ", true, SuperFast);
    PrintText(CreditCentral, 9, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 10,0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 11,0, "                                                ", true, SuperFast);
    Pause(500);

    PrintText(CreditCentral, 1, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "                                     @@@ @@@    ", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "                                    @@@@@@@@@   ", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "                                    @@@@@@@@@   ", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "       Thanks for Playing!           @@@@@@@    ", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "                                      @@@@@     ", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "                                       @@@      ", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "                                        @       ", true, SuperFast);
    PrintText(CreditCentral, 9, 0, "                                                ", true, SuperFast);

    PrintText(CreditCentral, 1, 0, "                                                ", true, SuperFast);
    PrintText(CreditCentral, 2, 0, "                                     @@@ @@@    ", true, SuperFast);
    PrintText(CreditCentral, 3, 0, "                                    @@ @@@ @@   ", true, SuperFast);
    PrintText(CreditCentral, 4, 0, "                                    @ @ @ @ @   ", true, SuperFast);
    PrintText(CreditCentral, 5, 0, "       Thanks for Playing!           @ @ @ @    ", true, SuperFast);
    PrintText(CreditCentral, 6, 0, "                                      @ @ @     ", true, SuperFast);
    PrintText(CreditCentral, 7, 0, "                                       @ @      ", true, SuperFast);
    PrintText(CreditCentral, 8, 0, "                                        @       ", true, SuperFast);
    PrintText(CreditCentral, 9, 0, "                                                ", true, SuperFast);

    PrintText(CreditCentral, 7, 0, "                 -Team Luvdisc         @ @      ", true, SuperSlow);
    Pause(2000);


    WINDOW* Notification = newwin(3, 26, MaxY-5, (MaxX-26)/2);
    wbkgd(Notification, COLOR_PAIR(4));
    PrintText(Notification, 2, 2, "Press any key to return", false, Normal);

    chtype ch = wgetch(win);

    // CLEANUP
    DeleteWindow(CreditCentral);
    DeleteWindow(Credit1);
    DeleteWindow(Credit2);
    DeleteWindow(Credit3);
    DeleteWindow(Credit4);
    DeleteWindow(Credit5);
    DeleteWindow(CreditLeft);
    DeleteWindow(CreditRight);
    DeleteWindow(CreditBottom);
    DeleteWindow(Notification);
}
