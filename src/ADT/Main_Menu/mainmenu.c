#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "../../ADT/Main_Menu/mainmenu.h"

#include "../../ADT/Basestats/basestats.h"
#include "../../ADT/Array/array.h"
#include "../../ADT/Assignment/assignment.h"
#include "../../ADT/Boolean/boolean.h"
#include "../../ADT/Binary_Tree/bintree.h"
#include "../../Modul/Battle/battle.h"
#include "../Character/character.h"
#include "../General/general.h"
#include "../Graf/grafarea.h"
#include "../Map/map.h"
#include "../Matriks/matriks.h"
#include "../List_Rekursif/listrek.h"
#include "../Mesin_Kar/mesinkar.h"
#include "../Mesin_Kata/mesinkata.h"
#include "../Point/point.h"
#include "../Queue/queue.h"
#include "../Save_Index/saveindex.h"
#include "../../Modul/Save_Load/saveload.h"
#include "../../Modul/Skill_Tree/skilltree.h"
#include "../Stack/stackt.h"


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


// External Variable
Player player;

void Greetings (WINDOW* win, Menu MM)
// I.S. : In ncurses mode, win defined, P defined, MM defined
// F.S. : Print a greeting line according to player stats
{
    if (!NewPlayer(MM)) {
        if ((STR(player) > DEF(player)) && (STR(player) > LUC(player))) {
            wbkgd(win, COLOR_PAIR(2));
            PrintText(win, 1, 0, "Welcome back,", true, Normal);
            Pause(1000);
            PrintText(win, 3, 0, NAMA(player), true, Normal);
            Pause(500);
            PrintText(win, 4, 0, "The Seductive", true, Normal);
        }
        else if ((DEF(player) > STR(player)) && (DEF(player) > LUC(player))) {
            wbkgd(win, COLOR_PAIR(5));
            PrintText(win, 1, 0, "Welcome back,", true, Normal);
            Pause(1000);
            PrintText(win, 3, 0, NAMA(player), true, Normal);
            Pause(500);
            PrintText(win, 4, 0, "The Heartbreaker",true, Normal);
        }
        else if ((LUC(player) > STR(player)) && (LUC(player) > DEF(player))) {
            wbkgd(win, COLOR_PAIR(4));
            PrintText(win, 1, 0, "Welcome back,", true, Normal);
            Pause(1000);
            PrintText(win, 3, 0, NAMA(player), true, Normal);
            Pause(500);
            PrintText(win, 4, 0, "The Beloved", true, Normal);
        }
        else {
            wbkgd(win, COLOR_PAIR(6));
            PrintText(win, 1, 0, "Welcome back,", true, Normal);
            Pause(1000);
            PrintText(win, 3, 0, NAMA(player), true, Normal);
            Pause(500);
            PrintText(win, 4, 0, "The Unpredictable", true, Normal);
        }
    }
    else {
        if (NoName(MM)) {
            wbkgd(win, COLOR_PAIR(1));
            PrintText(win, 2, 0, "Greetings, unloved one", true, Normal);
        }
        else {
            wbkgd(win, COLOR_PAIR(1));
            PrintText(win, 1, 0, "Hi there,", true, Normal);
            Pause(500);
            PrintText(win, 3, 0, NAMA(player), true, Slow);
        }
    }
}

