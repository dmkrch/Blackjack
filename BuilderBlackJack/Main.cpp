//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Game.h"
#include <dos.h>


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

Game* game;
Deck* deck;
Card taken_card;

int id;
double t1 = 0.3;
int x0;
int y0;
int x1;
int y1;
double ax;
double ay;
int dest_x;
int dest_y;
double t = 0;
bool cheats = false;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}

void __fastcall TForm1::N3Click(TObject *Sender)
{
	Panel1->Visible = false;
	Panel2->Visible = false;
	Panel3->Visible = false;
	Button1->Visible = false;
    Button2->Visible = false;

	static int counter = 0;

	if(counter != 0)
	{
    	game->Reset();  		   // resetting points and cards of players on the board. And setting playing state to true to everyone.
		deck->Delete_Deck(deck);   // deleting previous deck
    }

	game = new Game();
	deck = new Deck(Form1);


	String name;
	int money;
	int bots;
	int percents;

	Form1->Hide();
	Form2->ShowModal();
	Form1->Show();

	name = Form2->Edit1->Text;
	money = Form2->Edit2->Text.ToInt();
	bots = (Form2->Edit3->Text).ToInt();
	percents = Form2->Edit4->Text.ToInt();

	if(Form2->RadioButton1->Checked)
	{
		cheats = true;
	}
	else
	{
		cheats = false;
    }


	game->Make_Preparations_For_Game(bots, name, money, percents);
	deck->Show_Deck();

	Label10->Caption = name;

	String str6 = "играет";
	Label7->Caption = str6;
	Label8->Caption = str6;
	Label9->Caption = str6;
	Label24->Caption = str6;


	for(int i = 0; i < game->Amount_Of_Bots() + 1; ++i)
	{
		if (i == 0)
		{
			String str = game->Get_Money(i);
			str += " $";
			Label29->Caption = str;
		}

		else if (game->Get_Name(i) == "Bot-1")
		{
			String str = game->Get_Money(i);
			str += " $";
			Label26->Caption = str;
		}

		else if (game->Get_Name(i) == "Bot-2")
		{
			String str = game->Get_Money(i);
			str += " $";
			Label27->Caption = str;
		}

		else if (game->Get_Name(i) == "Bot-3")
		{
			String str = game->Get_Money(i);
			str += " $";
			Label28->Caption = str;
		}
	}

	Label16->Caption = 0;
	Label21->Caption = 0;
	Label22->Caption = 0;
    Label25->Caption = 0;


	if (bots == 1)
	{
		Panel1->Visible = true;
		String str = "Bot-";
		str+=1;

		Label1->Caption = str;
	}

	if (bots == 2)
	{
		String str = "Bot-";
		String str1 = "Bot-";
		str+=1;
		str1+=2;

		Label1->Caption = str;
		Label4->Caption = str1;

		Panel1->Visible = true;
		Panel2->Visible = true;
	}

	if (bots == 3)
	{
		String str = "Bot-";
		String str1 = "Bot-";
		String str2 = "Bot-";
		str+=1;
		str1+=2;
		str2+=3;

		Label1->Caption = str;
		Label4->Caption = str1;
		Label17->Caption = str2;

		Panel1->Visible = true;
		Panel2->Visible = true;
		Panel3->Visible = true;
	}


	Panel4->Visible = true;

	Button3->Visible = true;

	++counter;
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	srand(time(0));

	/*struct res{float x,y;}res;

	struct factor{float x,y;}factor;

	res.x=Screen->Width;
	res.y=Screen->Height;

	factor.x=1920/res.x;
	factor.y=1080/res.y;

    int cc=ControlCount-1; //количество объектов на форме
while(cc!=-1) //дл€ каждого объекта выполн€ем следующие операции
{
Controls[cc]->Left/=factor.x; //правильно располагаем по горизонтали
Controls[cc]->Top/=factor.y; //Епо вертикали
Controls[cc]->Width/=factor.x; //раст€гиваем до нужной ширины
Controls[cc]->Height/=factor.y; //Евысоты
cc--;
}
//теперь раст€гиваем саму форму
Form1->Width/=factor.x;
Form1->Height/=factor.y;
//измен€ем размер шрифтов; не забудьте поставить свойство формы Scaled=true
Form1->PixelsPerInch=Screen->PixelsPerInch;   */
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Button3->Visible = false;

	for (int i = 1; i <= game->Amount_Of_Bots(); i++)
	{
		if (game->Is_Playing(i))
		{

		taken_card = game->Bot_Take(i, deck, Label13, x1, y1);

		if (taken_card.Get_Value() != -1)
		{
			int cards = game->Amount_Of_Cards(i);


			if (game->Get_Name(i) == "Bot-1")
			{
				Label16->Caption = cards;
			}

			else if(game->Get_Name(i) == "Bot-2")
			{
				Label21->Caption = cards;
			}

			else if(game->Get_Name(i) == "Bot-3")
			{
				Label22->Caption = cards;
			}


			id = i;
			x0 = taken_card.Get_Face_Image()->Left;
			y0 = taken_card.Get_Face_Image()->Top;

			ax = (2 * (x1-x0)) / (t1 * t1);
			ay = (2 * (y1-y0)) / (t1 * t1);


			Timer1->Enabled = true;
			for(DWORD tt=GetTickCount();GetTickCount()-tt<1500;Sleep(1.5)) Application->ProcessMessages();
		}
        }
	}

	Label13->Caption = "¬аш ход!";

	Button1->Visible = true;
	Button2->Visible = true;

	Button3->Visible = false;
}


