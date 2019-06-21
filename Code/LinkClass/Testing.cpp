#include "LinkClass.h"
#include <iostream>

using namespace std;




int main(int argc, char const *argv[])
{
	int m1[4] = {2,3,4,5};
	LinkClass link1 = LinkClass(m1, 0.5);

	cout<<link1.RetMotor(1)<<endl;

	return 0;
}