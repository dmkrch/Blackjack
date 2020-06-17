//---------------------------------------------------------------------------

#pragma hdrstop

#include "Player.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


Player::Player(String name, int money, bool is_bot)
{
	this->name = name;
	this->money = money;
	this->is_bot = is_bot;
	this->points = 0;
	this->is_playing = true;
}

Card Player::Take_Card(Deck* deck, TLabel* Label)
{
	int random_index;

	random_index = rand() % deck->Get_Deck_Size();  // getting random id from 0 to current deck size

	Card card = deck->Get_Card(random_index);		// takes a card from deck
	points += (int)card.Get_Value();				// adds points equal to card

	cards.push_back(card);							// pushing this card to player's hand cards

	return card;
}

void Player::Set_Playing_State(bool state)
{
	is_playing = state;
}

bool Player::Is_Playing()
{
	return is_playing;
}

bool Player::Is_Bot()
{
	return is_bot;
}

int Player::Get_Points()
{
	return points;
}

int Player::Get_Money()
{
	return money;
}

String Player::Get_Name()
{
	return name;
}

bool Player::Is_Taking_Card(Deck* deck)
{
	int random_number;
	int needed_points = 21 - points;
	int amount_of_suitable_cards = 0;
	int chance_for_taking_suitable_card = 0;

	for (int i = 0; i < deck->Get_Deck_Size(); ++i)
	{
		if (deck->Show_Card(i).Get_Value() <= needed_points)
		{
			++amount_of_suitable_cards;
		}
	}

	chance_for_taking_suitable_card = (amount_of_suitable_cards * 100) / deck->Get_Deck_Size();

	if (chance_for_taking_suitable_card > 75)
		return true;

	else if (chance_for_taking_suitable_card < 10)
		return false;

	else
	{
		random_number = rand() % 100;

		if (random_number > chance_for_taking_suitable_card)
			return false;
		else
			return true;
	}
}

void Player::Reset_Cards()
{
	for (int i = 0; i < cards.size(); i++)
	{
        cards[i].Delete_Card();
	}
	cards.clear();
}

void Player::Reset_Points()
{
	points = 0;
}

int Player::Get_Amount_Of_Cards()
{
	return cards.size();
}

void Player::Set_Money(int money)
{
    this->money = money;
}
