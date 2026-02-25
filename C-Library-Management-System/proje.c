#include "proje.h"
// YARDIMCI FONKSIYON: Gelen metni dinamik bellekte (Heap) kopyalar.
char* metinKopyala(const char* kaynak) {
    if (kaynak == NULL) return NULL;
    char* yeni = (char*)malloc(strlen(kaynak) + 1);
    if (yeni) strcpy(yeni, kaynak);
    return yeni;
}
// Yeni bir kategori struct'i hazirlar, baslangic kapasitesini belirler ve bos dizi olusturur.
Kategori KategoriOlustur(char *ad, unsigned short kod) {
    Kategori k;
    k.kategoriAdi = metinKopyala(ad); 
    k.kategoriKodu = kod;
    k.kitapSayisi = 0;
    k.kapasite = 2; 
    k.kategoriKitaplar = (Kitap*)malloc(sizeof(Kitap) * k.kapasite); 
    return k;
}
// Verilen bilgilerle bir Kitap struct'i olusturur ve metin alanlarini dinamik kopyalar.
Kitap KitapOlustur(char *ad, char *yazar, unsigned short kod, float fiyat, int yil) {
    Kitap k;
    k.kitapAdi = metinKopyala(ad);
    k.yazar = metinKopyala(yazar);
    k.kategoriKodu = kod;
    k.fiyat = fiyat;
    k.basimYili = yil;
    return k;
}
// Kitabi ilgili kategoriye ekler. Eger dizi dolduysa kapasiteyi 2 katina cikarir.
void KitapEkle(Kategori *kategoriDizi, int kategoriSayisi, Kitap yeniKitap) {
    int index = -1;
    for (int i = 0; i < kategoriSayisi; i++) {
        if (kategoriDizi[i].kategoriKodu == yeniKitap.kategoriKodu) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        Kategori *kat = &kategoriDizi[index];
        if (kat->kitapSayisi >= kat->kapasite) {
            kat->kapasite *= 2; 
            Kitap *temp = (Kitap*)realloc(kat->kategoriKitaplar, sizeof(Kitap) * kat->kapasite);
            if (temp != NULL) {
                kat->kategoriKitaplar = temp;
                printf(">> %s kategorisi icin kapasite artirildi. Yeni kapasite: %d\n", kat->kategoriAdi, kat->kapasite);
            } else {
                printf("Bellek hatasi (realloc)!\n");
                return;
            }
        }
        kat->kategoriKitaplar[kat->kitapSayisi] = yeniKitap;
        kat->kitapSayisi++;
    } else {
        printf("Hata: %d kodlu kategori bulunamadi, kitap eklenemedi!\n", yeniKitap.kategoriKodu);
        free(yeniKitap.kitapAdi);
        free(yeniKitap.yazar);
    }
}
//Kitabi yazdiriyor.
void KitapBilgileriniYazdir(Kitap *kitap) {
    if (kitap) {
        printf("   - Kitap: %-30s | Yazar: %-20s | Fiyat: %.2f | Yil: %d\n", 
               kitap->kitapAdi, kitap->yazar, kitap->fiyat, kitap->basimYili);
    }
}
//Katagoriyi yazdiriyor.
void KategoriBilgileriniYazdir(Kategori *kategori) {
    if (kategori) {
        printf("ID: %d | Kategori: %s | Kitap Sayisi: %d\n", 
               kategori->kategoriKodu, kategori->kategoriAdi, kategori->kitapSayisi);
    }
}
//Tüm dosyayı basiyor.
void TumKategorileriYazdir(Kategori *kategoriDizi, int kategoriSayisi) {
    printf("\n--- TUM LISTE ---\n");
    for (int i = 0; i < kategoriSayisi; i++) {
        KategoriBilgileriniYazdir(&kategoriDizi[i]);
        for (int j = 0; j < kategoriDizi[i].kitapSayisi; j++) {
            KitapBilgileriniYazdir(&kategoriDizi[i].kategoriKitaplar[j]);
        }
        printf("-----------------\n");
    }
}
//Girilen kategorinin ortalamasini hesapla.
float FiyatOrtalamasiHesapla(Kategori *kategori) {
    if (kategori->kitapSayisi == 0) return 0.0;
    float toplam = 0;
    for (int i = 0; i < kategori->kitapSayisi; i++) {
        toplam += kategori->kategoriKitaplar[i].fiyat;
    }
    return toplam / kategori->kitapSayisi;
}
//Girilen kategorinin ortalama ustu kitaplarini listele.
void OrtalamaUstuKitaplariListele(Kategori *kategori) {
    float ortalama = FiyatOrtalamasiHesapla(kategori);
    printf("\n'%s' Kategorisi (Ortalama Fiyat: %.2f) uzerindeki kitaplar:\n", kategori->kategoriAdi, ortalama);
    for (int i = 0; i < kategori->kitapSayisi; i++) {
        if (kategori->kategoriKitaplar[i].fiyat > ortalama) {
            KitapBilgileriniYazdir(&kategori->kategoriKitaplar[i]);
        }
    }
}
//En pahalisini hesapla.
void EnPahaliKitaplariYazdir(Kategori *kategoriDizi, int kategoriSayisi) {
    printf("\n--- KATEGORILERIN EN PAHALI KITAPLARI ---\n");
    for (int i = 0; i < kategoriSayisi; i++) {
        Kategori *kat = &kategoriDizi[i];
        if (kat->kitapSayisi > 0) {
            int maxIndex = 0;
            for (int j = 1; j < kat->kitapSayisi; j++) {
                if (kat->kategoriKitaplar[j].fiyat > kat->kategoriKitaplar[maxIndex].fiyat) {
                    maxIndex = j;
                }
            }
            printf("%s: %s (%.2f TL)\n", kat->kategoriAdi, 
                   kat->kategoriKitaplar[maxIndex].kitapAdi, kat->kategoriKitaplar[maxIndex].fiyat);
        } else {
            printf("%s: Kitap yok.\n", kat->kategoriAdi);
        }
    }
}
//Eski kitaplarin fiyatini guncelle.
void EskiKitapFiyatGuncelle(Kategori *kategoriDizi, int kategoriSayisi, int yil, float yeniFiyat) {
    int guncellenenSayisi = 0;
    for (int i = 0; i < kategoriSayisi; i++) {
        for (int j = 0; j < kategoriDizi[i].kitapSayisi; j++) {
            if (kategoriDizi[i].kategoriKitaplar[j].basimYili < yil) {
                kategoriDizi[i].kategoriKitaplar[j].fiyat = yeniFiyat;
                guncellenenSayisi++;
            }
        }
    }
    printf("\n%d yilindan eski %d kitabin fiyati %.2f olarak guncellendi.\n", yil, guncellenenSayisi, yeniFiyat);
}
//Dosyaya gecir.
void DiziyiDosyayaYaz(Kategori *kategoriDizi, int kategoriSayisi) {
    FILE *fpKat = fopen("kategoriler.txt", "w");
    FILE *fpKit = fopen("kitaplar.txt", "w");

    if (!fpKat || !fpKit) {
        printf("Dosya yazma hatasi!\n");
        return;
    }

    for (int i = 0; i < kategoriSayisi; i++) {
        fprintf(fpKat, "%d|%s\n", kategoriDizi[i].kategoriKodu, kategoriDizi[i].kategoriAdi);
        
        for (int j = 0; j < kategoriDizi[i].kitapSayisi; j++) {
            Kitap *k = &kategoriDizi[i].kategoriKitaplar[j];
            fprintf(fpKit, "%d|%s|%s|%.2f|%d\n", 
                    k->kategoriKodu, k->kitapAdi, k->yazar, k->fiyat, k->basimYili);
        }
    }

    fclose(fpKat);
    fclose(fpKit);
    printf("Veriler dosyalara basariyla kaydedildi.\n");
}
//Dosyadan gecir.
void DosyadanDiziyeAktar(Kategori **kategoriDiziPtr, int *kategoriSayisiPtr) {
    FILE *fpKat = fopen("kategoriler.txt", "r");
    FILE *fpKit = fopen("kitaplar.txt", "r");

    if (!fpKat) {
        printf("Kayitli veri bulunamadi (kategoriler.txt yok). Bos baslaniyor.\n");
        *kategoriDiziPtr = NULL;
        *kategoriSayisiPtr = 0;
        return;
    }

    char satir[200];
    int count = 0;
    Kategori *dizi = NULL;

    
    while (fgets(satir, sizeof(satir), fpKat)) {
        unsigned short kod = 0;  
        char ad[50] = "";        
        
        
        satir[strcspn(satir, "\n")] = 0;
        
        // Format: ID|Ad
        char *token = strtok(satir, "|");
        if(token) kod = atoi(token);
        
        token = strtok(NULL, "|");
        if(token) strcpy(ad, token);

        dizi = (Kategori*)realloc(dizi, sizeof(Kategori) * (count + 1));
        dizi[count] = KategoriOlustur(ad, kod);
        count++;
    }
    fclose(fpKat);

    *kategoriDiziPtr = dizi;
    *kategoriSayisiPtr = count;

    if (!fpKit) return; 

    while (fgets(satir, sizeof(satir), fpKit)) {
        satir[strcspn(satir, "\n")] = 0;
        
        // Format: ID|Ad|Yazar|Fiyat|Yil
        unsigned short catId;
        char kAd[50], yazar[50];
        float fiyat;
        int yil;

        char *token = strtok(satir, "|");
        if(!token) continue; catId = atoi(token);
        
        token = strtok(NULL, "|");
        if(!token) continue; strcpy(kAd, token);
        
        token = strtok(NULL, "|");
        if(!token) continue; strcpy(yazar, token);
        
        token = strtok(NULL, "|");
        if(!token) continue; fiyat = atof(token);
        
        token = strtok(NULL, "|");
        if(!token) continue; yil = atoi(token);

        Kitap yeniKitap = KitapOlustur(kAd, yazar, catId, fiyat, yil);
        KitapEkle(*kategoriDiziPtr, *kategoriSayisiPtr, yeniKitap);
    }
    fclose(fpKit);
    printf("Dosyalardan veri okuma tamamlandi. %d kategori yuklendi.\n", count);
}
//Tun bellekleri birak.
void SerbestBirak(Kategori *kategoriDizisi,int kategoriSayisi){
for (int i = 0; i < kategoriSayisi; i++) {
        for (int j = 0; j < kategoriDizisi[i].kitapSayisi; j++) {
            free(kategoriDizisi[i].kategoriKitaplar[j].kitapAdi);
            free(kategoriDizisi[i].kategoriKitaplar[j].yazar);
        }
        free(kategoriDizisi[i].kategoriKitaplar);
        
        free(kategoriDizisi[i].kategoriAdi);
    }
    free(kategoriDizisi);
    printf("Bellek temizlendi. Program kapaniyor.\n");
}