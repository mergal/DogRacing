#include "Dog.h"
#include <stdlib.h>
#include <time.h>


Dog::Dog()
{
	_id = ++numberOfDogs;
	_speed= rand()%71+20;
	_fatigue=0;
	_form= rand()%40+40;
	_odds= 10000.0/(double)(_form*_speed);
}


double Dog::Run()
{
	double result = 1000.0*(100+_fatigue)/(double)(_speed * _form);
	if(rand()%51 < _fatigue)
	{
		result*=2;
		_fatigue-= rand()%16;
		return result;
	}
	if(rand()%201 < _fatigue)
	{
		result*=5;
		_form-=rand()%10+5;
		return result;
	}
	_fatigue+=rand()%16;
	return result;
}


void Dog::Rest()
{
	_fatigue = 0;
	if((_form += rand()%30-15)>100)
		_form=100;
	else if(_form<10)
		_form=10;
	_odds= 10000.0/(double)(_form*_speed);
}