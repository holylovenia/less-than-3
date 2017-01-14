// Deskripsi: Definisi ADT Waktu. ADT Waktu adalah modifikasi ADT Jam, dengan komponen tambahan berupa tanggal

#ifndef WAKTU_H
#define WAKTU_H

#include <time.h>
#include "../Boolean/boolean.h"

/* *** Definisi TYPE WAKTU *** */
typedef struct {
	int SS;		/* detik, [0..59] */
	int MM;		/* menit, [0..59] */
	int HH;		/* jam, [0..23] */
	int MDAY;	/* tanggal dalam bulan, [1..31] */
	int MON;	/* bulan, [1..12] */
	int YEAR;	/* tahun */
} WAKTU;


/* *** Notasi Akses: selektor WAKTU *** */
#define Hour(W) (W).HH
#define Minute(W) (W).MM
#define Second(W) (W).SS
#define Day(W) (W).MDAY
#define Month(W) (W).MON
#define Year(W) (W).YEAR


WAKTU time_tToWAKTU (time_t rawtime) ;
/* 	Fungsi mengkonversi masukan data time_t menuju keluaran tipe WAKTU
 *	Tipe data time_t merupakan tipe bawaan time.h
 *	Tipe data time_t berisi jumlah detik sejak 00:00:00 GMT, 1 Januari 1970 */

WAKTU GetCurrWAKTU (void) ;
/*	Fungsi mengembalikan waktu lokal mesin saat pemanggilan fungsi */

#endif
