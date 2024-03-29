s#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     IR,             sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     Arm1,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Arm2,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Right1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     Right2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     none1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Arm3,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     Left2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     Left1,         tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    leftright,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    updown,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    IRservo,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//													 Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition
//
// You need to customize two functions with code unique to your specific robot
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"	 //Include file to "handle" the Bluetooth messages
#include "hitechnic-irseeker-v2.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//																		initializeRobot
//
// Prior to the start of tele-op mode you may want to perform some initialization on your robot
// and the variables within your program
//
// In most cases you may not have to add any code to this function and it will remain "empty"
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
	// Place code here to sinitialize servos to starting positions
	// Sensors are automatically configured and setup by ROBOTC They may need a brief time to stabilize

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//																				 Main Task
//
// The following is the main code for the tele-op robot operation Customize as appropriate for
// your specific robot
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot Most tele-op programs will follow the following
// logic:
//	 1 Loop forever repeating the following actions:
//	 2 Get the latest game controller / joystick settings that have been received from the PC
//	 3 Perform appropriate actions based on the joystick + buttons settings This is usually a
//			simple action:
//			*	 Joystick values are usually directly translated into power levels for a motor or
//				 position of a servo
//			*	 Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//				 position
//	 4 Repeat the loop
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings
//
// At the end of the tele-op period the FMS will autonmatically abort (stop) execution of the program
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
bool bAtBeacon(void)
	{
		int zones[5];
		HTIRS2readAllACStrength(IR, zones[0], zones[1], zones[2], zones[3], zones[4]);
		clearDebugStream();
		for(int i = 0; i < 5; i++)
			{
				writeDebugStreamLine("zone %d:\t%d", i, zones[i]);
			}
		return ((zones[1] > 50) && (zones[2] > 50) && (abs(zones[1] - zones[2]) < 10));
	}

task main()
{
	//**************************************
	//Inital setup
	//**************************************
	//Setup Static Variables
	//Max Servo Angles
	int maxDown = 250;
	int maxUp = 198;
	float maxLeft = 230.0;
	float maxRight = 30.0;
	//Arm Speeds
	int a1dnpwr = 10;
	int a1tbpwr = 100;
	int a2dnpwr = 10;
	int a2tbpwr = 100;
	int a3dnpwr = 10;
	int a3tbpwr = 100;
	//Joystick Deadzone
	int deadzone = 15;
	//Servo starting positions
	float currentLR = 170.0;
	int currentUD = maxDown;
	//Wheel speed
	//**************************************
	//End Inital setup
	//**************************************

	initializeRobot();

	//waitForStart();		// wait for start of tele-op phase

	while (true)
	{

		servo[IRservo] = 200;
		///////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////
		////																									 ////
		////			Add your robot specific tele-op code here		////
		////																									 ////
		///////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////
		//**************************************
		//Define control buttons
		//**************************************
		//Sets Joystick1 button 1 to control Arm 1 going up
		getJoystickSettings(joystick); // Get Joystick Variables
		int a1upcon = joy2Btn(6);//defines liftarm controls
		int a1dncon = joy2Btn(8);
		int a2upcon = joy2Btn(5);
		int a2dncon = joy2Btn(7);
		int a3con = joystick.joy2_TopHat;

		int y1 = joystick.joy2_y1; //Motor Left
		int y2 = joystick.joy2_y2; //Motor Right
    int lrleft = joy2Btn(1);//Servo LR Left
		int lrright = joy2Btn(3);//Servo LR Right
		int udtoggle = joy2Btn(4);//Servo UD up
		int lrpwrdwn = joy2Btn(2);
		//**************************************
		//End Button Controls
		//**************************************
		//**************************************
		//Process Start
		//**************************************
		//Arm Control Start
		motor[Arm1] = a1upcon == true ? a1tbpwr : a1dncon == true ? -a1dnpwr : 0;
		motor[Arm2] = a2upcon == true ? a2tbpwr : a2dncon == true ? -a2dnpwr : 0;
		motor[Arm3] = a3con == 0 ? a3tbpwr : a3con == 4 ? -a3dnpwr : 0;
		//Arm Control end
		if (lrpwrdwn == true)
		{
			servoChangeRate[leftright] = 0;
		}
		else
		{
			servoChangeRate[leftright] = 20;
		}
		//Tank Drive start
		motor[Left1] = y1 > deadzone ? y1 : y1 < -deadzone ? y1/2 : 0;
		motor[Right1] = y2 > deadzone ? y2 : y2 < -deadzone ? y2/2 : 0;
		motor[Left2] = y1 > deadzone ? y1 : y1 < -deadzone ? y1/2 : 0;
		motor[Right2] = y2 > deadzone ? y2 : y2 < -deadzone ? y2/2 : 0;
		//Tank Drive end

		//LR Servo Control Start
		if(lrleft == true && time1[T1] >= 10)
		{
			if(currentLR < maxLeft)
			{
				currentLR = currentLR + 01;
			}
			servo[leftright] = (int) currentLR;	 //when button 0 (labeled as 1) is pushed move servo to left position
			ClearTimer(T1);
		}
		else if(lrright == true && time1[T1] >= 10)
		{
			if(currentLR > maxRight)
			{
				currentLR = currentLR - 01;
			}
			servo[leftright] = (int) currentLR;	 //when button 2 (labeled as 3) is pushed move servo to right position
			ClearTimer(T1);
		}
		//LR Servo Control End

		//UD Servo Control Start
		if (udtoggle == 1 && time1[T2] >= 500)//When the tip control button is pressed
		{
			if (currentUD == maxDown) //If the number of times tip has been pressed is even then
			{
				currentUD = maxUp;//set updown servo to the down(flat) position
			}
			else
			{
				currentUD = maxDown;//set updown servo to the up(tilted) position
			}
			ClearTimer(T2);
		}
		servo[updown] = currentUD;

		//UD Servo Control End
		if(bAtBeacon())
			PlaySound(soundBeepBeep);


		// Insert code to have servos and motors respond to joystick and button values

		// Look in the ROBOTC samples folder for programs that may be similar to what you want to perform
		// You may be able to find "snippets" of code that are similar to the functions that you want to
		// perform
	}
}
