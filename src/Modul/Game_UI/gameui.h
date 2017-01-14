#ifndef gameui_h
#define gameui_h

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "../../Modul/Interface/interface.h"

#include "../../ADT/Basestats/basestats.h"
#include "../../ADT/Array/array.h"
#include "../../ADT/Assignment/assignment.h"
#include "../../ADT/Boolean/boolean.h"
#include "../../ADT/Binary_Tree/bintree.h"
#include "../../Modul/Battle/battle.h"
#include "../../ADT/Character/character.h"
#include "../../ADT/General/general.h"
#include "../../ADT/Graf/grafarea.h"
#include "../../ADT/List_Rekursif/listrek.h"
#include "../../ADT/Map/map.h"
#include "../../ADT/Matriks/matriks.h"
#include "../../ADT/Mesin_Kar/mesinkar.h"
#include "../../ADT/Mesin_Kata/mesinkata.h"
#include "../../ADT/Point/point.h"
#include "../../ADT/Queue/queue.h"
#include "../../Modul/Save_Load/saveload.h"
#include "../../Modul/Skill_Tree/skilltree.h"
#include "../../ADT/Stack/stackt.h"
#include "../../Modul/Statistic/statistic.h"

void OpeningCutscene (boolean isNewPlayer);
// I.S.: isNewPlayer value defined
// F.S.: Cinematic dialogue played on-screen.
        //  A full cinematic dialogue for new players
        //  A short flashback cinematic if the player loads game

void ClosingCutscene (WINDOW* win);
// I.S.: win defined and allocated
// F.S.: Cinematic closing dialogue for player that has defeated the queen.

void GameMapControl (POINT* POS_Player, addressarea P, POINTOFENEMY E[MaxMap+1]);
// I.S.: Everything defined.
// F.S.: Player will return to main menu. Either:
//       1. Reached game over.
//       2. Defeated the queen.
//       3. Chose to return to menu.

void GameBattleControl (Enemy E, boolean * isWin);
// I.S.: In Battle Mode, win defined and allocated
// F.S.: Draw battle interface on screen.

#endif
