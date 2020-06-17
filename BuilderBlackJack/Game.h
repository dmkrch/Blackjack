#include <vector>
#include "Player.h"
#include <string>
#include <vcl.h>
#include "Main.h"


#ifndef GameH
#define GameH

class Game
{
private:
	int rounds;
	double bet_money; // ammount of money that player must bet
	std::vector<Player> players;

public:
	Game();


	/* Function makes preparationos to the game */
	void Make_Preparations_For_Game(int bots, String name, int money, int percents);

	/* Function adds players to the game */
	void Add_Player(Player player);

	/* Functions returns true if at least one player still plays and false if noone plays */
	bool Is_Playing(int i);

	/* Resets all player information for next round */
	void Reset();

	/* Functions retuens true if at least one bot still plays and false if noone plays */
	bool Is_Bots_Playing();

	/* Returns true if player is still playing and false if he passed */
	bool Is_Player_Playing();

	/* Player takes a card */
	Card Player_Take(Deck* deck, TLabel* Label13, TButton* Button1, TButton* Button2);

	/* Player passes */
	void Player_Pass(TLabel* Label13, TButton* Button1, TButton* Button2);

	int Amount_Of_Cards(int i);

	int Amount_Of_Bots();

	Card Bot_Take(int i, Deck* deck, TLabel* Label13, int&, int&);

	int Get_Money(int i);

	int Get_Points(int i);

	String Get_Name(int i);

	std::vector<int> Find_Winners();

	void Change_Money(std::vector<int> winners_id);

	void Bot_Pass(int i);

	void End_Of_Round(Game* game, Deck* deck);
};
#endif
