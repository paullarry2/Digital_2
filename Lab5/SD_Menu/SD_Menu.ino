// Larry Paúl Fuentes
// Carné 18117
// Digital 2
// Laboratorio 5
// 09/04/2021


#include <SPI.h>
#include <SD.h>

File root; 
File myFile; //Variable que manejara todos los datos de lectura
int menu; // Variable que almacenara la entrada de la SD

void setup()
{
  // Inicio mi puerto serial a 115200 y mi SPI usando el modulo 0
  Serial.begin(115200);
  SPI.setModule(0);

//Rutina de incio de conexion con mi SD, uso mi puerto PA_3 como CS
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");
  imp_menu(); // Luego de terminar conexion e imprimir datos de mi SD, me imprime el menu
}

void loop()
{ // Chequea mi available, para ver si se ha enviado algo por comunicación seria. 
  // Cada numero depende del menu, realia una accion diferente 
  if (Serial.available()==1){
    menu = Serial.read(); 
    if(menu == '1'){
      imp_DK(); 
    }
    else if(menu == '2'){
      imp_SM(); 
    }
    else if(menu == '3'){
      imp_MT(); 
    }
    else if(menu == '0'){ // Si se presiona la opcion 0, imprime otra vez los datos de mi SD
      myFile = SD.open("/");
      printDirectory(myFile, 0);
      imp_menu(); // Vuelve a imprimir el menú
    }
    else {
      Serial.println("Ingeso no Valido, Intente de Nuevo: "); // Progra defensiva
    }
  }  
}

// Funcion para imprimir mis datos en la SD
void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

void imp_MT(){ //  Funcion que imprime mi primera figura
  myFile = SD.open("METROID.TXT");
  if (myFile) {
    Serial.println("METROID.TXT:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening METROID.TXT");
  }
  imp_menu();
}

void imp_SM(){ //  Funcion que imprime mi segunda figura
  myFile = SD.open("SAMUS.TXT");
  if (myFile) {
    Serial.println("SAMUS.TXT:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening SAMUS.TXT");
  }
  imp_menu();
}

void imp_DK(){ //  Funcion que imprime mi tercera figura
  myFile = SD.open("DONKEY~1.TXT");
  if (myFile) {
    Serial.println("DONKEY~1.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening DONKEY~1.txt");
  }
  imp_menu(); // Al finalizar cada una de las figuras imprimo nuevamente mi menu
}


//METROID.TXT    396
//SAMUS.TXT   429
//DONKEY~1.TXT

void imp_menu(){ // Funcion que imprime mi menú 
  Serial.println("");
  Serial.println("Que archivo desea abrir: ");
  Serial.println("Presione 0 para ver los archivos de la SD");
  Serial.println("Presione 1 para abrir el primer archivo");
  Serial.println("Presione 2 para abrir el segundo archivo");
  Serial.println("Presione 3 para abrir el tercer archivo");
  Serial.println("");
  
}
