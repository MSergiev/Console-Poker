#include "Hand.h"

//Constructor
Hand::Hand(const vector<Card>& hand) {
	setHand(hand);
	countCardProps();
}

//Count number of faces and suits in the hand
void Hand::countCardProps(){
	for(unsigned i = 0; i < sizeof(countFaces)/sizeof(countFaces[0]); i++)
		countFaces[i] = 0;
	for(unsigned i = 0; i < sizeof(countSuits)/sizeof(countSuits[0]); i++)
		countSuits[i] = 0;
	for(unsigned i = 0; i < hand.size(); i++){
		countFaces[hand.at(i).getFace()-1]++;
		countSuits[hand.at(i).getSuit()-1]++;
	}
}

//Hand getter
const vector<Card>& Hand::getHand() const {
	return hand;
}

//Hand setter
void Hand::setHand(const vector<Card>& hand) {
	this->hand = hand;
}

const string& Hand::getOwnerName() const {
	return ownerName;
}

void Hand::setOwnerName(const string& ownerName) {
	this->ownerName = ownerName;
}

Hand operator+(Hand& hand1, Hand& hand2){
	Hand h1 = hand1;
	Hand h2 = hand2;
	while(h2.cardsRemaining()>0) h1.addCard(h2.getCard(0));
	return h1;
}
bool operator>(Hand& hand1, Hand& hand2) {return (Hand::determineWinner(hand1, hand2) == 1?true:false);}
bool operator<(Hand& hand1, Hand& hand2) {return (Hand::determineWinner(hand1, hand2) == -1?true:false);}
bool operator>=(Hand& hand1, Hand& hand2) {return (Hand::determineWinner(hand1, hand2) >= 0?true:false);}
bool operator<=(Hand& hand1, Hand& hand2) {return (Hand::determineWinner(hand1, hand2) <= 0?true:false);}
bool operator==(Hand& hand1, Hand& hand2) {return (Hand::determineWinner(hand1, hand2) == 0?true:false);}

//Sort hand by suit
void Hand::sortBySuit(const bool& asc){
	unsigned tmp;
	for(unsigned i = 0; i < getHand().size(); i++){
		tmp = i;
		for(unsigned j = i; j < getHand().size(); j++){
			if(asc){
				if(getHand().at(j).getSuit() < getHand().at(tmp).getSuit())	tmp = j;
			} else {
				if(getHand().at(j).getSuit() > getHand().at(tmp).getSuit())	tmp = j;
			}
		}
		swapCards(i, tmp);
	}
}

//Sort hand by face
void Hand::sortByFace(const bool& asc){
	unsigned tmp;
	for(unsigned i = 0; i < getHand().size(); i++){
		tmp = i;
		for(unsigned j = i; j < getHand().size(); j++){
			if(asc){
				if(getHand().at(j).getFace() < getHand().at(tmp).getFace()) tmp = j;
			} else {
				if(getHand().at(j).getFace() > getHand().at(tmp).getFace()) tmp = j;
			}
		}
		swapCards(i, tmp);
	}
}

//Swap position of two cards
void Hand::swapCards(const unsigned& index1, const unsigned& index2){
	Card tmp = hand[index1];
	hand[index1] = hand[index2];
	hand[index2] = tmp;
}

//Draw a card from the hand
Card Hand::getCard(int index) {
	Card selected = hand[index];
	hand.erase(hand.begin()+index);
	return selected;
}

Card Hand::peekCard(int index) {
	return hand[index];
}

void Hand::addCard(Card card){
	hand.push_back(card);
}

//Number of cards remaining
int Hand::cardsRemaining(){
	return hand.size();
}

//Find if hand has a face match
bool Hand::hasFaceMatch(const int& num1, const int& num2) {
	bool flag1 = 0, flag2 = 0;
	for(unsigned i = 0; i < sizeof(countFaces)/sizeof(countFaces[0]); i++){
		if(countFaces[i] == num1 && !flag1){flag1 = true; continue;}
		if(countFaces[i] == num2) flag2 = true;
	}
	return (flag1&flag2);
}

//Find if hand has a number of matching suits
bool Hand::hasSuitMatch(const int& num) {
	for(unsigned i = 0; i < sizeof(countSuits)/sizeof(countSuits[0]); i++)
		if(countSuits[i] == num) return true;
	return false;
}

