//---- Datos del programa -----
//Nombre programa:
//Autor:
//Version:
//Descripcion:

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

//---- Variables -----
const int a = 1;
const int b = 2;
const int c = 3;
const int d = 4;
const int e = 5;
const int f = 6;
const int g = 7;

const int Act1 = 8;
const int Act2 = 9;

bool iniciar = true;

int valOrderCount = 0;
int Unidad = 0;
int Decena = 0;
int Regulador = 0;
int Numero = 0;
int Repetidor = 0;
int ControlRep = 10;  //Controlador de Repeticiones de Ciclo

void setup() {
  lcd.init();                     
  lcd.backlight();
  
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(Act1, OUTPUT);
  pinMode(Act2, OUTPUT);
}

void loop() {

  if(iniciar){
    lcd.setCursor(0, 0);
    lcd.print("Contador:00");
    iniciar = false;
    }
    
  Contador();

  if (Regulador == 0) {
    digitalWrite(Act1, LOW);
    digitalWrite(Act2, HIGH);
    Numero = Unidad;
    Regulador = 1;
  } else if (Regulador == 1) {
    digitalWrite(Act1, HIGH);
    digitalWrite(Act2, LOW);
    Numero = Decena;
    Regulador = 0;
  }

  Suiche(Numero);
}

void Suiche(int numero) {

  switch (numero) {
    case 0:
      NumCero();
      break;

    case 1:
      NumUno();
      break;

    case 2:
      NumDos();
      break;

    case 3:
      NumTres();
      break;

    case 4:
      NumCuatro();
      break;

    case 5:
      NumCinco();
      break;

    case 6:
      NumSeis();
      break;

    case 7:
      NumSiete();
      break;

    case 8:
      NumOcho();
      break;

    case 9:
      NumNueve();
      break;
  }

}

void Contador() {
  valOrderCount++;
  Repetidor++;
  lcd.setCursor(0, 1);
  lcd.print("Ciclo:");
  lcd.setCursor(6, 1);
  lcd.print(Repetidor);
  lcd.setCursor(10, 1);
  lcd.print("Max:");
  lcd.setCursor(14, 1);
  lcd.print(ControlRep);
  
  if (Repetidor == ControlRep) {
    Unidad = Unidad + 1;
    Repetidor = 0;
    if(Unidad >= 10){
      lcd.setCursor(10, 0);
      lcd.print(0);
      }else{ 
    lcd.setCursor(10, 0);
    lcd.print(Unidad);
      }
  }

  if (Unidad >= 10) {
    Unidad = 0;
    Decena = Decena + 1;
    lcd.setCursor(9, 0);
    lcd.print(Decena);
    if (Decena >= 10) {
      Decena = 0;
      if (valOrderCount >= (Repetidor * ControlRep)) {
        valOrderCount = 0;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Contador:00");
        
      }
    }
  }

}

// Funciones de los números
void NumCero() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void NumUno() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void NumDos() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void NumTres() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);

}

void NumCuatro() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void NumCinco() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void NumSeis() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void NumSiete() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void NumOcho() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void NumNueve() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
