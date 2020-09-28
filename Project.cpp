// ConsoleApplication1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include<vector>
using namespace std;
#include<time.h>
#include <math.h>
#include<cmath>
class car {
public:
	int x;
	int y;
	int direction;
	int server[4];
	double power[4];
};
int max(double a, double b, double c, double d)
{
	if (a >= b&&a >= c&&a >= d) { return(0); }
	else if (b >= a&&b >= c&&b >= d) { return(1); }
	else if (c >= a&&c >= b&&c >= d) { return(2); }
	else if (d >= a&&d >= b&&d >= c) { return(3); }
}

int position(int x, int y)
{
	if (x == 1500) { if (y == 1500) { return(4); } else if (y == 750) { return(9); } else if (y == 0) { return(14); } else if (y == -750) { return(19); } else if (y == -1500) { return(24); } }
	else if (x == 750) { if (y == 1500) { return(3); } else if (y == 750) { return(8); } else if (y == 0) { return(13); } else if (y == -750) { return(18); } else if (y == -1500) { return(23); } }
	else if (x == 0) { if (y == 1500) { return(2); } else if (y == 750) { return(7); } else if (y == 0) { return(12); } else if (y == -750) { return(17); } else if (y == -1500) { return(22); } }
	else if (x == -750){ if (y == 1500) { return(1); } else if (y == 750) { return(6); } else if (y == 0) { return(11); } else if (y == -750) { return(16); } else if (y == -1500) { return(21); } }
	else if (x == -1500) { if (y == 1500) { return(0); } else if (y == 750) { return(5); } else if (y == 0) { return(10); } else if (y == -750) { return(15); } else if (y == -1500) { return(20); } }
	return(25);
}


