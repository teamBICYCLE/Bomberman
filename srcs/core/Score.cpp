#include <algorithm>
#include "Score.hh"


Score::Score(void)
    : twitter_(TwitterConnection::getInstance())
{
}

Score::~Score(void)
{
}

bool sortFct(std::string one, std::string two)
{

    if (one.find(SEP_SCORE) != std::string::npos &&
            two.find(SEP_SCORE) != std::string::npos &&
            !one.empty() && !two.empty())
    {
        one = one.substr(one.find_last_of(SEP_SCORE), (one.length() - one.find_last_of(SEP_SCORE)));
        two = two.substr(two.find_last_of(SEP_SCORE), (two.length() - two.find_last_of(SEP_SCORE)));

        std::stringstream ss1(one);
        std::stringstream ss2(two);
        int ione;
        int itwo;

        ss1 >> ione;
        ss2 >> itwo;
        return (ione < itwo);
    }
    return false;
}

bool Score::isHighScore(int score) const
{
    std::list<std::string> lst;
    std::string line;
    std::ifstream infile;
    std::string frontStr;
    int front;

    infile.open(PATH_SCORE);
    if (infile.fail())
        std::cerr << "Unable to open score file !" << std::endl;
    while (!infile.eof())
    {
        getline(infile, line);
        if (!line.empty())
            lst.push_back(line);
    }
    infile.close();
    lst.sort(sortFct);
    lst.reverse();
    if (!lst.empty())
    {
        frontStr = lst.front();
        frontStr = frontStr.substr(frontStr.find_last_of(SEP_SCORE), (frontStr.length() - frontStr.find_last_of(SEP_SCORE)));
        std::stringstream ss(frontStr);
        ss >> front;
        if (score > front || lst.size() == 1)
            return true;
    }
    return false;
}

void Score::save(int score) const
{
    std::ofstream	leaderboards(PATH_SCORE, std::ios::app);
    time_t          t;
    char            buff[20];

    if (leaderboards.good() && score > 0)
    {
        t = time(NULL);
        strftime(buff, 20, "%d/%m %H:%M", localtime(&t));
        leaderboards << buff << SEP_SCORE << score << std::endl;
        leaderboards.close();
    }
    if (Score::isHighScore(score))
    {
        std::cout << "TWEEEEEET" << std::endl;
        twitter_->sendTweet(score);
    }
}

std::list<std::string> *Score::getScores(void) const
{
    std::list<std::string> *ret = new std::list<std::string>;
    std::string line;
    std::ifstream infile;

    infile.open(PATH_SCORE);
    if (!infile.fail())
    {
        while (!infile.eof())
        {
            getline(infile, line);
            if (!line.empty() &&
                    line.find(SEP_SCORE) != std::string::npos &&
                    line.find(SEP_SCORE) + SEP_LEN < line.length())
                ret->push_back(line);
        }
        infile.close();
        ret->sort(sortFct);
        ret->reverse();
    }
    return ret;
}

