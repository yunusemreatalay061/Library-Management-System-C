/**
Yunus Emre ATALAY 2321021030
Fatih Sultan Mehmet Vakıf Üniversitesi 2. Sınıf Güz Dönemi Projesi
*/

#include "proje.h"

int main() {
    Kategori *kategoriDizisi = NULL;
    int kategoriSayisi = 0;

    printf("--- VERI OKUMA ---\n");
    DosyadanDiziyeAktar(&kategoriDizisi, &kategoriSayisi);

    if (kategoriSayisi == 0) {
        printf("Veri yok, varsayilan test verileri olusturuluyor...\n");
        kategoriDizisi = (Kategori*)realloc(kategoriDizisi, sizeof(Kategori) * 3);
        kategoriDizisi[0] = KategoriOlustur("Roman", 101);
        kategoriDizisi[1] = KategoriOlustur("Tarih", 102);
        kategoriDizisi[2] = KategoriOlustur("Matematik", 103);
        kategoriSayisi = 3;

        Kitap k1 = KitapOlustur("Uzun Hikaye", "Mustafa Kutlu", 101, 250.00, 1987);
        Kitap k2 = KitapOlustur("Toprak Ana", "Cengiz Aytmatov", 101, 180.00, 1951);
        Kitap k3 = KitapOlustur("Nutuk", "Mustafa Kemal Ataturk", 102, 1923.00, 1927);
        Kitap k4 = KitapOlustur("Calculus", "James Stewart", 103, 350.00, 1947);

        KitapEkle(kategoriDizisi, kategoriSayisi, k1);
        KitapEkle(kategoriDizisi, kategoriSayisi, k2);
        KitapEkle(kategoriDizisi, kategoriSayisi, k3);
        KitapEkle(kategoriDizisi, kategoriSayisi, k4);
    }
                                                        
    TumKategorileriYazdir(kategoriDizisi, kategoriSayisi);
    
    EnPahaliKitaplariYazdir(kategoriDizisi, kategoriSayisi);
    
    OrtalamaUstuKitaplariListele(&kategoriDizisi[0]);

    EskiKitapFiyatGuncelle(kategoriDizisi, kategoriSayisi, 1960, 50.00);
    
    printf("\n--- GUNCELLEME SONRASI KONTROL ---\n");
    TumKategorileriYazdir(kategoriDizisi, kategoriSayisi);

    printf("\n--- CIKIS VE KAYIT ---\n");
    DiziyiDosyayaYaz(kategoriDizisi, kategoriSayisi);
    SerbestBirak(kategoriDizisi,kategoriSayisi);

    return 0;
}