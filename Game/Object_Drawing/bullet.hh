#ifndef BULLET_H
#define BULLET_H
/**
  * @file
  * @brief Defines a class that contains methods for handling movements of the bullet fired from the player
  * and calculate score if bullet hit the alien
  */
#include <QGraphicsPixmapItem>
#include <QObject>
#include "logic.hh"

/**
 * @brief Bullet is a class, which has methods dealing with movement and behavior of the bullet fired from the player.
 *
 * The class provides signal emitted when the number of bullet is more than 5, when the bullet hit the alien , Score is emitted
 * methods of movement of the bullet object, getting the bus's location to follow/pursuit
 *
 */

class Bullet: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @post Location is set to based on the origin of the player, set image to the alien object,
     * amount of movement in a time interval and start the timer.
     */
    Bullet();
    int dir = 0;
signals:
    void MoreWave(bool);
    /**
     * @brief signal emitted when the bullet hit the alien
     * @param true if the alien is hit, false otherwise
     */
    void Scored(bool);
public slots:
    /**
     * @brief moves the location of the bullet object in straight line from the location of the player.
     * the object is deleted either hitting the alien or goes outside of the map
     * @pre -
     * @post If either detect_hit_bus or outofmap signal emitted, removes the bullet object from the map and emit Score signal for score.
     * based on the direction the gun of the player is pointing, calculate if the coordinate of the bullet exceed the map's dimesion, if true removes the bullet's object.
     * Exception guarantee: strong.
     */
    void move();
private:
    int count_time = 0;
};

#endif // BULLET_H
