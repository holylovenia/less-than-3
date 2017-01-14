#include "../Graf/grafarea.h"

int main() {
  infotypemap X;
  addressarea P,P2;
  ListArea L;
  IndeksMap(X) = 1;
  //Test CreateEmptyArea and IsEmptyArea
  CreateEmptyArea(&L);
  if (IsEmptyArea(L)) {
    printf("CreateEmptyArea and IsEmptyArea Correct\n");
  } else {
    printf("CreateEmptyArea and IsEmptyArea Incorrect\n");
  }
  //Test AlokasiArea
  P = AlokasiArea(X);
  if (P != Nil) {
    printf("AlokasiArea Correct\n");
  } else {
    printf("AlokasiArea Incorrect\n");
  }
  //Test SetFirstArea
  CreateEmptyArea(&L);
  SetFirstArea(&L,X);
  if (!IsEmptyArea(L)) {
    printf("SetFirstArea Correct\n");
  } else {
    printf("SetFirstArea Incorrect\n");
  }
  //Test SetArea
  IndeksMap(X) = 2;
  P2 = AlokasiArea(X);
  P = FirstArea(L);
  SetArea(P2,&P,1);
  if (Neighbor(P)[1] != Nil) {
    printf("SetArea Correct\n");
  } else {
    printf("SetArea Incorrect\n");
  }
  return 0;
}
