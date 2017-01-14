OBJS = LessThan3.o mainmenu.o gameui.o interface.o basestats.o mesinkata.o mesinkar.o skilltree.o battle.o assignment.o bintree.o general.o grafarea.o listrek.o map.o matriks.o point.o array.o queue.o statistic.o stackt.o saveload.o waktu.o saveindex.o character.o
DRIVER =
ObjectDir = obj/
CC = gcc
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)

all :
	make driver
	make main
	make clean


driver : marray mwaktu mstackt mqueue mpoint mbintree mgrafarea mmesinkar msaveindex massignment mmatriks mbasestats mcharacter mlistrek mmainmenu mmap

main : LessThan3

LessThan3 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -lncurses -lm -o bin/LessThan3/LessThan3

LessThan3.o : src/Main/LessThan3.c src/ADT/Main_Menu/mainmenu.c src/Modul/Interface/interface.c src/Modul/Game_UI/gameui.c
	$(CC) $(CFLAGS) src/Main/LessThan3.c

marray : marray.o array.o
	$(CC) $(LFLAGS) marray.o array.o -o bin/Driver/marray
mwaktu : mwaktu.o waktu.o
	$(CC) $(LFLAGS) mwaktu.o waktu.o -o bin/Driver/mwaktu
mstackt : mstackt.o stackt.o queue.o
	$(CC) $(LFLAGS) mstackt.o stackt.o queue.o -o bin/Driver/mstackt
mqueue : mqueue.o queue.o
	$(CC) $(LFLAGS) mqueue.o queue.o -o bin/Driver/mqueue
mpoint : mpoint.o point.o
	$(CC) $(LFLAGS) mpoint.o point.o -o bin/Driver/mpoint
mbintree : mbintree.o bintree.o
	$(CC) $(LFLAGS) mbintree.o bintree.o -o bin/Driver/mbintree
mgrafarea : mgrafarea.o grafarea.o point.o matriks.o
	$(CC) $(LFLAGS) mgrafarea.o grafarea.o point.o matriks.o -lncurses -o bin/Driver/mgrafarea
mmesinkar : mmesinkar.o mesinkar.o general.o
	$(CC) $(LFLAGS) mmesinkar.o mesinkar.o general.o -o bin/Driver/mmesinkar
msaveindex : msaveindex.o saveindex.o character.o waktu.o mesinkata.o general.o mesinkar.o
	$(CC) $(LFLAGS) msaveindex.o saveindex.o waktu.o mesinkata.o general.o mesinkar.o -lncurses -o bin/Driver/msaveindex
massignment : massignment.o assignment.o matriks.o point.o map.o mesinkata.o mesinkar.o grafarea.o array.o general.o basestats.o
	$(CC) $(LFLAGS) massignment.o assignment.o matriks.o point.o map.o mesinkata.o mesinkar.o grafarea.o array.o general.o basestats.o -lncurses -o bin/Driver/massignment
mmatriks : matriks.o mmatriks.o
	$(CC) $(LFLAGS) matriks.o mmatriks.o -lncurses -o bin/Driver/mmatriks
mbasestats : mbasestats.o basestats.o mesinkata.o mesinkar.o general.o
	$(CC) $(LFLAGS) mbasestats.o basestats.o mesinkata.o mesinkar.o general.o -lncurses -o bin/Driver/mbasestats
mcharacter : mcharacter.o character.o general.o basestats.o mesinkata.o mesinkar.o statistic.o
	$(CC) $(LFLAGS) mcharacter.o character.o general.o basestats.o mesinkata.o mesinkar.o statistic.o -lm -lncurses -o bin/Driver/mcharacter
mlistrek : mlistrek.o listrek.o bintree.o
	$(CC) $(LFLAGS) mlistrek.o listrek.o bintree.o -o bin/Driver/mlistrek
