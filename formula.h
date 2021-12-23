#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define ll long long

struct Master
{
	char kode[4];
	char nama[50];
	int harga;
};

struct stok
{
	char kode[4];
	int stok_barang;
	int hargajual; //per stok
	int hargabeli; //per stok
	ll modal;
	ll laba;	
};

struct transaksi
{
	char time[50];
	char kode[4];
	char nama[50];
	int jml;
	int harga; //harga setelah dikalikan jumlah barang
	ll bayar;
	ll kembalian;
	ll totalharga;
	time_t T;
};

//mode kasir beneran
void kasirmode();

//pengisian master barang dengan stok awal
void masterbarang();

//penghapusan master barang
void removemasterbarang();

//read data master barang
void bacamasterbarang();

//penambahan stok barang
void menambahstok();

//read data stok secara detail
void bacastok();

//data riwayat transaksi
void riwayattransaksi();

//print struk
void printstruk();

//laporan
void laporan();


