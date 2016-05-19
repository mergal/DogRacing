#include "Person.h"
#include "Dog.h"
#include <string>


using namespace std;

string names[]={ "Janusz", "Mirek", "Andrzej", "Jurek", "Mietek", "Wiesław" };

Person::Person()
{
	_name=names[rand()%6];
	_onions=500;
	_stupidity=rand()%101;
	_courage=rand()%101;
	_prudence=rand()%101;
	_betDog=NULL;
	_betAmount=0;
}


void Person::bet(Dog*dog, int amount)
{
	if(amount>_onions) amount=_onions;
	_betDog = dog;
	_betAmount = amount;
	_onions -= amount;
}

void Person::claimWinnings(Dog* winner)
{
	if(_betDog->id() == winner->id()) _onions += _betAmount*_betDog->odds();
	_betDog=NULL;
	_betAmount=0;
}

string Person::description()
{
	return _name + " ma " + to_string(_onions) + " cebul";
}