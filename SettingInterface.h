#pragma once

#include "GameInterface.h"

class SettingInterface : public QWidget
{
public:
    explicit SettingInterface(QWidget *parent = nullptr);

    ~SettingInterface() override = default;

private:
    static int MapSize;

    static int BombNumber;

    QLabel *TitleLabel = new QLabel("扫雷小游戏", this);

    QLabel *MapSizeLabel = new QLabel("布局大小：", this);

    QLineEdit *MapSizeLineEdit = new QLineEdit(QString::number(MapSize), this);

    QLabel *BoardNumberLabel = new QLabel("炸弹数量：", this);

    QLineEdit *BoardNumberLineEdit = new QLineEdit(QString::number(BombNumber), this);

    QPushButton *StartGameButton = new QPushButton("开始游戏", this);
};
