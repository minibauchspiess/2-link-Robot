#ifndef LINKCLASS_H
#define LINKCLASS_H

#define START_SPEED 1
#define HOMESPEEDFAST 30
#define HOMESPEEDSLOW 5

class LinkClass{

public:
	LinkClass(int coil[], int bumper, int numSteps=8, float resolution=360.0/4096.0, float maxSpeed=110, float acel=80);
	~LinkClass();

	void ExecuteStep(int step);

	void StepDir(int dir);

	void GoToDeg(float destDeg, float speed);		//Go to destination angle with the given speed. Speed given in deg/s

	void Home(float initAngle=0);

	float GetAngle();

	//void phase4(int motor, float destDeg, LinkClass *otherLink, float speedx, float speedy);
	//float CalculatePhase4Speed(float x, float y, float theta1, float theta2, int linkNum, LinkClass *otherLink);

private:
	int coil[4];

	int bumper;

	int numSteps;
	int step;
	float angleDeg;
	float resolution;
	
	float maxSpeed;
	float acel;
};

#endif