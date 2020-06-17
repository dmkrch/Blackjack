#include <vector>
#include <string>
#include <iostream>
#include <vcl.h>

#ifndef DeckH
#define DeckH


class Card
{
	private:
		int value;           // value of a card.    Jack - 2, Queen - 3 and etc.
		TImage* face_image;  // stores image component of a side with all information about card
		TImage* back_image;  // stores image component of the other side with no information about card

	public:
		Card()
		{

		}

		Card(int value, TImage* face_image, TImage* back_image)
		{
			this->value = value;
			this->face_image = face_image;
			this->back_image = back_image;
		}

		int Get_Value()
		{
			return value;
		}

		TImage* Get_Face_Image()
		{
			return face_image;
		}

		TImage* Get_Back_Image()
		{
			return back_image;
		}

		void Set_Value(int val)
		{
            value = val;
		}

		void Delete_Card()
		{
			delete(face_image);
			delete(back_image);
        }
};


class Deck
{
private:
	std::vector<Card> deck;


public:
	Deck(TForm* Form1);


	Card Get_Card(int i);

	Card Show_Card(int i);

	int Get_Deck_Size();

	void Show_Deck();

	void Delete_Deck(Deck* deck);
};


#endif
