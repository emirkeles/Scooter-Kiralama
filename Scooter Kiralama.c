#include <stdio.h>
#include <time.h>       
#include <unistd.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

typedef struct{
int scooterNo;
int uzaklik;	// Scooterin kullaniciye metre cinsinden uzakligi
int sarjDurumu;
int kiraDurumu;
}scooter;
scooter *Scooterlar;
scooter xscooter;	// Admin tarafindan eklenecek scooterin structu

typedef struct{
char ad[15];
char soyad[15];
char eposta[30];
char telefon[15];
char sifre[10];
char tcNo[11];
int kartkayit; // Kullanici kartini kaydederse 1, kaydetmezse 0 degeri.
float bakiye;
int ogrenci;   // Ogrenciyse 1, degilse 0 degeri.
int ilkKullanim; // Ilk defa scooter kullaniliyorsa 0 degeri, ilk defa kullanmiyorsa 1 degeri
time_t sure;	// Kullanicinin scooteri kiraladigi anin degerini tutan degisken
scooter Scooter;
}kullanici;
kullanici uye;
kullanici *Uyeler;

int axa=0,aktifuye=-1;

float acilis=3.0;
float tarife=0.01;			// 		saniye basina ucreti
float ogrenciIndirimi=0.003;//     	her saniyede indirim yapilacak ucret
 
 void yas_sorgu();
 void menu(kullanici *Uyeler,scooter *Scooterlar);
 void admin_giris(kullanici *Uyeler,scooter *Scooterlar);
 void menu_admin(kullanici *Uyeler,scooter *Scooterlar);
 void scooter_ekleme(kullanici *Uyeler,scooter *Scooterlar);
 void scooter_kiralama(kullanici *Uyeler,scooter *Scooterlar);
 void bakiye_goruntuleme(kullanici *Uyeler,scooter *Scooterlar);
 void scooter_birakma(kullanici *Uyeler,scooter *Scooterlar);
 void bakiye_yukleme(kullanici *Uyeler,scooter *Scooterlar);
 void kayit_gor(kullanici *Uyeler,scooter *Scooterlar);
 void kayit_sil(kullanici *Uyeler);
 void kayit_ara(kullanici *Uyeler);
 void uye_ol(kullanici *Uyeler,scooter *Scooterlar);
 void uye_giris(kullanici *Uyeler,scooter *Scooterlar);
 void olustur(scooter *Scooterlar);	// 10 adet scooter rastgele uzakliklarda olusturuluyor.
 void sirala(scooter *Scooterlar);	// Scooterlar, kullanici istegine gore uzaklik veya sarj durumuna gore siralaniyor.
 void yazdir(scooter *Scooterlar);	// Yeni siralanan scooterlar yazdiriliyor.
 void cikis();
 void bilgiKayit(kullanici *Uyeler,scooter *Scooterlar);
 void sifremi_unuttum(kullanici *Uyeler);
 
int main(){
	if(axa==0){
	Uyeler=(kullanici*)calloc(20,sizeof(kullanici));	// Bellekte yer dinamik olarak ayriliyor.
	Scooterlar=(scooter*)calloc(20,sizeof(scooter));
	axa++;}
	time_t s;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);	
	int j;
	FILE *f,*p,*k,*q;
	f=fopen("uyebilgileri.TXT","r");
	p=fopen("scooterbilgi.TXT","r");
	k=fopen("kredikarti.TXT","r");
	q=fopen("saat.TXT","r");
	for(j=0;j<=19;j++){
	fscanf(f,"%s %s %s %s %s %d %f %d %d %d %d %d %d %s\n",&Uyeler[j].ad,&Uyeler[j].soyad,&Uyeler[j].eposta,&Uyeler[j].telefon,&Uyeler[j].sifre,&Uyeler[j].kartkayit,&Uyeler[j].bakiye,&Uyeler[j].ogrenci,&Uyeler[j].Scooter.scooterNo,&Uyeler[j].Scooter.uzaklik,&Uyeler[j].Scooter.sarjDurumu,&Uyeler[j].Scooter.kiraDurumu,&Uyeler[j].ilkKullanim,Uyeler[j].tcNo);
	fscanf(p,"%d %d %d %d\n",&Scooterlar[j].scooterNo,&Scooterlar[j].uzaklik,&Scooterlar[j].sarjDurumu,&Scooterlar[j].kiraDurumu);
	fscanf(k,"%d\n",&Uyeler[j].kartkayit);
	fscanf(q,"%d\n",&Uyeler[j].sure);
	}
	fclose(f);
	fclose(p);
	fclose(k);
	fclose(q);
	
	system("cls");
	int abc,i;
	olustur(Scooterlar);
	
	int a;
	here:
		system("cls");
		printf("       ____    ____________________________________________________________      ______________       ___   _______   _____   ___   ___________            \n");
		printf("      /   /   /   /   ____   /     ______/               /   ________/    /     /              \\   __/__/__/      |  /    /__/__/__/          /           \n");
		printf("     /   /   /   /   /   /  /     /_____      __________/   /       /    /     /     ____       \\ /       /       | /    /        /____      /            \n");
		printf("    /   /___/   /   /   /  /______     /     /  _______/   /_______/    /     /     /    \\       /       /    /|  |/    /        /    /     /             \n");
		printf("   /           /   /   /  /______/    /     /  /___   /   ________/    /     /     /     /      /       /    / |       /        /    /     /               \n");
		printf("  /   ___     /   /   /  /           /     /______/  /   /       /    /_____/     /_____/      /       /    /  |      /        /    /     /_____           \n");
		printf(" /   /  /    /   /___/  /___________/               /   /_______/          /                  /       /    /   |     /        /    /           /           \n");
		printf("/___/  /____/__________/     /__/  /_______________/___________/__________/__________________/_______/____/    |____/________/    /___________/            \n");
		