void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Button1->Visible = false;
	Button2->Visible = false;
	taken_card = game->Player_Take(deck, Label13, Button1, Button2);

	if (taken_card.Get_Value() != -1)
	{
		Label25->Caption = game->Amount_Of_Cards(0);


		id = 0;

		x0 = taken_card.Get_Face_Image()->Left;
		y0 = taken_card.Get_Face_Image()->Top;

		x1 = 40 + (game->Amount_Of_Cards(0) - 1) * 80;
		y1 = 380;


		ax = (2 * (x1-x0)) / (t1 * t1);
		ay = (2 * (y1-y0)) / (t1 * t1);


		Timer1->Enabled = true;
		for(DWORD tt=GetTickCount();GetTickCount()-tt<1500;Sleep(1.5)) Application->ProcessMessages();


		if (game->Is_Bots_Playing())
		{
			for (int i = 1; i <= game->Amount_Of_Bots(); i++)
			{
				if(game->Is_Playing(i))
				{
					taken_card = game->Bot_Take(i, deck, Label13, x1, y1);

					if (taken_card.Get_Value() != -1)
					{

						int cards = game->Amount_Of_Cards(i);

						if (game->Get_Name(i) == "Bot-1")
						{
							Label16->Caption = cards;
						}

						else if(game->Get_Name(i) == "Bot-2")
						{
							Label21->Caption = cards;
						}

						else if(game->Get_Name(i) == "Bot-3")
						{
							Label22->Caption = cards;
						}


						id = i;
						x0 = taken_card.Get_Face_Image()->Left;
						y0 = taken_card.Get_Face_Image()->Top;

						ax = (2 * (x1-x0)) / (t1 * t1);
						ay = (2 * (y1-y0)) / (t1 * t1);


						Timer1->Enabled = true;
						for(DWORD tt=GetTickCount();GetTickCount()-tt<1500;Sleep(1.5)) Application->ProcessMessages();
					}

					else
					{
						switch (i)
						{
							case 1:
								Label7->Caption = "пасс";
								break;
							case 2:
								Label8->Caption = "пасс";
								break;
							case 3:
								Label9->Caption = "пасс";
								break;
						}
					}
				}
			}

			Label13->Caption = "¬аш ход!";
			Button1->Visible = true;
			Button2->Visible = true;
		}

		else
		{
			Label13->Caption = "¬аш ход!";
			Button1->Visible = true;
			Button2->Visible = true;
        }
	}

	else if(game->Is_Bots_Playing())
	{
		Label24->Caption = "пасс";


		while(game->Is_Bots_Playing())
		{
			for (int i = 1; i <= game->Amount_Of_Bots(); i++)
			{
				if(game->Is_Playing(i))
				{
					taken_card = game->Bot_Take(i, deck, Label13, x1, y1);

					if (taken_card.Get_Value() != -1)
					{

						int cards = game->Amount_Of_Cards(i);

						if (game->Get_Name(i) == "Bot-1")
						{
							Label16->Caption = cards;
						}

						else if(game->Get_Name(i) == "Bot-2")
						{
							Label21->Caption = cards;
						}

						else if(game->Get_Name(i) == "Bot-3")
						{
							Label22->Caption = cards;
						}

						id = i;
						x0 = taken_card.Get_Face_Image()->Left;
						y0 = taken_card.Get_Face_Image()->Top;

						ax = (2 * (x1-x0)) / (t1 * t1);
						ay = (2 * (y1-y0)) / (t1 * t1);


						Timer1->Enabled = true;
						for(DWORD tt=GetTickCount();GetTickCount()-tt<1500;Sleep(1.5)) Application->ProcessMessages();
					}

					else
					{
						switch (i)
						{
							case 1:
								Label7->Caption = "пасс";
								break;
							case 2:
								Label8->Caption = "пасс";
								break;
							case 3:
								Label9->Caption = "пасс";
								break;
						}
					}
				}
			}
		}

		/* end of round */
		game->End_Of_Round(game, deck);
	}

	else
	{
		Label24->Caption = "пасс";

		/* end of round */
		game->End_Of_Round(game, deck);
	}
}


