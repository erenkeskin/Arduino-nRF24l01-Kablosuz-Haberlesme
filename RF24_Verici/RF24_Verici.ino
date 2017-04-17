// Gerekli olan kütüphaneler
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// RF Tanımlamaları
#define CE_PIN    9
#define CSN_PIN   10

RF24 verici(CE_PIN, CSN_PIN);

const byte koleAdrei[6] = {'R', 'x', 'E', 'r', 'e', 'n'};

bool tamam;
int i, veriler[10];

// Kullanılacak Fonksiyonlar
void RFbaslat();

void setup() {

  Serial.begin(9600);
  RFbaslat();

  delay(1000);
  
}

void loop() {

  // Gonderilecek veri dizisini oluştur
  for (i = 0; i < 10; i++) {
    veriler[i] = i;
  }

  // Veri gonderme işlemini yap ve bir değişkene ata
  tamam = verici.write( &veriler, sizeof(veriler) );

  Serial.print("Gonderilen Veri Islemleri: ");

  // Eğer veriler gonderildiyse
  if (tamam) {

    // Giden verileri ekrana bastir
    Serial.println("Veriler Iletildi..");
    for (i = 0; i < 10; i++) {
      Serial.println(veriler[i]);
    }
    
  }
  else {
    Serial.println(" Tx Hatasi");     // Gonderilemediyse hata ver.
  }
  delay(100);
  
}

// RF Modülümüzü başlatıyoruz
void RFbaslat(){
  
  Serial.println("Haberlesme Baslatildi..");
  verici.begin();                       // Modül başlatıldı
  verici.setDataRate( RF24_250KBPS );   // Veri akış oranı belirlendi
  verici.setRetries(3, 10);             // Tek seferde aktarılacak saı belirlendi (delay, count) parametreleri ile
  verici.openWritingPipe(koleAdrei);    // Haberleşme kanalının adresi verildi
  verici.stopListening();               // Veri gönderdiği için veri alışını kesti
  
}
