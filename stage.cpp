#include <algorithm>
#include <vector>
#include <string>
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Show.h"
#include "Calc.h"
#include "Command.h"
#include "Unit.h"

using namespace std;

Stage::Stage()
{
    player_ = new Player();
    enemy1_ = new Enemy("半グレA", 1); 
    enemy2_ = new Enemy("半グレB", 2); 
}

Stage::~Stage()
{
    delete player_;
    delete enemy1_;
    delete enemy2_;
}

// 今戦場にいる敵のリストをひとまとめにして返す
vector<Enemy*> Stage::getEnemyList()
{
    vector<Enemy*> list;
    if (enemy1_) list.push_back(enemy1_);
    if (enemy2_) list.push_back(enemy2_);
    return list;
}

// バトルが終了したかどうかを判定する
bool Stage::isBattleEnd()
{
    // プレイヤーが死んだか、逃走に成功していたら終了
    if (!player_->is_alive() || player_->getStatus()->getEscape())
    {
        return true;
    }
    // または、敵が二人とも倒れていたら終了
    if (!enemy1_->is_alive() && !enemy2_->is_alive())
    {
        return true;
    }
    return false;
}

　//メインループ

void Stage::start()
{
    Show::addLog("ならず者が 現れた！");

    // バトルが終わる条件を満たすまで
    while (!isBattleEnd())
    {
        // 現在のHPやAA（アスキーアート）を画面に表示する
        Show::draw(player_, getEnemyList());

        // 生きているunitリスト作成
        vector<Unit*> order;
        if (player_->is_alive()) order.push_back(player_);
        if (enemy1_->is_alive()) order.push_back(enemy1_);
        if (enemy2_->is_alive()) order.push_back(enemy2_);

        // 全員の行動を予約する
        for (size_t i = 0; i < order.size(); ++i)
        {
            Unit* reserv = order[i];
            
            // 自分の番が回ってきたので、前のターンに構えていた防御やカウンターを解除する
            reserv->getStatus()->setCounter(false);
            reserv->getStatus()->setGuard(false);

            // プレイヤーならキー入力を待ち、敵ならランダムで行動を決める
            if (reserv == player_)
            {
                playerPhase();
            }
            else
            {
                enemyPhase(dynamic_cast<Enemy*>(reserv));
            }
        }

        //　行動順をソート
        // 優先度（防御など）が高い順、同じなら素早さが高い順に並べる
        sort(order.begin(), order.end(), [](Unit* a, Unit* b) 
        {
            if (a->getNextCommand().priority != b->getNextCommand().priority)
            {
                return a->getNextCommand().priority > b->getNextCommand().priority;
            }
            return a->getStatus()->getSpd() > b->getStatus()->getSpd();
        });

        // 実行フェーズ
        for (size_t i = 0; i < order.size(); ++i)
        {
            Unit* activeEntity = order[i];

            // ターン中自分の番が来る前に死んでいたら
            if (!activeEntity->is_alive())
            {
                continue;
            }

            // 状態異常のカウントダウン
            bool wasPara = activeEntity->getStatus()->getisPara();
            bool wasBuff = activeEntity->getStatus()->getisAtkBuff();

            activeEntity->getStatus()->tickStatus();

            if (wasPara && !activeEntity->getStatus()->getisPara())
            {
                Show::addLog(activeEntity->getStatus()->getName() + " のしびれが取れた！");
            }

            if (wasBuff && !activeEntity->getStatus()->getisAtkBuff())
            {
                Show::addLog(activeEntity->getStatus()->getName() + " の攻撃力アップが切れた。");
            }

            // 麻痺の判定
            if (activeEntity->getStatus()->getisPara())
            {
                // 1〜100のサイコロを振って、25以下（＝25%の確率）なら
                if (Calc::getRandom(1, 100) <= 25)
                {
                    Show::addLog(activeEntity->getStatus()->getName() + " は体がしびれて動けない！");
                    Show::draw(player_, getEnemyList());
                    Show::waitForInput();
                    continue; 
                }
            }

            // 予約しておいた技をターゲットに対して実行する
            executeAction(activeEntity, activeEntity->getNextTarget(), activeEntity->getNextCommand());

            // 全滅したか
            if (isBattleEnd()) break;
        }
    }
    // バトルが終わったら結果画面を表示
    showResult();
}

// 行動決定フェーズ

// プレイヤーがコマンドを選ぶ時の処理
void Stage::playerPhase()
{
    // コマンド選択ループ
    while (true)
    {
        // 技リストを画面に出して、番号を選んでもらう
        int skillId = Show::displayCommandList(player_->getSkillIds());
        CommandData cmd = CommandMaster::Getter(skillId);

        // MPが足りているか比較
        if (player_->getStatus()->getMp() < cmd.mpCost)
        {
            // 警告メッセージをログに送る
            Show::addLog("ＭＰが 足りません！");
            Show::draw(player_, getEnemyList());
            Show::waitForInput();
            continue; 
        }

        Unit* target = nullptr;

        //選んだ技が「通常攻撃(ID 1)」の時だけ、ターゲット選択を行う
        if (cmd.id == 1)
        {
            int targetIdx = Show::selectTarget(getEnemyList());

            // ターゲット選択でEsc（キャンセル）されたら、技選択の最初に戻る
            if (targetIdx == -1)
            {
                continue; 
            }

            target = getEnemyList()[targetIdx];
        }
        else
        {
            // 防御や自己強化などは、自分自身をターゲットにする
            target = player_;
        }

        // 行動予約を完了する
        player_->setNextAction(cmd, target);
        break;
    }
}

