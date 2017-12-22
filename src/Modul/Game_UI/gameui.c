#include <ncurses.h>

#include "../../Modul/Interface/interface.h"
#include "../../Modul/Game_UI/gameui.h"

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
#include "../../ADT/Save_Index/saveindex.h"
#include "../../Modul/Save_Load/saveload.h"
#include "../../Modul/Skill_Tree/skilltree.h"
#include "../../ADT/Stack/stackt.h"


// KAMUS GLOBAL
Player player;
int nMedLeft;

BinTree skillTree;
ListLR acquiredSkill;

ListArea listArea;
MATRIKS area[11];
Koneksi con;
POINTOFENEMY enemyLoc[11];
addressarea currMap;
int nCurrMap;

dbBST enemyData;
TabEnemyMap tabEnemy;
POINT posP, posB;


void OpeningCutscene (boolean isNewPlayer)
// I.S.: isNewPlaye value defined
// F.S.: Cinematic dialogue played on-screen.
        //  A full cinematic dialogue for new players
        //  A short flashback cinematic if the player loads game
{
    noecho();
    curs_set(false);

    WINDOW* win = newwin(MaxY, MaxX, 0, 0);
    
    if (isNewPlayer) {
        wbkgd(win, COLOR_PAIR(8));
        wrefresh(win);

        PrintText(win, 17, 0, "Hello?", true, Slow);
        Pause(3000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(7));
        PrintText(win, 17, 0, ". . .", true, SuperSlow);
        Pause(3000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(8));
        PrintText(win, 17, 0, "Are you awake?", true, Slow);
        Pause(3000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(7));
        PrintText(win, 17, 0, ". . .", true, Slow);
        Pause(3000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(8));
        PrintText(win, 17, 0, "Hey!! I'm talking to you!", true, Normal);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(7));
        PrintText(win, 17, 0, "Huh? ...what? What happened?", true, Fast);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(8));
        PrintText(win, 17, 0, "You're blocking my way.", true, Normal);
        Pause(500);
        PrintText(win, 18, 0, "Can't you find somewhere else to sleep?", true, Normal);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(7));
        PrintText(win, 17, 0, "I was sleeping in my bedroom.", true, Normal);
        Pause(500);
        PrintText(win, 18, 0, " Wait, where am I?", true, Normal);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(8));
        PrintText(win, 17, 0, "Oh dear, it's one of the new guys.", true, Normal);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(7));
        PrintText(win, 17, 0, "New guys?", true, Normal);
        Pause(500);
        PrintText(win, 18, 0, "Who are you? Can you tell me about this place?", true, Normal);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(8));
        PrintText(win, 17, 0, "Okay new guy, Rule #1: Don't ask questions.", true, Normal);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(7));
        PrintText(win, 17, 0, "But, who...", true, Normal);
        Pause(500);
        wclear(win);

        wbkgd(win, COLOR_PAIR(8));
        PrintText(win, 17, 0, "Shush, what did I say about Rule #1?", true, Normal);
        Pause(500);
        PrintText(win, 18, 0, "Good god, you men are all the same", true, Normal);
        Pause(2000);
        wclear(win);
        PrintText(win, 17, 0, "Just stay quiet and listen to me, new guy.", true , Normal);
        Pause(500);
        PrintText(win, 18, 0, "I'll explain what's happening right now.", true, Normal);
        Pause(2000);
        wclear(win);

        PrintText(win, 10, 0, "Okay, so now you're in Romance Realm. Yes, that name is very cliched, we know that.", true, Normal);
        PrintText(win, 11, 0, "By we, I meant the girls of Romance Realm.", true, Normal);
        PrintText(win, 13, 0, "There are no guys in Romance Realm, which is why we usually abduct one from your world.", true, Normal);
        PrintText(win, 14, 0, "Yeah, you're not the only one from your world here, but you can't see each other.", true, Normal);
        PrintText(win, 15, 0, "That's a good thing right? You have more time to look at us.", true, Normal);
        PrintText(win, 17, 0, "Okay, so now you have two options.", true, Normal);
        PrintText(win, 18, 0, "First, you could stay here forever -- away from your boring life, surrounded by pretty girls.", true, Normal);
        PrintText(win, 19, 0, "Second, you could technically go back to your world. To do that, you need to defeat the Queen.", true, Normal);
        PrintText(win, 20, 0, "She's the most powerful and beautiful woman in this Realm. She could bring you back.", true, Normal);
        PrintText(win, 22, 0, "You need to defeat her before she'd help you, though.", true, Normal);
        PrintText(win, 24, 0, "That's about it. You just had to choose: stay, or try to leave.", true, Normal);
        PrintText(win, 25, 0, "Oh, and if any one of the girls managed to allure you, you won't be able to go back at all.", true, Normal);
        Pause(500);
        PrintText(win, 27, 0, "Simple, right?", true, Normal);
        Pause(1000);
        wclear(win);

        PrintText(win, 17, 0, "Did you get all that?", true, Normal);
        Pause(1000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(7));
        PrintText(win, 17, 0, "What the...? I still can't understand half of what you said.", true, Normal);
        Pause(500);
        PrintText(win, 18, 0, "Could you repeat that, please?", true, Normal);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(8));
        PrintText(win, 17, 0, "Tch, you're wasting my time! Here, take this note with you.", true, Normal);
        Pause(500);
        PrintText(win, 18, 0, "Everything you need is in there.", true, Normal);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(7));
        PrintText(win, 17, 0, "Huh? Oh, thanks Miss.", true, Normal);
        Pause(500);
        PrintText(win, 18, 0, "Wait, can you tell me your name?", true, Normal);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(8));
        PrintText(win, 17, 0, "My name is Aphrodite. I'm sure we'll meet again.", true, Normal);
        Pause(500);
        PrintText(win, 18, 0, "I gotta go. Smell ya later, new guy.", true, Normal);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(7));
        PrintText(win, 17, 0, "Hey, wait!", true, Slow);
        Pause(2000);
        wclear(win);

        wbkgd(win, COLOR_PAIR(1));
        PrintText(win, 17, 0, "She left behind a faint, yet pleasant scent as she walked away.", true, Normal);
        wrefresh(win);
        Pause(2000);
    }
    else {
        wbkgd(win, COLOR_PAIR(1));
        PrintText(win, 16, 0, "You are still in the Romance Realm.", true, Slow);
        PrintText(win, 17, 0, "You have lost track of time, and you have yet to defeat the Queen.", true, Slow);
        Pause(1000);
        PrintText(win, 19, 0, "And so continues your journey...", true, Slow);
        Pause(1000);
    }

    DeleteWindow(win);
}

void ClosingCutscene (WINDOW* win)
// I.S.: win defined and allocated
// F.S.: Cinematic closing dialogue for player that has defeated the queen.
{
    noecho();
    curs_set(false);

    wbkgd(win, COLOR_PAIR(8));
    PrintText(win, 17, 0, ". . .", true, SuperSlow);
    Pause(3000);

    PrintText(win, 17, 0, "You've actually beaten me...", true, Slow);
    Pause(3000);
    wclear(win);

    PrintText(win, 17, 0, "I know there's something different about you when I first saw you.", true, Slow);
    Pause(3000);
    wclear(win);

    PrintText(win, 17, 0, "I, Aphrodite, the Queen of Romance Realm admit my defeat.", true, Slow);
    Pause(500);
    PrintText(win, 19, 0, "Take my hand. I'll bring you back to your world.", true, Slow);
    Pause(3000);
    wclear(win);

    wbkgd(win, COLOR_PAIR(7));
    PrintText(win, 17, 0, ". . .", true, SuperSlow);
    Pause(3000);
    wclear(win);

    wbkgd(win, COLOR_PAIR(8));
    PrintText(win, 17, 0, "Hey, are you listening to me? Come on, give me your hand.", true, Slow);
    Pause(3000);
    wclear(win);
    Pause(3000);

    wbkgd(win, COLOR_PAIR(6));
    PrintText(win, 17, 0, "You grabbed her hands and found yourself waking up in your bed.", true, Slow);
    Pause(500);
    PrintText(win, 19, 0, "Did you actually go to the Romance Realm? Or was that all just an oddly vivid dream?", true, Slow);
    Pause(2000);
    wclear(win);

    Pause(2000);
    PrintText(win, 17, 0, "You found an envelope sitting on your bedside table.", true, Slow);
    Pause(500);
    PrintText(win, 19, 0, "As you opened it, you found a tantalizingly familiar scent.", true, Slow);
    Pause(2000);
    wclear(win);

    wbkgd(win, COLOR_PAIR(1));
    PrintText(win, 15, 0, "Hey, new guy. Nice work for beating me back then.", true, Normal);
    PrintText(win, 16, 0, "I suppose beginner's luck really does exist.", true, Normal);
    PrintText(win, 18, 0, "Come visit me again sometime. I promise you won't defeat me that easily again.", true, Normal);
    PrintText(win, 19, 0, "Just think of me before you go to sleep and I'll bring you back here.", true, Normal);

    PrintText(win, 21, 0, "                                    <3 -A ", true, Normal);
    Pause(5000);
    wclear(win);
}

void PlayerStat (WINDOW* win)
// I.S. : In exwin defined and allocated
// F.S. : Draw Player Stat on side-screen
{
    wclear(win);
    box(win, 0, 0);
    if (HP(player) > (HPMAXPlayer(player)/2)) {
        wbkgd(win, COLOR_PAIR(3));
    }
    else {
        if (HP(player) > (HPMAXPlayer(player)/5)) {
            wbkgd(win, COLOR_PAIR(4));
        }
        else {
            wbkgd(win, COLOR_PAIR(2));
        }
    }

    PrintText(win, 2, 4, "Name  :", false, Normal);
    PrintText(win, 2, 12, NAMA(player), false, Normal);

    PrintText(win, 3, 4, "Level :", false, Normal);
    mvwprintw(win, 3, 12, "%d", LV(player));

    mvwhline(win, 5, 0, ACS_LTEE, 1);
    mvwhline(win, 5, 1, 0, 38);
    mvwhline(win, 5, 39, ACS_RTEE, 1);

    PrintText(win, 7, 4, "HP  =", false, Normal);
    mvwprintw(win, 7, 11, "%d / %d", HP(player), HPMAXPlayer(player));

    PrintText(win, 9, 4, "EXP =", false, Normal);
    mvwprintw(win, 9, 11, "%d / %d", EXP(player), EXPLimit(player));
    wrefresh(win);
}

void DrawMap (WINDOW* win)
// I.S.: In exploration mode, win defined and allocated (81x31)
// F.S.: Draw Map of the Game on the screen
{
    box(win, 0, 0);
    for (int row = 1; row < MapSize; row++) {
        mvwhline(win, row*MapRowMultiplier, 0, ACS_LTEE, 1);
        mvwhline(win, row*MapRowMultiplier, 1, 0, MapSize*MapColumnMultiplier);
        mvwhline(win, row*MapRowMultiplier, (MapSize*MapColumnMultiplier), ACS_RTEE, 1);
    }

    for (int col = 1; col < MapSize; col++) {
        mvwvline(win, 0, col*MapColumnMultiplier, ACS_TTEE, 1);
        mvwvline(win, 1, col*MapColumnMultiplier, 0, MapSize*MapRowMultiplier);
        mvwvline(win, (MapSize*MapRowMultiplier), col*MapColumnMultiplier, ACS_BTEE, 1);
    }

    for (int row = 1; row < MapSize; row++) {
        for(int col = 1; col < MapSize; col++) {
            mvwhline(win, row*MapRowMultiplier, col*MapColumnMultiplier, ACS_PLUS, 1);
        }
    }
    wrefresh(win);
}

//void SkillTreeManager (WINDOW* win)

void RestoreMapView (WINDOW* BG, WINDOW* Stat, WINDOW* Extra, WINDOW* Map, WINDOW* AlertATR, WINDOW* AlertSKL)
// I.S.: Fresh from battle mode
// F.S.: Map view restored
{
    box(BG, 0, 0);
    wrefresh(BG);

    box(Extra, 0, 0);
    mvwprintw(Extra, 2, 4, "Control");
    mvwprintw(Extra, 5, 6, "WASD - Move");
    mvwprintw(Extra, 7, 6, "V - Skill Tree");
    mvwprintw(Extra, 9, 6, "B - Player Attribute");
    mvwprintw(Extra, 11,6, "N - Note");
    mvwprintw(Extra, 13,6, "M - Menu");
    wrefresh(Extra);

    wclear(Stat);
    box(Stat, 0, 0);
    if (HP(player) > (HPMAXPlayer(player)/2)) {
        wbkgd(Stat, COLOR_PAIR(3));
    }
    else {
        if (HP(player) > (HPMAXPlayer(player)/5)) {
            wbkgd(Stat, COLOR_PAIR(4));
        }
        else {
            wbkgd(Stat, COLOR_PAIR(2));
        }
    }

    mvwprintw(Stat, 2, 4, "Name  :");
    mvwprintw(Stat, 2, 12, NAMA(player));

    mvwprintw(Stat, 3, 4, "Level :");
    mvwprintw(Stat, 3, 12, "%d", LV(player));

    mvwhline(Stat, 5, 0, ACS_LTEE, 1);
    mvwhline(Stat, 5, 1, 0, 38);
    mvwhline(Stat, 5, 39, ACS_RTEE, 1);

    mvwprintw(Stat, 7, 4, "HP  =");
    mvwprintw(Stat, 7, 11, "%d / %d", HP(player), HPMAXPlayer(player));

    mvwprintw(Stat, 9, 4, "EXP =");
    mvwprintw(Stat, 9, 11, "%d / %d", EXP(player), EXPLimit(player));
    wrefresh(Stat);

    wbkgd(Map, COLOR_PAIR(1));
    DrawMap(Map);

    mvwprintw(AlertATR, 1, 2, "ATR");
    wrefresh(AlertATR);

    mvwprintw(AlertSKL, 1, 2, "SKL");
    wrefresh(AlertSKL);
}

void PrintControl (WINDOW* win)
// I.S.: win defined and allocated
// F.S.: Print map control in win
{
    PrintText(win, 2, 4, "Control", false, Fast);
    PrintText(win, 5, 6, "WASD - Move", false, Fast);
    PrintText(win, 7, 6, "V - Skill Tree", false, Fast);
    PrintText(win, 9, 6, "B - Player Attribute", false, Fast);
    PrintText(win, 11,6, "N - Note", false, Fast);
    PrintText(win, 13,6, "M - Menu", false, Fast);
}

