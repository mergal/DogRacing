#pragma once

#include <string>
#include <vector>
#include <iterator>
#include "Dog.h"

using namespace std;

class Person
{
	static vector <string> names;
	string _name;
	double _money,_betAmount;
	Dog* _betDog;
	int _stupidity, _courage, _prudence;
public:
	Person();

	double money(){ return _money; }
	int stupidity(){ return _stupidity; }
	int courage(){ return _courage; }
	int prudence(){ return _prudence; }
	void init();
	void bet(Dog*dog, double amount);
	void claimWinnings(Dog*);
	string description();
};