void PrintMenu (WINDOW* win, Menu MM)
// I.S. : In ncurses mode, win defined, MM defined
// F.S. : Print Logo, Greetings, followed by Menu Box out of several states
{
    if (Sub(MM) == "Main") {
        PrintText(win, 1, 3, "Start Game", false, Fast);
        PrintText(win, 3, 3, "New Game", false, Fast);
        PrintText(win, 5, 3, "Load Game", false, Fast);
        PrintText(win, 7, 3, "Options", false, Fast);
        PrintText(win, 9, 3, "Credits", false, Fast);
        PrintText(win, 11, 3, "Exit", false, Fast);
    }
    else if (Sub(MM) == "Options") {
        PrintText(win, 3, 1, "OPTIONS", false, Fast);
        Pause(500);
        PrintText(win, 5, 3, "Graphics", false, Fast);
        PrintText(win, 7, 3, "Audio", false, Fast);
        PrintText(win, 9, 3, "Back", false, Fast);
    }
    else if (Sub(MM) == "Graphics") {
        PrintText(win, 3, 1, "GRAPHICS", false, Fast);
        Pause(500);
        PrintText(win, 5, 3, "3D Engine", false, Fast);
        PrintText(win, 7, 3, "Terminal", false, Fast);
        PrintText(win, 9, 3, "Back", false, Fast);
    }
    else if (Sub(MM) == "Audio") {
        PrintText(win, 3, 1, "AUDIO", false, Fast);
        Pause(250);
        PrintText(win, 5, 3, "ON", false, Fast);
        PrintText(win, 7, 3, "OFF", false, Fast);
        PrintText(win, 9, 3, "Back", false, Fast);
    }
}


