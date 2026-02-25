#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *kitapAdi;             
    char *yazar;               
    unsigned short int kategoriKodu; 
    float fiyat;                
    int basimYili;              
} Kitap;

typedef struct {
    char *kategoriAdi;         
    unsigned short int kategoriKodu; 
    Kitap *kategoriKitaplar;    
    int kitapSayisi;            
    int kapasite;              
} Kategori;


Kategori KategoriOlustur(char *ad, unsigned short kod);
Kitap KitapOlustur(char *ad, char *yazar, unsigned short kod, float fiyat, int yil);

void KitapEkle(Kategori *kategoriDizi, int kategoriSayisi, Kitap yeniKitap);

void KitapBilgileriniYazdir(Kitap *kitap);
void KategoriBilgileriniYazdir(Kategori *kategori);
void TumKategorileriYazdir(Kategori *kategoriDizi, int kategoriSayisi);

float FiyatOrtalamasiHesapla(Kategori *kategori);
void OrtalamaUstuKitaplariListele(Kategori *kategori);
void EnPahaliKitaplariYazdir(Kategori *kategoriDizi, int kategoriSayisi);
void EskiKitapFiyatGuncelle(Kategori *kategoriDizi, int kategoriSayisi, int yil, float yeniFiyat);

void DiziyiDosyayaYaz(Kategori *kategoriDizi, int kategoriSayisi);
void DosyadanDiziyeAktar(Kategori **kategoriDiziPtr, int *kategoriSayisiPtr);
void SerbestBirak(Kategori *kategoriDizisi,int kategoriSayisi);

