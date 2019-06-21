#ifndef LINKCLASS_H
#define LINKCLASS_H

#define START_SPEED 1

class LinkClass{

public:
	LinkClass(int coil[], int numSteps=8, float resolution=360.0/4096.0, float maxSpeed=110, float acel=80);
	~LinkClass();

	void ExecuteStep(int step);

	void GoToDeg(float destDeg, float speed);		//Go to destination angle with the given speed. Speed given in deg/s

	float GetAngle();

private:
	int coil[4];

	int numSteps;
	int step;
	float angleDeg;
	float resolution;
	
	float maxSpeed;
	float acel;
};

#endif