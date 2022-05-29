//---- Datos del programa -----
//Nombre programa: Code Lock
//Autor: Sebastian Gutierrez Clavijo
//Version: 1.2
//Descripcion: Desarrollar un Code Lock para una puerta que pueda desbloquearse con un Keypad y por RFID.

/*  Actualmente en Desarrollo:
    Arduino
    Matrix Keypad 4X4
    LCD Display
    Rele 5v
    RFID
    Modulo de Wifi (Puede ser )
    Pin (8)Rele
    Pin (13,12,11,10,9) RFID
    Pines(7-0)y(14(1),15(0))Keypad
*/

//Incluir Librerias del RFID
#include <SPI.h>                  // incluye libreria bus SPI
#include <MFRC522.h>              // incluye libreria especifica para MFRC522

//Incluir Libreria del Arduino para I2C (Protocolo comunicacion)
#include <Wire.h>

//Incluir Libreria de la pantalla LCD para I2C (Protocolo comunicacion)
#include <LiquidCrystal_I2C.h>

//Incluir libreria Keypad
#include <Key.h>
#include <Keypad.h>

//Instanciar variables para los pines del RFID
#define RST_PIN 9               // constante para referenciar pin de reset
#define SS_PIN 10                 // constante para referenciar pin de slave select

//Longitud de la contraseña +1 por caracter nulo
#define Password_Length 7

// Caracter para capturar la contraseña comun
char Data[Password_Length];
// Caracter para capturar la contraseña Master
char Data2[Password_Length];
// Contraseña comun
char Master[Password_Length] = "000000";  //Revisar como retornar dato
// Contraseña Master
char MasterKey[Password_Length] = "*A3D0#";

//Controlador de Cambio de Contraseña
boolean Change = false;

// Pin conectado a la entrada del relé del bloqueo
int lockOutput = 8;
const int led = 8;
// Contador de caracteres presionados
byte data_count = 0;
// Caracter que presiona la tecla especifica del Keypad
char customKey;

// Creamos un array para almacenar el UID leido
byte LecturaUID[4];
byte Usuario1[4] = {0xA1, 0x67, 0x45, 0x1B} ;   // UID de tarjeta leido Tarjeta Homero  0x es para decir que es Hexadecimal
byte Usuario2[4] = {0x9D, 0x98, 0x78, 0x59} ;   // UID de llavero leido Tarjeta Bart  0x es para decir que es Hexadecimal

//Tamaño de las filas y columnas
const byte ROWS = 4;
const byte COLS = 4;

//Un Array que representa los botones del Keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//Conectores al Arduino-Keypad
byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 14, 15};

// Crear Objecto del Keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Crear Objecto del LCD (Tipo de Pantalla,Tamaño 16x2)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Crear Objecto para el RFID (Slave Select, Reset)
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {

  // Setup RFID
  Serial.begin(9600);                                 // inicializa comunicacion por monitor serie a 9600 bps
  SPI.begin();                                        // inicializa bus SPI
  mfrc522.PCD_Init(); //Inicializamos el Modulo RFID  // inicializa modulo lector

  // Setup de LCD
  lcd.backlight();
  lcd.init();

  // Colocamos el Pin lockOutput(13)en OUTPUT para el Rele
  pinMode(lockOutput, OUTPUT);
  //pinMode(led, OUTPUT);
}

