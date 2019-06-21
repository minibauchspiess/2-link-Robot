

#ifndef LINKCLASS_H
#define LINKCLASS_H

class LinkClass{

public:
	LinkClass(int coil[]);
	~LinkClass();

	void ExecuteStep(int step, int delayM);

	//void ShowCoils();

	int RetMotor(int m);

private:
	int coil[4];
	int numSteps;

	int step;
};

#endif