printf("\n\n\nLutfen Yapmak Istediginiz Islemi Seciniz%90s|Saat %02d:%02d|\n\n"," ",current_time->tm_hour,current_time->tm_min, current_time->tm_sec);
printf("\n\n\n===================================\n1.Admin Girisi\n===================================\n2.Uye Ol\n===================================\n3.Uye Girisi\n===================================\n4.Sifremi Unuttum\n===================================\n5.Cikis\n===================================\n");
scanf("%d",&a);
system("cls");
switch(a){
	case 1:  admin_giris(Uyeler,Scooterlar);   break;
	case 2:  uye_ol(Uyeler,Scooterlar); break;
	case 3:  uye_giris(Uyeler,Scooterlar); break;
	case 4:  sifremi_unuttum(Uyeler);break;
	case 5:  cikis();exit(0); break;
	default:printf("\aYanlis Kodlama Yaptiniz\n\n"); goto here;
}
    return 0;
}
void menu(kullanici *Uyeler,scooter *Scooterlar){
		int b;
	time_t s;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
	rap:
		system("cls");
		printf("       ____    ____________________________________________________________      ______________       ___   _______   _____   ___   ___________          \n");
		printf("      /   /   /   /   ____   /     ______/               /   ________/    /     /              \\   __/__/__/      |  /    /__/__/__/          /          \n");
		printf("     /   /   /   /   /   /  /     /_____      __________/   /       /    /     /     ____       \\ /       /       | /    /        /____      /           \n");
		printf("    /   /___/   /   /   /  /______     /     /  _______/   /_______/    /     /     /    \\       /       /    /|  |/    /        /    /     /            \n");
		printf("   /           /   /   /  /______/    /     /  /___   /   ________/    /     /     /     /      /       /    / |       /        /    /     /              \n");
		printf("  /   ___     /   /   /  /           /     /______/  /   /       /    /_____/     /_____/      /       /    /  |      /        /    /     /_____          \n");
		printf(" /   /  /    /   /___/  /___________/               /   /_______/          /                  /       /    /   |     /        /    /           /          \n");
		printf("/___/  /____/__________/     /__/  /_______________/___________/__________/__________________/_______/____/    |____/________/    /___________/           \n");
	
	printf("\n\n\nLutfen Yapmak Istediginiz Islemi Seciniz%90s|Saat %02d:%02d|\n\n"," ",current_time->tm_hour,current_time->tm_min, current_time->tm_sec);
	printf("\n===================================\n");
	printf("1.Scooter Kiralama");
	printf("\n===================================\n");
	printf("2.Guncel Bakiye Goruntuleme");
	printf("\n===================================\n");
	printf("3.Scooter Birakma");
	printf("\n===================================\n");
	printf("4.Bakiye Yukleme");
	printf("\n===================================\n");
	printf("5.Cikis");
	printf("\n===================================\n");
	scanf("%d",&b);
	switch(b){
		case 1: scooter_kiralama(Uyeler,Scooterlar); break;
		case 2: bakiye_goruntuleme(Uyeler,Scooterlar); break;
		case 3: scooter_birakma(Uyeler,Scooterlar); break;
		case 4: bakiye_yukleme(Uyeler,Scooterlar); break;
		case 5: bilgiKayit(Uyeler,Scooterlar); main(); break;	// Dosyadaki bilgiler kayit altina aliniyor.
		default: printf("\aHatali Kod Girisi Yaptiniz\n\nLutfen Tekrar Deneyiniz");
		sleep(2);
		system("cls");
		goto rap;
	}
}
void menu_admin(kullanici *Uyeler,scooter *Scooterlar){
	int a;
	time_t s;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
	rep:
		system("cls");
		printf("       ____    ____________________________________________________________      ______________       ___   _______   _____   ___   ___________             \n");
		printf("      /   /   /   /   ____   /     ______/               /   ________/    /     /              \\   __/__/__/      |  /    /__/__/__/          /            \n");
		printf("     /   /   /   /   /   /  /     /_____      __________/   /       /    /     /     ____       \\ /       /       | /    /        /____      /             \n");
		printf("    /   /___/   /   /   /  /______     /     /  _______/   /_______/    /     /     /    \\       /       /    /|  |/    /        /    /     /              \n");
		printf("   /           /   /   /  /______/    /     /  /___   /   ________/    /     /     /     /      /       /    / |       /        /    /     /                \n");
		printf("  /   ___     /   /   /  /           /     /______/  /   /       /    /_____/     /_____/      /       /    /  |      /        /    /     /_____            \n");
		printf(" /   /  /    /   /___/  /___________/               /   /_______/          /                  /       /    /   |     /        /    /           /            \n");
		printf("/___/  /____/__________/     /__/  /_______________/___________/__________/__________________/_______/____/    |____/________/    /___________/             \n");
	printf("\n");
	printf("\n\n\nLutfen Yapmak Istediginiz Islemi Seciniz%90s|Saat %02d:%02d|\n\n"," ",current_time->tm_hour,current_time->tm_min, current_time->tm_sec);
	printf("\n===================================");
	printf("\n1.Kayitlari Goruntule");
	printf("\n===================================");
	printf("\n2.Kayit Sil");
	printf("\n===================================");
	printf("\n3.Kayit Ara");	
	printf("\n===================================");
	printf("\n4.Scooter Ekleme");
	printf("\n===================================");
	printf("\n5.Cikis\n");
	printf("===================================\n");
	scanf("%d",&a);
	switch(a){
		case 1: kayit_gor(Uyeler,Scooterlar); break;
		case 2: kayit_sil(Uyeler); break;
		case 3: kayit_ara(Uyeler); break;
		case 4: scooter_ekleme(Uyeler,Scooterlar); break;
		case 5: main(); break;
		default: printf("\aHatali Kod Girisi Yaptiniz\n\nLutfen Tekrar Deneyiniz");
		sleep(2);
		system("cls");
		goto rep;
	}
}
void scooter_kiralama(kullanici *Uyeler,scooter *Scooterlar){
 	system("cls");
 	time_t begin;
 	int sure[20];
 	char ch;
	int sorgulanacakScooter,i;
	yazdir(Scooterlar);
	sirala(Scooterlar);
	yazdir(Scooterlar);
	printf("\n\nKiralamak Istediginiz Scooterin No'sunu Giriniz: ");
	scanf("%d",&sorgulanacakScooter);
	sorgulanacakScooter--;	//Dizideki indisten dolayi degeri 1 azaltiyoruz.
	if(Scooterlar[sorgulanacakScooter].kiraDurumu==1){
		printf("Kiralamak Istediginiz Scooter Suanda Kullanimda!");
		sleep(2);
		system("cls");
		menu(Uyeler,Scooterlar);
	}
		if(Uyeler[aktifuye].Scooter.kiraDurumu==1){
		printf("Zaten Halihazirda Bir Scooter Kiralamissiniz!");
		sleep(2);
		system("CLS");
		menu(Uyeler,Scooterlar);
	}
	system("CLS");
	if(Uyeler[aktifuye].ogrenci==1){
		fiyatonay:
		printf("\t\t\t\t\t<<<   Fiyat Tarifeniz   >>>\n\n\n\t\t\t\t\tAcilis Ucreti ---> 3TL\n\n\t\t\t\t\tDakika Basina Ucret ---> 42kr\n");
		printf("\n\n<<< Ilk Kullanim Icin Acilis Ucreti = 0TL >>>\n\nOnayliyor Musunuz?(E-H)\n");
		ch=getch();
		
		if(ch=='H' || ch=='h'){
			printf("Onaylanmadi!");
			sleep(2);
			system("CLS");
		menu(Uyeler,Scooterlar);
		}
		else if(ch=='E'|| ch=='e'){
		Scooterlar[sorgulanacakScooter].kiraDurumu=1;
		Uyeler[aktifuye].Scooter=Scooterlar[sorgulanacakScooter];	
		printf("Onaylandi!");
	//	bilgiKayit(Uyeler,Scooterlar);
		begin=time(NULL);	//Scooterin kiralandigi anin degeri
		FILE *q,*r;
        q=fopen("saat.txt","w");
         for(i=0;i<=19;i++)
		 {
         	if(aktifuye==i)
			 {
         		fprintf(q,"%d\n",begin);
			 }
			 else
			 {
			 	fprintf(q,"%d\n",Uyeler[i].sure);
			 }
		 }
        fclose(q);
        r=fopen("saat.TXT","r");
		for(i=0;i<=19;i++){
		fscanf(r,"%d\n",&Uyeler[i].sure);
	}
	fclose(r);
		sleep(2);
		system("CLS");
		}
		else {
			printf("Yanlis harf girdiniz! Tekrar deneyin.\n");
			sleep(2);
			system("CLS");
			goto fiyatonay;
		}
	}
	else{
		fiyatonay2:
		printf("\t\t\t\t\t<<<   Fiyat Tarifeniz   >>>\n\n\n\t\t\t\t\tAcilis Ucreti ---> 3TL\n\n\t\t\t\t\tDakika Basina Ucret ---> 60kr\n");
		printf("\n\n<<< Ilk Kullanim Icin Acilis Ucreti = 0TL >>>\n\nOnayliyor Musunuz?(E-H)\n");
		ch=getch();
		if(ch=='H' || ch=='h'){
			printf("Onaylanmadi!");
			sleep(2);
			system("CLS");
		menu(Uyeler,Scooterlar);
		}
		else if(ch=='E' || ch=='e'){
		Scooterlar[sorgulanacakScooter].kiraDurumu=1;
		Uyeler[aktifuye].Scooter=Scooterlar[sorgulanacakScooter];
		printf("Onaylandi!");
	//	bilgiKayit(Uyeler,Scooterlar);
		begin=time(NULL);
		FILE *q,*r;
        q=fopen("saat.txt","w");
         for(i=0;i<=19;i++)
		 {
         	if(aktifuye==i)
			 {
         		fprintf(q,"%d\n",begin);
			 }
			 else
			 {
			 	fprintf(q,"%d\n",Uyeler[i].sure);
			 }
		 }
        fclose(q);
        r=fopen("saat.TXT","r");
		for(i=0;i<=19;i++){
		fscanf(r,"%d\n",&Uyeler[i].sure);
	}
		fclose(r);
		sleep(2);
		system("CLS");
		}
		else {
			printf("Yanlis harf girdiniz! Tekrar deneyin.");
			sleep(2);
			system("CLS");
			goto fiyatonay2;
		}
}
FILE *f,*d,*s,*t;
f=fopen("uyebilgileri.TXT","w");
for(i=0;i<=19;i++){
	if(i==aktifuye)
	fprintf(f,"%s %s %s %s %s %d %f %d %d %d %d %d %d %s\n",Uyeler[i].ad,Uyeler[i].soyad,Uyeler[i].eposta,Uyeler[i].telefon,Uyeler[i].sifre,Uyeler[i].kartkayit,Uyeler[i].bakiye,Uyeler[i].ogrenci,Scooterlar[sorgulanacakScooter].scooterNo,Scooterlar[sorgulanacakScooter].uzaklik,Scooterlar[sorgulanacakScooter].sarjDurumu,Scooterlar[sorgulanacakScooter].kiraDurumu,Uyeler[i].ilkKullanim,Uyeler[i].tcNo);
	else
	fprintf(f,"%s %s %s %s %s %d %f %d %d %d %d %d %d %s\n",Uyeler[i].ad,Uyeler[i].soyad,Uyeler[i].eposta,Uyeler[i].telefon,Uyeler[i].sifre,Uyeler[i].kartkayit,Uyeler[i].bakiye,Uyeler[i].ogrenci,Uyeler[i].Scooter.scooterNo,Uyeler[i].Scooter.uzaklik,Uyeler[i].Scooter.sarjDurumu,Uyeler[i].Scooter.kiraDurumu,Uyeler[i].ilkKullanim,Uyeler[i].tcNo);
}
fclose(f);
d=fopen("uyebilgileri.TXT","r");
for(i=0;i<=19;i++){
	fscanf(d,"%s %s %s %s %s %d %f %d %d %d %d %d %d %s\n",&Uyeler[i].ad,&Uyeler[i].soyad,&Uyeler[i].eposta,&Uyeler[i].telefon,&Uyeler[i].sifre,&Uyeler[i].kartkayit,&Uyeler[i].bakiye,&Uyeler[i].ogrenci,&Uyeler[i].Scooter.scooterNo,&Uyeler[i].Scooter.uzaklik,&Uyeler[i].Scooter.sarjDurumu,&Uyeler[i].Scooter.kiraDurumu,&Uyeler[i].ilkKullanim,Uyeler[i].tcNo);
}
fclose(d);
s=fopen("scooterbilgi.TXT","w");
for(i=0;i<=19;i++){
	fprintf(s,"%d %d %d %d\n",Scooterlar[i].scooterNo,Scooterlar[i].uzaklik,Scooterlar[i].sarjDurumu,Scooterlar[i].kiraDurumu);
}
fclose(s);
t=fopen("scooterbilgi.TXT","r");
for(i=0;i<=19;i++){
	fscanf(t,"%d %d %d %d\n",&Scooterlar[i].scooterNo,&Scooterlar[i].uzaklik,&Scooterlar[i].sarjDurumu,&Scooterlar[i].kiraDurumu);
}
fclose(t);
menu(Uyeler,Scooterlar);
 }