//Find if hand has a straight
bool Hand::hasStraight() {
	unsigned iterator = 0;
	while(countFaces[iterator]==0){iterator++;}
	for(unsigned i = iterator; i < iterator+5; i++)
		if(countFaces[i] == 0 || i >= sizeof(countFaces)/sizeof(countFaces[0])) return false;
	return true;
}

//Find the highest card value from the hand
unsigned short Hand::getHighestCard(const short& recur){
	unsigned short count = 0;
	for(unsigned short i = 0; i < sizeof(countFaces)/sizeof(countFaces[0]); i++)
		if(countFaces[i] > 0) count++;
	if(count == 0) return 0;
	unsigned short index  = (sizeof(countFaces)/sizeof(countFaces[0]) - 1);
	while(countFaces[index] == 0){index--;}
	if(recur>0) {
		countFaces[index] = 0;
		return getHighestCard(recur-1);
	}
	countCardProps();
	return index;
}

//Find the highest combo
unsigned short Hand::getHighestCombo(const short& recur){
	unsigned short count = 0;
	for(unsigned short i = 1; i < sizeof(countFaces)/sizeof(countFaces[0]); i++)
		if(countFaces[i] >= countFaces[count]) count = i;
	if(recur>0) {
		countFaces[count] = 0;
		return getHighestCombo(recur-1);
	}
	countCardProps();
	return count;
}

//Get a hand evaluation
int Hand::evaluate(){
	countCardProps();
	if(hasStraight() && hasSuitMatch(5)) return 8;
	if(hasFaceMatch(4)) return 7;
	if(hasFaceMatch(3,2)) return 6;
	if(hasSuitMatch(5)) return 5;
	if(hasStraight()) return 4;
	if(hasFaceMatch(3)) return 3;
	if(hasFaceMatch(2,2)) return 2;
	if(hasFaceMatch(2)) return 1;
	return 0;
}

//Return a string evaluation
string Hand::printEvaluation(){
	switch(evaluate()){
	case 0: return "High Card";
	case 1: return "One Pair";
	case 2: return "Two Pair";
	case 3: return "Three Of A Kind";
	case 4: return "Straight";
	case 5: return "Flush";
	case 6: return "Full House";
	case 7: return "Four Of A Kind";
	case 8: return "Straight Flush";
	default: return "Error";
	}
}

//Convert card face index to a symbol
string Hand::toFaceSymbol(const Face& index){
	switch(index){
	case TWO: return "2";
	case THREE: return "3";
	case FOUR: return "4";
	case FIVE: return "5";
	case SIX: return "6";
	case SEVEN: return "7";
	case EIGHT: return "8";
	case NINE: return "9";
	case TEN: return "T";
	case JACK: return "J";
	case QUEEN: return "Q";
	case KING: return "K";
	case ACE: return "A";
	default: return "0";
	}
}

//Convert card suit index to a symbol
string Hand::toSuitSymbol(const Suit& index){
	switch(index){
	case HEARTS: return "♥";
	case DIAMONDS: return "♦";
	case SPADES: return "♠";
	case CLUBS: return "♣";
	default: return "O";
	}
}

//Get a string of drawn cards from the hand
string Hand::drawHand(const int& faceDown){
	stringstream str;
	for(unsigned i = 0; i < 5; i++){
		int tmp = faceDown;
		for(unsigned j = 0; j < hand.size(); j++){
			switch(i){
			case 0: str << "┌─────┐"; break;
			case 1: (tmp&1)?str << "│░░░░░│":str << "│" << toFaceSymbol(hand[j].getFace()) << "    │"; break;
			case 2: (tmp&1)?str << "│░░░░░│":str << "│  " << toSuitSymbol(hand[j].getSuit()) << "  │"; break;
			case 3: (tmp&1)?str << "│░░░░░│":str << "│    " << toFaceSymbol(hand[j].getFace()) << "│"; break;
			case 4: str << "└─────┘"; break;
			}
			tmp=tmp>>1;
		}
		str << endl;
	}
	return str.str();
}

//Get a string of cards from the hand
string Hand::toString(){
	string str = "";
	for(unsigned i = 0; i < hand.size(); i++)
		str+=hand[i].toString() + "\n";
	return str;
}

