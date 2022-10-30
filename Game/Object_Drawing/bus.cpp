#include "bus.hh"
#include "time.h"
#include "random"
#include <QDebug>

Bus::Bus(QObject *parent) : QObject(parent)
{
    setPixmap(QPixmap(":/Image/arrow30x30.png"));
    setTransformOriginPoint(15,15);

    health = 100;
    x_bux = 0;
    y_bux = 0;
    passengers = 0;
}

void Bus::Decrease_Health(int time)
{
    health = health - 10*time;
}

void Bus::Pickup(int num)
{
    int i = 1;
    while(passengers < 46 && i < num)
    {
       passengers++;
       qDebug() << QString::number(passengers);
       i++;
    }
}

void Bus::Des(int num)
{
    int i = 1;
    while(passengers > 0 && i < num)
    {
       passengers--;
       qDebug() << QString::number(passengers);
       i++;
    }
}

int Bus::GenPass()
{
    srand(time(NULL));
    int p = rand() % (5);
    return p;
}

void Bus::Get_location(int x, int y)
{
    x_bux = x;
    y_bux = y;
}
