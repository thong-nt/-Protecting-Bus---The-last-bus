#include "player.hh"
#include "bullet.hh"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "alien.hh"

Player::Player():QObject(), QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/Image/aircratf.png"));
    setTransformOriginPoint(15,15);
    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/Media/shooting_shound.mp3"));
    bul_dir = 0;
    number_Alien = 0;
    num_bus_hit = 0;
    score = new Score();
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
        {
            bul_dir = 270;
            setPos(x()-10,y());
            setRotation(270);
        }
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 32 < 1092)
        {
            bul_dir = 90;
            setRotation(90);
            setPos(x()+10,y());
        }
    }
    else if (event->key() == Qt::Key_Up){
        if (pos().y() > 0)
        {
            setRotation(0);
            bul_dir = 0;
            setPos(x(),y()-10);
        }
    }
    else if (event->key() == Qt::Key_Down){
        if (pos().y() + 38 < 592)
        {
            bul_dir = 180;
            setRotation(180);
            setPos(x(),y()+10);
        }
    }
    else if (event->key() == Qt::Key_Space){
        Bullet * bullet = new Bullet();
        bullet->dir = bul_dir;
        if(bul_dir == 0)
            bullet->setPos(x()+4,y()-30);
        else if (bul_dir == 180)
            bullet->setPos(x()+4,y()+30);
        else if (bul_dir == 270)
            bullet->setPos(x()-5,y()+5);
        else if (bul_dir == 90)
            bullet->setPos(x()+5,y()+5);
        scene()->addItem(bullet);
        if(bulletsound->state() == QMediaPlayer::PlayingState)
            bulletsound->setPosition(0);
        else if (bulletsound->state() == QMediaPlayer::StoppedState)
            bulletsound->play();
        connect(bullet,&Bullet::MoreWave,this,&Player::Spawnmore);
        connect(bullet,&Bullet::Scored,this,&Player::UpdateScore);
    }
}

void Player::spawn()
{
    if(number_Alien < 5)
    {
        Alien * enemy = new Alien();
        scene()->addItem(enemy);
        connect(this,&Player::sendBusLoc_toAlien,enemy,&Alien::getBus_location);
        connect(enemy,&Alien::detect_hit_bus,this,&Player::Count_hit);
        connect(enemy,&Alien::outofmap,this,&Player::Spawnmore);
    }
}

void Player::getNum_Alien(int number)
{
    number_Alien = number;
}

void Player::Spawnmore(bool check)
{
    if(check == true)
    {
        number_Alien = 3;
    }
}

void Player::UpdateScore(bool plus)
{
    if(plus == true)
        score->increase();
    else
        score->decrease();
    emit sendScore(score->CurrentScore());
}

void Player::getBus_location(int x, int y)
{
    emit sendBusLoc_toAlien(x,y);
}

void Player::Count_hit(bool hit)
{
    if (hit == true)
    {
        num_bus_hit++;
        number_Alien--;
        qDebug() << "true       " << num_bus_hit;
    }
}
