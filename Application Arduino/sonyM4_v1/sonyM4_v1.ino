#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

byte serInString[400];  // array that will hold the different bytes  400=400bytes;
int  serInIndx  = 0;    // index of serInString[] in which to insert the next incoming byte
int  serOutIndx = 0;    // index of the outgoing serInString[] array;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  Serial.println("Démarrage...");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(38400);
}

void loop() // run over and over
{
  //readSerialString();
  printSerialString();
}

void serialEvent() {
  int sb;

  if (Serial.available()) {
    while (Serial.available()) {

    }
  }
}
  void readSerialString () {

    //Serial.print("reading Serial String: ");     //optional confirmation
    while (Serial.available()) {
      sb = Serial.read();
      serInString[serInIndx] = sb;
      serInIndx++;
      //serialWrite(sb);                        //optional confirmation
    }
    //Serial.println();
  }
}


void printSerialString() {
  if ( serInIndx > 0) {

    for (serOutIndx = 0; serOutIndx < serInIndx; serOutIndx++) {
      Serial.print(serInString[serOutIndx]);    //print out the byte at the specified index
      //serInString[serOutIndx] = "";            //optional: flush out the content
      commands(serOutIndx);
    }
    //reset all the functions to be able to fill the string back with content
    serOutIndx = 0;
    serInIndx  = 0;
    Serial.println();
  }

}
void commands(int serOutIndx) {
  switch (serInString[serOutIndx]) {
    case 0x00: {
        switch (serInString[serOutIndx + 1]) {
          case 0x30: {

            }
            break;
        }
      }
      break;
  }
}
