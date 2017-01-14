// COMPILE
// gcc matriks.c dmatriks.c -o dmatriks.c -lncurses

#include "matriks.h"

#define NRMax 10
#define NCMax 10

int main() {
    MATRIKS M1, M2;
    char buffer;

    // Initialize Matrix
    MakeMATRIKS (NRMax, NCMax, &M1);

    // Initialize ncurses
    initscr();
    noecho();
    curs_set(false);

    // Create windows for ncurses
    WINDOW* Comment = newwin(10, 60, 6, 92);
    wrefresh(Comment);

    WINDOW* TestWin = newwin(31, 81, 4, 8);
    box(TestWin, 0, 0);
    wrefresh(TestWin);

    // Fill Matrix with walls
    for (int i=1; i<=NRMax; i++) {
        for (int j=1; j<=NCMax; j++) {
            Elmt(M1, i, j) = '#';
        }
    }

    // Print Matrix
    wprintw(Comment, "Print Matrix 1\n");
    wprintw(Comment, "Press any key to continue.");
    wrefresh(Comment);

    TulisMATRIKS(TestWin, M1, 5, 5);
    wrefresh(TestWin);

    buffer = wgetch(Comment);

    // Clear Windows
    wclear(TestWin);
    wrefresh(TestWin);
    wclear(Comment);
    wprintw(Comment, "Cleared window, press any key to continue.");
    wrefresh(Comment);

    buffer = wgetch(Comment);
    wclear(Comment);

    // Print Matrix Copy
    CopyMATRIKS(M1, &M2);
    wprintw(Comment, "Print Matrix Copy\n");
    wprintw(Comment, "Press any key to continue.");
    wrefresh(Comment);

    box(TestWin, 0, 0);
    TulisMATRIKS(TestWin, M2, 5, 5);
    wrefresh(TestWin);

    buffer = wgetch(Comment);

    // End ncurses
    endwin();
    return 0;
}