#pragma once

#include <windows.h>
#include <mmsystem.h>
#include <thread>
#include <random>
#include <set>
#include <QPushButton>
#include <QWidget>
#include <QIntValidator>
#include <QLabel>
#include <QMessageBox>
#include <QApplication>
#include <QThread>
#include <QShortcut>
#include <QLineEdit>

#pragma comment(lib, "winmm.lib")

class GameInterface : public QWidget
{

public:
    GameInterface(QWidget *parent, const int &mapSize, const int &bombNumber);

    ~GameInterface() override = default;

private:
    int MapSize;

    int BombNumber;

    std::vector<std::vector<QPushButton *>> PointButton;

    std::vector<std::vector<bool>> HasBomb;

    std::vector<std::vector<bool>> Showed;

    void ShowInfo(const int &i, const int &j);

    void CheckWin();
};