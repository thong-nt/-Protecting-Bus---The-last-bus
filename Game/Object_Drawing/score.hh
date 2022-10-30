#ifndef SCORE_HH
#define SCORE_HH
/**
  * @file
  * @brief Defines a class that working with score of the player
  */
/**
 * @brief Score is a class, which provides methods that working with score of the player
 *
 * The class provides methods increase or decrease the player's score and return current score.
 *
 */
class Score
{
public:
    /**
     * @brief Default constructor
     * @post set the origin score to 0
     */
    Score();
    /**
     * @brief Function that increase the player's score
     * @pre -
     * @post Increase score private variable.Exception guarantee: nothrow
     */
    void increase();
    /**
     * @brief Function that decrease the player's score
     * @pre -
     * @post Decrease score private variable.Exception guarantee: nothrow
     */
    void decrease();
    /**
     * @brief Function that return the player's current score
     * @pre -
     * @return private variable score's current value
     * @post Exception guarantee: nothrow
     */
    int CurrentScore();

private:
    int score;

};
#endif // SCORE_HH
