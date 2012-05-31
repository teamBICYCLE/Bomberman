#ifndef     SCORE_HH
# define    SCORE_HH

# include   <time.h>
# include   <ctime>
# include   <string>
# include   <list>
# include   <fstream>
# include   <iostream>
# include   <sstream>

# define PATH_SCORE "Ressources/Scores/leaderboards.sc"

class Score
{

public:
    Score(void);
    ~Score(void);

public:
    const std::list<std::string> *getScores(void) const;
    void save(int) const;
};

#endif // SCORE_HH
