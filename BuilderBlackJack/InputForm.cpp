//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "InputForm.h"
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
int clicks = 0;


//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	int incorrect_counter = 0;

	 String money = Edit2->Text;
	 String bots = Edit3->Text;
	 String bet = Edit4->Text;


	 if (money.Length() > 5)
	 {
		++incorrect_counter;
	 }

	 for(int i = 1; i <= money.Length(); ++i)
	 {
		 if(money[i] > '9' || money[i] < '0')
			incorrect_counter++;
	 }



	 if (bots.Length() > 1)
	 {
		   ++incorrect_counter;
	 }

	 for (int i = 1; i <= bots.Length(); i++)
	 {
		if(bots[i] > '3' || bots[i] < '1')
			incorrect_counter++;
	 }



	 if (bet.Length() > 2)
	 {
		 incorrect_counter++;
	 }

	 for (int i = 1; i <= bet.Length(); i++)
	 {
		if(bet[i] > '9' || bet[i] < '0')
			incorrect_counter++;
	 }




	if(incorrect_counter == 0)
		Form2->Close();

	else
        ShowMessage("Неправильный ввод!");
}

