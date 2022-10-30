#include "score.hh"

Score::Score()
{
    score = 0;
}

void Score::increase()
{
    score++;
}

void Score::decrease()
{
    score--;
}

int Score::CurrentScore()
{
    return score;
}
