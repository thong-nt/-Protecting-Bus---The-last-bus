#include "alien.hh"
#include "bus.hh"


Alien::Alien(): QObject(), QGraphicsPixmapItem()
{
    int random_number_x = rand() % 1095;
    int random_number_y = rand() % 592;
    setPos(random_number_x,random_number_y);

    setPixmap(QPixmap(":/Image/UFO.png"));
    setTransformOriginPoint(30,30);

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Alien::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        auto& r = *colliding_items[i];
        if (typeid(r) == typeid(Bus)){
            emit detect_hit_bus(true);
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    if(x() < x_bus && y() < y_bus)
    {
        setPos(x()+5,y()+5);
    }
    else if(x() > x_bus && y() < y_bus)
    {
        setPos(x()-5,y()+5);
    }
    else if(x() < x_bus && y() > y_bus)
    {
        setPos(x()+5,y()-5);
    }
    else if(x() > x_bus && y() > y_bus)
    {
        setPos(x()-5,y()-5);
    }
    else if(x() == x_bus && y() > y_bus)
    {
        setPos(x(),y()-5);
    }else if(x() == x_bus && y() < y_bus)
    {
        setPos(x(),y()+5);
    }
    else if(x() < x_bus && y() == y_bus)
    {
        setPos(x()+5,y());
    }else if(x() > x_bus && y() == y_bus)
    {
        setPos(x()-5,y());
    }

    if (pos().y() < 0 || pos().y() > 1095 || pos().x() < 0 || pos().y() > 592){
        scene()->removeItem(this);
        emit outofmap(true);
        delete this;
    }
}

void Alien::getBus_location(int x, int y)
{
    x_bus = x;
    y_bus = y;
}
