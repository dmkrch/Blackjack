#pragma hdrstop

#include "Game.h"

#pragma package(smart_init)


Game::Game()
{
	bet_money = 0;
	rounds = 0;
}


void Game::Make_Preparations_For_Game(int amount_of_bots, String name, int money, int percents)
{
	Player player(name, money, false);
	Add_Player(player);

	for (int i = 0; i < amount_of_bots; ++i)
	{
		String name = "Bot-";
		name += (String)(i+1);

		Player bot(name, money, true);

		Add_Player(bot);
	}

	bet_money = (double)money * percents / 100;
}

void Game::Add_Player(Player player)
{
	players.push_back(player);
}

bool Game::Is_Playing(int i)
{
	if (players[i].Is_Playing() == true)
		return true;

	return false;
}

void Game::Reset()
{
	for (int i = 0; i < players.size(); ++i)
	{
		players[i].Set_Playing_State(true);
		players[i].Reset_Cards();
		players[i].Reset_Points();
	}
}

bool Game::Is_Bots_Playing()
{
	for (int i = 1; i < players.size(); ++i)
	{
		if (players[i].Is_Playing() == true)
			return true;
	}

	return false;
}

bool Game::Is_Player_Playing()
{
	return players[0].Is_Playing();
}

Card Game::Player_Take(Deck* deck, TLabel* Label13, TButton* Button1, TButton* Button2)
{
	Card null_card;
	Card curr_card;

	null_card.Set_Value(-1);

	if (players[0].Get_Points() < 21)
	{
		curr_card = players[0].Take_Card(deck, Label13);

		String str1 = "Вы взяли карту";
		Label13->Caption = str1;

		return curr_card;
	}

	else
	{
		Label13->Caption = "21 очко и больше";
		for(DWORD tt=GetTickCount();GetTickCount()-tt<1000;Sleep(1)) Application->ProcessMessages();

		Player_Pass(Label13, Button1, Button2);

		return null_card;
	}
}

void Game::Player_Pass(TLabel* Label13, TButton* Button1, TButton* Button2)
{
	players[0].Set_Playing_State(false);

	Label13->Caption = "Вы пасуете";

	Button1->Visible = false;
	Button2->Visible = false;

	for(DWORD tt=GetTickCount();GetTickCount()-tt<1000;Sleep(1)) Application->ProcessMessages();
}

int Game::Amount_Of_Cards(int i)
{
	return players[i].Get_Amount_Of_Cards();
}

int Game::Amount_Of_Bots()
{
	return (players.size() - 1);
}

Card Game::Bot_Take(int i, Deck* deck, TLabel* Label13, int& x1, int& y1)
{
	Card null_card;
	null_card.Set_Value(-1);


	if (players[i].Is_Playing())
	{
		String str = "Bot-";
		str += String(i);
		str += " ход";

		Label13->Caption = str;
		for(DWORD tt=GetTickCount();GetTickCount()-tt<1000;Sleep(1)) Application->ProcessMessages();

		if (players[i].Get_Points() < 21)
		{
			if (players[i].Is_Taking_Card(deck))
			{
				Card card = players[i].Take_Card(deck, Label13);

				String str = "Bot-";
				str += String(i);
				str += " берет карту";

				Label13->Caption = str;

				x1= 40 + 190 * (i - 1);
				y1 = 90 + players[i].Get_Amount_Of_Cards() * 17;

				return card;
			}
			else
			{
				String str = "Bot-";
				str+= i;
				str += " пасует";

				Label13->Caption = str;

				for(DWORD tt=GetTickCount();GetTickCount()-tt<1000;Sleep(1)) Application->ProcessMessages();

				players[i].Set_Playing_State(false);
			}
		}
		else
		{
			String str = "Bot-";
			str+= i;
			str += " пасует";

			Label13->Caption = str;

			for(DWORD tt=GetTickCount();GetTickCount()-tt<1000;Sleep(1)) Application->ProcessMessages();

			players[i].Set_Playing_State(false);
		}
	}

	return null_card;
}

int Game::Get_Money(int i)
{
	return players[i].Get_Money();
}

int Game::Get_Points(int i)
{
	return players[i].Get_Points();
}

String Game::Get_Name(int i)
{
	return players[i].Get_Name().c_str();
}

std::vector<int> Game::Find_Winners()
{
	std::vector<int> winners_id;

	int max_id = 0;
	int max_points = 0;

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].Get_Points() > max_points && players[i].Get_Points() <= 21)
		{
			max_points = players[i].Get_Points();
			max_id = i;
		}
	}

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].Get_Points() == max_points)
		{
			winners_id.push_back(i);
		}
	}


	return winners_id;
}

void Game::Change_Money(std::vector<int> winners_id)
{
	int total_money = 0;
	int add_money = 0;

	for (int i = 0; i < players.size(); i++)
	{
		int k;

		for (k = 0; k < winners_id.size(); ++k)
		{
			if (winners_id[k] == i)
			{
				break;
			}
		}

		if (k == winners_id.size())
		{
			if(players[i].Get_Money() > bet_money)
			{
				players[i].Set_Money(players[i].Get_Money() - bet_money);
				total_money += bet_money;
			}

			else
			{
				total_money += players[i].Get_Money();
				players[i].Set_Money(0);
			}
        }
	}

	add_money = total_money / winners_id.size();

	for(int i = 0; i < winners_id.size(); ++i)
	{
		players[winners_id[i]].Set_Money(players[winners_id[i]].Get_Money() + add_money);
	}
}