void TriggerEvent(WINDOW* window, addressarea P, POINT PosPlayer, char * contentBefore, int * result, boolean* takeMedicine) {
    // KAMUS
    *takeMedicine = false;
    int currMapIdx = IndeksMap(InfoMap(P)), i = 1;
    boolean win;
    Enemy enemy;

    // ALGORITMA
    if ((*contentBefore == 'E') || (*contentBefore == 'B')) {
        while ((Absis(PosPlayer) != Absis(Pos(tabEnemy,currMapIdx,i))) && (Ordinat(PosPlayer) != Ordinat(Pos(tabEnemy,currMapIdx,i)))) i++;
        if (*contentBefore == 'E') {
            CreateEnemy(player,&enemy,Name(tabEnemy,currMapIdx,i),enemyData);
        } else if (*contentBefore == 'B') {
            CreateEnemy(player,&enemy,NAMA(basestats(enemyData,dbBST_BossIndex(enemyData))),enemyData);
            //CreateEnemy(player,&enemy,"Aphrodite",enemyData);
        }
        for (int i=0; i<=(MapRowMultiplier*MapSize); i++) {
            PrintText(window, i, 0, "                                                                                 ", true, SuperFast);
            if (i%3 == 0) {
                wbkgd(window, COLOR_PAIR(2));
            }
            else {
                wbkgd(window, COLOR_PAIR(1));
            }
        }
        GameBattleControl(enemy, &win);
        if (win) {
            *result = 1 + (*contentBefore == 'B');
            *contentBefore = '.';
        } else {
            *result = -(HP(player) == 0);
        }
    } else if (*contentBefore == 'M') {
        HP(player) = HPMAXPlayer(player);
        *takeMedicine = true;
        nMedLeft--;
        *contentBefore = '.';
    }
}

