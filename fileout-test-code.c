#include "EV3_FileIO.c"
task main()
{
	TFileHandle fout;
	bool fileOkay = openWritePC(fout, "output.txt");
	if(!fileOkay)
	{
		displayString(0, "cannot output the file");
		wait1Msec(3000);
		eraseDisplay();
	}
	string sum = "sum";
	writeTextPC(fout, sum);
	closeFilePC(fout);

}
