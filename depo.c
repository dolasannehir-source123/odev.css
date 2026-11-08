#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10 


typedef struct {
    int barkodNo;     
    char urunAdi[30];  
    int stokMiktari;  
} Urun;

Urun depo[TABLE_SIZE];
int durum[TABLE_SIZE]; 


void depolarıHazirla() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        durum[i] = 0;
    }
}


int hashFunc(int barkod) {
    return barkod % TABLE_SIZE;
}


void urunEkle(int barkod, const char* adi, int stok) {
    int hash = hashFunc(barkod);
    int i = 0;
    int index = hash;

    
    while(durum[index] == 1 && i < TABLE_SIZE) {
        i++;
        index = (hash + (i * i)) % TABLE_SIZE;
    }

    if(durum[index] == 1) {
        printf("HATA: Depo tamamen dolu, '%s' eklenemedi!\n", adi);
        return;
    }

    depo[index].barkodNo = barkod;
    strcpy(depo[index].urunAdi, adi);
    depo[index].stokMiktari = stok;
    durum[index] = 1;
    
    printf("Basariyla Eklendi -> Urun: %s | Barkod: %d | Depo Indeksi: %d\n", adi, barkod, index);
}


int urunAra(int barkod) {
    int hash = hashFunc(barkod);
    int i = 0;
    int index = hash;

    while(durum[index] != 0 && i < TABLE_SIZE) {
        if(durum[index] == 1 && depo[index].barkodNo == barkod) {
            return index; 
        }
        i++;
        index = (hash + (i * i)) % TABLE_SIZE;
    }
    return -1; 
}

int main() {
    depolarıHazirla();

    printf("=== KASTAMONU YORESEL URUN DEPO SISTEMI ===\n\n");

    
    urunEkle(101, "Taskopru Sarimsagi", 500);
    urunEkle(111, "Siyez Bulguru", 250); 
    urunEkle(105, "Eksi Mayali Ekler", 120);
    urunEkle(121, "Kastamonu Simidi", 400); 

    printf("\n--- URUN ARAMA TESTI ---\n");
    int arananBarkod = 111;
    int sonucIndeks = urunAra(arananBarkod);

    if(sonucIndeks != -1) {
        printf("Urun Bulundu!\n");
        printf("Adi: %s\n", depo[sonucIndeks].urunAdi);
        printf("Stok: %d adet\n", depo[sonucIndeks].stokMiktari);
        printf("Bulundugu Konum (Indeks): %d\n", sonucIndeks);
    } else {
        printf("Aradiginiz barkoda ait urun bulunamadi.\n");
    }

    return 0;
}