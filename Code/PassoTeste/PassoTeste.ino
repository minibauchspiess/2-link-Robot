#include <Arduino_FreeRTOS.h>
#include "LinkClass.h"
#include "SerialManager.h"


//Tasks declaration (for multithreading)
void TaskMotor1(void *pvParameters);
void TaskMotor2(void *pvParameters);
void TaskReadings(void *pvParameters);



//Creating links objects
int m1[4] = {2,3,4,6};
LinkClass link1(m1);

int m2[4] = {8,9,10,11};
LinkClass link2(m2);

//Creating Serial Manager object
SerialManager sm;


//Variables used for the motor tasks
bool enableM1=false;
float m1Angle, m1Speed, tDelay;

bool enableM2=false;
float m2Angle, m2Speed;





float speed31, speed32;



void setup() {
  sm = SerialManager();
  //pinMode(LED_BUILTIN, OUTPUT);

  xTaskCreate( TaskReadings, "TaskReadings", 260, NULL, 1, NULL);
  xTaskCreate( TaskMotor1, "TaskMotor1", 260, NULL, 1, NULL);
  xTaskCreate( TaskMotor2, "TaskMotor2", 260, NULL, 1, NULL);
  
  
}

void loop() {

}


void TaskReadings(void *pvParameters){
  (void) pvParameters;
  while(true){
    //Teste da leitura da porta serial
    int result = sm.ReadSerial();
  
    if(result == 1){
      //Set global parameters according to readings
      char com = sm.GetCommand();
      m1Angle = sm.GetAngle(1);
      m2Angle = sm.GetAngle(2);

      //Activate motor tasks according to the command
      if(com == '0'){
        //Serial.println("Voltando pro comeco");
      }
      
      else if(com == '1'){
        m1Speed = sm.GetSpeed(1);
        m2Speed = sm.GetSpeed(2);
      
        enableM1 = true;
        while(enableM1){
          vTaskDelay(0.001);
        }
        enableM2 = true;
      }
  
      else if(com == '2'){
        m1Speed = sm.GetSpeed(1);
        m2Speed = sm.GetSpeed(2);
        
        enableM1 = true;
        enableM2 = true;
      }
    
      else if(com == '3'){
        //digitalWrite(12, HIGH);
        tDelay = sm.GetTime();
        enableM1 = true;
        enableM2 = true;
      }
      else if(com == '4'){
        
      } 
    }
    vTaskDelay(10);
  }
  
}

void TaskMotor1(void *pvParameters){
  (void) pvParameters;

  while(true){
    if(enableM1){
      
      switch(sm.GetCommand()){
        case '0':

          enableM1 = false;
          break;
          
        case '1':
          link1.GoToDeg(m1Angle, m1Speed);
          enableM1 = false;
          break;

        case '2':
          link1.GoToDeg(m1Angle, m1Speed);
          enableM1 = false;
          break;

        case '3':
          speed31 = min((abs(link1.GetAngle() - m1Angle) / tDelay), (abs(link1.GetAngle() - 360 - m1Angle) / tDelay));
          if(speed31 > 0){
            link1.GoToDeg(m1Angle, speed31);
          }
          enableM1 = false;
          break;

        case '4':

          enableM1 = false;
          break;
          
      }
    }
    vTaskDelay(1);
    
  }
  vTaskDelete(NULL);
}

void TaskMotor2(void *pvParameters){
  (void) pvParameters;
  
  while(true){
    if(enableM2){
      switch(sm.GetCommand()){
        case '0':

          enableM2 = false;
          break;
          
        case '1':
          link2.GoToDeg(m2Angle, m2Speed);
          enableM2 = false;
          break;

        case '2':
          link2.GoToDeg(m2Angle, m2Speed);
          enableM2 = false;
          break;

        case '3':
          speed32 = min((abs(link2.GetAngle() - m2Angle) / tDelay), (abs(link2.GetAngle() - 360 - m2Angle) / tDelay));
          if(speed32 > 0){
            link2.GoToDeg(m2Angle, speed32);
          }
          enableM2 = false;
          break;

        case '4':

          enableM2 = false;
          break;
          
      }
    }
    vTaskDelay(1);
    
  }
  vTaskDelete(NULL);
}



void blinkNTimes(float n){
  float i=0;
  while(i<n){
    digitalWrite(12, HIGH);
    delay(300);
    digitalWrite(12,LOW);
    delay(300);
    i = i + 1;
  }
}

