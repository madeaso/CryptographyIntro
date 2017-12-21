#include "FinalEncDec.h"

using namespace std;

int main() {
	int selection;
	string str, dict;

	selection = getMenuChoice("Encrypt text.", "Decrypt text.");

	if(selection == 1) {
		// Executes if user wants to encrypt text.
		cout << endl << "You have chosen to encrypt text. What are you trying to hide?" << endl << endl;
		selection = getMenuChoice("Input from keyboard.", "Input from text file");
		if(selection == 1) {
			cout << endl << "Please enter the text you would like to encrypt:" << endl;
			cin.ignore();
			getline(cin, str);
			Encrypter enc(str);
			enc.encryptText();
			cout << endl << "Here is your encrypted text:" << endl << enc.getEncText() << endl << endl;
		}
		else if(selection == 2) {
			cout << "Please enter the qualified path of the text file you would like to encrypt:" << endl;
			cin.ignore();
			getline(cin, str);
			Encrypter enc(str);
			enc.encryptFile();
			cout << endl << "Your encrypted text has been written to:" << endl << enc.getEncText() << endl << endl;
		}
		selection = 1;
	}

	else if(selection == 2) {
		//Executes if user wants to decrypt text.
		cout << endl << "You have chosen to decrypt text. What are you trying to find?" << endl << endl;

		cout << endl << "Which dictionary would you like to use for statistical comparisons?" << endl;
		selection = getMenuChoice("DictionaryWords.txt (slower)", "PopularWords.txt (faster)");
		if(selection == 1)
			dict = "DictionaryWords.txt";
		else
			dict = "PopularWords.txt";

		Decrypter dec(dict);
		dec.decryptText();
	}
	selection = 2;
	system("PAUSE");
	return 0;
}