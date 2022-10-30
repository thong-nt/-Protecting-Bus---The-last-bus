#ifndef STATISTICS_HH
#define STATISTICS_HH

/**
  * @file
  * @brief Defines a class that working player's information and the database contain it
  */

#include <string>
#include <QTime>
#include <map>

/**
 * @brief Statistic is a class, which provides methods that working player's information and the database contain it.
 *
 * The class provides methods reading player's info database, print out player's score board, obtain player's info from input and save it to the dabase
 * sorting player's score.
 *
 */

struct Player_Statistics
{
    std::string ID;
    std::string Name;
    int score;
};

class Statistics
{
public:
    /**
     * @brief Default constructor
     * @post read the database.txt file and sort its content
     */
    Statistics();
    /**
     * @brief Default destructor
     * @post deallocate Player_Statistics object
     */
    ~Statistics();
    /**
     * @brief Function that print the player's score leaderboard
     * @pre -
     * @post Print the information inside leader map.Exception guarantee: nothrow
     */
    void print();
    /**
     * @brief Function that store the player's information to listplayer map.
     * @param Nane: name of the player
     * @param ID : player's ID
     * @param score: player's score
     * @pre -
     * @post if the player's info is found in the listplayer map, update its new score
     * otherwise add the info to listplayer map.Exception guarantee: nothrow
     */
    void Add_Stat(std::string Name, std::string ID, int score);

    std::map<int,Player_Statistics*, std::greater<int>> leaders;
    /**
     * @brief Function that write the player's data to database
     * @pre -
     * @post Open database file in write mode and write in the file with format: ID;name;score.Exception guarantee: strong
     */
    void save_Database();
    std::map<std::string, Player_Statistics*> listplayer;
private:

    /**
     * @brief Function that read the data from database file.
     * @param QString fileName: file's name to be openned.
     * @pre -
     * @post seperate the read data with delimiter ";" and assign the data corresponding to listplayer map.
     *  Exception guarantee: strong.
     */
    void read_Database(QString fileName);
    /**
     * @brief Function that sort the player's score
     * @pre -
     * @post Append the data from listplayer map to leader map.Exception guarantee: nothrow
     */
    void Sort();
};

#endif // STATISTICS_HH
