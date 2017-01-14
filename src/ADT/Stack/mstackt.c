/* Driver Stack */
#include "../Stack/stackt.h"
#include <stdio.h>

int main() {
  Stack S;
  int i;
  infotypeS X[MaxElS+1];
  infotypeS Y;
  char CC;
  for (i = 1; i<=MaxElS; i++) {
    CreateEmptyQ(&X[i],1);
    AddQ(&X[i],(char) i + 38);
  }
  //Test CreateEmptyStack and IsEmptyStack
  CreateEmptyStack(&S);
  if (IsEmptyStack(S)) {
    printf("IsEmptyStack and CreateEmptyStack Correct\n");
  } else {
    printf("IsEmptyStack and CreateEmptyStack Incorrect\n");
  }
  //Test PushStack
  i = 1;
  while (i <= MaxElS) {
    PushStack(&S,X[i]);
    i++;
  }
  //Test PushStack and PopStack
  i = 0;
  while (!IsEmptyStack(S)) {
    i++;
    PopStack(&S,&Y);
    DelQ(&Y,&CC);
    printf("Top Stack %d : %c\n",i,CC);
  }
  if (IsEmptyStack(S)) {
    printf("Pop Stack Correct\n");
  } else {
    printf("Pop Stack Incorrect\n");
  }

  return 0;
}
