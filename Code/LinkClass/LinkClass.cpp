#include "LinkClass.h"
#include "Arduino.h"

LinkClass::LinkClass(int coil[], int numSteps, float resolution, float maxSpeed, float acel){
	//Start outputs in arduino that activate the step motor coils
	this->coil[0] = coil[0];
	this->coil[1] = coil[1];
	this->coil[2] = coil[2];
	this->coil[3] = coil[3];

	//The number of steps iterations depends if motor moves with full steps or half steps
	this->numSteps = numSteps;

	//Set current step to initial step
	step = 0;

	//Set motor to initial position
	pinMode(coil[0], OUTPUT);
	pinMode(coil[1], OUTPUT);
	pinMode(coil[2], OUTPUT);
	pinMode(coil[3], OUTPUT);

	digitalWrite(coil[0], HIGH);
	digitalWrite(coil[1], LOW);
	digitalWrite(coil[2], LOW);
	digitalWrite(coil[3], LOW);


	//Set initial angle to 0
	angleDeg = 0;

	//Set resolution
	this->resolution = resolution;

	//Set motor max speed (beyond that, motor can't follow every steps)
	this->maxSpeed = maxSpeed;

	//Set motor aceleration (for smooth start and stop)
	this->acel = acel;
}

LinkClass::~LinkClass(){}


void LinkClass::ExecuteStep(int step){
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

		digitalWrite(coil[(mainCoil-dir) % 4], LOW);			//Set last coil to LOW
	}
	else{		//numCoils == 2
		digitalWrite(coil[(mainCoil + (dir+1)/2) % 4], HIGH);
	}

	//Update current step
	this->step = step;

	//Update current orientation
	angleDeg = angleDeg + ((float)dir)*resolution;

	//Keep it in the range of [0,360]
	if(angleDeg >= 360){
		angleDeg = angleDeg - 360;
	}
	else if(angleDeg < 0){
		angleDeg = angleDeg + 360;
	}
}


void LinkClass::GoToDeg(float destDeg, float speed){

	//Take only angles in the range [0,360[
	while(destDeg < 0){
		destDeg = destDeg + 360;
	}
	while(destDeg >= 360){
		destDeg = destDeg - 360;
	}


	//Check wich direction is closest to the angle
	int dir;
	if(destDeg > angleDeg){
		if((destDeg-angleDeg) > ((angleDeg+360) - destDeg)){
			dir = -1;		//Go clockwise
		}
		else{
			dir = 1;		//Go counter-clockwise
		}
	}
	else{
		if((angleDeg-destDeg) > ((destDeg+360) - angleDeg)){
			dir = 1;		//Go forward
		}
		else{
			dir = -1;		//Go backwards
		}
	}


	//Avoid speed to be above motor limit
	if(speed > maxSpeed) speed = maxSpeed;

	long currentTime = 0;
	long lastUpdate = 0;
	int dt;
	float currentSpeed = speed;

	//Execute steps until reaches position
	while(abs(destDeg - angleDeg) >= resolution){			// 360/4096 is the resolution of each step. After the distance to desired angle is less than the resolution, stop iterations
		
		currentTime = micros();
		dt = currentTime - lastUpdate;

		if(dt > (int)((1000000 * resolution)/currentSpeed)){
			lastUpdate = currentTime;
			ExecuteStep(((step+dir+numSteps) % numSteps));
		}

		//Calculate next speed, given the time passed and acceleration
		/*if(currentSpeed < speed){
			currentSpeed = currentSpeed + acel*delayM;
			if(currentSpeed > speed){
				currentSpeed = speed;
			}
		}*/
	}
}


float LinkClass::GetAngle(){
	return angleDeg;
}