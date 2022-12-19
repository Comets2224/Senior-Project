#include <RoboClaw.h>

//RoboClaw roboclaw(&Serial2, 10000);

void setup() {
  //roboclaw.begin(38400);
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  if (Serial.available() > 0) {

    if (Serial.read() < 53) {

      digitalWrite(LED_BUILTIN, HIGH);
      //roboclaw.ForwardM1(0x80, 0);
      //roboclaw.ForwardM2(0x80, 0);

    }

    else {

      digitalWrite(LED_BUILTIN, LOW);
      //roboclaw.ForwardM1(0x80, 64);
      //roboclaw.ForwardM2(0x80, 64);

    }

    delay(1000);

  }
}
