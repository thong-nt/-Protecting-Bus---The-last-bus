#include "gameplaywindow.hh"
#include "ui_gameplaywindow.h"
#include "Graphics/initialize_dialog.hh"
#include "core/location.hh"
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <string>
#include "Object_Drawing/player.hh"
#include <QPixmap>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include "startwindow.hh"

const int PADDING = 10;

GameplayWindow::GameplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameplayWindow)
{
    ui->setupUi(this);
    ui->gameView->setFixedSize(width_, height_);
    ui->centralwidget->setFixedSize(width_, height_ + PADDING+180);

    QPixmap bkgnd(":/Image/dark_Flaze.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

      //Driver Info
    ui->Driver_Name_Label->move(20,height_+ PADDING*4);
    ui->Driver_Name_Label->setStyleSheet("QLabel {background-color : none; color: white;}");
    ui->ID_Label->move(20,height_+ PADDING*6);
    ui->ID_Label->setStyleSheet("QLabel {background-color : none; color: white;}");
    ui->Score_Lable->move(20,height_+ PADDING*8);
    ui->Score_Lable->setStyleSheet("QLabel {background-color : none; color: white;}");
    ui->Bus_No_Label->move(20,height_+ PADDING*10);
    ui->Bus_No_Label->setStyleSheet("QLabel {background-color : none; color: white;}");
    ui->Route_Label->move(20,height_+ PADDING*12);
    ui->Route_Label->setStyleSheet("QLabel {background-color : none; color: white;}");
    ui->HealthB_LB->move(20,height_+ PADDING*16);
    ui->HealthB_LB->setStyleSheet("QLabel {background-color : none; color: white;}");
    ui->Bus_HBar->move(100,height_+ PADDING*16);
    ui->Bus_HBar->setStyleSheet("QProgressBar {border: 2px solid grey;border-radius: 5px;text-align: center;}\nQProgressBar::chunk {background-color: #05B8CC; width: 20px;}");
    ui->Mute_checkBox->setStyleSheet("QCheckBox {border: none; color: white;}");
    ui->Mute_checkBox->move(1027,height_+ PADDING*13);

    ui->Stop_Name_LB->move(920,height_+ PADDING*4);
    ui->Stop_Name_LB->setStyleSheet("QLabel {background-color : none; color: white;}");
    ui->PassengerStop->move(920,height_+ PADDING*6);
    ui->PassengerStop->setStyleSheet("QLabel {background-color : none; color: white;}");
    ui->Passenger_BusLB->move(920,height_+ PADDING*8);
    ui->Passenger_BusLB->setStyleSheet("QLabel {background-color : none; color: white;}");

    QPixmap pixpin(":/Image/Pin_stop.png");
    ui->stop_pin_but->setPixmap(pixpin.scaled(ui->stop_pin_but->width(),ui->stop_pin_but->height(),Qt::KeepAspectRatio));

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);

    player = new Player();
    map->addItem(player);

    New_bus = new Bus();
    map->addItem(New_bus);

    back_sound = new QMediaPlayer();
    back_sound->setMedia(QUrl("qrc:/Media/ingame.mp3"));
    back_sound->play();

    timer = new QTimer(this);
    New_Game = new Logic();
    connect(timer, &QTimer::timeout, this, &GameplayWindow::PlayBackground);
    connect(timer, &QTimer::timeout, New_Game, &Logic::Calculate_time);
    connect(New_Game, &Logic::sendTimer, this, &GameplayWindow::Moving_Bus);
    connect(timer,&QTimer::timeout,player,&Player::spawn);
    connect(timer, &QTimer::timeout, New_Game, &Logic::control_Numb_Alien);
    connect(New_Game, &Logic::sendNumAlien, player, &Player::getNum_Alien);
    connect(this,&GameplayWindow::sendLocBus,player,&Player::getBus_location);
    connect(timer, &QTimer::timeout, this, &GameplayWindow::updateScore);
    connect(timer, &QTimer::timeout, this, &GameplayWindow::updateHealth);

}

GameplayWindow::~GameplayWindow()
{
    delete ui;
}

void GameplayWindow::setSize(int w, int h)
{
    width_ = w;
    height_ = h;
}

void GameplayWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}

void GameplayWindow::Recieve_initail_data(QString name, QString ID)
{
    player->Name = name.toStdString();
    player->ID = ID.toStdString();
    ui->Driver_Name_Label->setText(ui->Driver_Name_Label->text()+ " " +name);
    ui->ID_Label->setText(ui->ID_Label->text()+ " " + ID);
}

void GameplayWindow::ready_State(bool yes)
{
    if (yes == true)
    {
        offlinedata_ = std::make_shared<CourseSide::OfflineData>();
        offlinedata_->buses.empty();
        offlinedata_->stops.empty();

        GameplayWindow::Assign_Task(false);
    }
}

void GameplayWindow::Moving_Bus(QTime Cal_time)
{
    if(offlinedata_->buses.front()->timeRoute2.find(Cal_time) != offlinedata_->buses.front()->timeRoute2.end())
    {
        qDebug() << "Match time";
        New_bus->x_bux = offlinedata_->buses.front()->timeRoute2.find(Cal_time)->second.first.giveX()*2.3324;
        New_bus->y_bux = offlinedata_->buses.front()->timeRoute2.find(Cal_time)->second.first.giveY();
        New_bus->setPos(New_bus->x_bux,New_bus->y_bux);
        emit sendLocBus(New_bus->x_bux,New_bus->y_bux);

        if( offlinedata_->buses.front()->timeRoute2.find(Cal_time)->second.second != nullptr)
        {
            GameplayWindow::MovePinStop(offlinedata_->buses.front()->timeRoute2.find(Cal_time)->second);
        }
    }
    else
    {
        qDebug() << "Not Match time          " << Cal_time;
        emit sendLocBus(New_bus->x_bux,New_bus->y_bux);
    }
}

