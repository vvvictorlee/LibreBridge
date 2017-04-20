#include <cstdint>
#include <string>
#include "LibreBridge.hpp"
#include "Bid.hpp"
#include "Misc.hpp"

using namespace std;

void Bid::setBid(string stringBid, Position pla, uint8_t lastLevel, Suit lastSuit, bool lastDoubled, bool lastRedoubled)
{
	betType = Invalid;
	player = pla;
	suit = NoTrump;
	level = 0;
	if(stringBid == "X")
	{
		if(!lastLevel || lastDoubled || lastRedoubled) return;
		betType = Double;
	}
	else if(stringBid == "XX")
	{
		if(!lastLevel || !lastDoubled || lastRedoubled) return;
		betType = Redouble;
	}
	else if(stringBid == "Pass" || stringBid == "") betType = Pass;
	else
	{
		if(stringBid.length() < 2 || stringBid.length() > 3) return;
		level = stringBid[0];
		if(level < 0 || level > 7) return;
		if(stringBid.length() == 2 && (stringBid[1] == 'C' || stringBid[1] == 'D' || stringBid[1] == 'H' || stringBid[1] == 'S'))
		{
			suit = charToSuit(stringBid[1]);
			if(lastLevel > level) return;
			if(lastLevel == level && lastSuit >= suit) return;
			betType = Normal;
		}
		else if(stringBid.length() == 3 && stringBid[1] == 'N' && stringBid[2] == 'T')
		{
			suit = NoTrump;
			if(lastLevel > level) return;
			if(lastLevel == level && lastSuit == suit) return;
			betType = Normal;
		}
	}
}

void Bid::setBid(BetType& b, Suit& s, uint8_t& l, Position position, uint8_t lastLevel, Suit lastSuit, bool lastDoubled, bool lastRedoubled)
{
	if(b == Double)
	{
		if(!lastLevel || lastDoubled || lastRedoubled) return;
		betType = Double;
	}
	else if(b == Redouble)
	{
		if(!lastLevel || !lastDoubled || lastRedoubled) return;
		betType = Redouble;
	}
	else if(b == Pass) betType = Pass;
	else
	{
		if(l < 0 || l > 7) return;
		level = l;
		suit = s;
		if(s != NoTrump)
		{
			if(lastLevel > level) return;
			if(lastLevel == level && lastSuit >= suit) return;
			betType = Normal;
		}
		else
		{
			suit = NoTrump;
			if(lastLevel > level) return;
			if(lastLevel == level && lastSuit == suit) return;
			betType = Normal;
		}
	}
}

string Bid::toString()
{
	if(betType == Invalid) return "Invalid.";
	if(betType == Pass) return "Pass";
	if(betType == Double) return "Double";
	if(betType == Redouble) return "Redouble";
	return to_string(level) + suitToString(Suit(suit)); // betType == Normal
}

BetType Bid::getBetType()
{
	return betType;
}

Suit Bid::getSuit()
{
	return Suit(suit);
}

uint8_t Bid::getLevel()
{
	return level;
}