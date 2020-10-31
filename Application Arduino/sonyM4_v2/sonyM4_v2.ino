#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

String inputString = "";

void setup()
{
  Serial.begin(38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  Serial.println("Démarrage...");

  mySerial.begin(38400);
}

void loop() // run over and over
{
  printSerialString();
}

void serialEvent() {
  while (mySerial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
  }
}

void printSerialString() {
  if (inputString.length() > 0) {
    for (int serOutIndx = 0; serOutIndx < inputString.length(); serOutIndx++) {
      commands(serOutIndx);
    }
  }
}

void commands(int serOutIndx) {
  switch (inputString[serOutIndx]) {
    case 0x00: {
        switch (inputString[serOutIndx + 1]) {
          case 0x30: {
              inputString = inputString.substring(0, serOutIndx + 1);
            }
            break;
        }
      }
      break;
  }
}
