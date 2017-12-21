#include "Cyphers.h"
#include <fstream>
#include <sstream>
const int MAX_SWAPS = 100;

Encrypter::Encrypter(string str) {
	this->userIn = str;
}

void Encrypter::encryptText() {
	int selection;
	int shft;

	cout << endl << "Which type of cypher would you like to use?" << endl;
	selection = getMenuChoice("Shift cypher.", "Substitution cypher.");
	if(selection == 1) {
		cout << endl << "Please enter the amount of shift for the characters: ";
		cin >> shft;

		encText = shift(userIn, shft);
		
	}
	else if(selection == 2) {
		encText = sub(userIn);
	}
}

void Encrypter::encryptFile() {
	fstream file;
	string line, temp;
	int selection;
	int shft;

	this->fileName = this->userIn;
	this->userIn = "";
	
	file.open(fileName, fstream::in);
	if(file.fail()) {
		this->encText = "ERROR: File could not be opened.";
		return;
	}
	this->encText = fileName.substr(0, fileName.length() - 4) + "_enc.txt";

	while(!file.eof()) {
		getline(file, line);
		line += '\n';
		userIn += line;
	}

	file.close();
	file.open(encText, fstream::out);
	
	cout << endl << "Which type of cypher would you like to use?" << endl;
	selection = getMenuChoice("Shift cypher.", "Substitution cypher.");
	if(selection == 1) {
		cout << endl << "Please enter the amount of shift for the characters: ";
		cin >> shft;

		file << shift(userIn, shft);
	}
	else if(selection == 2) {
		file << sub(userIn);
	}
	file.close();
}

string Encrypter::shift(string str, int shift) {
	string enc;

	for(int i = 0; i < str.length(); i++) {
		if(str[i] >= 65 && str[i] <= 90) {
			enc += ((str[i] + shift) % 91);
			if(enc[i] < 65)
				enc[i] += 65;
		}
		else if(str[i] >= 97 && str[i] <= 122) {
			enc += ((str[i] + shift) % 123);
			if(enc[i] < 97)
				enc[i] += 97;
		}
		else {
			enc += str[i];
		}
	}
	return enc;
}

string Encrypter::sub(string str) {
	string enc;

	for(int i = 0; i < str.length(); i++) {
		switch(str[i]) {
		case 'A': enc += 'B'; break; case 'a': enc += 'b'; break;
		case 'B': enc += 'E'; break; case 'b': enc += 'e'; break;
		case 'C': enc += 'I'; break; case 'c': enc += 'i'; break;
		case 'D': enc += 'N'; break; case 'd': enc += 'n'; break;
		case 'E': enc += 'O'; break; case 'e': enc += 'o'; break;
		case 'F': enc += 'A'; break; case 'f': enc += 'a'; break;
		case 'G': enc += 'H'; break; case 'g': enc += 'h'; break;
		case 'H': enc += 'X'; break; case 'h': enc += 'x'; break;
		case 'I': enc += 'D'; break; case 'i': enc += 'd'; break;
		case 'J': enc += 'T'; break; case 'j': enc += 't'; break;
		case 'K': enc += 'Z'; break; case 'k': enc += 'z'; break;
		case 'L': enc += 'F'; break; case 'l': enc += 'f'; break;
		case 'M': enc += 'W'; break; case 'm': enc += 'w'; break;
		case 'N': enc += 'S'; break; case 'n': enc += 's'; break;
		case 'O': enc += 'L'; break; case 'o': enc += 'l'; break;
		case 'P': enc += 'G'; break; case 'p': enc += 'g'; break;
		case 'Q': enc += 'R'; break; case 'q': enc += 'r'; break;
		case 'R': enc += 'P'; break; case 'r': enc += 'p'; break;
		case 'S': enc += 'C'; break; case 's': enc += 'c'; break;
		case 'T': enc += 'U'; break; case 't': enc += 'u'; break;
		case 'U': enc += 'Q'; break; case 'u': enc += 'q'; break;
		case 'V': enc += 'J'; break; case 'v': enc += 'j'; break;
		case 'W': enc += 'V'; break; case 'w': enc += 'v'; break;
		case 'X': enc += 'Y'; break; case 'x': enc += 'y'; break;
		case 'Y': enc += 'K'; break; case 'y': enc += 'k'; break;
		case 'Z': enc += 'M'; break; case 'z': enc += 'm'; break;
		default: enc += str[i];
		}
	}

	return enc;
}

Decrypter::Decrypter(string dict) {
	this->dictFile = dict;
}

