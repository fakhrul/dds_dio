#include <Arduino.h>

#define BUZZER 18

#define OUT_1 2
#define OUT_2 15
#define OUT_3 5
#define OUT_4 4

char cmdbuf[200];
int cmdLength;
#define CMD_START 'S'

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);

  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // while (!Serial2)
  // {
  //   ; // wait for serial port to connect. Needed for native USB port only
  // }

  Serial.write("Serial opened");
  Serial.write("Serial2 opened");

  pinMode(BUZZER, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(OUT_1, OUTPUT);
  pinMode(OUT_2, OUTPUT);
  pinMode(OUT_3, OUTPUT);
  pinMode(OUT_4, OUTPUT);
}

void loop()
{
  cmdLength = 0;
  memset(cmdbuf, 0, sizeof(cmdbuf));

  while (Serial2.available() > 0)
  {
    delay(10);
    int inChar = Serial2.read();
    cmdbuf[cmdLength] = inChar;
    cmdLength++;
  }

  if (cmdLength > 0)
  {
    Serial.write("received");
    // if(cmdbuf[0] == CMD_START && cmdbuf[1] == 'B' && cmdbuf[2] == '1')
    // {
    //   //buzzer
    //   digitalWrite(BUZZER, HIGH);
    // }
    // else if(cmdbuf[0] == CMD_START && cmdbuf[1] == 'B' && cmdbuf[2] == '0')
    // {
    //   digitalWrite(BUZZER, LOW);

    // }
    if (cmdbuf[0] == 'B')
    {
      // buzzer
      digitalWrite(BUZZER, HIGH);
    }
    else if (cmdbuf[0] == 'b')
    {
      digitalWrite(BUZZER, LOW);
    }
    else if (cmdbuf[0] == 'L')
    {
      // buzzer
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (cmdbuf[0] == 'l')
    {
      digitalWrite(LED_BUILTIN, LOW);
    }

    else if (cmdbuf[0] == 'Q')
    {
      // buzzer
      digitalWrite(OUT_1, HIGH);
    }
    else if (cmdbuf[0] == 'q')
    {
      digitalWrite(OUT_1, LOW);
    }

    else if (cmdbuf[0] == 'W')
    {
      // buzzer
      digitalWrite(OUT_2, HIGH);
    }
    else if (cmdbuf[0] == 'w')
    {
      digitalWrite(OUT_2, LOW);
    }

    else if (cmdbuf[0] == 'E')
    {
      // buzzer
      digitalWrite(OUT_3, HIGH);
    }
    else if (cmdbuf[0] == 'e')
    {
      digitalWrite(OUT_3, LOW);
    }

    else if (cmdbuf[0] == 'R')
    {
      // buzzer
      digitalWrite(OUT_4, HIGH);
    }
    else if (cmdbuf[0] == 'r')
    {
      digitalWrite(OUT_4, LOW);
    }

    else
    {
      // digitalWrite(BUZZER, LOW);
    }
  }
}