void GameplayWindow::PlayBackground()
{
    if (back_sound->state() == QMediaPlayer::StoppedState)
        back_sound->play();
}

void GameplayWindow::updateScore()
{
    std::string s = "Score: " + std::to_string(player->score->CurrentScore());
    ui->Score_Lable->setText(QString::fromStdString(s));
}

void GameplayWindow::updateHealth()
{
    if(New_bus->health > 0)
    {
        New_bus->Decrease_Health(player->num_bus_hit);
        qDebug() << "bus is hit";
        ui->Bus_HBar->setValue(New_bus->health);
        player->num_bus_hit = 0;
    }
    if (New_bus->health <= 0)
    {
        timer->stop();
        AddrecordStat->Add_Stat(player->Name,player->ID,player->score->CurrentScore());
        AddrecordStat->save_Database();
        map->clear();
        map->setBackgroundBrush(Qt::black);
        ui->stop_pin_but->setVisible(true);
        QGraphicsTextItem *text = new QGraphicsTextItem();
        text->setPlainText(QString("DEFEAT - BUS HAS BEEN DESTROYED"));
        text->setDefaultTextColor(Qt::red);
        text->setFont(QFont("times",40));
        text->setPos(width_/4-200, height_/2-30);
        map->addItem(text);
        QGraphicsTextItem *text2 = new QGraphicsTextItem();
        text2->setPlainText(QString("*Press any key to continue*"));
        text2->setDefaultTextColor(Qt::red);
        text2->setFont(QFont("times",20));
        text2->setPos(width_/4+120, height_/2+30);
        map->addItem(text2);

    }
}

void GameplayWindow::Assign_Task(bool done)
{
    if (done == false)
    {
        New_Game->readData();
        New_Game->FindRoute();
        offlinedata_ = New_Game->offlinedata_;

        QString routeId = QString::fromStdString(std::to_string(offlinedata_->buses.front()->routeId));
        QString routeName = QString::fromStdString(offlinedata_->buses.front()->routeName);
        QString routeNumber = QString::fromStdString(std::to_string(offlinedata_->buses.front()->routeNumber));
        QString route = QString::fromStdString(offlinedata_->buses.front()->routeName);
        QString time =  offlinedata_->buses.front()->schedule.front().toString();

        //qDebug() << routeId + " : " + routeName + " : " + routeNumber + " : " + route + " : " + time;

        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this, "Your task: ", "Bus ID: " + routeId + "\n" "Bus Number: " + routeNumber + "\n" "Route: " + routeName,
                                        QMessageBox::Ok);
        if (reply == QMessageBox::Ok)
        {
            ui->Bus_No_Label->setText(ui->Bus_No_Label->text()+ " " +routeNumber);
            ui->Route_Label->setText(ui->Route_Label->text() + routeName);
            Stop_name = offlinedata_->buses.front()->timeRoute2.begin()->second.second->getName();

            GameplayWindow::MovePinStop(offlinedata_->buses.front()->timeRoute2.begin()->second);

            New_bus->x_bux = offlinedata_->buses.front()->timeRoute2.begin()->second.first.giveX()*2.3324;
            New_bus->y_bux = offlinedata_->buses.front()->timeRoute2.begin()->second.first.giveY();
            New_bus->setPos(New_bus->x_bux,New_bus->y_bux);

            player->setFlag(QGraphicsItem::ItemIsFocusable);
            player->setFocus();
            player->setPos(width_/2,height_/2);
            if (newtimer == false)
            {
                timer->start(1000);
                newtimer = true;
            }
            else
            {
                if (!timer->isActive())
                    timer->start();
            }
        }
    }
}

void GameplayWindow::MovePinStop(std::pair<Interface::Location, std::shared_ptr<CourseSide::Stop> > stop)
{
    ui->stop_pin_but->move(stop.first.giveX()*2.3324+10,stop.first.giveY());
    ui->Stop_Name_LB->setText("Stop Name: " + stop.second->getName());

    int on_Bus = New_bus->GenPass();
    New_bus->Pickup(on_Bus);
    ui->Passenger_BusLB->setText("Passenger on Bus: " + QString::number(New_bus->passengers));

    if (number_Stop != 0)
    {
        int leave_Bus = New_bus->GenPass();
        New_bus->Des(leave_Bus);
        ui->PassengerStop->setText("Passenger at Stop: " + QString::number(leave_Bus));
    }
    number_Stop++;
}

void GameplayWindow::keyPressEvent(QKeyEvent *event)
{
    if (New_bus->health == 0 && event != nullptr)
    {
        StartWindow *newone = new StartWindow();
        this->close();
        back_sound->stop();
        newone->show();
    }
}

void GameplayWindow::on_Mute_checkBox_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        back_sound->setMuted(false);
    }else if (arg1 == 2)
    {
        back_sound->setMuted(true);
    }
}
