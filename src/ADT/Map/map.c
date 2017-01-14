#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Map/map.h"
#include "../Array/array.h"
#include "../Mesin_Kar/mesinkar.h"
#include "../Mesin_Kata/mesinkata.h"

#include "../../Modul/Interface/interface.h"

void HapusGate(addressarea *P) {
/*  I.S : P terdefinisi, P dapat berisi nilai Nil
    F.S : Setiap node yang tidak memiliki koneksi, gate akan dihapus
    Setiap node akan dikunjungi dan akan dicek apakah setiap gate akan memiliki addressarea Neighbor
		yang berkorenspodensi dengannya, jika tidak maka gate akan dihapus, jika berisi suatu
    addressarea maka node tersebut akan dikunjungi untuk dicek lagi jika belum pernah
    dikunjungi sebelumnya
*/
  int i;
  if (*P == Nil) {
    //Do Nothing
  } else if (Visited(*P)) {
    //Do Nothing
  } else {
    Visited(*P) = true;
    i = 1;
    while (i<=MaxNeighbor) {
      HapusGate(&Neighbor(*P)[i]);
      i++;
    }
    i = 1;
    while (i <= MaxNeighbor) {
      if (Elmt(Map(*P),Ordinat(GateDepart(InfoMap(*P))[i]),Absis(GateDepart(InfoMap(*P))[i]) ) == '.' && Neighbor(*P)[i] == Nil) {
        Elmt(Map(*P),Ordinat(GateDepart(InfoMap(*P))[i]),Absis(GateDepart(InfoMap(*P))[i]) ) = '#';
      }
      i++;
    }
  }
}
void DealokasiMap(addressarea *P) {
/*
  I.S : P terdefinisi, P dapat berisi nilai Nil
  F.S : Semua nilai visited dari P diset false dan setiap addressarea area akan didealokasi
*/
  int i;
  if (*P == Nil) {
    //Do Nothing
  } else if (!Visited(*P)) {
    //Do Nothing
  } else {
    Visited(*P) = false;
    i = 1;
    while (i<=MaxNeighbor) {
      DealokasiMap(&Neighbor(*P)[i]);
      i++;
    }
    DealokasiArea(*P);
  }
}
//void GetMapAddressFromIndex(int nCurrMap, addressarea *currMap) {
/*  I.S : P terdefinisi (dapat bernilai Nil), currMap bernilai nil
    F.S : currMap berisi alamat area dengan indeks nCurrMap. Jika tidak ada, *currMap tetap bernilai nil
*/
	/*int i;
	if (*currMap == Nil) {
		// Do nothing
	} else if (Visited(*currMap)) {
		// Do nothing
	} else if (IndeksMap(InfoMap(*currMap)) == nCurrMap) {
		// Do nothing
	} else {
		Visited(*currMap) = true;
		for (i = 1; i <= MaxNeighbor; i++)
			GetMapAddressFromIndex(nCurrMap,currMap);
	}
}*/
void SetAllVisitedAreaToFalse(addressarea *P) {
/*
  I.S : P terdefinisi, P dapat berisi nilai Nil
  F.S : Semua nilai visited dari P diset false
*/
  int i;
  if (*P == Nil) {
    //Do Nothing
  } else if (!Visited(*P)) {
    //Do Nothing
  } else {
    Visited(*P) = false;
    i = 1;
    while (i<=MaxNeighbor) {
      SetAllVisitedAreaToFalse(&Neighbor(*P)[i]);
      i++;
    }
  }
}
void GetMapAddressFromIndex(int nCurrMap, addressarea mapAddr, addressarea *currMap) {
	int i;
	if (mapAddr == Nil) {
		// Do nothing
	} else if (Visited(mapAddr)) {
		// Do nothing
	} else {
		Visited(mapAddr) = true;
		if (IndeksMap(InfoMap(mapAddr)) == nCurrMap) {
			*currMap = mapAddr;
		} else {
			for (i = 1; (i <= MaxNeighbor) && (*currMap == Nil); i++)
				GetMapAddressFromIndex(nCurrMap,Neighbor(mapAddr)[i],currMap);
		}
	}
}


