#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
//#include <windows.h>
#include <cstdio>
//#include <conio.h>
#include <fstream>

using namespace std;

void update(vector<vector<bool> > &map) //计算下一次的map
{
    vector<vector<bool> > map_copy = map;
    for (int x = 0; x < map.size(); x++) {
        for (int y = 0; y < map[x].size(); y++) {
            int ans_life = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) {}
                    else {
                        if(x + i >= 0 && x + i < map.size() && y + i >= 0 && y + i < map[x].size() && map[x + i][y + j] == 1) ans_life++;
                    }
                }
            }
            if (ans_life == 3) map_copy[x][y] = true;
            else if (ans_life == 2) map_copy[x][y] = map[x][y];
            else map_copy[x][y] = false;
        }
    }
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            map[i][j] = map_copy[i][j];
        }
    }
    return;
}

/*
void HideCursor() { //隐藏鼠标
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
}
*/

int main() {
    int n = 40, m = 40;
    //HideCursor();
    srand(time(0));
    vector<vector<bool> > map;

    printf("请选择游戏模式：\n1.随机初始图像\n2.指定初始图像\n请输入：");
    while (true) {
        int mode;
        cin >> mode;
        printf("\n");
        if (mode == 1) { //随机初始图像
            printf("请输入图像长宽：\n长：");
            cin >> n;
            printf("\n");
            printf("宽：");
            cin >> m;
            printf("\n");
            map = vector<vector<bool> >(n, vector<bool>(m, false));

            //随机初始化map数组
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    map[i][j] = rand() & 1;
                    //1代表活
                    //0代表死亡
                }
            }
            break;
        } else if (mode == 2) { //指定初始图像
            printf("请选择初始图案类型：\n1.枪\n2.振荡器1\n3.滑翔机\n4.振荡器2\n5.振荡器3\n请输入初始图案类型：");
            ifstream sin;
            while (true) {
                int mapMode;
                cin >> mapMode;
                printf("\n");
                if (mapMode == 1) {
                    sin.open("map/map1.txt");
                    break;
                } else if (mapMode == 2) {
                    sin.open("map/map2.txt");
                    break;
                } else if (mapMode == 3) {
                    sin.open("map/map3.txt");
                } else if (mapMode == 4) {
                    sin.open("map/map4.txt");
                    break;
                } else if (mapMode == 5) {
                    sin.open("map/map5.txt");
                    break;
                } else printf("您输入的图案我们暂时没有！请重新输入：");
            }
            string str[105];
            string line;
            while (getline(sin, line)) {
                vector<bool> tmp;
                for (int i = 0; i < line.size(); ++i) {
                    tmp.push_back(line[i] - '0');
                }
                map.push_back(tmp);
            }
            break;
        } else printf("输入有误，请重新输入：");
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
    while (true) {
        system("cls");
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (map[i][j] == 0) printf(" ");
                else printf("*");
            }
            printf("\n");
        }
        update(map);
        if (kbhit()) {
            input = getch();
            if (input == 'w') stopTime += 100;
            else if (input == 's' && stopTime >= 100) stopTime -= 100;
        }
        Sleep(stopTime);
        if (tot > 100) break;
        tot++;
    }
    return 0;
}