void GameMapControl (POINT* POS_Player, addressarea P, POINTOFENEMY E[MaxMap+1])
// I.S.: Everything defined.
// F.S.: Player will return to main menu. Either:
//       1. Reached game over.
//       2. Defeated the queen.
//       3. Chose to return to menu.
{
    WINDOW* Background = CreateWindow(MaxY, MaxX, 0, 0);
    wbkgd(Background, COLOR_PAIR(1));
    wrefresh(Background);

    WINDOW* Stat = CreateWindow(12, 40, 4, 8);
    wrefresh(Stat);
    PlayerStat(Stat);
    Pause(1000);

    WINDOW* Map = CreateWindow(31, 81, 4, 60);
    wbkgd(Map, COLOR_PAIR(1));
    DrawMap(Map);
    TulisMATRIKS(Map, Map(P), Absis(*POS_Player), Ordinat(*POS_Player));
    wrefresh(Map);
    Pause(500);

    WINDOW* Extra = CreateWindow(18, 40, 17, 8);
    wbkgd(Extra, COLOR_PAIR(6));
    wrefresh(Extra);
    PrintControl(Extra);

    WINDOW* AlertATR = CreateWindow(3, 7, 4, 147);
    wbkgd(AlertATR, COLOR_PAIR(5));
    mvwprintw(AlertATR, 1, 2, "ATR");
    wrefresh(AlertATR);

    WINDOW* AlertSKL = CreateWindow(3, 7, 8, 147);
    wbkgd(AlertSKL, COLOR_PAIR(5));
    mvwprintw(AlertSKL, 1, 2, "SKL");
    wrefresh(AlertSKL);

    chtype cmd = '0';

    boolean MapMode = true;

    int brs,kol;
    char command, contentBefore = ' ';
    boolean takeMedicine;
    int i,j, result = 1; // 1 normal , 0 draw (sementara, langsung jadi 1), -1 kalah -> Game Over
    POINT LocBefore;
    int PrevHP = HP(player);

    while ((MapMode) && (result >= 0) && (result < 2)) {

        nCurrMap = IndeksMap(InfoMap(P));
        if (AP(player) > 0) {
            wbkgd(AlertATR, COLOR_PAIR(1));
        }
        else {
            wbkgd(AlertATR, COLOR_PAIR(5));
        }
        wrefresh(AlertATR);

        if (SP(player) > 0) {
            wbkgd(AlertSKL, COLOR_PAIR(1));
        }
        else {
            wbkgd(AlertSKL, COLOR_PAIR(5));
        }
        wrefresh(AlertSKL);

        TulisMATRIKS(Map, Map(P), Absis(*POS_Player), Ordinat(*POS_Player));
        LocBefore = MakePOINT(Absis(*POS_Player),Ordinat(*POS_Player));

        cmd = wgetch(Map);

        if ((cmd == 'w') || (cmd == 'W') || (cmd == 's') || (cmd == 'S') || (cmd == 'a') || (cmd == 'A') || (cmd == 'd') || (cmd == 'D')) {
            if ((cmd == 'w') || (cmd == 'W')) {
                if (Elmt(Map(P),Ordinat(*POS_Player)-1,Absis(*POS_Player)) != '#') {
                    if (Ordinat(*POS_Player)-1 < GetFirstIdxBrs(Map(P)) ) {
                        if ( Neighbor(P)[1] != Nil) {
                            Absis(*POS_Player) = Absis(GateArrived(InfoMap(P))[1]);
                            Ordinat(*POS_Player) = Ordinat(GateArrived(InfoMap(P))[1]);
                            LoadEnemy(E,&InfoMap(P));
                            P = Neighbor(P)[1];
                        }
                    } else {
                        contentBefore = Elmt(Map(P),Ordinat(*POS_Player) - 1, Absis(*POS_Player));
                        if(Elmt(Map(P),Ordinat(*POS_Player) - 1, Absis(*POS_Player)) == 'E' || Elmt(Map(P),Ordinat(*POS_Player) - 1, Absis(*POS_Player)) == 'M')  {
                            Elmt(Map(P),Ordinat(*POS_Player) - 1, Absis(*POS_Player)) = '.';
                        }
                        Ordinat(*POS_Player)--;
                    }
                }
            }
            else if ((cmd == 's') || (cmd == 'S')) {
                if (Elmt(Map(P),Ordinat(*POS_Player) + 1, Absis(*POS_Player)) != '#') {
                    if (Ordinat(*POS_Player)+1 > GetLastIdxBrs(Map(P)) ) {
                        if ( Neighbor(P)[3] != Nil) {
                            Absis(*POS_Player) = Absis(GateArrived(InfoMap(P))[3]);
                            Ordinat(*POS_Player) = Ordinat(GateArrived(InfoMap(P))[3]);
                            LoadEnemy(E,&InfoMap(P));
                            P = Neighbor(P)[3];
                        }
                    } else {
                        contentBefore = Elmt(Map(P),Ordinat(*POS_Player) + 1, Absis(*POS_Player));
                        if(Elmt(Map(P),Ordinat(*POS_Player) + 1, Absis(*POS_Player)) == 'E' || Elmt(Map(P),Ordinat(*POS_Player) + 1, Absis(*POS_Player)) == 'M')  {
                            Elmt(Map(P),Ordinat(*POS_Player) + 1, Absis(*POS_Player)) = '.';
                        }
                        Ordinat(*POS_Player)++;
                    }
                }
            }
            else if ((cmd == 'd') || (cmd == 'D')) {
                if (Elmt(Map(P),Ordinat(*POS_Player),Absis(*POS_Player)+1) != '#') {
                    if (Absis(*POS_Player)+1 > GetLastIdxKol(Map(P)) ) {
                        if ( Neighbor(P)[2] != Nil) {
                            Absis(*POS_Player) = Absis(GateArrived(InfoMap(P))[2]);
                            Ordinat(*POS_Player) = Ordinat(GateArrived(InfoMap(P))[2]);
                            LoadEnemy(E,&InfoMap(P));
                            P = Neighbor(P)[2];
                        }
                    } else {
                        contentBefore = Elmt(Map(P),Ordinat(*POS_Player), Absis(*POS_Player) + 1);
                        if(Elmt(Map(P),Ordinat(*POS_Player), Absis(*POS_Player) + 1) == 'E' || Elmt(Map(P),Ordinat(*POS_Player), Absis(*POS_Player) + 1) == 'M')  {
                            Elmt(Map(P),Ordinat(*POS_Player), Absis(*POS_Player) + 1) = '.';
                        }
                        Absis(*POS_Player)++;
                    }
                }
            }
            else if ((cmd == 'a') || (cmd == 'A')) {
                if (Elmt(Map(P),Ordinat(*POS_Player), Absis(*POS_Player)-1) != '#') {
                    if (Absis(*POS_Player)-1 < GetFirstIdxKol(Map(P)) ) {
                        if ( Neighbor(P)[4] != Nil) {
                            Absis(*POS_Player) = Absis(GateArrived(InfoMap(P))[4]);
                            Ordinat(*POS_Player) = Ordinat(GateArrived(InfoMap(P))[4]);
                            LoadEnemy(E,&InfoMap(P));
                            P = Neighbor(P)[4];
                        }
                    } else {
                        contentBefore = Elmt(Map(P),Ordinat(*POS_Player), Absis(*POS_Player) - 1);
                        if(Elmt(Map(P),Ordinat(*POS_Player), Absis(*POS_Player) - 1) == 'E' || Elmt(Map(P),Ordinat(*POS_Player), Absis(*POS_Player) - 1) == 'M')  {
                            Elmt(Map(P),Ordinat(*POS_Player), Absis(*POS_Player) - 1) = '.';
                        }
                        Absis(*POS_Player)--;
                    }
                }
            }
            // Pengecekan Event
            TriggerEvent(Map, P,*POS_Player,&contentBefore,&result, &takeMedicine);
            if (result == 0) {
                Elmt(Map(P),Ordinat(*POS_Player), Absis(*POS_Player)) = contentBefore;
                *POS_Player = LocBefore;
                result = 1;
            }
            else if (result == (-1)) {
                MapMode = false;
            }

            // Cleanup
            RestoreMapView(Background, Stat, Extra, Map, AlertATR, AlertSKL);
        }
        else if ((cmd == 'v') || (cmd == 'V')) {    // OPEN SKILL
            WINDOW* SkillTreeBG = CreateWindow(31, 81, 4, 60);
            wbkgd(SkillTreeBG, COLOR_PAIR(6));

            // Tree Line
            mvwhline(SkillTreeBG, 7, 22, ACS_ULCORNER, 1);
            mvwhline(SkillTreeBG, 7, 23, 0, 17);
            mvwhline(SkillTreeBG, 7, 40, ACS_BTEE, 1);
            mvwhline(SkillTreeBG, 7, 41, 0, 17);
            mvwhline(SkillTreeBG, 7, 58, ACS_URCORNER, 1);
            mvwvline(SkillTreeBG, 8, 22, 0, 1);
            mvwvline(SkillTreeBG, 8, 58, 0, 1);

            mvwvline(SkillTreeBG, 14, 22, 0, 2);
            mvwvline(SkillTreeBG, 14, 58, 0, 2);

            mvwhline(SkillTreeBG, 21, 13, ACS_ULCORNER, 1);
            mvwhline(SkillTreeBG, 21, 14, 0, 8);
            mvwhline(SkillTreeBG, 21, 22, ACS_BTEE, 1);
            mvwhline(SkillTreeBG, 21, 23, 0, 8);
            mvwhline(SkillTreeBG, 21, 31, ACS_URCORNER, 1);

            mvwhline(SkillTreeBG, 21, 49, ACS_ULCORNER, 1);
            mvwhline(SkillTreeBG, 21, 50, 0, 8);
            mvwhline(SkillTreeBG, 21, 58, ACS_BTEE, 1);
            mvwhline(SkillTreeBG, 21, 59, 0, 8);
            mvwhline(SkillTreeBG, 21, 67, ACS_URCORNER, 1);

            mvwvline(SkillTreeBG, 22, 13, 0, 1);
            mvwvline(SkillTreeBG, 22, 31, 0, 1);
            mvwvline(SkillTreeBG, 22, 49, 0, 1);
            mvwvline(SkillTreeBG, 22, 67, 0, 1);

            wrefresh(SkillTreeBG);

            int choice = 0;
            BinTree ST;
            boolean SkillMode = true;
            boolean JustChosen = false;

            // Skill Windows
            WINDOW* Skill1 = CreateWindow(5, 9, 6, 96);
            SearchID(skillTree, 1, &ST);
            if (Unlocked(Akar(ST))) {
                wbkgd(Skill1, COLOR_PAIR(1));
            }
            else {
                wbkgd(Skill1, COLOR_PAIR(5));
            }
            mvwprintw(Skill1, 2 , 4, "1");
            wrefresh(Skill1);

            WINDOW* Skill2 = CreateWindow(5, 9, 13, 78);
            SearchID(skillTree, 2, &ST);
            if (Unlocked(Akar(ST))) {
                wbkgd(Skill2, COLOR_PAIR(1));
            }
            else {
                wbkgd(Skill2, COLOR_PAIR(5));
            }
            mvwprintw(Skill2, 2, 4, "2");
            wrefresh(Skill2);

            WINDOW* Skill3 = CreateWindow(5, 9, 13, 114);
            SearchID(skillTree, 3, &ST);
            if (Unlocked(Akar(ST))) {
                wbkgd(Skill3, COLOR_PAIR(1));
            }
            else {
                wbkgd(Skill3, COLOR_PAIR(5));
            }
            mvwprintw(Skill3, 2, 4, "3");
            wrefresh(Skill3);

            WINDOW* Skill4 = CreateWindow(5, 9, 20, 78);
            SearchID(skillTree, 4, &ST);
            if (Unlocked(Akar(ST))) {
                wbkgd(Skill4, COLOR_PAIR(1));
            }
            else {
                wbkgd(Skill4, COLOR_PAIR(5));
            }
            mvwprintw(Skill4, 2, 4, "4");
            wrefresh(Skill4);

            WINDOW* Skill5 = CreateWindow(5, 9, 20, 114);
            SearchID(skillTree, 5, &ST);
            if (Unlocked(Akar(ST))) {
                wbkgd(Skill5, COLOR_PAIR(1));
            }
            else {
                wbkgd(Skill5, COLOR_PAIR(5));
            }
            mvwprintw(Skill5, 2, 4, "5");
            wrefresh(Skill5);

            WINDOW* Skill6 = CreateWindow(5, 9, 27, 69);
            SearchID(skillTree, 6, &ST);
            if (Unlocked(Akar(ST))) {
                wbkgd(Skill6, COLOR_PAIR(1));
            }
            else {
                wbkgd(Skill6, COLOR_PAIR(5));
            }
            mvwprintw(Skill6, 2, 4, "6");
            wrefresh(Skill6);

            WINDOW* Skill7 = CreateWindow(5, 9, 27, 87);
            SearchID(skillTree, 7, &ST);
            if (Unlocked(Akar(ST))) {
                wbkgd(Skill7, COLOR_PAIR(1));
            }
            else {
                wbkgd(Skill7, COLOR_PAIR(5));
            }
            mvwprintw(Skill7, 2, 4, "7");
            wrefresh(Skill7);

            WINDOW* Skill8 = CreateWindow(5, 9, 27, 105);
            SearchID(skillTree, 8, &ST);
            if (Unlocked(Akar(ST))) {
                wbkgd(Skill8, COLOR_PAIR(1));
            }
            else {
                wbkgd(Skill8, COLOR_PAIR(5));
            }
            mvwprintw(Skill8, 2, 4, "8");
            wrefresh(Skill8);

            WINDOW* Skill9 = CreateWindow(5, 9, 27, 123);
            SearchID(skillTree, 9, &ST);
            if (Unlocked(Akar(ST))) {
                wbkgd(Skill9, COLOR_PAIR(1));
            }
            else {
                wbkgd(Skill9, COLOR_PAIR(5));
            }
            mvwprintw(Skill9, 2, 4, "9");
            wrefresh(Skill9);

            WINDOW* Confirm = newwin(4, 38, 30, 9);
            WINDOW* ExtraDesc = newwin(13, 36, 20, 10);

            // Change Extra Window
            wclear(Extra);
            box(Extra,0,0);
            wbkgd(Extra, COLOR_PAIR(1));
            wrefresh(Extra);


            // Print Control Help
            PrintText(Extra, 2, 0, "Player Skill", true, Normal);
            if (SkillMode) {
                if (SP(player) > 1) {
                    PrintText(Extra, 5, 4, "Skill Points:", false, Normal);
                }
                else {
                    PrintText(Extra, 5, 4, "Skill Point :", false, Normal);
                }
                mvwprintw(Extra, 5, 19, "%d", SP(player));
            }
            PrintText(Extra, 7, 4, "Control", false, Fast);
            PrintText(Extra, 8, 6, "1-9 - Choose Skill", false, Normal);
            if (SP(player) > 0) {
                PrintText(Extra, 9, 6, "Enter - Unlock Skill", false, Normal);
                PrintText(Extra, 10,6, "Q - Return", false, Normal);
            }
            else {
                PrintText(Extra, 9, 6, "Q - Return", false, Normal);
            }

            while (SkillMode) {
                // Refresh skill tree color
                if (choice != 1) {
                    SearchID(skillTree, 1, &ST);
                    if (Unlocked(Akar(ST))) {
                        wbkgd(Skill1, COLOR_PAIR(1));
                    }
                    else {
                        wbkgd(Skill1, COLOR_PAIR(5));
                    }
                    wrefresh(Skill1);
                }
                if (choice != 2) {
                    SearchID(skillTree, 2, &ST);
                    if (Unlocked(Akar(ST))) {
                        wbkgd(Skill2, COLOR_PAIR(1));
                    }
                    else {
                        wbkgd(Skill2, COLOR_PAIR(5));
                    }
                    wrefresh(Skill2);
                }
                if (choice != 3) {
                    SearchID(skillTree, 3, &ST);
                    if (Unlocked(Akar(ST))) {
                        wbkgd(Skill3, COLOR_PAIR(1));
                    }
                    else {
                        wbkgd(Skill3, COLOR_PAIR(5));
                    }
                    wrefresh(Skill3);
                }
                if (choice != 4) {
                    SearchID(skillTree, 4, &ST);
                    if (Unlocked(Akar(ST))) {
                        wbkgd(Skill4, COLOR_PAIR(1));
                    }
                    else {
                        wbkgd(Skill4, COLOR_PAIR(5));
                    }
                    wrefresh(Skill4);
                }
                if (choice != 5) {
                    SearchID(skillTree, 5, &ST);
                    if (Unlocked(Akar(ST))) {
                        wbkgd(Skill5, COLOR_PAIR(1));
                    }
                    else {
                        wbkgd(Skill5, COLOR_PAIR(5));
                    }
                    wrefresh(Skill5);
                }
                if (choice != 6) {
                    SearchID(skillTree, 6, &ST);
                    if (Unlocked(Akar(ST))) {
                        wbkgd(Skill6, COLOR_PAIR(1));
                    }
                    else {
                        wbkgd(Skill6, COLOR_PAIR(5));
                    }
                    wrefresh(Skill6);
                }
                if (choice != 7) {
                    SearchID(skillTree, 7, &ST);
                    if (Unlocked(Akar(ST))) {
                        wbkgd(Skill7, COLOR_PAIR(1));
                    }
                    else {
                        wbkgd(Skill7, COLOR_PAIR(5));
                    }
                    wrefresh(Skill7);
                }
                if (choice != 8) {
                    SearchID(skillTree, 8, &ST);
                    if (Unlocked(Akar(ST))) {
                        wbkgd(Skill8, COLOR_PAIR(1));
                    }
                    else {
                        wbkgd(Skill8, COLOR_PAIR(5));
                    }
                    wrefresh(Skill8);
                }
                if (choice != 9) {
                    SearchID(skillTree, 9, &ST);
                    if (Unlocked(Akar(ST))) {
                        wbkgd(Skill9, COLOR_PAIR(1));
                    }
                    else {
                        wbkgd(Skill9, COLOR_PAIR(5));
                    }
                    wrefresh(Skill9);
                }

                // Print control help
                if (JustChosen) {
                    wclear(Extra);
                    wclear(ExtraDesc);
                    box(Extra, 0, 0);
                    wrefresh(Extra);
                    wrefresh(ExtraDesc);
                    mvwprintw(Extra, 2, 14, "Player Skill");
                    if (SP(player) > 1) {
                        mvwprintw(Extra, 5, 4, "Skill Points:");
                    }
                    else {
                        mvwprintw(Extra, 5, 4, "Skill Point :");
                    }
                    mvwprintw(Extra, 5, 19, "%d", SP(player));
                    mvwprintw(Extra, 7, 4, "Control");
                    mvwprintw(Extra, 8, 6, "1-9 - Choose Skill");
                    if (SP(player) > 0) {
                        mvwprintw(Extra, 9, 6, "Enter - Unlock Skill");
                        mvwprintw(Extra, 10,6, "Q - Return");
                    }
                    else {
                        mvwprintw(Extra, 9, 6, "Q - Return");
                    }
                    JustChosen = false;
                }

                // Read input
                char sp = wgetch(Extra);

                // Clean window
                wclear(Confirm);
                wrefresh(Confirm);

                // Highlight selection
                if (sp == '1') {
                    wbkgd(Skill1, COLOR_PAIR(4));
                    wrefresh(Skill1);
                    choice = 1;
                }
                else if (sp == '2') {
                    wbkgd(Skill2, COLOR_PAIR(4));
                    wrefresh(Skill2);
                    choice = 2;
                }
                else if (sp == '3') {
                    wbkgd(Skill3, COLOR_PAIR(4));
                    wrefresh(Skill3);
                    choice = 3;
                }
                else if (sp == '4') {
                    wbkgd(Skill4, COLOR_PAIR(4));
                    wrefresh(Skill4);
                    choice = 4;
                }
                else if (sp == '5') {
                    wbkgd(Skill5, COLOR_PAIR(4));
                    wrefresh(Skill5);
                    choice = 5;
                }
                else if (sp == '6') {
                    wbkgd(Skill6, COLOR_PAIR(4));
                    wrefresh(Skill6);
                    choice = 6;
                }
                else if (sp == '7') {
                    wbkgd(Skill7, COLOR_PAIR(4));
                    wrefresh(Skill7);
                    choice = 7;
                }
                else if (sp == '8') {
                    wbkgd(Skill8, COLOR_PAIR(4));
                    wrefresh(Skill8);
                    choice = 8;
                }
                else if (sp == '9') {
                    wbkgd(Skill9, COLOR_PAIR(4));
                    wrefresh(Skill9);
                    choice = 9;
                }

                // Description color (based on the status of Skill)
                if ((sp == '1') || (sp == '2') || (sp == '3') || (sp == '4') || (sp == '5') || (sp == '6') || (sp == '7') || (sp == '8') || (sp == '9')) {
                    SearchID(skillTree, choice, &ST);
                    if (Unlocked(Akar(ST))) {
                        wbkgd(ExtraDesc, COLOR_PAIR(1));
                    }
                    else {
                        wbkgd(ExtraDesc, COLOR_PAIR(6));
                    }

                    wclear(Extra);
                    box(Extra, 0, 0);

                    wclear(ExtraDesc);
                    wrefresh(ExtraDesc);

                    PrintText(Extra, 2, 0, NamaBT(Akar(ST)), true, MaxSpeed);
                    wprintw(ExtraDesc, "\n\n%s", Deskripsi(Akar(ST)));
                    wrefresh(ExtraDesc);
                }
                else if (sp == '\n') {
                    if (SP(player) > 0) {
                        if (choice == 0) {  // Hasn't chosen any skill
                            wbkgd(Confirm, COLOR_PAIR(2));
                            PrintText(Confirm, 1, 0, "Please select a skill.", true, Normal);
                            Pause(1000);
                        }
                        else {  // Skill chosen
                            wbkgd(Confirm, COLOR_PAIR(4));
                            if ((CanItBeUnlocked(acquiredSkill, choice)) || ((choice == 1) && (!Unlocked(Akar(skillTree))))) {
                                PrintText(Confirm, 1, 0, "Are you sure you want to", true, Normal);
                                PrintText(Confirm, 2, 0, "unlock this skill?", true, Normal);
                                Pause(100);
                                PrintText(Confirm, 3, 0, "     > Yes         No       ", true, MaxSpeed);

                                int Cf = 1;
                                chtype cch = 'r';

                                while (cch != '\n') {
                                    cch = wgetch(Confirm);
                                    if ((cch == 'a') || (cch == 'A')) {
                                        PrintText(Confirm, 3, 0, "     > Yes         No       ", true, MaxSpeed);
                                        Cf = 1;
                                    }
                                    else if ((cch == 'd') || (cch == 'D')) {
                                        PrintText(Confirm, 3, 0, "       Yes       > No       ", true, MaxSpeed);
                                        Cf = 2;
                                    }
                                }

                                if (Cf == 1) {  // Chosen skill is unlocked
                                    ChooseSkill(choice, skillTree, &player, &acquiredSkill);
                                    SP(player)--;
                                    wclear(Confirm);
                                    wrefresh(Confirm);
                                    wbkgd(Confirm, COLOR_PAIR(1));
                                    PrintText(Confirm, 2, 0, "You have unlocked the skill!", true, Normal);
                                    Pause(1000);
                                    wclear(Confirm);
                                    wbkgd(Confirm, COLOR_PAIR(4));
                                    wrefresh(Confirm);
                                }
                            }
                            else {  // Skill cannot be unlocked
                                SearchID(skillTree, choice, &ST);
                                if (Unlocked(Akar(ST))) {
                                    wbkgd(Confirm, COLOR_PAIR(6));
                                    PrintText(Confirm, 2, 0, "You already have this skill", true, Normal);
                                }
                                else {
                                    PrintText(Confirm, 2, 0, "This skill is not available for unlock", true, Normal);
                                }
                                Pause(1000);
                            }
                            JustChosen = true;
                            choice = 0;
                        }
                        wclear(Confirm);
                        wrefresh(Confirm);
                    }
                    else {  // Skill Point == 0
                        wbkgd(Confirm, COLOR_PAIR(2));
                        PrintText(Confirm, 2, 0, "You don't have any skill point.", true, Normal);
                        Pause(1000);
                        wclear(Confirm);
                        wbkgd(Confirm, COLOR_PAIR(4));
                        wrefresh(Confirm);
                        JustChosen = true;
                    }
                }
                else if ((sp == 'q') || (sp == 'Q')) {  // Quit
                    SkillMode = false;
                }
                if (SP(player) == 0) {  // Skill Point alert window turned off
                    wbkgd(AlertSKL, COLOR_PAIR(5));
                    wrefresh(AlertSKL);
                }
            }

            // Cleanup
            DeleteWindow(SkillTreeBG);
            DeleteWindow(Skill1);
            DeleteWindow(Skill2);
            DeleteWindow(Skill3);
            DeleteWindow(Skill4);
            DeleteWindow(Skill5);
            DeleteWindow(Skill6);
            DeleteWindow(Skill7);
            DeleteWindow(Skill8);
            DeleteWindow(Skill9);
            DeleteWindow(Confirm);
            DeleteWindow(ExtraDesc);

            // Restore Extra
            wclear(Extra);
            box(Extra, 0, 0);
            wbkgd(Extra, COLOR_PAIR(6));
            PrintControl(Extra);

            // Restore Map
            box(Map, 0, 0);
            DrawMap(Map);
        }
        else if ((cmd == 'b') || (cmd == 'B')) {    // OPEN ATTRIBUTE
            wclear(Extra);
            box(Extra, 0, 0);

            // Move focus from Map to Extra
            wbkgd(Map, COLOR_PAIR(5));
            wrefresh(Map);
            wbkgd(Extra, COLOR_PAIR(1));

            int AllocSessionSTR = 0;
            int AllocSessionDEF = 0;
            int AllocSessionLUC = 0;
            int APStart = AP(player);

            int AllocChoice = 1;
            boolean AllocMode = (APStart > 0);

            // Print player attribute
            PrintText(Extra, 2, 0, "Player Attribute", true, Normal);
            if (AllocMode) {
                if (AP(player) > 1) {
                    PrintText(Extra, 5, 4, "Attribute Points: ", false, Normal);
                }
                else {
                    PrintText(Extra, 5, 4, "Attribute Point : ", false, Normal);
                }
                mvwprintw(Extra, 5, 21, "  %d  ", AP(player));
                wrefresh(Extra);
                Pause(500);
                PrintText(Extra, 7, 14, "STR", false, Normal);
                PrintText(Extra, 8, 14, "DEF", false, Normal);
                PrintText(Extra, 9, 14, "LUC", false, Normal);
            }
            else {
                PrintText(Extra, 5, 14, "STR", false, Normal);
                mvwprintw(Extra, 5, 18, "  %d  ", STR(player));
                PrintText(Extra, 7, 14, "DEF", false, Normal);
                mvwprintw(Extra, 7, 18, "  %d  ", DEF(player));
                PrintText(Extra, 9, 14, "LUC", false, Normal);
                mvwprintw(Extra, 9, 18, "  %d  ", LUC(player));
            }

            chtype ap = '0';

            if (AllocMode) {
                PrintText(Extra, 11, 0, "Use WASD to assign points", true, Normal);
                PrintText(Extra, 12, 0, "Use Enter to confirm/quit", true, Normal);
            }
            else {
                PrintText(Extra, 13, 4, "Press any key to return", true, Normal);
                ap = wgetch(Extra);
            }

            while (AllocMode) {
                // Attribute allocation interface setup
                if (AP(player) > 1) {
                    mvwprintw(Extra, 5, 4, "Attribute Points:");
                }
                else {
                    mvwprintw(Extra, 5, 4, "Attribute Point :");
                }

                if (AP(player) > 0) {
                    wbkgd(AlertATR, COLOR_PAIR(1));
                }
                else {
                    wbkgd(AlertATR, COLOR_PAIR(5));
                }
                wrefresh(AlertATR);
                mvwprintw(Extra, 5, 21, "  %d  ", AP(player));
                wrefresh(Extra);

                if (AllocChoice == 1) {
                    if (AllocSessionSTR > 0) {
                        if (AP(player) > 0) {
                            mvwprintw(Extra, 7, 18, "< %d > ", STR(player));
                        }
                        else {
                            mvwprintw(Extra, 7, 18, "< %d   ", STR(player));
                        }
                    }
                    else {
                        if (AP(player) > 0) {
                            mvwprintw(Extra, 7, 18, "  %d > ", STR(player));
                        }
                        else {
                            mvwprintw(Extra, 7, 18, "  %d   ", STR(player));
                        }
                    }
                    mvwprintw(Extra, 8, 18, "  %d  ", DEF(player));
                    mvwprintw(Extra, 9, 18, "  %d  ", LUC(player));
                }
                else if (AllocChoice == 2) {
                    mvwprintw(Extra, 7, 18, "  %d  ", STR(player));

                    if (AllocSessionDEF > 0) {
                        if (AP(player) > 0) {
                            mvwprintw(Extra, 8, 18, "< %d > ", DEF(player));
                        }
                        else {
                            mvwprintw(Extra, 8, 18, "< %d   ", DEF(player));
                        }
                    }
                    else {
                        if (AP(player) > 0) {
                            mvwprintw(Extra, 8, 18, "  %d > ", DEF(player));
                        }
                        else {
                            mvwprintw(Extra, 8, 18, "  %d   ", DEF(player));
                        }
                    }
                    mvwprintw(Extra, 9, 18, "  %d  ", LUC(player));
                }
                else if (AllocChoice == 3) {
                    mvwprintw(Extra, 7, 18, "  %d  ", STR(player));
                    mvwprintw(Extra, 8, 18, "  %d  ", DEF(player));
                    if (AllocSessionLUC > 0) {
                        if (AP(player) > 0) {
                            mvwprintw(Extra, 9, 18, "< %d > ", LUC(player));
                        }
                        else {
                            mvwprintw(Extra, 9, 18, "< %d   ", LUC(player));
                        }
                    }
                    else {
                        if (AP(player) > 0) {
                            mvwprintw(Extra, 9, 18, "  %d > ", LUC(player));
                        }
                        else {
                            mvwprintw(Extra, 9, 18, "  %d   ", LUC(player));
                        }
                    }
                }

                // Input for Attribute Allocation
                ap = wgetch(Extra);

                // Input Processing
                if ((ap == 'w') || (ap =='W')) {
                    AllocChoice--;
                    if (AllocChoice < 1) {
                        AllocChoice = 1;
                    }
                }
                else if ((ap == 's') || (ap == 'S')) {
                    AllocChoice++;
                    if (AllocChoice > 3) {
                        AllocChoice = 3;
                    }
                }
                else if ((ap == 'd') || (ap == 'D')) {
                    if (AP(player) > 0) {
                        AP(player)--;
                        if (AllocChoice == 1) {
                            AllocSessionSTR++;
                            STR(player)++;
                        }
                        else if (AllocChoice == 2) {
                            AllocSessionDEF++;
                            DEF(player)++;
                        }
                        else if (AllocChoice == 3) {
                            AllocSessionLUC++;
                            LUC(player)++;
                        }
                    }
                }
                else if ((ap == 'a') || (ap == 'A')) {
                    if (AllocChoice == 1) {
                        if (AllocSessionSTR > 0) {
                            AllocSessionSTR--;
                            STR(player)--;
                            AP(player)++;
                        }
                    }
                    else if (AllocChoice == 2) {
                        if (AllocSessionDEF > 0) {
                            AllocSessionDEF--;
                            DEF(player)--;
                            AP(player)++;
                        }
                    }
                    else if (AllocChoice == 3) {
                        if (AllocSessionLUC > 0) {
                            AllocSessionLUC--;
                            LUC(player)--;
                            AP(player)++;
                        }
                    }
                }
                else if (ap == '\n') {
                    // Pop-up window for confirmation
                    WINDOW* Confirm = newwin(4, 38, 30, 9);
                    wbkgd(Confirm, COLOR_PAIR(4));

                    PrintText(Confirm, 1, 0, "Confirm attribute placement?", true, Normal);
                    PrintText(Confirm, 2, 0, "Your progress will be saved.", true, Normal);
                    PrintText(Confirm, 3, 0, "     > Yes         No       ", true, Normal);

                    int Choice = 1;
                    chtype cch = 'r';

                    while (cch != '\n') {
                        cch = wgetch(Confirm);
                        if ((cch == 'a') || (cch == 'A')) {
                            PrintText(Confirm, 3, 0, "     > Yes         No       ", true, MaxSpeed);
                            Choice = 1;
                        }
                        else if ((cch == 'd') || (cch == 'D')) {
                            PrintText(Confirm, 3, 0, "       Yes       > No       ", true, MaxSpeed);
                            Choice = 2;
                        }
                    }

                    // Cleanup
                    DeleteWindow(Confirm);

                    if (Choice == 1) {
                        // Save Game
                        AllocMode = false;
                        Save(player, nMedLeft, con, nCurrMap, posP, posB, tabEnemy, skillTree, acquiredSkill);
                    }
                    else {}
                }
            }

            // Cleanup
            wclear(Extra);
            box(Extra, 0, 0);
            wbkgd(Extra, COLOR_PAIR(6));
            PrintControl(Extra);

            // Restore Map Color
            wbkgd(Map, COLOR_PAIR(1));
        }
        else if ((cmd == 'n') || (cmd == 'N')) {    // OPEN NOTE
            // Pop-up window replacing Map View
            WINDOW* Note = CreateWindow(31, 81, 4, 60);
            wbkgd(Note, COLOR_PAIR(6));

            wclear(Extra);
            wbkgd(Extra, COLOR_PAIR(1));
            box(Extra, 0, 0);
            wrefresh(Extra);

            PrintText(Note, 2, 4, "New Guy's guide to Romance Realm", false, SuperFast);

            PrintText(Note, 4, 6, "First things first, on the left side is your stats and extra window.", false, SuperFast);
            PrintText(Note, 5, 4, "The stat window would show you your name, just in case you forget it,", false, SuperFast);
            PrintText(Note, 6, 4, "your level, your HP, that stands for Heart Point, and your experience.", false, SuperFast);
            PrintText(Note, 7, 4, "On the right would be 2 indicators for your unspent points. Handy.", false, SuperFast);

            PrintText(Note, 9, 6, "On the map screen, you should see a block marked with P. That's you.", false, SuperFast);
            PrintText(Note, 10,4, "The walls are marked with '#', you can't move through that. And the", false, SuperFast);
            PrintText(Note, 11,4, "girls are marked with E. You would start the encounter with them if you", false, SuperFast);
            PrintText(Note, 12,4, "trespass their private space. Sometimes you would also find medicines", false, SuperFast);
            PrintText(Note, 13,4, "(M) on the map. This will restore your HP. Use them wisely, they don't", false, SuperFast);
            PrintText(Note, 14,4, "grow on trees you know. You would eventually see a Q on the map.", false, SuperFast);
            PrintText(Note, 15,4, "She's the Queen of this Realm. ", false, SuperFast);

            PrintText(Note, 17,6, "While encountering a girl, please don't play dead like you used to do", false, SuperFast);
            PrintText(Note, 18,4, "in real life. You had 3 options, initially. The commands are either A,", false, SuperFast);
            PrintText(Note, 19,4, "B, or F. A stands for Attract, B stands for Bore, and F stands for Flirt.", false, SuperFast);
            PrintText(Note, 20,4, "It's like rock-paper-scissor, Attract wins against Flirt, Block wins", false, SuperFast);
            PrintText(Note, 21,4, "against Attract, Flirt wins, against Bore. You won't take damage if you", false, SuperFast);
            PrintText(Note, 22,4, "countered Attract with Bore. You would do extra damage if you countered", false, SuperFast);
            PrintText(Note, 23,4, "a Bore with Flirt. And Flirt do less damage if countered with Attract.", false, SuperFast);

            PrintText(Note, 25,4, "Later on, you would unlock skills, if you survived long enough that is.", false, SuperFast);

            PrintText(Note, 27,4, "Try not to get your HP below 0, if you wanted to leave that is.", false, SuperFast);
            PrintText(Note, 28,4, "                                                                   -A", false, SuperFast);

            PrintText(Extra, 8, 0, "Press any key to return", true, Normal);

            // Wait for input to go back
            char buffer = wgetch(Note);

            // Cleanup
            DeleteWindow(Note);

            // Restore Map
            box(Map, 0, 0);
            DrawMap(Map);
            wrefresh(Map);

            // Restore Extra
            wclear(Extra);
            box(Extra,0,0);
            wbkgd(Extra, COLOR_PAIR(6));
            PrintControl(Extra);
        }

        else if ((cmd == 'm') || (cmd == 'M')) {    // OPEN MENU
            wclear(Extra);
            box(Extra, 0, 0);

            // Move focus from Map to Extra
            wbkgd(Map, COLOR_PAIR(5));
            wrefresh(Map);

            wbkgd(Extra, COLOR_PAIR(4));

            PrintText(Extra, 2, 0, "Menu", true, Normal);
            Pause(500);
            PrintText(Extra, 4, 4, "> Continue", false, Normal);
            PrintText(Extra, 6, 4, "  Save Game", false, Normal);
            PrintText(Extra, 8, 4, "  Return To Main Menu", false, Normal);

            chtype cm = 'r';
            int choice = 1;
            int y = 4;
            int prevy = y;
            boolean MenuMode = true;

            while (MenuMode) {
                // Input
                cm = wgetch(Extra);

                if ((cm == 'w') || (cm =='W')) {
                    choice--;
                    if (choice < 1) {
                        choice =  1;
                    }
                }
                else if ((cm == 's') || (cm == 'S')) {
                    choice++;
                    if (choice > 3) {
                        choice = 3;
                    }
                }
                else if (cm == '\n') {
                    WINDOW* Notif = newwin(6, 38, 27, 9);
                    wbkgd(Notif, COLOR_PAIR(1));
                    if (choice == 1) {
                        MenuMode = false;
                    }
                    else if (choice == 2) {
                        // SAVE GAME
                        Save(player, nMedLeft, con, nCurrMap, posP, posB, tabEnemy, skillTree, acquiredSkill);

                        PrintText(Notif, 4, 4, "Your progress has been saved", false, Normal);
                        Pause(1000);
                    }
                    else if (choice == 3) {
                        PrintText(Notif, 2, 0, "Are you sure you want to quit?", true, Normal);
                        PrintText(Notif, 3, 0, "Unsaved progress will be lost.", true, Normal);
                        PrintText(Notif, 5, 0, "     > Yes         No       ", true, MaxSpeed);

                        chtype nch = 'r';
                        int notifchoice = 1;

                        while (nch != '\n') {
                            nch = wgetch(Notif);
                            if ((nch == 'a') || (nch == 'A')) {
                                PrintText(Notif, 5, 0, "     > Yes         No       ", true, MaxSpeed);
                                notifchoice = 1;
                            }
                            else if ((nch == 'd') || (nch == 'D')) {
                                PrintText(Notif, 5, 0, "       Yes       > No       ", true, MaxSpeed);
                                notifchoice = 2;
                            }
                        }

                        if (notifchoice == 1) {
                            MenuMode = false;
                            MapMode = false;
                            Pause(500);
                        }
                    }
                    DeleteWindow(Notif);
                }
                y = choice*2 + 2;
                mvwprintw(Extra, prevy, 4, " ");
                mvwprintw(Extra, y, 4, ">");
                prevy = y;
            }

            // Cleanup
            if (MapMode) {  // Returned to map
                wclear(Extra);
                box(Extra, 0, 0);
                wbkgd(Extra, COLOR_PAIR(6));
                PrintControl(Extra);

                // Restore Map Color
                wbkgd(Map, COLOR_PAIR(1));
                wrefresh(Map);
            }
        }
        if (HP(player) <= 0) {
            MapMode = 0;
        }
    }

    // CLEANUP
    DeleteWindow(Stat);
    DeleteWindow(Map);
    DeleteWindow(Extra);
    DeleteWindow(AlertATR);
    DeleteWindow(AlertSKL);

    // End-Game status
    if ((result == -1) || (result == 2)) {
        SaveFileIndex sFI;
        ReadSaveFileIndex (&sFI);
        if (SearchSaveFileIndex (sFI, NAMA(player)) != 0) {
            BuildSkillTree(&skillTree,&acquiredSkill);

            char* TempName = (char*) malloc (20);
            TempName = NAMA(player);
            Load(TempName, &player, &nMedLeft, &con, &nCurrMap, &posP, &posB, &tabEnemy, &acquiredSkill);

            ListLR L = acquiredSkill;
            BinTree B;
            while (L != Nil) {
                SearchID(skillTree,ID(Akar(Info(L))),&B);
                Unlocked(Akar(B)) = true;
                L = Next(L);
            }

            LoadBST(&enemyData);
            CreateEmptyArea(&listArea);
            Baca_Area(area);
            PlaceMedicine(nMedLeft,area);
            LoadMap(&listArea,area,con,posB);
            SaveEnemyPoint(area,enemyLoc);
            SetAllVisitedAreaToFalse(&FirstArea(listArea));
            GetMapAddressFromIndex(nCurrMap,FirstArea(listArea),&currMap);
        }
        else {
            char* TempName = (char*) malloc (20);
            TempName = NAMA(player);
            CreatePlayerAwal(&player, TempName);

            nMedLeft = 6;
            BuildSkillTree(&skillTree,&acquiredSkill);
            LoadBST(&enemyData);
            CreateEmptyArea(&listArea);
            Baca_Area(area);
            PlaceMedicine(nMedLeft,area);
            Init_List(&listArea, area, &con, &posB);
            SaveEnemyPoint(area,enemyLoc);
            currMap = FirstArea(listArea);
            posP = Random_Pos_Player(Map(currMap));
            AssignEnemy(enemyData,area,&tabEnemy);
        }

        if (result == -1) {
            EndGameScreen(Background, false);
        }
        else if (result == 2) {
            ClosingCutscene(Background);
            EndGameScreen(Background, true);
        }
    }

    // Cleanup
    DeleteWindow(Background);
}

