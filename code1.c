float const nickelDim = 146;
float const quarterDim = 127;
float const loonieDim = 110;
float const fullDim = 294;

int const TOL = 3;

#include "EV3_FileIO.c"

float getDiameter()
{
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Color_Color;
	wait1Msec(50);

	float diameter = 0;

	nMotorEncoder(motorB) = 0;

	while(SensorValue[S2] != (int)colorBlack && SensorValue[S1] == 0)
		motor[motorB] = 10;

	motor[motorB] = 0;
	diameter = nMotorEncoder(motorB); //get diameter for each coin
	wait1Msec(500);

	motor[motorB] = -10; //actuator goes back to original place
	while(nMotorEncoder(motorB) > 0)
	{}
	motor[motorB] = 0;

	return diameter;
}

void moveRamp()
{
	clearTimer(T1);
	while(time1[T1] < 500)
		motor[motorC] = 7;

	motor[motorC] = 0;
	wait1Msec(1000);

	clearTimer(T1);
	while(time1[T1] < 700)
		motor[motorC] = -7;

	motor[motorC] = 0;
	wait1Msec(500);
}


void getUserInput()
{
	while(!getButtonPress(buttonRight) && !getButtonPress(buttonLeft))
	{
		displayString(1,"Look at the computer");
		displayString(2, "Enter the password");
	}
	eraseDisplay();
}

float calculateSum(int nickel, int dime, int quarter, int loonie, int toonie)
{
	float sum = 0;
	sum = nickel * 0.05 + dime * 0.1 + quarter *0.25 + loonie + toonie * 2;
	return sum;
}

void outputInfo(int nickel, int dime, int quarter, int loonie, int toonie, int totalCount, float sum)
{
	clearTimer(T1);
	while(time1[T1] < 8000)
	{
		displayString(1, "SUM: CA$: %.2f", sum);
		displayString(2, "Nickel Count: %d", nickel);
		displayString(3, "Dime Count: %d", dime);
		displayString(4, "Quarter Count: %d", quarter);
		displayString(5, "Loonie Count: %d", loonie);
		displayString(6, "Toonie Count: %d", toonie);
	}
	eraseDisplay();
}


task main()
{
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Color_Color;
	wait1Msec(50);

	int nickel = 0;
	int dime = 0;
	int quarter = 0;
	int loonie = 0;
	int toonie = 0;
	int totalCount = 0;

	while(!getButtonPress(buttonUp))
		displayString(1, "Press UP Button To Start");
	eraseDisplay();

	clearTimer(T1);
	while(time1[T1] < 5000)
	{
		displayString(2, "*****DIRECTIONS*****");
		displayString(3, "Enter a coin every 5 seconds");
		displayString(4, "Press ENTER when it is done.");
	}
	eraseDisplay();

	while(!getButtonPress(buttonEnter))
	{
		displayString(1, "ENTER COIN NOW");
		displayString(2, "Once you're done,");
		displayString(3, "Press ENTER for 2 seconds.");
		float diameter = getDiameter();

		if(diameter == 0)
		{}
		else if(abs(diameter - nickelDim) <= TOL)
		{
			nickel ++;
			totalCount ++;
			moveRamp();
		}
		else if (diameter >= (nickelDim + TOL) && diameter <= (fullDim - TOL))
		{
			dime ++;
			totalCount ++;
			moveRamp();
		}
		else if (abs(diameter - quarterDim) <= TOL)
		{
			quarter ++;
			totalCount ++;
			moveRamp();
		}
		else if (abs(diameter - loonieDim) <= TOL+1)
		{
			loonie ++;
			totalCount ++;
			moveRamp();
		}
		else if (diameter <= (loonieDim - TOL))
		{
			toonie ++;
			totalCount ++;
			moveRamp();
		}

		else if (abs(diameter - fullDim) <= TOL)
		{
			while(!getButtonPress(buttonAny))
			{
				displayString(1,"ERROR GETTING A DIAMETER");
				displayString(2,"DO NOT TOUCH ANYTHING");
			}
			eraseDisplay();
			while(getButtonPress(buttonAny))
			{}
		}
	}
	eraseDisplay();
	while(getButtonPress(buttonEnter))
	{}

	float sum = calculateSum(nickel, dime, quarter, loonie, toonie);
	if(totalCount != 0)
		outputInfo(nickel, dime, quarter, loonie, toonie, totalCount, sum);
	else
	{
		displayString(1, "You didn't insert any coins");
		wait1Msec(3000);
		eraseDisplay();
	}
	getUserInput();
}
