#ifndef LOGIC_HH
#define LOGIC_HH

/**
  * @file
  * @brief Defines a class that contains ultility methods helping define the game's logic
  */

#include <QtCore>
#include <QTime>
#include <QTimer>
#include "graphics/simplemainwindow.hh"
#include <QWidget>
#include "offlinereader.hh"
#include "alien.hh"
#include "bullet.hh"
#include "player.hh"

/**
 * @brief Logic is a class, which has ultility methods helping define the game's logic
 *
 * The class provides methods reading data from json file, find route to destination for the bus,
 * timer calculation, generate number of aliens,
 *
 */

class Logic: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @post -
     */
    Logic();
    std::shared_ptr<CourseSide::OfflineData> offlinedata_;


    void readData();
    void FindRoute();
signals:
    /**
     * @brief signal emitted to send the current QTime object
     * @param QTime object
     */
    void sendTimer(QTime time_);
    /**
     * @brief signal emitted to send the number of aliens
     * @param number:number of aliens.
     */
    void sendNumAlien(int number);
public slots:
    /**
     * @brief Function that served as a timer, increase the seconds,reset if seconds reach 60 and increase minute, after 60 mins, increase hour
     * @pre -
     * @post setting min_ and sec_ private variable and emitting signal sendTimer.Exception guarantee: strong.
     */
    void Calculate_time();
    /**
     * @brief Function that add number of aliens in the window if number of aliens<5
     * @pre -
     * @post setting number_alien private variable and emitting signal sendNumAlien.Exception guarantee: strong.
     */
    void control_Numb_Alien();

private:
    void Check_time();
    int min_ = 0;
    int sec_ = 0;
    QTime time_;
    int number_alien = 0;
};


#endif // LOGIC_TEAMSIDE_HH
