
#include "janken.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <limits>

using namespace std;

// ===== Playerクラス =====

// コンストラクタ
Player::Player(const char* playerName) {
    SetName(playerName);
    hand = ROCK;
    winCount = 0;
}

// 名前を設定する
void Player::SetName(const char* playerName) {
    int i = 0;

    while (i < NAME_LENGTH - 1 && playerName[i] != '\0') {
        name[i] = playerName[i];
        i++;
    }

    name[i] = '\0';
}

// 名前を取得する
const char* Player::GetName() const {
    return name;
}

// 手を設定する
void Player::SetHand(int newHand) {
    hand = newHand;
}

// 手を取得する
int Player::GetHand() const {
    return hand;
}

// 勝利数を1増やす
void Player::AddWin() {
    winCount++;
}

// 勝利数を取得する
int Player::GetWinCount() const {
    return winCount;
}


// ===== JankenGameクラス =====

// コンストラクタ
JankenGame::JankenGame()
    : player("プレイヤー"),
    computer("コンピューター"),
    drawCount(0) {
}

// プレイヤーの手を入力
int JankenGame::InputHand() {
    int hand;

    while (true) {
        cout << "\n0:グー 1:チョキ 2:パー" << endl;
        cout << "手を入力してください：";

        if (cin >> hand) {
            if (hand >= 0 && hand <= 2) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return hand;
            }
        }

        if (cin.eof()) {
            return -1;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "0～2を入力してください。" << endl;
    }
}

// 手を文字で表示する
const char* JankenGame::ShowHand(int hand) {
    const char* handNames[3] = {
        "グー", "チョキ", "パー"
    };

    return handNames[hand];
}

// 勝敗判定
int JankenGame::Judge(int playerHand, int computerHand) {

    // あいこ
    if (playerHand == computerHand) {
        return 0;
    }

    // プレイヤーの勝ち
    if ((playerHand == ROCK && computerHand == SCISSORS) ||
        (playerHand == SCISSORS && computerHand == PAPER) ||
        (playerHand == PAPER && computerHand == ROCK)) {
        return 1;
    }

    // プレイヤーの負け
    return -1;
}

// ゲーム全体の進行
void JankenGame::Play() {

    char inputName[NAME_LENGTH];

    cout << "名前を入力してください：";
    cin >> setw(NAME_LENGTH) >> inputName;

    if (!cin) {
        return;
    }

    player.SetName(inputName);

    cout << "\nじゃんけんゲーム開始！" << endl;

    const int MAX_BATTLE = 5;
    const int TARGET_WIN = 3;

    // 最大5回、またはどちらかが3勝するまで
    while (player.GetWinCount() < TARGET_WIN &&
        computer.GetWinCount() < TARGET_WIN &&
        player.GetWinCount() + computer.GetWinCount() < MAX_BATTLE) {

        // 人間の手
        int playerHand = InputHand();

        if (playerHand == -1) {
            return;
        }

        player.SetHand(playerHand);

        // コンピューターの手
        computer.SetHand(rand() % 3);

        // お互いの手を表示
        cout << "\n" << player.GetName() << "："
            << ShowHand(player.GetHand()) << endl;

        cout << computer.GetName() << "："
            << ShowHand(computer.GetHand()) << endl;

        // 勝敗判定
        int result = Judge(player.GetHand(), computer.GetHand());

        if (result == 1) {
            cout << "あなたの勝ち！" << endl;
            player.AddWin();
        }
        else if (result == -1) {
            cout << "あなたの負け！" << endl;
            computer.AddWin();
        }
        else {
            cout << "あいこ！" << endl;
            drawCount++;
        }

        // 現在の成績
        cout << "現在の成績："
            << player.GetWinCount() << "勝 "
            << computer.GetWinCount() << "敗 "
            << drawCount << "引き分け" << endl;
    }

    // 最終結果
    cout << "\n===== 最終結果 =====" << endl;

    cout << player.GetWinCount() << "勝 "
        << computer.GetWinCount() << "敗 "
        << drawCount << "引き分け" << endl;

    if (player.GetWinCount() > computer.GetWinCount()) {
        cout << player.GetName() << "の勝利です！" << endl;
    }
    else if (player.GetWinCount() < computer.GetWinCount()) {
        cout << "コンピューターの勝利です！" << endl;
    }
    else {
        cout << "引き分けです！" << endl;
    }
}