int main()
{
	int times = 0;
	int i = 0;
	int change[4] = {0,0,0,0};
	int randtemp;
	int n = 0;
	double tempd[4] = {0,0,0,0};
	double tempend[4] = { 0,0,0,0 };
	car temp;
	vector<car> Car;
	vector<car>::iterator ptr;
	srand((unsigned)time(NULL));
	FILE *f;
	f= fopen("Data.txt", "w");


	for(times=0;times<86400;++times)
	{
		n = Car.size();
		for (ptr = Car.begin();ptr != Car.end();)
		{
			if(ptr->direction==0)
            {
				ptr->y += 10;
				if (sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y - 750) * (ptr->y - 750)) <= 1) { ptr->power[0] = -50; }
				else { ptr->power[0] = -50 - 20 * log10(sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y - 750) * (ptr->y - 750))); }
				if (sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y - 750) * (ptr->y - 750)) <= 1) { ptr->power[1] = -50; }
				else { ptr->power[1] = -50 - 20 * log10(sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y - 750) * (ptr->y - 750))); }
				if (sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y + 750) * (ptr->y + 750)) <= 1) { ptr->power[2] = -50; }
				else { ptr->power[2] = -50 - 20 * log10(sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y + 750) * (ptr->y + 750))); }
				if (sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y + 750) * (ptr->y + 750)) <= 1) { ptr->power[3] = -50; }
				else { ptr->power[3] = -50 - 20 * log10(sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y + 750) * (ptr->y + 750))); }
				
				if (ptr->server[0] == 4) { ptr->server[0] = ptr->server[1] = ptr->server[2] = ptr->server[3] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]); }

				if (ptr->server[0] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3])) { ptr->server[0] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[0] += 1; }

				if (ptr->server[1] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]) && ptr->power[ptr->server[1]] < -110)
				{
					ptr->server[1] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[1] += 1;
				}

				if (ptr->server[2] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3])&&ptr->power[ptr->server[2]]+5<ptr->power[max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3])])
				{ ptr->server[2] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[2] += 1; }

				if (ptr->server[3] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3])&&times%30==0) {ptr->server[3]= max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[3] += 1;}

				tempd[0] += ptr->power[ptr->server[0]];
				tempd[1] += ptr->power[ptr->server[1]];
				tempd[2] += ptr->power[ptr->server[2]];
				tempd[3] += ptr->power[ptr->server[3]];


				switch (position(ptr->x, ptr->y))
				{
				case 0:ptr->direction = 3;++ptr;break;
				case 4:ptr->direction = 2;++ptr;break;
				case 1:
				case 2:
				case 3:randtemp = rand() % 6;if (randtemp == 0 || randtemp == 1 || randtemp == 2) { ptr = Car.erase(ptr); }
					   else if (randtemp == 3 || randtemp == 4) { ptr->direction = 3;++ptr;}
					   else if (randtemp == 5) { ptr->direction = 2;++ptr;} break;
				case 5:
				case 10:
				case 15:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr->direction = 3;++ptr;}
						else if (randtemp == 5) { ptr = Car.erase(ptr); } break;
				case 9:
				case 14:
				case 19:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr = Car.erase(ptr); }
						else if (randtemp == 5) { ptr->direction = 2; ++ptr;} break;
				case 6:
				case 7:
				case 8:
				case 11:
				case 12:
				case 13:
				case 16:
				case 17:
				case 18:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr->direction = 3;++ptr;}
						else if (randtemp == 5) { ptr->direction = 2;++ptr;} break;
				case 25:++ptr;break;
				}
			}
			else if(ptr->direction==1)
			{
				ptr->y -= 10;
				if (sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y - 750) * (ptr->y - 750)) <= 1) { ptr->power[0] = -50; }
				else { ptr->power[0] = -50 - 20 * log10(sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y - 750) * (ptr->y - 750))); }
				if (sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y - 750) * (ptr->y - 750)) <= 1) { ptr->power[1] = -50; }
				else { ptr->power[1] = -50 - 20 * log10(sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y - 750) * (ptr->y - 750))); }
				if (sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y + 750) * (ptr->y + 750)) <= 1) { ptr->power[2] = -50; }
				else { ptr->power[2] = -50 - 20 * log10(sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y + 750) * (ptr->y + 750))); }
				if (sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y + 750) * (ptr->y + 750)) <= 1) { ptr->power[3] = -50; }
				else { ptr->power[3] = -50 - 20 * log10(sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y + 750) * (ptr->y + 750))); }

				if (ptr->server[0] == 4) { ptr->server[0] = ptr->server[1] = ptr->server[2] = ptr->server[3] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]); }

				if (ptr->server[0] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3])) { ptr->server[0] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[0] += 1; }

				if (ptr->server[1] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]) && ptr->power[ptr->server[1]] < -110)
				{
					ptr->server[1] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[1] += 1;
				}

				if (ptr->server[2] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]) && ptr->power[ptr->server[2]] + 5 < ptr->power[max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3])])
				{
					ptr->server[2] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[2] += 1;
				}

				if (ptr->server[3] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]) && times % 30 == 0) { ptr->server[3] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[3] += 1; }

				tempd[0] += ptr->power[ptr->server[0]];
				tempd[1] += ptr->power[ptr->server[1]];
				tempd[2] += ptr->power[ptr->server[2]];
				tempd[3] += ptr->power[ptr->server[3]];

				switch (position(ptr->x, ptr->y))
				{
				case 20:ptr->direction = 3;++ptr;break;
				case 24:ptr->direction = 2;++ptr;break;
				case 21:
				case 22:
				case 23:randtemp = rand() % 6;if (randtemp == 0 || randtemp == 1 || randtemp == 2) { ptr = Car.erase(ptr); }
						else if (randtemp == 3 || randtemp == 4) { ptr->direction = 2;++ptr;}
						else if (randtemp == 5) { ptr->direction = 3;++ptr;} break;
				case 5:
				case 10:
				case 15:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr = Car.erase(ptr);}
						else if (randtemp == 5) { ptr->direction = 3;++ptr;} break;
				case 9:
				case 14:
				case 19:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr->direction = 2;++ptr;}
						else if (randtemp == 5) { ptr = Car.erase(ptr); } break;
				case 6:
				case 7:
				case 8:
				case 11:
				case 12:
				case 13:
				case 16:
				case 17:
				case 18:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr->direction = 2; ++ptr;}
						else if (randtemp == 5) { ptr->direction = 3;++ptr;} break;
				case 25:++ptr;break;
				}
			}
			else if(ptr->direction==2)
			{
				ptr->x -= 10;
				if (sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y - 750) * (ptr->y - 750)) <= 1) { ptr->power[0] = -50; }
				else { ptr->power[0] = -50 - 20 * log10(sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y - 750) * (ptr->y - 750))); }
				if (sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y - 750) * (ptr->y - 750)) <= 1) { ptr->power[1] = -50; }
				else { ptr->power[1] = -50 - 20 * log10(sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y - 750) * (ptr->y - 750))); }
				if (sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y + 750) * (ptr->y + 750)) <= 1) { ptr->power[2] = -50; }
				else { ptr->power[2] = -50 - 20 * log10(sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y + 750) * (ptr->y + 750))); }
				if (sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y + 750) * (ptr->y + 750)) <= 1) { ptr->power[3] = -50; }
				else { ptr->power[3] = -50 - 20 * log10(sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y + 750) * (ptr->y + 750))); }
				
				if (ptr->server[0] == 4) { ptr->server[0] = ptr->server[1] = ptr->server[2] = ptr->server[3] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]); }

				if (ptr->server[0] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3])) { ptr->server[0] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[0] += 1; }

				if (ptr->server[1] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]) && ptr->power[ptr->server[1]] < -110)
				{
					ptr->server[1] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[1] += 1;
				}

				if (ptr->server[2] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]) && ptr->power[ptr->server[2]] + 5 < ptr->power[max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3])])
				{
					ptr->server[2] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[2] += 1;
				}

				if (ptr->server[3] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]) && times % 30 == 0) { ptr->server[3] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[3] += 1; }

				tempd[0] += ptr->power[ptr->server[0]];
				tempd[1] += ptr->power[ptr->server[1]];
				tempd[2] += ptr->power[ptr->server[2]];
				tempd[3] += ptr->power[ptr->server[3]];

				switch (position(ptr->x, ptr->y))
				{
				case 0:ptr->direction = 1;++ptr;break;
				case 20:ptr->direction = 0;++ptr;break;
				case 5:
				case 10:
				case 15:randtemp = rand() % 6;if (randtemp == 0 || randtemp == 1 || randtemp == 2) { ptr = Car.erase(ptr); }
						else if (randtemp == 3 || randtemp == 4) { ptr->direction = 0; ++ptr;}
						else if (randtemp == 5) { ptr->direction = 1;++ptr;} break;
				case 1:
				case 2:
				case 3:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr = Car.erase(ptr);}
					   else if (randtemp == 5) { ptr->direction = 1;++ptr;} break;
				case 21:
				case 22:
				case 23:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr->direction = 0; ++ptr;}
						else if (randtemp == 5) { ptr = Car.erase(ptr);} break;
				case 6:
				case 7:
				case 8:
				case 11:
				case 12:
				case 13:
				case 16:
				case 17:
				case 18:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr->direction = 0;++ptr;}
						else if (randtemp == 5) { ptr->direction = 1; ++ptr;} break;
				case 25:++ptr;break;
				}

			}
			else if(ptr->direction==3)
            {
				ptr->x += 10;
				if (sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y - 750) * (ptr->y - 750)) <= 1) { ptr->power[0] = -50; }
				else { ptr->power[0] = -50 - 20 * log10(sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y - 750) * (ptr->y - 750))); }
				if (sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y - 750) * (ptr->y - 750)) <= 1) { ptr->power[1] = -50; }
				else { ptr->power[1] = -50 - 20 * log10(sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y - 750) * (ptr->y - 750))); }
				if (sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y + 750) * (ptr->y + 750)) <= 1) { ptr->power[2] = -50; }
				else { ptr->power[2] = -50 - 20 * log10(sqrt((ptr->x + 750)* (ptr->x + 750) + (ptr->y + 750) * (ptr->y + 750))); }
				if (sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y + 750) * (ptr->y + 750)) <= 1) { ptr->power[3] = -50; }
				else { ptr->power[3] = -50 - 20 * log10(sqrt((ptr->x - 750)* (ptr->x - 750) + (ptr->y + 750) * (ptr->y + 750))); }

				if (ptr->server[0] == 4) { ptr->server[0] = ptr->server[1] = ptr->server[2] = ptr->server[3] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]); }

				if (ptr->server[0] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3])) { ptr->server[0] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[0] += 1; }

				if (ptr->server[1] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]) && ptr->power[ptr->server[1]] < -110)
				{
					ptr->server[1] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[1] += 1;
				}

				if (ptr->server[2] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]) && ptr->power[ptr->server[2]] + 5 < ptr->power[max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3])])
				{
					ptr->server[2] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[2] += 1;
				}

				if (ptr->server[3] != max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]) && times % 30 == 0) { ptr->server[3] = max(ptr->power[0], ptr->power[1], ptr->power[2], ptr->power[3]);change[3] += 1; }

				tempd[0] += ptr->power[ptr->server[0]];
				tempd[1] += ptr->power[ptr->server[1]];
				tempd[2] += ptr->power[ptr->server[2]];
				tempd[3] += ptr->power[ptr->server[3]];

				switch (position(ptr->x, ptr->y))
				{
				case 4:ptr->direction = 1;++ptr;break;
				case 24:ptr->direction = 0;++ptr;break;
				case 9:
				case 14:
				case 19:randtemp = rand() % 6;if (randtemp == 0 || randtemp == 1 || randtemp == 2) { ptr = Car.erase(ptr); }
						else if (randtemp == 3 || randtemp == 4) { ptr->direction = 1; ++ptr;}
						else if (randtemp == 5) { ptr->direction = 0;++ptr;} break;
				case 1:
				case 2:
				case 3:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr->direction = 1;++ptr;}
					   else if (randtemp == 5) { ptr = Car.erase(ptr); } break;
				case 21:
				case 22:
				case 23:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr = Car.erase(ptr); }
						else if (randtemp == 5) { ptr->direction = 0; ++ptr;} break;
				case 6:
				case 7:
				case 8:
				case 11:
				case 12:
				case 13:
				case 16:
				case 17:
				case 18:randtemp = rand() % 6;if (randtemp == 3 || randtemp == 4) { ptr->direction = 1;++ptr;}
						else if (randtemp == 5) { ptr->direction = 0; ++ptr;} break;
				case 25:++ptr;break;
				}
			}
        }
		if (n != 0) { tempend[0] += tempd[0] / n;tempend[1] += tempd[1] / n;tempend[2] += tempd[2] / n;tempend[3] += tempd[3] / n; }
		n = 0;tempd[0] = 0;tempd[1] = 0;tempd[2] = 0;tempd[3] = 0;

		for (i = 0;i < 12;++i) 
			{
				switch (i)
				{
				case 0:if (rand() % 100 < 3) 
				{
					temp.x = -750;
					temp.y = 1500;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 1; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 2; }
					else if (randtemp == 5) { temp.direction = 3; }
					Car.push_back(temp);
				}break;
				case 1:if (rand() % 100 < 3) {
					temp.x = 0;
					temp.y = 1500;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 1; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 2; }
					else if (randtemp == 5) { temp.direction = 3; }
					Car.push_back(temp);
				}break;
				case 2:if (rand() % 100 < 3) {
					temp.x = 750;
					temp.y = 1500;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 1; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 2; }
					else if (randtemp == 5) { temp.direction = 3; }
					Car.push_back(temp);
				}break;
				case 3:if (rand() % 100 < 3) {
					temp.x = 1500;
					temp.y = 750;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 2; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 0; }
					else if (randtemp == 5) { temp.direction = 1; }
					Car.push_back(temp);
				}break;
				case 4:if (rand() % 100 < 3) {
					temp.x = 1500;
					temp.y = 0;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 2; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 0; }
					else if (randtemp == 5) { temp.direction = 1; }
					Car.push_back(temp);
				}break;
				case 5:if (rand() % 100 < 3) {
					temp.x = 1500;
					temp.y = -750;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 2; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 0; }
					else if (randtemp == 5) { temp.direction = 1; }
					Car.push_back(temp);
				}break;
				case 6:if (rand() % 100 < 3) {
					temp.x = 750;
					temp.y = -1500;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 0; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 3; }
					else if (randtemp == 5) { temp.direction = 2; }
					Car.push_back(temp);
				}break;
				case 7:if (rand() % 100 < 3) {
					temp.x = 0;
					temp.y = -1500;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 0; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 3; }
					else if (randtemp == 5) { temp.direction = 2; }
					Car.push_back(temp);
				}break;
				case 8:if (rand() % 100 < 3) {
					temp.x = -750;
					temp.y = -1500;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 0; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 3; }
					else if (randtemp == 5) { temp.direction = 2; }
					Car.push_back(temp);
				}break;
				case 9:if (rand() % 100 < 3) {
					temp.x = -1500;
					temp.y = -750;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 3; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 1; }
					else if (randtemp == 5) { temp.direction = 0; }
					Car.push_back(temp);
				}break;
				case 10:if (rand() % 100 < 3) {
					temp.x = -1500;
					temp.y = 0;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 3; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 1; }
					else if (randtemp == 5) { temp.direction = 0; }
					Car.push_back(temp);
				}break;
				case 11:if (rand() % 100 < 3) {
					temp.x = -1500;
					temp.y = 750;
					temp.server[0] = 4;
					temp.server[1] = 4;
					temp.server[2] = 4;
					temp.server[3] = 4;
					randtemp = rand() % 6;
					if (randtemp == 0 || randtemp == 1 || randtemp == 2) { temp.direction = 3; }
					else if (randtemp == 3 || randtemp == 4) { temp.direction = 1; }
					else if (randtemp == 5) { temp.direction = 0; }
					Car.push_back(temp);
				}break;
				}
		}
		fprintf(f,"%d	%d	%d	%d	%d\n", times,change[0], change[1], change[2], change[3]);
	}
	tempend[0] /= 86400;tempend[1] /= 86400;tempend[2] /= 86400;tempend[3] /= 86400;
	printf("Average Power :\nBest : %f\nThreshold : %f\nEntropy : %f\nMy Policy : %f", tempend[0], tempend[1], tempend[2], tempend[3]);
}

