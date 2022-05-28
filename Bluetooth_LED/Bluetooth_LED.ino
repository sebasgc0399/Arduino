#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); // RX, TX
// Connect HC-06      Arduino Uno
//     Pin 1/TXD          Pin 7
//     Pin 2/RXD          Pin 8

char myChar ;
#define LED1 13

void setup() {

  mySerial.begin(9600);
  mySerial.println("mySerial OPEN");
  pinMode(LED1, OUTPUT);

}

void loop() {

  if (mySerial.available()) {
    myChar = mySerial.read();

    switch (myChar) {

      case '1':
        digitalWrite(LED1, HIGH);
        break;

      case '0':
        digitalWrite(LED1, LOW);
        break;

      default:
        mySerial.println("Opcion invalida");
        break;

    }
  }
}
