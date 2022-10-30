#ifndef ALIEN_HH
#define ALIEN_HH
/**
  * @file
  * @brief Defines a class that contains methods for handling movements and behaviors of the alien
  *
  */
#include <QtCore>
#include <QGraphicsPixmapItem>
#include "Graphics/gameplaywindow.hh"
#include "Object_Drawing/logic.hh"


/**
 * @brief Alien is a class, which has methods dealing with movement and behavior of alien object.
 *
 * The class provides signal emitted when the alien hit the bus, the alien is out of the map,
 * methods of movement of the alien object, getting the bus's location to follow/pursuit
 *
 */

class Alien: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @post Location is set to (random% 1095, random % 592), set image to the alien object,
     * amount of movement in a time interval and start the timer.
     */
    Alien();

signals:
    /**
     * @brief signal emitted when the alien hit the bus
     * @param true if the bus is hit, false otherwise
     */
    void detect_hit_bus(bool);
    /**
     * @brief signal emitted when alien is outside of the map's dimension
     * @param true if object's coordinate exceed either x/y coordinate of the map, false otherwise
     */
    void outofmap(bool);

public slots:
    /**
     * @brief moves the location of the alien object to a new coordinate in map grid.
     * @pre -
     * @post Location is updated. If either detect_hit_bus or outofmap signal emitted, removes the alien object from the map.
     * Exception guarantee: strong.
     */
    void move();
    /**
     * @brief Function that gettingthe bus's location in certain map coordinate by setting x_bus/y_bus to current x/y of the bus.
     * @param x coordinate of the location of the bus
     * @param y coordinate of the location of the buss
     * @pre -
     * @post Location is given. Exception guarantee: strong.
     */
    void getBus_location(int x, int y);

private:
    int x_bus = 0;
    int y_bus = 0;
};

#endif // ALIEN_HH
