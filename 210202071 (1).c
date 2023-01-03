#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fileapi.h>
#include <dirent.h>

int Global_counter=0; //genel sayac

int Global_counter_2=0;//genel sayac 2

int blm=200;//yetim etiket ders kodu sayacı

struct dizi{
    char dizi[200][1000];
    int indisler[20];
};

struct dizi etiketler;//tüm etiketler burada tutuluyor

struct dizi yetim_etiketler;//tüm yetim etiketler burada tutuluyor

struct dizi Global_dosya_yolu;//tüm txt uzantılı dosya yolları burada tutuluyor

struct dizi Global_indis;//etiketlerin [[ ]]indisleri burada tutuluyor

struct dizi Global_istenen;//tüm istenen etiketler burada tutuluyor

void dosya_yolu_bulma(const char* dirname); 

int *string_ara_1(struct dizi ana_metin, char *aranan);

void islem();

void arama(int a);

int karakter_sayisi(char *s);

struct dizi dosyayi_diziye_yazma(char *dosya_yolu);

void guncelleme(int a);

void dosyadan_etiket_degistirme(char *dosya_yolu,char *degisecek_etiket,char *degisecek_etiketin_yerine_gececek_etiket);

int string_ara_2(char *ana_metin, char * aranan);

void silme(char *dosya_yolu,char *degisenin_yerine_gececek_etiket,char*degisecek_etiket,int indis[20][10]);

void etiket_kontrol(char *dosya_yolu);

int *string_ara_3(struct dizi ana_metin, char * aranan) ;

void cikti(int a);

void yetim_etiket_bulma(int a);

void yetim_etiket_ekrana_yazdirma(int a);

void yetim_etiket_dosya_olusturma(char *yetim);

void istenen_etiket(int a);


int main(){
    setlocale(LC_ALL, "Turkey");
    remove("output.txt");
    printf("Üniversite programina hosgeldiniz\n");
    islem();
    return 0;
}

void dosya_yolu_bulma(const char* dosya_adi) {//dosya yollarını Global_dosya_yolu adlı struct dizisine yazma
    DIR* dir = opendir(dosya_adi);
    if (dir == NULL) {
        return;
    }
    struct dirent* dosya;
    dosya = readdir(dir);
    while (dosya != NULL) {
        
        if (strcmp(dosya->d_name, ".") != 0 && strcmp(dosya->d_name, "..") != 0) {
            char path[100] = { 0 };
            strcat(path, dosya_adi);
            strcat(path, "/");
            strcat(path, dosya->d_name);
            int x=string_ara_2(dosya->d_name,"output.txt");
            int i=string_ara_2(dosya->d_name,"txt");
            if (i==1&& x==0)
            {
                strcat(Global_dosya_yolu.dizi[Global_counter],path);
                strcat(Global_istenen.dizi[Global_counter],dosya->d_name);
                Global_counter++;
            }
            
            
            dosya_yolu_bulma(path);
        }
        dosya = readdir(dir);
            

    }
    closedir(dir);
}

struct dizi dosyayi_diziye_yazma(char *dosya_yolu){//dosya içeriğini diziye çekme
    Global_counter=0;
    struct dizi dondurulecek_dizi;
    int i=0;
    FILE *file;
    
    fopen_s(&file,dosya_yolu,"r");
  
    if (file==NULL){       
        printf("dosya acilamadi!");
        exit(1);
    }
    for(int a=0;a<100;a++)  for (int b = 0; b<1000 ; b++)   dondurulecek_dizi.dizi[a][b]=NULL;//dizi içeriğini sıfırlama
    while (!feof(file)){
		for (i = 0; !feof(file);i++) {
            fgets(dondurulecek_dizi.dizi[Global_counter],1000,file);
            Global_counter++;
		}
    } 
    fclose(file);
    return dondurulecek_dizi;
}

