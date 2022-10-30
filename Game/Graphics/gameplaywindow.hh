#ifndef GAMEPLAYWINDOW_HH
#define GAMEPLAYWINDOW_HH

/**
  * @file
  * @brief Defines a class that contains methods for handling gameplay window and its functions
  *
  */

#include <QMainWindow>
#include "Graphics/initialize_dialog.hh"
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>
#include "offlinereader.hh"
#include "Object_Drawing/logic.hh"
#include <Object_Drawing/player.hh>
#include <QMediaPlayer>
#include "Object_Drawing/bus.hh"
#include "statistics.hh"

/**
 * @brief GameplayWindow is a class, which provides methods handling gameplay window and its functions
 *
 * The class provides methods that set size of the window, set the picture from external to the background,
 * setting the player's information on the window, moving bus object to next stop, moving the pin of the stop to the next stop
 * playing the background's sound, updte the player's score, update the bus's health if it get hit, checkbox for player who does not want background sound,
 * reading data from the file to assign the bus's route
 *
 */

class Player;
class Logic;
class Statistics;

namespace Ui {
class GameplayWindow;
}

class GameplayWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Default constructor
     * @post initialize the gameplay window with Tampere city map, spawning bus, player and aliens objects, bus health,
     * player's info, player's score, bus's health, pin for stop's destination, setting images for the objects,
     * sending signals when the game commence.
     * @param QWidget *parent
     */
    explicit GameplayWindow(QWidget *parent = nullptr);
    /**
     * @brief Default destructor
     * @post deallocate GameplayWindow object
     */
    virtual ~GameplayWindow();
    /**
     * @brief Set the size of the window
     * @param w: width of the window
     * @param h: heigth of the window
     * @pre -
     * @post Exception guarantee: strong.
     */
    void setSize(int w, int h);
    /**
     * @brief Set the backgroud's picture from external image
     * @param img: QImage object of the picture
     * @pre -
     * @post Exception guarantee: strong.
     */
    void setPicture(QImage &img);
    /**
     * @brief Set the name and ID of the player to Name/ID private variable,
     * @param name: QString object of player's name
     * @param ID: QString object of player's ID
     * @pre -
     * @post Set the label to provided name and ID.Exception guarantee: strong.
     */
    void Recieve_initail_data(QString name, QString ID);
    void Bus_Direction(int a);
    /**
     * @brief if the game ready to start, assign the bus's route from external json file
     * @param yes: true/false
     * @pre -
     * @post Exception guarantee: strong.
     */
    void ready_State(bool yes);

    Statistics *AddrecordStat;

private slots:
    /**
     * @brief function that move the bus to the destination based on the offline data, also move the pin point of next bus stop
     * if the bus reached a stop.
     * @param Cal_time: QTime object
     * @pre -
     * @post Emit the signal to send the current coordinate of the bus. Also move the pin point of next bus stop
     * if the bus reached a stop.Exception guarantee: strong.
     */
    void Moving_Bus(QTime Cal_time);
    /**
     * @brief Set the background's sound
     * @pre -
     * @post Exception guarantee: nothrow.
     */
    void PlayBackground();
    /**
     * @brief Set the player's score and assign it to the coresponding label
     * @pre -
     * @post Exception guarantee: nothrow.
     */
    void updateScore();
    /**
     * @brief Set the bus's health according to how many time it was hit
     * If the bus's health is <=0, the window change to game over , with a notificaton
     * @pre -
     * @post if the bus's health is <=0,stop the timer, save the player's record to the external file,
     * update the window to game over screen.Exception guarantee: nothrow.
     */
    void updateHealth();
    /**
     * @brief Using checkbox to mute/unmute the background sound
     * @param arg1: 0/1 flag
     * @pre -
     * @post if arg1=1 -> mute, if arg1=0 -> unmute. Exception guarantee: strong.
     */
    void on_Mute_checkBox_stateChanged(int arg1);

signals:
    /**
     * @brief signal emits the bus's current coordinate
     * @param x coordinate
     * @param y coordinate
     */
    void sendLocBus(int,int);

private:
    Ui::GameplayWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    int width_ = 1095; //pxls
    int height_ = 592;
    int tick_ = 500; //ms
    QString Stop_name = "";
    int x_loc_bus = 0;
    int y_loc_bus = 0;
    bool newtimer = false;
    std::shared_ptr<CourseSide::OfflineData> offlinedata_;
    QMediaPlayer *back_sound;

    /**
     * @brief assign the bus's route from external json file
     * @param done: true/false
     * @pre -
     * @post Exception guarantee: strong.
     */

    void Assign_Task(bool done);

    /**
     * @brief Function which assign the stop's location to the window's label, also init random number of passenger on the bus
     * assign it to the window's label, if the bus reach a stop, updte new pin point, eject random number of passengers
     * @param stop: object of a stop
     * @pre -
     * @post Stop's name and number of passenger updated in the window's coresponding labels
     * Increase number_Stop.Exception guarantee: nothrow.
     */

    void MovePinStop(std::pair<Interface::Location, std::shared_ptr<CourseSide::Stop> > stop);
    Player * player;
    Logic *New_Game;
    Bus *New_bus;
    int number_Stop = 0;
protected:
    /**
     * @brief Function reset the game and start a new game with a key in the keyboard
     * @param event: QKeyEvent object
     * @pre -
     * @post creating new window, stop the background sound .Exception guarantee: nothrow.
     */
  virtual void  keyPressEvent(QKeyEvent *event);
};

#endif // GAMEPLAYWINDOW_HH
