#include <algorithm>
#include "Score.hh"

Score::Score(void)
{
}

Score::~Score(void)
{
}

bool sortFct(std::string one, std::string two)
{
    one = one.substr(one.find_last_of(" - "), (one.length() - one.find_last_of(" - ")));
    two = one.substr(two.find_last_of(" - "), (two.length() - two.find_last_of(" - ")));

    std::stringstream ss1(one);
    std::stringstream ss2(two);
    int ione;
    int itwo;

    ss1 >> ione;
    ss2 >> itwo;
    return (ione < itwo);
}

void Score::save(int score) const
{
    std::ofstream	leaderboards(PATH_SCORE, std::ios::app);
    time_t          t;
    char            buff[20];

    if (leaderboards.good())
    {
        t = time(NULL);
        strftime(buff, 20, "%d/%m %H:%M", localtime(&t));
        leaderboards << buff << " : " << score << std::endl;
        leaderboards.close();
    }
}

const std::list<std::string> *Score::getScores(void) const
{
    std::list<std::string> *ret = new std::list<std::string>;
    std::string line;
    std::ifstream infile;
    int i = 0;

    infile.open(PATH_SCORE);
    if (infile.fail())
        std::cerr << "Unable to open score file !" << std::endl;
    while (!infile.eof() || i < 10)
    {
        getline(infile, line);
        ret->push_back(line);
        ++i;
    }
    infile.close();
    ret->sort(sortFct);
    return ret;
}

