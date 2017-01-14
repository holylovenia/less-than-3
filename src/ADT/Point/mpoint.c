#include <stdio.h>
#include "../Point/point.h"

int main() {
  POINT P1,P2;
  P1 = MakePOINT(1,1);
  P2 = MakePOINT(2,2);
  printf("Absis P1 = %d\n Ordinat P1 = %d\n",Absis(P1),Ordinat(P1));
  printf("Absis P2 = %d\n Ordinat P2 = %d\n",Absis(P2),Ordinat(P2));
  return 0;
}
