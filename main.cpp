/**
    CIS22C : Group #9 Final Project
    Dataset used: Olympic Medal Winners from http://www.tableausoftware.com/public/community/sample-data-sets

    Columns of data in input file have this order:
    Athlete-Age-Country-Year-Closing Ceremony Date-Sport-Gold Medals-Silver Medals-Bronze Medals

*/

#include <fstream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include "Athlete.h"
#include "BST.h"
#include "LinkedStack.h"
#include "hashedDict.h"
#include "validation.h"
#include <vector>
#include <string>

using namespace std;
const int HASH_SIZE = 3100;

const string FNAME = "OlympicAthletes.txt";
bool readData(int&, BST*,hashedDict<string,Athlete*>*);
void parseInput(string&, string&, string&, string&, string&, int&, int*, int&);
void processCommand(BST*, LinkedStack<Athlete>*,hashedDict<string,Athlete*>*);
int hashSize(int);
void projectInfo();
bool deleteNode(string&, LinkedStack<Athlete>*);
unsigned int hashMap(const string&);

int main()
{
    BST* bst = new BST;
    LinkedStack<Athlete>* Stack = new LinkedStack<Athlete>;
    hashedDict<string,Athlete*>* hashTable = new hashedDict<string,Athlete*>(HASH_SIZE);
    int hashSize =0;
    readData(hashSize, bst, hashTable);
    processCommand(bst, Stack, hashTable);
    delete bst;
    delete Stack;
    delete hashTable;
    return 0;
}

