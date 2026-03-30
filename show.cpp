#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "Show.h"
#include "Player.h"
#include "Enemy.h"
#include "Status.h"
#include "Command.h"
using namespace std;

vector<string> Show::logBuffer_;

// AAデータ
static const vector<string> Player_AA =
{
"  ●",
"／|＼",
"  |",
"／ ＼",
};

static const vector<string> Enemy_AA = 
{
"∧＿∧",
"(　･ω･)=つ≡つ",
"(っ　≡つ=つ",
"/　　　) ",
"( /￣∪"
};

int Show::selectTarget(const vector<Enemy*>& enemy) 
{
    // 表示の開始座標
    int startX = 35; // 横方向（列）
    int startY = 15; // 縦方向（行）

    while (true) 
    {
        //ターゲットリストの描画
        // 上枠
        cout << "\033[" << startY << ";" << startX << "H" << "------- TARGET -------";
        
        for (size_t i = 0; i < enemy.size(); i++) 
        {
            int row = startY + 1 + i;
            // 左右の枠
            cout << "\033[" << row << ";" << startX << "H" << "|";
            cout << "\033[" << row << ";" << (startX + 22) << "H" << "|";
            
            // リストの中身
            cout << "\033[" << row << ";" << (startX + 2) << "H" << "\033[20X";
            if (enemy[i]->is_alive()) 
            {
                cout << (i + 1) << ": " << enemy[i]->getStatus()->getName();
            } else 
            {
                // 倒れている敵は選択できないようにグレーで表示
                cout << "\033[90m" << (i + 1) << ": " << enemy[i]->getStatus()->getName() << " [DEAD]\033[m";
            }
        }
        
        //下枠
        int bottomRow = startY + 1 + enemy.size();
        cout << "\033[" << bottomRow << ";" << startX << "H" << "----------------------";

        //入力選択フェーズ
        cout << "\033[25;5H" << "\033[K" << "対象の番号を選んでください (1-" << enemy.size() << ") > " << flush;
        
        int key = getch();
        if (key == 27) return -1; // Escキーでキャンセル

        int index = key - '1';

        // 有効な番号かつ生きている敵かチェック
        if (index >= 0 && index < (int)enemy.size() && enemy[index]->is_alive()) 
        {
            string targetName = enemy[index]->getStatus()->getName();

            // 確認フェーズ (Y/N)
            while (true) 
            {
                cout << "\033[25;5H" << "\033[K" << targetName << " でよろしいですか？ (Y/N) > " << flush;
                
                int confKey = getch();

                // 'Y' または 'Enter' で確定
                if (confKey == 'y' || confKey == 'Y' || confKey == 10 || confKey == 13) 
                {
                    return index; // ターゲット決定！
                }
                
                // 'N' または 'Esc' でキャンセルして選択に戻る
                if (confKey == 'n' || confKey == 'N' || confKey == 27) 
                {
                    break; // 内側のループ（確認）を抜けて、外側のループ（選択）の最初へ
                }
            }
        }
        else 
        {
            // 無効な入力や倒れている敵を選んだ場合
            cout << " 正しい番号を選んでください。";
            cout.flush();
            usleep(1500000); // 1.5秒だけ警告を表示
        }
    }
}

