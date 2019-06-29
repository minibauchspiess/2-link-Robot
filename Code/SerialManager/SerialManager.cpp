#include "SerialManager.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

SerialManager::SerialManager(int numDoSerial){
	Serial.begin(numDoSerial);
	Clear();
}

SerialManager::~SerialManager(){}

int SerialManager::ReadSerial(){
	if(Serial.available() != 0){
		//Create buffer with the size of bytes available to read
		int bufferSize = Serial.available();
		char buff[bufferSize];

		//Flags to help indicate if the message follows the pre-determined protocol
		int flagInit=-1, flagEnd=-1;

		//Pass all readings to buffer
		for(int i = 0; i<bufferSize; i++){
			buff[i] = (char)Serial.read();

			//Mark flag if begining of message was found
			if(buff[i] == '('){
				flagInit = i;
			}	//Else, mark if end was found
			else if(buff[i] == ')'){
				flagEnd = i;
			}
		}

		//Check if message is entirely inside (). Otherwise, discard reading
		if((flagInit == -1) || (flagEnd == -1)){
			return -1;
		}


		Clear();


		//In buffer, go through the message inside (), getting the needed information
		command = buff[flagInit+1];

		int indMarker = flagInit + 3;

		for(int i = flagInit+3; i <= flagEnd; i++){
			//Check if already went through one value
			if((buff[i] == ',') || (buff[i] == ')')){
				//Create auxiliar buffer to hold inside value as a char array
				char aux[i-indMarker];
				for(int j=0; j<(i-indMarker); j++){
					aux[j] = buff[indMarker + j];
				}

				//Convert it to float and update parameters register
				parameters[numParameters] = atof(aux);
				numParameters++;

				//Set marker to next position, to obtain next value
				indMarker = i + 1;
			}
		}



		return 1;
	}
	else{
		vTaskDelay(0.001);
		return 0;
	}

}

void SerialManager::Clear(){
	command = ' ';
	numParameters = 0;
	for(int i=0;i<4;i++){
		parameters[i] = 0;
	}
}

char SerialManager::GetCommand(){
	return command;
}

float SerialManager::GetAngle(int motor){
	if(motor == 1){
		return parameters[0];
	}
	else{
		if(numParameters == 4){
			return parameters[2];
		}
		else{
			return parameters[1];
		}
	}
}


float SerialManager::GetSpeed(int motor){
	if(numParameters <= 2){
		return DEFAULT_SPEED;
	}
	else if(numParameters == 3){
		return parameters[2];
	}
	else{
		if(motor == 1){
			return parameters[1];
		}
		else{
			return parameters[3];
		}
	}
}

float SerialManager::GetTime(){
	if(numParameters == 3){
		return parameters[2];
	}
	else{
		return DEFAULT_TIME;
	}
}



float SerialManager::GetParameter(int param){
	return parameters[param];
}


int SerialManager::GetNumParams(){
	return numParameters;
}