void bakiye_goruntuleme(kullanici *Uyeler,scooter *Scooterlar){
     system("CLS");
     char x;
     printf("\n\tBakiye --> [ %.2f TL ]\n\n", Uyeler[aktifuye].bakiye);
     printf("Bakiye yuklemek icin 1 ana menu'ye donmek icin 2\n");
     x=getch();
     switch(x)
     {
         case '1':
             system("CLS");
             bakiye_yukleme(Uyeler,Scooterlar);
             break;
             case '2':
                 system("CLS");
                 menu(Uyeler,Scooterlar);
                 break;
     }
 }
void scooter_birakma(kullanici *Uyeler,scooter *Scooterlar){
 srand(time(NULL));
 system("CLS");
 int i;
 time_t begin;
 time_t end;
 int counter=0;
  for(i=0;Scooterlar[i].scooterNo!=0;i++){               //kiralanan scooter bulunuyor.
  
  if(Uyeler[aktifuye].Scooter.scooterNo==Scooterlar[i].scooterNo) 
  {
  	printf("\t\t\tSurusu bitirmek icin scooteri kurallara uygun olarak kitledim\n\n\t\t\tOnayliyorsaniz: 1\t\t\tOnaylamiyorsaniz:2\n");
        char x;
        x=getch();
        if(x=='1')
        system("cls");
        {
		printf("Fotograf cekmek icin '1'e basiniz");
        x=getch();
        	if(x=='1')
       	 	{
       	 		system("cls");
        	printf("Lutfen Bekleyin...\n");
        	sleep(1);
        	printf("Fotograf isleniyor...\n");
        	sleep(1);
        	printf("Surus bitiriliyor...\n");
        	sleep(1);
        	system("cls");
		}
	}
    begin=Uyeler[aktifuye].sure;		// TXT dosyasindan scooterin kiralandigi anin bilgisi cekiliyor.
	end = time(NULL);
	
  	Uyeler[aktifuye].Scooter.sarjDurumu=Uyeler[aktifuye].Scooter.uzaklik=0;
  	Scooterlar[i].sarjDurumu=Scooterlar[i].sarjDurumu-((end - begin)/120);	// Birakilan scooterin kullanilan sureye bagli olarak sarji azaliyor.
  	Scooterlar[i].uzaklik=(rand()%2900+100);	
  	counter=1;
  
  if(Uyeler[aktifuye].ogrenci==1)
        	{
        		if(Uyeler[aktifuye].ilkKullanim==0){		// Ilk scooter kullaniminda acilis ucreti alinmiyor.
        		printf("\t\t   <<<\tIlk Kullanim Indirimi Tanimlandi: ACILIS UCRETI ALINMAYACAK\t>>>\n");
				printf("\n\n\t\t\t---------------------> Surus Ozeti <----------------------\n");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tSure: %d Dk %d Sn\t\tToplam:%.2f TL\t%1s-\n",(end - begin)/60,(end - begin)%60,0+((end - begin)*(tarife-ogrenciIndirimi))," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tAcilis ucreti --> + %.2f TL\t%16s -\n",0," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tSure tutari --> + %.2f TL\t%16s -\n",(end - begin)*tarife," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tOgrenci indirimi --> - %.2f TL\t%16s -\n", (((end - begin)*ogrenciIndirimi))," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tToplam --> %.2f TL\t%24s -\n",0+((end - begin)*(tarife-ogrenciIndirimi))," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t----------------------------------------------------------\n");
        		if(Uyeler[aktifuye].bakiye<(0+((end - begin)*(tarife-ogrenciIndirimi))))
        		{
        			printf("bakiyeniz yetersiz!..\nbakiye sayfasina yonlendiriliyorsunuz.\n");
        			printf("\n\nGecmek icin herhangi bir tusa basiniz.");
        			getch();
        			bakiye_yukleme(Uyeler,Scooterlar);
				}
				else{
					printf("Odeme Tamamlandi!\n");
					Scooterlar[i].kiraDurumu=0;
					Uyeler[aktifuye].Scooter.kiraDurumu=Uyeler[aktifuye].Scooter.scooterNo=0;
					Uyeler[aktifuye].bakiye=Uyeler[aktifuye].bakiye-(0+((end - begin)*(tarife-ogrenciIndirimi)));
					Uyeler[aktifuye].ilkKullanim+=1;
				}
				}
				else if(Uyeler[aktifuye].ilkKullanim!=0){
        		printf("\n\n\t\t\t---------------------> Surus Ozeti <----------------------\n");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tSure: %d Dk %d Sn\t\tToplam:%.2f TL\t%1s-\n",(end - begin)/60,(end - begin)%60,acilis+((end - begin)*(tarife-ogrenciIndirimi))," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tAcilis ucreti --> + %.2f TL\t%16s -\n",acilis," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tSure tutari --> + %.2f TL\t%16s -\n",(end - begin)*tarife," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tOgrenci indirimi --> - %.2f TL\t%16s -\n", (((end - begin)*ogrenciIndirimi))," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tToplam --> %.2f TL\t%24s -\n",acilis+((end - begin)*(tarife-ogrenciIndirimi))," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t----------------------------------------------------------\n");
        		if(Uyeler[aktifuye].bakiye<(acilis+((end - begin)*(tarife-ogrenciIndirimi))))
        		{
        			printf("bakiyeniz yetersiz!..\nbakiye sayfasina yonlendiriliyorsunuz.\n");
        			printf("\n\nGecmek icin herhangi bir tusa basiniz.");
        			getch();
        			bakiye_yukleme(Uyeler,Scooterlar);
				}
				else{
					printf("Odeme Tamamlandi!\n");
					Scooterlar[i].kiraDurumu=0;
					Uyeler[aktifuye].Scooter.kiraDurumu=Uyeler[aktifuye].Scooter.scooterNo=0;	
					Uyeler[aktifuye].bakiye=Uyeler[aktifuye].bakiye-(acilis+((end - begin)*(tarife-ogrenciIndirimi)));	// Kullanici bakiyesinden fiyat cikartiliyor.
				}
        	}
			}
			else
			{
				if(Uyeler[aktifuye].ilkKullanim==0){
				printf("\t\t   <<<\tIlk Kullanim Indirimi Tanimlandi: ACILIS UCRETI ALINMAYACAK\t>>>\n");
        		printf("\n\n\t\t\t---------------------> Surus Ozeti <----------------------\n");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tSure: %d Dk %d Sn\t\tToplam:%.2f TL\t%1s-\n",(end - begin)/60,(end - begin)%60,0+((end - begin)*(tarife))," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tAcilis ucreti --> + %.2f TL\t%16s -\n",0," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tSure tutari --> + %.2f TL\t%16s -\n",(end - begin)*tarife," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tOgrenci indirimi --> - %.2f TL\t%16s -\n", (((end - begin)))," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t-\tToplam --> %.2f TL\t%24s -\n",0+((end - begin)*(tarife))," ");
        		printf("\t\t\t-\t%48s -\n"," ");
        		printf("\t\t\t----------------------------------------------------------\n");
        		if(Uyeler[aktifuye].bakiye<(0+((end - begin)*(tarife))))
        		{
        			printf("\nbakiyeniz yetersiz!..\nbakiye sayfasina yonlendiriliyorsunuz.\n");
        			printf("\n\nGecmek icin herhangi bir tusa basiniz.");
        			getch();
        			bakiye_yukleme(Uyeler,Scooterlar);
				}
				else{
					printf("Odeme Tamamlandi!\n");
					Scooterlar[i].kiraDurumu=0;
					Uyeler[aktifuye].Scooter.kiraDurumu=Uyeler[aktifuye].Scooter.scooterNo=0;
					Uyeler[aktifuye].bakiye=Uyeler[aktifuye].bakiye-(0+((end - begin)*(tarife)));
					Uyeler[aktifuye].ilkKullanim+=1;
				}
				}
				else if(Uyeler[aktifuye].ilkKullanim!=0){
        		printf("\n\n\t\t\t---------------------> Surus Ozeti <---------------------\n");
        		printf("\t\t\t-\t%48s-\n"," ");
        		printf("\t\t\t-\tSure: %d Dk %d Sn\t\tToplam:%.2f TL\t%8s-\n",(end - begin)/60,(end - begin)%60,acilis+((end - begin)*tarife)," ");
        		printf("\t\t\t-\t%48s-\n"," ");
        		printf("\t\t\t-\tAcilis ucreti --> + %.2f TL\t%16s-\n",acilis," ");
        		printf("\t\t\t-\t%48s-\n"," ");
        		printf("\t\t\t-\tSure tutari --> + %.2f TL\t%16s-\n",(end - begin)*tarife," ");
        		printf("\t\t\t-\t%48s-\n"," ");
        		printf("\t\t\t-\tToplam --> %.2f TL\t%24s-\n",acilis+((end - begin)*tarife)," ");
        		printf("\t\t\t-\t%48s-\n"," ");
        		printf("\t\t\t---------------------------------------------------------\n");
        		if(Uyeler[aktifuye].bakiye<(acilis+((end - begin)*tarife)))
        		{
        			printf("Bakiyeniz yetersiz!..\n\n");
        			printf("Bakiye ekranina yonlendirilmek icin herhangi bir tusa basiniz.");
        			getch();
        			bakiye_yukleme(Uyeler,Scooterlar);
				}
				else{
					printf("Odeme Tamamlandi!");
					Scooterlar[i].kiraDurumu=0;
					Uyeler[aktifuye].Scooter.kiraDurumu=Uyeler[aktifuye].Scooter.scooterNo=0;
					Uyeler[aktifuye].bakiye=Uyeler[aktifuye].bakiye-(acilis+((end - begin)*tarife));
				}
			}
		}
  	}
  }
  if(counter==0)
  {
  	printf("scooter bulunamadi!");
  }
        printf("Devam etmek icin herhangi bir tusa basiniz");
     	getch();
        system("CLS"); 
        bilgiKayit(Uyeler,Scooterlar);
        menu(Uyeler,Scooterlar);
 
}
void bakiye_yukleme(kullanici *Uyeler,scooter *Scooterlar){
 	char kartAdSoyad[30],kartNumara[19],CVC[3],SKT[7],telefonKod[4],telefonKodSorgu[4],krediKayit;
 	float tutar;
 	int i;
 	srand(time(NULL));
 	for(i=0;i<4;i++){
	telefonKod[i]='A'+rand()%26;
	}
	system("cls");
	printf("\t\t---------BAKIYE YUKLEME EKRANI---------\n\n ");
	printf("<<<<<<<<<<          Kredi Karti ile Bakiye Yukleme          >>>>>>>>>>\n\n");
	if(Uyeler[aktifuye].kartkayit==1){		// Kullanici sonraki islemler icin kartini sisteme kaydettiyse bilgileri istenmiyor.
	printf("Yukleyeceginiz tutari giriniz(TL): ");
	scanf("%f",&tutar);
	printf("3D Secure Kodunuz:%s\n",telefonKod);	// Karttan para cekilmesi icin banka tarafindan kullanicinin telefonuna 3D Secure kodu gonderiliyor.
	printf("Bakiye yukleme onayi icin 3D Secure kodunuzu giriniz: ");
	scanf("%s",&telefonKodSorgu);
	if(strcmp(telefonKod,telefonKodSorgu)){
		printf("Yanlis kod girdiniz. Bakiye yukleme islemi basarisiz!");
		sleep(2);
		system("CLS");
		menu(Uyeler,Scooterlar);
	}
	else if(!strcmp(telefonKod,telefonKodSorgu)){
		Uyeler[aktifuye].bakiye+=tutar;
		printf("Yukleme Islemi Basarili.\n");
		printf("Bakiyeniz: %.2f",Uyeler[aktifuye].bakiye);
		sleep(2);
		system("CLS");
	}
	goto end;
	}
	else{
	printf("Sonraki islemleriniz icin kredi kartinizi sisteme kaydetmek ister misiniz?(E-H):\n");
	fflush(stdin);
	krediKayit=getchar();
	printf("Yukleyeceginiz tutari giriniz(TL): ");
	scanf("%f",&tutar);
	fflush(stdin);
	printf("Kart Uzerindeki Isim Soyisim: ");
	gets(kartAdSoyad);
	printf("Kart Numarasi: ");
	gets(kartNumara);
	printf("Son Kullanma Tarihi(orn:05/24): ");
	scanf("%s",&SKT);
	printf("CVC Kodu: ");
	scanf("%s",&CVC);
	printf("3D Secure Kodunuz:%s\n",telefonKod);
	printf("Bakiye yukleme onayi icin 3D Secure kodunuzu giriniz: ");
	scanf("%s",&telefonKodSorgu);
	if(strcmp(telefonKod,telefonKodSorgu)){
		printf("Yanlis kod girdiniz. Bakiye yukleme islemi basarisiz!");
		sleep(2);
		system("CLS");
	}
	else if(!strcmp(telefonKod,telefonKodSorgu)){
		Uyeler[aktifuye].bakiye+=tutar;
		printf("Yukleme Islemi Basarili.\n");
		printf("Bakiyeniz: %.2f",Uyeler[aktifuye].bakiye);
		sleep(2);
		system("CLS");
	}
	if(krediKayit=='E'){
		Uyeler[aktifuye].kartkayit=1;
		}
		else{
		Uyeler[aktifuye].kartkayit=0;
		}
	}
	end:;
	FILE *kredikarti,*uyebilgileri;
	kredikarti=fopen("kredikarti.TXT","w");
	uyebilgileri=fopen("uyebilgileri.TXT","w");
		for(i=0;i<=19;i++){
			fprintf(kredikarti,"%d\n",Uyeler[i].kartkayit);
			fprintf(uyebilgileri,"%s %s %s %s %s %d %f %d %d %d %d %d %d %s\n",Uyeler[i].ad,Uyeler[i].soyad,Uyeler[i].eposta,Uyeler[i].telefon,Uyeler[i].sifre,Uyeler[i].kartkayit,Uyeler[i].bakiye,Uyeler[i].ogrenci,Uyeler[i].Scooter.scooterNo,Uyeler[i].Scooter.uzaklik,Uyeler[i].Scooter.sarjDurumu,Uyeler[i].Scooter.kiraDurumu,Uyeler[i].ilkKullanim,Uyeler[i].tcNo);
			}
		if(uyebilgileri==NULL){
			printf("Kayit alinirken bir hata olustu.\n");
			exit(1);
		}
		if(kredikarti==NULL){
			printf("Kayit alinirken bir hata olustu.\n");
			exit(1);
			}
		fclose(uyebilgileri);
		fclose(kredikarti);
	kredikarti=fopen("kredikarti.TXT","r");
	uyebilgileri=fopen("uyebilgileri.TXT","r");
	for(i=0;i<=19;i++){
		fscanf(kredikarti,"%d\n",&Uyeler[i].kartkayit);
		fscanf(uyebilgileri,"%s %s %s %s %s %d %f %d %d %d %d %d %d %s\n",&Uyeler[i].ad,&Uyeler[i].soyad,&Uyeler[i].eposta,&Uyeler[i].telefon,&Uyeler[i].sifre,&Uyeler[i].kartkayit,&Uyeler[i].bakiye,&Uyeler[i].ogrenci,&Uyeler[i].Scooter.scooterNo,&Uyeler[i].Scooter.uzaklik,&Uyeler[i].Scooter.sarjDurumu,&Uyeler[i].Scooter.kiraDurumu,&Uyeler[i].ilkKullanim,Uyeler[i].tcNo);
	}
	if(uyebilgileri==NULL){
		printf("Kayit alinirken bir hata olustu.\n");
		exit(1);
	}
	if(kredikarti==NULL){
		printf("Kayit alinirken bir hata olustu");
		exit(1);
	}
	fclose(uyebilgileri);
	fclose(kredikarti);
		menu(Uyeler,Scooterlar);
	}
