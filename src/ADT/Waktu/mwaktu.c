/* Driver ADT Waktu */
#include "../Waktu/waktu.h"
#include <stdio.h>

int main() {
  /* Kamus */
  WAKTU Time;
  /* Algoritma */
  //Test time_tToWAKTU and GetCurrWAKTU
  Time = GetCurrWAKTU();
  printf("Tanggal = %d\nBulan = %d\nTahun = %d\nJam = %d\nMenit = %d\nDetik = %d\n",Day(Time), Month(Time), Year(Time), Hour(Time), Minute(Time), Second(Time));

  return 0;
}
