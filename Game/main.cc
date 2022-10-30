#include <QApplication>
#include "Graphics/startwindow.hh"
#include "Graphics/gameplaywindow.hh"

using namespace CourseSide;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    StartWindow *StartMenu = new StartWindow();
    StartMenu->show();

    return a.exec();
}
