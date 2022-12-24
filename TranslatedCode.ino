#include <iostream>
#include <string>
#include <vector>
#include "bits/stdc++.h"
#include <RoboClaw.h>
using namespace std;

RoboClaw roboclaw(&Serial2, 10000);

int distanceMMStorage[180] = { 0 };
int scansPerformed = 0;

void setup() {

  Serial.begin(921600);
  Serial1.begin(115200, SERIAL_8N1, 4, 2);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  roboclaw.begin(38400);

}

void loop() {

  byte data[22] = {};

  int bytesRead = Serial1.readBytesUntil(char(250), data, 22);

  if (bytesRead != 21) {

    //Serial.println("Bad data.");

    for (int i = 0; i < bytesRead; i++) {

      //Serial.print((int)data[i]);
      //Serial.print("\t");

    }

    //Serial.println("");

    return;

  } 

  data[0] = ((data[0]) - 160);

  for (int i = 1; i < 5; i++) {

    if (data[i * 4] != 128) {

      int distanceMM = data[4 * i - 1] | ((data[4 * i] & 0x3f) << 8);

      int angle = data[0] * 4 + i + 1;

      if (angle < 180) {

        distanceMMStorage[angle] = distanceMM;

        //Serial.print(distanceMM);
        //Serial.print(",");
        //Serial.println(angle);

      }
    }
  }

  int quad1 = *min_element(&(distanceMMStorage[0]), &(distanceMMStorage[44]));
  int quad2 = *min_element(&(distanceMMStorage[45]), &(distanceMMStorage[89]));
  int quad3 = *min_element(&(distanceMMStorage[90]), &(distanceMMStorage[134]));
  int quad4 = *min_element(&(distanceMMStorage[135]), &(distanceMMStorage[180]));
  //int quad5 = findMinimumValue(slicing(distances, 180, 224));
  //int quad6 = findMinimumValue(slicing(distances, 225, 269));
  //int quad7 = findMinimumValue(slicing(distances, 270, 314));
  //int quad8 = findMinimumValue(slicing(distances, 315, 359));

  scansPerformed += 1;

  if (scansPerformed % 360 == 0) {

    for (int i = 0; i < 181; i++) {

      distanceMMStorage[i] = 6001;

    }

    Serial.println(quad1);
    Serial.println(quad2);
    Serial.println(quad3);
    Serial.println(quad4);

    int minVal = 6001;
    int minQuad = 0;

    if (minVal > quad1) {

      minVal = quad1;
      minQuad = 1;
    }

    if (minVal > quad2) {

      minVal = quad2;
      minQuad = 2;
    }

    if (minVal > quad3) {

      minVal = quad3;
      minQuad = 3;
    }

    if (minVal > quad4) {

      minVal = quad4;
      minQuad = 4;
    }

    //include conditional statements for the quads 5-8 later.


  }
  
  roboclaw.ForwardM1(0x80, 64);
  roboclaw.ForwardM2(0x80, 64);
  roboclaw.ForwardM1(0x81, 64);
  roboclaw.ForwardM2(0x81, 64);

}
