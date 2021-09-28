#include<iostream>
#include<conio.h>
#include<math.h>
#include<windows.h>
using namespace std;

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void PrintCircle(int cr, int cc, int R, char sym, int sa = 0, int ea = 359)
{
	for (int an = sa; an <= ea; an++)
	{
		int r = ceil(R * -sin(an * 3.1415 / 180) + cr);
		int c = ceil(R * cos(an * 3.1415 / 180) + cc);
		gotoRowCol(r, c);
		cout << sym;
	}
}
void PrintDonut(int cr, int cc, int R, char sym, int X, int sa = 0, int ea = 359)
{
	for (int an = sa; an <= ea; an += X)
	{
		int r = ceil(R * -sin(an * 3.1415 / 180) + cr);
		int c = ceil(R * cos(an * 3.1415 / 180) + cc);
		gotoRowCol(r, c);
		PrintCircle(r, c, R / 4, sym);
	}
}
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
void wait(int T)
{
	for (int i = 0; i < 100000 * T; i++);
}
void B2T(int sr, int sc, int ln, int T, char Sym)
{
	for (int i = 0; i < ln; i++)
	{
		gotoRowCol(sr - i, sc);
		cout << Sym;
		wait(T);
	}
}
void L2R(int sr, int sc, int ln, int T, char Sym)
{
	for (int i = 0; i < ln; i++)
	{
		gotoRowCol(sr, sc + i);
		cout << Sym;
		wait(T);
	}
}
void T2B(int sr, int sc, int ln, int T, char Sym)
{
	for (int i = 0; i < ln; i++)
	{
		gotoRowCol(sr + i, sc);
		cout << Sym;
		wait(T);
	}
}
void R2L(int sr, int sc, int ln, int T, char Sym)
{
	for (int i = 0; i < ln; i++)
	{
		gotoRowCol(sr, sc - i);
		cout << Sym;
		wait(T);
	}
}
void DiaL2R(int sr, int sc, int ln, int T, char Sym)
{
	for (int i = 0; i < ln; i++)
	{
		gotoRowCol(sr - i, sc + i);
		cout << Sym;
		wait(T);
	}
}
void DiaR2L(int sr, int sc, int ln, int T, char Sym)
{
	for (int i = 0; i < ln; i++)
	{
		gotoRowCol(sr - i, sc - i);
		cout << Sym;
		wait(T);
	}
}
void PrintSpiral(int cr, int cc, int size, int arms, char sym)
{
	float R = 0.0;
	float inc = size / (360.0 * arms);
	for (int an = 0; an < 360 * arms; an++)
	{
		float r = ceil(R * -sin(an * 3.1415 / 180.0) + cr);
		float c = ceil(R * cos(an * 3.1415 / 180.0) + cc);
		gotoRowCol(r, c);
		cout << sym;
		R += inc;
	}
}
void PrintFan(int cr, int cc, int s, char sym)
{
	int n;
	int c = 14;
	PrintCircle(cr, cc, s + 1, sym);
	while (true)
	{
		n = c / 10;
		for (int k = 0; k <= 119; k += n)
		{
			for (int i = 0; i <= s; i++)
			{
				PrintCircle(cr, cc, i, sym, 0 + k, 0 + k);
				PrintCircle(cr, cc, i, sym, 120 + k, 120 + k);
				PrintCircle(cr, cc, i, sym, 240 + k, 240 + k);
			}
			wait(10);
			for (int i = 0; i <= s; i++)
			{
				PrintCircle(cr, cc, i, ' ', 0 + k, 0 + k);
				PrintCircle(cr, cc, i, ' ', 120 + k, 120 + k);
				PrintCircle(cr, cc, i, ' ', 240 + k, 240 + k);
			}
		}
		if (n < 15)
		{
			c += 3;
		}
	}
}
void PrintSinWave(int cr, int si, int Cols, int amp, int W, char sym)
{
	W *= 2;
	int r, c;
	float da = 360.0 * W / Cols;
	for (float a = si; a < 360.0 * W + si; a += da)
	{
		c = (a - si) / da;
		r = (sin(a * 3.14 / 360.0) * amp * -1) + cr;
		gotoRowCol(r, c);
		cout << sym;
	}
}
void PrintSnake(int cr, int Cols, int amp, int W, char sym)
{
	while (true)
	{
		for (int si = 0; si <= 719; si += 5)
		{
			PrintSinWave(cr, si, Cols, amp, W, sym);
			wait(20);
			PrintSinWave(cr, si, Cols, amp, W, ' ');
		}
	}
}
void PrintLetterA(int sr, int sc, int s, char sym)
{
	int T = 0;
	L2R(sr, sc, s / 2 + 1, T, sym);
	R2L(sr, sc, s / 2 + 1, T, sym);
	DiaL2R(sr, sc - s / 2 - 1, s / 2 + 2, T, sym);
	DiaR2L(sr, sc + s / 2 + 1, s / 2 + 2, T, sym);
	DiaL2R(sr + s / 2, sc - s, s / 2 + 1, T, sym);
	DiaR2L(sr + s / 2, sc + s, s / 2 + 1, T, sym);

}
void PrintLetterN(int sr, int sc, int s, char sym)
{
	int T = 0;
	DiaR2L(sr + s / 2, sc + s / 2, s, T, sym);
	T2B(sr - s / 2, sc - s / 2, s + 1, T, sym);
	B2T(sr + s / 2, sc + s / 2, s + 1, T, sym);
}
void PrintLetterS(int sr, int sc, int s, char sym)
{
	int T = 0;
	PrintCircle(sr + s / 3 - 1, sc, s / 3, sym, -150, 90);
	PrintCircle(sr - s / 3, sc, s / 3, sym, 30, 270);
}
void LetterAnimationA(int Rows, int Cols, int s, char sym)
{
	for (int i = Rows / 5; i <= 4 * Rows / 5; i++)
	{
		PrintLetterA(i, Cols / 2, 20, sym);
		wait(100);
		PrintLetterA(i, Cols / 2, 20, ' ');
	}
	for (int i = Cols / 5; i <= 4 * Cols / 5; i++)
	{
		PrintLetterA(Rows / 2, i, 20, sym);
		wait(100);
		PrintLetterA(Rows / 2, i, 20, ' ');
	}
	for (int i = Cols / 5; i <= 4 * Cols / 5; i++)
	{
		PrintLetterA(i, i, 20, sym);
		wait(100);
		PrintLetterA(i, i, 20, ' ');
	}
	for (int i = Cols / 5; i <= 4 * Cols / 5; i++)
	{
		PrintLetterA(Rows - i, Cols - i, 20, sym);
		wait(100);
		PrintLetterA(Rows - i, Cols - i, 20, ' ');
	}
}
void LetterAnimationN(int Rows, int Cols, int s, char sym)
{
	for (int i = Rows / 5; i <= 4 * Rows / 5; i++)
	{
		PrintLetterN(i, Cols / 2, 20, sym);
		wait(100);
		PrintLetterN(i, Cols / 2, 20, ' ');
	}
	for (int i = Cols / 5; i <= 4 * Cols / 5; i++)
	{
		PrintLetterN(Rows / 2, i, 20, sym);
		wait(100);
		PrintLetterN(Rows / 2, i, 20, ' ');
	}
	for (int i = Cols / 5; i <= 4 * Cols / 5; i++)
	{
		PrintLetterN(i, i, 20, sym);
		wait(100);
		PrintLetterN(i, i, 20, ' ');
	}
	for (int i = Cols / 5; i <= 4 * Cols / 5; i++)
	{
		PrintLetterN(Rows - i, Cols - i, 20, sym);
		wait(100);
		PrintLetterN(Rows - i, Cols - i, 20, ' ');
	}
}
void LetterAnimationS(int Rows, int Cols, int s, char sym)
{
	for (int i = Rows / 5; i <= 4 * Rows / 5; i++)
	{
		PrintLetterS(i, Cols / 2, 20, sym);
		PrintLetterS(i, Cols / 2, 20, ' ');
	}
	for (int i = Cols / 5; i <= 4 * Cols / 5; i++)
	{
		PrintLetterS(Rows / 2, i, 20, sym);
		PrintLetterS(Rows / 2, i, 20, ' ');
	}
	for (int i = Cols / 5; i <= 4 * Cols / 5; i++)
	{
		PrintLetterS(i, i, 20, sym);
		PrintLetterS(i, i, 20, ' ');
	}
	for (int i = Cols / 5; i <= 4 * Cols / 5; i++)
	{
		PrintLetterS(Rows - i, Cols - i, 20, sym);
		PrintLetterS(Rows - i, Cols - i, 20, ' ');
	}
}
void PrintCharacter(int cr, int cc, char Sym)
{
	gotoRowCol(cr, cc - 1);
	cout << "___";
	gotoRowCol(cr, cc + 2);
	cout << "=";
	gotoRowCol(cr, cc - 2);
	cout << "\\";
	gotoRowCol(cr - 1, cc - 3);
	cout << "\\";
	gotoRowCol(cr + 1, cc - 1);
	cout << "o";
	gotoRowCol(cr + 1, cc + 1);
	cout << "o";
	gotoRowCol(cr - 1, cc);
	cout << Sym;
}
void RemoveCharacter(int cr, int cc)
{

	gotoRowCol(cr, cc - 1);
	cout << "   ";
	gotoRowCol(cr, cc + 2);
	cout << " ";
	gotoRowCol(cr, cc - 2);
	cout << " ";
	gotoRowCol(cr - 1, cc - 3);
	cout << " ";
	gotoRowCol(cr + 1, cc - 1);
	cout << " ";
	gotoRowCol(cr + 1, cc + 1);
	cout << " ";
	gotoRowCol(cr - 1, cc);
	cout << " ";
}
void StoneAnimation(int Rows, int Cols, int A[5], char C[5])
{
	gotoRowCol(Rows / 3, 0);
	for (int i = 0; i < 5; i++) cout << C[i];
	for (int r = Rows / 3 + 1; r < Rows - 3; r++)
	{
		L2R(r, 0, Cols / 3, 0, -37);
	}
	for (int r = Rows - 3; r < Rows; r++)
	{
		L2R(r, 0, Cols, 0, -37);
	}
	for (int i = 4; i >= 0; i--)
	{
		int r = 0, c = 0;
		gotoRowCol(Rows / 3, i);
		for (int k = 1 + i; k < Cols / 3 - 2; k++)
		{
			PrintCharacter(Rows / 3 - 1, k, C[i]);
			wait(500);
			RemoveCharacter(Rows / 3 - 1, k);
		}
		PrintCharacter(Rows / 3 - 1, Cols / 3 - 2, C[i]);
		float t = 0;
		do
		{
			r = (Rows / 3) + ((9.8 / 2) * t * t);
			c = (Cols / 3 + 1) + (A[i] * t);
			if (r >= Rows - 4)
			{
				gotoRowCol(Rows - 4, c);
				cout << C[i];
			}
			else
			{
				gotoRowCol(r, c);
				cout << ".";
			}
			wait(8);
			t += 0.01; //adjust it my laptop is superfast!
		} while (r < Rows - 4);
		RemoveCharacter(Rows / 3 - 1, Cols / 3 - 2);

	}
	PrintCharacter(Rows / 3 - 1, Cols / 3 - 2, ' ');
}