void kayit_gor(kullanici *Uyeler,scooter *Scooterlar){
 system("cls");
 FILE *s;
 int x,i;
 char y;
 s=fopen("ensonuye.TXT","r");
 fscanf(s,"%d",&x);
 fclose(s);
 x=x-1;
 if(x==-1){
 	printf("Su Anda Sisteme Kayitli Uye Yoktur!!!");
 	sleep(2);
 	system("cls");
 	menu_admin(Uyeler,Scooterlar);
 }
 else{
 	here:
 		system("cls");
 		printf("%15s  %10s %15s      %13s %13s %13s %13s\n\n","AD","SOYAD","E-POSTA","TELEFON","SIFRE","BAKIYE","OGRENCI");
 	for(i=0;i<=x;i++){
 		printf("%15s %10s   %15s    %10s %10s %11.2f ",Uyeler[i].ad,Uyeler[i].soyad,Uyeler[i].eposta,Uyeler[i].telefon,Uyeler[i].sifre,Uyeler[i].bakiye);
 		if(Uyeler[i].ogrenci)
 		printf("%15s\n\n","EVET");
 		else
 		printf("%15s\n\n","HAYIR");
	 }
	 printf("\nCikmak icin 1'e Basin\n");
	 y=getch();
	 if(y=='1'){
	system("cls");
	menu_admin(Uyeler,Scooterlar);
}
	 else
	 goto here;
 }
 } 
