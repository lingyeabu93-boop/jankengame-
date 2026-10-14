
#pragma once

const int NAME_LENGTH = 50;

// じゃんけんの手
enum Hand {
    ROCK = 0,
    SCISSORS = 1,
    PAPER = 2
};

// プレイヤークラス
class Player {
private:
    char name[NAME_LENGTH];
    int hand;
    int winCount;

public:
    Player(const char* playerName);

    void SetName(const char* playerName);
    const char* GetName() const;

    void SetHand(int newHand);
    int GetHand() const;

    void AddWin();
    int GetWinCount() const;
};

// じゃんけんゲームクラス
class JankenGame {
private:
    Player player;
    Player computer;

    int drawCount;

    int InputHand();
    int Judge(int playerHand, int computerHand);
    const char* ShowHand(int hand);

public:
    JankenGame();

    void Play();
};