void LoadEnemy(POINTOFENEMY PosEnemy[MaxMap+1], infotypemap *X) {
/*
  I.S : X terdefinisi dan array PosEnemy berisi setiap koordinat musuh di suatu map
  F.S : Map dari infotypemap akan dirubah kembali posisi musuhnya sehingga menjadi seperti awalnya
        yaitu enemy dapat respawn kembali
*/
  int index;
  int i;
  index = IndeksMap(*X);
  for (i = 1; i<=LengthPOINTOFENEMY(PosEnemy[index]); i++) {
    Elmt(MapInfo(*X), Ordinat(PositionEnemy(PosEnemy[index])[i]),Absis(PositionEnemy(PosEnemy[index])[i])) = 'E';
  }
}
void EmptyGateInfo(infotypemap *X) {
/* I.S : X terdefinisi
   F.S : Nilai yang berhubungan dengan Gate akan diassign menjadi Point(0,0).
*/
  int i = 0;
  while (i<=MaxNeighbor) {
    ElmtGateArrived((*X),i) = MakePOINT(0,0);
    i++;
  }
  i = 0;
  while (i<=MaxNeighbor) {
    ElmtGateDeparted((*X),i) = MakePOINT(0,0);
    i++;
  }
}
void SaveEnemyPoint(MATRIKS A[MaxMap+1], POINTOFENEMY *PosEnemy) {
/*
    I.S : A adalah array of area yang terdefinisi dan tidak kosong
    F.S : Setiap posisi musuh di suatu map akan di catat dan di simpan di array of Point PosEnemy
*/
  int index;
  int i,j;
  for (index = 1; index <= MaxMap; index++) {
    LengthPOINTOFENEMY(PosEnemy[index]) = 0;
    for (i = 1; i<= GridY; i++) {
      for (j = 1; j<=GridX; j++) {
        if (Elmt(A[index],i,j) == 'E') {
          LengthPOINTOFENEMY(PosEnemy[index])++;
          PositionEnemy(PosEnemy[index])[LengthPOINTOFENEMY(PosEnemy[index])] = MakePOINT(j,i);
        }
      }
    }
  }
}
void SearchGateCopyMatrix(infotypemap *X,MATRIKS A[MaxMap+1], int arrrandomnumber[MaxMap+1]){
/*
  Mencari setiap koordinat gate dari masing - masing area dan mencopy matriks A ke matriks infotype X
  I.S : X berisi array of infotypemap yang kosong, A berisi array of area dimana area adalah matrix of char
        dan arrrandomnumber berisi bilangan random yang unik dan telah berisi nilai
  F.S : X berisi array of infotypemap yang setiap elemennya berisi area A[index] dimana setiap index diambil
        dari arrandomnumber[i]
*/
  int i,j,k,n;
  for (k = 1; k<=MaxMap; k++) {
    CopyMATRIKS(A[arrrandomnumber[k]],&MapInfo(X[k]));
    EmptyGateInfo(&X[k]);
    IndeksMap(X[k]) = arrrandomnumber[k];
    n = 0;
    //Search All Gate at Top
    i = 1; j = 1;
    while (j<=GridX) {
      if (Elmt(A[arrrandomnumber[k]],i,j) == '.') {
        n++;
        ElmtGateDeparted(X[k],n) = MakePOINT(j,i);
      }
      j++;
    }
    //Search All Gate at Right
    i = 1; j = GridX;
    while (i<=GridY) {
      if (Elmt(A[arrrandomnumber[k]],i,j) == '.') {
        n++;
        ElmtGateDeparted(X[k],n) = MakePOINT(j,i);
      }
      i++;
    }
    //Search All Gate at Down
    i = GridY; j = GridX;
    while (j >= 1) {
      if (Elmt(A[arrrandomnumber[k]],i,j) == '.') {
        n++;
        ElmtGateDeparted(X[k],n) = MakePOINT(j,i);
      }
      j--;
    }
    //Search All Gate at Left
    i = GridY; j = 1;
    while (i >= 1) {
      if (Elmt(A[arrrandomnumber[k]],i,j) == '.') {
        n++;
        ElmtGateDeparted(X[k],n) = MakePOINT(j,i);
      }
      i--;
    }
  }
}
void Baca_Area(MATRIKS *A) {
/*
  I.S : Matriks A terdefinisi
  F.S : Matriks A berisi semua area yang telah dibaca dari file eksternal
*/
  int kol,brs;
  int i;
  START("map.txt");
  for (i=1; i<=MaxMap; i++) {
    ADVKATA();
    while (CC != '#') ADV();
    MakeMATRIKS(GridY,GridX,&(A[i]));
    brs = 1;
    kol = 1;
    while (CC != '*' && CC!=MARK) {
      if (CC == '\n') {
        brs++;
        kol = 1;
      } else if (CC == '\r') {
		ADV();
		if (CC == '\n') {
			brs++;
			kol = 1;
      }
      } else {
        Elmt(A[i],brs,kol) = CC;
        kol++;
      }
      ADV();
    }
  }
  ADVKATA();
}
void LoadMap(ListArea *L, MATRIKS A[MaxMap+1], Koneksi Connection, POINT PBos) {
/*
  I.S : ListArea L kosong, Connection berisi nilai koneksi, MATRIKS A[11] akan berisi semua area yang dibaca dari file eksternal
  		  dan berisi koordinat dari bos pada map yang paling jauh
  F.S : Akan terbentuk map yang sama dari parameter input connection
  Koneksi Connection akan dibaca dan dari koneksi tersebut akan digenerate map yang sama dengan
  yang tertulis di koneksi
*/
  int i;
  int j,k;
  infotypemap X[MaxMap+1];
  int urutan[MaxMap+1];
  addressarea P1,P2;

  j = 0;

  for (i = 1; i<= LengthKoneksi(Connection); i++) {
    if (NomorMap(Pilihan(Connection)[i]) > 0) {
      j++;
      urutan[j] = NomorMap(Pilihan(Connection)[i]);
    }
  }
  SearchGateCopyMatrix(X,A,urutan);

  Elmt(MapInfo(X[MaxMap]),Ordinat(PBos),Absis(PBos)) = 'B';
  j = 0;
  for ( i = 1; i<=LengthKoneksi(Connection); i++) {
    if (Arah(Pilihan(Connection)[i]) == 0) {
	    j++;
      SetFirstArea(L,X[j]);
      P2 = FirstArea(*L);
    } else if (Arah(Pilihan(Connection)[i]) >= 1 && Arah(Pilihan(Connection)[i]) <= MaxNeighbor) {
      j++;
      P1 = AlokasiArea(X[j]);
      SetArea(P1,&P2,Arah(Pilihan(Connection)[i]));
      k = Arah(Pilihan(Connection)[i]) + 2;
      if (k > MaxNeighbor) {
        k = k - MaxNeighbor;
      }
      GateArrived(InfoMap(P2))[Arah(Pilihan(Connection)[i])] = GateDepart(InfoMap(P1))[k];
      SetArea(P2,&P1,k);
      GateArrived(InfoMap(P1))[k] = GateDepart(InfoMap(P2))[Arah(Pilihan(Connection)[i])];
    } else if (Arah(Pilihan(Connection)[i]) > MaxNeighbor) {
	    k = Arah(Pilihan(Connection)[i]) - MaxNeighbor;
      P2 = Neighbor(P2)[k];
    }
  }

  P2 = FirstArea(*L);
  HapusGate(&P2);
}
void PlaceMedicine(int N, MATRIKS A[MaxMap+1]) {
/*
	I.S : array of matriks A terdefinisi, N menandakan berapa medicine yang ingin ditaruh pada area acak yang dipilih dari
				array of matriks A indeks acak
	F.S : array of matriks A akan berisi N medicine
*/
  int i,x,y;
  int randomnumber;
  boolean sudahmap[MaxMap+1];
  for (i = 1; i<=MaxMap; i++) {
    sudahmap[i] = false;
  }
  i = 1;
  while (i<=N) {
    randomnumber = rand()%MaxMap;
    randomnumber++;
    while (!sudahmap[randomnumber]) {
      sudahmap[randomnumber] = true;
    }
    x = rand() % GridX;
    x++;
    y = rand() % GridY;
    y++;
    while (x == GridX || x == 1 || Elmt(A[randomnumber],y,x) == '#' || y == 1 || y == GridY || Elmt(A[randomnumber],y,x) == 'E' || Elmt(A[randomnumber],y,x) == 'M') {
      x = rand() % GridX;
      x++;
      y = rand() % GridY;
      y++;
    }
    Elmt(A[randomnumber],y,x) = 'M';
    i++;
  }
}

