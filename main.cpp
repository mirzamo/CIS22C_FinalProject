/**
    CIS22C : Group #9 Final Project
    Dataset used: Olympic Medal Winners from http://www.tableausoftware.com/public/community/sample-data-sets

    Columns of data in input file have this order:
    Athlete-Age-Country-Year-Closing Ceremony Date-Sport-Gold Medals-Silver Medals-Bronze Medals

    NOTES FOR THE GROUP IF YOU HAVE ANY/ DESCRIPTION FOR WHAT YOURE DOING:

    Elena : Athlete, testing functions done
    Misha:
    Mahsa: I/O functions done
    Kelly:

*/

#include <fstream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include "Athlete.h"
#include "validation.h"
#include <vector>
#include <string>

using namespace std;

const string FNAME = "OlympicAthletes.txt";
bool readData(vector<Athlete*>*, int&);
void testPrint(const vector<Athlete*>*);
void parseInput(string&, string&, string&, string&, string&, int&, int*, int&);
void processCommand(); // input will be hash table and BST
bool isPrime (int);
int hashSize(int);

int main()
{
    vector<Athlete*>* testVec = new vector<Athlete*>;
    int hashSize =0;
    readData(testVec, hashSize);
    //testPrint(testVec);
    processCommand();
    delete testVec;
    return 0;
}

/**
    Returns true if able to read (non-corrupt) file, else returns false.
    If able to read file, it dynamically allocates Athletes in memory.
    It fills all data structures with pointers to these Athletes.
*/
bool readData(vector<Athlete*>* testVec, int& hashSi)
{
    ifstream fileHandle;
    fileHandle.open(FNAME);

    bool ableToPopulate = fileHandle.good();

    if (ableToPopulate)
    {
        string line =" ", name = " ", country = " ", sport = " ", date = " ";
        int age =0, year=0, numObjects =0;
        int medals[3] = {0};
        while (getline(fileHandle, line))
        {
            parseInput(line,name,country,sport,date,age,medals,year);
            Sport winStats(country,year,sport,date);
            Athlete* athlete = new Athlete(name, age, medals, winStats);
            testVec->push_back(athlete);
            numObjects++;
        }
        fileHandle.close();
        hashSi = hashSize(numObjects);
    }
    else
        printErrorMsg(Error::BAD_IFILE);
    return ableToPopulate;
}

/**
    Function to test that code to build Athlete structures works correctly.
    Prints out certain dynamically allocated Athlete object fields.
*/

void testPrint(const vector<Athlete*>* testVec)
{
    int si = testVec->size();
    for (int i=0; i < si ; i++)
    {
        cout<< testVec->at(i)->getName()<<"\t" <<  testVec->at(i)->getAge()<<"\t" <<
        testVec->at(i)->getMedalCount(Medal::BRONZE)<<"\t" <<
        testVec->at(i)->getWinStats()._country << endl;
    }

}

/**
    Function that cuts up inputted line read from file into chunks and changes correct values by reference.
*/

void parseInput(string& line, string& name, string& country, string& sport, string& date, int& age, int* medals, int& year)
{
    unsigned int cut = line.find_first_of("1234567890");
    name = line.substr(0,cut-1);
    line = line.substr(cut);
    age = stoi(line.substr(0,3));
    line = line.substr(3);
    cut = line.find_first_of("1234567890");
    country = line.substr(0,cut-1);
    line = line.substr(cut);
    year = stoi(line.substr(0,5));
    line = line.substr(5);
    cut = line.find_first_not_of("1234567890/");
    sport = line.substr(0,cut);
    line = line.substr(cut+1);
    cut = line.find_first_of("1234567890");
    line = line.substr(cut);
    medals[0] = stoi(line.substr(0,1));
    medals[1] = stoi(line.substr(2,3));
    medals[2] = stoi(line.substr(4,5));
}

/**
    Prints out error message based on an error message table.
*/
void printErrorMsg(Error msg)
{
    cout << ErrorTable[static_cast<int>(msg)] << endl;
}

/**
    Displays the menu for user.
*/
void menu()
{
    int w1 = 10, w2 = 10;
    cout<< endl;
    cout << setw(w1) << left << "0: " << setw(w2) << left << "Display data set info" << endl;
    cout << setw(w1) << left << "1: " << setw(w2) << left << "Insert new entry" << endl;
    cout << setw(w1) << left << "2: " <<  setw(w2) << left << "Delete an entry"<< endl;
    cout << setw(w1) << left << "3: " <<  setw(w2) << left << "Display entries in an indented list"<< endl;
    cout << setw(w1) << left << "4: " <<  setw(w2) << left << "Search for an entry"<< endl;
    cout << setw(w1) << left << "5: " <<  setw(w2) << left << "Show hash table statistics"<< endl;
    cout << setw(w1) << left << "6: " <<  setw(w2) << left << "Quit"<<endl;
}

/**
    Validated whether user input is valid.
*/
bool validChoice(string choice)
{
    string allowable = "123456";
    if (choice.size()==1 && (allowable.find(toupper(choice[0])) != std::string::npos))
        return true;
    else
    {
        printErrorMsg(Error::BAD_INPUT);
        menu();
        return false;
    }
}

/**
    Processes user command for the data entries.
*/
void processCommand() // input will be hash table and BST
{
    //create hash function pointer here

    menu();
    bool inProgress = true;
    while (inProgress)
    {
        string choice;
        do
        {
            cout<<" >> ";
            getline(cin, choice);
        }
        while (!validChoice(choice));
        switch (toupper(choice[0]))
        {
        case '0':
        {
            // display dataset info
            break;
        }
        case '1':
        {
            // Insert new entry
            break;
        }
        case '2':
        {
            // delete an entry
            break;
        }
        case '3':
        {
            // Display entries in an indented list
            break;
        }
        case '4':
        {
            // Search for an entry
            break;
        }
        case '5':
            {
                // Show hash table statistics
                break;
            }
        case '6':
            inProgress = false;
        }

    }
}


//****************
// Deterine hash size
//****************
int hashSize(int numAthletes)
{
    int hashSize = numAthletes * 2;
    for (hashSize + 1 ; !isPrime(hashSize) ; hashSize++ ) {};
    return hashSize;
}


//****************
// Checks if a number is prime
//****************
bool isPrime (int num)
{
    if (num <= 1)
        return false;
    else if (num == 2)
        return true;
    else if (num % 2 == 0)
        return false;
    else
    {
        for (int i = 3 ; i < sqrt(num) ; i++)
            if (num % i == 0)
                return false;
        return true;
    }
}
