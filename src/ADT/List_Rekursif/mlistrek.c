/* Driver ListRek */
#include "../List_Rekursif/listrek.h"
#include <stdio.h>

int main() {
  BinTree BT, BT2;
  BinTree Hasil;
  ListLR L,TL;
  infotypeBT X,Y;
  Unlocked(X) = false;
  IsPassive(X) = true;
  ID(X) = 1;
  printf("\nNama X (maks 30): ");
  scanf("%s", NamaBT(X));
  printf("Deskripsi X (maks 300): ");
  scanf("%s", Deskripsi(X));
  printf("ID X: %d\n\n", ID(X));

  Unlocked(Y) = true;
  IsPassive(Y) = false;
  ID(Y) = 2;
  printf("\nNama Y (maks 30): ");
  scanf("%s", NamaBT(Y));
  printf("Deskripsi Y (maks 300): ");
  scanf("%s", Deskripsi(Y));
  printf("ID Y: %d\n\n", ID(Y));

  BT = Tree(X,NilBT,NilBT);
  //Test AlokasiLR and IsEmptyLR
  L = AlokasiLR(BT);
  if (!IsEmptyLR(L)) {
    printf("AlokasiLR and IsEmptyLR Correct\n");
  } else {
    printf("AlokasiLR and IsEmptyLR Incorrect\n");
  }
  //Test IsOneElmtLR
  if (IsOneElmtLR(L)) {
    printf("IsOneElmtLR Correct\n");
  } else {
    printf("IsOneElmtLR Incorrect\n");
  }
  //Test FirstElmtLR
  CreateEmptyTree(&Hasil);
  Hasil = FirstElmt(L);
  if (Hasil != NilBT) {
    printf("FirstElmtLR Correct\n");
  } else {
    printf("FirstElmtLR Incorrect\n");
  }
  //Test TailLR
  TL = TailLR(L);
  if (IsEmptyLR(TL)) {
    printf("TailLR Correct\n");
  } else {
    printf("TailLR Incorrect\n");
  }
  //Test Konso
  BT2 = Tree(Y,NilBT,NilBT);
  L = Konso(BT2,L);
  printf("Konso Correct if ID == 2, ID = %d\n",ID(Akar(FirstElmt(L))));
  //Test KonsB
  L = NilLR;
  L = KonsB(L,BT);
  L = KonsB(L,BT2);
  printf("KonsB Correct if ID == 2, ID = %d\n",ID(Akar(FirstElmt(TailLR(L)))));

  //Test PrintListLR
  PrintListLR(L);
  //Test SearchLR
  if (SearchLR(L,BT)) {
    printf("SearchLR Correct\n");
  } else {
    printf("SearchLR Incorrect\n");
  }

  return 0;

}
