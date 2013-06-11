#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          Claw,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Wheel1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     Wheel2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     Wheel4,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     Wheel3,        tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    W2Servo,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    W1Servo,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    W3Servo,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    W4Servo,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)

#include "JoystickDriver.c"

//char tophat = joystick.joy1_TopHat;


task main()
{
	//ClearTimer(T1);
	while(true)                        // infinite loop:
	{
	  getJoystickSettings(joystick);     // update buttons and joysticks

	  if(joy1Btn(3) == 1)      // if the topmost button on joy1's D-Pad ('TopHat') is pressed:
	  {
	  	while(true){
	    PlaySound(soundBeepBeep);
	  }
	  }
	  else
	  {
	  	ClearSounds();
	  }
	}
}