int karakter_sayisi(char *s) {//karakter sayısını bulur
    int i;
    for (i = 0 ; s[i] != '\0' ; i++){}
    return i-1;
}

int string_ara_2(char *ana_metin, char * aranan) {//genel string bulma işlemi yapar
    int i, j;
    int ana_metin_n = karakter_sayisi(ana_metin);
    int aranan_N = karakter_sayisi(aranan);
    
    for (i = 0 ; i <= ana_metin_n ; i++) {
        for (j = 0 ; j < aranan_N ; j++) {
            if (ana_metin[i+j] != aranan[j])
                break;
                
        }
            
        if (j == aranan_N){
            return 1; 
        }
    }
    
    return 0;
}


void islem(){//işlemler menüsünün arayüz yazılımı burada bulunmaktadır aynı zamanda etiket tespiti ve dosya yolları bu fonksiyonun içerisinde bulunur
    int a,secim;
        
    for (int x = 0; ; x++){  
        secim=0;     
        for(int z=0;z<100;z++)  for (int b = 0; b<1000 ; b++)   etiketler.dizi[z][b]=NULL;//dizi içeriğini sıfırlama
        for(int z=0;z<100;z++)  for (int b = 0; b<1000 ; b++)   Global_dosya_yolu.dizi[z][b]=NULL;//dizi içeriğini sıfırlama
        for(int x=0;x<100;x++) for(int b=0;b<1000;b++) Global_istenen.dizi[x][b]=NULL;//dizi içeriğini sıfırlama
        Global_counter_2=0;
        dosya_yolu_bulma(".");//Tüm .txt uzantılı dosyayolları bulunur 
        a=Global_counter;
        Global_counter=0;
        
        printf("\nyapmak istediginiz islemi seciniz:\n");
        printf("Etiket arama islemi icin 1 \nGuncelleme icin 2\ncikti icin 3'u seciniz:\n ");        
        scanf("%d",&secim);
        for (int i = 0; i < a; i++){//tüm dosyalardaki etiketler bulunur
            etiket_kontrol(Global_dosya_yolu.dizi[i]);
        }

        
        if (secim==1){
            printf("Etiket arama islemi secildi yonlendirme yapiliyor...\n");
            yetim_etiket_ekrana_yazdirma(a);
        istenen_etiket(a);
            arama(a);
            
        }
        else if(secim==2){
            printf("Guncelleme islemi secildi yonlendirme yapiliyor...\n");
            guncelleme(a);
        }
        else if(secim==3){
            printf("cikti olusturuluyor...");
            cikti(a);
        }
        else break;
    }
}

void etiket_kontrol(char *dosya_yolu){//tüm dosyalar taranarak geçerli etiket formatına uyan bütün etiketler bulunur
    FILE *file;
    fopen_s(&file,dosya_yolu,"r");
    struct dizi gecici;
    char aranan[250];
    char *ayrac1="[[";
    char *ayrac2="]]";
    int gecici_dizi_n;
    int aranan_N=karakter_sayisi(aranan);
    int j,k;
    int indisno[40][40];
    for (int i = 0; i < 40; i++)
        for (int a = 0; a <40; a++)  indisno[i][a]=-1;
    for (int z = 0; fgets(gecici.dizi[z],250,file)!=NULL; z++){//[[indis bulma
        gecici_dizi_n=karakter_sayisi(gecici.dizi[z]);
        k=0;
        for (int i = 0 ; i <= gecici_dizi_n ; i++) {
            for (j = 0 ; j < 2 ; j++) {
                if (gecici.dizi[z][i+j] != ayrac1[j])  break;
            }
            
            if (j == 2){
                indisno[z][k]=(j+i);
                k+=2;
            }
        }

        k=1;
        for (int i = 0 ; i <= gecici_dizi_n ; i++) {//]]indis bulma
            for (j = 0 ; j < 2 ; j++) {
                if (gecici.dizi[z][i+j] != ayrac2[j])  break;
            }

            if (j == 2){
                indisno[z][k]=(j+i);
                k+=2;
            }
        }    

    }

    fclose(file);
    j=0;
    k=0;
    
    int ilk=0,ikinci=0;
    FILE *dosya;

    fopen_s(&dosya,dosya_yolu,"r");
    while(!feof(dosya)){
        fgets(gecici.dizi[ilk],250,dosya);
        for (int k = 0; k<20; k+=2){
            int a=0;
            ikinci=indisno[j][k+1];
            if(ilk<0||ikinci<0) break;
            else {
                for (ilk=indisno[j][k]; ilk<ikinci-2; ilk++){//etiketleri global etiketler dizisine çekme
                    etiketler.dizi[Global_counter_2][a]=gecici.dizi[j][ilk];
                    a++;
                }
                Global_counter_2++;        
            }

        }

        j++;
    }

    fclose(dosya);
    for(int a=0;a<100;a++) for(int b=0;b<1000;b++) gecici.dizi[a][b]=NULL;//dizi içeriğini sıfırlama
    //1 den fazla etiket kontrolü 


}

