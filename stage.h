#ifndef STAGE_H
#define STAGE_H

#include <vector>

// 別のファイルで定義されているクラスを使うための宣言（前方宣言）
class Player;
class Enemy;
class Entity;
struct CommandData;

class Stage
{
private:
    //登場人物のポインタ
    Player* player_;
    Enemy* enemy1_;
    Enemy* enemy2_;

    // 内部補助関数
    std::vector<Enemy*> getEnemyList();         // 今stage上にいる敵のリストをひとまとめにして返す
    bool isBattleEnd();                         // バトルが終了したかどうかを判定する
    void playerPhase();                         // プレイヤーがコマンドを選ぶ時の処理
    void enemyPhase(Enemy* enemy);              // 敵が行動を決める時の処理
    void executeAction(Entity* attacker, Entity* target, const CommandData& cmd);// 実際にダメージを与えたり状態を変えたりする実行処理
    void showResult();// リザルト

public:
    Stage();
    ~Stage();
    void start(); // バトル開始（メインループ）
};

#endif