void kayit_sil(kullanici *Uyeler){
     system("cls");
     FILE *dosya;
     
     int j;
	FILE *f,*p,*d,*kredikarti;
	f=fopen("ensonuye.TXT","r");
	fscanf(f,"%d",&j);
	fclose(f);
	f=fopen("ensonuye.TXT","w");
	fprintf(f,"%d",(j-1));
	fclose(f);
    int i,b;
 	char tel[15];
 	printf("\nSilinecek kisinin telefon numarasini giriniz : ");
 	scanf("%s",tel);
 	for(i=0;i<=j;i++){
     if(!(strcmp(Uyeler[i].telefon,tel)))
     b=i;
 }
 dosya=fopen("uyebilgileri.txt","w");
 for(i=0;i<=j;i++){
 	if (i>=b)
 	{
 		Uyeler[i]=Uyeler[i+1];
	 }	 
}
            system("cls");
    		sleep(2);
    		bilgiKayit(Uyeler,Scooterlar);
    		menu_admin(Uyeler,Scooterlar);
}

void kayit_ara(kullanici *Uyeler){
 system("cls");
 FILE *dosya;
 char y,tel[15];
 
 int durum=0;
 fflush(stdin);
 printf("\nAramak istediginiz kisinin telefon numarasini giriniz: ");
 gets(tel);
 dosya=fopen("uyebilgileri.txt","r");
 if( dosya==NULL ){
  puts("Dosya acilamadi");
  exit(1);
 }
  while(!feof(dosya)){
   fscanf(dosya,"%s %s %s %s %s %d %f\n",uye.ad,uye.soyad,uye.eposta,uye.telefon,uye.sifre,&uye.kartkayit,&uye.bakiye); 
   if(strcmp(uye.telefon,tel) == 0){
    system("cls");
    printf("%15s  %10s %15s      %13s      %13s \n\n","AD","SOYAD","TELEFON","E-POSTA","BAKIYE");
    printf(" %15s %10s  %15s      %15s  %10.2f\n\n ",uye.ad,uye.soyad,uye.telefon,uye.eposta,uye.bakiye);
    durum=1;
     printf("\nCikmak icin herhangi bir tusa basin\n");
     getch();
    menu_admin(Uyeler,Scooterlar);
    	}	
	}
	if(durum==0){
    		system("cls");
			printf("\nAradiginiz kullanici bulunamadi.\n\nMenuye yonlendiriliyorsunuz...");
    		sleep(2);
    		menu_admin(Uyeler,Scooterlar);
		}
}
void olustur(scooter *Scooterlar){
	int i;
	for(i=0;i<=9;i++)
     {
     	Scooterlar[i].scooterNo=i+1;
     	Scooterlar[i].sarjDurumu=rand()%90+10;
     	Scooterlar[i].uzaklik=rand()%2900+100;
	 }
}

