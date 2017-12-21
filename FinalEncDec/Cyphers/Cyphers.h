#include "MenuIO.h"
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

class Pearson {
private:
	double r;
public:
	double calcR(double*, double*);
};

class Encrypter {
private:
	string userIn;
	string encText;
	string fileName;

	string shift(string, int);
	string sub(string);
public:
	Encrypter(string);
	void encryptText();
	void encryptFile();
	string getUserIn() {return userIn;}
	string getEncText() {return encText;}
	string getFileName() {return fileName;}
};

class Decrypter {
private:
	string dictFile;
	double r;
	Pearson pear;
	//int decShift(string, string);

public:
	Decrypter(string);
	void decryptText();
};

void getFreq(string, double*);