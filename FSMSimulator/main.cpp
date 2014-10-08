
#include <iostream>

#include "MFSMParser.h"
#include "GeneralParser.h"


using namespace std;

int main(){

	string filename;
	char _char;

	do {
		cout << "Please enter the mfsm or fsm file path> ";
		//
		//filename = "samples/mFsmOne.mfsm";//
		cin >> filename;
		GeneralParser parser(filename,cout,cin);
		if ( parser.is_fsm() ){
			FSMParser parser(filename,cout,cin,false);
			FSM *fsm = parser.parse_file(NULL);
			fsm->execute();
			delete fsm;
		} else {
			MFSMParser parser(filename,cout,cin);
			MFSM *mfsm = parser.parse_file();
			mfsm->execute();
			delete mfsm;
		}
		cout << "Would you like to enter another fsm/mfsm name (y/N): ";
		cin >> _char;
	} while ( tolower(_char) == 'y' ); 


	system("pause");
	return 0;
}

