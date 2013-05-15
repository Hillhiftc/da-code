#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     IR,             sensorI2CCustom)
#pragma config(Sensor, S4,     IR2,            sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     Arm1,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Arm2,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Right1,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Right2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     none1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Arm3,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     Left1,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     Left2,         tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    leftright,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    updown,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    IRservo,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "hitechnic-irseeker-v2.h"
int power = 80;
bool moved = 0;

bool sideIR(void)
{
	int zones[5];
	HTIRS2readAllACStrength(IR, zones[0], zones[1], zones[2], zones[3], zones[4]);
	//clearDebugStream();
	//for(int i = 0; i < 5; i++)
	//	{
	//		writeDebugStreamLine("zone %d:\t%d", i, zones[i]);
	//	}
	return (zones[2] > 105 && zones[1] < 50);
}

bool frontIR(void)
{
	int zones[5];
	HTIRS2readAllACStrength(IR2, zones[0], zones[1], zones[2], zones[3], zones[4]);
	//clearDebugStream();
	//for(int i = 0; i < 5; i++)
	//	{
	//		writeDebugStreamLine("zone %d:\t%d", i, zones[i]);
	//	}
	return (zones[2] > 135);
}



void initializeRobot()
{



	return;
}

void moveForward(float tiles)
{
	nMotorEncoder[Right1] = 0;

	motor[Left1] = power;
	motor[Left2] = power;
	motor[Right1] = power;
	motor[Right2] = power;

	while(abs(nMotorEncoder[Right1]) < (tiles * 3600)){}
}

void moveBackward(float tiles)
{
	nMotorEncoder[Right1] = 0;

	motor[Left1] = -40;
	motor[Left2] = -40;
	motor[Right1] = -40;
	motor[Right2] = -40;

	while(abs(nMotorEncoder[Right1]) < (tiles * 3600)){}
}

void motorStop()
{
	motor[Left1] = 0;
	motor[Left2] = 0;
	motor[Right1] = 0;
	motor[Right2] = 0;
}

void armstop()
{

	motor[Arm2] = 0;

}

void turnRight()
{
	nMotorEncoder[Right1] = 0;
	motor[Left1] = power;
	motor[Left2] = power;
	motor[Right1] = -power;
	motor[Right2] = -power;

	while(abs(nMotorEncoder[Right1]) < 100){}
}


void turnLeft()
{
	nMotorEncoder[Right1] = 0;
	motor[Left1] = -power;
	motor[Left2] = -power;
	motor[Right1] = power;
	motor[Right2] = power;

	while(abs(nMotorEncoder[Right1]) < 925){}
}
void armup()
{


	motor[Arm2] = power;
	wait1Msec(2000);
}

//TASK MAIN TASK MAIN TASK MAIN TASK MAIN TASK MAIN
//TASK MAIN TASK MAIN TASK MAIN TASK MAIN TASK MAIN
//TASK MAIN TASK MAIN TASK MAIN TASK MAIN TASK MAIN
task main()
{

	initializeRobot();

	//waitForStart(); // Wait for the beginning of autonomous phase.

	servoChangeRate[IRservo]= 5;





	moveForward(0.5);
	motorStop();
	wait1Msec(500);

	motor[Arm1] = power;
	wait1Msec(1800);
	motor[Arm1] = 0;
	wait1Msec(20);

	servo[updown] = 250;
	servo[leftright]= 180;
	servo[IRservo] = 250;

	turnLeft();
	motorStop();
	wait1Msec(20);

	//Backing up
	moveBackward(0.25);
	motorStop();
	wait1Msec(20);

	ClearTimer(T1);

	while(!sideIR()){
		if(time1[T1] < 3000)
			moveForward(0.01);
		else
			motorStop();

	}

	if(sideIR()){
		PlaySound(soundBeepBeep);
	}

	moveForward(0.35);
	motorStop();
	wait1Msec(20);

	nMotorEncoder[Right1] = 0;
	while(!frontIR())
	{
		if(moved == 0)
		{
			motor[Left1] = power;
			motor[Left2] = power;
			motor[Right1] = -power;
			motor[Right2] = -power;

			if(abs(nMotorEncoder[Right1]) >= 3200 )
			{
				moveBackward(0.5);
				moved = true;
			}
		}
		else
		{
			motorStop();
		}

	}

	PlaySound(soundBeepBeep);

	nMotorEncoder[Right1] = 0;
	motor[Left1] = power/2;
	motor[Left2] = power/2;
	motor[Right1] = -power/2;
	motor[Right2] = -power/2;

	while(abs(nMotorEncoder[Right1]) < 100){}

	motorStop();
	wait1Msec(20);

	servo[IRservo] = 105;

	armup();
	armstop();

	motor[Arm1] = -power;
	wait1Msec(157.5);
	motor[Arm1] = 0;


	wait1Msec(500);

	nMotorEncoder[Right1] = 0;
	motor[Left1] = 30;
	motor[Left2] = 30;
	motor[Right1] = 30;
	motor[Right2] = 30;
	while(abs(nMotorEncoder[Right1]) < (0.95 * 3600)){}
	motorStop();
	servo[updown] = 198;
	wait1Msec(250);

	motor[Arm1] = -power;
	wait1Msec(300);
	motor[Arm1] = 0;
	wait1Msec(300);


	moveBackward(0.6);
	motorStop();


	motor[Arm2] = -power;
	wait1Msec(350);
	motor[Arm2] = 0;
	wait1Msec(20);

	motor[Arm1] = -power;
	wait1Msec(100);
	motor[Arm1] = 0;



	while (true)
	{}
}