int Show::displayCommandList(const vector<int>& playerSkillIds) 
{
    // 表示フェーズ
    int startRow = 15;
    //上枠
    cout << "\033[" << startRow << ";3H" << "----------------------------"; 

    //技リストの描画
    for (size_t i = 0; i < playerSkillIds.size(); i++)
    {
        CommandData cmd = CommandMaster::Getter(playerSkillIds[i]);
        int row = startRow + 1 + i; 
        
        //左右の枠
        cout << "\033[" << row << ";3H" << "|"; 
        cout << "\033[" << row << ";30H" << "|";
        
        //技名表示
        cout << "\033[" << row << ";5H" << "\033[24X" 
             << (i + 1) << ": " << cmd.name << " (MP:" << cmd.mpCost << ")";
    }

    //下枠
    int bottomRow = startRow + 1 + playerSkillIds.size();
    cout << "\033[" << bottomRow << ";3H" << "----------------------------"; 

    // 入力選択フェーズ
    while (true) 
    {
        //入力ガイドを表示
        cout << "\033[" << bottomRow + 1 << ";5H" << "\033[K" 
             << "コマンドを選択 (1-" << playerSkillIds.size() << ") > " << flush;

        int key = getch();
        if (key == 27) return -1; //Escキーでキャンセル（Stageに戻る）

        int index = key - '1'; //ASCIIコードから添字に変換

        //有効な数字が押されたかチェック
        if (index >= 0 && index < (int)playerSkillIds.size()) 
        {
            CommandData selectedCmd = CommandMaster::Getter(playerSkillIds[index]);

            //確認フェーズ (Y/N)
            while (true) 
            {
                cout << "\033[" << bottomRow + 1 << ";5H" << "\033[K" 
                     << selectedCmd.name << " でよろしいですか？ (Y/N) > " << flush;
                
                int confKey = getch();

                //Yまたはnterで確定
                if (confKey == 'y' || confKey == 'Y' || confKey == 10 || confKey == 13) 
                {
                    return playerSkillIds[index]; //決定したスキルIDを返す
                }
                
                //Nたは Escでキャンセルして選択に戻る
                if (confKey == 'n' || confKey == 'N' || confKey == 27) 
                {
                    break; 
                }
            }
        }
    }
}

int Show::getch() 
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Enterなし・入力文字を画面に出さない設定
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 設定を元に戻す
    return ch;
}


void Show::addLog(const string& msg) 
{
    logBuffer_.push_back(msg);          //ログ最後尾にメッセージ追加

    if (logBuffer_.size() > MAX_LOGS_)  //ログが最大保持数より多かったら一番古いログ削除
    {
        logBuffer_.erase(logBuffer_.begin());
    }
}

void Show::clearLogs() 
{
    logBuffer_.clear();//ログ全消し
}

void Show::waitForInput() //ボタンが押されるまで待つ
{
    cout << "\033[25;50H" << "-- 任意のキーを押して下さい --" << flush;
    getch(); 
    cout << "\033[25;50H" << "\033[20X" << flush;
}

void Show::draw(Player* player, const vector<Enemy*>& enemy) 
{
    cout << "\033[2J\033[H";    //画面クリア
    int startY_AA = 7;          //AA表示Y行
    int startX_AA = 40;         //AA表示X行

    //プレイヤー表示
    for (size_t i = 0; i < Player_AA.size(); i++)
    {
        //AA描画
        cout << "\033[" << (startY_AA + i) << ";" << startX_AA << "H" << Player_AA[i];
    }
    
    //プレイヤーステータス表示
    cout << "\033[5;4H"  << " 　名前:" << player->getStatus()->getName();
    cout << "\033[6;4H"  << " 　ｈｐ:" << player->getStatus()->getHp();
    cout << "\033[7;4H"  << " 攻撃力:" << player->getStatus()->getAtk();
    cout << "\033[8;4H"  << " 防御力:" << player->getStatus()->getDef();
    cout << "\033[9;4H"  << " 　ｍｐ:" << player->getStatus()->getMp();
    cout << "\033[10;4H" << " 素早さ:" << player->getStatus()->getSpd();

    //ステータスの枠
    for(int i = 0; i < 7; i++)
    {
        cout << "\033[" << i + 4 << ";3H" << "|"; 
        cout << "\033[" << i + 4 << ";30H" << "|";
    }
    cout << "\033[4;3H"  << "----------------------------";
    cout << "\033[11;3H" << "----------------------------";
   

    //敵表示
    for (size_t i = 0; i < enemy.size(); i++)
    {
        int startY = 5;             //敵の表示開始行
        int startX = 90 + (i * 30); //X座標
        startY_AA = 7;              //敵のAA表示開始行
        startX_AA = 92 + (i * 30);  //X座標
        

        if (enemy[i]->is_alive())
        {
            //ステータス表示
            cout << "\033[" << startY << ";" << startX << "H" << "[" << enemy[i]->getStatus()->getName() << "]" 
            << "\033[" << (startY + 1) << ";" << (startX + 1) << "H" << " HP:" << enemy[i]->getStatus()->getHp();

            //AA表示
            for (size_t j = 0; j < Enemy_AA.size(); j++)
            {
                //下にずらして描画
                cout << "\033[" << (startY_AA + j) << ";" << startX_AA << "H" << Enemy_AA[j];
            }
        } 
        else 
        {
            // 死亡している場合
            cout << "\033[" << startY << ";" << startX << "H" << " [DEAD]";
        }
    }

    //バトルログの枠表示 
    cout << "\033[26;1H" << "============================================================================================================================================================";
    cout << "\033[38;1H" << "============================================================================================================================================================";

    //バトルログの中身表示
    for (size_t i = 0; i < logBuffer_.size(); i++)
    {
        if (i >= MAX_LOGS_) break; 
        cout << "\033[" << (27 + i) << ";5H" << "\033[155X" << logBuffer_[i];
    }
    cout << flush; 
}


