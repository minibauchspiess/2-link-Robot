#include "LinkClass.h"
#include "Arduino.h"
#include <Arduino_FreeRTOS.h>

LinkClass::LinkClass(int coil[], int bumper, int numSteps, float resolution, float maxSpeed, float acel){
	//Start outputs in arduino that activate the step motor coils
	this->coil[0] = coil[0];
	this->coil[1] = coil[1];
	this->coil[2] = coil[2];
	this->coil[3] = coil[3];

	//Set bumper input (to identify initial position)
	this->bumper = bumper;
	pinMode(bumper, INPUT_PULLUP);

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
	angleDeg = angleDeg - ((float)dir)*resolution;

	//Keep it in the range of [0,360]
	if(angleDeg >= 360){
		angleDeg = angleDeg - 360;
	}
	else if(angleDeg < 0){
		angleDeg = angleDeg + 360;
	}
}


void LinkClass::StepDir(int dir){
	//Invert direction (+1 is direction counter-clockwise, but motor uses steps clockwise as positive)
	int nxtStep = step - dir;
	if(nxtStep>7){
		nxtStep = nxtStep - 8;
	}
	else if(nxtStep<0){
		nxtStep = nxtStep + 8;
	}
	ExecuteStep(nxtStep);
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
		if((destDeg-angleDeg) < ((angleDeg+360) - destDeg)){
			dir = 1;		//Go counter-clockwise
		}
		else{
			dir = -1;		//Go clockwise
		}
	}
	else{
		if((angleDeg-destDeg) < ((destDeg+360) - angleDeg)){
			dir = -1;		//Go clockwise
		}
		else{
			dir = 1;		//Go counter-clockwise
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
		
		vTaskDelay( 0 );

		currentTime = micros();
		dt = currentTime - lastUpdate;

		if(dt > (int)((1000000 * resolution)/currentSpeed)){
			lastUpdate = currentTime;
			StepDir(dir);
		}
	}
}

void LinkClass::Home(float initAngle){

	float speed = HOMESPEEDFAST;
	long currentTime = 0;
	long lastUpdate = 0;
	int dt;
	//Execute steps until reaches bumper, at normal speed
	while(digitalRead(bumper)){
		vTaskDelay(0);
		currentTime = micros();
		dt = currentTime - lastUpdate;

		if(dt > (int)((1000000 * resolution)/speed)){
			lastUpdate = currentTime;
			StepDir(1);
		}
	}

	//Set initial angle in given position
	angleDeg = initAngle;
}


float LinkClass::GetAngle(){
	return angleDeg;
}


/*float LinkClass::CalculatePhase4Speed(float x, float y, int linkNum, LinkClass *otherLink){

}*/