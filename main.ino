#include <RoboClaw.h>

void setup() {
  //roboclaw.begin(38400);
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  long num = Serial.parseInt();

  if (num < 200 && num > 0) {

    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(num);
    //roboclaw.ForwardM1(0x80, 0);
    //roboclaw.ForwardM2(0x80, 0);

  } else {

    digitalWrite(LED_BUILTIN, LOW);
    //roboclaw.ForwardM1(0x80, 64);
    //roboclaw.ForwardM2(0x80, 64);
  }
}
