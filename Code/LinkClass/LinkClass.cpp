#include "LinkClass.h"
#include "Arduino.h"

LinkClass::LinkClass(int coil[]){
	//Start outputs in arduino that activate the step motor coils
	this->coil[0] = coil[0];
	this->coil[1] = coil[1];
	this->coil[2] = coil[2];
	this->coil[3] = coil[3];

	//The number of steps iterations depends if motor moves with full steps or half steps
	numSteps = 8;

	//Set current step to initial step
	step = 0;

	//Set motor to initial position
	/**/pinMode(coil[0], OUTPUT);
	pinMode(coil[1], OUTPUT);
	pinMode(coil[2], OUTPUT);
	pinMode(coil[3], OUTPUT);

	digitalWrite(coil[0], HIGH);
	digitalWrite(coil[1], LOW);
	digitalWrite(coil[2], LOW);
	digitalWrite(coil[3], LOW);
}

LinkClass::~LinkClass(){}


void LinkClass::ExecuteStep(int step, int delayM){
	//Check direction of rotation
	int dir = step - this->step;
	if(abs(dir) == (numSteps-1)){
		dir = -dir/(numSteps-1);
	}

	//Check main coil to be active, and the number of coils actives in this step (1 or 2)
	int mainCoil = step/2;
	int numCoils = (step%2) + 1;

	//Knowing the rotation direction, main coil to activate and if next coil needs to be active, activate the correct coils
	if(numCoils == 1){
		if((mainCoil == 0) && (dir == 1)) mainCoil = 4;		//To fix the looping problem in the vector

		digitalWrite(coil[mainCoil-dir], LOW);			//Set last coil to LOW
		/*Serial.print("Bobina ");
		Serial.print((mainCoil-dir));
		Serial.println("Setada para LOW");*/
	}
	else{		//numCoils == 2
		digitalWrite(coil[(mainCoil + (dir+1)/2) % 4], HIGH);
		/*Serial.print("Bobina ");
		Serial.print(((mainCoil + (dir+1)/2) % 4));
		Serial.println("Setada para HIGH");*/
	}

	this->step = step;

	delayMicroseconds(delayM);
}
/*
void LinkClass::ShowCoils(){
	//Serial.begin(9600);
	Serial.print("Bobina 1: ");
	Serial.print("Bobina 1: ");
}
*/
int LinkClass::RetMotor(int m){
	return 0;
}