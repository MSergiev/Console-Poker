#ifndef DECK_H_
#define DECK_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Card.h"
using std::vector;
using std::cout;
using std::endl;


class Deck {
private:
	vector <Card> deck;
public:
	Deck();
	Deck(const vector<Card>& deck);
	void initDeck();
	const vector<Card>& getDeck() const;
	void setDeck(const vector<Card>& deck);
	void shuffle();
	int cardsRemaining();
	vector<Card> dealHand(const int& size);
	Card drawCard(const unsigned& index = 0);
	void addCard(Card card);
	string toString();
	virtual ~Deck();
};

#endif /* DECK_H_ */
