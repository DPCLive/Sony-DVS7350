#define externalDevice Serial1
 
enum t_state : uint8_t {WAITING_00, WAITING_30, WAITING_LENGTH, WAITING_COMMAND} state = WAITING_00;
 
const uint32_t maxCommandLength = 4;
 
struct t_command {
  uint8_t length;
  uint8_t bytes[maxCommandLength];
};
 
const t_command commandList[] = {   // don't forget to pad with 0x00 to the left
  {0x03, {0x00, 0x21, 0xc0, 0x05}}, // command Comm_0
  {0x03, {0x00, 0x21, 0xc0, 0x06}}, // command Comm_1
  {0x02, {0x00, 0x00, 0x00, 0x00}}, // command Comm_2
  {0x02, {0x00, 0x00, 0x00, 0x01}}, // command Comm_3
  {0x03, {0x00, 0x20, 0x10, 0x09}}, // command Comm_4
  {0x03, {0x00, 0x20, 0x11, 0x0d}}, // command Comm_5
  {0x03, {0x00, 0x20, 0x11, 0x20}}, // command Comm_6
  {0x03, {0x00, 0x10, 0x1b, 0x0d}}, // command Comm_7
  {0x04, {0x00, 0x16, 0x00, 0x1f}}, // command Comm_8
  {0x03, {0x00, 0x0a, 0x1b, 0x0d}}, // command Comm_9
};
const uint8_t numberOfCommands = sizeof commandList / sizeof commandList[0];
 
// we assign symbolic names to the indexes to make it easier to read the code
enum : uint8_t {Comm_0 = 0, Comm_1, Comm_2, Comm_3, Comm_4, Comm_5, Comm_6, Comm_7, Comm_8, Comm_9, Comm_Unknown = 0xFF};
 
// define static answers if you know them
const uint8_t answerComm_2[] = {0x03, 0x00, 0x80, 0x92}; // hardwire answer to Comm_2
const uint8_t answerComm_3[] = {0x03, 0x00, 0x81, 0x17}; // hardwire answer to Comm_3
const uint8_t answerComm_4[] = {0x04, 0x20, 0x90, 0x09, 0x01}; // hardwire answer to Comm_4


bool receiveCommand(t_command& aCommand)
{
  bool commandComplete = false;
  int r = externalDevice.read();
  if (r == -1) return false;
 
  uint8_t byteReceived = (uint8_t) r;
  static uint8_t bytePosition;
 
  switch (state) {
    case WAITING_00: // handle ping
      if (r == 0x00) state = WAITING_30;
      break;
 
    case WAITING_30:
      if (r == 0x30) {
          Serial.println(F("Got PING"));
        // got ping, provide answer
        externalDevice.write(0x84);
        externalDevice.write(0x84);
        state = WAITING_LENGTH;
      } else if (r != 0x00) state = WAITING_00; // handle 00 00 30 ... by recognizing the 2 last bytes
      break;
 
    case WAITING_LENGTH:
      if (byteReceived == 0x00) { // length can't be 0. Handle possible ping
        state = WAITING_30;
      } else {
        if (byteReceived <= maxCommandLength) {
          aCommand.length = byteReceived;
          bytePosition = byteReceived;
          memset(aCommand.bytes, 0x00, maxCommandLength); // empty the previous command cf https://en.cppreference.com/w/cpp/string/byte/memset
          state = WAITING_COMMAND;
        } else {
          // handle error, this can't be a command.
          Serial.println(F("error: Command length too long"));
          externalDevice.end();                     // close the connection
          delay(100);                               // wait a bit
          externalDevice.begin(38400, SERIAL_8N1);  // open a fresh connection
          state = WAITING_00;                       //  wait for a new ping
        }
      }
      break;
 
    case WAITING_COMMAND:
      aCommand.bytes[--bytePosition] = byteReceived;
      if (bytePosition == 0) {
        commandComplete = true;
        state = WAITING_COMMAND;
      }
      break;
  }
 
  return commandComplete;
}
 
bool handleCommand(t_command& aCommand)
{
  uint8_t commandIndex = Comm_Unknown;
 
  // Do we know this command?
  for (uint8_t i = 0; i < numberOfCommands; i++) {
    // check if we have the right length and matching bytes for the command
    if ((aCommand.length == commandList[i].length) && (!memcmp(aCommand.bytes, commandList[i].bytes, maxCommandLength))) { // cf memcmp() doc: https://en.cppreference.com/w/cpp/string/byte/memcmp
      commandIndex = i; // found our command
      break;
    }
  }
 
  // did we find our command?
  if (commandIndex == Comm_Unknown) return false;
 
  // we have a known command
  switch (commandIndex) {
    case Comm_0: Serial.println(F("Command 0")); /* send answer */; break;
    case Comm_1: Serial.println(F("Command 1")); /* send answer */; break;
    case Comm_2: Serial.println(F("Command 2")); externalDevice.write(answerComm_2, sizeof answerComm_2); break;
    case Comm_3: Serial.println(F("Command 3")); externalDevice.write(answerComm_3, sizeof answerComm_3); break;
    case Comm_4: Serial.println(F("Command 4")); externalDevice.write(answerComm_4, sizeof answerComm_4); break;
    case Comm_5: Serial.println(F("Command 5")); /* send answer */; break;
    case Comm_6: Serial.println(F("Command 6")); /* send answer */; break;
    case Comm_7: Serial.println(F("Command 7")); /* send answer */; break;
    case Comm_8: Serial.println(F("Command 8")); /* send answer */; break;
    case Comm_9: Serial.println(F("Command 9")); /* send answer */; break;
  }
  return true;
}
 
void setup() {
  Serial.begin(115200);
  externalDevice.begin(38400, SERIAL_8N1);
}
 
void loop() {
  t_command aCommand;
  if (receiveCommand(aCommand)) handleCommand(aCommand);
  // you can do other non blocking stuff here
}