void Game::Bot_Pass(int i)
{
	players[i].Set_Playing_State(false);
}

void Game::End_Of_Round(Game* game, Deck* deck)
{
	/* a lot of code both to prepare info for next round and show on output form winners */
	Form1->Hide();


	/* showing winners on output form */
	for (int i = 0; i < game->Amount_Of_Bots() + 1; i++)
	{
		if (game->Get_Money(i) != 0) // if money != 0
		{
			if (i == 0)
			{
				Form3->Panel1->Visible = true;
				Form3->Label2->Caption = game->Get_Points(i);
			}

			else if(game->Get_Name(i) == "Bot-1")
			{
				Form3->Panel2->Visible = true;
				Form3->Label4->Caption = game->Get_Name(i);
				Form3->Label5->Caption = game->Get_Points(i);
			}

			else if(game->Get_Name(i) == "Bot-2")
			{
				Form3->Panel3->Visible = true;
				Form3->Label7->Caption = game->Get_Name(i);
				Form3->Label8->Caption = game->Get_Points(i);
			}

			else if(game->Get_Name(i) == "Bot-3")
			{
				Form3->Panel4->Visible = true;
				Form3->Label10->Caption = game->Get_Name(i);
				Form3->Label11->Caption = game->Get_Points(i);
			}
		}
	}



	// display winner on output form
	std::vector<int> winners_id = game->Find_Winners();

	String winner = "Winner: ";

	for(int i = 0; i < winners_id.size(); ++i)
	{
		winner+= game->Get_Name(winners_id[i]);

		if (i + 1 != winners_id.size())
		{
			winner+= ", ";
		}
	}
	Form3->Label13->Caption = winner;


	Form3->ShowModal();

	/* here we need to change money */
	game->Change_Money(winners_id);

	/* here we need to show new money, points of players */
	for(int i = 0; i < game->Amount_Of_Bots() + 1; ++i)
	{
			if (i == 0)
			{
				Form1->Label25->Caption = "0";
				String str = game->Get_Money(i);
				str += " $";
				Form1->Label29->Caption = str;
			}

			else if (game->Get_Name(i) == "Bot-1")
			{
				Form1->Label16->Caption = "0";
				String str = game->Get_Money(i);
				str += " $";
				Form1->Label26->Caption = str;
			}

			else if (game->Get_Name(i) == "Bot-2")
			{
				Form1->Label21->Caption = "0";
				String str = game->Get_Money(i);
				str += " $";
				Form1->Label27->Caption = str;
			}

			else if (game->Get_Name(i) == "Bot-3")
			{
				Form1->Label22->Caption = "0";
				String str = game->Get_Money(i);
				str += " $";
				Form1->Label28->Caption = str;
			}
	}


	game->Reset();  		   // resetting points and cards of players on the board. And setting playing state to true to everyone.
	deck->Delete_Deck(deck);   // deleting previous deck
	deck = new Deck(Form1);    // creating new one


	/* now we need to check if anybody has money = 0. If true - set his playing state to false */
	for (int i = 0; i < game->Amount_Of_Bots() + 1; ++i)
	{
		if (game->Get_Money(i) == 0)
		{
			if (i == 0)
			{
				Form1->Label29->Caption = players[i].Get_Money();
				Form1->Label24->Caption = "выбыл";

				game->Player_Pass(Form1->Label13, Form1->Button1, Form1->Button2);

				ShowMessage("Вы проиграли");
                Application->Terminate();
			}

			if (game->Get_Name(i) == "Bot-1")
			{
				Form3->Panel2->Visible = false;
				Form1->Label7->Caption = "выбыл";
				Form1->Label26->Caption = players[i].Get_Money();
				game->Bot_Pass(i);
			}

			else if(game->Get_Name(i) == "Bot-2")
			{
				Form3->Panel3->Visible = false;
				Form1->Label8->Caption = "выбыл";
				Form1->Label28->Caption = players[i].Get_Money();
				game->Bot_Pass(i);
			}

			else if(game->Get_Name(i) == "Bot-3")
			{
				Form3->Panel4->Visible = false;
				Form1->Label9->Caption = "выбыл";
				Form1->Label28->Caption = players[i].Get_Money();
				game->Bot_Pass(i);
			}
		}
	}


	/* we need to check if bots has != 0 money */
	int temp = 0;

	for (int i = 1; i < game->Amount_Of_Bots() + 1; ++i)
	{
		if (game->Get_Money(i) == 0)
		{
			++temp;
		}
	}

	if (temp == game->Amount_Of_Bots())
	{
		ShowMessage("Вы выиграли!!!");
		Application->Terminate();
	}


	/* setting state of players */
	for (int i = 0; i < game->Amount_Of_Bots() + 1; i++)
	{
		if(game->Is_Playing(i))
		{
			if (i == 0)
			{
				Form1->Label24->Caption = "играет";
			}

			if (i == 1)
			{
				Form1->Label7->Caption = "играет";
			}

			else if(i == 2)
			{
				Form1->Label8->Caption = "играет";
			}

			else if(i == 3)
			{
				Form1->Label9->Caption = "играет";
			}
		}

	}



	/* showing form and additional options */
	Form1->Show();
	Form1->Button3->Visible = true;

	Form1->Label13->Caption = "";
	deck->Show_Deck();
}
