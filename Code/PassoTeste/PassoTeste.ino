#include "LinkClass.h"

int m1[4] = {2,3,4,6};
LinkClass link1(m1);



void setup() {

  Serial.begin(9600);
}

void loop() {

  int dt,dt2;

  link1.GoToDeg(90, 22.5);
  delay(111111111);
}
