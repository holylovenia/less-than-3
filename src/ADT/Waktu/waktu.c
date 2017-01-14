// Deskripsi: Implementasi ADT Waktu. ADT Waktu adalah modifikasi ADT Jam, dengan komponen tambahan berupa tanggal

#include <stdio.h>
#include "../Boolean/boolean.h"
#include "../Waktu/waktu.h"

WAKTU time_tToWAKTU (time_t rawtime) {
/* 	Fungsi mengkonversi masukan data time_t menuju keluaran tipe WAKTU
 *	Tipe data time_t merupakan tipe bawaan time.h
 *	Tipe data time_t berisi jumlah detik sejak 00:00:00 GMT, 1 Januari 1970 */
	// KAMUS
	struct tm *info;
	WAKTU waktu;

	// ALGORITMA
	info = localtime(&rawtime);

	Second(waktu) = info->tm_sec;
	Minute(waktu) = info->tm_min;
	Hour(waktu) = info->tm_hour;
	Day(waktu) = info->tm_mday;
	Month(waktu) = info->tm_mon + 1;
	Year(waktu) = info->tm_year + 1900;
	return waktu;
}

WAKTU GetCurrWAKTU (void) {
/*	Fungsi mengembalikan waktu lokal mesin saat pemanggilan fungsi */
	// KAMUS
	time_t rawtime;

	// ALGORITMA
	time(&rawtime);
	return time_tToWAKTU(rawtime);
}
