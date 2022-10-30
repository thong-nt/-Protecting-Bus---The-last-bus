#ifndef BUS_HH
#define BUS_HH

/**
  * @file
  * @brief Defines the class that handling the status of the bus.
  *
  */

#include <QObject>
#include <QGraphicsPixmapItem>
/**
 * @brief Bus is a class, which has methods dealing with the status of the bus.
 *
 * The class provides methods of amount of health the bus is lost when get hit, receiving and releasing passengers
 * its current coordinate on the map
 *
 */
class Bus : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @post Init the default location of the bus, set image to the bus object,
     * set health of the bus to 100, its number of passenger to 0.
     */
    explicit Bus(QObject *parent = nullptr);
    int health;
    /**
     * @brief Function that decrease the bus's health based on how many times it is hit
     * @param time: number of times the bus get hit
     * @pre -
     * @post set the bus's health based on number of time it is hit (-10 per hit) .Exception guarantee: strong.
     */
    void Decrease_Health(int time);

    int passengers;
    /**
     * @brief Function that increase number of passengers in the bus, if the current number of passengers in the bus is lower than limit (46)
     * @param num: number of passengers the bus is going to take
     * @pre -
     * @post set the bus's passengers number. Exception guarantee: strong.
     */
    void Pickup(int num);
    /**
     * @brief Function that decrease the bus's passengers number ,if the current number of passengers in the bus is >0
     * @param num: number of passengers the bus is going to eject
     * @pre -
     * @post set the bus's passengers number. Exception guarantee: strong.
     */
    void Des(int num);
    /**
     * @brief Function that generate random number
     * @pre -
     * @return return random generated number.
     * @post Exception guarantee: nothrow.
     */
    int GenPass();

    int x_bux;
    int y_bux;
    /**
     * @brief Function that gettingthe bus's location in certain map coordinate by setting x_bus/y_bus to current x/y of the bus.
     * @param x coordinate of the location of the bus
     * @param y coordinate of the location of the buss
     * @pre -
     * @post Location is given. Exception guarantee: nothrow.
     */
    void Get_location(int x, int y);

signals:


};

#endif // BUS_HH
