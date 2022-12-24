#include <iostream>
#include <string>
#include <vector>
#include "bits/stdc++.h"
using namespace std;

int distanceMMStorage[180] = { 0 };
int scansPerformed = 0;

void setup() {

  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
}

void loop() {

  int b = char(Serial2.read());
  //int b = 250; Temporary declaration

  vector<int> data = {};

  for (;;) {

    if (b == 250 && sizeof(data) / sizeof(data[0]) > 20) {

      break;
    }

    data.push_back(b); //append b to the dataset

    Serial.print("test");

    b = char(Serial2.read());
  }

  if (sizeof(data) / sizeof(data[0]) == 21) {

    data[0] = ((data[0]) - 160);

    for (int i = 1; i < 5; i++) {

      if (data[i * 4] != 128) {

        int distanceMM = data[4 * i - 1] | ((data[4 * i] & 0x3f) << 8);

        int angle = data[0] * 4 + i + 1;

        if (angle < 181) {

          distanceMMStorage[angle] = distanceMM;
        }
      }
    }
  }

  int quad1 = *min_element(&(data[0]), &(data[44]));
  int quad2 = *min_element(&(data[45]), &(data[89]));
  int quad3 = *min_element(&(data[90]), &(data[134]));
  int quad4 = *min_element(&(data[135]), &(data[180]));
  //int quad5 = findMinimumValue(slicing(distances, 180, 224));
  //int quad6 = findMinimumValue(slicing(distances, 225, 269));
  //int quad7 = findMinimumValue(slicing(distances, 270, 314));
  //int quad8 = findMinimumValue(slicing(distances, 315, 359));

  if (scansPerformed % 360 == 0) {

    Serial.println(quad1);
    Serial.print(quad2);
    Serial.print(quad3);
    Serial.print(quad4);

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
  
}
