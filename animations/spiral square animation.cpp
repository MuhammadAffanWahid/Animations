#include<iostream>
#include<windows.h>
using namespace std;
#include<conio.h>
#include<math.h>

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void Wait(int T)
{
	for (int i = 0; i < 100000 * T; i++);
}
void L2R(int R, int si, int ei, int T, char Sym)
{
	for (int i = si; i <= ei; i++)
	{
		gotoRowCol(R, i);
		cout << Sym;
		Wait(T);
	}
}
void T2B(int C, int si, int ei, int T, char Sym)
{
	for (int i = si; i <= ei; i++)
	{
		gotoRowCol(i, C);
		cout << Sym;
		Wait(T);
	}
}
void R2L(int R, int C, int si, int ei, int T, char Sym)
{
	for (int i = si; i <= ei; i++)
	{
		gotoRowCol(R, C - i);
		cout << Sym;
		Wait(T);
	}
}
void B2T(int C, int si, int ei, int T, char Sym)
{
	for (int i = ei; i > si; i--)
	{
		gotoRowCol(i, C);
		cout << Sym;
		Wait(T);
	}
}
void PrintAnimation(int Rows, int Cols, char Sym, int T)
{
	for (int ri = 0; ri < Rows / 2 - 8; ri++)
	{
		L2R(ri, ri, Cols - ri - 2, T, Sym);
		T2B(Cols - ri - 1, ri, Cols - ri - 6, T, Sym);
		R2L(Rows - ri - 5, Cols - 1, ri, Cols - ri - 1, T, Sym);
		B2T(ri, ri, Cols - ri - 5, T, Sym);
	}
}
int main()
{
	int Rows = 100, Cols = 100, T = 30;  //Set Width=100 and Height=96
	char Sym = '*';
	PrintAnimation(Rows, Cols, Sym, T);
	return _getch();
}