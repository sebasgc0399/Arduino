//---- Datos del programa -----
//Nombre programa:
//Autor:
//Version:
//Descripcion:


//---- Variables -----
const int a = 1;
const int b = 2;
const int c = 3;
const int d = 4;
const int e = 5;
const int f = 6;
const int g = 7;
int Leds[] = {a, b, c, d, e, f, g};

const int BOTON1 = 13;
const int BOTON2 = 12;
int valOrderCount = 1;
bool iniciar = true;

int val1;
int val2;

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(BOTON1, INPUT);
  pinMode(BOTON2, INPUT);
}

void loop() {
  val1 = digitalRead(BOTON1);
  val2 = digitalRead(BOTON2);

  if (iniciar)
  {
    Reset();
    iniciar = false;
  }

  if (val1 == HIGH) {
    Suiche(valOrderCount);
    delay(1000);
    val1 = LOW;
    valOrderCount++;
  }

  if (val2 == HIGH) {
    Suiche(valOrderCount);
    delay(1000);
    val2 = LOW;
    valOrderCount--;
  }
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

void Reset() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(Leds[i], HIGH);
  }
}

// Funciones de los números
void NumCero() {
  Reset();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
}

void NumUno() {
  Reset();
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
}

void NumDos() {
  Reset();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(g, LOW);
  digitalWrite(e, LOW);
  digitalWrite(d, LOW);
}

void NumTres() {
  Reset();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(g, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
}

void NumCuatro() {
  Reset();
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
}

void NumCinco() {
  Reset();
  digitalWrite(a, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
}

void NumSeis() {
  Reset();
  digitalWrite(a, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(e, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
}

void NumSiete() {
  Reset();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
}

void NumOcho() {
  Reset();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void NumNueve() {
  Reset();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(c, LOW);
}