void DrawSprite (WINDOW* win, int Choice)
// I.S. : win allocated and defined
// F.S. : Sprite printed on screen
{
    if (Choice == 1) {
        mvwprintw(win, 0, 0, "     , ,,,***.(((/  ,.,,&&&%/,///*/,#((%(//*/((*((///.//*(//#(/*,         ,          ");
        mvwprintw(win, 1, 0, "   ,, ,,,***,/((*  .,,.,%&&&(#/((/#,(//#(///*/#/###((//*//(//#/*,           ,        ");
        mvwprintw(win, 2, 0, " ,, ,,,, ****/(. . ,,*,,*&&&(##(((#(*///#///,/((#%%%###(*(/(////.. .  .,,.    .  .   ");
        mvwprintw(win, 3, 0, ",,,,,,,,,,**//...  /,*,,*#&%(. ..%*(*(*/#(/(/*(#(%%%#%#%#((//,//.,... ,*****,,   .. .");
        mvwprintw(win, 4, 0, ",, ,,**,****/,,,.  (**,,*/&%#,/      *(*(###(#(###(*   .   .//,/,,.., ,*******.,   ,,");
        mvwprintw(win, 5, 0, "******,.,*%***,.   /**,,,*(&%,,&      ((/%%%#%##%/,/         ./,,,,.../**///**.,.  .*");
        mvwprintw(win, 6, 0, "***,,**/%//***  .*./*,,,,*/%&(%&&.*%/ /%#(%%%&&%%&@@#.      ./(*,*,, **%%/////../,,  ");
        mvwprintw(win, 7, 0, ",,***#%/////,*//..//*.*,,*/(@ %@@@@@@@%##%%%@@&%@@@% %%/,(*##***,*  *&&&/*, ./*,,,, .");
        mvwprintw(win, 8, 0, "***(&///*//****.%%//*.**,*/(% (&@@@@@@@%#%%%%%@@@@@@@@@&&@%#*##/**,/  /&&&&&&%(   (/*");
        mvwprintw(win, 9, 0, "//&(/*****//,*%%%%/// /*,*/(#.*&@@@@@@@@%%%&%%&@@@@@@@@@@&%##%&/*,,*   %&&&&&&& .,*//");
        mvwprintw(win, 10,0, "*%(****/(//%%%%%(*%//.//.*/((** @@@@@@@@@&%@@&&@@@@@@@@@&%%(%%@,*.*.   /%%&&&&&/ ,/%/");
        mvwprintw(win, 11,0, "#(*/((/@@@@&%@%/*,&(/ */.*//((*  #@@@@@@@@@@@@@&@@@@@@&%%##/%%@,..*     @%%%%%%%, ,/%");
        mvwprintw(win, 12,0, "#/(&&&&&%&&@%/*,,.%(/ ,/,**/(#*    ,@@@@@@@@&@@@@&@&&%%%,. #(#(,..,     ,@%%%%%,  *%&");
        mvwprintw(win, 13,0, "%(&&%%&&&//,,,..%(***/***/##/       (&&&(&&&&&%%%,**, *(#&*. *       ,@%%%%%@&/   (@&");
        mvwprintw(win, 14,0, "%%&&&&&%(/,,,,,.  %#(#(//*//(%/          %&&&&&%%/***//,  ###(,  ,      . ,@&@%&@@@(*");
        mvwprintw(win, 15,0, "/(%%            .,,,,*****.  .(%%%*. /        * .&@%%%%%@@                           ");
        mvwprintw(win, 16,0, "   *,,,,,***/#%%#**/%#((#(##%%#(***,*,,,...    ,@&%%#%*/* //#&.. ..        . ,,.     ");
        mvwprintw(win, 17,0, ",,*,,,..,.      #@@%&//   /#%#/((//*                 ,*%%/  *           .   #%%#%%%%%");
        mvwprintw(win, 18,0, ",,,*,,**        #@@%/    /#%/###(//*              , %%/  .    .        . , *%%%#%%%%%");
        mvwprintw(win, 19,0, "*****/,          @@@#&%#*    ,(/%#%%(/       ///((///%%/            /(    ,  , #%%%((");
        mvwprintw(win, 20,0, ",//(, .,,,  . .   %@&&%(*   (#%%##%%&&@#(    //((#####%&*            ##%%%.  .. ...%%");
        mvwprintw(win, 21,0, "*#( . ...,.  ,.  ,%.##%/  *(%&&&&&&&&&&* (#&@@@@&&&%%(*          ,#@@@@@@@/  *  ,, %%");
        mvwprintw(win, 22,0, "(,  ....,         ./#( (&&@@@@@@@@&%%%%%%##%%&&&&&&%%##%/,        %&@@@@@@@@@@, /  .,");
    }
    else if (Choice == 2) {
        mvwprintw(win, 0, 0, "  (/((/(#%%#%%(*,*,.,*#((//( ,*,/*((/////,/%(((,*///,*//*/,**,*//((((/%%%##%%%%%%%%%%");
        mvwprintw(win, 1, 0, "//// ,((((((#%%%%**,./((((*/./((/../**,///((/&@@@@@%(///..**,.,/ .,*///(((((#%&&%%%%#");
        mvwprintw(win, 2, 0, " ,//*,*((////(#%/.*,.(/(((///(&&%/,,*///*//((@@&&@@&%(*//*.**..*/...**,,,,/(((((%&@@@");
        mvwprintw(win, 3, 0, "  .****/(////////,**.(//((/*/&&%%&//***/////((&/     ,@/(/*.**.*///., ,//(/*,***(#%&&");
        mvwprintw(win, 4, 0, "      .,//*,,**/,*,*,/(/(((,(&@@@@@#(#///((((((&@,//.//(%/(*.**.*//*/*.,,(/((((((/*,*");
        mvwprintw(win, 5, 0, "       ......,(*,***,*(((((,#&%&%(%&&(&%(//(((((&&%&&&%(&&((/*/*,*//*////,/((/(/(((((");
        mvwprintw(win, 6, 0, "           ..(/,,,,,,*((/((/#    /&&&&@@%#/###&@@@@&&&&&%%(/*/*,,//,(/////(((/(((//((");
        mvwprintw(win, 7, 0, "            (/.***,*,//((/(( . ,*//#%&@@@&@@@&&%%@@@@@&&&@&%%(****,*((*((((((((((////");
        mvwprintw(win, 8, 0, "   *       (,  .,*,*..(/((*((*(//%&%&@@@@@&&@@@@@&@@@@@@@@&*(*/ *,,((,*/&&&&&&%%#%%%%");
        mvwprintw(win, 9, 0, "         *        .,..,(//(,((&(&&&@@@@@@@@@@@@@@@@@@@@@@@&&/   **  **/(/        ,   ");
        mvwprintw(win, 10,0, " .&.                ,. *////*/(@&&&@@@@@@@@@@@@@@@@@@@@@@@%      (.   *((%           ");
        mvwprintw(win, 11,0, "                    *,  ///.**/(&@@@@@@@@@@@@@@@@@@@@@@@@&    ,,,.(/*    (##         ");
        mvwprintw(win, 12,0, "                  *,  ../**,*//%@@@@@@@@@&&@@@@@@@@@@@% .,.  ./****,*/(*  .#         ");
        mvwprintw(win, 13,0, "        .,*.    .,   /,  , /*/ //(%&@@@@@@@@@@@@@@@@@@&*      . .//((//***/////      ");
        mvwprintw(win, 14,0, "          .**   .,,*.**   *,.** */*(&&&@@@@@@@@@@@@@@*/(       .(&@@@%#&/*****,*%%%%%");
        mvwprintw(win, 15,0, "      .    ...  ...,*,(   ,.,,,,/./   (%&&@@@@@@@@&,////(.*//@@@@@@@@@@@&,#%*((*.....");
        mvwprintw(win, 16,0, "     ..           ....,/.*/. ,,,,*/. (.   .,,/((**,       &@@@@@@@@@@@@@@@/..,#((((#/");
        mvwprintw(win, 17,0, "     *,            ..,*/%&  .  .,,,/(.    .,,         .#&@@@@@@@@@@@@@@@@@**((/(*/#/*");
        mvwprintw(win, 18,0, "..  .//.            ,*#&(   *     ,,*/   .. //       (&@@@@@@@@@@@@@@@@@@@//**/%%((/*");
        mvwprintw(win, 19,0, "*,../#.,((*        .%%(  *  .    /. . */     ./    /&@@@@@@@@@@@@@@@@@@@@&(//((((#%&%");
        mvwprintw(win, 20,0, "////%%* ,*(,.,....#%#       .....   ...      .   %&@@@@@@@@@@@@@@@@@@@&&@//*////((#%&");
        mvwprintw(win, 21,0, "%%%&@*..,///.  %%,        /..,*..            &&@@@@@@@@@@@@@@@@@@&&&&&@  .*/////(/(((");
        mvwprintw(win, 22,0, "%%%&@*..,/////....        /..,*..          &&@@@@@@@@@@@@@@@@@@@@&&&@    .*/////(/(((");
    }
    else if (Choice == 3) {
        mvwprintw(win, 0, 0, "      *,    @&@*.@@@&%,#*&@@@%&&&%@@@@@@@@%##*&@@@@@@@%//(@@@@@@@&&&&@/        ./((((");
        mvwprintw(win, 1, 0, "     ,,,,  &&.@&@%*&@@@@,#%&@@@,&&/@@&((##(*,*#/&&@@@@@&%@%/&@#@@@%@&%%@@          ,(");
        mvwprintw(win, 2, 0, " . ..,, %@/@&*@@@@/*@@@@% %@@@& &(@@@@@@@@@@@%%(%%@@@&%&(@@%/@/@@@@@&&%@@.      ..,,,");
        mvwprintw(win, 3, 0, ", ...%&/@@&@@@@@%*@@@@%/(@@@& %(@@@@@@@@@@@@%#%#@&&%&&.&/%&%/,#%@@@@%@%&@#       ***,");
        mvwprintw(win, 4, 0, "/(#(&&@&@@&%@@@@%*/@@@&@@@@%% #&&@@@@&%#(&@@%(%%#%%%%(/#@@@@%(#,%@@@%@@%@&%%,      ,,");
        mvwprintw(win, 5, 0, "&%%%@&(%@%@@&%@@@@&(*@@&%%@@##&(.          #&@&(%#%##%%%,(@@@@* @@@@#@@@@&%&(&&&,   .");
        mvwprintw(win, 6, 0, "&&&%@&@@@@%&@#@@&((@%%((%##(%, (#       . /&@(%####%#,(%%(//(#/.@@@@/@@@@%&@(&&&&%%##");
        mvwprintw(win, 7, 0, "&&%#@&@@@@%&&%@@%*%@@@,*@##/%(,*/       %%%@@(%%%%**(/%       /(&@@%#@@@@#&@(&&&(&%&%");
        mvwprintw(win, 8, 0, "   *       (,  .,*,*..(/((*((*(//%&%&@@@@@&&@@@@@&@@@@@@@@&*(*/ *,,((,*/&&&&&&%%#%%%%");
        mvwprintw(win, 9, 0, "//..(%%@@@@@%@@@@&/*&@@,,***(*#/##(//#*&@&&@@@%%@@@@@@@.     %&,,/(@#/%@@%@(@@,#&&&%&");
        mvwprintw(win, 10,0, ",,,/&@@(@@@@@@@*@*/%@@&,,. #,*(*####%%&&&&@@@@@@@@@@@,/(,,&@*&@,/ #@%%@,(%&&&&&&&&%&,");
        mvwprintw(win, 11,0, "  *&@@*(//@@&%**.@@@/.,. /*,%,%%###%%%&&&&@@@@@@@@@&&&***@%%&&.((#/.%@##@/@#/%/&@@&@&");
        mvwprintw(win, 12,0, " .((@@&/(#%%@&*/**(@@(/ ,,  %,/*(&&&&&&&&&&@@@@@@%@@&&&&%#(###%.,(((..@(.%.&@%,(#(%%&");
        mvwprintw(win, 13,0, " /#@(#/%,(#(*,.*@@ %, ,,  .#(% (&&&&&&@@@@@@@@@@@@&&&&%%%###  ,((. /(.,/ #@@,*/(/////");
        mvwprintw(win, 14,0, "///%*(###/*,,,, #@*((*,, .   *##*  @@@@@@@@@@@@@@@@@@@&&&&%%(   ((,..(..*. #@@,*/#((#");
        mvwprintw(win, 15,0, "#.(/*,. ,.,#&@&,/(, .,.,,    %#*/& /@@@@@@@@@@#@@@@@@@&&&     (.  ..... ,/@@%**//*(##");
        mvwprintw(win, 16,0, "&(.(/,.,  #@@&@*(#*// .%..,.    ##  .**#*@@@@@@@@@@@@@@(     . (   ,/.... ( (@&//,##/");
        mvwprintw(win, 17,0, "&/**/*.%@@@%@/*(&@%@@/,.*@%.      .    //@#**&@@@#.        *@##.  . %,(.. ##(%@/,**##");
        mvwprintw(win, 18,0, "@@@%@ ,*@**@@&/&&%,*&&..,(   ,@*.  .,@*#/,/%       *@@//@/    %%,,. #@,((///(*###%%%(");
        mvwprintw(win, 19,0, "@@@@@%&. .,&@**&@/((((,,,#&&%%/* *@#   ..((%(,@. *.  *%@@@,*/*. .. @%%. (@@((*////*((");
        mvwprintw(win, 20,0, "@@%%#*/ /.*@%&@@/&(*/&@@*.%,(&*@#/@@.     .***, . .. *%&@##/(%@@.  #@%%./&@%(*((//(/#");
        mvwprintw(win, 21,0, "%%@&.,*/,*/,@@/(.(@*@/@&&&@,@/@#.#*@@            /*/#*&&&(&%%@@@@...&@@#*@@@,*/%(///*");
        mvwprintw(win, 22,0, "@@  ,.(, ,*%&/(,(.#(#/#*&(&**..*/.(,((.  (/ ***,  #. ,@(,,/@#@@@@&. .@@@#@@@@ ((///*@");
    }
    else if (Choice == 4) {
        mvwprintw(win, 0, 0, "   ........(%#/%/(#&//,,/#**,,/*.#,*#/&/..........(%(&(*,.....,,..,..,.*/%&&(#*,,,..,");
        mvwprintw(win, 1, 0, ". .......*/(,*(,,&//.,*%*(/,,/.,(/(#,&,..........,(%&@@@*.....,,,*/.....,.,*%%/*,,..,");
        mvwprintw(win, 2, 0, " .........,.,*,,#,.&//,,/#*%%/*,,.,#,*,,/*..*.,****/*%&(%(*........,,,**,,,.,,./(/*,,");
        mvwprintw(win, 3, 0, "...,...,/#*.*,/.*/,&////(/#&%(*/*,,//,**///*,*(/*(((#((***,............,*...,/(%*,,..");
        mvwprintw(win, 4, 0, "...,*/*.#%%/./*(,#/%#/#/#%&&&%//,,%..%/*(((**,.,,.,(#/*,,............,*......#/,,...,");
        mvwprintw(win, 5, 0, "...#**#,,**//,%(((&&%%&%(.....//,**/(**&.#*%(,,,..,..*(***,,,,,,,,,,,*......,%/,,...,");
        mvwprintw(win, 6, 0, ",/%*/#%%(%##%&&@@@@@@@@@#,..,/&,%*,/,,&&@%(/**%&.*.,..,,.,...****,,.....,...,,.%*,,..");
        mvwprintw(win, 7, 0, "/#*/#/......,,%@@@@@@@@@,,..(&@&&,,/*.,%@&(,./.*/...............,,...........*((,,,..");
        mvwprintw(win, 8, 0, "//((//,....&@@@@@@@@@@@@@,///&&,,(*,.%&@#,..%*&&...,.*...,........,...,.#%%(*/,,,,,**");
        mvwprintw(win, 9, 0, "(/(/(&%,.,/##@@@@@@@@@@@@@&&&&&&,,./%.#/(&%,..,,#%&....&&,./@#.#,,.,@,...*(((/*/,,,,*");
        mvwprintw(win, 10,0, "#(%//%%%&&&&&@@@@@@@@&@@@@@@@@@@./.*((.***&/...,*((%,,%##&&%@&&@&&&%#(((((/((/*/,,**/");
        mvwprintw(win, 11,0, ".#%/*&&%&&&&&@@@@@@@@@@@@@@@@@@/.*.*#%#,,%*&..,.,(/(*.,(/###%%%#((##(/*/(/*((/*/,,**/");
        mvwprintw(win, 12,0, ".(*((&&&&&@@@@@@@@@@@@@@@@@@/.,..*&,&/,&*%*.,,.//(/**##//(#(/*((/*//*/*((/*/,*//(@@@@");
        mvwprintw(win, 13,0, ",,&@(.*#&&&@@@@@&%@@&&&&@@@@@...../*&.%%*&*#&.,.,///&(*,,(((//#**////(//,/*(#///**(/@");
        mvwprintw(win, 14,0, "%#/*&.*.#@@@@@@@@@@@@@@@@,...,.,##%.(%##*/@.,.**#*%/*,,...**#/**(*,*((//*(#///*/#&@@%");
        mvwprintw(win, 15,0, "%./&&//*.*..**(@@@@@@@@&@*.,.,,,*%*&,.#(%/#&*#,##%*#//*,,,,,,,,,*//****(*/*(#////(%@@");
        mvwprintw(win, 16,0, "&&,(..*.**(####(#&&/**,***%%#@&&@#/&/#&&@/../&*.*#(//*/((((/***,,,,/*/*(#//((#@@@@@&%");
        mvwprintw(win, 17,0, "/,*,%.,...,,*(/(#(/(#@**///%&&%&@@@@@@@@@#&...(.,.,(*/**//%%**,,,**/,.,/*(#/###@@@@@&");
        mvwprintw(win, 18,0, ",#(*,,.,/,//*/(/(/#&&*.,*((/@%(,%&@@@@@@@@@&...,.,,,#%*///#&*,/****/#/*/*(#(%&@@@@@&@");
        mvwprintw(win, 19,0, "/*..*/*((#(%*#%%%%%#/*,*#%%#%@@&%,&&(&&&&//%#(......,,.,**/@//***#(**,.(/(/#%#@@@@@@&");
        mvwprintw(win, 20,0, "..,%&&&&&&&&%/*/#&&&&&%@/%&@/#@@@@&@%&/,*#%#((./.....,..%*%%****,,.,,,,,/%(%#@@@@@@&&");
        mvwprintw(win, 21,0, "&&&&@@@@@&@(&&&&%%%@&%#....%&%@@@@&&&&&&&&........,*,,*%,**,,,.....%%%@@@@@@@&&**,,,,");
        mvwprintw(win, 22,0, "&@@@@@@@@##@@&&%#%#/((##,%%@@@@@&&&&&&@&&/*....,....,**(,....,,,,..,(&@@@@@@@@&@***//");
    }
    else if (Choice == 5) {
        mvwprintw(win, 0, 0, "        .,(#%&(/*/*///,,//(/*/(%/*.//((///#.......  .,. ..  . . .   ... . .   . .    ");
        mvwprintw(win, 1, 0, "       ..(&/@***//*////,*#%/%(((/*/*.,.#&&%%/*....   .. . ..   .... ...   . ..   .   ");
        mvwprintw(win, 2, 0, "       .*&%(//%/((//#*#*(*((*//**/*/*,%@@@&%&%#/... . ,.. . .   ...... ..  ..  .     ");
        mvwprintw(win, 3, 0, "     .,&((@((%&%#%((*(*%@%,,*,*****/&%@@&@@/#/(/.. ...,. . . . ..   . .  .   .   ..  ");
        mvwprintw(win, 4, 0, "     ..*@*(@%(/@%(((/***(@@@&,,,****,@@@&%%##/((.      ,.  . .  . ....    ..  .      ");
        mvwprintw(win, 5, 0, "     .,%&*%@&&,&(///**,*/@@@@@@*,,*,,*@@&%#//*/*, . ....,. .  ... . ..  .. .  ..  .  ");
        mvwprintw(win, 6, 0, "     .,@&*&@%(,/#///**,*/##%@@@@@#,,,,.,#@#((/(. . . .. ,.  .  .. . . .. . .  .      ");
        mvwprintw(win, 7, 0, "    .,,@%*&%//,,&**/*****@@@@@@&&%%@%,,,**,........ . . ,.. .. .. ... .    .   .  .  ");
        mvwprintw(win, 8, 0, "    .,*@#*%(/**,&/,*****/@@%@/,/.  %%@&.,***,...........  . .  .... ..   .    ..  .  ");
        mvwprintw(win, 9, 0, "    .,(@#*(#/**,@#*,**,(/@@@@&@@/@@@@@@#,/*,,...... .. .. .   .... . ..   ..  . .    ");
        mvwprintw(win, 10,0, "    .,#,/%**,,#@/****%/@@@@@@@@@@@@@@&,/,,,..,... .....,.  ...... ..   .   . . .  .  ");
        mvwprintw(win, 11,0, "    .,#,(&,*,,&@&/,**&%@@@@@@@@@@@@@@@,/,,,..,... ......,.    .. . ...  .. .   .     ");
        mvwprintw(win, 12,0, "    .,%,*(/,,,&/,*//*&@@@@@@@@@@@@@@@@//,,,.,,.. .... ..,..... ... ..  . .. . .      ");
        mvwprintw(win, 13,0, "    .,%,,#%,,,.%#@(//@@@@@@@@@@@@@@@@@%*,,*.,,.. .......,.  ...... .. .  . ..  . .   ");
        mvwprintw(win, 14,0, "    ..%&(*.%,/,...#@&//@@@@@@@@@@@@@@@@@%,//,.,... .......,.  .. , ,.... .   .       ");
        mvwprintw(win, 15,0, "     .#&/*./***,....@@#@@@@@@@@@@@@@@@@@#,(,,...........,.,, ....,,,. .. .... .  .   ");
        mvwprintw(win, 16,0, "      (&**.,/,/,.....@@@@@@@@@@@@@@@@@@&/,,,,.... ......*.,, .. .,,,  ..  .   .      ");
        mvwprintw(win, 17,0, "     .(%**..#,,*......%@@@@@@@@@@@@@@@%@%,,,..... ......*.,, .. .  ,,... . . .    .  ");
        mvwprintw(win, 18,0, "     ,%%**../,,**.....,..&@@@@@@@@@@@&&.,,............**,,... ,,,  ... . .  . ..     ");
        mvwprintw(win, 19,0, "     ,%#**..,*,,,.............*&@@(%@&&@#.,,.....,......,/.,.. .., ,,, .  . .        ");
        mvwprintw(win, 20,0, "    .(##**...***,...................#@@@#.,,,...,,..,...,/*,,,, **,, ,. . . .. .  .  ");
        mvwprintw(win, 21,0, "    .&/#/*...***.....................@@@#..,,...,,,  ,...((.****,.,  ,,..    .     . ");
        mvwprintw(win, 22,0, "   .,&,(/,...***.................(/**@@&&...,...(#(.#%&%&&&&&&&(/*,,*,.   . .    .   ");
    }
    else if (Choice == 6) {
        mvwprintw(win, 0, 0, " .  . . ...(.,, , *,/(@.@@@@* (@*((((@@@@*(@@@@@@@@@/(....                           ");
        mvwprintw(win, 1, 0, ".   . .. .(, . * ( /((*((@,@ (@(/@(@@@@@@@.@@@@@@@/(*/@(.. ..      . .  .   .   .   .");
        mvwprintw(win, 2, 0, ".   ... ..*. ,*,(* ..* //((.(@@(@(@@@(@@/@,.(@@@*,,,///(((. . ..    .  . . .    .   .");
        mvwprintw(win, 3, 0, " . .. .../(@@/@,@    .*** /.@@/*/.,.,*@@@, @/*//(,@(.@(////((.. .. .   .. .. . . .  .");
        mvwprintw(win, 4, 0, ".. .. ../(@@@@*(/.//* @@/,(@@@,,***((**/@,(@*/*@,/@@(.@@//***/.. .  . . ..  . .  . ..");
        mvwprintw(win, 5, 0, ".   ....(@@@@((.*(((, @@ *(@@(/((@.(@@/(/,@@@(@@((@@@ *@//****(... .  ..(.....((//@((");
        mvwprintw(win, 6, 0, "...  ..*@@@@@@( /@@@ .@@ ((@@@@/(@*(@@(@/,@@(*@/@ @@@, @@/**,**/(.... .(/(/((@@/**/(/");
        mvwprintw(win, 7, 0, ". .. ./@@@@@(/( @@@@ .@@ /@@@@@@/(@ @(@*(*(@@@@.@,(@@/ .@**,..,*/((.   .((((((@@((. .");
        mvwprintw(win, 8, 0, "... ..@@@@@@(@(.@@@@./@@.,.. ./@@*(@*@@.@(@@@@( @/,@@(/ @( ,. .*/(.    . ((/(((@@@   ");
        mvwprintw(win, 9, 0, ". .../@@@@@@.@@/,@@((..*      (((@((/@/,(/@@@@(,@/.@** ,/@  *.*(,, , ,   ,((((((@@@  ");
        mvwprintw(win, 10,0, ". ../@@(/(@@ /@( @@@@,/ .,    @@@@@(@((*@,   , .@..@*., ,@@* (/(,, ,,,, ,,,((((((@@@/");
        mvwprintw(win, 11,0, "...(,,..(/@@ *@@(.@@*(@   .. .@@@@@@(@@@@/.  .(*(.(@(   ,(@@(.,/,,, ,,  ,, ,,((((@@@@");
        mvwprintw(win, 12,0, ".. ..  ((*@@  /@@//@@@(@@@@@@@@@@@@@@@@@/    (@((.@*(// ((@(@@. @/,,, ,, ,,,,,((((((@");
        mvwprintw(win, 13,0, "((.(/,*/(((@*  ,@@(/@@@(@@@@@@@@@@@@@@@@@@@(@@@/@/@,/ *((.*,/(//  @/@@@@@@@@@@@@(((/(");
        mvwprintw(win, 14,0, "//@((**(/@@.@     *((((@@@@@@@@@@@@@@@@@@@@@@@//(@/. @@*(@(*../(..*.@(@@@@@@@@@@*/(//");
        mvwprintw(win, 15,0, "@@@((..@.@@(.@.  ,/ .(@((@@@@@@@@@@@@@@@@@@@@@//@,* /  /@@@@ *@(@ .,/(/@(@@..@@@@(((/");
        mvwprintw(win, 16,0, "@@,@  /@.(@@.//(*/   .,@@@@@@@@@@@@@@@@@@@@@@/*(..  *.(@  @(*/@*@// *(@@/*(. .@@@(/((");
        mvwprintw(win, 17,0, ",@(  .@@..@(@. /.(. . ..,,@@@@@@@@@@@@@@@@@(@***      *@@@@@.@.,@@(/,/*.  **  //((*/*");
        mvwprintw(win, 18,0, "@/*. *@@/ @@.@*   .    .../@@(@@@@@@@@@/../@*./,*(*........ /@/*@@@( /(@@@   @@(.*(*/");
        mvwprintw(win, 19,0, "(@/*( @@@  @*,.*,,     (..,*     ,, ... ... (/(.,,,.......   @@ .@@/.,((@@@ @@@@@@(/@");
        mvwprintw(win, 20,0, "@@/@  @@@ , **,, *@*/.@..@, . ,/***//*..  *@@/@/*/,,....  , ,@@  @(*( @(@, *(@@(/.,@@");
        mvwprintw(win, 21,0, "@(.   (@@@  /@/**(..*@*.**             /@@/@(@@@@,*.  .,*    //  @*** (@(@@/@@((@@@@@");
        mvwprintw(win, 22,0, ". .@( ,@@(,@@ @@@@@@@@@@@.     /@@@@@@@@@,/@@@@/(@./,.*///.   .,@@@@, (( ..,/@(.(@@@/");
    }
    else if (Choice == 7) {
        mvwprintw(win, 0, 0, "&%#(((((((###%%%%&@*,*/@&&%&/&,,%%##%%#.,./%*#%%%&%&&&&&&&&@@&(@@@@@@@&&%&&%@@&&%####");
        mvwprintw(win, 1, 0, "@@#(((((%%&@%@%%#/*%/&&&%%%#/% #(//(%/... /(*/#%%%%%%%%&&&&&&&(#@@@@@@@@@%&&(#&&@@&&%");
        mvwprintw(win, 2, 0, "@##%&@@@@&@@&&&%//#&%%%%% (#.(***((..*#./*,/#%%##%%%%%%%%##(#*@@&@&&@@@@(&(#%@@&%@&@&");
        mvwprintw(win, 3, 0, "&@@@@@&@@@@@&@&@(///&%%%%%( (*,***/#,.(.*/./(##/#%(/#%##(*&,#*&&%@&&@@@@/#&&%&(&%@&&%");
        mvwprintw(win, 4, 0, "@&&@@@&@@@@&&&(//(,%#%%%%%  /.,*//(/,&&&%./(.*/(#*#%.*/#//*%/./*%&&&&@#&&(&&&&@&(&@((");
        mvwprintw(win, 5, 0, "&@@&@@@&@&&%//(#(*%(%%%%%/  .,,/(#(,&&%(/./#.**//*%#.****,(*../*#%&/&&&&%#@//&&%&&&%&");
        mvwprintw(win, 6, 0, "@&@@@&&&&%/((##( (%,%%%%% ,, /*(##/&&@@@@/,/*,*//*%*.***,(,/%.**#%%*%%&&%*&**%%%#@@@%");
        mvwprintw(win, 7, 0, "&&&&&&%#&(/(#%%/.. %@*%%%%% *%,./#%(%%#%@@@&./#,*//*%.,**,(.(&%.*,/%%*##%*%,/.&/#@#%%");
        mvwprintw(win, 8, 0, "&&&%%%%/(##%%*#    &@*%%%#% /%,/        (&@@#.%(*/(/% **,,,//#%.**#%%//(#%%*/.*.%*%%#");
        mvwprintw(win, 9, 0, "%%%(%/###%/##     ,@@*#%%#% /*  /.,       (@@#*%%###%,//(@@&&&&.//#/#(//(%%.,,,,(*/#%");
        mvwprintw(win, 10,0, "%(%((###((  ., .. /&&./%%/% /*.%. .,..  *&/&@@%#%&&%/*@@@&%&&&&/#%(*(////#% .,,,.#,(%");
        mvwprintw(win, 11,0, "(%(#%(*.  /( ..,  /&%#,(%/(./*%&,&,//,.,&@&@@@@%&&&&%@(//%&@&%%%*//*///%# ,,,, %.(#@@");
        mvwprintw(win, 12,0, "##%##%%. ..*,  .,#%% .*/..*/&&&*&@@@&&@@@@@@@@#&&%@(..       &%*///,///%, ***, %.(*%%");
        mvwprintw(win, 13,0, "####%%( ...***  *  /%%&  ,././%&&&&&&&@@@@@@@@@@@&&@&& *.       (////.///%  */*,.%,/,");
        mvwprintw(win, 14,0, "(#,,,*,,****. ,.  */(&&&,  ,.*%&&&&&&&&@@@@@@@@@@#@@@#%,,*,, /# *///(*//%,  .//*,%/,*");
        mvwprintw(win, 15,0, "******/,,  (    % /(&&&(  * %@@&&&&&@@@@@@@@@@@@@@@@(@@&%/(%.,(****//##    //**(##///");
        mvwprintw(win, 16,0, "////#*.  *( *&%#(# /#&&@@,  ,@@@@@@@@@@@@@@@@&@@@@&&&&&&&&&&&*,*,//(##     ///#/.((@@");
        mvwprintw(win, 17,0, "((#%%,.  /#.  .@&%/%% */&(&&%  /@@@@@@@@@@@@@@@@@@@@&&&&%%&&&& *# **#%/    . (((%*..,");
        mvwprintw(win, 18,0, "%(,.   #%.     ,@%#*/&  .#&((%   &@@@@@@%@@@@@@@@@@@@@&&&&&&*/    ,%%   ..,* (%%.(,..");
        mvwprintw(win, 19,0, ".   .%%/         ,%#,,*/.  &@%,   ,@@@@@@@#@@@@&@@@@@@@@@@@       %(  ., .*  %%. . %*");
        mvwprintw(win, 20,0, ",(%%%      ,       .   ..,#, ,%%*   /@@@@@@@@@@@@@@@@@@@&      .(  %#,* .,   & . ., .");
        mvwprintw(win, 21,0, "#  .   *                 ... ,%%, . .@@@@@@@@@@@@@%.              #  ,.   *  %* ,,..*");
        mvwprintw(win, 22,0, ", ..   *     .                  ..%#,,,. ,@@@%*                 . ,.%.         .%# ,,");
    }
    else if (Choice == 8) {
        mvwprintw(win, 0, 0, "             *    ....*(*,((((/,  /##########/%(%#%%&&&&@&&%&@&@@@@&,                ");
        mvwprintw(win, 1, 0, "         ./,     ..*,,,*/(#/(/(*####((######((,((%(&&&&&&%&@@&@&@@@&%                ");
        mvwprintw(win, 2, 0, ". ..,.    .     .,..,,**(%(%/,(#########(,(/#/#(%%%&&&%&&%@@&@&@@@@&&                ");
        mvwprintw(win, 3, 0, "*              ......//(/(#/.*//((########*#/((#%#&&%&&%&&&%@@@@@&@&%                ");
        mvwprintw(win, 4, 0, "         ,/***((, //(,,#&,**      ./((#/##//(%#%%&&(&&&%&&&&@&@&&@%                  ");
        mvwprintw(win, 5, 0, "   .             /*/*,,#%((*/....     (/##/(##%(%%%%&&@%&&&&@#&@#                    ");
        mvwprintw(win, 6, 0, "                  ./,**.,#%(((%&&/,(&%*.*(##(###/((%%%&(%%%%&@&/&&%                  ");
        mvwprintw(win, 7, 0, "  .          .    /.(/.,,(%##%%%%%&&&%%%##%#####(%##%/%%#%//#&@@%%&&%                ");
        mvwprintw(win, 8, 0, "            .  . ..(*(.#/(%#%%%%%%%%%%%%%%%#%&%(%##(&&/#%,*#&@&&&%#                  ");
        mvwprintw(win, 9, 0, ",.        . . , .,*%/*/%(#%#%%%%%%%%&&&%&&&&%#/**##&&&*,#&@#&%&%(##                 .");
        mvwprintw(win, 10,0, "           . , ..,((**%/#%%%%#%%&&&&&&&&&&@@@%&. .   *%%*%@&(%%&%&.#(                ");
        mvwprintw(win, 11,0, "          .,  .*./#*/*&,##%%%%%&&&&&&&&&&@@@@@&,/,( .,%&&%& *(*                .,,,,.");
        mvwprintw(win, 12,0, "*          ,  */./#*((&.(%%%%%%&&&&&&&&&@@@@@@@&@@,**#/&(#&%%%. #*                .  ");
        mvwprintw(win, 13,0, "         . *./.*#*(%%*,(%%%%%,*%&&&&@@@@@@@@@@&&&&/#%*#%%, *#*                ..     ");
        mvwprintw(win, 14,0, "   .       .*,*(.*/(/(%**,#%%%%%%(#%&@@@@@@@@@@@&%,((#/&%##%%#   #*                  ");
        mvwprintw(win, 15,0, "  .     ,,*.*/./*#*(&***,,%%%%%&&&@@@@@@@@@@@*  .#*%#/&((   (*                     ,.");
        mvwprintw(win, 16,0, "      ..   * ,**..***(#(/***,%%%%&&@@@@@@@@@%.   /(%(#%##*#/   *.                    ");
        mvwprintw(win, 17,0, "         ,   *(...,/**(%#&***,*&@@@@&%*,*(##.,*#(/,/%%(#/*,   (            .. .....,,");
        mvwprintw(win, 18,0, "         / *# ,.,/*(/(%,//*.**/%%#%/*(##% .//*,*/%##(,/., ..       %&@@@**%&   .. ..*");
        mvwprintw(win, 19,0, "             (* .#,*,,(#//%(/,*,(#&@%..#*#.*(**(/*%#&* (. *      .#&&&@@@,,/(%/.     ");
        mvwprintw(win, 20,0, "      *,(,  *( ., (((,/(%&&&&&&&&&*/,/./*,(*%//(*%(%(  /   .    #@@@@@@@@@&&,/#%,    ");
        mvwprintw(win, 21,0, "       *(  .%    * ,%%(#%%%&&&&&%@@/.*,/%&/.%.**%(((/    *      #%@@@@@@@@@,.*/#     ");
        mvwprintw(win, 22,0, "        #//#(@@%%%%#(#%###%&&&&%&@&&%(, (%#   *#/(#(.   ,.     *@@@@&@@@@@  ...,     ");
    }
    else if (Choice == 9) {
        mvwprintw(win, 0, 0, ".  . /%%( ./&&%(*((//((((###&&&,.#((/((*, ,,.....,  ,.....*   .**,(#%%%%#,####%% &@@@");
        mvwprintw(win, 1, 0, "    . /((/ .###(*/#%%/*&&%#((((((/ ,*(/*/,, ,.,.....,..... .*.  (***%%%%## ####%%*@&&");
        mvwprintw(win, 2, 0, "    ..//,   ##(  /*####,*((((((((((* ,*/,.,. ../,*,,,,.,.....*,  (*/*#####*%###%%#&&/");
        mvwprintw(win, 3, 0, "     .      #/ ,/./*##((/.*(/**/(///* ..*.,,,,,*%((,,(*.,.. ..*, .*,*/####((###%%%%%%");
        mvwprintw(win, 4, 0, "            ,  ##/ /*(((//,..*,,,,,*/,, .,,,,.#,%.  .   .,.. .**,...#(%####.##%%%%###");
        mvwprintw(win, 5, 0, "           .  .#### **,(/*** ,.,,,,,,**,..****((     .(/ .,.   //,..#%####(.%#%%#%###");
        mvwprintw(win, 6, 0, "              .%####,,,**(*,,,,.,.,,********///   .,,*/@&/.,   **/,,(&%%##(/%%%%#///,");
        mvwprintw(win, 7, 0, "             , %#//(///*,,,/*,,**,*,,////((%///.@/ ****@@%,, .  /**//&%%#((#*%%%%&&%.");
        mvwprintw(win, 8, 0, "            ///.####..#((**.*/**///#**,**(((#&&*/****(/@@%#  ,  .///.&%#((#%.&%%&&&..");
        mvwprintw(win, 9, 0, "            *(.,.. /,(,&&&&&%(/**/((/(@@&%%&&&&@%%#&&&@&&&& .,. . /*.%%###%%*&%&&&/. ");
        mvwprintw(win, 10,0, "                 .(//./(&&&&%%%/  /%&&@@@@@@@@@@@@@@@&&&&&&&.,./,.,*,/%##%%%%#&&&% . ");
        mvwprintw(win, 11,0, "                (  /**.*&&&&,   ,#&@@@@@@@@@@@@@@@@@@@&&&&&& .,//,,.*,%%%%%&&*&&&(. .");
        mvwprintw(win, 12,0, "                (/( *****&/     ,*,@@@@@@@@@@@@@@@@@@@@@@&&@  .*//*.,,%#%   #*&&&  ..");
        mvwprintw(win, 13,0, "               ..##(,,**((   .*,/*(/@@@@@@@@@@@@@@%@@@@@@@&&    ////.*(%%*    (&%    ");
        mvwprintw(win, 14,0, "               ,/.*/(/ *,* /@//.*/#%@@@@@@@@@@@@@@@@@@@@@&&      ,//*,*#/%    ,&*    ");
        mvwprintw(win, 15,0, " .              ./#.////., (.#/*&&&%@&&&&@@@@@@@@@@@@@@&&@.      , ///,,/#    .%.    ");
        mvwprintw(win, 16,0, "        .....     *(,,//(,*#((@@@%@&&&&&&@@@@@@@@@@@(&&&&,.       (,.//*.,,   ,*     ");
        mvwprintw(win, 17,0, "            .... .. */,.(/(*/&@@@&@&&&&&@@@@@@@@@%&&&&&&  .///     /(/,,(*.*  #*     ");
        mvwprintw(win, 18,0, "            .      **  /. (((*#&&&&&&&&@@@@@@@&&&&&&&&&  .  #%/**,  ./((*... ((#&&&&&");
        mvwprintw(win, 19,0, "       .     .,, ..  .///, .  /((/%%&&&&&&&&&&&&&&&&& ....  ,&&&@%/....   .,. .#(#*,.");
        mvwprintw(win, 20,0, "  .         .,**,     ./////*   *(/,&&&&((//*&&&&&&,. ......       ,%/#(**.  ,,,,,,//");
        mvwprintw(win, 21,0, ". .        &*.....      .///////*    ./*&&&&&&&&&&*   ......        /(##(/,./((#((((/");
        mvwprintw(win, 22,0, "...  (.   ###(/*/*/((, ../,////////*  ..,,**/(#/*       .           ,*/#######%%#####");
    }
    else if (Choice == 10) {
        mvwprintw(win, 0, 0, "                   ./##/*(%%#(%%%%%%%%%%%%%&&@&%&&&&&&&&&&%%%%%//%%%((((%/*/((((((%(#");
        mvwprintw(win, 1, 0, "                .*###(/#%##%%#,#(((#%%%&%%%%%&%%%&&&&&&&%%%%%%#(%%%*((((#%%%%%%####(#");
        mvwprintw(win, 2, 0, "     *%#        .*(#*(&%#%%%#/%&&&&&%####((((%%%%(#%%%%%%%%%#%%##%#%,,/((((#####%%%%(");
        mvwprintw(win, 3, 0, ".             ,(((&/***%%##%%%*%%&&&&@&&&@@&%%%#//%#(/%%%%%%%%%#%%(##(/#,**//(//////(");
        mvwprintw(win, 4, 0, "            .    ./(,*##%/#%%##%%&&&&##@@@@@@@%#%#/%(*%%%%%%%%%%%/%#((%*(,,/(#%*#####");
        mvwprintw(win, 5, 0, " .             ..,*/#*%###&&%&%%%%%%&&&&%@@@@@@%@@@@@#/%%%%#%%/%%%(%((/#(,,*/(#%%%%%%");
        mvwprintw(win, 6, 0, " .   .*,%@@&,,,**//***&&&&&&&%%#((###%&@@@@@@@&@@&&@*,,.///%%#(%#(%%#(#////(#,,*(###%");
        mvwprintw(win, 7, 0, ". .#@@@@@@@@@@%(##&&&&&&&&&&&&%###%&@@@@@@@&@@@@,.    @&**&%###,%%%*/#////#/(/((##/*(");
        mvwprintw(win, 8, 0, "..,(&@@@@@@@@&&&%&&&&&&&((/##(###%&&@@@@@@@@@@&/&..      &(&%/#/#%%#*/*/////###&&&&%%");
        mvwprintw(win, 9, 0, ".%&@@@@@@@@@@&%#&&&&&&&%/((((((#(((%&&@@@@@@@@@@@@@(      ,&&%//(%#% ,/*////((##&&%%%");
        mvwprintw(win, 10,0, "(&&&&&@@@@@@&&&&&&&((((,,*#%%%&&&&&@@@@@@@@@@@@@@**&@&%&&%%%*//%%(, ****//(((##%(%%%&");
        mvwprintw(win, 11,0, "*&@@@@@@@@@@@%%#(///((* ..,/(%%%%#%%&&@@@@@@@@@@@@@@@@&&&&%%#**%%// , .***/((####%%%&");
        mvwprintw(win, 12,0, "*%&@@@@@@@@@@&(##((/**(/   .**#(,.    @(@@@@@@@@@@@@@@&&&%%&&&&(%,*%%,# , .,,////#(##");
        mvwprintw(win, 13,0, "/%&&@@@@@@@@@@&//(,/(##(/  (*/#.#.    ,  @&@@@@@@@@@@@&&&&&&@@#,/%%*( .  .#(#(///####");
        mvwprintw(win, 14,0, "*%&&&&&&&@@@@@@@@@%#%###(. ##/(##&      ./&&&%&@@@@@@@@@@@@@@@@%(,#%%./, ,/#&&@%%%///");
        mvwprintw(win, 15,0, ",%%%%%&&&@@@@@@@@@@%%##(# *%%//%/#@#*,#@&&&&&&@@@@@@@&&@@@@@@@@#/*%%% *(#(@@@@%%&@@//");
        mvwprintw(win, 16,0, ",,#%%%&&@@@@@@@@@@@%%%%#( ##%(/(%(%%%%%%%%%%&&&&@@@##%%%%@@@@@@(/(%%#.####%@@@%%%%%%%");
        mvwprintw(win, 17,0, ",*/(###%%%###%%%%%%#####*,%##(*/#%##%%%%%%%%&&&&/##%%%%%#@@@@#/#/%%%%&&&&&@@@%%%&&@&&");
        mvwprintw(win, 18,0, "*&/////(((#%%%%#(###*.*##((/ ,*#%,#%%%%%%%%%%%(#%%%%%#&@@&@@@@/%%%&&@@@@@@@@@#(%%&&%%");
        mvwprintw(win, 19,0, "&&&&&/**/((((#(((##(/ ..*#(**/   *%%, *%%%%%%%%%%%%%%&&&%@@@@@@@(&%&&@@@@@@@@@@@&%%%%");
        mvwprintw(win, 20,0, "&&&&////////*//......*/#***%*   *%%#  *%%%%%%%%%%%%%%#@@@@@@@%%%&@@@@@@@@@@@@%%%#%%%%");
        mvwprintw(win, 21,0, "&&&%##(#####%(%,*.(//*/%**/&&     /%%,    ...((/***(@@@@@@@@&(%%%%&@@@@@@@@@@@@(#%%&%");
        mvwprintw(win, 22,0, "%%%%####%%%%((%,#&***,&%%/*#&&%(       /%*  */##//(,@@@@@@@@@@@#&%##%&&&@@@&@&&@@&#%%");
    }
    else if (Choice == 11) {
        mvwprintw(win, 0, 0, "       .,.., *, ,.,*,,.,.*.../.,#/*//,.,,...#/,(.*********/(#((/**(/*#*/(##%(**/(%%#(");
        mvwprintw(win, 1, 0, "      ,,,,.*  ..*.  (,.,./%,...,.**,/,*,....,/*,(. ,*,***/(((((((,//**/*///###(/*/*((");
        mvwprintw(win, 2, 0, "    *..,, *,   ,,.  *...(&&*...,..*,,,,,....,,,,,, ,,*.*,#*(((((/*#(((###**(##((*,,*/");
        mvwprintw(win, 3, 0, "  ,,,..,  *  ,**,,   .,(&@@(,.....,,,,,,....,..,,#. ,,*,,*#/%###**##%#//*.,/((//,.*,/");
        mvwprintw(win, 4, 0, ",......  /,   ,,,,. ./*@@@@%,,,......,.,..,..,*,,   ,.*.,,/(/((*(.******....**,,..*.*");
        mvwprintw(win, 5, 0, "  ... , *,. , ,,.,.,.#%(@@@@#*,*.....,.,.#*.,,*,,. ..,*, ,,((/,,/...(***.. ,*/%...*,,");
        mvwprintw(win, 6, 0, "  .    ,**. . ...,.,       &@#/**.......#&*./,,,.. ..,**. ,,%*,(.***,../.. */(,,,,/*,");
        mvwprintw(win, 7, 0, "      ,///... .....,(%(%*(/*#/(#*/,,,..%%(.((/,.......,* ,.,.(//**...,(..  //,,,,**//");
        mvwprintw(win, 8, 0, ".     ////.,. ..,.,,@%@@@@&@@@@@##**/* ...,, *,....,, ,/  ,,,.,,,*/**.*.. .....,,,*//");
        mvwprintw(win, 9, 0, ".. ..  ,,,,... .....&@@@@@@@@@@@@%/##@&/#@*,.....,, .*   ,,,,....../,.  ..., *//////(");
        mvwprintw(win, 10,0, ",%   ....,,..  ...../@@@@@@@@@@@@@&@@@@@@&@%,......,   . .. ,,,,,,,, (.,     ,*###(##");
        mvwprintw(win, 11,0, "  ./.,.. ..,. . ....,&@@@@@@@@@@@@@@@@@&@@@,,....,..  .   ....**,,, .**.  ,,,,,,,,,,,");
        mvwprintw(win, 12,0, ".....    ..,,.,.. ....@@@@@@@@@@@@@@@@@@@&..,...,*.        .....((  .* *  ****,..,,,,");
        mvwprintw(win, 13,0, ".... %%/  (/,,/... .,. .@@@@@&@@@@@@@@@@, .,.,,.,/.          ...      ,* .,,,,,,,,...");
        mvwprintw(win, 14,0, ".. .....  /(*,/,.,  ... ,,&@@@@@@@@@%,   ..,*,. .*.        ., ,,,***... *,,,,,,,,,,,,");
        mvwprintw(win, 15,0, " .,   * .. //,,(../*,,...,***&&(***..,     **.. ., .        #(. .(/.       ..........");
        mvwprintw(win, 16,0, ".. .*        ,*..,.,,/ (/,.*//*,..(., *.   ,,  ,.     ....,. ..(.     ...#,   ./(/*,*");
        mvwprintw(win, 17,0, "   .((   .      ,.....(,*/*/((//,..,*(*#%&&&(,,,(%*%&&&, .,   ,*           ..,,,,,,*/");
        mvwprintw(win, 18,0, "   (&*     ...   ,  .. ...,.  ,..,,.*(@@@@@@@(*/*,*@@/*%**.   ...    .          .....");
        mvwprintw(win, 19,0, "  .##(*  ,,,*.      .....,%#***%&@@@@@@@@@@@@#*,,.#@@@&/, ..&         ...            ");
        mvwprintw(win, 20,0, ". .(%%&(*%.      .&@/,.,,.#.*, ,&&&@@@@@@@@@@,..*#@@@@@@&. . .        .  ,,,.   .....");
        mvwprintw(win, 21,0, "*..(#####&&&%##%&&&&&/(.., .%*.#@@@@@@@@@@@%..(@&%@@@@@@(,         ....%*  .//,  .,,.");
        mvwprintw(win, 22,0, "%/.  .(((/#&&&&@@@@@@&&&(. *,.#&@@@@@@@@@@@@@@@@@@@@@@@@&% .&%.     /,    ...,,....,,");
    }
}