void Show::displayAction(int commandId, const string& actorName) 
{
    string msg;

    //IDに応じてメッセージを作成
    switch (commandId) 
    {
        case 1: msg = actorName + " の攻撃！"; break;
        case 2: msg = actorName + " の防御！"; break;
        case 3: msg = actorName + " の回復！"; break;
        case 4: msg = actorName + " のATKバフ！"; break;
        case 5: msg = actorName + " の逃げる！"; break;
        case 6: msg = actorName + " のカウンター！"; break;
        case 7: msg = actorName + " のでんじは！"; break;
    }

    //ログバッファに追加
    addLog(msg);
}

int Show::displayTitle()
{
    //画面クリア
    cout << "\033[2J\033[H";

    //タイトル
    cout << "\033[13;52H" << "     ■■■■■           ■        ■■       ■■    ■■■■■■■" << endl;
    cout << "\033[14;52H" << "    ■■     ■        ■■■       ■■       ■■    ■      " << endl;
    cout << "\033[15;52H" << "   ■■               ■ ■       ■■■     ■■■    ■      " << endl;
    cout << "\033[16;52H" << "   ■               ■   ■      ■■■     ■■■    ■      " << endl;
    cout << "\033[17;52H" << "   ■              ■     ■     ■   ■■■  ■■    ■      " << endl;
    cout << "\033[18;52H" << "   ■      ■■■     ■     ■     ■    ■    ■    ■■■■■■ " << endl;
    cout << "\033[19;52H" << "   ■        ■     ■■■■■■■     ■    ■    ■    ■      " << endl;
    cout << "\033[20;52H" << "   ■■       ■    ■       ■    ■    ■    ■    ■      " << endl;
    cout << "\033[21;52H" << "    ■■     ■■    ■       ■    ■         ■    ■      " << endl;
    cout << "\033[22;52H" << "     ■■■■■      ■■       ■■   ■         ■    ■■■■■■■" << endl;

    cout << "\033[32;52H" << "   [ Enter ] : GAME START";
    cout << "\033[32;92H" << "   [  Esc  ] : Exit";
    cout << "\033[36;52H" << "[Enter]か[Esc]キーを押して下さい。 >";
    cout.flush();
    
    while (true) {
        int key = getch(); //キー入力を待つ

        if (key == 10 || key == 13) //enterキー
        {  
            return 1; 
        }
        if (key == 27) //escキー
        { 
            return 0; 
        }

    }
}

