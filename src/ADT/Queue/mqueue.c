/* Driver Queue */

#include "../Queue/queue.h"
#include <stdio.h>

int main() {
  Queue Q;
  infotype X;
  int i;
  //Test CreateEmptyQ and IsEmptyQ
  CreateEmptyQ(&Q,5);
  if (IsEmptyQ(Q)) {
    printf("CreateEmptyQ and IsEmptyQ Correct\n");
  } else {
    printf("CreateEmptyQ and IsEmptyQ Incorrect\n");
  }
  //Test AddQ and IsFullQ
  i = 1;
  while (i <= 5) {
    X = (char) i + 48;
    AddQ(&Q,X);
    i++;
  }

  //Test DelQ and NbElmtQ
  while (NBElmtQ(Q) > 0) {
    DelQ(&Q,&X);
    printf("%c tersisa : %d\n",X,NBElmtQ(Q));
  }
  if (IsEmptyQ(Q)) {
    printf("DelQ and NbElmtQ Correct\n");
  } else {
    printf("DelQ and NbElmtQ Inccorect\n");
  }
  return 0;
}
