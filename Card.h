#pragma once

#include <string>


using namespace std;

class Card
{
private:
	static int numberOfCards;
	int rank;
	string suit;

public:
	Card();
	int Compare(Card);
	string description();
};	