//int a :toplam dosya yolu sayısı
void arama(int a){//arama işlemi burada gerçekleştirilir hem etiket hem de normal kelime arama işlemlerini tek fonksiyonda halledildi
    char aranan[100];
    printf("arama yapmak istediginiz etiketi giriniz: ");
    while ((getchar()) != '\n');
    fgets(aranan,100,stdin);
    int b;
    for (int i = 0; i < a; i++){
        struct dizi buf=dosyayi_diziye_yazma(Global_dosya_yolu.dizi[i]);
        Global_counter=0;
        b=string_ara_3(buf,aranan);
        if(Global_counter_2!=0){
            printf("%s isimli dosyada bulunmustur:%d tane vardır %d nci satırda \n",Global_dosya_yolu.dizi[i],Global_counter_2,b);
        }
    }
}

int *string_ara_3(struct dizi ana_metin, char * aranan) {//arama fonksiyonuna özel yazılmış string arama fonksiyonudur [[ ]]formatında aratılmamış etiketleri ayırt etmede kullanmak üzere tasarlandı
    
    int j=0,b=0;
    int aranan_N = karakter_sayisi(aranan);
    Global_counter_2=0;
    
    for (int i = 0 ; i <= 200 ; i++) {
        for (int a = 0; a <100 ; a++){
            for (j = 0 ; j < aranan_N ; j++)    if (ana_metin.dizi[i][a+j] != aranan[j])    break;
            
            if (j == aranan_N){
                if(ana_metin.dizi[i][a+j]==aranan[j-1]) {//programlama_I ve programlama_II arasındaki farkı bulmada kullanılır([[ ]]formatıyla aranmamış ise )
                    break;
                }
                else{
                    Global_counter_2++;
                    b=i+1;
                }
            }
        }
    }
    return b;
}

//int a :toplam dosya yolu sayısı
void yetim_etiket_ekrana_yazdirma(int a){//yetim etiketleri arama arayüzünde konsola yazmak için oluşturulmuş bir fonksiyondur sadece arama fonksiyonunda kullanılmıştır
    int controller;   
    int c=Global_counter_2;//toplam etiket sayısını c değişkenine atama
    Global_counter_2=0;
    for (int i = 0; i <c; i++){
        for(int x=i+1; x<c;x++){
            int d=string_ara_2(etiketler.dizi[i],etiketler.dizi[x]);
            if (d==1){
                int z=karakter_sayisi(etiketler.dizi[i]);
                int y=karakter_sayisi(etiketler.dizi[x]);
                if (y==z){
                    *etiketler.dizi[x]=NULL;  //aynı etiketleri silme
                }
            }
        }
    }
    Global_counter_2=0;
    printf("\n%s\n","Yetim Etiketler:");
    for (int i = 0; i < a+10; i++){
        controller=0;
        for(int j=0;j<a+2;j++) {
            if(*etiketler.dizi[i]==NULL){controller++; break;}//silinen etiketlerin arasındaki boşluk giderme
            if(string_ara_2(Global_dosya_yolu.dizi[j], etiketler.dizi[i])) controller++; //etikete ait dosya varsa 'controller' kontrolcüsünü 1 arttırır ve ilk forun içerisindeki if komutuna girmesini engeller
        }
        if (controller==0){
            printf("\n%s",etiketler.dizi[i]);
        }
    }
}

