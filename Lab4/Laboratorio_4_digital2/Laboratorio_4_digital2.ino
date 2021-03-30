//Larry Paúl Fuentes 
//carné 18117
//Laboratorio 4
//22/03/2021

// Se utilizo de referecnia el codigo de ejemplo debounce de energia, para el antirebote de los switch 1 y 2 . 
#include "wiring_private.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"


//Variables Pines
const int buttonPin = 31;
const int buttonPin2 = 17;     // the number of the pushbutton pin
#define verde  GREEN_LED   // the number of the LED pin
#define rojo RED_LED
#define azul BLUE_LED

//Variables jugador 1
const int J1_1 = 2;
const int J1_2 = 3;
const int J1_3 = 4;
const int J1_4 = 5;
const int J1_5 = 6;
const int J1_6 = 7;
const int J1_7 = 8;
const int J1_8 = 9;
int J1_Contador = 0;

//Variables jugador 2
const int J2_1 = 11;
const int J2_2 = 12;
const int J2_3 = 13;
const int J2_4 = 33;
const int J2_5 = 34;
const int J2_6 = 35;
const int J2_7 = 36;
const int J2_8 = 37;
int J2_Contador = 0;

// Estados
int ledState = HIGH;         // the current state of the output pin
int ledState2 = HIGH;
int buttonState;             // the current reading from the input pin
int buttonState2;
int pressState = LOW;
int semaforoState = LOW;
int J1_win = LOW;
int J2_win = LOW;



//Variables Tiempo Debounce
long lastDebounceTime = 0;  // the last time the output pin was toggled
long lastDebounceTime2 = 0;
long debounceDelay = 100;    // the debounce time; increase if the output flickers


