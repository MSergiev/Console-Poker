/*
 * Card.h
 *
 *  Created on: Apr 12, 2017
 *      Author: ADMIN
 */

#include <string>
#ifndef CARD_H_
#define CARD_H_
using std::string;

class Card {
private:
	int suit, face;
public:
	Card(const int& suit, const int& face);
	int getFace() const;
	void setFace(int face);
	int getSuit() const;
	void setSuit(int suit);
	string getSuitString();
	string getFaceString();
	string toString();
	virtual ~Card();
};

#endif /* CARD_H_ */
