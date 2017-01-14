/* Deskripsi : Implementasi ADT Point */

#include <stdio.h>
#include "../Point/point.h"

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y){
/* Membentuk sebuah POINT dari komponen-komponennya */
	POINT p;
	Absis(p) = X;
	Ordinat(p) = Y;
	return p;
}