//Destructor
Hand::~Hand() {
}

int Hand::determineWinner(Hand& hand1, Hand& hand2){
	if(hand1.evaluate()>hand2.evaluate()) return 1;
	else if(hand1.evaluate()<hand2.evaluate()) return -1;
	else {
		int recur;
		switch(hand1.evaluate()){
		case 1: case 2: case 3: case 6: case 7:
			recur = (hand1.evaluate()==2?2:hand1.evaluate()==6?1:0);
			for(int i = 0; i <= recur; i++){
				if(hand1.getHighestCombo(i) > hand2.getHighestCombo(i))	return 1;
				else if(hand1.getHighestCombo(i) < hand2.getHighestCombo(i)) return -1;
			}
			break;
		case 0: case 4: case 5: case 8:
			if(hand1.getHighestCard() > hand2.getHighestCard())	return 1;
			else if(hand1.getHighestCard() < hand2.getHighestCard()) return -1;
			else{
				recur = 0;
				cout << endl;
				while(hand1.getHighestCard(recur) == hand2.getHighestCard(recur) && recur < hand1.cardsRemaining()){recur++;}
				if(hand1.getHighestCard(recur) > hand2.getHighestCard(recur)) return 1;
				else if(hand1.getHighestCard(recur) < hand2.getHighestCard(recur)) return -1;
			}
		}
	}
	return 0;
}











//Winner logic
void Hand::winner(Hand& hand1, Hand& hand2){
	if(hand1.evaluate()>hand2.evaluate())
		cout << "1 wins with " << hand1.printEvaluation() << " against " << hand2.printEvaluation();
	else if(hand1.evaluate()<hand2.evaluate())
		cout << "2 wins with " << hand2.printEvaluation() << " against " << hand1.printEvaluation();
	else{
		int recur;
		switch(hand1.evaluate()){
		case 1: case 2: case 3: case 6: case 7:
			recur = (hand1.evaluate()==2?2:hand1.evaluate()==6?1:0);
			for(int i = 0; i <= recur; i++){
				if(hand1.getHighestCombo(i) > hand2.getHighestCombo(i)){
					cout << "1 wins with " << hand1.printEvaluation() << " and highest card " << hand1.toFaceSymbol(static_cast<Face>(hand1.getHighestCombo(i)+1)); break;}
				else if(hand1.getHighestCombo(i) < hand2.getHighestCombo(i)){
					cout << "2 wins with " << hand2.printEvaluation() << " and highest card " << hand2.toFaceSymbol(static_cast<Face>(hand2.getHighestCombo(i)+1)); break;}
			}
			break;
		case 0: case 4: case 5: case 8:
			if(hand1.getHighestCard() > hand2.getHighestCard()){
				cout << "1 wins with " << hand1.printEvaluation() << " and highest card " << hand1.toFaceSymbol(static_cast<Face>(hand1.getHighestCard()+1)); break;}
			else if(hand1.getHighestCard() < hand2.getHighestCard()){
				cout << "2 wins with " << hand2.printEvaluation() << " and highest card " << hand2.toFaceSymbol(static_cast<Face>(hand2.getHighestCard()+1)); break;}
			else{
				recur = 0;
				cout << endl;
				while(hand1.getHighestCard(recur) == hand2.getHighestCard(recur) && recur < hand1.cardsRemaining()){
					//cout << "Recur: " << recur << " : " << hand1.toFaceSymbol(hand1.getHighestCard(recur)+1) << endl;
					recur++;
				}
				if(hand1.getHighestCard(recur) > hand2.getHighestCard(recur)){
					cout << "1 wins with " << hand1.printEvaluation() << " and highest card " << hand1.toFaceSymbol(static_cast<Face>(hand1.getHighestCard(recur)+1)); break;}
				else if(hand1.getHighestCard(recur) < hand2.getHighestCard(recur)){
					cout << "2 wins with " << hand2.printEvaluation() << " and highest card " << hand2.toFaceSymbol(static_cast<Face>(hand2.getHighestCard(recur)+1)); break;}
				else cout << "Equal standing with " << hand2.printEvaluation() << endl; break;}
		}
	}
}
