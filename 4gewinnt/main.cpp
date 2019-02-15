#include <iostream>
#include <conio.h>
#include "ic.hpp"

using namespace ic;
using namespace ic::shorties;
using namespace std;

/////Umlaute/////
const unsigned char AE = static_cast<unsigned char>(142);
const unsigned char ae = static_cast<unsigned char>(132);
const unsigned char OE = static_cast<unsigned char>(153);
const unsigned char oe = static_cast<unsigned char>(148);
const unsigned char UE = static_cast<unsigned char>(154);
const unsigned char ue = static_cast<unsigned char>(129);
const unsigned char ss = static_cast<unsigned char>(225);

/////Funktionen/////
///Spiel///
bool checkColumn ( char column, bool onlyCheck = false );
char checkWin ();
void wait();
int random(int lowerbounds, int upperbounds);
///Zeichnen///
void chooseComputer();
void drawGamefield ();
void drawCursor ();
void drawTokens ();
void clearTokens ();
void clearCursor ();
void clearText1 ();
void clearText2 ();

/////Variablen/////
char matrix[7][6] = {0};
char totalMoves = 0;
bool secondPlayer = false;
bool gameEnd = false;
char input = 0;
char computer = 0;
char negativPoints[7] = {0};

int main ()
{
	char nextGame;
	char win;
	bool columnFull = false;
	bool computerFinish = false;
	char tmp;
	// Blinkcursor verstecken
	cursize(-1);

	title(TEXT("Vier Gewinnt"));
	clrscr(BG_DARKGREEN);
	drawGamefield();
	chooseComputer();
	drawCursor();
	while ( !gameEnd )
	{
		win = checkWin();
		if ( win == 0 )
		{
			if(secondPlayer == true && computer > 0)
			{
				for(char x = 0; x <= 6; x++) negativPoints[x] = 0;
				computerFinish = false;
				switch(computer)
				{
				case 1:
					{
						while(computerFinish == false)
						{
							if (checkColumn(random(0,6)))
							{
								drawTokens();
								clearCursor();
								drawCursor();
								computerFinish = true;
							}
						}
					}
					break;
				case 2:
					{
						while(computerFinish == false)
						{

					}
					break;
				case 3:
					{
						//...
					}
					break;
				}
			}
			else
			{
				int c = _getch();
				switch(c)
				{
					case 'A': case 'a': // Nach Links
						{
							if ( input > 0 ) --input;
							clearCursor();
							drawCursor();
						}
						break;
					case 'D': case 'd': // Nach Rechts
						{
							if ( input < 6 ) ++input;
							clearCursor();
							drawCursor();
						}
						break;
					case 'S': case 's': // Spielstein Runter
						{
							if (checkColumn(input))
							{
								drawTokens();
								clearCursor();
								drawCursor();
							}
						}
						break;
					case 27: // Ende
						{
								gameEnd = true;
						}
						break;
					case 0: case 224:
						{
							int c = _getch();
							switch(c)
							{
								case 75:
									{
										if ( input > 0 ) --input;
										clearCursor();
										drawCursor();
									}
									break;
								case 77:
									{
										if ( input < 6 ) ++input;
										clearCursor();
										drawCursor();
									}
									break;
								case 80:
									{
										if (checkColumn(input))
										{
											drawTokens();
											clearCursor();
											drawCursor();
										}
									}
									break;
							}
						}
				}
			}
		}
		else
		{
			textcolor(FG_WHITE);
			gotoxy(49,7);
			if ( win == 1)
				if ( secondPlayer )
					cout << "Spieler 1 hat gewonnen!!! ";
				else
					cout << "Spieler 2 hat gewonnen!!!";
			else
				cout << "Niemand hat gewonnen...";
			gotoxy(49,9);
			cout << "Noch ein Spiel?";
			gotoxy(49,10);
			cout << "<J>a <N>ein";
			nextGame = _getch();
			switch (nextGame)
			{
			case 'J': case 'j':
				{
					for ( char y = 0; y <= 5; y++)
						for ( char x = 0; x <= 6; x++)
							matrix[x][y] = 0;
					secondPlayer = false;
					totalMoves = 0;
					clearTokens();
					clearText1();
					drawCursor();
				}
				break;
			case 'N': case 'n': case 27:
				{
					gameEnd = true;
				}
			}
		}
	}
	return 0;
}


bool checkColumn ( char column, bool onlyCheck )
{
	if(onlyCheck)
	{
		if ( matrix[column][0] == 0 )
			return true;
	}
	else
	{
		for ( char i = 0; i <= 5; i++)
		{
			if ( matrix[column][i] == 0 )
			{
				if ( !secondPlayer )
					matrix[column][i] = 1;
				else
					matrix[column][i] = 2;
				++totalMoves;
				if ( secondPlayer )
					secondPlayer = false;
				else
					secondPlayer = true;
				return true;
			}
		}
	}
	return false;
}

char checkWin ()
{
	char mem = 0;
	for ( char y = 0; y <= 2; y++) //check vertical
	{
		for ( char x = 0; x <= 6; x++)
		{
			mem = matrix[x][y];
			if ( mem != 0 )
				if ((matrix[x][y+1] == mem) && (matrix[x][y+2] == mem) && (matrix[x][y+3] == mem))
					return 1;
		}
	}
	for ( char y = 0; y <= 5; y++) //check horizontal
	{
		for ( char x = 0; x <= 3; x++)
		{
			mem = matrix[x][y];
			if ( mem != 0 )
				if ((matrix[x+1][y] == mem) && (matrix[x+2][y] == mem) && (matrix[x+3][y] == mem))
					return 1;
		}
	}
	for ( char y = 0; y <= 2; y++) //check diagonal left down to right up
	{
		for ( char x = 0; x <= 3; x++)
		{
			mem = matrix[x][y];
			if ( mem != 0 )
				if (( matrix[x+1][y+1] == mem) && (matrix[x+2][y+2] == mem) && (matrix[x+3][y+3] == mem))
					return 1;
		}
	}
	for ( char y = 5; y >= 3; y--) //check diagonal left up to right down
	{
		for ( char x = 0; x <= 3; x++)
		{
			mem = matrix[x][y];
			if ( mem != 0 )
				if (( matrix[x+1][y-1] == mem) && (matrix[x+2][y-2] == mem) && (matrix[x+3][y-3] == mem))
					return 1;
		}
	}
	if ( totalMoves == 42 )
		return 2;
	return 0;
}

void wait ()
{
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
}

int random(int lowerbounds, int upperbounds)
{
   return lowerbounds + std::rand() % (upperbounds - lowerbounds + 1);
}

void chooseComputer()
{
	textcolor(FG_WHITE);
	gotoxy(49,7);
	cout << "<0> 2 Spieler Modus";
	gotoxy(49,8);
	cout << "<1> Computer (Dumm)";
	gotoxy(49,9);
	cout << "<2> Computer (Normal)";
	gotoxy(49,10);
	cout << "<3> Computer (Extrem)";
	gotoxy(49,11);
	cout << "<Esc> Spiel Beenden";
	char computerPower = _getch();
	switch (computerPower)
	{
	case '1':
		computer = 1;
		break;
	case '2':
		computer = 2;
		break;
	case '3':
		computer = 3;
		break;
	case 27:
		gameEnd = true;
		break;
	case '0': default:
		computer = 0;
	}
	clearText1();
}

void drawGamefield ()
{
	//Hintergrund		
	bgcolor(BG_DARKGREEN);
	textcolor(FG_GREEN);		
	gotoxy(0,0); for(char i=0;i<80;i++) cout << "\xb1";
	gotoxy(0,1); cout << "\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1       "; textcolor(FG_WHITE); cout << "Vier Gewinnt"; textcolor(FG_GREEN); cout << "        \xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1    "; textcolor(FG_WHITE); cout << "V 1.05 "; textcolor(FG_RED); cout << "Beta"; textcolor(FG_GREEN); cout << "   \xb1\xb1\n";
	gotoxy(0,2); for(char i=0;i<80;i++) cout << "\xb1";
	for(char i=0;i<22;i++)
	{
		gotoxy(0,i+3);
		cout << "\xb1\xb1";
	}
	for(char i=0;i<22;i++)
	{
		gotoxy(46,i+3);
		for(char i=46;i<80;i++) cout << "\xb1";
	}
	gotoxy(0,23); for(char i=0;i<80;i++) cout << "\xb1";
	gotoxy(0,24); for(char i=0;i<80;i++) cout << "\xb1";
	clearText1 ();
	textcolor(FG_WHITE);
	gotoxy(57,24);
	cout << "\xb8 2008 Oliver K"<<ae<<"dtler";
	gotoxy(48,14);
	cout << " <A>links <S>runter <D>rechts ";
	// Ständer zeichnen
	textcolor(FG_BLUE);
	for(char y=7;y<=17;y+=2)
	{
		gotoxy(9,y);
		for(char i=0;i<30;i++) cout << "\xdb";
	}
	for(char x=9;x<=40;x+=4)
	{
		for(char y=8;y<=18;y+=2)
		{
			gotoxy(x,y);
			cout << "\xdb\xdb";
		}
	}
	gotoxy(7,19);
	for(char i=0;i<34;i++) cout << "\xdb";
}

void drawCursor ()
{
	if ( !secondPlayer ) textcolor(FG_RED); else textcolor(FG_YELLOW);
	gotoxy(input*4+11,5);
	cout << "\xdb\xdb";
	gotoxy(input*4+11,6);
	cout << "\x19\x19";
}

void drawTokens ()
{
	for(char x=11,xx=0;x<=36;x+=4,++xx)
	{
		for(char y=8,yy=5;y<=18;y+=2,--yy)
		{
			gotoxy(x,y);
			if(matrix[xx][yy] == 1)
			{
				textcolor(FG_RED);
				cout << "\xdb\xdb";
				textcolor(FG_BLUE);
			}
			else if(matrix[xx][yy] == 2)
			{
				textcolor(FG_YELLOW);
				cout << "\xdb\xdb";
				textcolor(FG_BLUE);
			}
		}
	}
}

void clearTokens ()
{
	for(char x=11;x<=36;x+=4)
	{
		for(char y=8;y<=18;y+=2)
		{
			gotoxy(x,y);
			cout << "  ";
		}
	}
}

void clearCursor ()
{
	gotoxy(9,5);
	cout << "                            ";
	gotoxy(9,6);
	cout << "                            ";
}

void clearText1 ()
{
	for(char i=0;i<5;i++)
	{
		gotoxy(48,i+7);
		for(char i=48;i<78;i++) cout << " ";
	}
}

void clearText2 ()
{
	//...
}