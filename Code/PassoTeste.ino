

#define M1A1 2
#define M1B1 3
#define M1A2 4
#define M1B2 5


#define M2A1
#define M2B1
#define M2A2
#define M2B2

int now = M1A1;
int flag = 0;
float leitura;
float passos;


void AtivaBobina(int bobVelha, int bobNova){
  //Seta bobina velha para 0, antes de setar a proxima para 5V
  digitalWrite(bobVelha, LOW);
  digitalWrite(bobNova, HIGH);
}

void Passo(int npassos, int wait){

  for(int i = 0; i<npassos; i=i+1){
    switch (now){
      case M1A1:
        if(flag == 0){
          flag = 1;
          digitalWrite(M1B1, HIGH);
        }
        else{
          digitalWrite(M1A1, LOW);
          now = M1B1;
          flag = 0;
        }
        break;
  
      case M1B1:
        if(flag == 0){
          flag = 1;
          digitalWrite(M1A2, HIGH);
        }
        else{
          digitalWrite(M1B1, LOW);
          now = M1A2;
          flag = 0;
        }
        break;

        case M1A2:
          if(flag == 0){
            flag = 1;
           digitalWrite(M1B2, HIGH);
          }
          else{
            digitalWrite(M1A2, LOW);
            now = M1B2;
            flag = 0;
          }
         break;

        case M1B2:
          if(flag == 0){
            flag = 1;
            digitalWrite(M1A1, HIGH);
          }
          else{
            digitalWrite(M1B2, LOW);
            now = M1A1;
            flag = 0;
          } 
          break;
    }
    
    delay(wait);
  }
}



void setup() {

  Serial.begin(9600);

  pinMode(M1A1, OUTPUT);
  pinMode(M1A2, OUTPUT);
  pinMode(M1B1, OUTPUT);
  pinMode(M1B2, OUTPUT);

  digitalWrite(M1A1, HIGH);
  digitalWrite(M1A2, LOW);
  digitalWrite(M1B1, LOW);
  digitalWrite(M1B2, LOW);

 //PrintWriter output;
  

}

void loop() {
  leitura=0;
  //Passo(4096,1);
  //delay(10000);
  if(Serial.available() > 0){
    leitura = Serial.parseFloat();
  }
  if(Serial.available() > 0){
    Serial.println(leitura);
  }
  passos = leitura * 4096 / 360;
  Passo(passos,1);
}
