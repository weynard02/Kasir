#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "formula.h"
#define ll long long

void printstruk()
{
	FILE *fp;
	struct transaksi struk = {"", "", "", 0, 0, 0, 0, 0, 0};
	if ((fp=fopen("struk.dat", "rb+"))==NULL)
	{
		printf("Error, tidak ditemukan file yang dicari\n");
		return;
	}
	int flag = 0;
	ll total = 0;
	ll cash = 0;
	ll kembali = 0;
	printf("\n");
	puts("===================SELAMAT DATANG DI INDOFEB=====================");
	while(!feof(fp))
	{
		if(fread(&struk, sizeof(struct transaksi), 1, fp))
		{
			if (!flag)
			{
				printf("Tanggal = %s", struk.time);
				printf("%-16s%-16s\t%s\t%s\n", "Kode Barang", "Nama barang", "Jumlah", "Harga");
			}
			flag = 1;
			printf("%-16s%-16s\t%d\t%s%d\n", struk.kode, struk.nama, struk.jml, "Rp", struk.harga);
			total = struk.totalharga; cash = struk.bayar; kembali = struk.kembalian;
			continue;
		}
		printf("Total = Rp%lld (Sudah termasuk pajak 10%%)\n", total);
		printf("Bayar = Rp%lld\n", cash);
		printf("Kembalian = Rp%lld\n", kembali);
	}
	
	printf("TERIMA KASIH TELAH BERBELANJA\n");
	printf("===============================================================\n\n");
}

