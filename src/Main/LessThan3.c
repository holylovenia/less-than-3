// COMPILER
// gcc array.c assignment.c basestats.c battle.c bintree.c character.c general.c grafarea.c listrek.c map.c matriks.c mesinkar.c mesinkata.c point.c queue.c saveload.c skilltree.c stackt.c statistic.c prototest.c interface.c mainmenu.c gameui.c saveindex.c waktu.c -lm -lncurses -o prototest

// 16 COLOR
// #04252e:#A31929:#00b159:#ffc425:#3b5998:#F799B5:#66cccc:#94a3a5:#46585D:#dc322f:#329f69:#ffca66:#268bd2:#F799B5:#7FC6C1:#ffffff


#include <ncurses.h>

#include "../ADT/Main_Menu/mainmenu.h"
#include "../Modul/Interface/interface.h"
#include "../Modul/Game_UI/gameui.h"

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


int main() {

    Menu MM;
    boolean Start;

    Start = true;

    // Initialize Menu
    InitializeMenu(&MM);

    // Menu Loop
    while (Start) {
        LoadMainMenu(&MM, &Start);

        if (Start) {
            //OpeningCutscene(NewPlayer(MM));
            if (NewPlayer(MM)) {
                // Initialize map and enemy
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
            else {}

            // Game Start!
            GameMapControl(&posP, currMap, enemyLoc);
            
            // Re-define
            NewPlayer(MM) = false;
        }
    }

    DealokasiMap(&currMap);

    endwin();
    return 0;
}
