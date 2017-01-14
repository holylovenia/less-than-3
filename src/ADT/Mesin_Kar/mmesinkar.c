#include "../../ADT/Mesin_Kar/mesinkar.h"
#include <stdio.h>

int main() {
  START("enemy.txt");
  while (CC!= MARK) {
    printf("%c",CC);
    ADV();
  }

  return 0;
}
