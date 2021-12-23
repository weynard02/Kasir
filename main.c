#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "formula.h"
#define ll long long
int main() 
{
	//struct Master brg;
	printf("SELAMAT DATANG DI INDOFEB\n");
	while(1)
	{
		int a;
		printf("Masukkan nomor mode yang akan digunakan!\n");
		puts("1. Transaksi");
		puts("2. Show Master Barang");
		puts("3. Tambahkan Master Barang");
		puts("4. Tambahkan stok");
		puts("5. Riwayat transaksi");
		puts("6. Laporan Keuangan");
		puts("7. Reset menu");
		puts("8. Struk terakhir");
		puts("9. Keluar");
		printf("> ");
		scanf("%d",  &a);
		printf("\n");
		if (a<1 || a>8)
		{
			printf("Mode tidak tersedia, silakan coba lagi!\n");
			continue;
		}
		if (a == 1)
		{
			bacamasterbarang();
			kasirmode();
			
		}
		else if (a == 2)
		{
			bacamasterbarang();
			char in;
			printf("Lebih detail? (y/n)\n> ");
			scanf(" %c", &in);
			if (tolower(in) == 'y')
			{
				bacastok();
			}
		}
		else if (a == 3)
		{
			masterbarang();
		}
		else if (a == 4)
		{
			menambahstok();
		}
		else if (a == 5)
		{
			riwayattransaksi();
		}
		else if (a == 6)
		{
			laporan();
		}
		else if (a == 7)
		{
			int menu;
			printf("\n1. Reset Transaksi\n2. Reset total\n3. Delete barang\nMasukkan nomor mode (1/2/3)\n> ");
			scanf("%d", &menu);
			if (menu == 1)
			{
				char msk;
				printf("PERHATIAN, MERESET RIWAYAT TRANSAKSI DAPAT MENGAKIBATKAN KEHILANGAN DATA PENDAPATAN DAN KEUNTUNGAN/KERUGIAN. TETAP DILAKUKAN? (TEKAN y untuk melanjutkan)\n> ");
				scanf(" %c", &msk);
				if (tolower(msk) == 'y')
				{
					FILE *fp;
					fp = fopen("riwayattransaksi.dat", "wb");
					fclose(fp);
					printf("RESET TRANSAKSI SUKSES\n");
					continue;
				}
				printf("RESET TRANSAKSI GAGAL\n");
			}
			else if (menu == 2)
			{
				char msk;
				printf("PERHATIAN, MERESET TOTAL AKAN MENGHAPUS SEMUA DATA PADA KASIR INI. TETAP DILAKUKAN? (TEKAN y untuk melanjutkan)\n> ");
				scanf(" %c", &msk);
				if (tolower(msk) == 'y')
				{
					FILE *fp, *fp2, *fp3;
					fp  = fopen("masterbarang.dat", "wb");
					fp2 = fopen("stokbarang.dat", "wb");
					fp3 = fopen("riwayattransaksi.dat", "wb");
					fclose(fp); fclose(fp2); fclose(fp3);
					printf("RESET SUKSES\n");
					continue;
				}
				printf("RESET GAGAL\n");
				
			}
			else if (menu == 3)
			{
				removemasterbarang();
			}
			else
			{
				puts("input tidak dikenal");
			}
		}
		else if (a == 8)
		{
			printstruk();
		}
		else if (a == 9)
		{
			return 0;
		}
	}
}
