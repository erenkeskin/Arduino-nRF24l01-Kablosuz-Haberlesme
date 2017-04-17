/*

  Eren Keskin 
  Joystick Kontrollü Araç - Alıcı Kodları (Receiver)
  Ayrıntılar: http://herenkeskin.com/arduino-nrf24l01-ile-joystick-kontrollu-araba
  17.04.2017
  
*/

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
int sayac, durum = 0;

// Motor Tanımlamaları
#define motorSol1 A0          // Analog 0
#define motorSol2 A1          // Analog 1
#define motorSag1 A2          // Analog 2
#define motorSag2 A3          // Analog 3
const int motorSolPWM = 3;    // Digital 3
const int motorSagPWM = 5;    // Digital 3

// Kullanılacak Fonksiyonlar
void RFbaslat();
void motorAyarlari();

void setup() {

  Serial.begin(9600);
  motorAyarlari();
  RFbaslat();

  delay(1000);

}

void loop() {

  if ( alici.available() ) {
    alici.read( &alinanVeriler, sizeof(alinanVeriler) );
    alindi = true;

    if (alindi == true) {

      // Gelen verileri ekrana bastır
      Serial.println("Veriler Aliniyor..");
      for (int i = 0; i < 10; i++) {
        Serial.println(alinanVeriler[i]);
      }

      int x_ekseni = alinanVeriler[0];
      x_ekseni = map(x_ekseni, 0, 1023, 255, 0);
      int y_ekseni = alinanVeriler[1];
      y_ekseni = map(y_ekseni, 0, 1023, 255, 0);
      int mars = alinanVeriler[7];

      // Eğer 7 numaralı pine basildiysa aracı çalıştır
      if (mars != durum) {
        if (mars == HIGH) {
          sayac++;
        }
        delay(50);
      }
      durum = mars;

      if (sayac % 2 == 1) {
        analogWrite(motorSagPWM, x_ekseni);
        analogWrite(motorSolPWM, y_ekseni);
        Serial.println("Motorlara hiz verildi..");
      } else {
        analogWrite(motorSagPWM, 0);
        analogWrite(motorSolPWM, 0);
        Serial.println("Motorlar durduruldu..");
      }
      alindi = false;
    } else {
      analogWrite(motorSagPWM, 0);
      analogWrite(motorSolPWM, 0);
      Serial.println("Motorlar durduruldu..");
    }
    delay(100);
  } else {
    analogWrite(motorSagPWM, 0);
    analogWrite(motorSolPWM, 0);
    Serial.println("Motorlar durduruldu..");
  }

}

// RF Modülümüzü başlatıyoruz
void RFbaslat() {

  Serial.println("Haberlesme Baslatildi..");
  alici.begin();
  alici.setDataRate( RF24_250KBPS );
  alici.openReadingPipe(1, koleAdresi);
  alici.startListening();

}

void motorAyarlari() {

  pinMode(motorSol1, OUTPUT);
  pinMode(motorSol2, OUTPUT);
  pinMode(motorSag1, OUTPUT);
  pinMode(motorSag2, OUTPUT);
  pinMode(motorSolPWM, OUTPUT);
  pinMode(motorSagPWM, OUTPUT);

  digitalWrite(motorSol1, HIGH);
  digitalWrite(motorSol2, LOW);
  digitalWrite(motorSag1, HIGH);
  digitalWrite(motorSag2, LOW);

  analogWrite(motorSolPWM, 0);
  analogWrite(motorSagPWM, 0);

  Serial.println("##---------------##");
  Serial.println("Motor Ayarlari Yapildi.");
  Serial.println("##---------------##");

}