int main()
{
	int Rows = 100, Cols = 100;
	char sym = '*';
	while (true)
	{
		for (int i = 1; i <= Rows / 2 - 5; i++)
		{
			PrintCircle(Rows / 2, Cols / 2, i, sym);
			wait(100);
			PrintCircle(Rows / 2, Cols / 2, i, ' ');
		}
		for (int i = Rows / 2 - 6; i >= 0; i--)
		{
			PrintCircle(Rows / 2, Cols / 2, i, sym);
			wait(100);
			PrintCircle(Rows / 2, Cols / 2, i, ' ');
		}
	}
}
int main1()
{
	int Rows = 100, Cols = 100;
	while (true)
	{
		for (int i = 1; i <= Rows / 4 - 3; i++)
		{
			PrintCircle(Rows / 4, Cols / 4, i, '*');
			PrintCircle(Rows / 4, Cols * 3 / 4, i, '*');
			PrintCircle(Rows * 3 / 4, Cols / 4, i, '*');
			PrintCircle(Rows * 3 / 4, Cols * 3 / 4, i, '*');
			wait(100);
			PrintCircle(Rows / 4, Cols / 4, i, ' ');
			PrintCircle(Rows / 4, Cols * 3 / 4, i, ' ');
			PrintCircle(Rows * 3 / 4, Cols / 4, i, ' ');
			PrintCircle(Rows * 3 / 4, Cols * 3 / 4, i, ' ');
		}
		for (int i = Rows / 4 - 3; i >= 0; i--)
		{
			PrintCircle(Rows / 4, Cols / 4, i, '*');
			PrintCircle(Rows / 4, Cols * 3 / 4, i, '*');
			PrintCircle(Rows * 3 / 4, Cols / 4, i, '*');
			PrintCircle(Rows * 3 / 4, Cols * 3 / 4, i, '*');
			wait(100);
			PrintCircle(Rows / 4, Cols / 4, i, ' ');
			PrintCircle(Rows / 4, Cols * 3 / 4, i, ' ');
			PrintCircle(Rows * 3 / 4, Cols / 4, i, ' ');
			PrintCircle(Rows * 3 / 4, Cols * 3 / 4, i, ' ');
		}
	}

}
int mainFace()
{
	int Rows = 100, Cols = 100;
	char sym = -37;
	int Radius = Rows / 2 - 10;
	PrintCircle(Rows / 2, Cols / 2, Radius, sym);
	PrintCircle(Rows / 2, Cols / 2, Radius * 3 / 4, sym, 200, 340);
	PrintCircle(Radius * 3 / 4 + 3, Radius * 3 / 4, Radius / 8 + 3, sym);
	PrintCircle(Radius * 3 / 4 + 3, Radius * 7 / 4, Radius / 8 + 3, sym);
	B2T(Cols / 2, Rows / 2 - 6, Rows / 2 + 6, 0, sym);
	gotoRowCol(Radius * 3 / 4 + 3, Radius * 3 / 4 + 1);
	cout << sym;
	gotoRowCol(Radius * 3 / 4 + 3, Radius * 7 / 4 + 1);
	cout << sym;
	return _getch();

}
int mainDonut()
{
	int Rows = 100, Cols = 100;
	char sym = -37;
	int X = 8;
	PrintDonut(Rows / 2, Cols / 2, Cols / 3, sym, X);
	return _getch();
}
int mainSpiral()
{
	int Rows = 100, Cols = 100;
	char sym = '*';
	PrintSpiral(Rows / 2, Cols / 2 - 2, Rows / 2, 8, sym);
	return _getch();
}
int main3()
{
	int Rows = 100, Cols = 100;
	char sym = '*';
	PrintFan(Rows / 2, Cols / 2, 20, sym);
	return _getch();
}
int mainsine()
{
	int Rows = 100, Cols = 100, si = 0;
	char sym = '*';
	PrintSinWave(Rows / 2, si, Cols, 20, 3, sym);
	return _getch();
}
int mainsnake()
{
	int Rows = 100, Cols = 100;
	char sym = '*';
	PrintSnake(Rows / 2, Cols, 20, 1, sym);
	return _getch();
}
int main22()
{
	int Rows = 100, Cols = 100;
	PrintLetterA(Rows / 2, Cols / 2, 20, '*');
	wait(3000);
	PrintLetterA(Rows / 2, Cols / 2, 20, ' ');
	PrintLetterN(Rows / 2, Cols / 2, 20, '*');
	wait(3000);
	PrintLetterN(Rows / 2, Cols / 2, 20, ' ');
	PrintLetterA(Rows / 2, Cols / 2, 20, '*');
	wait(3000);
	PrintLetterA(Rows / 2, Cols / 2, 20, ' ');
	PrintLetterS(Rows / 2, Cols / 2, 20, '*');
	wait(3000);
	PrintLetterS(Rows / 2, Cols / 2, 20, ' ');
	LetterAnimationA(Rows, Cols, 20, '*');
	LetterAnimationN(Rows, Cols, 20, '*');
	LetterAnimationS(Rows, Cols, 20, '*');
	return _getch();

}
int main2()
{
	int Rows = 100, Cols = 100, A[5], Num;
	char C[5], Char;
	cout << "Insert five Characters and their forces (C1,F1,C2,F2,...) : ";
	for (int i = 0; i < 5; i++)
	{
		cin >> Char;
		C[i] = Char;
		cin >> Num;
		A[i] = Num;
	}
	StoneAnimation(Rows, Cols, A, C);
	return _getch();
}