#include "Dog.h"
#include "Person.h"
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <unistd.h>


#define NUMBEROFDOGS 10
#define NUMBEROFPLAYERS 5

using namespace std;

int Dog::numberOfDogs=0;

Dog race(Dog*, int);
void betting(Person*,Dog*);
void sortByOdds(Dog *);

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	Person people[NUMBEROFPLAYERS];
	Dog dogs[NUMBEROFDOGS];
	int raceNumber = 1 , races = atoi(argv[1]);
	while(raceNumber<=races)
	{
		sortByOdds(dogs);
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		for (int i = 0; i < NUMBEROFPLAYERS; ++i)
			cout<<people[i].description();
		int laps=rand()%6+5;
		sleep(1);
		cout << "Wyścig nr " <<raceNumber << "\tLiczba okrążeń: " << laps
			<< "\nPsy biegnące w wyścigu:\nNr\tKurs\n";
			sleep(1);
		for (int i = 0; i < NUMBEROFDOGS; ++i)
			cout << dogs[i].id()<<"\t"<<dogs[i].odds()<<"\n";

		betting(people,dogs);
		sleep(1);
		Dog winner = race(dogs,laps);

		cout << "Zwycięzcą wyścigu został pies nr "<< winner.id() << "\n";

		for (int i = 0; i < NUMBEROFPLAYERS; ++i)
			people[i].claimWinnings(&winner);
		sleep(5);
		for (int i = 0; i < NUMBEROFDOGS; ++i)
			dogs[i].Rest();

		raceNumber++;
	}
	for (int i = 0; i < NUMBEROFPLAYERS; ++i)
		cout<<people[i].description();
}

Dog race(Dog* raceDogs, int laps)
{
	double results[NUMBEROFDOGS]={0} , best = 100000;
	for (int i = 0; i < laps; ++i)
	{
		cout<<"**************OKRĄŻENIE NR "<< i+1<<"***************\n";
		for (int j = 0; j < NUMBEROFDOGS; ++j)
			results[j] += raceDogs[j].Run();
	}

	int winner=0;

	for (int i = 0; i < NUMBEROFDOGS; ++i)
	{
		if(results[i]<best) 
		{
			winner=i;
			best=results[i];
		}
	}
	return raceDogs[winner];
}


void betting(Person*men,Dog* dog)
{
	for (int i = 0; i < NUMBEROFPLAYERS; ++i)
	{
		sleep(1);
		if(rand() % 101 < men[i].stupidity())
			men[i].bet(&dog[rand() % NUMBEROFDOGS], (rand() % 24000+1000)/100.0 );
		else if(men[i].prudence()<20)
			men[i].bet(&dog[rand() % 4 + 2], (rand() % (200*men[i].courage()) + 1000)/100.0);
		else if(men[i].prudence()<50)
			men[i].bet(&dog[rand() % 4 + 1], (rand() % (200*men[i].courage()) + 1000)/100.0);
		else if(men[i].prudence()<80)
			men[i].bet(&dog[rand() % 3], (rand() % (200*men[i].courage()) + 1000)/100.0);
		else
			men[i].bet(&dog[0], (rand() % (200*men[i].courage()) + 1000)/100.0);
	}
}


void sortByOdds(Dog *dog)
{
	for (int i = 0; i < NUMBEROFDOGS-1; ++i)
	{
		for (int j = NUMBEROFDOGS-1; j >= i+1; --j)
		{
			if(dog[j].odds() < dog[j-1].odds())
			{
				Dog buff = dog[j];
				dog[j]=dog[j-1];
				dog[j-1] = buff;
			}
		}
	}
}