mmainmenu : mmainmenu.o mainmenu.o interface.o map.o grafarea.o matriks.o array.o mesinkar.o mesinkata.o point.o skilltree.o basestats.o character.o general.o listrek.o bintree.o statistic.o saveload.o waktu.o saveindex.o
	$(CC) $(LFLAGS) mmainmenu.o mainmenu.o interface.o map.o grafarea.o matriks.o array.o mesinkar.o mesinkata.o point.o skilltree.o basestats.o character.o general.o listrek.o bintree.o statistic.o saveload.o waktu.o saveindex.o -lm -lncurses -o bin/Driver/mmainmenu
mmap : mmap.o map.o array.o grafarea.o matriks.o mesinkata.o mesinkar.o general.o point.o
	$(CC) $(LFLAGS) mmap.o map.o  array.o grafarea.o matriks.o mesinkata.o mesinkar.o general.o point.o -lm -lncurses -o bin/Driver/mmap

marray.o : src/ADT/Array/array.h src/ADT/Array/array.c
	$(CC) $(CFLAGS) src/ADT/Array/marray.c
mwaktu.o : src/ADT/Waktu/waktu.h src/ADT/Waktu/waktu.c
	$(CC) $(CFLAGS) src/ADT/Waktu/mwaktu.c
mstackt.o : src/ADT/Stack/stackt.h src/ADT/Stack/stackt.c src/ADT/Queue/queue.c
	$(CC) $(CFLAGS) src/ADT/Stack/mstackt.c
mqueue.o : src/ADT/Queue/queue.h src/ADT/Queue/queue.c
	$(CC) $(CFLAGS) src/ADT/Queue/mqueue.c
mpoint.o : src/ADT/Point/point.h src/ADT/Point/point.c
	$(CC) $(CFLAGS) src/ADT/Point/mpoint.c
mbintree.o : src/ADT/Binary_Tree/bintree.h src/ADT/Binary_Tree/bintree.c
	$(CC) $(CFLAGS) src/ADT/Binary_Tree/mbintree.c
mgrafarea.o : src/ADT/Graf/grafarea.h src/ADT/Graf/grafarea.c src/ADT/Matriks/matriks.c src/ADT/Point/point.c
	$(CC) $(CFLAGS) src/ADT/Graf/mgrafarea.c
msaveindex.o : src/ADT/Save_Index/saveindex.h src/ADT/Save_Index/saveindex.c
	$(CC) $(CFLAGS) src/ADT/Save_Index/msaveindex.c
mmesinkar.o : src/ADT/Mesin_Kar/mesinkar.h src/ADT/Mesin_Kar/mesinkar.c src/ADT/General/general.c
	$(CC) $(CFLAGS) src/ADT/Mesin_Kar/mmesinkar.c
massignment.o : src/ADT/Assignment/assignment.h src/ADT/Assignment/assignment.c
	$(CC) $(CFLAGS) src/ADT/Assignment/massignment.c
mmatriks.o : src/ADT/Matriks/matriks.h src/ADT/Matriks/matriks.c
	$(CC) $(CFLAGS) src/ADT/Matriks/mmatriks.c
mbasestats.o : src/ADT/Basestats/basestats.h src/ADT/Basestats/basestats.c
	$(CC) $(CFLAGS) src/ADT/Basestats/mbasestats.c
mcharacter.o : src/ADT/Character/character.h src/ADT/Character/character.c
	$(CC) $(CFLAGS) src/ADT/Character/mcharacter.c
mlistrek.o : src/ADT/List_Rekursif/listrek.h src/ADT/List_Rekursif/listrek.c
	$(CC) $(CFLAGS) src/ADT/List_Rekursif/mlistrek.c
mmainmenu.o : src/ADT/Main_Menu/mainmenu.h src/ADT/Main_Menu/mainmenu.c
	$(CC) $(CFLAGS) src/ADT/Main_Menu/mmainmenu.c
mmap.o : src/ADT/Map/map.h src/ADT/Map/map.c
	$(CC) $(CFLAGS) src/ADT/Map/mmap.c


