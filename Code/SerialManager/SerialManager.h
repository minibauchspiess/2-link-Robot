
/*************************************************************************************************************************/
//	Class used to manage the inputs from the serial port
//	Every message start with the commands '0', '1', '2', '3' or '4', where:
//		- '0' commands motors to go to the initial position. No aditional parameters are needed
//		- '1' executes phase 1: the two motors go to the respective angle, at a constant speed and in different momments. Aditional parameters:
//				* motors final angles
//				* speed of the motors (if one parameter is passed, both motors move at the same speed. If none are passed, they move at a default speed)
//		- '2' executes phase 2: both motors go to the desired angle at the same speed and same time. Aditional parameters:
//				* motors final angles
//				* speed of both motors. If no argument is passed, default speed is aplied
//		- '3' executes phase 3: both motors go to the desired angle at the same time and ariving at the same time (with proportional speeds). Aditional parameters:
//				* motors final angles
//				* time for both motors to arrive at desired angle. If no parameters passed, default time is used
//		- '4' executes phase 4: both motors move in a variable speed, so that the end of the second link executes a linear movement. Aditional parameters:
//				* motor final angles
//				
//
//	Available commands:
//		- (0);
//
//		- (1,dgm1,spm1,dgm2,spm2)
//				* dgm1: angle of motor 1;
//				* spm1: speed of motor 1 (in degrees/second);
//				* dgm2: angle of motor 2;
//				* spm2: speed of motor 2;
//
//		- (1,dgm1,dgm2,sp)
//				* sp: speed (for both motors)
//				
//		- (1,dgm1,dgm2)
//
//
//		- (2,dgm1,dgm2,sp)
//
//		- (2,dgm1,dgm2)
//
//		- (3,dgm1,dgm2,t)
//
//		- (3,dgm1,dgm2)

/**************************************************************************************************************************/


class SerialManager
{
public:
	SerialManager(int numDoSerial = 9600);
	~SerialManager();

	int ReadSerial();
	void Clear();

	char GetCommand();

	float GetParameter(int param);
	int GetNumParams();


private:
	char command;
	float parameters[4];
	int numParameters;
	
};
