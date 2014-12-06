/**
    Athlete class designed for Olympic medal winners data set.
*/

#ifndef ATHLETE_H
#define ATHLETE_H

#include <string>
#include <iostream>
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
    int _year;
    std::string _sportType;
    std::string _ceremonyDate;
    Sport(std::string country, int year, std::string sport, std::string date): _country(country), _year(year), _sportType(sport), _ceremonyDate(date) {};
    Sport (): _country(" "), _year(0), _sportType(" "), _ceremonyDate(" ") {};
    Sport (const Sport& oldSport)
    {
        _country = oldSport._country;
        _year = oldSport._year;
        _sportType = oldSport._sportType;
        _ceremonyDate = oldSport._ceremonyDate;
    }
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
    Sport getWinStats() const
    {
        return _winStats;
    }
    void print()
    {
        std::cout<< _name << " from " << _winStats._country<< " for " << _winStats._sportType<<std::endl;
    }
//    std::string printFull()
//    {
//        std::cout << _name << "\nAge " <<_age<<"\n "<<_winStats._country << "\n"<<_winStats._sportType <<"\n"<<_winStats._year<<std::endl;
//        std::cout << "Ceremony Date: "<<_winStats._ceremonyDate;
//        std::cout <<"\nMedals: "<< _medals[0] <<" Gold, "<<_medals[1] <<" Silver, "<<_medals[2] <<" Bronze"<<std::endl;
//    }
    void printFull()
    {
        std::cout << _name << "\nAge " <<_age<<"\n "<<_winStats._country << "\n"<<_winStats._sportType <<"\n"<<_winStats._year<<std::endl;
        std::cout << "Ceremony Date: "<<_winStats._ceremonyDate;
        std::cout <<"\nMedals: "<< _medals[0] <<" Gold, "<<_medals[1] <<" Silver, "<<_medals[2] <<" Bronze"<<std::endl;
    }

    //Constructor and Destructor
    Athlete(const Athlete& oldAthlete)
    {
        _name = oldAthlete.getName();
        _age = oldAthlete.getAge();
        _medals[0] = getMedalCount(Medal::GOLD);
        _medals[1] = getMedalCount(Medal::SILVER);
        _medals[2] = getMedalCount(Medal::BRONZE);
        _winStats = oldAthlete.getWinStats();
    }

    Athlete(std::string name, int age, int medals[3], Sport winStats):
        _name(name),_age(age),_winStats(winStats)
    {
        for (int i=0; i<3; i++)
            _medals[i] = medals[i];
    }

    Athlete(): _name(" "),_age(0) {};

    ~Athlete() {};

    Athlete getAthlete()
    {
        Athlete AthleteCopy(_name,_age,_medals,_winStats);
        return AthleteCopy;
    }
};

#endif // ATHLETE_H
