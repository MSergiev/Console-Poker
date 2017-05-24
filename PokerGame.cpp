#include "PokerGame.h"

PokerGame::PokerGame() {
	setNumOfPlayers(2);
	gameType = 0;
}

void PokerGame::splash() {
	cout << "╔═══════════════ C++ ════════════════╗" << endl;
	cout << "║ ╔════╗ ╔════╗ ╔═╗╔═╗ ╔════╗ ╔════╗ ║" << endl;
	cout << "║ ║ ╔╗ ║ ║ ╔╗ ║ ║ ║║ ║ ║ ╔══╝ ║ ╔╗ ║ ║" << endl;
	cout << "║ ║ ║║ ║ ║ ║║ ║ ║ ╚╝ ║ ║ ║    ║ ╚╝ ║ ║" << endl;
	cout << "║ ║ ╚╝ ║ ║ ║║ ║ ║  ╔═╝ ║ ╚══╗ ║  ╔═╝ ║" << endl;
	cout << "║ ║ ╔══╝ ║ ║║ ║ ║  ╚═╗ ║ ╔══╝ ║  ╚═╗ ║" << endl;
	cout << "║ ║ ║    ║ ║║ ║ ║ ╔╗ ║ ║ ║    ║ ╔╗ ║ ║" << endl;
	cout << "║ ║ ║    ║ ╚╝ ║ ║ ║║ ║ ║ ╚══╗ ║ ║║ ║ ║" << endl;
	cout << "║ ╚═╝    ╚════╝ ╚═╝╚═╝ ╚════╝ ╚═╝╚═╝ ║" << endl;
	cout << "╚════════════════════════════════════╝" << endl;
	cout << endl;
}

void PokerGame::clearScreen() {
	for(int i = 0; i < 50; i++) cout << endl;
}

void PokerGame::pause(){

	 cout << "Press enter to continue...\n" << flush;
	 cin.ignore(20, cin.peek());
	 cin.ignore(20, '\n');

}

void PokerGame::discardFromHand(Hand& hand, const int& discard){
	if(discard < 1 || discard > 3) return;
	bool index[hand.cardsRemaining()] = {0};
	for(int i = 0; i < discard; i++){
		int choice;
		cout << "\nEnter " << (i==0?"first":i==1?"second":"third") << " card index to discard: ";
		cin >> choice;
		cout << "- Discarding " << hand.peekCard(choice-1).toString() << endl;
		index[choice-1]=true;
	}

	for(int i = sizeof(index)/sizeof(index[0])-1; i >= 0; i--){
		if(index[i]){
			deck.addCard(hand.getCard(i));
			hand.addCard(deck.drawCard());
		}
	}
	hand.sortByFace();
	cout << "\n\nNew hand: (" << hand.printEvaluation() << ")" << endl;
	cout << hand.drawHand() << endl;
	pause();
}

void PokerGame::beginGame(){
	splash();
	gameInit();
	switch(gameType){
	case 1: classicGameLoop(); break;
	case 2: texasGameLoop(5); break;
	}
}

void PokerGame::gameInit() {
	deck.shuffle();
	unsigned short num;
	unsigned short game;
	cout << "\n1 - Classic Poker " << endl;
	cout << "2 - Texas Hold'em " << endl;
	cout << "Input game type: ";
	cin >> game;
	cout << "\nInput number of players: ";
	cin >> num;
	setNumOfPlayers(num);
	setGameType(game);
	string name;
	cout << endl;
	for(int i = 0; i < numOfPlayers; i++){
		cout << "Enter name for player " << i+1 << ": ";
		cin >> name;
		playerHands.push_back(deck.dealHand(gameType==1?5:2));
		playerHands.at(i).setOwnerName(name);
		playerHands.at(i).sortByFace();
		credit.push_back(100);
	}
}

