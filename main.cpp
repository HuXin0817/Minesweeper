#include "SettingInterface.h"

#pragma comment(linker, "/subsystem:“windows" / entry : "mainCRTStartup")

int main(int argc, char *argv[])
{
    // ShowWindow(GetForegroundWindow(), SW_HIDE);

    QApplication a(argc, argv);

    auto *setInterface = new SettingInterface(nullptr);
    setInterface->show();

    return QApplication::exec();
}