#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "formula.h"
#define ll long long

void laporan()
{
	FILE *fp, *fp2;
	struct transaksi ts = {"", "", "", 0, 0, 0, 0, 0, 0};
	if ((fp = fopen("riwayattransaksi.dat", "rb+")) == NULL)
	{
		printf("Error, tidak ditemukan file yang dicari\n");
		return;
	}
	struct stok sedia = {"", 0, 0, 0, 0, 0};
	ll modal_total = 0;
	if ((fp2 = fopen("stokbarang.dat", "rb+"))==NULL)
	{
		printf("Error, tidak ditemukan file yang dicari\n");
		return;
	}
	while(!feof(fp2))
	{
		if(fread(&sedia, sizeof(struct stok), 1, fp2))
		{
			modal_total+=sedia.modal;
		}
	}
	fclose(fp2);
	printf("SELAMAT DATANG DI LAPORAN KEUANGAN, MASUKKAN MODE YANG INGIN DITAMPAKKAN\n");
	puts("1. Laporan Harian");
	puts("2. Laporan Mingguan");
	puts("3. Laporan Bulanan");
	printf("> ");
	int mode;
	scanf("%d", &mode);
	time_t t;
	time(&t);
	double cmp = 0;
	if (mode == 1) cmp = 86400; //24 x 3600
	else if (mode == 2) cmp = 604800; //7 x 24 x 3600
	else if (mode == 3) cmp = 18144000; //30 x 7 x 24 x 3600
	ll counter_trans = 0;
	ll income = 0;
	char tanggal_flag[50] = "0";
	//printf("%s\n", ctime(&t));
	printf("===============================================================\n");
	while (!feof(fp))
	{
		if (fread(&ts, sizeof(struct transaksi), 1, fp))
		{
			if (strcmp(tanggal_flag, ts.time)!=0)
			{
				//printf("%s", ts.time);
				//printf("%ld\n", (long int)ts.T);
				//printf("%ld\n",(long int)t);
				//printf("%lf\n", difftime(t, ts.T));
				if (difftime(t,  ts.T)<=cmp) //mengecek perbedaan waktu
				{
					counter_trans++;
					income += ts.totalharga;
				}
			}
			strcpy(tanggal_flag, ts.time);
		}
	}
	printf("Modal awal total = Rp%lld\n", modal_total);
	printf("Jumlah Transaksi = %lld\n", counter_trans);
	printf("Pendapatan = Rp%lld\n", income);
	if (modal_total > income)
	{
		printf("Kerugian total = Rp%lld\n", modal_total - income);
	}
	else
	{
		printf("Keuntungan total = Rp%lld\n", income - modal_total);
	}
	printf("===============================================================\n");
	fclose(fp); fclose(fp2);
}
