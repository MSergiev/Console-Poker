/*
 * Card.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: ADMIN
 */

#include "Card.h"

Card::Card(const int&  suit, const int&  face) {
	setSuit(suit);
	setFace(face);
}

string Card::getSuitString() {
	switch(suit){
	case 1: return "Hearts";
	case 2: return "Diamonds";
	case 3: return "Spades";
	case 4: return "Clubs";
	default: return "Unknown";
	}
}

string Card::getFaceString() {
	switch(face){
	case 1: return "Two";
	case 2: return "Three";
	case 3: return "Four";
	case 4: return "Five";
	case 5: return "Six";
	case 6: return "Seven";
	case 7: return "Eight";
	case 8: return "Nine";
	case 9: return "Ten";
	case 10: return "Jack";
	case 11: return "Queen";
	case 12: return "King";
	case 13: return "Ace";
	default: return "Unknown";
	}
}

string Card::toString() {
	return getFaceString() + " of " + getSuitString();
}

int Card::getFace() const {
	return face;
}

void Card::setFace(int face) {
	this->face = face;
}

int Card::getSuit() const {
	return suit;
}

void Card::setSuit(int suit) {
	this->suit = suit;
}

Card::~Card() {
}
