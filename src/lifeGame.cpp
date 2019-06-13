//
// Created by dreamstart on 2019-06-13.
//
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include <fstream>
using namespace std;

void updateMap(vector<vector<bool> > &map) //计算下一次的map
{
    vector<vector<bool> > map_copy = map;
    int height, width;
    height = map.size();
    for (int x = 0; x < height; x++) {
        width = map[x].size();
        for (int y = 0; y < width; y++) {
            int ans_life = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) {
                        continue;
                    } else if (x + i >= 0 && x + i < height && y + j >= 0 && y + j < width && map[x + i][y + j] == 1) {
                        ans_life++;
                    }
                }
            }
            if (ans_life == 3) map_copy[x][y] = true;
            else if (ans_life == 2) map_copy[x][y] = map[x][y];
            else map_copy[x][y] = false;
        }
    }
    for (int i = 0; i < height; i++) {
        width = map[i].size();
        for (int j = 0; j < width; j++) {
            map[i][j] = map_copy[i][j];
        }
    }
}

void outputMap(vector<vector<bool> > &map) //输出图像
{
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 0) printf(" ");
            else printf("*");
        }
        printf("\n");
    }
}

void hideCursor() { //隐藏鼠标
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
}

long monitorKeyboard(long Time) //监控键盘
{
    if (kbhit()) { //监控键盘
        char input;
        input = getch();
        if (input == 'w') Time += 100;
        else if (input == 's' && Time >= 100) Time -= 100;
        else if (input == 'q' || input == 'Q') return 233;
    }
    return Time;
}

void loadSpecifiedModeMap(int MODE, vector<vector<bool> > &map) {
    MODE--;
    string a[10];
    a[0] = "map/map1.txt";
    a[1] = "map/map2.txt";
    a[2] = "map/map3.txt";
    a[3] = "map/map4.txt";
    a[4] = "map/map5.txt";
    ifstream sin(a[MODE].data());
    string line;
    while (getline(sin, line)) {
        vector<bool> arr;
        for (int i = 0; i < line.size(); ++i) {
            arr.push_back(line[i] - '0');
        }
        map.push_back(arr);
    }
}

void runGame(vector<vector<bool> > &map) {
    long stopTime = 100;
    while (true) {
        system("cls");
        printf("按q结束此次游戏\n");
        outputMap(map); //输出图形
        updateMap(map);
        stopTime = monitorKeyboard(stopTime);
        if (stopTime == 233) {
            system("cls");
            break;
        }
        Sleep(stopTime);
    }
}

void initSpecifiedModeMap(vector<vector<bool> > &map) {
    printf("请选择初始图案类型：\n1.枪\n2.振荡器1\n3.滑翔机\n4.振荡器2\n5.振荡器3\n请输入初始图案类型：");
    while (true) {
        int mapMode;
        scanf("%d", &mapMode);
        system("cls");
        printf("\n");
        if (mapMode <= 5 && mapMode >= 1) {
            loadSpecifiedModeMap(mapMode, map); //初始化数组
            break;
        } else printf("您输入的图案我们暂时没有！请重新输入：");
    }
}

void initRandomMap(vector<vector<bool> > &map) {
    int height, width;
    printf("请输入图像长宽：\n长：");
    scanf("%d", &height);
    printf("\n");
    printf("宽：");
    scanf("%d", &width);
    printf("\n");
    system("cls");
    map = vector<vector<bool> >(height, vector<bool>(width, false));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[i][j] = rand() & 1;
            //1代表活
            //0代表死亡
        }
    }
}

void runRandomModeGame() {
    vector<vector<bool> > map;
    initRandomMap(map);
    runGame(map); //跑
}

void runSpecifiedModeGame() {
    vector<vector<bool> > map;
    initSpecifiedModeMap(map);
    runGame(map);
}

void startLifeGame() {
    while (true) {
        hideCursor();//隐藏鼠标
        printf("请选择游戏模式：\n1.随机初始图像\n2.指定初始图像\n0.结束游戏\n请输入：");
        int mode;
        scanf("%d", &mode);
        system("cls");
        if (mode == 1) {
            runRandomModeGame();
        } else if (mode == 2) {
            runSpecifiedModeGame();
        } else if (mode == 0) {
            break;
        } else printf("输入有误，请重新输入：");
    }
}