// 敵（半グレ）が行動を決める時の処理
void Stage::enemyPhase(Enemy* enemy)
{
    const vector<int>& skills = enemy->getSkillIds();
    CommandData cmd;

    //使える技が見つかるまで、何度も引き直すループ
    while (true)
    {
        // 技リストの中からランダムに一つ選ぶ
        int randomIndex = Calc::getRandom(0, static_cast<int>(skills.size()) - 1);
        cmd = CommandMaster::Getter(skills[randomIndex]);

        // MPが足りているか比較
        if (enemy->getStatus()->getMp() >= cmd.mpCost)
        {
            break;
        }
    }

    // ターゲットを決定する
    Unit* target = nullptr;

    // 攻撃系の技（ID 1, 7 など）はプレイヤーを狙う
    if (cmd.id == 1 || cmd.id == 7)
    {
        target = player_;
    }
    else
    {
        // それ以外（防御、カウンターなど）は自分自身を狙う
        target = enemy;
    }

    // 決まった技とターゲットを予約する
    enemy->setNextAction(cmd, target);
}

// アクション実行フェーズ

// 実際にダメージを与えたり状態を変えたりする処理
void Stage::executeAction(Unit* attacker, Unit* target, const CommandData& cmd)
{
    // ＭＰを消費させる
    int currentMp = attacker->getStatus()->getMp();
    attacker->getStatus()->setMp(currentMp - cmd.mpCost);

    // 選んだ技のID確認
    switch (cmd.id)
    {
        case 2: // 防御
        {
            Show::addLog(attacker->getStatus()->getName() + " は身を守っている！");
            attacker->getStatus()->setGuard(true); // 防御フラグを立てる
            break;
        }

        case 3: // 回復
        {
            Show::addLog(attacker->getStatus()->getName() + " の傷が癒えていく....！");

            int healAmount = 50;

            // 回復前のHPを覚えておく
            int beforeHp = attacker->getStatus()->getHp();

            // 実際にセットする（Status側のガードで最大値は超えない）
            attacker->getStatus()->setHp(beforeHp + healAmount);

            // セットした後のHPを確認し、実際に増えた「差分」を計算する
            int afterHp = attacker->getStatus()->getHp();
            int actualHeal = afterHp - beforeHp;

            // 実際に増えた数値をログに出す
            Show::addLog(attacker->getStatus()->getName() + " の体力が " + to_string(actualHeal) + " 回復した！");
            break;
        }

        case 4: // 攻撃バフ
        {
            Show::addLog(attacker->getStatus()->getName() + " は少しの間攻撃力が上がった！");
            attacker->getStatus()->setAtkBuff(true);
            break;
        }

        case 5: // 逃走
        {
            Show::addLog(attacker->getStatus()->getName() + " は逃げ出した！");
            attacker->getStatus()->setEscape(true);
            break;
        }

        case 6: // カウンター
        {
            Show::addLog(attacker->getStatus()->getName() + " はカウンターを狙っている！");
            attacker->getStatus()->setCounter(true);
            break;
        }

        case 7: // 麻痺
        {
            Show::addLog(target->getStatus()->getName() + " は麻痺状態になった!");
            target->getStatus()->setPala(true);
            break;
        }

        default: //攻撃
        {
            Show::addLog(attacker->getStatus()->getName() + " の " + cmd.name + " ！");

            // ダメージ数値を計算する
            int damage = Calc::calculateDamage(attacker, target, cmd);

            // 相手が防御中なら、耐えたメッセージを出す
            if (target->getStatus()->getGuard())
            {
                Show::addLog(target->getStatus()->getName() + " は攻撃を耐え忍んだ！");
            }

            // 相手のHPを減らし、ダメージログを表示
            target->getStatus()->setHp(target->getStatus()->getHp() - damage);
            Show::addLog(target->getStatus()->getName() + " に " + to_string(damage) + " のダメージ！");
            if (!target->is_alive())
            {
                Show::addLog(target->getStatus()->getName() + " は力尽きて倒れた！");
            }

            // カウンターをしていた場合
            if (target->is_alive() && target->getStatus()->getCounter())
            {
                Show::addLog(" ＞＞ カウンター発動！ ＜＜ ");
                int cDamage = Calc::calculateCounterDamage(damage);
                attacker->getStatus()->setHp(attacker->getStatus()->getHp() - cDamage);
                Show::addLog(attacker->getStatus()->getName() + " は手痛い反撃を喰らった！");
                Show::addLog(to_string(cDamage) + " のダメージ！");
                if (!attacker->is_alive())
                {
                    Show::addLog(attacker->getStatus()->getName() + " は相打ちで倒れた！");
                }
            }
            break;
        }
    }
    Show::draw(player_, getEnemyList());
    Show::waitForInput();
}

void Stage::showResult() // リザルト
{
    // 画面に残っている古いログを一度消す
    Show::clearLogs();

    if (player_->getStatus()->getEscape() && player_->is_alive()) // 逃走した場合の処理
    {
        Show::addLog("あなたは逃げ出した.....");
    }
    else if (player_->is_alive()) // 勝利
    {
        Show::addLog("勝利！ ならず者たちは逃げ出した。");
    }
    else // 敗北
    {
        Show::addLog("敗北... 路上に倒れ伏した。");
    }

    Show::draw(player_, getEnemyList());
    Show::waitForInput();
}