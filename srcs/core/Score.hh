#ifndef     SCORE_HH
# define    SCORE_HH

# include   <time.h>
# include   <ctime>
# include   <string>
# include   <list>
# include   <fstream>
# include   <iostream>
# include   <sstream>
#include    "TwitterConnection.hh"

# define PATH_SCORE "Ressources/Scores/leaderboards.sc"
# define SEP_SCORE " - "

class Score
{

public:
    Score(void);
    ~Score(void);

public:
    std::list<std::string> *getScores(void) const;
    void save(int) const;

private:
    bool isHighScore(int score) const;

private:
    TwitterConnection *twitter_;
};

#endif // SCORE_HH
