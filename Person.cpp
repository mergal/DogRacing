#include "Person.h"
#include "Dog.h"
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

vector <string> Person::names;

void Person::init()
{
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}
	


Person::Person()
{
	static int amountOfNames = (init(), names.size());
	_name=names[rand()%6];
	_money=500;
	_stupidity=rand()%101;
	_courage=rand()%101;
	_prudence=rand()%101;
	_betDog=NULL;
	_betAmount=0;
}


void Person::bet(Dog * dog, double amount)
{
	if(amount>_money) amount=_money;
	_betDog = dog;
	_betAmount = amount;
	_money -= amount;
	cout<<_name<<" postawił "<<_betAmount<<"$ na psa nr "<<_betDog->id()<<"\n";
}

void Person::claimWinnings(Dog* winner)
{
	double winnings=0;
	if(_betDog->id() == winner->id())
	{
		winnings = (int)(100*_betAmount*_betDog->odds())/100.0;
		_money += winnings;
	}
	_betDog=NULL;
	_betAmount=0;
	cout<<_name<<" wygrał "<<winnings<<"$\n";
}

string Person::description()
{
	return _name + " ma " + to_string(_money) + " $\n";
}