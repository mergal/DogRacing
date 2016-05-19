#pragma once

#include <string>
#include "Dog.h"

using namespace std;

class Person
{
	string _name;
	int _onions,_betAmount;
	Dog* _betDog;
	int _stupidity, _courage, _prudence;
public:
	Person();
	int onions(){ return _onions; }
	int stupidity(){ return _stupidity; }
	int courage(){ return _courage; }
	int prudence(){ return _prudence; }
	void bet(Dog*dog, int amount);
	void claimWinnings(Dog*);
	string description();
};