void kasirmode()
{
	FILE *fp, *fpp, *fp2, *fstruk;
	time_t t; //variabel yg berisi waktu
	time(&t);
	int i = 0;
	struct stok sedia = {"", 0, 0, 0, 0, 0};
	struct Master brg = {"", "", 0};
	if ((fp = fopen("stokbarang.dat", "rb+")) == NULL)
	{
		printf("Error, tidak ditemukan file yang dicari\n");
		return;
	}
	if ((fpp = fopen("masterbarang.dat", "rb+")) == NULL)
	{
		printf("Error, tidak ditemukan file yang dicari\n");
		return;
	}
	struct transaksi ts = {"", "", "", 0, 0, 0, 0, 0};
	struct transaksi struk = {"", "", "", 0, 0, 0, 0, 0};
	if ((fp2 = fopen("riwayattransaksi.dat", "ab+")) == NULL)
	{
		printf("Error, tidak ditemukan file yang dicari\n");
		return;
	}
	if ((fstruk = fopen("struk.dat", "wb")) == NULL)
	{
		printf("Error, tidak ditemukan file yang dicari\n");
		return;
	}
/*	char **arrkode = (char**) malloc(1000 * sizeof(char*));
	if (arrkode == NULL)
	{
		printf("Malloc error arrkode\n");
	}
	char **arrnama = (char**) malloc(1000 * sizeof(char*));
	if (arrnama == NULL)
	{
		printf("Malloc error arrnama\n");
	}
	int *arrstok = (int*) malloc(1000 * sizeof(int));
	if (arrstok == NULL)
	{
		printf("Malloc error arrstok\n");
	}
	int *arrprice = (int*) malloc(1000 * sizeof(int));
	if (arrprice == NULL)
	{
		printf("Malloc error arrprice\n");
	}*/
	char arrkode[1000][4];
	char arrnama[1000][100];
	int arrstok[1000];
	int arrprice[1000];
	while(1)
	{
		char in[4];
		int jml;
		ll total = 0;
		printf("Masukkan kode barang dan jumlahnya yang ingin dibeli\nContoh: 001 3\nTekan 000 pada kode untuk ke pembayaran\n> ");
		scanf("%s", in);
		if (strlen(in)!=3)
		{
			printf("Panjang kode tidak sesuai. Tolong dicoba lagi!\n");
			continue;
		}
		if (!strcmp(in, "000"))
		{
			//printf("i=%d\n", i);
			if (i==0)
			{
				printf("Transaksi Batal\n");
				break;
			}
			printf( "%-16s%-16s\t%s\t%s\n", "Kode Barang", "Nama barang", "Jumlah", "Harga");
			for (int a = 0; a < i; a++)
			{
				printf("%-16s%-16s\t%d\t%s%d\n", arrkode[a], arrnama[a], arrstok[a], "Rp", arrstok[a]*arrprice[a]);
				total += arrstok[a]*arrprice[a];
				
			}
			ll cash;
			total += total*10/100;
			printf("(Catatan: dipungut pajak 10%%)\n");
			printf("Total pembayaran = Rp%lld\n", total);
			while(1){
				printf("Masukkan uang = Rp");
				scanf("%lld", &cash);
				if (cash>=total) break;
				printf("Cash tidak mencukupi!\n");
			}
			printf("Kembalian = Rp%lld\n", cash-total);
			
			for (int a = 0; a<i;a++) //pengurangan dimulai
			{
				fseek(fp, 0, SEEK_SET);
				while(!feof(fp))
				{
					if(fread(&sedia, sizeof(struct stok), 1, fp))
					{
						//printf("Update Stok Now in %s\n", sedia.kode);
						if(!strcmp(sedia.kode, arrkode[a]))
						{
							sedia.stok_barang-=arrstok[a];
							sedia.laba += arrstok[a]*sedia.hargajual;
							fseek(fp, (atoi(arrkode[a])-1)*sizeof(struct stok), SEEK_SET);
							fwrite(&sedia, sizeof(struct stok), 1, fp);
							break;
						}
					}
				}
			}
			for (int a = 0; a < i; a++)
			{
				strcpy(ts.time, ctime(&t));
				strcpy(ts.kode, arrkode[a]);
				strcpy(ts.nama, arrnama[a]);
				ts.jml = arrstok[a];
				ts.harga = arrstok[a]*arrprice[a];
				ts.bayar = cash;
				ts.kembalian = cash - total;
				ts.totalharga = total;
				ts.T = time(&t); // mengambil waktu sekarang
				fseek(fp2, (a)*sizeof(struct transaksi), SEEK_SET);
				fwrite(&ts, sizeof(struct transaksi), 1,  fp2);
				
				strcpy(struk.time, ctime(&t));
				strcpy(struk.kode, arrkode[a]);
				strcpy(struk.nama, arrnama[a]);
				struk.jml = arrstok[a];
				struk.harga = arrstok[a]*arrprice[a];
				struk.bayar = cash;
				struk.kembalian = cash - total;
				struk.totalharga = total;
				fseek(fstruk, (a)*sizeof(struct transaksi), SEEK_SET);
				fwrite(&struk, sizeof(struct transaksi), 1,  fstruk);
			}
			printstruk();
			fclose(fp); fclose(fpp); fclose(fp2); fclose(fstruk);
			break;
		}
		scanf("%d", &jml);
		while(!feof(fp))
		{
			if (fread(&sedia, sizeof(struct stok), 1, fp))
			{
				//printf("Search %s\n", sedia.kode);
				fread(&brg, sizeof(struct Master), 1, fpp);
				if (!strcmp(sedia.kode, in))
				{
					if (sedia.stok_barang == 0)
					{
						printf("Barang habis.\n");
						break;
					}
					if (sedia.stok_barang - jml < 0)
					{
						printf("Stok tidak mencukupi.\n");
						break;
					}
					strcpy(arrkode[i], in);
					strcpy(arrnama[i], brg.nama);
					arrstok[i] = jml;
					arrprice[i] = sedia.hargajual;
					i++;
					//printf("%d\n", i);
					printf("Pembelian sukses.\n");
					fseek(fp, 0, SEEK_SET);
					fseek(fpp, 0, SEEK_SET);
					break;
				}
			}
			else
			{
				printf("Not found.\n");
			}
		}
	}
	fclose(fp); fclose(fpp); fclose(fp2); fclose(fstruk);
}
