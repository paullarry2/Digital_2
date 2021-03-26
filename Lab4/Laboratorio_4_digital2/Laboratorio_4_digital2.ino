//Larry Paúl Fuentes 
//carné 18117
//Laboratorio 4
//22/03/2021

// Se utilizo de referecnia el codigo de ejemplo debounce de energia, para el antirebote de los switch 1 y 2 . 

//Variables Pines
const int buttonPin = 31;
const int buttonPin2 = 17;     // the number of the pushbutton pin
#define verde  GREEN_LED   // the number of the LED pin
#define rojo RED_LED


// Estados del debounce
int ledState = HIGH;         // the current state of the output pin
int ledState2 = HIGH;
int buttonState;             // the current reading from the input pin
int buttonState2;
int pressState = LOW;
int semaforoState = LOW;
int lastButtonState = LOW;// the previous reading from the input pin
int lastButtonState2 = LOW;

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
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);
  
  if (buttonState == HIGH){
    pressState = 1;
  }
  else if (buttonState == LOW and pressState == 1){ 
    SemaforoCheck();
    delay(50);
    pressState = 0;
  }

  if (buttonState2 == HIGH){
    pressState = 1;
  }
  else if (buttonState2 == LOW and pressState2 == 1){
    SemaforoCheck();
    delay(50);
    pressState = 0;
    
  }
  //Chequea que el juego no haya comenzado todavia.

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  }
  




void SemaforoCheck(){
  if (semaforoState == LOW){
    //Si no ha iniciado lo que hara será empezar la secuencia de semaforo
    semaforo(); 
    semaforoState = HIGH;
  }
}
