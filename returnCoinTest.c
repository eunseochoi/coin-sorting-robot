
task main()
{
	motor[motorD] = 10;
	wait1Msec(1500);
	motor[motorD] = 0;

	while(!getButtonPress(buttonDown))
	{
		displayString(1, "Press DOWN BUTTON");
		displayString(2, "when every coin is returned");
	}

	eraseDisplay();

	while(getButtonPress(buttonDown))
	{}

	motor[motorD] = -10;
	wait1Msec(3000);
	motor[motorD] = 0;

	clearTimer(T1);
	while(time1[T1] < 5000)
	{
		displayString(1, "Thank you so much");
		displayString(2, "for using our machine!");
	}
	eraseDisplay();


}