void GameBattleControl (Enemy E, boolean * isWin)
// I.S. :
// F.S. :
{
    WINDOW* Background = CreateWindow(MaxY, MaxX, 0, 0);
    wbkgd(Background, COLOR_PAIR(1));
    wrefresh(Background);

    WINDOW* SpriteView = newwin(23, 86, 1, 8);
    wbkgd(SpriteView, COLOR_PAIR(1));
    wrefresh(SpriteView);

    WINDOW* BattleInfoBG = CreateWindow(12, 86, 25, 8);
    wbkgd(BattleInfoBG, COLOR_PAIR(6));
    wrefresh(BattleInfoBG);

    WINDOW* BattleInfo = newwin(10, 82, 26, 10);
    wbkgd(BattleInfo, COLOR_PAIR(6));
    wrefresh(BattleInfo);
    scrollok(BattleInfo, true);

    WINDOW* RoundCounter= newwin(5, 60, 17, 98);
    wbkgd(RoundCounter, COLOR_PAIR(2));

    WINDOW* EnemyStat  = CreateWindow(15, 60, 2, 98);
    wbkgd(EnemyStat, COLOR_PAIR(1));
    wrefresh(EnemyStat);

    WINDOW* EnemyCommand = newwin(4, 16, 12, 120);
    wbkgd(EnemyCommand, COLOR_PAIR(1));

    WINDOW* PlayerStat = CreateWindow(15, 60, 22, 98);
    wbkgd(PlayerStat, COLOR_PAIR(1));
    wrefresh(PlayerStat);

    WINDOW* PlayerCommand = newwin(4, 16, 32, 120);
    wbkgd(PlayerCommand, COLOR_PAIR(6));

    int CountAct, CountRound = 0;
    Stack S; // Enemy acts storage
    Queue Q, QCopy, X, XCopy;
    char InputP, InputE;
    char ga = '0';

    // Read Enemy Acts
    InputAksiMusuh(&S);

    // Draw Sprite
    DrawSprite(SpriteView, Sprite(E));
    wrefresh(SpriteView);

    wbkgd(BattleInfo, COLOR_PAIR(1));
    PrintText(BattleInfo, 4, 0, Desc(E), true, Normal);
    Pause(1000);
    wbkgd(BattleInfo, COLOR_PAIR(6));
    wclear(BattleInfo);

    // EnemyStat Fill
    mvwhline(EnemyStat, 5, 0, ACS_LTEE, 1);
    mvwhline(EnemyStat, 5, 1, 0, 58);
    mvwhline(EnemyStat, 5, 59, ACS_RTEE, 1);

    mvwhline(EnemyStat, 7, 0, ACS_LTEE, 1);
    mvwhline(EnemyStat, 7, 1, 0, 58);
    mvwhline(EnemyStat, 7, 59, ACS_RTEE, 1);

    for (int col = 1; col <= 3; col++) {
        mvwvline(EnemyStat, 5, 20*col, ACS_TTEE, 1);
        mvwvline(EnemyStat, 6, 20*col, 0, 1);
        mvwvline(EnemyStat, 7, 20*col, ACS_BTEE, 1);
    }

    if (ISBOSS(E)) {    // Special Boss Stat window
        PrintText(EnemyStat, 1, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, Fast);
        PrintText(EnemyStat, 4, 0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", true, Fast);
    }

    PrintText(EnemyStat, 2, 4, "Name  :", false, Normal);
    PrintText(EnemyStat, 2, 12, NAMA(E), false, Normal);

    PrintText(EnemyStat, 3, 4, "Level :", false, Normal);
    mvwprintw(EnemyStat, 3, 12, "%d", LV(E));


    mvwprintw(EnemyStat, 6, 6, "STR = %d", STR(E));
    mvwprintw(EnemyStat, 6, 26,"DEF = %d", DEF(E));
    mvwprintw(EnemyStat, 6, 46,"LUC = %d", LUC(E));
    wrefresh(EnemyStat);
    Pause(500);

    // PlayerStat Fill
    mvwhline(PlayerStat, 5, 0, ACS_LTEE, 1);
    mvwhline(PlayerStat, 5, 1, 0, 58);
    mvwhline(PlayerStat, 5, 59, ACS_RTEE, 1);

    mvwhline(PlayerStat, 7, 0, ACS_LTEE, 1);
    mvwhline(PlayerStat, 7, 1, 0, 58);
    mvwhline(PlayerStat, 7, 59, ACS_RTEE, 1);

    for (int col = 1; col <= 3; col++) {
        mvwvline(PlayerStat, 5, 20*col, ACS_TTEE, 1);
        mvwvline(PlayerStat, 6, 20*col, 0, 1);
        mvwvline(PlayerStat, 7, 20*col, ACS_BTEE, 1);
    }

    PrintText(PlayerStat, 2, 4, "Name  :", false, Normal);
    PrintText(PlayerStat, 2, 12, NAMA(player), false, Normal);

    PrintText(PlayerStat, 3, 4, "Level :", false, Normal);
    mvwprintw(PlayerStat, 3, 12, "%d", LV(player));

    mvwprintw(PlayerStat, 6, 6, "STR = %d", STR(player));
    mvwprintw(PlayerStat, 6, 26,"DEF = %d", DEF(player));
    mvwprintw(PlayerStat, 6, 46,"LUC = %d", LUC(player));
    wrefresh(PlayerStat);
    Pause(500);

    // Check Level 5 Passive Skill
    TurnOnPassiveSkillLevel5(BattleInfo, acquiredSkill, &player, &E);

    while (!IsOver(player, E, CountRound)) {
        // PlayerStat and EnemyStat round initializer
        if (HP(player) > (HPMAXPlayer(player)/2)) {
            wbkgd(PlayerStat, COLOR_PAIR(3));
        }
        else {
            if (HP(player) > (HPMAXPlayer(player)/5)) {
                wbkgd(PlayerStat, COLOR_PAIR(4));
            }
            else {
                wbkgd(PlayerStat, COLOR_PAIR(2));
            }
        }
        if (HP(E) > (HPMAXEnemy(player,E)/2)) {
            wbkgd(EnemyStat, COLOR_PAIR(3));
        }
        else {
            if (HP(E) > (HPMAXEnemy(player,E)/5)) {
                wbkgd(EnemyStat, COLOR_PAIR(4));
            }
            else {
                wbkgd(EnemyStat, COLOR_PAIR(2));
            }
        }
        wrefresh(EnemyStat);
        wrefresh(PlayerStat);

        CountRound++;
        CountAct = 0;

        mvwprintw(RoundCounter, 2, 26, "Round %d", (CountRound));
        wrefresh(RoundCounter);

        mvwprintw(EnemyCommand, 1, 1, " Enemy's Move");
        mvwprintw(PlayerCommand, 1, 1,"  Your Move  ");

        PrintAksiMusuh(EnemyCommand, InfoTop(S), CountAct);
        wrefresh(EnemyCommand);
        wrefresh(PlayerCommand);

        PopStack(&S, &X);
        XCopy = X;

        mvwprintw(EnemyStat, 9, 4, "HP    =    %d / %d   ", HP(E), HPMAXEnemy(player, E));
        mvwprintw(PlayerStat, 9, 4, "HP    =    %d / %d   ", HP(player), HPMAXPlayer(player));
        wrefresh(PlayerStat);
        wrefresh(EnemyStat);

        InputAksiPlayer(PlayerCommand, BattleInfo, &Q, player, acquiredSkill);
        QCopy = Q;

        while ((CountAct < 4) && (!IsOver(player, E, (CountRound-1)))) {
            wclear(EnemyCommand);
            wclear(PlayerCommand);

            wrefresh(EnemyCommand);
            wrefresh(PlayerCommand);

            wprintw(BattleInfo, "\n");
            CountAct++;
            PrintAksiMusuh(EnemyCommand, X, CountAct);
            PrintAksiPlayer(PlayerCommand, Q, CountAct);

            wrefresh(EnemyCommand);
            wrefresh(PlayerCommand);

            // Next player move
            DelQ(&QCopy, &InputP);

            // Next enemy move
            DelQ(&XCopy, &InputE);

            // Calculate Damage
            DamageTaken(BattleInfo, InputP, InputE, &player, &E, acquiredSkill);

            mvwprintw(EnemyStat, 9, 4, "HP    =    %d / %d   ", HP(E), HPMAXEnemy(player, E));
            mvwprintw(PlayerStat, 9, 4, "HP    =    %d / %d   ", HP(player), HPMAXPlayer(player));
            wrefresh(PlayerStat);
            wrefresh(EnemyStat);

            // Refresh Health View
            if (HP(player) > (HPMAXPlayer(player)/2)) {
                wbkgd(PlayerStat, COLOR_PAIR(3));
            }
            else {
                if (HP(player) > (HPMAXPlayer(player)/5)) {
                    wbkgd(PlayerStat, COLOR_PAIR(4));
                }
                else {
                    wbkgd(PlayerStat, COLOR_PAIR(2));
                }
            }
            if (HP(E) > (HPMAXEnemy(player,E)/2)) {
                wbkgd(EnemyStat, COLOR_PAIR(3));
            }
            else {
                if (HP(E) > (HPMAXEnemy(player,E)/5)) {
                    wbkgd(EnemyStat, COLOR_PAIR(4));
                }
                else {
                    wbkgd(EnemyStat, COLOR_PAIR(2));
                }
            }

            mvwprintw(EnemyStat, 9, 4, "HP    =    %d / %d   ", HP(E), HPMAXEnemy(player, E));
            mvwprintw(PlayerStat, 9, 4, "HP    =    %d / %d   ", HP(player), HPMAXPlayer(player));

            wrefresh(PlayerStat);
            wrefresh(EnemyStat);
        }

        // Cleanup
        wclear(EnemyCommand);
        wclear(PlayerCommand);
    }

    *isWin = IsWinner(player, E);

    // Clean Views
    wclear(EnemyCommand);
    wclear(PlayerCommand);
    wrefresh(EnemyCommand);
    wrefresh(PlayerCommand);

    wrefresh(EnemyStat);
    wrefresh(PlayerStat);

    wclear(BattleInfo);

    if (*isWin) {
        int PrevLV = LV(player);
        GetEXP(&player, E);


        PrintText(BattleInfo, 4, 0, "You have won the encounter!", true, Slow);
        Pause(500);
        if (LV(player) != PrevLV) {
            PrintText(BattleInfo, 5, 0, "You leveled up!", true, Slow);
        }
        Pause(1000);

        PrintText(BattleInfo, 8, 0, "Press any key to continue", true, Normal);
        char mapb = wgetch(BattleInfo);
    }
    else {
        if (HP(player) == 0) {
            wbkgd(BattleInfo, COLOR_PAIR(2));
            PrintText(BattleInfo, 3, 0, "You have been defeated!", true, Slow);
            Pause(100);
            PrintText(BattleInfo, 4, 0, "Your mind is slowly losing to her beauty.", true, Slow);
            Pause(500);
            PrintText(BattleInfo, 6, 0, "You are trapped forever in this realm.", true, Slow);
            Pause(3000);
        }
        else {
            PrintText(BattleInfo, 4, 0, "The encounter is a draw..", true, Slow);
            PrintText(BattleInfo, 5, 0, "Better luck next time", true, Slow);

            Pause(1000);
            PrintText(BattleInfo, 8, 0, "Press any key to return to map", true, Normal);
            char mapb = wgetch(BattleInfo);
        }

    }

    DeleteWindow(Background);
    DeleteWindow(SpriteView);
    DeleteWindow(BattleInfoBG);
    DeleteWindow(BattleInfo);
    DeleteWindow(RoundCounter);
    DeleteWindow(EnemyStat);
    DeleteWindow(EnemyCommand);
    DeleteWindow(PlayerStat);
    DeleteWindow(PlayerCommand);
}
