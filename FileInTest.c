
#include "EV3_FileIO.c"
task main()
{
	TFileHandle fin;
	bool fileOkay = openReadPC(fin, "cfile.txt");
	if(!fileOkay)
	{
		displayString(1, "cannot read the file");
		wait1Msec(3000);
		eraseDisplay();

	}
	int passwordMatch;
	readIntPC(fin, passwordMatch);
	closeFilePC(fin);

	if(passwordMatch == 0)
	{
		displayString(1, "%d", passwordMatch);
		wait1Msec(5000);
	}
	else
	{
		displayString(1, "%d", passwordMatch);
		wait1Msec(5000);
	}

}
