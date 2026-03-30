#ifndef SHOW_H
#define SHOW_H

#include <vector>
#include <string>
using namespace std;

class Player;
class Enemy;

struct CommandData; 

class Show 
{
private:
    Show() {}
    static vector<string> logBuffer_;
    static const int MAX_LOGS_ = 11; // ログの最大保持数

public:
    // --- 画面描画 ---
    static void draw(Player* player, const vector<Enemy*>& enemy);
    static int  displayTitle();
    static void displayAction(int commandId, const string& actorName);

    // --- メニュー・ターゲット選択 ---
    static int  displayCommandList(const vector<int>& playerSkillIds);
    static int  selectTarget(const vector<Enemy*>& enemies);

    // --- ログ管理 ---
    static void addLog(const string& msg);
    static void clearLogs();

    // --- 入力・制御 ---
    static void waitForInput();
    static int  getch();
};

#endif