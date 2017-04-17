/*

  Eren Keskin 
  Joystick Kontrollü Araç - Verici Kodları (Transmitter)
  Ayrıntılar: http://herenkeskin.com/arduino-nrf24l01-ile-joystick-kontrollu-araba
  17.04.2017
  
*/

// Gerekli olan kütüphaneler
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// RF Tanımlamaları
#define CE_PIN    9
#define CSN_PIN   10

RF24 verici(CE_PIN, CSN_PIN);

const byte koleAdrei[6] = {'R', 'x', 'E', 'r', 'e', 'n'};

// Joystick Tanımlamaları
const int joyYatay = 0;   // Analog 0
const int joyDikey = 1;   // Analog 1
const int joyButon = 2;

const int yukari = 3;
const int asagi = 5;
const int sag = 4;
const int sol = 6;
const int butonSol = 7;
const int butonSag = 8;

bool tamam;

// Kullanılacak Fonksiyonlar
void joystick();
void RFbaslat();

void setup() {

  Serial.begin(9600);
  joystick();
  RFbaslat();

  delay(1000);
  
}

void loop() {

  int joyYatayDeger = analogRead(joyYatay);
  int joyDikeyDeger = analogRead(joyDikey);
  int joyButonDeger = digitalRead(joyButon);

  int yukariDeger = digitalRead(yukari);
  int asagiDeger = digitalRead(asagi);
  int sagDeger = digitalRead(sag);
  int solDeger = digitalRead(sol);
  int butonSolDeger = digitalRead(butonSol);
  int butonSagDeger = digitalRead(butonSag);

  int veriler[10] = {joyYatayDeger, joyDikeyDeger, joyButonDeger, yukariDeger, asagiDeger, sagDeger, solDeger, butonSolDeger, butonSagDeger};

  tamam = verici.write( &veriler, sizeof(veriler) );

  Serial.print("Gonderilen Veri Islemleri: ");
  if (tamam) {
    Serial.println("Veriler Iletildi..");
    for (int i = 0; i < 10; i++) {
      Serial.println(veriler[i]);
    }
  }
  else {
    Serial.println(" Tx Hatasi");
  }
  delay(100);
  
}

// Joystick Modülümüz için tanımlamalarımızı yapıyoruz.
void joystick() {

  pinMode(joyYatay, INPUT);
  pinMode(joyDikey, INPUT);
  pinMode(joyButon, INPUT);
  pinMode(yukari, INPUT);
  pinMode(asagi, INPUT);
  pinMode(sag, INPUT);
  pinMode(sol, INPUT);
  pinMode(butonSol, INPUT);
  pinMode(butonSag, INPUT);

  Serial.println("##---------------##");
  Serial.println("Butonlar aktif.");
  Serial.println("##---------------##");

}

// RF Modülümüzü başlatıyoruz
void RFbaslat(){
  
  Serial.println("Haberlesme Baslatildi..");
  verici.begin();
  verici.setDataRate( RF24_250KBPS );
  verici.setRetries(3, 10);
  verici.openWritingPipe(koleAdrei);
  verici.stopListening();
    
}
