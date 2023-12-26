#include "SettingInterface.h"

int SettingInterface::MapSize = 20;

int SettingInterface::BombNumber = 20;

SettingInterface::SettingInterface(QWidget *parent) : QWidget(parent)
{

    QIcon icon("Bomb.png");
    setWindowIcon(icon);

    this->setFixedSize(500, 500);
    setWindowTitle("扫雷");

    TitleLabel->setGeometry(0, 0, this->geometry().width(), 150);
    TitleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    TitleLabel->setStyleSheet("QLabel { font-family: 'Times New Roman, 华文行楷'; font-size: 22pt; }");

    MapSizeLabel->setGeometry(50, 170, 200, 60);
    MapSizeLabel->setStyleSheet("QLabel { font-family: 华文行楷; font-size: 12pt; }");
    MapSizeLabel->setAlignment(Qt::AlignTop);

    MapSizeLineEdit->setGeometry(250, 150, 200, 60);
    MapSizeLineEdit->setStyleSheet("QLineEdit { font-family: Consolas; font-size: 12pt; }");
    MapSizeLineEdit->setPlaceholderText(tr("请输入布局大小"));
    MapSizeLineEdit->setClearButtonEnabled(true);
    MapSizeLineEdit->setValidator(new QIntValidator(0, 99, this));
    MapSizeLineEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    BoardNumberLabel->setGeometry(50, 270, 200, 60);
    BoardNumberLabel->setStyleSheet("QLabel { font-family: 华文行楷; font-size: 12pt; }");
    BoardNumberLabel->setAlignment(Qt::AlignTop);

    BoardNumberLineEdit->setGeometry(250, 250, 200, 60);
    BoardNumberLineEdit->setStyleSheet("QLineEdit { font-family: Consolas; font-size: 12pt; }");
    BoardNumberLineEdit->setPlaceholderText(tr("请输入炸弹数量"));
    BoardNumberLineEdit->setClearButtonEnabled(true);
    BoardNumberLineEdit->setValidator(new QIntValidator(0, 999, this));
    BoardNumberLineEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    StartGameButton->setGeometry(50, 350, 400, 80);
    StartGameButton->setStyleSheet("QPushButton { font-family: 华文行楷; font-size: 12pt; }");

    QObject::connect(new QShortcut(QKeySequence(Qt::Key_Return), this), &QShortcut::activated, StartGameButton,
                     &QPushButton::click);

    QObject::connect(StartGameButton, &QPushButton::clicked, [this]()
                     {
        MapSize = MapSizeLineEdit->text().toInt();
        BombNumber = BoardNumberLineEdit->text().toInt();

        if (MapSize * MapSize <= BombNumber) {
            QMessageBox::critical(nullptr, "Error", "炸弹太多了！");
            MapSizeLineEdit->setText("20");
            BoardNumberLineEdit->setText("20");
            return;
        }
        
        if (BombNumber == 0) {
            QMessageBox::critical(nullptr, "Error", "炸弹数量不能为0！");
            MapSizeLineEdit->setText("20");
            BoardNumberLineEdit->setText("20");
            return;
        }

        this->close();
        auto *gameInterface = new GameInterface(nullptr, MapSize, BombNumber);
        gameInterface->show(); });
}
