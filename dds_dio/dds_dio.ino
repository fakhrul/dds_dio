#include "PCF8574.h"
#include "Arduino.h"


#define RXD2 32
#define TXD2 17

// Set i2c address
PCF8574 pcf8574(0x24, 4, 5);  // 0x24 is address   IO4 is SDA   IO5 is SCL

int cmdLength;
char cmdBuf[200];

int rcCmdLength;
char rcCmdBuf[200];


char stateP0 = 'a';
char stateP1 = 'b';
char stateP2 = 'c';
char stateP3 = 'd';
char stateP4 = 'e';
char stateP5 = 'f';
char stateP6 = 'g';
char stateP7 = 'h';

void setup() {
  Serial.begin(115200);

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  //Initiaite Digital IO
  pcf8574.pinMode(P0, OUTPUT);
  pcf8574.pinMode(P1, OUTPUT);
  pcf8574.pinMode(P2, OUTPUT);
  pcf8574.pinMode(P3, OUTPUT);
  pcf8574.pinMode(P4, OUTPUT);
  pcf8574.pinMode(P5, OUTPUT);
  pcf8574.pinMode(P6, OUTPUT);
  pcf8574.pinMode(P7, OUTPUT);
  // pcf8574.pinMode(P1, INPUT);

  // Serial.print("Init pcf8574...");
  if (pcf8574.begin()) {
    // Serial.println("OK");
  } else {
    // Serial.println("KO");
  }
}


void loop() {

  cmdLength = 0;
  memset(cmdBuf, 0, sizeof(cmdBuf));

  while (Serial.available() > 0) {
    delay(1);
    int inChar = Serial.read();
    cmdBuf[cmdLength] = inChar;
    cmdLength++;
  }

  if (cmdLength > 0) {
    char code = cmdBuf[0];
    // Serial.println(cmdBuf);
    switch (code) {
      case 'A':
        pcf8574.digitalWrite(P0, LOW);
        stateP0 = code;
        break;
      case 'a':
        pcf8574.digitalWrite(P0, HIGH);
        stateP0 = code;
        break;
      case 'B':
        pcf8574.digitalWrite(P1, LOW);
        stateP1 = code;
        break;
      case 'b':
        pcf8574.digitalWrite(P1, HIGH);
        stateP1 = code;
        break;
      case 'C':
        pcf8574.digitalWrite(P2, LOW);
        stateP2 = code;
        break;
      case 'c':
        pcf8574.digitalWrite(P2, HIGH);
        stateP2 = code;
        break;
      case 'D':
        pcf8574.digitalWrite(P3, LOW);
        stateP3 = code;
        break;
      case 'd':
        pcf8574.digitalWrite(P3, HIGH);
        stateP3 = code;
        break;
      case 'E':
        pcf8574.digitalWrite(P4, LOW);
        stateP4 = code;
        break;
      case 'e':
        pcf8574.digitalWrite(P4, HIGH);
        stateP4 = code;
        break;


      case 'F':
        pcf8574.digitalWrite(P5, LOW);
        stateP5 = code;
        break;
      case 'f':
        pcf8574.digitalWrite(P5, HIGH);
        stateP5 = code;
        break;
      case 'G':
        pcf8574.digitalWrite(P6, LOW);
        stateP6 = code;
        break;
      case 'g':
        pcf8574.digitalWrite(P6, HIGH);
        stateP6 = code;
        break;
      case 'H':
        pcf8574.digitalWrite(P7, LOW);
        stateP7 = code;
        break;
      case 'h':
        pcf8574.digitalWrite(P7, HIGH);
        stateP7 = code;
        break;
      case 'S':
        char szBuffer[8 + 1];
        sprintf(szBuffer, "%c%c%c%c%c%c%c%c", stateP0, stateP1, stateP2, stateP3, stateP4, stateP5, stateP6, stateP7);
        Serial.print(szBuffer);
        break;
      default:
        break;
    }

        cmdLength = 0;
    memset(cmdBuf, 0, sizeof(cmdBuf));
  }


  while (Serial2.available() > 0) {
    delay(1);
    int inChar = Serial2.read();
    rcCmdBuf[rcCmdLength] = inChar;
    rcCmdLength++;
  }


  // k1=98FA089A
  // k2=98FA0C9E
  // k3=98FA0496
  // k4=98FA099B
  // k5=98FA0294
  // k6=98FA0597
  // k7=98FA0193
  // k8=98FA0395

  if (rcCmdLength > 0) {

    // Serial.print(rcCmdBuf);


    if (strncmp(rcCmdBuf, "LC:98FA089A", 11) == 0) {
      pcf8574.digitalWrite(P5, LOW);
      stateP5 = 'F';
    } else if (strncmp(rcCmdBuf, "LC:98FA0C9E", 11) == 0) {
      pcf8574.digitalWrite(P5, HIGH);
      stateP5 = 'f';
    } else if (strncmp(rcCmdBuf, "LC:98FA0496", 11) == 0) {
      pcf8574.digitalWrite(P6, LOW);
      stateP5 = 'G';
    } else if (strncmp(rcCmdBuf, "LC:98FA099B", 11) == 0) {
      pcf8574.digitalWrite(P6, HIGH);
      stateP5 = 'g';
    } else if (strncmp(rcCmdBuf, "LC:98FA0294", 11) == 0) {
      pcf8574.digitalWrite(P7, LOW);
      stateP5 = 'H';
    } else if (strncmp(rcCmdBuf, "LC:98FA0597", 11) == 0) {
      pcf8574.digitalWrite(P7, HIGH);
      stateP5 = 'h';
    }

    rcCmdLength = 0;
    memset(rcCmdBuf, 0, sizeof(rcCmdBuf));
  }
}