void __fastcall TForm1::Button2Click(TObject *Sender)
{
	game->Player_Pass(Label13, Button1, Button2);

    Label24->Caption = "пасс";

	while(game->Is_Bots_Playing())
	{
		for (int i = 1; i <= game->Amount_Of_Bots(); i++)
		{
			if(game->Is_Playing(i))
			{
				taken_card = game->Bot_Take(i, deck, Label13, x1, y1);

				if (taken_card.Get_Value() != -1)
				{

					int cards = game->Amount_Of_Cards(i);

					if (game->Get_Name(i) == "Bot-1")
					{
						Label16->Caption = cards;
					}

					else if(game->Get_Name(i) == "Bot-2")
					{
						Label21->Caption = cards;
					}

					else if(game->Get_Name(i) == "Bot-3")
					{
						Label22->Caption = cards;
					}


					id = i;
					x0 = taken_card.Get_Face_Image()->Left;
					y0 = taken_card.Get_Face_Image()->Top;

					ax = (2 * (x1-x0)) / (t1 * t1);
					ay = (2 * (y1-y0)) / (t1 * t1);


					Timer1->Enabled = true;
					for(DWORD tt=GetTickCount();GetTickCount()-tt<1500;Sleep(1.5)) Application->ProcessMessages();
				}

				else
				{
					switch (i)
					{
						case 1:
							Label7->Caption = "пасс";
							break;
						case 2:
							Label8->Caption = "пасс";
							break;
						case 3:
							Label9->Caption = "пасс";
							break;
					}
				}
			}
		}
	}

    /* end of round */
	game->End_Of_Round(game, deck);
}

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if (id == 0)
	{
		t += ((double)Timer1->Interval / 1000);

		dest_x = ax* t * t;
		dest_y = ay* t * t;

		taken_card.Get_Face_Image()->Hide();
		taken_card.Get_Back_Image()->Hide();

		taken_card.Get_Face_Image()->Left = x0 + dest_x;
		taken_card.Get_Back_Image()->Left = x0 + dest_x;
		taken_card.Get_Face_Image()->Top = y0 + dest_y;
		taken_card.Get_Back_Image()->Top = y0 + dest_y;

		taken_card.Get_Back_Image()->Show();

		if (taken_card.Get_Back_Image()->Left < x1)
		{
			taken_card.Get_Back_Image()->Hide();
			taken_card.Get_Face_Image()->Show();
			Timer1->Enabled = false;

			t = 0;
		}
	}

	else
	{
		t += ((double)Timer1->Interval / 1000);

		dest_x = ax* t * t;
		dest_y = ay* t * t;

		taken_card.Get_Face_Image()->Hide();
		taken_card.Get_Back_Image()->Hide();

		taken_card.Get_Face_Image()->Left = x0 + dest_x;
		taken_card.Get_Back_Image()->Left = x0 + dest_x;
		taken_card.Get_Face_Image()->Top = y0 + dest_y;
		taken_card.Get_Back_Image()->Top = y0 + dest_y;

		taken_card.Get_Back_Image()->Show();

		if (taken_card.Get_Back_Image()->Left < x1)
		{
			taken_card.Get_Back_Image()->BringToFront();
			taken_card.Get_Face_Image()->BringToFront();

			if (cheats)
			{
				taken_card.Get_Face_Image()->Show();
				taken_card.Get_Back_Image()->Hide();
			}
			else
			{
				taken_card.Get_Face_Image()->Hide();
                taken_card.Get_Back_Image()->Show();
            }


			Timer1->Enabled = false;

			t = 0;
		}
    }
}


void __fastcall TForm1::N2Click(TObject *Sender)
{
    ShowMessage("Game 21 points. Version 1.0 by dmkrch");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

