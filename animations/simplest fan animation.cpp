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
void PrintAnimation(int Rows, int Cols, char Sym, int T,int gap)
{
	gotoRowCol(Rows / 2, Cols / 2 - 5);
	cout << "Hello CFP!";
	while (true)
	{
		for (int ri = 0; ri < Rows / 2 - 8; ri++)
		{
			if (ri % gap == 0)
			{
				L2R(ri, ri, Cols - ri - 2, T, Sym);
				T2B(Cols - ri - 1, ri, Cols - ri - 2, T, Sym);
				R2L(Rows - ri - 1, Cols - 1, ri, Cols - ri - 1, T, Sym);
				B2T(ri, ri, Cols - ri - 1, T, Sym);
				Sym++;
			}
		}
		for (int ri = Rows / 2 - 9; ri >= 0; ri--)
		{
			if (ri % gap == 0)
			{
				T2B(ri, ri, Cols - ri - 2, T, ' ');
				L2R(Cols - ri - 1, ri, Cols - ri - 2, T, ' ');
				B2T(Rows - ri - 1, ri, Cols - ri - 1, T, ' ');
				R2L(ri, Cols - 1, ri, Cols - ri - 1, T, ' ');
			}
		}
	}
}
void PrintNTimes(int N,char Sym)
{
	for (int i = 0; i < N; i++) cout << Sym;
}
void PrintVerticalFan()
{
	int H = 30;
	char Sym = '*';
	PrintNTimes(H - 1, Sym);
	cout << endl;
	for (int i = 2; i < H / 2; i++)
	{
		PrintNTimes(i-1, ' ');
		cout << Sym;
		PrintNTimes(2 * (H / 2 - i) - 1, ' ');
		cout << Sym << endl;
	}
	PrintNTimes(H / 2 - 1, ' ');
	cout << Sym << endl;
	for (int i = 1; i < H / 2 - 1; i++)
	{
		PrintNTimes(H/2 - i - 1, ' ');
		cout << Sym;
		PrintNTimes(2 * (i) - 1, ' ');
		cout << Sym << endl;
	}
	PrintNTimes(H - 1, Sym);
}
void PrintHorizontalFan()
{
	int H = 30;
	char Sym = '*';
	cout << Sym;
	PrintNTimes(H - 3, ' ');
	cout << Sym << endl;
	for (int i = 2; i < H / 2; i++)
	{
		cout << Sym;
		PrintNTimes(i-2, ' ');
		cout << Sym;
		PrintNTimes(H- 2*i -1, ' ');
		cout << Sym;
		PrintNTimes(i-2, ' ');
		cout << Sym;
		cout << endl;
	}
	cout << Sym;
	PrintNTimes(H / 2 - 2, ' ');
	cout << Sym;
	PrintNTimes(H / 2 - 2, ' ');
	cout << Sym << endl;
	for (int i = 1; i < H / 2 - 1; i++)
	{
		cout << Sym;
		PrintNTimes(H/2 - i - 2, ' ');
		cout << Sym;
		PrintNTimes(2*(i)-1, ' ');
		cout << Sym;
		PrintNTimes(H / 2 - i - 2, ' ');
		cout << Sym;
		cout << endl;
	}
	cout << Sym;
	PrintNTimes(H - 3, ' ');
	cout << Sym;
}
int mainAnimation()
{
	int Rows = 100, Cols = 100, T = 10,gap = 1;  //Set Width=100 and Height=100
	char Sym = 'A';
	PrintAnimation(Rows, Cols, Sym, T, gap);
	return _getch();
}
int main()
{
	int T = 4000;
	while (true)
	{
		PrintVerticalFan();
		Wait(T);
		system("cls");
		PrintHorizontalFan();
		Wait(T);
		system("cls");
		if (T > 400) T -= 400;
	}
		return _getch();
}