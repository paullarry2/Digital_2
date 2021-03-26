//Larry Paúl Fuentes 
//carné 18117
//Laboratorio 4
//22/03/2021

// Se utilizo de referecnia el codigo de ejemplo debounce de energia, para el antirebote de los switch 1 y 2 . 

//Variables Pines
const int buttonPin = 31;
const int buttonPin2 = 17;     // the number of the pushbutton pin
const int verde =  GREEN_LED;      // the number of the LED pin
const int rojo = RED_LED;


// Estados del debounce
int ledState = HIGH;         // the current state of the output pin
int ledState2 = HIGH;
int buttonState;             // the current reading from the input pin
int buttonState2;
int semaforoState = LOW;
int lastButtonState = LOW;// the previous reading from the input pin
int lastButtonState2 = LOW;

//Variables Tiempo Debounce
long lastDebounceTime = 0;  // the last time the output pin was toggled
long lastDebounceTime2 = 0;
long debounceDelay = 100;    // the debounce time; increase if the output flickers
void semaforo (void);


void setup() {
  // Inicializo mi pines
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(verde, OUTPUT);
  pinMode(rojo, OUTPUT);
  Serial.begin(9600);
 
}

void loop() {
   int reading = digitalRead(buttonPin);
   int reading2 = digitalRead(buttonPin2);    
   
   

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    semaforoState = reading;

  }
  //Chequea que el juego no haya comenzado todavia.
  if (semaforoState == LOW){
    //Si no ha iniciado lo que hara será empezar la secuencia de semaforo
    semaforo(); 
    semaforoState = HIGH;

  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  }
  
}


void semaforo (void) {
  digitalWrite(HIGH, rojo); //Pone en rojo 
  delay(250);
  digitalWrite(HIGH,rojo);
  digitalWrite(HIGH,verde); //Esta combinacion en rgb crea el color amarillo
  delay(250);
  digitalWrite(LOW,rojo);
  digitalWrite(HIGH, verde); //Pone en verde
  delay(250);
  digitalWrite(LOW,verde); // Termina secuencia
}
