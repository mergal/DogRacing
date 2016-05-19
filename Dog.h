#pragma once

class Dog
{
	static int numberOfDogs;
	int _id, _speed, _fatigue, _form;
	double _odds;
	
public:
	Dog();
	double Run();
	void Rest();
	int id(){return _id;};
	double odds(){return _odds;};
};
