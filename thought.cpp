#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <cstdio>
#include <conio.h>
using namespace std;

void update(vector<vector<bool> > &map, int n, int m) //计算下一次的map
{
	vector<vector<bool> > map_copy = map;
	for(int x = 1; x <= n; x++) {
		for(int y = 1; y <= m; y++) {
			int ans_life = 0;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (i == 0 && j == 0) {}
					else {
						if (map[x + i][y + j] == 1) ans_life++;
					}
				}
			}
			if(ans_life == 3) map_copy[x][y] = true;
			else if(ans_life == 2) map_copy[x][y] = map[x][y];
			else if(ans_life > 3) map_copy[x][y] = false;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			map[i][j] = map_copy[i][j];
		}
	}
	return ;
}

void HideCursor(){ //隐藏鼠标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}

int main() {
	HideCursor();
	srand(time(0));
	int n = 40, m = 40;
	//scanf("%d %d", &n, &m);
	vector<vector<bool> > map(n + 2, vector<bool > (m + 2, false));
	//    bool map[n + 1][m + 1];

	//随机初始化map数组
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			map[i][j] = rand() & 1;
			//1代表活
			//0代表死亡
		}
	}
	//测试输入
	/*
	   for(int i = 1; i <= n; i++) {
	   for(int j = 1; j <= m; j++) {
	   cout << map[i][j];
	   }
	   cout << endl;
	   }
	   */

	char input;
	long stopTime = 100;
	int tot = 0; //记录次数的
	while(true)
	{
		system("cls");
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if(map[i][j] == 0) printf(" ");
				else printf("*");
			}
			printf("\n");
		}
		update(map, n, m);
		if(kbhit()) {
			input = getch();
			if(input == 'w') stopTime += 100;
			else if(input == 's' && stopTime >= 100) stopTime -= 100;
		}
		Sleep(stopTime);
		if(tot > 100) break;
		tot++;
	}
	return 0;
}
