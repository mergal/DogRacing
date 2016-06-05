#include "Dog.h"
#include "Person.h"
#include "Card.h"
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <vector>
#include <stack>
#include <queue>


#define NUMBEROFDOGS 8
#define NUMBEROFPLAYERS 5

using namespace std;

int Dog::numberOfDogs=0;
int Card::numberOfCards=0;

int Play(vector<Card*>);
bool Add_To_Stack(vector<Card*>*vec_of_cards,stack<Card*>*stack_of_cards);

Dog race(Dog*, int);
void betting(Person*,Dog*);
void sortByOdds(Dog *);




int main(int argc, char const *argv[])
{
	srand(time(NULL));

	if(argv[1] && argv[1][0]=='w' && argv[1][1]=='a' && argv[1][2] == 'r')
	{
		Card cards [52];
		vector<Card*> deck;
		deck.push_back(cards);
		for(int i=0;i<52;deck.insert(deck.begin()+rand()%deck.size(),&cards[i++]));
		deck.pop_back();
		Play(deck)==1?cout<<"\nWinner:PLAYER 1\n":cout<<"\nWinner:PLAYER 2\n";
	}
	else
	{
		Person people[NUMBEROFPLAYERS];
		Dog dogs[NUMBEROFDOGS];
		int raceNumber = 1 , races = rand()%6+5;
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
			sleep(1);
			cout << "Zwycięzcą wyścigu został pies nr "<< winner.id() << "\n";

			for (int i = 0; i < NUMBEROFPLAYERS; ++i)
				people[i].claimWinnings(&winner);
			sleep(3);
			for (int i = 0; i < NUMBEROFDOGS; ++i)
				dogs[i].Rest();

			raceNumber++;
		}	
		for (int i = 0; i < NUMBEROFPLAYERS; ++i)
			cout<<people[i].description();
	}
}	




Dog race(Dog* raceDogs, int laps)
{
	int winner=0;
	double results[NUMBEROFDOGS]={0} , best = 100000;
	for (int i = 0; i < laps; ++i)
	{
		cout<<"**************OKRĄŻENIE NR "<< i+1<<"***************\n";
		for (int j = 0; j < NUMBEROFDOGS; ++j)
			results[j] += raceDogs[j].Run();
		sleep(1);
	}

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
			men[i].bet(&dog[rand() % NUMBEROFDOGS-1], (rand() % (200*men[i].courage()) + 1000)/100.0);
		else if(men[i].prudence()<50)
			men[i].bet(&dog[rand() % NUMBEROFDOGS-3], (rand() % (200*men[i].courage()) + 1000)/100.0);
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




int Play(vector<Card*> Deck)	
{
	stack<Card*> players_stack[2];
	stack<Card*> to_win;
	vector<Card*> players_vec[2];
	
	for(int i=0;i<52;players_stack[i%2].push(Deck[i++]));
	
	int comp=0;
	while(1)
	{
		if(players_stack[0].empty())
		{
			if(!Add_To_Stack(&players_vec[0],&players_stack[0]))
				return 2;
		}
		if(players_stack[1].empty())
		{
			if(!Add_To_Stack(&players_vec[1],&players_stack[1]))
				return 1;
		}

		cout<<setw(30)<<left<<players_stack[0].top()->description()<<
		players_stack[1].top()->description()<<"\n";
		to_win.push(players_stack[0].top());
		to_win.push(players_stack[1].top());
		comp = players_stack[0].top()->Compare(*(players_stack[1].top()));
		players_stack[0].pop();
		players_stack[1].pop();

		
		if(comp>0)
		{
			while(!to_win.empty())
			{
				players_vec[0].push_back(to_win.top());
				to_win.pop();
				
			}
			cout<<"**********REMAINING CARDS***********\n"
			<<setw(30)<<left<<players_vec[0].size()+players_stack[0].size()
			<<players_vec[1].size()+players_stack[1].size()<<"\n";
		}
		else if(comp<0)
		{
			while(!to_win.empty())
			{
				players_vec[1].push_back(to_win.top());
				to_win.pop();
			}
			cout<<"**********REMAINING CARDS***********\n"
			<<setw(30)<<left<<players_vec[0].size()+players_stack[0].size()
			<<players_vec[1].size()+players_stack[1].size()<<"\n";
		}
		else
		{
			if(players_stack[0].empty())
			{
				if(!Add_To_Stack(&players_vec[0],&players_stack[0]))
					return 2;
			}
			if(players_stack[1].empty())
			{
				if(!Add_To_Stack(&players_vec[1],&players_stack[1]))
					return 1;
			}
			cout<<"XXXXXXXXXXXXXXX\t\t\tXXXXXXXXXXXXXXXXX\n";
			to_win.push(players_stack[0].top());
			to_win.push(players_stack[1].top());
			players_stack[0].pop();
			players_stack[1].pop();

		}
		usleep(500000);
	}
}



bool Add_To_Stack(vector<Card*>*vec_of_cards,stack<Card*>*stack_of_cards)
{
	if(vec_of_cards->size()==0)
		return false;
	while(vec_of_cards->size())
	{
		int random=rand()%vec_of_cards->size();
		stack_of_cards->push(vec_of_cards->at(random));
		vec_of_cards->erase(vec_of_cards->begin()+random);
	}
	return true;
}