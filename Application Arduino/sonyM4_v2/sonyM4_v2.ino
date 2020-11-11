#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

String inputString = "00300030";
int serOutIndx;

void setup()
{
  Serial.begin(38400);
  //inputString.reserve(10);
  /*while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }*/
  Serial.println("Démarrage...");
  mySerial.begin(38400);
}

void loop() // run over and over
{
 // printSerialString();
}

void serialEvent() {
  while(mySerial.available()) {
    byte indatas = mySerial.read();
    inputString += indatas;
  }
  
}

void printSerialString() {
  if (inputString.length() > 0) {
    for (serOutIndx = 0; serOutIndx < inputString.length(); serOutIndx++) {
      commands(serOutIndx);
    }
  }
}

void commands(int serOutIndx) {
  Serial.println(inputString.substring(serOutIndx,serOutIndx+2).toInt());
  switch (inputString[serOutIndx]) {
    case 0: {
      Serial.println("ok");
        switch (inputString[serOutIndx + 1]) {
          case 0x30: {
            mySerial.write("8484");
            Serial.println("8484");
              inputString = inputString.substring(0, serOutIndx + 1);
              serOutIndx = 0;
            }
            break;
        }
      }
      break;
  }
}
