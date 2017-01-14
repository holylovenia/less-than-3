// Deskripsi: Driver ADT Base Stats

#include "../../ADT/Basestats/basestats.h"
#include <stdio.h>

int main() {
	dbBST enemyData;
	int j;
	char input[20];

	// Test Load BST
	LoadBST(&enemyData);
	for (j = 1; j <= dbBST_NbElmt(enemyData); j++) {
		printf("%d: ", j);
		printf("%s ", NAMA(basestats(enemyData,j)));
		printf("%d ", BHP(basestats(enemyData,j)));
		printf("%d ", BSTR(basestats(enemyData,j)));
		printf("%d ", BDEF(basestats(enemyData,j)));
		printf("%d ", BLUC(basestats(enemyData,j)));
		printf("%d ", BEXP(basestats(enemyData,j)));
		printf("%s ", DESC(basestats(enemyData,j)));
		printf("%d ", SPRITE(basestats(enemyData,j)));
		printf("%d\n", BISB(basestats(enemyData,j)));
	}

	// Test Search BST
	printf("\nNama yg ingin dicari: ");
	scanf("%s",input);
	printf("Indeks %s: %d\n",input, SearchBST(enemyData,input));
}
