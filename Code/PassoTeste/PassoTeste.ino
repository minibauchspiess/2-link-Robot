#include "LinkClass.h"

#define M1A1 2
#define M1B1 3
#define M1A2 4
#define M1B2 5


#define M2A1 6
#define M2B1 7
#define M2A2 8
#define M2B2 9

int now = M1A1;
int flag = 0;
float leitura;
float passos;

int m1[4] = {2,3,4,6};
LinkClass link1(m1);


void AtivaBobina(int bobVelha, int bobNova){
  //Seta bobina velha para 0, antes de setar a proxima para 5V
  digitalWrite(bobVelha, LOW);
  digitalWrite(bobNova, HIGH);
}

void Passo(int motor, int npassos, int wait){
  
  int dir = npassos / abs(npassos);
  for(int i = 0; abs(i)<abs(npassos); i=i+dir){
    switch (now){
      case M1A1:
        if(flag == 0){
          flag = 1;
          digitalWrite(M1B1, HIGH);
          digitalWrite(M2B1, HIGH);
        }
        else{
          digitalWrite(M1A1, LOW);
          digitalWrite(M2A1, LOW);
          now = M1B1;
          flag = 0;
        }
        break;
  
      case M1B1:
        if(flag == 0){
          flag = 1;
          digitalWrite(M1A2, HIGH);
          digitalWrite(M2A2, HIGH);
        }
        else{
          digitalWrite(M1B1, LOW);
          digitalWrite(M2B1, LOW);
          now = M1A2;
          flag = 0;
        }
        break;

        case M1A2:
          if(flag == 0){
            flag = 1;
           digitalWrite(M1B2, HIGH);
           digitalWrite(M2B2, HIGH);
          }
          else{
            digitalWrite(M1A2, LOW);
            digitalWrite(M2A2, LOW);
            now = M1B2;
            flag = 0;
          }
         break;

        case M1B2:
          if(flag == 0){
            flag = 1;
            digitalWrite(M1A1, HIGH);
            digitalWrite(M2A1, HIGH);
          }
          else{
            digitalWrite(M1B2, LOW);
            digitalWrite(M2B2, LOW);
            now = M1A1;
            flag = 0;
          } 
          break;
    }
    
    delayMicroseconds(wait);
  }
}



void setup() {

  Serial.begin(9600);
/*
  pinMode(M1A1, OUTPUT);
  pinMode(M1A2, OUTPUT);
  pinMode(M1B1, OUTPUT);
  pinMode(M1B2, OUTPUT);

  digitalWrite(M1A1, HIGH);
  digitalWrite(M1A2, LOW);
  digitalWrite(M1B1, LOW);
  digitalWrite(M1B2, LOW);

  pinMode(M2A1, OUTPUT);
  pinMode(M2A2, OUTPUT);
  pinMode(M2B1, OUTPUT);
  pinMode(M2B2, OUTPUT);

  digitalWrite(M2A1, HIGH);
  digitalWrite(M2A2, LOW);
  digitalWrite(M2B1, LOW);
  digitalWrite(M2B2, LOW);
*/
 //PrintWriter output;
 //int m1[4] = {2,3,4,6};
 //int m2[4] = {6,7,8,9};
 //link1 = LinkClass(m1);
 //LinkClass link2 = LinkClass(m2);
  

}

void loop() {
  /*leitura=0;
  //Passo(4096,1);
  //delay(10000);
  if(Serial.available() > 0){
    leitura = Serial.parseFloat();
  }
  if(Serial.available() > 0){
    Serial.println(leitura);
  }
  passos = leitura * 4096 / 360;
  Passo(1, passos,5000);*/
 
  for(int i=0; i<4096; i++){
    
    link1.ExecuteStep(i%8, 775);
  }
  delay(2000);
  
}