void yazdir(scooter *Scooterlar){
	FILE *f;
	int enson;
	f=fopen("ensonscooter.txt","r");
	fscanf(f,"%d",&enson);
	fclose(f);
	int i;
	for(i=0;i<enson;i++){
		if(Scooterlar[i].kiraDurumu==0){
			printf("\t\t\tNo:%d\t|Uzaklik:%dm\t|Sarj: %%%d\t|Scooter SeriKodu: #%.2d\t\n",i+1,Scooterlar[i].uzaklik,Scooterlar[i].sarjDurumu,Scooterlar[i].scooterNo);
		}
	}
}

void sirala(scooter *Scooterlar){
	FILE *f;
	int enson;
	f=fopen("ensonscooter.txt","r");
	fscanf(f,"%d",&enson);
	fclose(f);
	int i,j,secim;
	printf("\nSarja gore siralanmasi icin 1'e Uzakliga gore siralanmasi icin 2'ye basin");
	scanf("%d",&secim);
	system("CLS");
	if(secim==2){
	 for(i=0;i<enson;i++){
		for(j=1;j<enson-i;j++){
			if(Scooterlar[j-1].uzaklik>Scooterlar[j].uzaklik)
			{
				int temp3=Scooterlar[j].uzaklik;					//	Uzaklik durumuna gore siralanan scooterlarin
				Scooterlar[j].uzaklik=Scooterlar[j-1].uzaklik;		//	sarj ve numara bilgileri de yer degistiriyor.
				Scooterlar[j-1].uzaklik=temp3;
				int temp2=Scooterlar[j].scooterNo;
				Scooterlar[j].scooterNo=Scooterlar[j-1].scooterNo;
				Scooterlar[j-1].scooterNo=temp2;
				int temp=Scooterlar[j].sarjDurumu;
				Scooterlar[j].sarjDurumu=Scooterlar[j-1].sarjDurumu;
				Scooterlar[j-1].sarjDurumu=temp;
			}
		}
	}
}
	if(secim==1){
	 for(i=0;i<enson;i++){
		for(j=1;j<enson-i;j++){
			if(Scooterlar[j-1].sarjDurumu<Scooterlar[j].sarjDurumu)
			{
				int temp3=Scooterlar[j].uzaklik;					//	Sarj durumuna gore siralanan scooterlarin
				Scooterlar[j].uzaklik=Scooterlar[j-1].uzaklik;		//	uzaklik ve numara bilgileri de yer degistiriyor.
				Scooterlar[j-1].uzaklik=temp3;
				int temp2=Scooterlar[j].scooterNo;
				Scooterlar[j].scooterNo=Scooterlar[j-1].scooterNo;
				Scooterlar[j-1].scooterNo=temp2;
				int temp=Scooterlar[j].sarjDurumu;
				Scooterlar[j].sarjDurumu=Scooterlar[j-1].sarjDurumu;
				Scooterlar[j-1].sarjDurumu=temp;
				}
			}
		}
	}
}

void scooter_ekleme(kullanici *Uyeler,scooter *Scooterlar){
 	system("cls");
 	int k,i;
 	FILE *f,*p,*x;
 	f=fopen("ensonscooter.TXT","r");
 	fscanf(f,"%d",&k);
 	fclose(f);
 	p=fopen("ensonscooter.TXT","w");
 	fprintf(p,"%d",(k+1));
 	fclose(p);
	printf("\n===================================");
	printf("\nEklemek Istediginiz Scooter'in Sarj Yuzdesini Giriniz:  ");
	scanf("%d",&xscooter.sarjDurumu);
	system("cls");
	x=fopen("scooterbilgi.TXT","w");
	for(i=0;i<=19;i++){
		if(i==k)
		fprintf(x,"%d %d %d %d %d\n",k+1,(rand()%2900+100),xscooter.sarjDurumu,0,0);
		else
		fprintf(x,"%d %d %d %d\n",Scooterlar[i].scooterNo,Scooterlar[i].uzaklik,Scooterlar[i].sarjDurumu,Scooterlar[i].kiraDurumu);
		
	}
	fclose(x);
	x=fopen("scooterbilgi.TXT","r");
	for(i=0;i<=19;i++){
		fscanf(x,"%d %d %d %d\n",&Scooterlar[i].scooterNo,&Scooterlar[i].uzaklik,&Scooterlar[i].sarjDurumu,&Scooterlar[i].kiraDurumu);
	}
	fclose(x);
	printf("****   Scooter Basariyla Eklendi   ****");
	sleep(2);
	system("cls");
	menu_admin(Uyeler,Scooterlar);
 } 
