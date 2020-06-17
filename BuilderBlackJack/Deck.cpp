//---------------------------------------------------------------------------

#pragma hdrstop

#include "Deck.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


Deck::Deck(TForm* Form1)
{
	int val = 0;

	for (int i = 0; i < 40; i++)
	{
		if (i % 4 == 0)
			++val;

		TImage* face = new TImage(Form1);
		TImage* back = new TImage(Form1);

		face->Parent = Form1;
		back->Parent = Form1;

		String str = "Images\\";
		str += i;
		str += ".bmp";

		face ->Picture->LoadFromFile(str);
		back ->Picture->LoadFromFile("Images\\52.bmp");


		if (i < 20)
		{
		face->Top = 168 + i*2;
		face->Left = 580 + i*2;
		back->Top = 168 + i*2;
		back->Left = 580 + i*2;
		}

		else
		{
		face->Top = 168 + 19*2;
		face->Left = 580 + 19*2;
		back->Top = 168 + 19*2;
		back->Left = 580 + 19*2;
        }

		face->Hide();
		back->Hide();

		Card card(val, face, back);

		deck.push_back(card);
	}

	val = 1;

	for (int i = 40; i < 52; i++)
	{
		if (i % 4 == 0)
			++val;

		TImage* face = new TImage(Form1);
		TImage* back = new TImage(Form1);

		face->Parent = Form1;
		back->Parent = Form1;

		String str = "Images\\";
		str += i;
		str += ".bmp";

		face ->Picture->LoadFromFile(str);
		back ->Picture->LoadFromFile("Images\\52.bmp");


		face->Top = 168 + 19*2;
		face->Left = 580 + 19*2;

		back->Top = 168 + 19*2;
		back->Left = 580 + 19*2;

		face->Hide();
		back->Hide();

		Card card(val, face, back);

		deck.push_back(card);
	}


}

Card Deck::Get_Card(int i)
{
	Card card = deck[i];

	deck.erase(deck.begin() + i);

	return card;
}

Card Deck::Show_Card(int i)
{
	Card card = deck[i];

    return card;
}

int Deck::Get_Deck_Size()
{
	return deck.size();
}

void Deck::Show_Deck()
{
	for (int i = 0; i < 20; i++)
	{
		deck[i].Get_Back_Image()->Show();
	}
}

void Deck::Delete_Deck(Deck* deck)
{
	for (int i = 0; i < deck->Get_Deck_Size(); i++)
	{
		deck->deck[i].Delete_Card();
	}

	deck->deck.clear();

	delete deck;
}
