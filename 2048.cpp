#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <windows.h>
#include <conio.h>
using namespace std;

 //控制台清屏函数（避免 flicker）
void clearScreen() {
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

 //游戏棋盘逻辑为 4×4
vector<vector<int>> grid(4, vector<int>(4, 0));
int score = 0;//分数

 //绘制字符画
void display() {
    clearScreen();
    cout << "当前得分: " << score << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "|";
        for (int j = 0; j < 4; j++) {
            if (grid[i][j] == 0)
                cout << setw(4) << " ";
            else
                cout << setw(4) << grid[i][j];
        }
        cout << " |" << endl;
        cout << "-----------------" << endl;
    }
}

 //随机选取空位并放入 2 或 4
void spawnTile() {
    vector<pair<int, int>> empty;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == 0)
                empty.emplace_back(i, j);

    if (empty.empty()) return;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0, empty.size() - 1);
    auto [r, c] = empty[dist(rng)];

     //10% 概率生成 4
    grid[r][c] = (rand() % 10 == 0 ? 4 : 2);
}

 //将一行向左合并
vector<int> compressRow(vector<int> row) {
    vector<int> newRow;
    for (int x : row)
        if (x != 0) newRow.push_back(x);
    while (newRow.size() < 4) newRow.push_back(0);
    return newRow;
}

vector<int> mergeRow(vector<int> row) {
    for (int i = 0; i < 3; i++) {
        if (row[i] != 0 && row[i] == row[i + 1]) {
            row[i] *= 2;
            score += row[i];
            row[i + 1] = 0;
        }
    }
    return compressRow(row);
}

 //移动逻辑
bool moveLeft() {
    bool moved = false;
    for (int i = 0; i < 4; i++) {
        auto old = grid[i];
        auto compressed = compressRow(grid[i]);
        auto merged = mergeRow(compressed);
        if (merged != old) moved = true;
        grid[i] = merged;
    }
    return moved;
}

bool moveRight() {
    bool moved = false;
    for (int i = 0; i < 4; i++) {
        auto old = grid[i];
        reverse(grid[i].begin(), grid[i].end());
        auto compressed = compressRow(grid[i]);
        auto merged = mergeRow(compressed);
        reverse(merged.begin(), merged.end());
        if (merged != old) moved = true;
        grid[i] = merged;
    }
    return moved;
}

bool moveUp() {
    bool moved = false;
    for (int j = 0; j < 4; j++) {
        vector<int> col;
        for (int i = 0; i < 4; i++) col.push_back(grid[i][j]);
        auto old = col;
        auto compressed = compressRow(col);
        auto merged = mergeRow(compressed);
        for (int i = 0; i < 4; i++) grid[i][j] = merged[i];
        if (merged != old) moved = true;
    }
    return moved;
}

bool moveDown() {
    bool moved = false;
    for (int j = 0; j < 4; j++) {
        vector<int> col;
        for (int i = 0; i < 4; i++) col.push_back(grid[i][j]);
        auto old = col;
        reverse(col.begin(), col.end());
        auto compressed = compressRow(col);
        auto merged = mergeRow(compressed);
        reverse(merged.begin(), merged.end());
        for (int i = 0; i < 4; i++) grid[i][j] = merged[i];
        if (merged != old) moved = true;
    }
    return moved;
}

 //检查游戏是否结束
bool isGameOver() {
     //有空位就没结束
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == 0)
                return false;
     //检查是否还能合并
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (i < 3 && grid[i][j] == grid[i + 1][j]) return false;
            if (j < 3 && grid[i][j] == grid[i][j + 1]) return false;
        }
    return true;
}

int main() {
    srand((unsigned)time(nullptr));
    system("cls");

     //初始化两个数字
    spawnTile();
    spawnTile();
    display();

    char op;
    while (true) {
        cout << "按q退出，输入方向 (WASD): ";
        char op = _getch();  // 立即读取按键，不用回车

        bool moved = false;
        if (op == 'a' || op == 'A') moved = moveLeft();
        else if (op == 'd' || op == 'D') moved = moveRight();
        else if (op == 'w' || op == 'W') moved = moveUp();
        else if (op == 's' || op == 'S') moved = moveDown();
        else if (op == 'q' || op == 'Q') {  // 退出键
            cout << "\n你退出了游戏。" << endl;
            break;
        }
        else {
            continue;
        }

        if (moved) spawnTile();
        display();

        if (isGameOver()) {
            cout << "游戏结束！" << endl;
            break;
        }
    }

    return 0;
}