//int a :toplam dosya yolu sayısı
void istenen_etiket(int a){//istenen etiketleri arama arayüzünde konsola yazmak için oluşturulmuş bir fonksiyondur sadece arama fonksiyonunda kullanılmıştır
    int controller,i,j;
    printf("\n\nİstenen Etiket:\n\n");
    for ( i = 0; i < a; i++){
        controller=0;
        for( j=0;j<a+2;j++) {
            if(string_ara_2(Global_istenen.dizi[i], etiketler.dizi[j])) {//dosya yollarını teker teker etiketlerle karşılaştırır eğer var ise controller değişkenini 1 arttırır bu sayede ilk for döngüsündeki if komutuna girmez
                controller++;
                break;
            }
        }
        if (controller==0){
            int z=karakter_sayisi(Global_istenen.dizi[i]);
            for(int x=0;x<z-3;x++) printf("%c",Global_istenen.dizi[i][x]);//.txt kısmını atıp ekrana istenen etiketleri yazdırır
            printf("\n");
        }
    }

}

//int a :toplam dosya yolu sayısı
void guncelleme(int a){//yetim etikete dosya oluşturma ve etiket güncelleme (etiket güncellenince otomatik o etikete ait dosya adıda güncellenmekte) işlemi yapılmaktadır
    int secim=0;
    printf("etiket değiştirmek için 1 yetim etiket dosyası oluşturmak için 2 giriniz: ");
    scanf("%d",&secim);
    if(secim==1){//etiket değiştirme işlemi
        char aranan[100];
        char degisecek_etiket[30],degisenin_yerine_gececek_etiket[30];
        printf("degistirmek istediginiz etiketi giriniz: ");
        while ((getchar()) != '\n');
        fgets(degisecek_etiket,30,stdin);
        printf("degistirmek istediginiz etiketin yeni ismi ne olsun?: ");
        fgets(degisenin_yerine_gececek_etiket,30,stdin);
        for (int i = 0; i < a; i++){
            dosyadan_etiket_degistirme(Global_dosya_yolu.dizi[i],degisecek_etiket,degisenin_yerine_gececek_etiket);//etiket değiştirildiği fonksiyona yönlendirme
            Global_counter_2=0;
            
            if (string_ara_2(Global_dosya_yolu.dizi[i],degisecek_etiket)){//değiştirilen etiket yetim değil ise dosya adı değiştirilir
                char path[100]={ 0 };
                int z =karakter_sayisi(Global_dosya_yolu.dizi[i]);//dosya yolunun karakter sayısı
                char *k=strrchr(Global_dosya_yolu.dizi[i],'/');
                int k_n=karakter_sayisi(k);//dosya adının karakter sayısı
                int x=karakter_sayisi(degisenin_yerine_gececek_etiket);
                for (int a = 0; a < z-k_n+1; a++){
                    path[a]=Global_dosya_yolu.dizi[i][a];
                }
                printf("dosyayolu : %s\n",Global_dosya_yolu.dizi[i]);
                strncat(path,degisenin_yerine_gececek_etiket,x);
                strcat(path,".txt");
                printf("path :%s\n",path);
                rename(Global_dosya_yolu.dizi[i],path);   
            }
        
        }
    }
    
    else if(secim==2){//yetim etikete dosya oluşturma işlemi
        char yetim[100];
        printf("dosyası olusturulacak yetim etiket: ");
        while (getchar() != '\n');
        fgets(yetim,100,stdin);
        yetim_etiket_dosya_olusturma(yetim);
    }
    
    
}

