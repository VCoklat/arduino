#include <EEPROM.h>
#include <string.h>
const int EEPROM_MIN_ADDR = 0;
const int EEPROM_MAX_ADDR = 511;
const int BUFSIZE = 1000;
char buf[BUFSIZE];
String myString;
char myStringChar[BUFSIZE];
int last_buff = 0;
bool new_string;

boolean eeprom_is_addr_ok(int addr) {
  return ((addr >= EEPROM_MIN_ADDR) && (addr <= EEPROM_MAX_ADDR));
}

boolean eeprom_write_bytes(int startAddr, const byte* array, int numBytes) {
  int i;
  if (!eeprom_is_addr_ok(startAddr) || !eeprom_is_addr_ok(startAddr + numBytes)) {
    return false;
  }
  for (i = 0; i < numBytes; i++) {
    EEPROM.write(startAddr + i, array[i]);
  }
  return true;
}

boolean eeprom_write_string(int addr, const char* string) {
  int numBytes;
  numBytes = strlen(string) + 1;
  return eeprom_write_bytes(addr, (const byte*)string, numBytes);
}

boolean eeprom_read_string(int addr, char* buffer, int bufSize) {
  byte ch;
  int bytesRead;
  if (!eeprom_is_addr_ok(addr)) {
    return false;
  }
  if (bufSize == 0) {
    return false;
  }
  // is there is room for the string terminator only, no reason to go further
  if (bufSize == 1) {
    buffer[0] = 0;
    return true;
  }
  bytesRead = 0;
  ch = EEPROM.read(addr + bytesRead);
  buffer[bytesRead] = ch;
  bytesRead++;
  while ( (ch != 0x00) && (bytesRead < bufSize) && ((addr + bytesRead) <= EEPROM_MAX_ADDR) ) {
    ch = EEPROM.read(addr + bytesRead);
    buffer[bytesRead] = ch;
    bytesRead++;
  }
  // make sure the user buffer has a string terminator, (0x00) as its last byte
  if ((ch != 0x00) && (bytesRead >= 1)) {
    buffer[bytesRead - 1] = 0;
  }
  return true;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  // EEPROM WRITE
  if(Serial.available()) {
    String input = Serial.readString();
    strcpy(buf, input.c_str());
    if(buf[0] == 'r') {
      for (int i = 0; i < BUFSIZE; i++) {
        eeprom_read_string(i, buf, BUFSIZE);
        if (buf[0] == 0) {
          new_string = true;
        } else if (new_string) {
          if(i != 1) Serial.println();
          Serial.print("Address: ");
          Serial.println(i);
          Serial.print("Value: ");
          Serial.println(buf);
          new_string = false;
        }
      }
      Serial.println("###############");
    } else if(buf[0] == 'c') {
      for (int i = 0 ; i < EEPROM.length() ; i++) {
        EEPROM.write(i, 0);
      }
      last_buff = 0;
      Serial.println("Memory Cleared");
      Serial.println("###############");
    } else if(buf[0] == 'w') {
      input = input.substring(1, input.length());
      strcpy(buf, input.c_str());
      eeprom_write_string(last_buff, 0);
      last_buff++;
      eeprom_write_string(last_buff, buf);
      Serial.print(buf);
      Serial.print(" is saved to address ");
      Serial.println(last_buff);
      last_buff = last_buff + input.length();
      Serial.println("###############");
    } else {
      Serial.println("Unknown Command");
      Serial.println("###############");
    }
  }
}
