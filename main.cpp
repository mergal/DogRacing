#include "Dog.h"
#include "Person.h"
#include <stdlib.h>
#include <time.h> 
#include <iostream>


#define NUMBEROFDOGS 8
#define NUMBEROFPEOPLE 2

using namespace std;

int Dog::numberOfDogs=0;

Dog Race(Dog*, int);
void betting(Person*,Dog*);

int main(int argc, char const *argv[])
{
	argc==2? srand(atoi(argv[1])):srand(time (NULL));
	Person people[NUMBEROFPEOPLE];
	Dog dogs[NUMBEROFDOGS];
	int raceNumber=1;
	srand(time(NULL));
	while(people[0].onions()>0 || people[1].onions()>0)
	{
		cout << people[0].description() << "\n" <<people[1].description() << "\n\n\n";
		int laps=rand()%6+5;

		cout << "Wyścig nr " <<raceNumber << "\nLiczba okrążeń: " << laps
			<< "\nPsy biegnące w wyścigu:\nNr\tKurs\n";

		for (int i = 0; i < NUMBEROFDOGS; ++i)
			cout << dogs[i].id()<<"\t"<<dogs[i].odds()<<"\n";

		betting(people,dogs);
		Dog winner = Race(dogs,laps);

		for (int i = 0; i < 500000000; ++i);

		cout << "Zwycięzcą wyścigu został pies nr "<< winner.id() << "\n\n";

		for (int i = 0; i < NUMBEROFPEOPLE; ++i)
			people[i].claimWinnings(&winner);

		for (int i = 0; i < NUMBEROFDOGS; ++i)
			dogs[i].Rest();

		raceNumber++;
	}
}

Dog Race(Dog* raceDogs, int laps)
{
	double result=0, best=1000000;
	int winner=0;
	for (int i = 0; i < NUMBEROFDOGS; ++i)
	{
		result=0;
		for (int j = 0; j < laps; ++j)
			result += raceDogs[i].Run();
		if(result<best)
		{
			winner=i;
			best=result;
		}
	}
	return raceDogs[winner];
}


void betting(Person*men,Dog* dog)
{
	for (int i = 0; i < NUMBEROFPEOPLE; ++i)
	{
		//if(rand%101 < men[i].stupidity())
			men[i].bet(&dog[rand() % 8], rand() % 51);
		//else ???
	}
}