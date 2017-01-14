/* Driver ADT Map */
#include "../../ADT/Map/map.h"
#include "../../ADT/Graf/grafarea.h"
int main() {
  /* Kamus */
  POINT PosB;
  POINTOFENEMY E[11];
  MATRIKS A[11];
  ListArea L;
  Koneksi Con;
  addressarea P;
  POINT Pos_Player;
  POINT LocBefore;
  /* Algoritma */
  //Fitur New Game
  CreateEmptyArea(&L);
  Baca_Area(A);
  PlaceMedicine(3,A);
  SaveEnemyPoint(A,E);
  Init_List(&L, A, &Con, &PosB);

  P = FirstArea(L);
  Pos_Player = Random_Pos_Player(Map(P));

  DealokasiMap(&FirstArea(L));
  return 0;
}
