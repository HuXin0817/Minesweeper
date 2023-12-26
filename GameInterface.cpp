#include "GameInterface.h"
#include "SettingInterface.h"

GameInterface::GameInterface(QWidget *parent, const int &mapSize = 20, const int &bombNumber = 20) : QWidget(parent), MapSize(mapSize), BombNumber(bombNumber)
{

    QIcon icon("Bomb.png");
    setWindowIcon(icon);

    std::random_device rd;
    std::mt19937 gen(rd());

    PointButton = std::vector<std::vector<QPushButton *>>(MapSize);
    for (auto &item : PointButton)
    {
        item = std::vector<QPushButton *>(MapSize);
    }

    HasBomb = std::vector<std::vector<bool>>(MapSize);
    for (auto &item : HasBomb)
    {
        item = std::vector<bool>(MapSize);
    }

    Showed = std::vector<std::vector<bool>>(MapSize);
    for (auto &item : Showed)
    {
        item = std::vector<bool>(MapSize);
    }

    std::set<int> bomb;
    std::uniform_int_distribution dist(0, MapSize * MapSize - 1);

    while (bomb.size() < BombNumber)
    {
        bomb.insert(dist(gen));
    }

    for (const auto &i : bomb)
    {
        HasBomb[i / MapSize][i % MapSize] = true;
    }

    this->setFixedSize(50 * (MapSize + 1), 50 * (MapSize + 1));
    this->setWindowTitle("扫雷小游戏");

    for (int i = 0; i < MapSize; i++)
    {
        for (int j = 0; j < MapSize; j++)
        {
            PointButton[i][j] = new QPushButton(this);
            PointButton[i][j]->setGeometry(25 + 50 * i, 25 + 50 * j, 50, 50);
            PointButton[i][j]->setContextMenuPolicy(Qt::CustomContextMenu);

            QFont font;
            font.setBold(true);
            font.setPointSize(12);

            PointButton[i][j]->setFont(font);
            PointButton[i][j]->setStyleSheet("color: red;");

            QObject::connect(PointButton[i][j], &QPushButton::clicked, [this, i, j]()
                             {
                if (PointButton[i][j]->text().length()) {
                    std::thread threadObj([]() {
                        mciSendStringA("play GameMusic\\ErrorTouch.mp3", nullptr, 0, nullptr);
                    });
                    threadObj.detach();
                    return;
                }
                std::thread threadObj([]() {
                    mciSendStringA("play GameMusic\\Touch.mp3", nullptr, 0, nullptr);
                });
                threadObj.detach();
                ShowInfo(i, j);
                QThread::msleep(100); });

            QObject::connect(PointButton[i][j], &QPushButton::customContextMenuRequested, [this, i, j]()
                             {
                if (PointButton[i][j]->text() == "*") {
                    std::thread threadObj([]() {
                        mciSendStringA("play GameMusic\\Touch.mp3", nullptr, 0, nullptr);
                    });
                    threadObj.detach();
                    PointButton[i][j]->setText("");
                } else {
                    std::thread threadObj([]() {
                        mciSendStringA("play GameMusic\\Touch.mp3", nullptr, 0, nullptr);
                    });
                    threadObj.detach();
                    PointButton[i][j]->setText("*");
                    CheckWin();
                }
                QThread::msleep(100); });
        }
    }
}

void GameInterface::ShowInfo(const int &i, const int &j)
{

    Showed[i][j] = true;
    PointButton[i][j]->text().clear();
    PointButton[i][j]->close();

    if (HasBomb[i][j])
    {
        for (int ii = 0; ii < MapSize; ii++)
        {
            for (int jj = 0; jj < MapSize; jj++)
            {
                PointButton[ii][jj]->setText("");
                if (HasBomb[ii][jj])
                {
                    QIcon icon("Bomb.png");
                    setWindowIcon(icon);
                    auto *qPushButton = new QPushButton(this);
                    qPushButton->setGeometry(25 + 50 * ii, 25 + 50 * jj, 50, 50);
                    qPushButton->setIcon(icon);
                    qPushButton->raise();
                    qPushButton->show();
                }
            }
        }

        std::thread threadObj([]()
                              { mciSendStringA("play GameMusic\\Lose.mp3", nullptr, 0, nullptr); });
        threadObj.detach();
        QMessageBox::critical(nullptr, "GameOver", "菜狗！！");
        QThread::msleep(500);
        this->close();
        auto *setting = new SettingInterface();
        setting->show();
        return;
    }

    int cnt = 0;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dy == 0 && dx == 0)
            {
                continue;
            }
            if (i + dx >= MapSize || i + dx < 0)
            {
                continue;
            }
            if (j + dy >= MapSize || j + dy < 0)
            {
                continue;
            }

            cnt += HasBomb[i + dx][j + dy];
        }
    }

    auto *numLabel = new QLabel(QString::number(cnt), this);
    numLabel->setGeometry(25 + 50 * i, 25 + 50 * j, 50, 50);
    numLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    numLabel->setStyleSheet("QLabel { font-family: Consolas; font-size: 11pt; }");
    numLabel->show();

    if (cnt == 0)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (dy == 0 && dx == 0)
                {
                    continue;
                }
                if (i + dx >= MapSize || i + dx < 0)
                {
                    continue;
                }
                if (j + dy >= MapSize || j + dy < 0)
                {
                    continue;
                }
                if (Showed[i + dx][j + dy])
                {
                    continue;
                }
                ShowInfo(i + dx, j + dy);
            }
        }
    }
}

void GameInterface::CheckWin()
{
    int cnt = 0;

    for (int i = 0; i < MapSize; i++)
    {
        for (int j = 0; j < MapSize; j++)
        {
            if (PointButton[i][j]->text() == "*" && !HasBomb[i][j])
            {
                return;
            }
            if (PointButton[i][j]->text() == "*" && HasBomb[i][j])
            {
                cnt++;
            }
        }
    }

    if (cnt == BombNumber)
    {
        std::thread threadObj([]()
                              { mciSendString("play GameMusic\\Win.mp3", nullptr, 0, nullptr); });
        threadObj.detach();
        QMessageBox::information(this, "Win", "这都能赢？！");
        this->close();
        auto *setting = new SettingInterface();
        setting->show();
    }
}
