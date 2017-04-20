#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player
{
	private:
	protected:
		char name[];
		Position position;
		std::vector<Card> hand;
		bool isHuman;
	public:
		void addCardToHand(Card card);
		void printHand(char c);
		void sortHand();
		void sortHand(Suit suit);
		uint8_t countHonorPoints();
		uint8_t countHonorPoints(Suit suit);
		void setPosition(Position p);
		Position getPosition(Position p);
		void clearHand();
		virtual Card playCard(Suit firstSuit) = 0; // If firstSuit is NoTrump, this is the first card to be played
		virtual void bid(Bid& bid, uint8_t lastLevel, Suit lastSuit, bool lastDoubled, bool lastRedoubled) = 0;
		Card playRandomCard(Suit firstSuit);
		bool hasCard(Card c) const;
		bool isValidPlay(Card c, Suit firstSuit) const;
		std::vector<Card> getPlayableCards(Suit firstSuit);
		bool getIsHuman();
};

#endif