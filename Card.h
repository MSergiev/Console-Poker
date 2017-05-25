#include <string>
#ifndef CARD_H_
#define CARD_H_
using std::string;

enum Suit{
	HEARTS=1, DIAMONDS, SPADES, CLUBS};
enum Face{
	TWO=1, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

class Card {
private:
	Suit suit;
	Face face;
public:
	Card(const Suit& suit, const Face& face);
	Face getFace() const;
	void setFace(Face face);
	Suit getSuit() const;
	void setSuit(Suit suit);
	string getSuitString();
	string getFaceString();
	string toString();
	virtual ~Card();
};

#endif /* CARD_H_ */
