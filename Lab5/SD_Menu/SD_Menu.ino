/*
  Listfiles
 
 This example shows how print out the files in a 
 directory on a SD card 
 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 2 Feb 2014
 by Scott Fitzgerald
 
 This example code is in the public domain.

 */
#include <SPI.h>
#include <SD.h>

File root;
File myFile;
int menu;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  SPI.setModule(0);


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
  imp_menu();
}

void loop()
{
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
    else {
      Serial.println("Ingeso no Valido, Intente de Nuevo: ");
    }
  }

  
}

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

void imp_MT(){
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

void imp_SM(){
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

void imp_DK(){
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
  imp_menu();
}


//METROID.TXT    396
//SAMUS.TXT   429
//DONKEY~1.TXT
void imp_menu(){
  Serial.println("");
  Serial.println("Que archivo desea abrir: ");
  Serial.println("Presione 1 para abrir el primer archivo");
  Serial.println("Presione 2 para abrir el segundo archivo");
  Serial.println("Presione 3 para abrir el tercer archivo");
  Serial.println("Presione 4 para ver los archivos de la SD");
  Serial.println("");
  
}
