#include <Arduino_FreeRTOS.h>
#include "LinkClass.h"

//Functions declaration
float ReadFloat();
char ReadChar();



//Tasks declaration (for multithreading)
void TaskRotateMotor1(void *pvParameters);
void TaskRotateMotor2(void *pvParameters);






//Creating links objects
int m1[4] = {2,3,4,6};
LinkClass link1(m1);

int m2[4] = {8,9,10,11};
LinkClass link2(m2);



void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  float sp = 90;
  //SetUp task
  //xTaskCreate( TaskRotateMotor2, "TaskRotateMotor2", 128, NULL, 1, NULL);
  //xTaskCreate( TaskRotateMotor1, "TaskRotateMotor1", 128, NULL, 1, NULL);
}

void loop() {
  float in1 = -90, in2 = 60;
  char a;
  //in1 = ReadFloat();
  //in2 = ReadFloat();

  a = ReadChar();
  Serial.println(a);
  
  //digitalWrite(LED_BUILTIN, HIGH);
  delay((int)100 * in2);
  link1.GoToDeg(in1, in2);
  digitalWrite(LED_BUILTIN, LOW);
  
  delay(1000);
}





void TaskRotateMotor1(void *pvParameters){
  (void) pvParameters;
  link1.GoToDeg(90, 17.5);
  vTaskDelete( NULL );
}

void TaskRotateMotor2(void *pvParameters){
  (void) pvParameters;
  link2.GoToDeg(90, 17.5);
  vTaskDelete( NULL );
}

//Take reading as a float
float ReadFloat(){
  while(Serial.available() < 0){}
    return Serial.parseFloat();
  
}

char ReadChar(){
  if(Serial.available() > 0){
    return (char)Serial.read();
  }
}

