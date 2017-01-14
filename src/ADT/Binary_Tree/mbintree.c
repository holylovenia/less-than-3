//Cara Compile : gcc -o test dbintree.c bintree.c
/* Driver Binary Tree */
#include "../Binary_Tree/bintree.h"
#include <stdio.h>

int main() {
  infotypeBT X;
  BinTree BT;
  //Test CreateEmptyTree and IsTreeEmpty
  CreateEmptyTree(&BT);
  if (IsTreeEmpty(BT)) {
    printf("CreateEmptyTree and IsTreeEmpty Correct\n");
  } else {
    printf("CreateEmptyTree and IsTreeEmpty Incorrect\n");
  }
  //Test Tree
  Unlocked(X) = false;
  IsPassive(X) = true;
  ID(X) = 1;

  printf("\nNama (maks 30): ");
  scanf("%s", NamaBT(X));
  printf("Deskripsi (maks 300): ");
  scanf("%s", Deskripsi(X));
  printf("ID: %d\n\n", ID(X));

  BT = Tree(X,NilBT,NilBT);
  if (BT != NilBT) {
    printf("Tree Correct\n");
  } else {
    printf("Tree Incorrect\n");
  }
  //Test AlokNode
  BT = AlokNode(X);
  if (BT != NilBT) {
    printf("AlokNode Correct\n");
  } else {
    printf("AlokNode Incorrect\n");
  }
  //Test IsTreeOneElmt
  if (IsTreeOneElmt(BT)) {
    printf("IsTreeOneElmt Correct\n");
  } else {
    printf("IsTreeOneElmt Incorrect\n");
  }
  //Test PrintTree
  PrintTree(BT,2);
  //Test SearchTree
  if (SearchTree(BT,X)) {
    printf("SearchTree Correct\n");
  } else {
    printf("SearchTree Incorrect\n");
  }
  //Test NbElmt
  printf("NbElmt = %d\n",NbElmt(BT));
  //Test Level
  printf("Level = %d\n",Level(BT,X));
  return 0;
}