void PlaceBoss(MATRIKS *M, POINT *Position) {
/* Menaruh bos di area acak kecuali area pertama
   I.S : M terdefinisi
   F.S : Matriks M dengan nilai titik random akan diganti menjadi karakter 'B'
*/
  int x,y;
  x = rand() % GridX;
  x++;
  y = rand() % GridY;
  y++;
  while (x == GridX || x == 1 || Elmt(*M,y,x) == '#' || y == 1 || y == GridY || Elmt(*M,y,x) == 'E' || Elmt(*M,y,x) == 'M') {
    x = rand() % GridX;
    x++;
    y = rand() % GridY;
    y++;
  }
  *Position = MakePOINT(x,y);
  Elmt(*M,y,x) = 'B';
}
void Init_List(ListArea *L, MATRIKS A[11], Koneksi *Con, POINT *PosB) {
/*  I.S : ListArea L memiliki nilai Nil
    F.S : Terbentuk peta yang saling terhubung dari setiap node yang memiliki area
          yang diambil dari array of matriks A
*/
  addressarea P1,P2;
  int i;
  int j,k;
  int randomnumber,randomindex;
  TabInt arrRand;

  infotypemap X[11];
  boolean sudahmap[11];

  //Generate array of random number
  MakeEmptyTab(&arrRand);
  for (i = 1; i <= MaxMap; i++) {
	  ElmtTab(arrRand,i) = i;
  }
  Neff(arrRand) = MaxMap;
  ShuffleTab(&arrRand);

  SearchGateCopyMatrix(X,A,TI(arrRand));

  PlaceBoss(&(MapInfo(X[MaxMap])),PosB);

  LengthKoneksi(*Con) = 0;

  LengthKoneksi(*Con)++;
  Arah(Pilihan(*Con)[1]) = 0;
  NomorMap(Pilihan(*Con)[1]) = ElmtTab(arrRand,1);
  SetFirstArea(L,X[1]);
  P2 = FirstArea(*L);
  i = 2;

  while (i <= MaxMap) {
    randomindex = rand() % (MaxNeighbor * 2);
    randomindex++;
    if (randomindex <= MaxNeighbor && Neighbor(P2)[randomindex] == Nil) {
      LengthKoneksi(*Con)++;
      Arah(Pilihan(*Con)[LengthKoneksi(*Con)]) = randomindex;
      NomorMap(Pilihan(*Con)[LengthKoneksi(*Con)]) = ElmtTab(arrRand,i);

      P1 = AlokasiArea(X[i]);
      SetArea(P1,&P2,randomindex);
      k = randomindex + 2;
      if (k > MaxNeighbor) {
        k = k - MaxNeighbor;
      }
      GateArrived(InfoMap(P2))[randomindex] = GateDepart(InfoMap(P1))[k];
      SetArea(P2,&P1,k);
      GateArrived(InfoMap(P1))[k] = GateDepart(InfoMap(P2))[randomindex];

      i++;
    } else if (randomindex > MaxNeighbor && Neighbor(P2)[randomindex - MaxNeighbor] != Nil) {
      LengthKoneksi(*Con)++;
      Arah(Pilihan(*Con)[LengthKoneksi(*Con)]) = randomindex;
      NomorMap(Pilihan(*Con)[LengthKoneksi(*Con)]) = 0;

      P2 = Neighbor(P2)[randomindex - MaxNeighbor];
    }
  }

  //Untuk menghapus semua gate yang tidak memiliki jalan
  P2 = FirstArea(*L);
  HapusGate(&P2);
}
POINT Random_Pos_Player(MATRIKS M) {
/*
  Menghasilkan Posisi Random Player saat di awal permainan dengan beberapa constraint
  I.S : Matriks M terdefinisi dan tidak kosong
  F.S : Menghasilkan posisi random untuk player dimana di point tersebut tidak terdapat simbol 'E', simbol 'M'
        ataupun simbol '#'
*/
  int x,y;
  x = rand() % GridX;
  x++;
  y = rand() % GridY;
  y++;
  while (x == GridX || x == 1 || Elmt(M,y,x) == '#' || y == 1 || y == GridY || Elmt(M,y,x) == 'E' || Elmt(M,y,x) == 'M') {
    x = rand() % GridX;
    x++;
    y = rand() % GridY;
    y++;
  }
  return (MakePOINT(x,y));
}