void setup() {
  // Inicializo mi pines
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(verde, OUTPUT);
  pinMode(rojo, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(J1_1, OUTPUT);
  pinMode(J1_2, OUTPUT);
  pinMode(J1_3, OUTPUT);
  pinMode(J1_4, OUTPUT);
  pinMode(J1_5, OUTPUT);
  pinMode(J1_6, OUTPUT);
  pinMode(J1_7, OUTPUT);
  pinMode(J1_8, OUTPUT);
  pinMode(J2_1, OUTPUT);
  pinMode(J2_2, OUTPUT);
  pinMode(J2_3, OUTPUT);
  pinMode(J2_4, OUTPUT);
  pinMode(J2_5, OUTPUT);
  pinMode(J2_6, OUTPUT);
  pinMode(J2_7, OUTPUT);
  pinMode(J2_8, OUTPUT);  
  //attachInterrupt(digitalPinToInterrupt(buttonPin), SemaforoCheck, FALLING);
  //attachInterrupt(digitalPinToInterrupt(buttonPin2), SemaforoCheck, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPin), cuenta1, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPin2), cuenta2, FALLING);
  Serial.begin(9600);
 
}

void semaforo () {
  digitalWrite(rojo, HIGH); //Pone en rojo 
  delay(500);
  digitalWrite(rojo, LOW); //Pone en rojo 
  delay(100);
  digitalWrite(rojo, HIGH);
  digitalWrite(verde, HIGH); //Esta combinacion en rgb crea el color amarillo
  delay(500);
  digitalWrite(rojo, LOW); //Pone en rojo 
  digitalWrite(verde, LOW);
  delay(100);
  digitalWrite(rojo, LOW);
  digitalWrite(verde, HIGH); //Pone en verde
  delay(500);
  digitalWrite(verde, LOW); // Termina secuencia
}

void loop() {
  //Serial.println(J1_Contador);
  if(J1_win == 0 and J2_win == 0){
    J1_state();
    J2_state();
    Fin();
  }
  
  }
  
void cuenta1(){
  if (semaforoState == HIGH and J1_win == LOW){
    J1_Contador++;
  }
  SemaforoCheck();
}

void cuenta2(){
  if (semaforoState == HIGH and J2_win == LOW){
    J2_Contador++;
  }
  SemaforoCheck();
}

void Fin(){ //Gana jugador 1, color morado
  if (J1_Contador > 8){
    J1_win == 1;
    digitalWrite(rojo, LOW);
    digitalWrite(verde,LOW); //Morado
    digitalWrite(azul, HIGH);
    delay(2500);
    reseteo();
  }
  else if(J2_Contador > 8){ //Gana jugador 2, color naranja
    J2_win == 1;
    digitalWrite(rojo, HIGH);
    digitalWrite(verde, HIGH); //Naranja
    digitalWrite(azul, LOW);
    delay(2500);
    reseteo();
  }
}

void reseteo(){
    digitalWrite(J1_1, LOW);
    digitalWrite(J1_2, LOW);
    digitalWrite(J1_3, LOW);
    digitalWrite(J1_4, LOW);
    digitalWrite(J1_5, LOW);
    digitalWrite(J1_6, LOW);
    digitalWrite(J1_7, LOW);
    digitalWrite(J1_8, LOW);

    digitalWrite(J2_1, LOW);
    digitalWrite(J2_2, LOW);
    digitalWrite(J2_3, LOW);
    digitalWrite(J2_4, LOW);
    digitalWrite(J2_5, LOW);
    digitalWrite(J2_6, LOW);
    digitalWrite(J2_7, LOW);
    digitalWrite(J2_8, LOW);
    J1_Contador = 0;
    J2_Contador = 0;
    digitalWrite(rojo, LOW);
    digitalWrite(verde, LOW); //Naranja
    digitalWrite(azul, LOW);
    semaforoState = LOW;
}

void SemaforoCheck(){
  if (semaforoState == LOW){
    //Si no ha iniciado lo que hara será empezar la secuencia de semaforo
    semaforo(); 
    semaforoState = HIGH;
  }
}
void J1_state(){
  if (J1_Contador == 1){
     digitalWrite(J1_1, HIGH);
  }
  else if (J1_Contador == 2){
    digitalWrite(J1_1, LOW);
    digitalWrite(J1_2, HIGH);
  }
  else if (J1_Contador == 3){
    digitalWrite(J1_2, LOW);
    digitalWrite(J1_3, HIGH);
  }
  else if (J1_Contador == 4){
    digitalWrite(J1_3, LOW);
    digitalWrite(J1_4, HIGH);
  }
  else if (J1_Contador == 5){
    digitalWrite(J1_4, LOW);
    digitalWrite(J1_5, HIGH);
  }
  else if (J1_Contador == 6){
    digitalWrite(J1_5, LOW);
    digitalWrite(J1_6, HIGH);
  }
  else if (J1_Contador == 7){
    digitalWrite(J1_6, LOW);
    digitalWrite(J1_7, HIGH);
  }
  else if (J1_Contador == 8){
    digitalWrite(J1_7, LOW);
    digitalWrite(J1_8, HIGH);
  }
}

void J2_state(){
  if (J2_Contador == 1){
    digitalWrite(J2_1, HIGH);
  }
  else if (J2_Contador == 2){
    digitalWrite(J2_1, LOW);
    digitalWrite(J2_2, HIGH);
  }
  else if (J2_Contador == 3){
    digitalWrite(J2_2, LOW);
    digitalWrite(J2_3, HIGH);
  }
  else if (J2_Contador == 4){
    digitalWrite(J2_3, LOW);
    digitalWrite(J2_4, HIGH);
  }
  else if (J2_Contador == 5){
    digitalWrite(J2_4, LOW);
    digitalWrite(J2_5, HIGH);
  }
  else if (J2_Contador == 6){
    digitalWrite(J2_5, LOW);
    digitalWrite(J2_6, HIGH);
  }
  else if (J2_Contador == 7){
    digitalWrite(J2_6, LOW);
    digitalWrite(J2_7, HIGH);
  }
  else if (J2_Contador == 8){
    digitalWrite(J2_7, LOW);
    digitalWrite(J2_8, HIGH);
  }
}