/**
    Returns true if able to read (non-corrupt) file, else returns false.
    If able to read file, it dynamically allocates Athletes in memory.
    It fills all data structures with pointers to these Athletes.
*/
bool readData(int& hashSi, BST* bst, hashedDict<string,Athlete*>* hashTable)
{
    ifstream fileHandle;
    fileHandle.open(FNAME);

    bool ableToPopulate = fileHandle.good();

    if (ableToPopulate)
    {
        unsigned int (*hashFuncPtr)(const string&) = hashMap;
        string line =" ", name = " ", country = " ", sport = " ", date = " ";
        int age =0, year=0, numObjects =0;
        int medals[3] = {0};
        while (getline(fileHandle, line))
        {
            parseInput(line,name,country,sport,date,age,medals,year);
            Sport winStats(country,year,sport,date);
            Athlete* athlete = new Athlete(name, age, medals, winStats);
            bst->BST_insert(athlete);
            hashTable->addNode(name, athlete, hashFuncPtr);
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
    MISHA:
    Function asks user to input name of an Athlete to delete,
    searches bst for whether that athlete is present, displays error message if not found

    returns true/false depending on whether found
    changes delNode by reference
*/
bool getNodetoDelete(string& delNode);

/**
    MISHA:
    Function will allow user to input a new Athlete into the database.
    Feel free to write this and any other validation functions to validate that user input from keyboard is valid.
*/
bool insertUserNode();

/**
    Misha:
    Function will save all the nodes present to a file.
*/
bool saveToFile();


/**
    Mahsa, Kelly :
    Searches bst to see if node is found (thus returning bool on whether its found or not),
    copies data into stack, deletes all pointers to node in data structures, and deletes node itself.
*/

bool deleteNode(string& delNode, LinkedStack<Athlete>* Stack)
{
    bool ableToDelete = false;

    //Kelly: search Node from hash table, getAthlete data for constructor below - if found, turn ableToDelete to true;
    /**
    Athlete* athlete = new Athlete(name, age, medals, winStats);
    Stack->push(athlete);
    */
    // Mahsa: bst delete ptr
    //Kelly: hash func delete ptr + node
    return ableToDelete;
}


bool undoDelete(LinkedStack<Athlete>* Stack, BST* bst)
{
    bool ableToReturn = false;

    if (!Stack->isEmpty())
    {
        Athlete oldAthlete;
        Stack->pop(oldAthlete);
        cout<< oldAthlete.getName() <<" is returned to dataset." << endl;
        Athlete* athleteNew = new Athlete(oldAthlete);
        bst->BST_insert(athleteNew);
        //Kelly: hash table insert
        ableToReturn = true; // should fix this bool
    }
    else
        printErrorMsg(Error::EMPTY_STACK);
    return ableToReturn;
}


/**
    Function that cuts up inputted line read from file into chunks and changes correct values by reference.
*/

void parseInput(string& line, string& name, string& country, string& sport, string& date, int& age, int* medals, int& year)
{
    //Athlete-Age-Country-Year-Closing Ceremony Date-Sport-Gold Medals-Silver Medals-Bronze Medals
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
    date = line.substr(0,cut);
    line = line.substr(cut+1);
    cut = line.find_first_of("1234567890");
    sport = line.substr(0,cut-1);
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
    cout << setw(w1) << left << "6: " <<  setw(w2) << left << "Undo delete"<<endl;
    cout << setw(w1) << left << "7: " <<  setw(w2) << left << "Quit"<<endl;
}

/**
    Validated whether user input is valid.
*/
bool validChoice(string choice)
{
    string allowable = "01234567";
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
    Hash function set by user
*/
unsigned int hashMap(const string& key)
{
    unsigned len = key.size()+1;
    char Key[len];
    strcpy(Key,key.c_str());

    unsigned h = 0, i = 0;

    for ( i = 0; i < len; i++ )
        h = ( h << 4 ) ^ ( h >> 28 ) ^ Key[i]*3;


    return h % HASH_SIZE;
}

/**
    Processes user command for the data entries.
*/
void processCommand(BST* bst, LinkedStack<Athlete>* Stack, hashedDict<string,Athlete*>* hashTable)
{
    bool inProgress = true;
    unsigned int (*hashFuncPtr)(const string&) = hashMap;
    while (inProgress)
    {
        menu();
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
            projectInfo();
            break;
        }
        case '1':
        {
            // Misha: this for your function to insert user input
            break;
        }
        case '2':
        {
            // Misha: for your function to get user input for which node to delete (string output of the Athlete name)
            string delNode = "Michael Phelps"; //substitute this with user input
            deleteNode(delNode, Stack);
            break;
        }
        case '3':
        {
            bst->BST_Indented_List();
            break;
        }
        case '4':
        {
            // Misha: for your function to get user input for which node to delete (string output of the Athlete name)
            string key = "Michael Phelps"; //substitute this with user input
            hashTable->searchNode(key,hashFuncPtr);
            break;
        }
        case '5':
        {
            cout<< "_____Hash table statistics____"<<endl;
            cout<<"Total entries stored: " << hashTable->getCount()<<endl;
            cout<<"Number of collisions: " << hashTable->getColl()<<endl;
            cout<<"Load factor: " << setprecision(3)<< hashTable->getLoadFac()<<endl;
            cout << "Number of linked lists: " << hashTable->getNumLL()<<endl;
            cout<<"Length of longest linked list: " << hashTable->getMaxLLsize()<<endl;
            cout<<"Ave number of nodes stored in linked list: " << hashTable->getAveLLsize()<<endl;
            cout<<"Number of nodes in each linked list: " << endl;;
            break;
        }
        case '6':
        {
            undoDelete(Stack, bst);
            break;
        }
        case '7':
            inProgress = false;
        }

    }
}


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

int hashSize(int numAthletes)
{
    int hashSize = numAthletes * 2;
    for (hashSize + 1 ; !isPrime(hashSize) ; hashSize++ ) {};
    return hashSize;
}


void projectInfo()
{
    cout << "\n**********Group Info**********" << endl
         <<"Mahsa M, Elena M, Kelly D, Misha Y" <<endl
         << "CIS 22C Fall 2014" <<endl;


    cout << "\n**********Dataset Info**********" << endl
         << "Dataset used: Olympic Medal Winners "<<endl
         << "URL: http://www.tableausoftware.com/public/community/sample-data-sets" <<endl
         << "Data Format: Athlete-Age-Country-Year-Closing Ceremony Date-Sport-Gold Medals-Silver Medals-Bronze Medals" << endl;
}
