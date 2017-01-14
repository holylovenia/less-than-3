// COMPILER
// gcc array.c assignment.c basestats.c battle.c bintree.c character.c general.c grafarea.c listrek.c map.c matriks.c mesinkar.c mesinkata.c point.c queue.c saveload.c skilltree.c stackt.c statistic.c interface.c mainmenu.c gameui.c saveindex.c waktu.c dmainmenu.c -lm -lncurses -o dmainmenu

// 16 COLOR
// #04252e:#A31929:#00b159:#ffc425:#3b5998:#F799B5:#66cccc:#94a3a5:#46585D:#dc322f:#329f69:#ffca66:#268bd2:#F799B5:#7FC6C1:#ffffff


#include <ncurses.h>

#include "../../Modul/Interface/interface.h"
#include "../../ADT/Main_Menu/mainmenu.h"
#include "../../Modul/Game_UI/gameui.h"

int main() {

    Menu MM;
    boolean Start;

    Start = true;
    InitializeMenu(&MM);

    LoadMainMenu(&MM, &Start);

    endwin();
    return 0;
}
