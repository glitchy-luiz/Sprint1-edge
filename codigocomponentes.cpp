#include <LiquidCrystal.h>

// Definição dos pinos do sensor ultrassônico
int trigger = 7;
int echo = 8;
float dist = 0;

// Definição dos pinos dos LEDs
int ledR = 13;
int ledY = 12;
int ledG = 11;

// Definição do pino do Piezo
int piezo = 10;  

// Definição dos pinos do LCD
#define D4 4
#define D5 5
#define D6 6
#define D7 3
#define E 2
#define RS 9

LiquidCrystal LCD(RS, E, D4, D5, D6, D7);

void setup() {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  
  Serial.begin(9600);

  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(piezo, OUTPUT);  
  
  LCD.begin(16, 2);
}

void loop() {

  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  dist = pulseIn(echo, HIGH);
  dist = dist / 58; 
  Serial.print("Distancia = ");
  Serial.print(dist);
  Serial.println("cm");
  
  if (dist <= 50) {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
    LCD.clear();
    LCD.print("PERIGO ALERTA");
    tone(piezo, 1000); 
  } else if (dist > 50 && dist < 200) {
  
    digitalWrite(ledY, HIGH);
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    LCD.clear();
    LCD.print("CUIDADO PROXIMO");
    tone(piezo, 500);  
  } else {
    digitalWrite(ledG, HIGH);
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    LCD.clear();
    LCD.print("AREA SEGURA");
    noTone(piezo); 
  }
  
  delay(500); 
}