void admin_giris(kullanici *Uyeler,scooter *Scooterlar){
 	int a=0,i=0,c;
char kullaniciAdi[10],Sifre[10];
admin_yeniden_deneme:
printf("\n===================================\n");
printf("Admin Kullanici Adi Giriniz=  ");
scanf("%s",kullaniciAdi);
printf("\n===================================\n");
printf("Admin Sifre Giriniz=  ");
i=0;
while(i<10)
	{
	    Sifre[i]=getch();
	    c=Sifre[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	Sifre[i]='\0';
if(!strcmp("admin",kullaniciAdi) && !strcmp("1234",Sifre)){
printf("\n\n---Basariyla Giris Yapildi---");
sleep(2);
system("cls");
menu_admin(Uyeler,Scooterlar);
}
else{
	if(a==2){
		printf("\n\n\a3 Kere Yanlis Bilgi Girdiniz...");
		sleep(1);
		system("cls");
		printf("Oturum Sonlandiriliyor...");
		sleep(2);
		exit(0);
		
	}
	printf("\n\n\aYanlis Bilgi Girisi\n\n");
	printf("Tekrar Deneyiniz...");
	a++;
	sleep(2);
	system("cls");
	goto admin_yeniden_deneme;
}
 }
void uye_ol(kullanici *Uyeler,scooter *Scooterlar){
char x;
printf("===================================\n");
printf("Adinizi Giriniz:  ");
scanf("%s",&uye.ad);
printf("===================================\n");
printf("Soyadinizi Giriniz:  ");
scanf("%s",&uye.soyad);
printf("===================================\n");
printf("TC Kimlik Numaranizi Giriniz:	");
scanf("%s",&uye.tcNo);
printf("===================================\n");
printf("E-postanizi Giriniz:  ");
scanf("%s",&uye.eposta);
printf("===================================\n");
printf("Telefonunuzu Giriniz:  ");
scanf("%s",&uye.telefon);
printf("===================================\n");
printf("Ogrenci Misiniz?       1.Evet  2.Hayir    ");
x=getch();
if(x=='1')
uye.ogrenci=1;
else
uye.ogrenci=0;
printf("\n===================================\n");
printf("Lutfen Sifre Belirleyiniz (en fazla 10 karakter):  ");
scanf("%s",&uye.sifre);
yas_sorgu();
int i,j,k;
FILE *f,*p,*d,*kredikarti;
f=fopen("ensonuye.TXT","r");
fscanf(f,"%d",&j);
fclose(f);
f=fopen("ensonuye.TXT","w");
fprintf(f,"%d",(j+1));
fclose(f);
p=fopen("uyebilgileri.TXT","w");
for(i=0;i<=19;i++){
	if(i==j){
		fprintf(p,"%s %s %s %s %s %d %f %d %d %d %d %d %d %s\n",uye.ad,uye.soyad,uye.eposta,uye.telefon,uye.sifre,0,0.0,uye.ogrenci,0,0,0,0,0,uye.tcNo);
	}
	else{
		fprintf(p,"%s %s %s %s %s %d %f %d %d %d %d %d %d %s\n",Uyeler[i].ad,Uyeler[i].soyad,Uyeler[i].eposta,Uyeler[i].telefon,Uyeler[i].sifre,Uyeler[i].kartkayit,Uyeler[i].bakiye,Uyeler[i].ogrenci,Uyeler[i].Scooter.scooterNo,Uyeler[i].Scooter.uzaklik,Uyeler[i].Scooter.sarjDurumu,Uyeler[i].Scooter.kiraDurumu,Uyeler[i].ilkKullanim,Uyeler[i].tcNo);
	}
	
}
fclose(p);
d=fopen("uyebilgileri.TXT","r");
for(k=0;k<=19;k++){
	fscanf(d,"%s %s %s %s %s %d %f %d %f %d %d %d %d %s\n",Uyeler[k].ad,Uyeler[k].soyad,Uyeler[k].eposta,Uyeler[k].telefon,Uyeler[k].sifre,&Uyeler[k].kartkayit,&Uyeler[k].bakiye,&Uyeler[k].ogrenci,&Uyeler[k].Scooter.scooterNo,&Uyeler[k].Scooter.uzaklik,&Uyeler[k].Scooter.sarjDurumu,&Uyeler[k].Scooter.kiraDurumu,&Uyeler[k].ilkKullanim,Uyeler[k].tcNo);
}
fclose(d);
system("cls");
printf("\nAna Menuye Aktariliyorsunuz...\n");
sleep(2);
system("cls");


main();
 }
void cikis(){
	system("cls");
	printf("  \n \t\t\t              MARMARA UNIVERSITESI TEKNOLOJI FAKULTESI              \n");
	printf("     \t\t\t                   BILGISAYAR MUHENDISLIGI BOLUMU                   \n");
	printf("     \t\t\t                    BILGISAYAR PROGRAMLAMA DERSI                    \n");
	printf("     \t\t\t                              PROJESI                               \n");
	printf("     \t\t\t                                                                    \n");
	printf("     \t\t\t        * * * * * * * * * * * * * * * * * * * * * * * * * * *       \n");
	printf("     \t\t\t        *      ------    PROJE OGRENCILERI     ------       *       \n");
	printf("     \t\t\t        *                                                   *       \n");
	printf("     \t\t\t        *           Muhammed Emir Keles  170420010          *       \n");
	printf("     \t\t\t        *                                                   *       \n");
	printf("     \t\t\t        *           Amro Tulimat         170420924          *       \n");
	printf("     \t\t\t        *                                                   *       \n");
	printf("     \t\t\t        *           Taha Yasin Muslu     170420033          *       \n");
	printf("     \t\t\t        *                                                   *       \n");
	printf("     \t\t\t        *           Vahit Seyit Basa     170420024          *       \n");
	printf("     \t\t\t        *                                                   *       \n");
	printf("     \t\t\t        *                                                   *       \n");
	printf("     \t\t\t        * * * * * * * * * * * * * * * * * * * * * * * * * * *       \n");
	
}
void uye_giris(kullanici *Uyeler,scooter *Scooterlar){
	int i,sayac=1;
	printf("===================================\n");
	printf("E-Posta Giriniz:  ");
	scanf("%s",uye.eposta);
	printf("===================================\n");
	printf("Sifre Giriniz:  ");
	scanf("%s",uye.sifre);
	printf("===================================\n");
	for(i=0;i<=19;i++){
		if(!(strcmp(uye.eposta,Uyeler[i].eposta)) && !(strcmp(uye.sifre,Uyeler[i].sifre))){
			system("cls");
			printf("Menuye Aktariliyorsunuz...\n");
			aktifuye=i;
			sleep(2);
			menu(Uyeler,Scooterlar);
			break;
	}
			sayac=0;
		}
		if(sayac==0){
		system("cls");
			printf("Belirttiginiz Bilgilerde Kullanici Bulunamadi...");
			sleep(2);
			main();
			}
}
void sifremi_unuttum(kullanici *Uyeler){
	int i,sayac=1;
	char sorguEposta[30],epostaKod[4],epostaKodSorgu[4];
	srand(time(NULL));
	for(i=0;i<4;i++){
	epostaKod[i]='A'+rand()%26;
	}
	printf("===================================\n");
	printf("E-Posta Giriniz:  ");
	scanf("%s",&sorguEposta);
	for(i=0;i<=19;i++){
		if(!(strcmp(sorguEposta,Uyeler[i].eposta))){
			system("cls");
			printf("\t=================	Posta Kutusu	    =================\n\n");
			printf(">>>>>>  Scooter Kiralama Sifremi Unuttum Kodu: %s\n\n",epostaKod);
			printf("\n\n\n>>>>>>  E-Postaniza gelen kodu giriniz: ");
			scanf("%s",&epostaKodSorgu);
			if(strcmp(epostaKod,epostaKodSorgu)){
				printf("Yanlis kod girdiniz!\nMenuye yonlendiriliyorsunuz...");
				sleep(2);
				main();
				break;
			}
			else if(!strcmp(epostaKod,epostaKodSorgu)){
				printf("\n\n>>>>>>  Sifreniz: %s\n",Uyeler[i].sifre);
				printf("\n\nGecmek icin herhangi bir tusa basiniz...");
				getch();
				main();
				break;
			}
		}
	}
		printf("\n\n\nBelirttiginiz Bilgilerde Kullanici Bulunamadi...");
		sleep(2);
		main();
		}
void bilgiKayit(kullanici *Uyeler,scooter *Scooterlar){
	int i;
	 FILE *f,*d,*s,*t,*q;
f=fopen("uyebilgileri.TXT","w");
for(i=0;i<=19;i++){
	if(i==aktifuye)
	fprintf(f,"%s %s %s %s %s %d %f %d %d %d %d %d %d %s\n",Uyeler[i].ad,Uyeler[i].soyad,Uyeler[i].eposta,Uyeler[i].telefon,Uyeler[i].sifre,Uyeler[i].kartkayit,Uyeler[i].bakiye,Uyeler[i].ogrenci,Uyeler[i].Scooter.scooterNo,Uyeler[i].Scooter.uzaklik,Uyeler[i].Scooter.sarjDurumu,Uyeler[i].Scooter.kiraDurumu,Uyeler[i].ilkKullanim,Uyeler[i].tcNo);
	else
	fprintf(f,"%s %s %s %s %s %d %f %d %d %d %d %d %d %s\n",Uyeler[i].ad,Uyeler[i].soyad,Uyeler[i].eposta,Uyeler[i].telefon,Uyeler[i].sifre,Uyeler[i].kartkayit,Uyeler[i].bakiye,Uyeler[i].ogrenci,Uyeler[i].Scooter.scooterNo,Uyeler[i].Scooter.uzaklik,Uyeler[i].Scooter.sarjDurumu,Uyeler[i].Scooter.kiraDurumu,Uyeler[i].ilkKullanim,Uyeler[i].tcNo);
}
fclose(f);
d=fopen("uyebilgileri.TXT","r");
for(i=0;i<=19;i++){
	fscanf(d,"%s %s %s %s %s %d %f %d %d %d %d %d %d %s\n",Uyeler[i].ad,Uyeler[i].soyad,Uyeler[i].eposta,Uyeler[i].telefon,Uyeler[i].sifre,&Uyeler[i].kartkayit,&Uyeler[i].bakiye,&Uyeler[i].ogrenci,&Uyeler[i].Scooter.scooterNo,&Uyeler[i].Scooter.uzaklik,&Uyeler[i].Scooter.sarjDurumu,&Uyeler[i].Scooter.kiraDurumu,&Uyeler[i].ilkKullanim,Uyeler[i].tcNo);
}
fclose(d);
s=fopen("scooterbilgi.TXT","w");
for(i=0;Scooterlar[i].scooterNo!=0;i++){
	fprintf(s,"%d %d %d %d\n",Scooterlar[i].scooterNo,Scooterlar[i].uzaklik,Scooterlar[i].sarjDurumu,Scooterlar[i].kiraDurumu);
}
fclose(s);
t=fopen("scooterbilgi.TXT","r");
for(i=0;i<=19;i++){
	fscanf(t,"%d %d %d %d\n",&Scooterlar[i].scooterNo,&Scooterlar[i].uzaklik,&Scooterlar[i].sarjDurumu,&Scooterlar[i].kiraDurumu);
}
fclose(t);
q=fopen("saat.TXT","r");
for(i=0;i<=19;i++){
	fscanf(q,"%d\n",&Uyeler[i].sure);
}
fclose(q);
}
void yas_sorgu(){
int dtarih[8],starih[8];
int dtarihgun,dtarihay,dtarihyil,starihgun,starihay,starihyil;
printf("===================================\n");
printf("Lutfen Dogum Tarihinizi Giriniz (gun/ay/yil):  ");
dtarih[0]=getche()-'0';
dtarih[1]=getche()-'0';
printf("/");
dtarih[2]=getche()-'0';
dtarih[3]=getche()-'0';
printf("/");
dtarih[4]=getche()-'0';
dtarih[5]=getche()-'0';
dtarih[6]=getche()-'0';
dtarih[7]=getche()-'0';

char x[30];
time_t t=time(NULL);
strcpy(x,ctime(&t));
if(x[4]=='F'){
starih[2]=0;
starih[3]=2;
}
else if(x[4]=='S'){
starih[2]=0;
starih[3]=9;	
}
else if(x[4]=='O'){
starih[2]=1;
starih[3]=0;	
}
else if(x[4]=='N'){
starih[2]=1;
starih[3]=1;	
}
else if(x[4]=='D'){
starih[2]=1;
starih[3]=2;	
}
else if(x[4]=='J'){
if(x[5]=='j'){
starih[2]=0;
starih[3]=1;
}
else if(x[6]=='N'){
starih[2]=0;
starih[3]=6;	
}
else{
starih[2]=0;
starih[3]=7;	
}
}
else if(x[4]=='M'){
if(x[6]=='r'){
starih[2]=0;
starih[3]=3;
}
else{
starih[2]=0;
starih[3]=5;	
}
}
else if(x[4]=='A'){
if(x[5]=='p'){
starih[2]=0;
starih[3]=4;
}
else{
starih[2]=0;
starih[3]=8;	
}
}
starih[0]=x[8]-'0';
starih[1]=x[9]-'0';
starih[4]=x[20]-'0';
starih[5]=x[21]-'0';
starih[6]=x[22]-'0';
starih[7]=x[23]-'0';

starihgun=starih[0]*10+starih[1];
starihay=starih[2]*10+starih[3];
starihyil=starih[4]*1000+starih[5]*100+starih[6]*10+starih[7];
dtarihgun=dtarih[0]*10+dtarih[1];
dtarihay=dtarih[2]*10+dtarih[3];
dtarihyil=dtarih[4]*1000+dtarih[5]*100+dtarih[6]*10+dtarih[7];

if(starihyil-dtarihyil>18){
	printf("\nYasiniz sisteme kaydolmak icin yeterli.\n");
	sleep(2);
}
else if(starihyil-dtarihyil<18){
	printf("\nYasiniz sisteme kaydolmak icin yeterli degil.\n");
	sleep(3);
	main();
}
else{
	if(starihay-dtarihay>0){
		printf("\nYasiniz sisteme kaydolmak icin yeterli.\n");
		sleep(2);
	}
	else if(starihay-dtarihay<0){
	printf("\nYasiniz sisteme kaydolmak icin yeterli degil.\n");
	sleep(3);
	main();
	}
	else{
		if(starihgun-dtarihgun>=0){
			printf("\nYasiniz sisteme kaydolmak icin yeterli.\n");	
			sleep(2);
		}
		else{
			printf("\nYasiniz sisteme kaydolmak icin yeterli degil.\n");
		sleep(3);
		main();
		}
	}
}	
}
