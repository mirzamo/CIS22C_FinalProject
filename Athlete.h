/**
    Athlete class designed for Olympic medal winners data set.
*/

#ifndef ATHLETE_H
#define ATHLETE_H

#include <string>
/**
    Enum used for clear access to correct entry in array of medals inside Athlete class.
*/
enum class Medal
{
    GOLD, SILVER, BRONZE
};

/**
    Struct sport contains public variables pertinent to specific sport that athlete undertook.
    Fields are public for easier access.
*/
struct Sport
{
    std::string _country;
    int year;
    std::string _sportType;
    std::string _ceremonyDate;
    Sport(std::string country, int year, std::string sport, std::string date): _country(country), _sportType(sport), _ceremonyDate(date) {};
};

/**
    Class Athlete encompasses each one of provided data set.
*/

class Athlete
{
private:
    std::string _name;
    int _age;
    int _medals[3];
    Sport _winStats;
public:
    std::string getName() const
    {
        return _name;
    }
    int getAge() const
    {
        return _age;
    }
    int getMedalCount(Medal mType) const
    {
        return _medals[static_cast<int>(mType)];
    }
    Sport& getWinStats()
    {
        return _winStats;
    }
    //Constructor and Destructor
    Athlete(std::string name, int age, int medals[3], Sport winStats):
        _name(name),_age(age),_winStats(winStats)
    {
        for (int i=0; i<3; i++)
            _medals[i] = medals[i];
    }
    ~Athlete() {};

    // Overload Operators
    bool operator==(const Athlete& rhs) const
    {
        return (_name == rhs.getName());
    }

    bool operator>(const Athlete& rhs) const
    {
        return (_name > rhs.getName());
    }
};

#endif // ATHLETE_H
