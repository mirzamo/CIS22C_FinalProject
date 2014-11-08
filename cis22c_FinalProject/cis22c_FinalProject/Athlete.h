#ifndef ATHLETE_H
#define ATHLETE_H

#include <string>
enum class Medal {GOLD, SILVER, BRONZE};

struct Sport
{
    std::string _country;
    std::string _sportType;
    std::string _ceremonyDate;
    Sport(std::string country, std::string sport, std::string date): _country(country), _sportType(sport), _ceremonyDate(date){};
};

class Athlete
{
private:
    std::string _name;
    int _age;
    Medal[3] _medals;
    Sport _winningStats;
public:
    std::string getName();
    int getAge();
    int getMedalCount(Medal);
    getWinningStats(Sport);
    Athlete(name,age,medals,winningStats): _name(name),_age(age),_medals(medals),_winningStats(winningStats) {};
    ~Athlete(){};
};

#endif // ATHLETE_H
