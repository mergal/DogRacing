#include "Card.h"

using namespace std;

string ranks[]=
{
	"Deuce","Three","Four","Five","Six","Seven",
	"Eight","Nine","Ten","Jack","Queen","King","Ace"
};
	
string suits[]={"Heart","Diamond","Club","Spade"};

Card::Card()
{
	rank = numberOfCards%13;
	suit = suits[numberOfCards/13];
	numberOfCards++;
}

string Card::description()
{
	return ranks[rank] +" of "+ suit +"s";
}

int Card::Compare(Card card)
{
	return rank-card.rank;
}