battle.o : src/Modul/Battle/battle.h src/Modul/Battle/battle.c src/ADT/Character/character.c src/ADT/Mesin_Kata/mesinkata.c src/Modul/Skill_Tree/skilltree.c src/Modul/Statistic/statistic.c src/ADT/Stack/stackt.c src/Modul/Interface/interface.c src/ADT/Basestats/basestats.c src/ADT/Queue/queue.c src/ADT/Array/marray.c
	$(CC) $(CFLAGS) src/Modul/Battle/battle.c
saveload.o : src/Modul/Save_Load/saveload.h src/Modul/Save_Load/saveload.c src/ADT/Character/character.c src/ADT/General/general.c src/ADT/List_Rekursif/listrek.c src/ADT/Map/map.c src/ADT/Assignment/assignment.c src/ADT/Mesin_Kata/mesinkata.c src/Modul/Skill_Tree/skilltree.c src/ADT/Waktu/waktu.c src/ADT/Save_Index/saveindex.c
	$(CC) $(CFLAGS) src/Modul/Save_Load/saveload.c
skilltree.o : src/Modul/Skill_Tree/skilltree.h src/Modul/Skill_Tree/skilltree.c src/ADT/Character/character.c src/ADT/List_Rekursif/listrek.c src/ADT/Binary_Tree/bintree.c src/Modul/Statistic/statistic.c src/ADT/General/general.c
	$(CC) $(CFLAGS) src/Modul/Skill_Tree/skilltree.c
statistic.o : src/Modul/Statistic/statistic.h src/Modul/Statistic/statistic.c src/ADT/Character/character.c src/ADT/Basestats/basestats.c
	$(CC) $(CFLAGS) src/Modul/Statistic/statistic.c
interface.o : src/Modul/Interface/interface.h src/Modul/Interface/interface.c
	$(CC) $(CFLAGS) src/Modul/Interface/interface.c
gameui.o : src/Modul/Game_UI/gameui.h src/Modul/Game_UI/gameui.c src/Modul/Interface/interface.c src/ADT/Basestats/basestats.c src/ADT/Array/array.c src/ADT/Assignment/assignment.c src/ADT/Binary_Tree/bintree.c src/Modul/Battle/battle.c src/ADT/Character/character.c src/ADT/General/general.c src/ADT/Graf/grafarea.c src/ADT/List_Rekursif/listrek.c src/ADT/Map/map.c src/ADT/Matriks/matriks.c src/ADT/Matriks/matriks.h src/ADT/Point/point.c src/ADT/Queue/queue.c src/ADT/Mesin_Kata/mesinkata.c src/ADT/Mesin_Kar/mesinkar.c src/ADT/Stack/stackt.c src/Modul/Skill_Tree/skilltree.c src/Modul/Save_Load/saveload.c src/ADT/Save_Index/saveindex.c src/Modul/Statistic/statistic.c
	$(CC) $(CFLAGS) src/Modul/Game_UI/gameui.c

bintree.o : src/ADT/Binary_Tree/bintree.h src/ADT/Binary_Tree/bintree.c
	$(CC) $(CFLAGS) src/ADT/Binary_Tree/bintree.c
waktu.o : src/ADT/Waktu/waktu.h src/ADT/Waktu/waktu.c
	$(CC) $(CFLAGS) src/ADT/Waktu/waktu.c
point.o : src/ADT/Point/point.h src/ADT/Point/point.c
	$(CC) $(CFLAGS) src/ADT/Point/point.c
stackt.o : src/ADT/Stack/stackt.h src/ADT/Stack/stackt.c src/ADT/Queue/queue.c
	$(CC) $(CFLAGS) src/ADT/Stack/stackt.c
saveindex.o : src/ADT/Save_Index/saveindex.h src/ADT/Save_Index/saveindex.c src/ADT/Character/character.c src/ADT/Waktu/waktu.c src/ADT/Mesin_Kata/mesinkata.c src/ADT/General/general.c
	$(CC) $(CFLAGS) src/ADT/Save_Index/saveindex.c
