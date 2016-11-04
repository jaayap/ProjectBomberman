#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
	printf("Welcome to the serial test app!\n\n");

	Serial* SP = new Serial("COM3");    // adjust as needed - port com

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	
	int dataLength = 256;
	int readResult = 0;
	bool mort = false;
	bool pause = false;
	Sleep(500);

	while(SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData,dataLength);//on lit les infos de l'arduino
		
		if(readResult != -1){ //on lit les données
		/*	if (incomingData[0] == '0'){
				printf("\n bouclier");	
				SP->WriteData("b", 0);
				Sleep(150);
			}
			else if (incomingData[0] == '1'){ //on appuie sur le bouton
				printf("\n Laser");
				SP->WriteData("l", 1);
				Sleep(150);
			}*/

			if (incomingData[0] == 'A') { //on appuie sur le bouton
				printf("\n BombeButton");
				//SP->WriteData("a", 1); 
				Sleep(150);
			}
			else if (incomingData[0] == 'B') { //on appuie sur le bouton
				printf("\n BonusButton");
				//SP->WriteData("b", 1);
				
				Sleep(150);
			}
			else if (incomingData[0] == 'C') { //on appuie sur le bouton
				if (pause) {
					printf("\n Play");
					pause = false;
				}
				else {
					printf("\n Pause");
					pause = true;
				}
											 
				//SP->WriteData("B", 1);

				Sleep(150);
			}

			//JOYSTICK	
			if (incomingData[0] == 'X') {
				printf("\n BAS");
			}
			else if (incomingData[0] == 'H') {
				printf("\n HAUT");
			}
			else if (incomingData[0] == 'G') {
				printf("\n GAUCHE");
			}
			else if (incomingData[0] == 'D') {
				printf("\n DROITE");
			}
		}

		//on envoit des données
		if (mort) {
			SP->WriteData("a", 1);//allume la led 5
			Sleep(150);
		}
		else {
			SP->WriteData("b", 1);//etein la led 5
			Sleep(150);
		}

	}
	return 0;
}