void PokerGame::classicGameLoop(const int& turns){
	string names[numOfPlayers];
	for(int i = 0; i < numOfPlayers; i++) names[i] = playerHands[i].getOwnerName();
	for(int i = 0; i < turns; i++){
		for(int j = 0; j < numOfPlayers; j++){
			pause();
			clearScreen();
			cout << "============= ROUND " << i+1 << " =============\n\n";
			int discard;
			cout << playerHands[j].getOwnerName()  << "'s hand: (" << playerHands[j].printEvaluation() << ")\n\n";
			cout << playerHands[j].drawHand();
			for(int k = 0; k < playerHands[j].cardsRemaining(); k++) cout << "╚═ " << k+1 << " ═╝";
			cout << endl;
			cout << "\nInput number of cards to discard (up to three): ";
			cin >> discard;
			discardFromHand(playerHands[j], discard);
		}

		bool hands[numOfPlayers] = {0};
		for(int j = 0; j < numOfPlayers-1; j++){
			if(hands[j]) continue;
			for(int k = j+1; k < numOfPlayers; k++){
				if(playerHands[j] > playerHands[k]) hands[k] = 1;
				else if(playerHands[j] < playerHands[k]) {hands[j] = 1; break;}
			}
		}

		int winnerCount = 0;
		for(int j = 0; j < numOfPlayers; j++){
			if(!hands[j]) winnerCount++;
		}


		clearScreen();
		cout << "============= ROUND " << i+1 << " =============\n\n";
		for(int j = 0; j < numOfPlayers; j++){
			cout << playerHands[j].getOwnerName()  << "'s hand: (" << playerHands[j].printEvaluation() << ")\n";
			cout << playerHands[j].drawHand();
			cout << "\n===================================\n\n";
		}


		cout << "===================================\n";
		if(winnerCount == 1) {for(int j = 0; j < numOfPlayers; j++)
			if(!hands[j]) cout << playerHands.at(j).getOwnerName() << " wins with " << playerHands.at(j).printEvaluation() << "\n";}
		else cout << "Tie, split the pot.\n";
		cout << "===================================\n";

		deck.initDeck();
		deck.shuffle();
		playerHands.clear();

		for(int j = 0; j < numOfPlayers; j++){
			playerHands.push_back(deck.dealHand(5));
			playerHands.at(j).setOwnerName(names[j]);
			playerHands.at(j).sortByFace();
		}

		cout << "Next: Round " << (i+2) << endl;
	}
}

