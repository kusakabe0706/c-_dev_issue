#ifndef SHOW_H
#define SHOW_H

#include <vector>
#include <string>
#include "Command.h"

using namespace std;

class Player; // 前方宣言
class Enemy;

class Show {
private:
    static vector<string> logBuffer_;//ログ置き場
    static const int MAX_LOGS_ = 11; //表示するログの最大数

public:
    // --- 画面描画系 ---
    static void draw(Player* player, const vector<Enemy*>& enemy);
    static void displayAction(int commandId, const string& actorName);
    static void displayCommandList(const vector<Command*>& commands);
    static int  displayTitle();//タイトル画面表示

    // --- ログ管理系 ---
    static void addLog(const std::string& msg);//ログ追加
    static void clearLogs();//ログ削除

    // --- ユーティリティ（特殊入力・座標） ---
    static void waitForInput();
    static int  getch(); // Enter/Esc判定用の直接入力
};

#endif