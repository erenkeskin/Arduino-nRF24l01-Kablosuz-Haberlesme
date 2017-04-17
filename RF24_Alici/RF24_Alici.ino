// Gerekli olan kütüphaneler
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// RF Tanımlamaları
#define CE_PIN    8
#define CSN_PIN   7

const byte koleAdresi[6] = {'R', 'x', 'E', 'r', 'e', 'n'};

RF24 alici(CE_PIN, CSN_PIN);

// Veri İslemleri
int alinanVeriler[10];
bool alindi = false;

// Kullanılacak Fonksiyonlar
void RFbaslat();

void setup() {

  Serial.begin(9600);
  RFbaslat();

  delay(1000);

}

void loop() {

  // Alıcı ayarları çalışıyorsa
  if ( alici.available() ) {  

    // Verileri Oku
    alici.read( &alinanVeriler, sizeof(alinanVeriler) );
    alindi = true;

    // Eğer veri alma işlemi tamamlandıysa
    if (alindi == true) {

      // Verileri ekrana bastir
      Serial.println("Veriler Aliniyor..");
      for (int i = 0; i < 10; i++) {
        Serial.println(alinanVeriler[i]);
      }
      alindi = false;
      
    }
    delay(100);
  }
  
}

// RF Modülümüzü başlatıyoruz
void RFbaslat(){
  
  Serial.println("Haberlesme Baslatildi..");
  alici.begin();                        // Modül başlatıldı
  alici.setDataRate( RF24_250KBPS );    // Veri akış oranı belirlendi
  alici.openReadingPipe(1, koleAdresi); // Alıcı modülü olduğu için parametreler ona göre ayarlandı
  alici.startListening();               // Haberleşmeyi dinlemeye başladı
    
}
