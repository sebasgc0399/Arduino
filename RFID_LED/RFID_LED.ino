//Incluir Librerias del RFID
#include <SPI.h>                  // incluye libreria bus SPI
#include <MFRC522.h>              // incluye libreria especifica para MFRC522

//Instanciar variables para los pines del RFID
#define RST_PIN 9              // constante para referenciar pin de reset
#define SS_PIN 10              // constante para referenciar pin de slave select


// Creamos un array para almacenar el UID leido
byte LecturaUID[4];
byte Usuario1[4] = {0xA1, 0x67, 0x45, 0x1B} ;   // UID de tarjeta leido Tarjeta

boolean Control = true;

const int led = 8;

// Crear Objecto para el RFID (Slave Select, Reset)
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:

  // Setup RFID
  Serial.begin(9600);                                 // inicializa comunicacion por monitor serie a 9600 bps
  SPI.begin();                                        // inicializa bus SPI
  mfrc522.PCD_Init(); //Inicializamos el Modulo RFID  // inicializa modulo lector

  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Loop Inicial del RFID
  if ( ! mfrc522.PICC_IsNewCardPresent())   // si no hay una tarjeta presente
    return;                                 // retorna al loop esperando por una tarjeta

  if ( ! mfrc522.PICC_ReadCardSerial())     // si no puede obtener datos de la tarjeta
    return;

  //Almacenar el UID
  for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID
          LecturaUID[i]=mfrc522.uid.uidByte[i];     // almacena en array el byte del UID leido      
          }

          
//Comparar UID
    if (comparaUID(LecturaUID, Usuario1)) { // llama a funcion comparaUID con Usuario1
      Serial.println("Comparando1");

      if(Control == true){
        digitalWrite(led, HIGH);
        Control = false;
        }else if (Control == false){
          digitalWrite(led, LOW);
        Control = true;
          }
          
      mfrc522.PICC_HaltA();
    }

}
 boolean comparaUID(byte lectura[],byte usuario[]) // funcion comparaUID
{
  for (byte i=0; i < mfrc522.uid.size; i++){    // bucle recorre de a un byte por vez el UID
  if(lectura[i] != usuario[i])        // si byte de UID leido es distinto a usuario
    return(false);          // retorna falso
  }
  return(true);           // si los 4 bytes coinciden retorna verdadero
}
