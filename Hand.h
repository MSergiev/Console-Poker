#ifndef HAND_H_
#define HAND_H_
#include "Card.h"
#include <vector>
#include <sstream>
#include <iostream>
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::stringstream;

class Hand {
private:
	string ownerName;
	vector <Card> hand;
	unsigned short countFaces[13];
	unsigned short countSuits[4];
public:
	Hand(const vector<Card>& hand);

	const vector<Card>& getHand() const;
	void setHand(const vector<Card>& hand);
	const string& getOwnerName() const;
	void setOwnerName(const string& ownerName);

	friend Hand operator+(Hand& hand1, Hand& hand2);
	friend bool operator>(Hand& hand1, Hand& hand2);
	friend bool operator<(Hand& hand1, Hand& hand2);
	friend bool operator>=(Hand& hand1, Hand& hand2);
	friend bool operator<=(Hand& hand1, Hand& hand2);
	friend bool operator==(Hand& hand1, Hand& hand2);

	void countCardProps();
	void sortBySuit(const bool& asc = false);
	void sortByFace(const bool& asc = false);
	void swapCards(const unsigned& index1, const unsigned& index2);
	Card getCard(int index);
	Card peekCard(int index);
	void addCard(Card card);
	int cardsRemaining();
	bool hasFaceMatch(const int& num1, const int& num2 = 0);
	bool hasSuitMatch(const int& num);
	bool hasStraight();
	unsigned short getHighestCard(const short& recur = 0);
	unsigned short getHighestCombo(const short& recur = 0);
	int evaluate();
	string printEvaluation();
	string toFaceSymbol(const Face& index);
	string toSuitSymbol(const Suit& index);
	string drawHand(const int& faceDown = 0);
	string toString();
	static void winner(Hand& h1, Hand& h2);
	static int determineWinner(Hand& hand1, Hand& hand2);

	virtual ~Hand();
};

#endif /* HAND_H_ */