void Decrypter::decryptText() {
	int selection, lines = 0, lineCount, low, high, sort, index = 0, temp, lowIndex, highIndex, stack = 0;
	int count[26];
	double strPerc[26], dictPerc[26];
	string encStr, dictStr, line, inFilePath, outFilePath;
	bool test;
	fstream file;
	char swaps[MAX_SWAPS][2], alpha[26];
	char dictCount[26] = {'E', 'I', 'A', 'O', 'R', 'N',
					  'T', 'S', 'L', 'C', 'U', 'P',
					  'M', 'D', 'H', 'Y', 'G', 'B',
					  'F', 'V', 'K', 'W', 'Z', 'X',
					  'Q', 'J'};
	
	cout << "*** Manual Decryption Tool ***" << endl << endl;
	do {	
		cout	<< "Please enter your selection for the source of encrypted text:" << endl
			<< "1) Enter encrypted text from keyboard" << endl
			<< "2) Use text from a txt file" << endl;
		cin >> selection;
		cin.ignore();

		if(selection == 1 || selection == 2) {
			test = true;
		}
		else {
			test = false;
			cout << "Invalid input." << endl;
		}
	} while(!test);

	if(selection == 1) {
		cout << "Please enter encrypted text, terminated by pressing [enter]:" << endl;
		getline(cin, encStr);
	}
	else {
		cout << "Please enter name/path of file to be read:" << endl;
		getline(cin, inFilePath);
		
		file.open(inFilePath, ios::in);
		if(file) {
			cout << "File opened successfully!" << endl << endl;
			
			while(!file.eof()) {
				getline(file, line);
				line += '\n';
				encStr += line;
				lines++;
			}
			file.close();
		}
		else {
			cout << "File failed to open. Please try again." << endl;
			system("PAUSE");
			return;
		}

		if(lines > 20) {
			cout << "Your encrypted text contains " << lines << " lines." << endl
				<< "Please enter a range of lines from 1 to " << lines << " in ascending order." << endl
				<< "[Example: 5 13]: ";
			cin >> low >> high;
			cin.ignore();

			lineCount = 1;
			lowIndex = 0;
			highIndex = 0;

			for(int i = 0 ; i < encStr.length(); i++)
			{
				if(encStr[i] == '\n') {
					lineCount++;
					if(lineCount == low) {
						lowIndex = i + 1;	
					}
					if(lineCount - 1 == high) {
						highIndex = i + 1;
					}
				}				
			}

			encStr = encStr.substr(lowIndex, highIndex - lowIndex);
		}
	}

	cout << "\nHere is your encrypted text:\n" << encStr << endl << endl;

	for(int i = 0; i < 26; i++) {
		alpha[i] = i + 65;
	}
	for(int i = 0; i < 26; i++) {
		count[i] = 0;
	}

	for(int i = 0 ; i < encStr.length(); i++) {
		//increases the count for each character read in,
		//both lowercase and uppercase are counted.
		if(encStr[i] >= 65 && encStr[i] <= 90) {
			count[encStr[i] - 65]++;
		}
		else if(encStr[i] >= 97 && encStr[i] <= 122) {
			count[encStr[i] - 97]++;
		}
	}

	for(int i = 0; i < 25; i++) {
		sort = count[i];
		for(int cnt = i + 1; cnt < 26; cnt++) {
			if(sort < count[cnt]) {
				sort = count[cnt];
				index = cnt;
			}
		}
		temp = count[i];
		count[i] = count[index];
		count[index] = temp;

		temp = alpha[i];
		alpha[i] = alpha[index];
		alpha[index] = temp;
	}

	cout << "Character Count:\tRecommended swap(based on dictionary):" << endl;
	for(int i = 0; i < 26; i++) {
		cout << alpha[i] << " - " << count[i] << "\t\t\t" << dictCount[i] << endl;
	}
	cout << endl;
	test = true;
	do {
		cout << "Please select an option:" << endl
			<< "1) Perform a swap" << endl
			<< "2) Output latest text to a text file" << endl
			<< "3) View Stats" << endl
			<< "4) Quit" << endl;
		if (stack > 0) cout << "5) Undo previous swap" << endl;
		cin >> selection;

		if(selection == 1) {
			if(stack == MAX_SWAPS) {
				cout << "Stack is full, undo swaps or start over." << endl;	
			}
			else {
				cout << "Enter first character to be swapped: ";
				cin >> swaps[stack][0];

				cout << "Enter character to swap it with: ";
				cin >> swaps[stack][1];
				
				for(int i = 0 ; i < encStr.length(); i++) {
					if(encStr[i] == toupper(swaps[stack][0])) {
						encStr[i] = toupper(swaps[stack][1]);
					}
					else if(encStr[i] == toupper(swaps[stack][1])) {
						encStr[i] = toupper(swaps[stack][0]);
					}
					else if(encStr[i] == tolower(swaps[stack][0])) {
						encStr[i] = tolower(swaps[stack][1]);
					}
					else if(encStr[i] == tolower(swaps[stack][1])) {
						encStr[i] = tolower(swaps[stack][0]);
					}
				}
				stack++;

				cout << endl << "Here is the resulting text after " << stack << " swaps:" << endl
					<< encStr << endl << endl;
			}
		}
		else if(selection == 2) {
			if(lines > 0) {
				cout << endl << "Select an option:" << endl
					<< "\t1) OVERWRITE the original file with all changes, and close the program." << endl
					<< "\t2) Specify new file to write this excerpt to." << endl;
				cin >> selection;
				if(selection == 1) {
					test = false;
					outFilePath = inFilePath;
					
					file.open(inFilePath, ios::in);
					encStr = "";
					if(file) {
						cout << "File opened successfully!" << endl << endl;
						
						while(!file.eof()) {
							getline(file, line);
							line += '\n';
							encStr += line;
						}
						file.close();
					}
					else {
						cout << "File failed to open." << endl;
					}
					
					cout << "Please Wait, making swaps..."<< endl;
					for(int j = 0; j < stack; j++) {
						for(int i = 0 ; i < encStr.length(); i++) {
							if(encStr[i] == toupper(swaps[j][0])) {
								encStr[i] = toupper(swaps[j][1]);
							}
							else if(encStr[i] == toupper(swaps[j][1])) {
								encStr[i] = toupper(swaps[j][0]);
							}
							else if(encStr[i] == tolower(swaps[j][0])) {
								encStr[i] = tolower(swaps[j][1]);
							}
							else if(encStr[i] == tolower(swaps[j][1])) {
								encStr[i] = tolower(swaps[j][0]);
							}
						}
					}
				}
				else {
					cout << "Please enter name/path of output file:" << endl;
					cin.ignore();
					getline(cin, outFilePath);
				}
			}			
			else {
				cout << "Please enter name/path of output file:" << endl;
				cin.ignore();
				getline(cin, outFilePath);
			}
			
			file.open(outFilePath, ios::out);
			file << encStr;
			file.close();

			cout << endl << "Your text has been written to:" << endl << outFilePath << endl << endl;
		}
		else if(selection == 3) {
			getFreq(encStr, strPerc);
			
			file.open(this->dictFile, fstream::in);
			
			while(!file.eof()) {
				getline(file, line);
				line += '\n';
				dictStr += line;
			}
			file.close();

			getFreq(dictStr, dictPerc);
			this->r = pear.calcR(strPerc, dictPerc);

			cout << "Here are the percentages for character frequency in the text" << endl
				<< "\tEncrypted Text:\t\tDictionary:" << endl;
			for(int i = 0; i <= 25; i++) {
				cout << (char)('A' + i) << fixed << setprecision(2) << '\t' << strPerc[i] << "\t\t\t" << dictPerc[i] << endl;
			}

			cout << endl << "Pearson's r comes out to " << this->r << " as of now." << endl << endl;
		}
		else if(selection == 4) {
			test = false;
		}
		else if(selection == 5) {
			stack--;
			for(int i = 0 ; i < encStr.length(); i++) {
					if(encStr[i] == toupper(swaps[stack][0])) {
						encStr[i] = toupper(swaps[stack][1]);
					}
					else if(encStr[i] == toupper(swaps[stack][1])) {
						encStr[i] = toupper(swaps[stack][0]);
					}
					else if(encStr[i] == tolower(swaps[stack][0])) {
						encStr[i] = tolower(swaps[stack][1]);
					}
					else if(encStr[i] == tolower(swaps[stack][1])) {
						encStr[i] = tolower(swaps[stack][0]);
					}
				}
			cout << "Here is the resulting text after the undo:" << endl
					<< encStr << endl << endl;
		}
		else {
			cout << "Invalid choice, try again." << endl;
		}

	} while(test);
}

double Pearson::calcR(double perc[], double dictPerc[]) {
	double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0, sumY2 = 0;
	
	for(int i = 0; i <= 25; i++) {
		sumX += perc[i];
		sumY += dictPerc[i];
		sumXY += (perc[i] * dictPerc[i]);
		sumX2 += pow(perc[i], 2.0);
		sumY2 += pow(dictPerc[i], 2.0);
	}

	return pow(((sumXY - ((sumX * sumY) / 26)) / ((sqrt(sumX2 - (pow(sumX, 2.0) / 26))) * (sqrt(sumY2 - (pow(sumY, 2.0) / 26))))), 2.0);
}

//Returns percentage of each character in string.
void getFreq(string str, double store[26]) {
	double count[27] = {0};
	for(int i = 0; i < str.length(); i++) {
		if(str[i] >= 65 && str[i] <= 90) {
			count[str[i] - 65]++;
			count[26]++;
		}
		else if(str[i] >= 97 && str[i] <= 122) {
			count[str[i] - 97]++;
			count[26]++;
		}
	}
	for(int j = 0; j <= 25; j++) {
		count[j] = (count[j] / count[26]) * 100;
	}

	for(int i = 0; i <= 25; i++) {
		store[i] = count[i];
	}
}