void LoadMainMenu (Menu *MM, boolean *StartGame)
// I.S. : On startup menu, P, MM defined, StartGame to indicate the state of program
// F.S. : Control all the menus
//        Select sub-menu and switch states
//        User might choose exit to end program
{
    boolean FirstTimer = true;
    boolean PopupExist = false;
    boolean LoadMode = false;

    // Reset Stats
    *StartGame = false;
    EndMenu(*MM) = false;

    // New window for main menu
    WINDOW* Background = CreateWindow(MaxY, MaxX, 0, 0);
    wbkgd(Background, COLOR_PAIR(1));
    wrefresh(Background);

    // Borderless Windows
    WINDOW* Logo = newwin(15, (MaxX-4), 1, 2);
    wbkgd(Logo, COLOR_PAIR(1));
    wrefresh(Logo);

    WINDOW* Greeting = newwin(7, (MaxX-4), 16, 2);
    wrefresh(Greeting);

    WINDOW* Menu = newwin(13, 20, 22, (MaxX-22));
    wbkgd(Menu, COLOR_PAIR(1));
    wrefresh(Menu);

    // Dummy windows
    WINDOW* help = newwin(11, 30, 24, 4);

    WINDOW* dlc = newwin(0, 0, (MaxX-2), (MaxY-1));
    wbkgd(dlc, COLOR_PAIR(2));

    WINDOW* confirm = newwin(4, 44, 31, 8);
    wbkgd(confirm, COLOR_PAIR(6));

    // Initialize LoadData
    SaveFileIndex sFI;
    ReadSaveFileIndex (&sFI);

    // Print Game Logo
    GameLogo(Logo, false);
    if (!NewPlayer(*MM)) {
        Pause(500);
        GameLogo(Logo, true);
    }

    // Animate Logo
    AnimateLogo(Logo);

    Pause(1000);

    Greetings(Greeting, *MM);
    Pause(500);

    char* PrevMenu = "UNDEFINED";
    int cy;
    int prevcy = 1;

    while (!EndMenu(*MM)) {
        // Detects if sub-menu changes
        if (PrevMenu != Sub(*MM)) {
            wclear(Menu);
            PrintMenu(Menu,*MM);
            PrevMenu = Sub(*MM);
        }

        // Prints selector (>)
        if (Sub(*MM) == "Main") {
            cy = 2*(Choice(*MM)) - 1;
        }
        else if ((Sub(*MM) == "Options") || (Sub(*MM) == "Graphics") || (Sub(*MM) == "Audio")) {
            cy = 2*(Choice(*MM)) + 3;
        }

        // Delete previous selector
        mvwprintw(Menu, prevcy, 1, " ");
        prevcy = cy;

        // Print new selector
        mvwprintw(Menu, cy, 1, ">");
        wrefresh(Menu);

        // READ INPUT
        chtype ch = wgetch(Menu);

        // Pseudo-delete dummy windows
        if ((ch == '\n') && (Sub(*MM) == "Main")) {
            wclear(help);
            wrefresh(help);
        }
        if ((ch == '\n') && (Sub(*MM) == "Options")) {
            wclear(confirm);
            wrefresh(confirm);
        }
        if (PopupExist) {
            wborder(dlc, ' ', ' ', ' ',' ',' ',' ',' ',' ');
            wclear(dlc);
            wrefresh(dlc);
            PopupExist = false;
        }

        // Actual menu control
        if ((ch == 'w') || (ch == 'W')) {
            Choice(*MM)--;
            if (Choice(*MM)<1) {
                Choice(*MM) = 1;
            }
        }
        else if ((ch == 's') || (ch == 'S')) {
            Choice(*MM)++;
            if (Sub(*MM) == "Main") {
                if (Choice(*MM)>6) {
                    Choice(*MM) = 6;
                }
            }
            else if ((Sub(*MM) == "Options")|| (Sub(*MM) == "Graphics") || (Sub(*MM) == "Audio")) {
                if (Choice(*MM)>3) {
                    Choice(*MM) = 3;
                }
            }
        }
        else if (ch == '\n') {      // Enter Key Pressed
            if (Sub(*MM) == "Main") {
                if (Choice(*MM) == 1) {     // START GAME
                    if (NoName(*MM)) {
                        WINDOW* ErrMessage = CreateWindow(10, 44, 15, (MaxX-44)/2);
                        wbkgd(ErrMessage, COLOR_PAIR(2));
                        wrefresh(ErrMessage);
                        Pause(100);
                        PrintText(ErrMessage, 2, 0, "Error", true, Fast);
                        Pause(100);
                        PrintText(ErrMessage, 2, 0, "     ", true, Fast);
                        Pause(100);
                        PrintText(ErrMessage, 2, 0, "Error", true, Fast);
                        PrintText(ErrMessage, 4, 0, "Please enter your name in New Game or", true, Fast);
                        PrintText(ErrMessage, 5, 0, "Load Game before starting the game", true, Fast);
                        PrintText(ErrMessage, 7, 0, "> OK", true, Fast);
                        chtype er = wgetch(ErrMessage);
                        while (er != '\n') {
                            er = wgetch(ErrMessage);
                        }
                        DeleteWindow(ErrMessage);
                        wclear(Greeting);
                        Greetings(Greeting, *MM);
                    }
                    else {
                        Pause(100);
                        PrintText(Greeting, 1, 0, "     Good luck!     ", true, Normal);
                        GameLogo(Logo, false);
                        Pause(500);
                        EndMenu(*MM) = true;
                        *StartGame = true;
                    }
                    Pause(1000);
                }
                else if (Choice(*MM) == 2) {    // NEW GAME
                    // NEW GAME
                    WINDOW* PromptName = CreateWindow(12, 50, 14, (MaxX-50)/2);
                    wbkgd(PromptName, COLOR_PAIR(1));

                    // Dim the other menu
                    wbkgd(Background, COLOR_PAIR(5));
                    wrefresh(Background);
                    wbkgd(Logo, COLOR_PAIR(5));
                    wrefresh(Logo);
                    wbkgd(Menu, COLOR_PAIR(5));
                    wrefresh(Menu);
                    wbkgd(help, COLOR_PAIR(5));
                    wrefresh(help);

                    PrintText(PromptName, 2, 0, "New Game", true, Normal);

                    FillHalfGameLogo(Logo, false);

                    PrintText(PromptName, 5, 0, "Hi, welcome to LessThan3", true, Normal);
                    Pause(1500);
                    PrintText(PromptName, 5, 0, "First, tell me about yourself", true, Normal);
                    Pause(1500);
                    PrintText(PromptName, 5, 0, " Could you tell me your name? ", true, Normal);
                    Pause(500);
                    PrintText(PromptName, 6, 0, "Sorry, but I am not good at remembering names.", true, Normal);
                    PrintText(PromptName, 7, 0, "Could you keep it short please?", true, Normal);
                    curs_set(true);
                    echo();

                    //mvwgetnstr(PromptName, 9, 15, NAMA(*P), 20);
                    //CreatePlayerAwal(P);

                    char* TempName = (char*) malloc (20);
                    mvwgetnstr(PromptName, 9, 15, TempName, 20);

                    noecho();
                    curs_set(false);

                    boolean Conflict = (SearchSaveFileIndex (sFI, TempName) != 0);

                    if (!Conflict) {
                        CreatePlayerAwal(&player, TempName);

                        NewPlayer(*MM) = true;
                        NoName(*MM) = false;


                        PrintText(PromptName, 5, 0, "                               ", true, MaxSpeed);
                        PrintText(PromptName, 6, 0, "                                               ", true, MaxSpeed);
                        PrintText(PromptName, 7, 0, "                                               ", true, MaxSpeed);
                        PrintText(PromptName, 9, 0, "                                               ", true, MaxSpeed);

                        PrintText(PromptName, 5, 0, "Alright, I'll see you around!", true, Normal);
                        Pause(500);
                        PrintText(PromptName, 7, 0, "<3", true, Slow);
                        Pause(1500);
                    }
                    else {
                        int choice = 1;
                        wclear(PromptName);
                        box(PromptName, 0, 0);
                        PrintText(PromptName, 2, 0, "New Game", true, MaxSpeed);
                        PrintText(PromptName, 5, 0, "A user with that name already exists.", true, Normal);
                        Pause(500);
                        PrintText(PromptName, 6, 0, "Are you sure you want to continue?", true, Normal);
                        PrintText(PromptName, 8, 0, "        > Yes           No         ", true, MaxSpeed);
                        while (Conflict) {
                            char oc = wgetch(PromptName);

                            if ((oc == 'a') || (oc == 'A')) {
                                PrintText(PromptName, 8, 0, "        > Yes           No         ", true, MaxSpeed);
                                choice = 1;
                            }
                            else if ((oc == 'd') || (oc == 'D')) {
                                PrintText(PromptName, 8, 0, "          Yes         > No         ", true, MaxSpeed);
                                choice = 2;
                            }
                            else if (oc == '\n') {
                                Conflict = false;
                            }
                        }
                        wclear(PromptName);
                        box(PromptName,0,0);

                        if (choice == 1) {
                            CreatePlayerAwal(&player, TempName);
                            NewPlayer(*MM) = true;
                            NoName(*MM) = false;

                            PrintText(PromptName, 2, 0, "New Game", true, MaxSpeed);

                            PrintText(PromptName, 5, 0, "Alright, I'll see you around!", true, Normal);
                            Pause(500);
                            PrintText(PromptName, 7, 0, "<3", true, Slow);
                            Pause(1500);
                        }
                        else {
                            PrintText(PromptName, 2, 0, "New Game", true, MaxSpeed);

                            PrintText(PromptName, 5, 0, "Please use load game instead.", true, Normal);
                            Pause(500);
                            PrintText(PromptName, 7, 0, "<3", true, Slow);
                            Pause(1500);
                        }
                    }

                    DeleteWindow(PromptName);

                    // Restore the menu
                    wbkgd(Background, COLOR_PAIR(1));
                    wrefresh(Background);
                    wbkgd(Logo, COLOR_PAIR(1));
                    wrefresh(Logo);
                    wbkgd(Menu, COLOR_PAIR(1));
                    wrefresh(Menu);
                    wbkgd(help, COLOR_PAIR(1));
                    wrefresh(help);

                    if (!NoName(*MM)) {
                        GameLogo(Logo, true);
                    }

                    wclear(Greeting);
                    Greetings(Greeting, *MM);
                }
                else if (Choice(*MM) == 3) {    // LOAD GAME
                    if (NbSaves(sFI) > 0) {
                        // Clear Menu
                        wclear(Menu);

                        // Load window startup
                        WINDOW* LoadSave = CreateWindow((MaxY-2), 34, 1, (MaxX-36));
                        wbkgd(LoadSave, COLOR_PAIR(1));

                        PrintText(LoadSave, 2, 0, "Load Game", true, Slow);
                        FillHalfGameLogo(Logo, false);
                        mvwprintw(LoadSave, 4, 4, "%d", NbSaves(sFI));
                        wrefresh(LoadSave);

                        int loadChoice = 1;
                        int screenChoice = loadChoice;
                        int prevY = 5;
                        int loadY = 1;
                        LoadMode = true;
                        int DisplayStartIndex = 1;
                        int DisplayCount;

                        while (LoadMode) {
                            // Game loading will require the player to select a name from the list of existing names in save file.
                            wclear(LoadSave);
                            box(LoadSave, 0, 0);
                            mvwprintw(LoadSave, 2, 13, "Load Game");
                            DisplayCount = 1;
                            int temp = DisplayStartIndex;
                            while ((DisplayStartIndex <= NbSaves(sFI)) && (DisplayCount <= 15)) {
                                mvwprintw (LoadSave, (2*DisplayCount)+3, 4, "%s ", SaveName(sFI, DisplayStartIndex));
                                DisplayStartIndex++;
                                DisplayCount++;
                            }
                            DisplayStartIndex = temp;

                            // Print selector
                            loadY = 2*(screenChoice) + 3;
                            mvwprintw(LoadSave, prevY, 2, " ");
                            prevY = loadY;
                            mvwprintw(LoadSave, loadY, 2, ">");
                            wrefresh(LoadSave);

                            chtype tp = wgetch(LoadSave);

                            if ((tp == 'w') || (tp == 'W')) {
                                loadChoice--;
                                if (loadChoice<1) {
                                    loadChoice = 1;
                                }

                                screenChoice--;
                                if (screenChoice<1) {
                                    screenChoice = 1;
                                    // Scrolling mechanism
                                    DisplayStartIndex--;
                                    if (DisplayStartIndex < 1) {
                                        DisplayStartIndex = 1;
                                    }
                                }

                            }
                            else if ((tp == 's') || (tp == 'S')) {
                                loadChoice++;
                                if (loadChoice>NbSaves(sFI)) {
                                    loadChoice = NbSaves(sFI);
                                    screenChoice--;
                                }
                                screenChoice++;
                                if (screenChoice>15) {
                                    screenChoice = 15;
                                    // Scrolling mechanism
                                    DisplayStartIndex++;
                                    if (DisplayStartIndex > NbSaves(sFI)) {
                                        DisplayStartIndex = NbSaves(sFI);
                                    }
                                }
                            }
                            else if ((tp == 'q') || (tp == 'Q')) {
                                LoadMode = false;
                            }
                            else if (tp == '\n') {
                                // Load Game

                                BuildSkillTree(&skillTree,&acquiredSkill);

                                Load(SaveName(sFI, loadChoice), &player, &nMedLeft, &con, &nCurrMap, &posP, &posB, &tabEnemy, &acquiredSkill);

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

                                NewPlayer(*MM) = false;
                                NoName(*MM) = false;
                                LoadMode = false;
                            }
                        }
                        // CLEANUP
                        DeleteWindow(LoadSave);
                        if (!NewPlayer(*MM)) {
                            GameLogo(Logo, true);
                            Pause(500);
                            wclear(Greeting);
                            Greetings(Greeting, *MM);
                            Pause(500);
                        }
                        PrintMenu(Menu, *MM);
                    }
                    else {
                        WINDOW* Notification = CreateWindow(12, 50, 14, (MaxX-50)/2);
                        wbkgd(Notification, COLOR_PAIR(1));

                        PrintText(Notification, 2, 0, "Load Game", true, Normal);
                        PrintText(Notification, 5, 0, "No save data found", true, Normal);
                        PrintText(Notification, 6, 0, "Please start a new game", true, Normal);
                        PrintText(Notification, 9, 0, "> OK", true, Normal);

                        char buffer = wgetch(Notification);
                        while (buffer != '\n') {
                            buffer = wgetch(Notification);
                        }

                        DeleteWindow(Notification);
                        wclear(Greeting);
                        Greetings(Greeting, *MM);
                    }
                }
                else if (Choice(*MM) == 4) {    // OPTIONS
                    Sub(*MM) = "Options";
                    Choice(*MM) = 1;
                }
                else if (Choice(*MM) == 5) {    // CREDITS
                    wbkgd(Background, COLOR_PAIR(5));
                    wrefresh(Background);

                    wclear(Logo);
                    wclear(Greeting);
                    wclear(Menu);

                    WINDOW* Credits = newwin((MaxY-2), (MaxX-4), 1, 2);
                    wbkgd(Credits, COLOR_PAIR(6));
                    wrefresh(Credits);

                    ShowCredits(Credits);

                    DeleteWindow(Credits);

                    // Restore
                    wbkgd(Background, COLOR_PAIR(1));
                    wrefresh(Background);

                    GameLogo(Logo, false);
                    AnimateLogo(Logo);

                    if (!NoName(*MM)) {
                        GameLogo(Logo, true);
                    }

                    Greetings(Greeting, *MM);
                    PrintMenu(Menu, *MM);
                }
                else if (Choice(*MM) == 6) {    // EXIT GAME
                    WINDOW* ConfirmQuit = CreateWindow(10, 40, 14, (MaxX-40)/2);
                    wbkgd(ConfirmQuit, COLOR_PAIR(6));
                    PrintText(ConfirmQuit, 2, 0, "Exit Game", true, Normal);
                    PrintText(ConfirmQuit, 5, 0, "Are you sure you want to quit?", true, Normal);
                    PrintText(ConfirmQuit, 7, 0, "     > Yes            No      ", true, Normal);
                    chtype cq = 'r';
                    int choice = 1;
                    while (cq != '\n') {
                        cq = wgetch(ConfirmQuit);
                        if (cq == 'a') {
                            PrintText(ConfirmQuit, 7, 0, "     > Yes            No      ", true, MaxSpeed);
                            choice = 1;
                        }
                        else if (cq == 'd') {
                            PrintText(ConfirmQuit, 7, 0, "       Yes          > No      ", true, MaxSpeed);
                            choice = 2;
                        }
                    }
                    DeleteWindow(ConfirmQuit);

                    if (choice == 1) {
                        GameLogo(Logo, false);
                        Pause(500);
                        EndMenu(*MM) = true;
                        *StartGame = false;
                    }
                    else {
                        wclear(Greeting);
                        Greetings(Greeting, *MM);
                    }
                }
            }
            else if (Sub(*MM) == "Options") {
                if (Choice(*MM) == 1) {
                    Sub(*MM) = "Graphics";
                    Choice(*MM) = 3;
                }
                else if (Choice(*MM) == 2) {
                    Sub(*MM) = "Audio";
                    Choice(*MM) = 3;
                }
                else if (Choice(*MM) == 3) {
                    Sub(*MM) = "Main";
                    Choice(*MM) = 4;
                }
            }
            else if ((Sub(*MM) == "Graphics") || (Sub(*MM) == "Audio")) {
                if (Choice(*MM) == 2) {
                    if (Sub(*MM) == "Graphics") {
                        PrintText(confirm, 2, 0, "Graphics has been set to Terminal", false, Normal);
                    }
                    else {
                        PrintText(confirm, 2, 0, "Audio is set to OFF", false, Normal);
                    }
                }
                else if (Choice(*MM) == 3) {
                    Sub(*MM) = "Options";
                    Choice(*MM) = 3;
                }
            }
            FirstTimer = false;
        }
        else if ((ch=='q') || (ch=='Q')) {        // q pressed
            if (Sub(*MM) == "Main") {
                WINDOW* ConfirmQuit = CreateWindow(10, 40, 14, (MaxX-40)/2);
                wbkgd(ConfirmQuit, COLOR_PAIR(6));
                PrintText(ConfirmQuit, 2, 0, "Exit Game", true, Normal);
                PrintText(ConfirmQuit, 5, 0, "Are you sure you want to quit?", true, Normal);
                PrintText(ConfirmQuit, 7, 0, "     > Yes            No      ", true, Normal);
                chtype cq = 'r';
                int choice = 1;
                while (cq != '\n') {
                    cq = wgetch(ConfirmQuit);
                    if (cq == 'a') {
                        PrintText(ConfirmQuit, 7, 0, "     > Yes            No      ", true, MaxSpeed);
                        choice = 1;
                    }
                    else if (cq == 'd') {
                        PrintText(ConfirmQuit, 7, 0, "       Yes          > No      ", true, MaxSpeed);
                        choice = 2;
                    }
                }
                DeleteWindow(ConfirmQuit);
                if (choice == 1) {
                    GameLogo(Logo, false);
                    Pause(250);
                    EndMenu(*MM) = true;
                    *StartGame = false;
                }
                else {
                    wclear(Greeting);
                    Greetings(Greeting, *MM);
                }
            }
            else if (Sub(*MM) == "Options") {
                Sub(*MM) = "Main";
                Choice(*MM) = 4;
            }
            else if ((Sub(*MM) == "Graphics") || (Sub(*MM) == "Audio")) {
                Sub(*MM) = "Options";
                Choice(*MM) = 3;
            }
            FirstTimer = false;
        }
        else {  // Random key pressed
            if (FirstTimer) {
                wbkgd(help, COLOR_PAIR(4));
                PrintText(help, 1, 2, "Menu navigation:", false, Normal);
                PrintText(help, 3, 4, "W = Select Up", false, Normal);
                PrintText(help, 5, 4, "S = Select Down", false, Normal);
                PrintText(help, 7, 4, "Enter = Select Menu", false, Normal);
                PrintText(help, 9, 4, "Q = Back / Exit", false, Normal);
                FirstTimer = false;
            }
        }

        // AUTO POP-UP NOTIFICATION when selected
        if (Choice(*MM) == 1) {
            if ((Sub(*MM) == "Graphics") || (Sub(*MM) == "Audio")) {
                // Delete previous selector
                mvwprintw(Menu, 7, 1, " ");
                // Print new selector
                mvwprintw(Menu, 5, 1, ">");
                prevcy = 5;
                cy = 7;
                wrefresh(Menu);

                if (Sub(*MM) == "Graphics") {
                    dlc = CreateWindow(4, 24, 27, (MaxX-46));
                    wbkgd(dlc, COLOR_PAIR(2));
                    wrefresh(dlc);
                    PrintText(dlc, 1, 0, "Available on DLC", true, Normal);
                    PrintText(dlc, 2, 0, "<3 : Infinite", true, Normal);
                }
                else if (Sub(*MM) == "Audio") {
                    dlc = CreateWindow(4, 24, 27, (MaxX-46));
                    wbkgd(dlc, COLOR_PAIR(2));
                    wrefresh(dlc);
                    PrintText(dlc, 1, 0, "Available on DLC", true, Normal);
                    PrintText(dlc, 2, 0, "<3 : Melodious", true, Normal);
                }
                PopupExist = true;
            }
        }
    }
    //NewPlayer(*MM) = false;

    DeleteWindow(Background);
    DeleteWindow(Logo);
    DeleteWindow(Greeting);
    DeleteWindow(Menu);

    DeleteWindow(dlc);
    DeleteWindow(help);
    DeleteWindow(confirm);
}

void InitializeMenu (Menu *MM)
// I.S. : P defined, MM defined, Flag to indicate start or end game
// F.S. : Player started game or ended the game via Quit
{
    // Initialize NCURSES
    InitializeNcurses();

    // Loading Screen
    LoadingScreen (2, true);

    // Initialize MM
    Sub(*MM) = "Main";
    Choice(*MM) = 1;
    NewPlayer(*MM) = true;
    NoName(*MM) = true;
    EndMenu(*MM) = false;

    // endwin() in main program
}
