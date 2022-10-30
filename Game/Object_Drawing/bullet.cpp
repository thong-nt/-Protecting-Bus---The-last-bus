#include "bullet.hh"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "alien.hh"
#include <QDebug>
#include "player.hh"
#include "Object_Drawing/logic.hh"
#include <Graphics/gameplaywindow.hh>

extern GameplayWindow * Gameplay;

Bullet::Bullet(): QObject(), QGraphicsPixmapItem(){
    setPixmap(QPixmap(":/Image/bullet.png"));
    setTransformOriginPoint(10,10);

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Bullet::move(){
    count_time++;
    if (count_time == 5)
    {
       emit MoreWave(true);
    }
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        auto& r = *colliding_items[i];
        if (typeid(r) == typeid(Alien)){
            emit Scored(true);
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }
    }
        switch (dir) {
            case 0:
            {
                setRotation(0);
                setPos(x(),y()-10);
                if (pos().y() < 0){
                    scene()->removeItem(this);
                    delete this;
                }
                break;
            }
            case 90:
            {
                setRotation(90);
                setPos(x()+10,y());
                if (pos().x() > 1092){
                    scene()->removeItem(this);
                    delete this;
                }
                break;
            }
            case 180:
            {
                setRotation(180);
                setPos(x(),y()+10);
                if (pos().y() > 592){
                    scene()->removeItem(this);
                    delete this;
                }
                break;
            }
            case 270:
            {
                setRotation(270);
                setPos(x()-10,y());
                if (pos().x() < 0){
                    scene()->removeItem(this);
                    delete this;
                }
                break;
            }
        }
}

