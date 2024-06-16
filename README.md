<p align="center">
 <h1 align="center">E-Race Security</h1>
 <p align="center">O software de segurança exclusiva da Formula E</p>
</p>

## Introdução
Este projeto é um protótipo de um dispositivo de segurança da formula E, que tem como objetivo avisar os corredores caso tenha algum carro perigosamente perto deles
> Nota
> Nós utilizamos a biblioteca LiquidCrystal para o uso da tela LCD

## 1- Componentes iniciais:
Uma simulação do dispositivo foi feita no tinkercad pelo link: https://www.tinkercad.com/things/hpI5TdBSuch-sprint-1-edge?sharecode=ZoJzKEn2bqfH015mpk39YpvMtcMHJYzMl53APc7m-_k
Lá fizemos uso de diversos componentes, sendo eles:

- Tela LCD
- Buzzer
- Sensor de distância ultrassônico
- Potenciometro
- 3 Leds (cores diferentes)
- Arduino, jumpers e resistores

![image](https://github.com/glitchy-luiz/readme-da-sprint-edge/assets/84513178/3c7dc51d-e1ab-4744-a2fa-adc1a25eac37)

## 2- Código fonte
Nossa primeira tarefa no código é chamar a biblioteca do lcd, e declarar as variaveis dos pinos utilizados
```md
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

```

Após isso começamos o nosso void setup, no qual comparamos cada váriavel (referente a um componente) com seu pinmode, no caso, 'entrada' ou 'saida'. Além disso, também inicamos a tela Serial

```md
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
```

Agora no nosso void loop, nós iniciamos o sensor ultrassônico para emitir os sinais para serem captados, e usamos estes mesmos sinais para conseguirmos calcular a distâcia e a guardamos em uma váriavel, e a mostramos no serial

```md

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
```

A ultima etapa do código é fazer as verificações da distancias para analisarmos o nivel de perigo. Caso a distancia seja maior que 200, a area está segura, caso ela seja menor que 200 e maior que 50, a area está com perigo próximo, e caso a distância seja menor de 50, entra em perigo de alerta.
Em cada um desses casos, o perigo será mostrado ao corredor pela cor do led acesso, e pelo lcd para uma informação por extenso

```md
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
```

## 3- Finalização
Assim passamos por cima da principais partes do código e componentes do nosso protótipo, e esperamos atualiza-lo para termos mais precisão e informações ao usuário

INTEGRANTES:
- Luiz Fernando Souza RM: 555561
- Bruno Otavio RM:556196
- Guilherme Palhari  RM: 557073​
- Guilherme Flores  RM: 554948​
- Adolfo Kentaro  RM: 556884
