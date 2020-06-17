#include <string>
#include <vector>
#include "Deck.h"
#include <ctime>
#include <stdlib.h>
#include <vcl.h>


#ifndef PlayerH
#define PlayerH

class Player
{
private:
	String name;			    // name of player
	std::vector<Card> cards;	// player's hand cards
	int points;					// amount of points
	int money;					// amount of money
	bool is_playing;			// if player is still playing
	bool is_bot;				// if player is bot


public:
	Player(String name, int money, bool is_bot);

	/* Function that takes a card from deck and passes it to player's hand cards */
	Card Take_Card(Deck* deck, TLabel* Label);

	/* Function sets state of player: if he still plays or passes */
	void Set_Playing_State(bool state);

	/* Function returns true if player still plays and false if he doesn't */
	bool Is_Playing();

	/* Function returns true if player is bot and false if he is human */
	bool Is_Bot();

	/* Function returns player's points */
	int Get_Points();

	/* Function returns current money of player */
	int Get_Money();

	/* Function returns name of player */
	String Get_Name();

	/* Function returns true if bot decided to take card and false if not to take one */
	bool Is_Taking_Card(Deck* deck);

	/* Resets cards of player */
	void Reset_Cards();

	/* Resets points of player */
	void Reset_Points();

	int Get_Amount_Of_Cards();

	void Set_Money(int money);
};

#endif