void loop() {

  digitalWrite(lockOutput, HIGH);

  // Inicializamos LCD y muestre
  lcd.setCursor(0, 0);
  if (Change == true) {
    lcd.print("New Password:");  //Solicitamos nueva contraseña comun
  char customKey2 = customKeypad.getKey();
  if (customKey2) {
      //Ingresamos las teclas presionadas en el Array y incrementamos el contador
      Data2[data_count] = customKey2;
      lcd.setCursor(data_count, 1); //Escribimos en la 2 linea del LCD
      lcd.print(Data2[data_count]); //para escribir en el LCD
      data_count++; // para cada vez que presionemos una tecla no se borre la anterior
      for (int i = 0; i <= 6; i++) {
        Master[i] = Data2[i];   //Cambiamos contraseña comun
      }
  }
      if(data_count >= 6){
        Change = false;
        //memset(Data, 0, sizeof Data);
        data_count = 0;
        lcd.clear();
        }
  } else if (Change == false){
    lcd.print("Enter Password:");
  }

  // Resivamos las pulsaciones de las teclas
  char customKey = customKeypad.getKey();
  if (customKey) {
    //Ingresamos las teclas presionadas en el Array y incrementamos el contador
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1); //Escribimos en la 2 linea del LCD
    lcd.print(Data[data_count]); //para escribir en el LCD
    delay(500);
    lcd.setCursor(data_count, 1); //Para ocultar luego de 0,5 segundo
    lcd.print("*");
    data_count++; // para cada vez que presionemos una tecla no se borre la anterior
  }

  // Revisamos si hemos alcanzado la longitud maxima de la contraseña y luego validarla
  if (data_count == Password_Length - 1) {
    lcd.clear();


    //!strcmp para comparar cadenas (Datos Ingresados, Contraseña)
    if (!strcmp(Data, MasterKey)) {
      //Contraseña Maestra
      lcd.print("Correct");
      delay(1000);
      lcd.clear();
      clearData();
      Change = true;
      data_count = 0;
    }
    else if (!strcmp(Data, Master)) {
      //Contraseña Correcta
      lcd.print("Correct");
      // Encendemos el Rele por 5 segundos
      Rele();
    } else {
      //Contraseña Incorrecta
      lcd.print("Incorrect");
      delay(1000);
    }

    //Limpiar la Data y la pantalla LCD
    lcd.clear();
    clearData();
  }

  //Loop Inicial del RFID
  if ( ! mfrc522.PICC_IsNewCardPresent())   // si no hay una tarjeta presente
    return;                                 // retorna al loop esperando por una tarjeta

  if ( ! mfrc522.PICC_ReadCardSerial())     // si no puede obtener datos de la tarjeta
    return;                                 // retorna al loop esperando por otra tarjeta

  //Almacenar el UID
  for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID
    LecturaUID[i] = mfrc522.uid.uidByte[i];   // almacena en array el byte del UID leido
  }

  //Comparar UID
  if (comparaUID(LecturaUID, Usuario1)) { // llama a funcion comparaUID con Usuario1
    lcd.clear();
    // Encendemos el Rele por 5 segundos
        lcd.setCursor(0, 0);
    lcd.print("Bienvenido");
    lcd.setCursor(0, 1);
    lcd.print("Sebastian");
    Rele();
    lcd.clear();      //Limpiar la pantalla LCD
  }
  else if (comparaUID(LecturaUID, Usuario2)) { // llama a funcion comparaUID con Usuario2
    lcd.clear();
    // Encendemos el Rele por 5 segundos
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bienvenido");
    lcd.setCursor(0, 1);
    lcd.print("Usuario2");

    Rele();
    lcd.clear();
  }
  else {          // si retorna falso
    lcd.print("No te conozco");    // muestra texto equivalente a acceso denegado
    delay(1000);

    lcd.clear();      //Limpiar la pantalla LCD

  }
  mfrc522.PICC_HaltA();     // detiene comunicacion con tarjeta
}

void clearData() {
  // Ir al Array borrar los datos
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}

boolean comparaUID(byte lectura[], byte usuario[]) // funcion comparaUID
{
  for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID
    if (lectura[i] != usuario[i])       // si byte de UID leido es distinto a usuario
      return (false);         // retorna falso
  }
  return (true);          // si los 4 bytes coinciden retorna verdadero
}

void Rele() {
  digitalWrite(lockOutput, LOW);
  delay(5000);
  digitalWrite(lockOutput, HIGH);
  return;
}
