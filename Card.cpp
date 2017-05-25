#include "Card.h"

Card::Card(const Suit&  suit, const Face&  face) {
	setSuit(suit);
	setFace(face);
}

string Card::getSuitString() {
	switch(suit){
	case HEARTS: return "Hearts";
	case DIAMONDS: return "Diamonds";
	case SPADES: return "Spades";
	case CLUBS: return "Clubs";
	default: return "Unknown";
	}
}

string Card::getFaceString() {
	switch(face){
	case TWO: return "Two";
	case THREE: return "Three";
	case FOUR: return "Four";
	case FIVE: return "Five";
	case SIX: return "Six";
	case SEVEN: return "Seven";
	case EIGHT: return "Eight";
	case NINE: return "Nine";
	case TEN: return "Ten";
	case JACK: return "Jack";
	case QUEEN: return "Queen";
	case KING: return "King";
	case ACE: return "Ace";
	default: return "Unknown";
	}
}

string Card::toString() {
	return getFaceString() + " of " + getSuitString();
}

Face Card::getFace() const {
	return face;
}

void Card::setFace(Face face) {
	this->face = face;
}

Suit Card::getSuit() const {
	return suit;
}

void Card::setSuit(Suit suit) {
	this->suit = suit;
}

Card::~Card() {
}
