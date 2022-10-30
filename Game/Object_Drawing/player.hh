#ifndef PLAYER_HH
#define PLAYER_HH
/**
  * @file
  * @brief Defines a class that creat the player's object as airship, its functions and behavior with the alien
  */
#include <QGraphicsPixmapItem>
#include <QObject>
#include "Object_Drawing/logic.hh"
#include <QMediaPlayer>
#include <Object_Drawing/score.hh>

/**
 * @brief Player is a class, which provides methods to function the player á the airship and its behavior to the alien
 *
 * The class provides methods using keyboard to control the airship, calculate score, get number of alien in the window
 * get the bus's coordinate, count number of hit, spawning aliens to the maximum number.
 *
 */

class Player:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @post set the origin starting position of the airship, set image to the airship object,
     * set bul_dir,number_Alien, num_bus_hit to 0, set sound to the gun firing
     */
    Player();
    /**
     * @brief Function that control the player's airship using the keyboard.
     * @param QKeyEvent * event: input key from the keyboard
     * @pre -
     * @post arrow keys set the direction and new coordination of the airship, space fire the bullet
     * space also emits signal when the bullet hit the alien, spawning more aliens and calculate score. Exception guarantee: strong.
     */
    void keyPressEvent(QKeyEvent * event);
    Score *score;
    int num_bus_hit;
    std::string Name;
    std::string ID;

signals:
    /**
     * @brief signal emitted to send the current bus's coordinates.
     * @param x coordinate
     * @param y coordinate
     */
    void sendBusLoc_toAlien(int,int);
    /**
     * @brief signal emitted the current player's score.
     * @param current score.
     */
    void sendScore(int);

public slots:
    /**
     * @brief Function that spawn alien object if number of alien is below 5 and doing communication between signals and slots
     * @pre -
     * @post Creat alien object if number of alien below 5.Sending some signal to slots,
     * that send location of the bus to the alien, when the bus got hit and when the alien is out of map.Exception guarantee: strong.
     */
    void spawn();
    /**
     * @brief Function that set the number of alien
     * @pre -
     * @param num: number of alien
     * @post set the number of alien to private variable number_Alien. Exception guarantee: strong.
     */
    void getNum_Alien(int number);
    /**
     * @brief Function that set the coordinate of the bus
     * @pre -
     * @param x coordinate
     * @param y coordinate
     * @post emitting signal sendBusLoc_toAlien. Exception guarantee: strong.
     */
    void getBus_location(int x, int y);
    /**
     * @brief Function that modifies number of hit to bus and decrease number of aliens
     * @param hit: true or false
     * @pre -
     * @post if true, increase number of hit to bus and decrease number of aliens. Exception guarantee: strong.
     */
    void Count_hit(bool hit);
private slots:
    /**
     * @brief Function that spawn numbers of alien
     * @param check : true/false
     * @pre -
     * @post set the alien number to 3. Exception guarantee: strong.
     */
    void Spawnmore(bool check);
    /**
     * @brief Function update the score of the player
     * @param plus : true/false
     * @pre -
     * @post if plus is true, invoke the increase method for Score class, if plus is false invoke method derease.
     * Emitting signal sendScore. Exception guarantee: strong.
     */
    void UpdateScore(bool plus);

private:
    int bul_dir;
    int number_Alien ;
    QMediaPlayer *bulletsound;
};


#endif // PLAYER_HH
