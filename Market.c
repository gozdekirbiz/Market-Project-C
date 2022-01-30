#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<direct.h>
#include<time.h>
#include<ctype.h>
#include<windows.h>
#include<locale.h>

int i, j;
int ana_cikis;
int cevap;
int cikis;
struct {

	char urun_ad[20];
	int urun_no;
	int urun_adet;
	float urun_fiyat;
	float urun_maliyet;
	char urun_tedarikci[30];
	float kar;
	float karorani;
	float toplam;
}ekle, kontrol, liste, kar1,sil,guncelle,stok,satis,yeni,fatura2,genel;
void menu(void);
void fordelay(int j)
{
	int i, k;
	for (i = 0; i < j; i++)
		k = i;
} //sifre icin
//urun menusu voidleri


void urun_ekle()
{
	int choice;
	FILE *ptr;

	ptr = fopen("kayitlar.dat", "a+");
    urunno:
	system("cls");
	printf("\t\t\t\xB2\xB2\xB2\ URUN EKLE  \xB2\xB2\xB2\xB2");
	printf("\nUrun no:");
	scanf("%d", &kontrol.urun_no);
	while (fscanf(ptr, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci,&ekle.urun_adet, &ekle.urun_fiyat,&ekle.urun_maliyet) != EOF)
	{
		if (kontrol.urun_no == ekle.urun_no)
		{
			printf("Bu urun numarasi kullanilmaktadir.");
			fordelay(1000000000);
			goto urunno;

		}
	}
	ekle.urun_no = kontrol.urun_no;
	printf("\nUrun Adi:");
	scanf("%s", ekle.urun_ad);
	printf("\nTedarikci Adi:");
	scanf("%s", ekle.urun_tedarikci);
	printf("\n Urun Adeti:");
	scanf("%d", &ekle.urun_adet);
	printf("\n Urun Fiyati:");
	scanf("%f", &ekle.urun_fiyat);
	printf("\n Urun Alis Fiyati:");
	scanf("%f", &ekle.urun_maliyet);


	fprintf(ptr, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, ekle.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);


	fclose(ptr);
	printf("\nUrun basariyla kaydedildi!");
    yanlis_giris:
	printf("\n\n\n\t\t Yeni urun kaydetmek istiyorsaniz 1'e,ana menuye donmek icin 2'ye basiniz.");
	scanf("%d", &cevap);
	system("cls");
	if (cevap == 2)
		menu();
	else if (cevap == 1)
	{
		FILE* ptr;
		ptr = fopen("kayitlar.dat", "a+");
		goto urunno;
	}
		
	else
	{
		printf("\nYanlis giris!\a");
		goto yanlis_giris;
	}
}
void urunmenu();
void listele()
{
	FILE *file;
	file = fopen("kayitlar.dat", "r");
	int test = 0;
	system("cls");
	printf("\n\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 URUNLER \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\n\tURUN NO.\t\tADI\t\t\tTEDARIKCI ADI\t\tADET\t\t\tFIYATI\t\t\tMALIYETI\n");
	printf("========================================================================================================================");
	
	while (fscanf(file, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &ekle.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet) != EOF)
	{
		printf("\n\n\t%6d\t\t %10s\t\t\t %10s\t\t%d \t\t\t %.2f TL", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci,  ekle.urun_adet, ekle.urun_fiyat);
		test++;
	}

	fclose(file);
	if (test == 0)
	{
		system("cls");
		printf("\nKAYIT YOK!!\n");
	}

yanlisgiris:
	printf("\n\n\t\t Ana menuye donmek icin 1'e basin.");
	scanf("%d", &cikis);
	system("cls");
	if (cikis == 1)
		menu();
	else
	{
		printf("\nYanlis Giris!\a");
		goto yanlisgiris;
	}
}
void urun_sil();
void urun_sil()
{
	FILE* eski, * yenikayit;
	int test = 0;
	eski = fopen("kayitlar.dat", "r");
	yenikayit = fopen("yeni.dat", "w");
	printf("Silmek istediginiz urunun numarasini giriniz:");
	scanf("%d", &sil.urun_no);
	while (fscanf(eski, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &ekle.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet) != EOF)
	{
		if (ekle.urun_no != sil.urun_no)
			fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, ekle.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);

		else
		{
			test++;
			printf("\nKayit basari ile silindi.\n");
		}
	}
	fclose(eski);
	fclose(yenikayit);
	remove("kayitlar.dat");
	rename("yeni.dat", "kayitlar.dat");
	if (test == 0)
	{
		printf("\nKayit bulunamadi\a\a\a");
	yanlis_sil:
		printf("\nTekrar denemek icin 0'a, bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);

		if (ana_cikis == 1)
			urunmenu();
		else if (ana_cikis == 2)
			menu();
		else if (ana_cikis == 0)
			urun_sil();
		else
		{
			printf("\nGecersiz giris\a");
			goto yanlis_sil;
		}
	}
	else
	{
		printf("\nTekrar urun silmek icin 0'a,bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);
		system("cls");
		if (ana_cikis == 1)
			urunmenu();
		else if (ana_cikis == 0)
		{
			urun_sil();
		}
		else
			menu();
	}
}

void urun_guncelle();
void urun_guncelle()
{
	int secim, test = 0;
	FILE *eski, *yenikayit;
	eski = fopen("kayitlar.dat", "r");
	yenikayit = fopen("yeni.dat", "w");

	printf("\nDegistirmek istediginiz urunun numarasini giriniz: ");
	scanf("%d", &guncelle.urun_no);
	while (fscanf(eski, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &ekle.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet) != EOF)
	{
		if (ekle.urun_no == guncelle.urun_no)
		{
			test = 1;
			printf("\nHangisini degistirmek istersiniz?\n1.Stok\n2.Fiyat\n\nSeciminizi yapiniz(Stok icin 1, Fiyat icin 2):");
			scanf("%d", &secim);
			system("cls");
			if (secim == 1)
			{
				printf("Yeni stogu giriniz.");
				scanf("%d", &guncelle.urun_adet);
				fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, guncelle.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);
				system("cls");
				printf("Degisiklikler kaydedildi.");
			}
			else if (secim == 2)
			{
				printf("Yeni fiyati giriniz.");
				scanf("%f", &guncelle.urun_fiyat);
				fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, ekle.urun_adet, guncelle.urun_fiyat, ekle.urun_maliyet);
				system("cls");
				printf("Degisiklikler kaydedildi.");
			}

		}
		else
			fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, ekle.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);
	}
	fclose(eski);
	fclose(yenikayit);
	remove("kayitlar.dat");
	rename("yeni.dat", "kayitlar.dat");

	if (test != 1)
	{
		system("cls");
		printf("\nKayit bulunamadi.\a\a\a");
	yanlis_guncelleme:
		printf("\nTekrar denemek icin 0'a, bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);

		if (ana_cikis == 1)
			urunmenu();
		else if (ana_cikis == 2)
			menu();
		else if (ana_cikis == 0)
			urun_guncelle();
		else
		{
			printf("\nGecersiz giris\a");
			goto yanlis_guncelleme;
		}
	}
	else
	{
		printf("\nTekrar urun guncellemek icin 0'a,bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);
		system("cls");
		if (ana_cikis == 1)
			urunmenu();
		else if (ana_cikis == 0)
		{
			urun_guncelle();
		}
		else
			menu();
		
	}
	
}
//stok fonksiyonlari
void stokbilgisimenu();
void stokadarama();
void stokadarama()
{
	FILE* stokad,*yenikayit;
	stokad = fopen("kayitlar.dat", "r");
	yenikayit = fopen("yeni.dat", "w");
	int test = 0;
	system("cls");
	printf("\t\t\t\xB2\xB2\xB2\ ADA GORE STOK BILGISI  \xB2\xB2\xB2\xB2");
	printf("\nAramak istediginiz urunun adini giriniz: ");
	scanf("%s", kontrol.urun_ad);
	while (fscanf(stokad, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &ekle.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet) != EOF)
	{
		if (strcmp(ekle.urun_ad, (kontrol.urun_ad)) == 0)
		{
			system("cls");
			printf("\t\t\t\xB2\xB2\xB2\ ADA GORE STOK BILGISI \xB2\xB2\xB2\xB2");
			printf("\n\n\n\tURUN NO.\t\tADI\t\t\tTEDARIKCI ADI\t\tADET\n");
			printf("================================================================================================");
			printf("\n\n\t%6d\t\t %10s\t\t\t %10s\t\t%d", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, ekle.urun_adet);
			test++;
		}
		
	}
	if (test == 0)
	{
		system("cls");
		printf("\Boyle bir kayit bulunmamaktadir.\n");
	    yanlis_liste:
		printf("\nTekrar denemek icin 0'a, bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);

		if (ana_cikis == 1)
			stokbilgisimenu();
		else if (ana_cikis == 2)
			menu();
		else if (ana_cikis == 0)
			stokadarama();
		else
		{
			printf("\nGecersiz giris\a");
			goto yanlis_liste;
		}
	}
	else
	{
		printf("\nBir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);
		system("cls");
		if (ana_cikis == 1)
			stokbilgisimenu();
		else
			menu();

	}
}
void stoknoarama();
void stoknoarama()
{
	FILE *stokno, *yenikayit;
	stokno = fopen("kayitlar.dat", "r");
	yenikayit = fopen("yeni.dat", "w");
	int test = 0;
	system("cls");
	printf("\t\t\t\xB2\xB2\xB2\ NUMARAYA GORE STOK BILGISI  \xB2\xB2\xB2\xB2");
	printf("\nAramak istediginiz urunun numarasini giriniz: ");
	scanf("%d",&kontrol.urun_no);
	while (fscanf(stokno, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &ekle.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet) != EOF)
	{
		if (kontrol.urun_no==ekle.urun_no)
		{
			system("cls");
			printf("\t\t\t\xB2\xB2\xB2\ NUMARAYA GORE STOK BILGISI \xB2\xB2\xB2\xB2");
			printf("\n\n\n\tURUN NO.\t\tADI\t\t\tTEDARIKCI ADI\t\tADET\n");
			printf("================================================================================================");

			printf("\n\n\t%6d\t\t %10s\t\t\t %10s\t\t%d", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, ekle.urun_adet);
			test++;
		}

	}
	if (test == 0)
	{
		system("cls");
		printf("\Boyle bir kayit bulunmamaktadir.\n");
	yanlis_liste:
		printf("\nTekrar denemek icin 0'a, bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye, urun satisi icin 3'e basiniz.");
		scanf("%d", &ana_cikis);

		if (ana_cikis == 1)
			stokbilgisimenu();
		else if (ana_cikis == 2)
			menu();
		else if (ana_cikis == 0)
			stoknoarama();
		else if (ana_cikis == 3)
			urunsatisi();
		else
		{
			printf("\nGecersiz giris\a");
			goto yanlis_liste;
		}
	}
	else
	{
		printf("\n\n\nBir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);
		system("cls");
		if (ana_cikis == 1)
			stokbilgisimenu();
		else
			menu();

	}
}
void stokekle();
void stokekle()
{
	int test = 0;
	FILE *eski, *yenikayit;
	eski = fopen("kayitlar.dat", "r");
	yenikayit = fopen("yeni.dat", "w");
	printf("\t\t\t\xB2\xB2\xB2\ STOK EKLE  \xB2\xB2\xB2\xB2");
	printf("\nStok eklemek istediginiz urunun numarasini giriniz: ");
	scanf("%d", &guncelle.urun_no);
	while (fscanf(eski, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &ekle.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet) != EOF)
	{
		if (ekle.urun_no == guncelle.urun_no)
		{
			test = 1;
			system("cls");
			printf("\t\t\t\xB2\xB2\xB2\ STOK EKLE  \xB2\xB2\xB2\xB2");
			printf("\n\n\t\t\tEklemek istediginiz adet sayisini giriniz:");
			scanf("%d", &stok.urun_adet);
			guncelle.urun_adet=ekle.urun_adet+stok.urun_adet;
			fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, guncelle.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);
			system("cls");
			printf("\nDegisiklikler kaydedildi.");
		}
		else
			fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, ekle.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);
	}
	fclose(eski);
	fclose(yenikayit);
	remove("kayitlar.dat");
	rename("yeni.dat", "kayitlar.dat");

	if (test != 1)
	{
		system("cls");
		printf("\nKayit bulunamadi.\a\a\a");
	yanlis_guncelleme:
		printf("\nTekrar denemek icin 0'a, bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);
		system("cls");
		if (ana_cikis == 1)
			urunmenu();
		else if (ana_cikis == 2)
			menu();
		else if (ana_cikis == 0)
		{
			system("cls");
			stokekle();
		}
		else
		{
			printf("\nGecersiz giris\a");
			goto yanlis_guncelleme;
		}
	}
	else
	{
		printf("\nTekrar stok eklemek icin 0'a,bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);
		system("cls");
		if (ana_cikis == 1)
			stokbilgisimenu();
		else if (ana_cikis == 0)
		{
			stokekle();
		}
		else
			menu();

	}

	
}
void stoksil();
void stoksil() 
{
	int test = 0;
	FILE* eski, * yenikayit;
	eski = fopen("kayitlar.dat", "r");
	yenikayit = fopen("yeni.dat", "w");
	printf("\t\t\t\xB2\xB2\xB2\ STOK CIKAR  \xB2\xB2\xB2\xB2");
	printf("\nStok cikarmak istediginiz urunun numarasini giriniz. ");
	scanf("%d", &guncelle.urun_no);
	while (fscanf(eski, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &ekle.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet) != EOF)
	{
		if (ekle.urun_no == guncelle.urun_no)
		{
			test = 1;
			system("cls");
			printf("\t\t\t\xB2\xB2\xB2\ STOK CIKAR  \xB2\xB2\xB2\xB2");
			printf("\n\n\t\t\tEklemek istediginiz adet sayisini giriniz:");
			scanf("%d", &stok.urun_adet);
			guncelle.urun_adet = ekle.urun_adet - stok.urun_adet;
			fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, guncelle.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);
			system("cls");
			printf("\nDegisiklikler kaydedildi.");
		}
		else
			fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, ekle.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);
	}
	fclose(eski);
	fclose(yenikayit);
	remove("kayitlar.dat");
	rename("yeni.dat", "kayitlar.dat");

	if (test != 1)
	{
		system("cls");
		printf("\nKayit bulunamadi.\a\a\a");
	yanlis_guncelleme:
		printf("\nTekrar denemek icin 0'a, bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);
		system("cls");
		if (ana_cikis == 1)
			urunmenu();
		else if (ana_cikis == 2)
			menu();
		else if (ana_cikis == 0)
		{
			stoksil();
		}
		else
		{
			printf("\nGecersiz giris\a");
			goto yanlis_guncelleme;
		}
	}
	else
	{
		printf("\nTekrar stok silmek icin 0'a,bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);
		system("cls");
		if (ana_cikis == 1)
			stokbilgisimenu();
		else if (ana_cikis == 0)
		{
			stoksil();
		}
		else
			menu();

	}


}
void stokguncelle();
void stokguncelle()
{
	int test = 0;
	FILE* eski, * yenikayit;
	eski = fopen("kayitlar.dat", "r");
	yenikayit = fopen("yeni.dat", "w");
	printf("\t\t\t\xB2\xB2\xB2\ STOK GUNCELLE  \xB2\xB2\xB2\xB2");
	printf("\nStok guncellemek istediginiz urunun numarasini giriniz. ");
	scanf("%d", &guncelle.urun_no);
	while (fscanf(eski, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &ekle.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet) != EOF)
	{
		if (ekle.urun_no == guncelle.urun_no)
		{
			test = 1;
			system("cls");
			printf("\t\t\t\xB2\xB2\xB2\ STOK GUNCELLE  \xB2\xB2\xB2\xB2");
			printf("\n\t\tGuncellenmis adet sayisini giriniz:");
			scanf("%d", &stok.urun_adet);
			guncelle.urun_adet = stok.urun_adet;
			fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, guncelle.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);
			system("cls");
			printf("Degisiklikler kaydedildi.");
		}
		else
			fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, ekle.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);
	}
	fclose(eski);
	fclose(yenikayit);
	remove("kayitlar.dat");
	rename("yeni.dat", "kayitlar.dat");

	if (test != 1)
	{
		system("cls");
		printf("\nKayit bulunamadi.\a\a\a");
	yanlis_guncelleme:
		printf("\nTekrar denemek icin 0'a, bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);
		system("cls");
		if (ana_cikis == 1)
			urunmenu();
		else if (ana_cikis == 2)
			menu();
		else if (ana_cikis == 0)
		{
			stokguncelle();
		}
		else
		{
			printf("\nGecersiz giris\a");
			goto yanlis_guncelleme;
		}
	}
	else
	{
		printf("\nTekrar stok guncellemek icin 0'a,bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &ana_cikis);
		system("cls");
		if (ana_cikis == 1)
			stokbilgisimenu();
		else if (ana_cikis == 0)
		{
			stokguncelle();
		}
		else
			menu();

	}


}
void stoklistele();
void stoklistele()
{
	FILE* file;
	file = fopen("kayitlar.dat", "r");
	int test = 0;
	system("cls");
	printf("\n\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STOK LISTESI \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\n\tURUN NO.\t\tADI\t\tADET\n");
	printf("========================================================================================================================");

	while (fscanf(file, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &ekle.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet) != EOF)
	{
		printf("\n\n\t%6d\t\t %10s \t\t%d \t\t\t", ekle.urun_no, ekle.urun_ad,ekle.urun_adet);
		test++;
	}

	fclose(file);
	if (test == 0)
	{
		system("cls");
		printf("\nKAYIT YOK!!\n");
	}

yanlisgiris:
	printf("\n\n\t\t Ana menuye donmek icin 1'e basin.");
	scanf("%d", &cikis);
	system("cls");
	if (cikis == 1)
		menu();
	else
	{
		printf("\nYanlis Giris!\a");
		goto yanlisgiris;
	}
}
//kar zarar fonksiyonlari
void karzararmenu();
void karzarar();
void karzarar() {
	FILE* file;
	file = fopen("kayitlar.dat", "r");
	int test = 0;
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 KAR ZARAR TABLOSU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\n\tURUN NO.\t\tADI\t\tFIYATI\t\tKAR\t\tORAN\n");
	printf("=========================================================================================================");
	while (fscanf(file, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &ekle.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet) != EOF)
	{
		test++;
		kar1.kar = ekle.urun_fiyat - ekle.urun_maliyet;
		printf("\n\n\t%6d\t\t %10s\t\t%.2f TL\t\t%.2f TL ", ekle.urun_no, ekle.urun_ad, ekle.urun_fiyat, kar1.kar );
		kar1.karorani = kar1.kar / 100;
		if (kar1.karorani < 0)
			printf("\t %% %.2f ZARAR",kar1.karorani);
		else
			printf("\t %% %.2f KAR",kar1.karorani);
		
	}
	if (test == 0)
	{
		system("cls");
		printf("\nKAYIT YOK!!\n");
	}

yanlis_giris:
	printf("\n\n\n\t\t Ana Menuye donmek icin 1'e, Kar-Zarar menusune donmek icin 2'ye basiniz.");
	scanf("%d", &cevap);
	system("cls");
	if (cevap == 1)
		menu();
	else if (cevap == 2)
	{
		karzararmenu();
	}

	else
	{
		printf("\nYanlis giris!\a");
		goto yanlis_giris;
	}
}
int geneldurum();
int geneldurum()
{
	FILE *ptr;
	ptr = fopen("geneldurum.dat", "r");
	int test = 0;
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 KAR ZARAR TABLOSU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\n\tGELIR\t\tGIDER\t\t\tKAR\t\tORAN\n");
	printf("=========================================================================================================");
	genel.toplam = 0;
	genel.urun_maliyet = 0;
	genel.kar = 0;
	while (fscanf(ptr, "%f %f", &fatura2.toplam,&fatura2.urun_maliyet) != EOF)
	{
		test++;
		genel.toplam = genel.toplam + fatura2.toplam;
		genel.urun_maliyet = genel.urun_maliyet + fatura2.urun_maliyet;
		genel.kar = genel.toplam - genel.urun_maliyet;
	}
	printf("\n\n\t%.2f TL\t\t%.2f TL\t\t%.2f TL ", genel.toplam, genel.urun_maliyet, genel.kar);
	genel.karorani = genel.kar / 100;
	if (genel.karorani < 0)
		printf("\t\t %% %.2f ZARAR", genel.karorani);
	else
		printf("\t\t %% %.2f KAR", genel.karorani);
	if (test == 0)
	{
		system("cls");
		printf("\nKAYIT YOK!!\n");
	}

	yanlis_giris:
	printf("\n\n\n\t\t Ana Menuye donmek icin 1'e, Kar-Zarar menusune donmek icin 2'ye basiniz.");
	scanf("%d", &cevap);
	system("cls");
	if (cevap == 1)
		menu();
	else if (cevap == 2)
	{
		karzararmenu();
	}

	else
	{
		printf("\nYanlis giris!\a");
		goto yanlis_giris;
	}
}


//fatura fonksiyonlari
void fatura();
void fatura() {
	FILE *file,*genel;
	file = fopen("fatura.dat", "r");
	genel = fopen("geneldurum.dat", "a+");
	int test = 0;
	fatura2.toplam = 0;
	fatura2.urun_maliyet = 0;
	while (fscanf(file, "%d %s %s %d %f %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &satis.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet, &satis.urun_fiyat) != EOF)
	{
		printf("\n\n\t%6d\t\t %10s\t\t %10s\t\t\t%d\t\t%.2f\t\t\t%.2f TL", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, satis.urun_adet, ekle.urun_fiyat, satis.urun_adet*ekle.urun_fiyat);
		test++;
		fatura2.toplam = fatura2.toplam + satis.urun_fiyat;
		fatura2.urun_maliyet = fatura2.urun_maliyet + ekle.urun_maliyet;
		fprintf(genel, "%f %f\n", fatura2.toplam, fatura2.urun_maliyet);
	}	
	fclose(file);
	printf("\n\n\tToplam=%.2f", fatura2.toplam);
	fclose(genel);
}
int urunsatisi();
int urunsatisi() 
	{
		
		int test = 0,secim;
		FILE* eski, *yenikayit, * fatura1;
		printf("\t\t\t\xB2\xB2\xB2\ URUN SATISI  \xB2\xB2\xB2\xB2");
		eski = fopen("kayitlar.dat", "r");
		yenikayit = fopen("yeni.dat", "w");
		fatura1 = fopen("fatura.dat", "a+");
		printf("\n\t\t\tSatisi yapilan urunun numarasini giriniz: ");
		scanf("%d", &satis.urun_no);
		while (fscanf(eski, "%d %s %s %d %f %f", &ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, &ekle.urun_adet, &ekle.urun_fiyat, &ekle.urun_maliyet) != EOF)
		{
			if (ekle.urun_no == satis.urun_no)
			{
				test = 1;
				system("cls");
				printf("\t\t\t\xB2\xB2\xB2\ URUN SATISI  \xB2\xB2\xB2\xB2");
				printf("\n\t\t\tSatilan urunun adet sayisini giriniz:");
				scanf("%d", &satis.urun_adet);
				yeni.urun_adet = ekle.urun_adet - satis.urun_adet;
				if (yeni.urun_adet < 0)
				{
				yanlis_giris:
					printf("\n\n\t\t\tStokta yeterli urun bulunmamaktadir.\n\n\t\t\tIlgili urunun stok bilgilerine ulasmak icin 1'e basiniz.\n\n\t\t\tYeniden denemek icin 2'ye basiniz.");
					scanf("%d", &secim);
					if (secim == 1)
					{
						system("cls");
						stoknoarama();
					}
					else if (secim ==2)
					{
						system("cls");
						urunsatisi();
					}
					else 
					{
						printf("Yanlis giris yapildi.");
						goto yanlis_giris;
					}
				}
				else
				{
					satis.urun_fiyat = ekle.urun_fiyat * satis.urun_adet;
					fprintf(fatura1, "%d %s %s %d %f %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, satis.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet, satis.urun_fiyat);
					fclose(fatura1);
					
					printf("\n\t\t\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 NGE MARKET \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
					printf("\n\n\n\tURUN NO\t\t\tADI\t\t\tTEDARIKCI\t\tADET\t\tFIYAT\t\t\tTOPLAM\n");
					printf("=====================================================================================================================================");
					fatura();
					fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, ekle.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);

				}
			}
			else
				fprintf(yenikayit, "%d %s %s %d %f %f\n", ekle.urun_no, ekle.urun_ad, ekle.urun_tedarikci, yeni.urun_adet, ekle.urun_fiyat, ekle.urun_maliyet);
		}
		fclose(eski);
		fclose(yenikayit);
		remove("kayitlar.dat");
		rename("yeni.dat", "kayitlar.dat");
		
		

		if (test != 1)
		{
			system("cls");
			printf("\nKayit bulunamadi.\a\a\a");
		yanlis:
			printf("\nTekrar denemek icin 0'a, bir onceki menuye donmek icin 1'e, ana menuye donmek icin 2'ye basiniz.");
			scanf("%d", &ana_cikis);

			if (ana_cikis == 1)
				urunmenu();
			else if (ana_cikis == 2)
				menu();
			else if (ana_cikis == 0)
			{
				system("cls");
				urunsatisi();
			}
			
			else
			{
				printf("\nGecersiz giris\a");
				goto yanlis;
			}
		}
		printf("\n\n\n\t\t Urun satisina devam etmek icin 1'e,bitirip ana menuye donmek icin 2'ye basiniz.");
		scanf("%d", &cevap);
		system("cls");
		if (cevap == 2)
		{
			remove("fatura.dat");
			menu();
		}
		else if (cevap == 1)
		{
			system("cls");
			urunsatisi();
		}

		else
		{
			printf("\nYanlis giris!\n");
			goto yanlis_giris;
		}	
	}


//menu voidleri//

void urunmenu(void)
{
	int secim;
	system("cls");
	system("color 3");
	printf("\n\n\t\t\tMARKET");
	printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 URUNLER \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\t\t1.Urun Ekle\n\t\t2.Urun Sil\n\t\t3.Urun Guncelle\n\t\t4.Urun Listele\n\t\t5.Cikis\n\n\n\n\n\t\t Seciminizi Girin:");
	scanf("%d", &secim);

	system("cls");
	switch (secim)
	{
	case 1:urun_ekle();
	break;
	case 2:urun_sil();
	break;
	case 3:urun_guncelle();
	break;
	case 4:listele();
	break;
	case 5:menu();
	break;

	}
}
void stokbilgisimenu()
{
	int secim;
	system("cls");
	system("color 3");
	printf("\n\n\t\t\tMARKET");
	printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STOK \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\t\t1.Ada gore arama\n\t\t2.Numaraya gore arama\n\t\t3.Stok Ekle\n\t\t4.Stok Cikar\n\t\t5.Stok Guncelle\n\t\t6.Stok Listele\n\t\t7.Cikis\n\n\n\n\n\t\t Seciminizi Girin:");
	scanf("%d", &secim);

	system("cls");
	switch (secim)
	{
		case 1:stokadarama();
			break;
		case 2:stoknoarama();
			break;
		case 3:stokekle();
			break;
		case 4:stoksil();
			break;
		case 5:stokguncelle();
			break;
		case 6:stoklistele();
			break;
		case 7:menu();

			break;

	}
}
void karzararmenu()
{
	int secim;
	system("cls");
	system("color 3");
	printf("\n\n\t\t\tMARKET");
	printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 KAR-ZARAR \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\t\t1.Kar-Zarari goster\n\t\t2.Genel Durum\n\t\t3.Cikis\n\n\n\n\n\t\t Seciminizi Girin:");
	scanf_s("%d", &secim);

	system("cls");
	switch (secim)
	{
		case 1:karzarar();
			break;
		case 2:geneldurum();
			break;
		case 3:menu();

			break;

	}
}
void faturamenu() 
	{
		int secim;
		system("cls");
		system("color 3");
		printf("\n\n\t\t\tMARKET");
		printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 FATURA \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		printf("\n\n\t\t1.Urun Satisi\n\t\t2.Cikis\n\n\n\n\n\t\t Seciminizi Girin:");
		scanf_s("%d", &secim);

		system("cls");
		switch (secim)
		{
		case 1:urunsatisi();
		break;
	    case 2:menu();
		break;

		}



	}

//main menu ve baslangic
void menu(void)
{
	int secim;
	system("cls");
	system("color 3");
	printf("\n\n\t\t\tMARKET");
	printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ANA MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\t\t1.Urunler\n\t\t2.Stok Bilgisi\n\t\t3.Kar Zarar\n\t\t4.Fatura\n\t\t5.Cikis\n\n\n\n\n\t\t Seciminizi Girin:");
	scanf_s("%d", &secim);

	system("cls");
	switch (secim)
	{
	case 1:
		urunmenu();
		break;
	case 2:stokbilgisimenu();
		break;
	case 3:karzararmenu();
		break;
	case 4:faturamenu();
		break;
	case 5:exit(0);
		break;

	}
}
int main()
{
	char pass[10], password[10] = "c";
	int i = 0;
	printf("\n\n\t\tLutfen sifreyi giriniz:");
	scanf("%s", pass);
	
	if (strcmp(pass, password) == 0)
	{
		printf("\n\n\t\tSifre dogru\n\n\t\tYUKLENIYOR");
		for (i = 0; i <=2; i++)
		{
			fordelay(100000000);
			printf(".");
		}
		system("cls");
		menu();
	}
	else
	{
		printf("\n\nYanlis sifre!\a\a\a");
	yenidengir:
		printf("\nEnter 1 to try again and 0 to exit:");
		scanf_s("%d", &ana_cikis);
		if (ana_cikis == 1)
		{

			system("cls");
			main();
		}

		else if (ana_cikis == 0)
			system("cls");
		else
		{
			printf("\nGecersiz!");
			fordelay(1000000000);
			system("cls");
			goto yenidengir;
		}
	}
	return 0;
}