void dosyadan_etiket_degistirme(char *dosya_yolu,char *degisecek_etiket,char *degisenin_yerine_gececek_etiket){ 
    FILE *file;
    fopen_s(&file,dosya_yolu,"r");
    struct dizi gecici;
    int indis[20][10];
    int gecici_dizi_n;
    int aranan_N=karakter_sayisi(degisecek_etiket);
    int j,k;

    for (int i = 0; i < 20; i++)    for (int a = 0; a <10; a++)  indis[i][a]=-5;
    
    for (int z = 0; fgets(gecici.dizi[z],250,file)!=NULL; z++){//[[indis bulma
        gecici_dizi_n=karakter_sayisi(gecici.dizi[z]);
        k=0;
        for (int i = 0 ; i <= gecici_dizi_n ; i++){
            for (j = 0 ; j < aranan_N ; j++){
                if (gecici.dizi[z][i+j] != degisecek_etiket[j])  break;
                if (gecici.dizi[z][i+j+1]==degisecek_etiket[j]){//programlama_I ile programlama_II arasındaki farkı ayırt etmek için kontrolcü
                    j++;
                }   
            }
            if (j == aranan_N){
                indis[z][k]=i+1;
                k++;
                Global_counter_2++;
            }
        }
        Global_counter++;

    }

    fclose(file);
    
    
    
    if(Global_counter_2==0){ //global counter 2 0 ise global counter da 0 lanır ki yanlış işlem engellensin
        Global_counter=0;
    }
    
    else
        silme(dosya_yolu,degisenin_yerine_gececek_etiket,degisecek_etiket,indis);//bulunan değişecek etiketin indisleri silme fonksyonuna gönderilir 
}

void silme(char *dosya_yolu,char *degisenin_yerine_gececek_etiket,char *degisecek_etiket,int indis[20][10]){//eski etiketi siler ve yeni etiketi yerine yazar
    struct dizi metin;
    metin=dosyayi_diziye_yazma(dosya_yolu);//dosya yolunu tekrar açma için kaydedilir
    int i=0,a,b,c,d,k;
    remove(dosya_yolu);//dosyayı siler
    FILE *dosya;
    fopen_s(&dosya,dosya_yolu,"a");//dosyayı yeni ismiyle açar
    b=karakter_sayisi(degisecek_etiket);
    d=karakter_sayisi(degisenin_yerine_gececek_etiket);
    a=0;
    
    for (int j = 0; j<Global_counter; j++){
        c=karakter_sayisi(metin.dizi[j]);
        a=0;
        etiket:
        for (;; a++){
            if(indis[j][i]==-5) break;//indis -5 e eşitse o satırda etiket yoktur
            if (a==c)   break; //sonsuz döngüden a=c ise döngü kırılır(c:o satırdaki karakter sayısı)
      
            if (a==indis[j][i]-1){//degisecek etiketin yerine yeni etiketi yazma
                for (k = 0; k<d; k++)  fputc(degisenin_yerine_gececek_etiket[k],dosya);
                i++;
                a=a+b; //a Yı degisen etiketin indisi kadar kaydırır ki degisen etiketin üstüne yazılmasın
                if (indis[j][i]==-5){
                    for (;a<c; a++){
                        fputc(metin.dizi[j][a],dosya);//değişen etiketten sonraki son metinleri yazdırır
                    }
                    break;
                }
                
                for (;a<indis[j][i]-1; a++){//
                    fputc(metin.dizi[j][a],dosya);
                }
                goto etiket;  //aynı satırda 1 den fazla aynı etiket varsa onu da değiştirmek için kullanıldı 
            }
            fputc(metin.dizi[j][a],dosya);  //değişecek etiketin indisine gelene kadar yazma
        }
        if (a==0){
            fprintf(dosya,"%s",metin.dizi[j]);//o dosyada degisecek etiket yoksa aynen yazdırır
        }
        
        else    fprintf(dosya,"%s","\n");  //degisecek etiket varsa satır sonunda alt satıra geçirir
       i=0;
    }
    Global_counter=0;
    fclose(dosya);
}

