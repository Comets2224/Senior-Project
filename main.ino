#include <RoboClaw.h>

//char messageBuffer[3];
//size_t bytesRecieved;

//RoboClaw roboclaw(&Serial2, 10000);

void setup() {
  //roboclaw.begin(38400);
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  //int bytesQueued = Serial.readBytesUntil('\n', messageBuffer , 3);

  if (Serial.available() >= 3) {

    int num1 = Serial.read() * 100;
    int num2 = Serial.read() * 10;
    int num3 = Serial.read();

    int num = num1 + num2 + num3;

    if (num < 200) {

      digitalWrite(LED_BUILTIN, HIGH);
      //roboclaw.ForwardM1(0x80, 0);
      //roboclaw.ForwardM2(0x80, 0);

    }

    else {

      digitalWrite(LED_BUILTIN, LOW);
      //roboclaw.ForwardM1(0x80, 64);
      //roboclaw.ForwardM2(0x80, 64);

    }
  }
}

