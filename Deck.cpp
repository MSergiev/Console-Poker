#include "Deck.h"

Deck::Deck() {
	srand(time(0));
	initDeck();
}

Deck::Deck(const vector<Card>& deck) {
	srand(time(0));
	setDeck(deck);
}

void Deck::initDeck(){
	vector<Card> newDeck;
	for(int i = TWO; i!=ACE; ++i)
		for(int j = HEARTS; j!=CLUBS; ++j)
			newDeck.push_back(Card(static_cast<Suit>(j),static_cast<Face>(i)));
	setDeck(newDeck);
}

void Deck::setDeck(const vector<Card>& deck) {
	this->deck = deck;
}

void Deck::shuffle() {
	vector<Card> newDeck;
	int rnum;
	while(deck.size()>0){
		rnum = rand()%(deck.size());
		newDeck.push_back(drawCard(rnum));
	}
	setDeck(newDeck);
}

Card Deck::drawCard(const unsigned& index) {
	Card drawnCard = deck.at(index);
	deck.erase(deck.begin()+index);
	return drawnCard;
}

void Deck::addCard(Card card){
	deck.push_back(card);
}

vector<Card> Deck::dealHand(const int& size){
	vector<Card> hand;
	for(int i = 0; i < size; i++)
		hand.push_back(drawCard(0));
	return hand;
}

string Deck::toString() {
	string str = "";
	for(int i = 0; i < cardsRemaining(); i++)
		str+=deck[i].toString() + "\n";
	return str;
}

const vector<Card>& Deck::getDeck() const {
	return deck;
}

int Deck::cardsRemaining() {
	return deck.size();
}

Deck::~Deck() {
}

