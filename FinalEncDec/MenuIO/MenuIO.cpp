#include "MenuIO.h"

int getMenuChoice(string str1, string str2, string str3, string str4, string str5) {
	int choice;
	int args;

	do {
		args = 2;
		cout << "Please enter your choice:" << endl
			<< "1) " << str1 << endl
			<< "2) " << str2 << endl;
		if(str3.compare("") != 0) {
			cout << "3) " << str3 << endl;
			args++;
		}
		if(str4.compare("") != 0) {
			cout << "4) " << str4 << endl;
			args++;
		}
		if(str5.compare("") != 0) {
			cout << "5) " << str5 << endl;
			args++;
		}

		cout << "Your choice: ";
		cin >> choice;
		if(choice < 1 || choice > args) {
			cout << "Invalid input. Please try again." << endl << endl;
		}
	} while(choice < 1 || choice > args);

	return choice;
}