
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "janken.h"

using namespace std;

int main() {

    // 乱数の初期化
    srand(static_cast<unsigned int>(time(nullptr)));

    // じゃんけんゲームのオブジェクトを作成
    JankenGame game;

    // ゲーム開始
    game.Play();

    return 0;
}
