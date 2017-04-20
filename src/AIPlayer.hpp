#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

class AIPlayer: public Player
{
	private:
	protected:
	public:
		AIPlayer();
		virtual Card playCard(Suit firstSuit) = 0;
		virtual void makeBid(BetType& betType, Suit& suit, uint8_t& level) = 0;
		void bid(Bid& bid, uint8_t lastLevel, Suit lastSuit, bool lastDoubled, bool lastRedoubled);
};

#endif