void yetim_etiket_dosya_olusturma(char *yetim){//yetim etikete dosya oluşturma ve içerisine yazma işlemi burda yapılır 
    FILE *file;
    char path[100]="./dersler/";
    int x=karakter_sayisi(yetim);
    strncat(path,yetim,x);
    strcat(path,".txt");
    printf("path :%s",path);
    fopen_s(&file,path,"a");
    fprintf(file,"%s%d\n\n","Dersin Kodu\t:BLM",blm );
    fprintf(file,"%s%s\n","Dersin Adı\t:",yetim);
    fprintf(file,"%s\n","Dersin İçeriği: ");
    blm++;//global bir ders kodu ekleme sayacı
    fclose(file);

        
    
}

void cikti(int a){//çıktı burada alınır her tekrar yazdırılmasında değişen veriler otomatik güncellenip alt satırdan tekrar yazılır
    FILE *file; 
    file=fopen("output.txt","a");//dosya oluşturma ve açma
    fprintf(file,"%-18s - %21s\n","Etiket Listesi","Tekrar Sayisi");
    fprintf(file,"\n");
    int c=Global_counter_2;
    Global_counter_2=0;
    struct dizi gecici;
    gecici=etiketler;
    for (int i = 0; i <c; i++){
        for(int x=i+1; x<c;x++){
            int d=string_ara_2(etiketler.dizi[i],etiketler.dizi[x]);//eti,ketlerin aynı olanlarını silmek için kontrol işlemi yapılır
            if (d==1){
                int z=karakter_sayisi(etiketler.dizi[i]);
                int y=karakter_sayisi(etiketler.dizi[x]);
                if (y==z){//programlama_I ve programlama_II arasındaki farkı algılamak için kontorl işlemi yapılır
                    *etiketler.dizi[x]=NULL;//aynı olan etiketler silinir
                }
                        
            }
        }
    }
   
    for (int b = 0; b < c+10; b++){//toplam etiket sayısı bulunur
        if(*etiketler.dizi[b]!=NULL){//boş satırları atlamak için kontrol işlemi
            int x=string_ara_1(gecici,etiketler.dizi[b]);
            if (x!=0){
                fprintf(file,"%-35s %d\n",etiketler.dizi[b],x);//etiketi outputa yazma      
            }
        }
    }
    fclose(file);
    yetim_etiket_bulma(c);
}

int *string_ara_1(struct dizi ana_metin, char * aranan) {//çıktı fonksiyonu için yazılmış özel etiket eşleme ve sayı alma işlemi
    int j=0,b=0;
    int aranan_N = karakter_sayisi(aranan);

    for (int i = 0 ; i <= 40 ; i++) {
        if (ana_metin.dizi[i]!=NULL){
            int z=strcmp(ana_metin.dizi[i],aranan);
            if(z==0){
                b++;
            }
        }
    }
    return b;
}

void yetim_etiket_bulma(int a){//yetim etiketler bulunur ve output dosyasına yazılır
    FILE *file;
    file=fopen("output.txt","a");
    int h;
    fprintf(file,"\n%s\n","Yetim Etiketler:");
    for (int i = 0; i < a; i++){
        h=0;
        for(int j=0;j<a+2;j++) {
            if(*etiketler.dizi[i]==NULL){h++; break;}//silinen etiketlerin arasındaki boşluk giderme
            if(string_ara_2(Global_dosya_yolu.dizi[j], etiketler.dizi[i])) h++; //yetim olup olmama kontrolcüsü
        }
        if (h==0){
            fprintf(file,"%s\n",etiketler.dizi[i]);  
        }
    }
    fclose(file);
}