void PokerGame::texasGameLoop(const int& turns){
	int pot, stage, dealer, ante, limit;
	bool folded[numOfPlayers];
	int foldedCount, player, loop = 0;
	Hand dealerHand(deck.dealHand(5));

	while(1){
//Init game data
		stage = 31;
		pot = 0;
		foldedCount = 0;
		for(int i = 0; i < numOfPlayers; i++) {
			playerHands.at(i).setHand(deck.dealHand(2));
			playerHands.at(i).sortByFace();
			folded[i] = false;
		}
		history.str("- Begin new game -\n");
		dealer = loop%numOfPlayers;
		player = (dealer+2)%numOfPlayers;
		deck.initDeck();
		deck.shuffle();
		dealerHand.setHand(deck.dealHand(5));

		for(int i = 0; i < numOfPlayers; i++) {
			if(credit[i] <= 0) {
				folded[i] = true;
				foldedCount++;
			}
		}

		if(foldedCount == numOfPlayers-1){
			for(int i = 0; i < numOfPlayers; i++)
				if(credit[i] > 0) {
					cout << "======================================" << endl;
					cout << playerHands.at(i).getOwnerName() << " won the game. " << endl;
					cout << "======================================" << endl;
					pause();
					return;
				}
		}

		for(int turn = 0; turn < 4; turn++){
//Init round data
			limit = numOfPlayers;
			history << "\n- Begin round " << turn+1 << " -"<< endl;
			ante = 0;
			if(turn == 0){
				history << "Current dealer: " << playerHands.at(dealer).getOwnerName() << endl;
				for(int i = 1; i < 3; i++){
					pot += i;
					credit.at((dealer+i)%numOfPlayers)-=i;
					history << (i==1?"Small (1$)":"Big (2$)") << " blind from " << playerHands.at((dealer+i)%numOfPlayers).getOwnerName() << endl;
				}
				ante = 2;
			}


//Betting stage
			if(turn != 3){
				for(int i = 0; i < limit; i++){
					if(foldedCount==numOfPlayers-1) break;
					player = (player+1)%numOfPlayers;
					if(folded[player]) continue;
//Temporary evaluative hand
					Hand check = playerHands.at(player);
					for(int j = 0; j < (turn==0?0:turn==1?3:(turn+2)); j++) check.addCard(dealerHand.peekCard(j));
					check.sortByFace();
//Print history
					clearScreen();
					cout << "============= HISTORY =============\n";
					cout << history.str();
//Print game data
					cout << "\n============= ROUND " << turn+1 << " =============\n\n";
					cout << ((player==dealer)?"*DEALER* ":"") << "Player: " << playerHands.at(player).getOwnerName() << " (Credit: " << credit.at(player) << "$)\n\n";
					cout << "Pot: " << pot << "$\n";
					cout << "Ante: " << ante << "$.\n\n";
					cout << "Dealer hand:" << endl;
					cout << dealerHand.drawHand(stage) << endl;
					cout << "Waiting for player " << playerHands.at(player).getOwnerName() << endl;
					pause();
					cout << "Hand (" << check.printEvaluation() << "):" << endl;
					cout << playerHands.at(player).drawHand() << endl;
//Choose action
					short action = 0;
					while(action < 1 || action > 3){
						cout << "1 - Fold   2 - " << (ante==0?"Check":"Call") << "   3 - Raise" << endl;
						cout << "Choose action: ";
						cin >> action;
					}
//Execute action
					switch(action){
	//Case Fold
					case 1:
						folded[player] = true;
						cout << "You folded." << endl;
						history << playerHands.at(player).getOwnerName() << " folded." << endl;
						foldedCount++;
						break;
	//Case Call/Check
					case 2:
						if(ante==0){
							cout << "You checked." << endl;
							history << playerHands.at(player).getOwnerName() << " checked." << endl;
						} else {
							if(ante>credit[player]){
								pot+=credit[player];
								credit[player]-=credit[player];
								folded[player] = true;
								foldedCount++;
								cout << "You went all in with " << ante << "$." << endl;
								history << playerHands.at(player).getOwnerName() << " went all in with "  << ante << "$." << endl;
							} else {
								pot+=ante;
								credit[player]-=ante;
								cout << "You called with " << ante << "$." << endl;
								history << playerHands.at(player).getOwnerName() << " called with "  << ante << "$." << endl;
							}
						}
						break;
	//Case Raise
					case 3:
						int raise = 0;
						while(raise <= 0){
							cout << "Choose amount to raise with: ";
							cin >> raise;
						}
						if(raise>=credit[player]){
							raise = credit[player];
							folded[player] = true;
							foldedCount++;
						}
						limit = numOfPlayers;
						i = 0;
						ante=raise;
						pot+=raise;
						credit[player]-=raise;
						cout << "You raised ante to " << ante << "$." << endl;
						history << playerHands.at(player).getOwnerName() << " raised ante to " << ante << "$." << endl;
						break;
					}

					pause();
				}

//Enter final round
			} else {
				vector <Hand> evaluate;
				bool loser[numOfPlayers] = {false};
				int winnerCount = 0;

				for(int i = 0; i < numOfPlayers; i++) {
					evaluate.push_back(playerHands.at(i)+dealerHand);
					evaluate.at(i).sortByFace();
				}

				for(int i = 0; i < numOfPlayers-1; i++){
					if(folded[i] && credit[i] > 0) loser[i] = true;
					if(loser[i]) continue;
					for(int j = i+1; j < numOfPlayers; j++){
						if(folded[j] && credit[j] > 0) {loser[j] = true; break;}
						else if(evaluate[i] > evaluate[j]) {loser[j] = true; break;}
						else if(evaluate[i] < evaluate[j]) {loser[i] = true; break;}
					}
				}

				for(int i = 0; i < numOfPlayers; i++) if(!loser[i]) winnerCount++;

				dealerHand.sortByFace();

				clearScreen();
				cout << "=========== FINAL ROUND ===========\n\n";
				cout << "Dealer hand: " << endl;
				cout << dealerHand.drawHand();
				cout << "===================================\n";
				for(int i = 0; i < numOfPlayers; i++){
					if(folded[i]  && credit[i] > 0) continue;
					cout << "Player " << playerHands.at(i).getOwnerName() << "'s hand (" << evaluate.at(i).printEvaluation() << "):" << endl;
					cout << playerHands.at(i).drawHand() << endl;
					playerHands.at(i) = (playerHands.at(i)+dealerHand);
					playerHands.at(i).sortByFace();
				}

				if(winnerCount){
					for(int i = 0; i < numOfPlayers; i++)
						if(!loser[i]) {
							cout << "Player " << playerHands.at(i).getOwnerName() << " wins " << pot << "$ with " << evaluate.at(i).printEvaluation() << "." << endl;
							credit[i]+=pot;
							break;
						}
				} else {
					cout << "Tie between players: " << endl;
					for(int i = 0; i < numOfPlayers; i++)
						if(!loser[i]){
							cout << playerHands.at(i).getOwnerName() << " with " << evaluate.at(i).printEvaluation() << endl;
							credit[i]+=pot/winnerCount;
						}
					cout << "Each wins " << pot/winnerCount << "$." << endl;
				}
			}
//Shift dealer mask
			if(turn==0)stage = stage<<3;else stage = stage<<1;
		}
		pause();
		loop++;
	}
}

const vector<Hand>& PokerGame::getPlayerHands() const {
	return playerHands;
}

void PokerGame::setPlayerHands(const vector<Hand>& playerHands) {
	this->playerHands = playerHands;
}

unsigned short PokerGame::getGameType() const {
	return gameType;
}

void PokerGame::setGameType(unsigned short gameType) {
	(gameType>0&&gameType<3)?this->gameType = gameType:this->gameType = 1;
}

unsigned short PokerGame::getNumOfPlayers() const {
	return numOfPlayers;
}

void PokerGame::setNumOfPlayers(unsigned short numOfPlayers) {
	(numOfPlayers>1&&numOfPlayers<11)?this->numOfPlayers = numOfPlayers:this->numOfPlayers = 2;
}

PokerGame::~PokerGame() {
}

