#include "CommandMaster.h"
using namespace std;

CommandData CommandMaster::Getter(int id){

    switch(id){
        case 1: return CommandData(1, "攻撃", 0);
        case 2: return CommandData(2, "防御", 0);
        case 3: return CommandData(3, "回復", 10);
        case 4: return CommandData(4, "攻撃力アップ", 5);
        case 5: return CommandData(5, "逃げる", 0);
        case 6: return CommandData(6, "カウンター", 0);
        case 7: return CommandData(7, "でんじは", 5);
        //存在しないコマンドが呼ばれたとき
        default: return CommandData(0, "不明なコマンド", 0);
    }
}
