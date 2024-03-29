#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     Right,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Left,          tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{
	int LSpd;
	int RSpd;

	while(true)
	{
		getJoystickSettings(joystick);
		LSpd = joystick.joy1_y1;
		RSpd = joystick.joy1_y2;


		motor[Left] = LSpd > 10? LSpd : LSpd < -10? LSpd : 0;
		motor[Right] = RSpd > 10? RSpd : RSpd < -10? RSpd : 0;
	}


}