queue.o : src/ADT/Queue/queue.h src/ADT/Queue/queue.c
	$(CC) $(CFLAGS) src/ADT/Queue/queue.c
mesinkata.o : src/ADT/Mesin_Kata/mesinkata.h src/ADT/Mesin_Kata/mesinkata.c
	$(CC) $(CFLAGS) src/ADT/Mesin_Kata/mesinkata.c
mesinkar.o : src/ADT/Mesin_Kar/mesinkar.h src/ADT/Mesin_Kar/mesinkar.c src/ADT/General/general.c
	$(CC) $(CFLAGS) src/ADT/Mesin_Kar/mesinkar.c
matriks.o : src/ADT/Matriks/matriks.h src/ADT/Matriks/matriks.c
	$(CC) $(CFLAGS) src/ADT/Matriks/matriks.c
map.o : src/ADT/Map/map.h src/ADT/Map/map.c src/ADT/Mesin_Kata/mesinkata.c src/ADT/Mesin_Kar/mesinkar.c src/ADT/Array/array.c src/Modul/Interface/interface.c src/ADT/Graf/grafarea.c
	$(CC) $(CFLAGS) src/ADT/Map/map.c
mainmenu.o : src/ADT/Main_Menu/mainmenu.h src/ADT/Main_Menu/mainmenu.c src/Modul/Statistic/statistic.c src/Modul/Interface/interface.c src/ADT/Basestats/basestats.c src/ADT/Array/array.c src/ADT/Assignment/assignment.c src/ADT/Binary_Tree/bintree.c src/Modul/Battle/battle.c src/ADT/Character/character.c src/ADT/Graf/grafarea.c src/ADT/General/general.c src/ADT/Map/map.c src/ADT/Mesin_Kata/mesinkata.c src/ADT/Mesin_Kar/mesinkar.c src/ADT/Matriks/matriks.c src/ADT/List_Rekursif/listrek.c src/ADT/Point/point.c src/ADT/Save_Index/saveindex.c src/ADT/Queue/queue.c src/Modul/Save_Load/saveload.c src/Modul/Skill_Tree/skilltree.c src/ADT/Stack/stackt.c
	$(CC) $(CFLAGS) src/ADT/Main_Menu/mainmenu.c
listrek.o : src/ADT/List_Rekursif/listrek.h src/ADT/List_Rekursif/listrek.c src/ADT/Binary_Tree/bintree.c
	$(CC) $(CFLAGS) src/ADT/List_Rekursif/listrek.c
grafarea.o : src/ADT/Graf/grafarea.h src/ADT/Graf/grafarea.c src/ADT/Matriks/matriks.c src/ADT/Point/point.c
	$(CC) $(CFLAGS) src/ADT/Graf/grafarea.c
general.o : src/ADT/General/general.h src/ADT/General/general.c src/ADT/Character/character.c
	$(CC) $(CFLAGS) src/ADT/General/general.c
character.o : src/ADT/Character/character.h src/ADT/Character/character.c src/ADT/General/general.c src/ADT/Basestats/basestats.c src/Modul/Statistic/statistic.c
	$(CC) $(CFLAGS) src/ADT/Character/character.c
basestats.o : src/ADT/Basestats/basestats.h src/ADT/Basestats/basestats.c src/ADT/Mesin_Kata/mesinkata.c src/ADT/Mesin_Kar/mesinkar.c
	$(CC) $(CFLAGS) src/ADT/Basestats/basestats.c
assignment.o : src/ADT/Assignment/assignment.h src/ADT/Assignment/assignment.c src/ADT/Basestats/basestats.c src/ADT/Map/map.c src/ADT/Character/character.c src/ADT/Matriks/matriks.c src/ADT/Array/array.c src/ADT/General/general.c
	$(CC) $(CFLAGS) src/ADT/Assignment/assignment.c
array.o : src/ADT/Array/array.h src/ADT/Array/array.c
	$(CC) $(CFLAGS) src/ADT/Array/array.c

clean:
	\rm *.o
