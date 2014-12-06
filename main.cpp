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
#include "hashedDict.h"
#include "validation.h"
#include <string>
#include "Stack.h"

using namespace std;

//const string FNAME = "/Users/Mahsa/Desktop/yyyyy/yyyyy/CIS22C_FinalProject/OlympicAthletes.txt";
const string FNAME = "OlympicAthletes.txt";


/*****
file processing functions
******/
bool readData(int, BST*,hashedDict<string,Athlete*>*);
void parseInput(string&, string&, string&, string&, string&, int&, int*, int&);
void processCommand(BST*, Stack *,hashedDict<string,Athlete*>*);
int hashSize(int);
void projectInfo();
unsigned int hashMap(const string&, const int);
int getNumObjects();
bool out_file_name_is_valid (string name);
void makeOutputFile(BST*, hashedDict<std::string , Athlete*>* , Stack*);


bool deleteNode(string , BST* , Stack*, hashedDict<string,Athlete*>* ,unsigned int (*)(const std::string&));
void insert_input( BST* bst, Stack *myStack, hashedDict<string,Athlete*>* hashTable,
                   unsigned int (*hashFuncPtr)(const std::string&, const int));

/**
    Main function reads in the athlete data into hash table and binary search tree.
    It builds an empty stack as well.
    It presents user with a menu of options, and at the program exit it frees all memory.
*/


int main()
{
    int numObjects = getNumObjects();
    int hash_size = hashSize(numObjects);
    BST* bst = new BST;

    Stack* myStack = new Stack;

    hashedDict<string,Athlete*>* hashTable = new hashedDict<string,Athlete*>(hash_size);
    readData(hash_size, bst, hashTable);

    processCommand(bst, myStack, hashTable);
    delete bst;
    delete myStack;
    delete hashTable;
    return 0;
}


/*****
 get number of datas in input file
 ******/
int getNumObjects()
{
    ifstream fileHandle;
    fileHandle.open(FNAME);

    bool ableToPopulate = fileHandle.good();
    int numObjects =0;
    if (ableToPopulate)
    {
        string line;
        while (getline(fileHandle, line))
            numObjects++;
        fileHandle.close();
    }
    return numObjects;
}



/**
 Returns true if able to read (non-corrupt) file, else returns false.
 If able to read file, it dynamically allocates Athletes in memory.
 It fills all data structures with pointers to these Athletes.
 */
bool readData(int hashSi, BST* bst, hashedDict<string,Athlete*>* hashTable)
{
    ifstream fileHandle;
    fileHandle.open(FNAME);

    bool ableToPopulate = fileHandle.good();

    if (ableToPopulate)
    {
        unsigned int (*hashFuncPtr)(const string&, const int) = hashMap;
        string line =" ", name = " ", country = " ", sport = " ", date = " ";
        int age =0, year=0;
        int medals[3] = {0};
        while (getline(fileHandle, line))
        {
            parseInput(line,name,country,sport,date,age,medals,year);
            Sport winStats(country,year,sport,date);
            Athlete* athlete = new Athlete(name, age, medals, winStats);
            bst->BST_insert(athlete);
            hashTable->addNode(name, athlete, hashFuncPtr);
        }
        fileHandle.close();
    }
    else
        printErrorMsg(Error::BAD_IFILE);
    return ableToPopulate;
}

bool undoDelete(Stack *myStack, BST* bst,hashedDict<std::string , Athlete*>* hashTable,
                unsigned int (*hashFuncPtr)(const std::string&, const int))
{
    bool ableToReturn = !myStack->isEmpty();

    if (ableToReturn)
    {
        Athlete oldAthlete;
        myStack->pop(oldAthlete);
        Athlete* athleteNew = new Athlete(oldAthlete);
        bst->BST_insert(athleteNew);
        hashTable->addNode(athleteNew->getName(), athleteNew, hashFuncPtr);
        cout<< athleteNew->getName() <<" is returned to dataset." << endl;
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
    cout << setw(w1) << left << "0: " << setw(w2) << left << "Display information about dataset and implementation" << endl;
    cout << setw(w1) << left << "1: " << setw(w2) << left << "Insert new entry" << endl;
    cout << setw(w1) << left << "2: " <<  setw(w2) << left << "Delete an entry"<< endl;
    cout << setw(w1) << left << "3: " <<  setw(w2) << left << "Display entries in an indented list in bst"<< endl;
    cout << setw(w1) << left << "4: " <<  setw(w2) << left << "Display entries in hash table"<< endl;
    cout << setw(w1) << left << "5: " <<  setw(w2) << left << "Search for an entry"<< endl;
    cout << setw(w1) << left << "6: " <<  setw(w2) << left << "Show hash table statistics & number of nodes in data structures"<< endl;
    cout << setw(w1) << left << "7: " <<  setw(w2) << left << "Undo delete"<<endl;
    cout << setw(w1) << left << "8: " <<  setw(w2) << left << "Save to a file"<<endl;
    cout << setw(w1) << left << "9: " <<  setw(w2) << left << "Save to a file and Quit" <<endl;
}



/**
 Validated whether user input is valid.
 */
bool validChoice(string choice)
{
    string allowable = "0123456789";
    if (choice.size()==1 && (allowable.find(choice[0]) != std::string::npos))
        return true;
    else
    {
        printErrorMsg(Error::BAD_INPUT);
        menu();
        return false;
    }
}

/**
    Ensures that all numbers are digits.
 */
bool validChoiceDigits(string choice)
{
    string allowable = "0123456789";
    if ((allowable.find(choice[0]) != std::string::npos))
        return true;
    else
    {
        printErrorMsg(Error::BAD_INPUT);
        return false;
    }
}


/**
 Hash function set by user
 */
unsigned int hashMap(const string& key, const int hash_size)
{
    unsigned len = key.size()+1;
    char Key[len];
    strcpy(Key,key.c_str());

    unsigned h = 0, i = 0;

    for ( i = 0; i < len; i++ )
        h ^= Key[i];
    //h = 33 * h + Key[i];
    //h = ( h * 16777619 ) ^ Key[i];
    // h = ( h << 4 ) ^ ( h >> 28 ) ^ Key[i]*3;
    //h ^= ( h << 5 ) + ( h >> 2 ) + Key[i];

    return h % hash_size;
}


/*****
 delete a node from both hash table and tree
 *****/
bool deleteNode(string delNode, BST* bst, Stack* myStack , hashedDict<string,Athlete*>* hashTable,unsigned int (*hashFuncPtr)(const std::string&, const int))

{
    bool ableToDelete = false;

    ableToDelete = hashTable->searchNode(delNode , hashFuncPtr);

    if (ableToDelete)
    {
        Athlete athleteCopy = hashTable->getAthleteCopy(delNode, hashFuncPtr);
        myStack->push(athleteCopy);
        cout << endl;

        bst->BST_Delete(delNode);
        hashTable->deleteNode(delNode, hashFuncPtr);
    }

    else
        cout << " Athlete cannot be removed because it does not exist" << endl;
    /**
     Athlete* athlete = new Athlete(name, age, medals, winStats);
     Stack->push(athlete);
     */
    return ableToDelete;
}



/**
 Processes user command for the data entries.
 */
void processCommand(BST* bst, Stack *myStack, hashedDict<string,Athlete*>* hashTable)
{
    bool inProgress = true;
    unsigned int (*hashFuncPtr)(const string&, const int) = hashMap;
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
            insert_input(bst, myStack, hashTable, hashFuncPtr);
            break;
        }
        case '2':
        {
            string key = " ";
            cout << "Please enter athlete name to delete: ";
            getline(cin, key);
            deleteNode(key, bst, myStack , hashTable, hashFuncPtr);

            break;
        }
        case '3':
        {
            bst->BST_Indented_List();
            break;
        }
        case '4':
        {
            hashTable->printHashed(true);
            break;
        }
        case '5':
        {
            Athlete anAthlete;
            string key = " ";
            cout << "Please enter athlete name to search: ";
            getline(cin, key);

            if (!hashTable->searchNode(key,hashFuncPtr))
                printErrorMsg(Error::BAD_SEARCH);
        }

        case '6':
        {
            cout<< "_____Hash table statistics____"<<endl;
            cout<<"Total entries stored: " << hashTable->getCount()<<endl;
            cout<<"Number of collisions: " << hashTable->getColl()<<endl;
            cout<<"Load factor: " << setprecision(3)<< hashTable->getLoadFac()<<endl;
            cout << "Number of linked lists: " << hashTable->getNumLL()<<endl;
            cout<<"Length of longest linked list: " << hashTable->getMaxLLsize()<<endl;
            cout<<"Ave number of nodes stored in linked list: " << hashTable->getAveLLsize()<<endl;

            cout<< "\n_____Number of Nodes in All Data Structures____"<<endl;
            cout<<" #Items in BST: " << bst->size()<< endl;
            cout<<" #Items in Hash Table: " << hashTable->getCount() << endl;
            cout<<" #Items in Stack: " << myStack->getCount() << endl;
            break;
        }
        case '7':
        {
            undoDelete(myStack, bst, hashTable, hashFuncPtr);
            break;
        }

        case '8':
        {
            makeOutputFile(bst, hashTable , myStack);
            break;
        }
        case '9':
        {

            makeOutputFile(bst, hashTable , myStack);
            inProgress = false;
        }
        }
    }
}


/*****
 checks if a given number is prime
 ****/
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


/*****
 Ddetermine hash size : gets number
 of datas, multiply
 by 2, find the next prime number
 *****/
int hashSize(int numAthletes)
{
    int hashSize = numAthletes * 2+1;
    while (!isPrime(hashSize))
        hashSize++;
    return hashSize;
}



/******
 get information of an athlete and
 inserts in tree and hash table.
 Error if the athlete already exists
 *****/
void insert_input (BST* bst, Stack *myStack, hashedDict<string,Athlete*>* hashTable,
                   unsigned int (*hashFuncPtr)(const std::string&, const int))
{
    string name = " ", country = " ", sport = " ", date = " ", num = " ";
    int age =0, year=0;
    int medals[3] = {0};

    cout << "Enter Athlete's First and Last Name:\t";
    getline(cin , name);

    bool alreadyExists = hashTable->searchNode(name, hashFuncPtr);

    if (!alreadyExists)
    {
        cout << "Enter Country:\t";
        getline (cin , country);

        cout << "Enter Sport:\t ";
        getline (cin , sport);

        cout << "Enter date:\t";
        getline (cin, date);

        do
        {
            cout << "Enter age: ";
            getline(cin, num);
        }
        while (!validChoiceDigits(num));
        age = stoi(num);

        do
        {
            cout << "Enter year: ";
            getline(cin, num);
        }
        while (!validChoiceDigits(num));
        year = stoi(num);

        do
        {
            cout << "Enter number of gold medals: ";
            getline(cin, num);
        }
        while (!validChoiceDigits(num));
        medals[2] = stoi(num);

        do
        {
            cout << "Enter number of silver medals: ";
            getline(cin, num);
        }
        while (!validChoiceDigits(num));
        medals[2] = stoi(num);

        do
        {
            cout << "Enter number of bronze medals: ";
            getline(cin, num);
        }
        while (!validChoiceDigits(num));
        medals[2] = stoi(num);

        Sport winStats(country,year,sport,date);
        Athlete* athlete = new Athlete(name, age, medals, winStats);

        bst->BST_insert(athlete);
        hashTable->addNode(name, athlete, hashFuncPtr);

        cout << athlete->getName() << " added successfully." << endl;
    }
    else
        cout << "\nError: The Athlete already exists in the dataset.\n" << std::endl;
}


/****
 Displays project info
 ***/
void projectInfo()
{
    cout << "\n**********Group Info: Team #9**********" << endl
         <<"Team Members: Mahsa M, Elena M, Kelly D, Misha Y" <<endl
         << "Purpose: CIS 22C Fall 2014 Final Project" <<endl;


    cout << "\n**********Dataset Info**********" << endl
         << "Dataset used: Olympic Medal Winners "<<endl
         << "URL: http://www.tableausoftware.com/public/community/sample-data-sets" <<endl
         << "Data Format: Athlete-Age-Country-Year-Closing Ceremony Date-Sport-Gold Medals-Silver Medals-Bronze Medals" << endl;

    cout << "\n**********Implementation Info**********" << endl
         << "Data Structures Used: Stack (Linked), BST , Hash Dictionary"<<endl;
}


//*******************************
//OUTPUT FILE NAME VALIDATION
//if the neame is not followed by .txt, it is invalid
//**************************

bool out_file_name_is_valid (string name)
{
    size_t pos = 0;
    string token;

    if (name[0] == '.')
    {
        cout << "Invalid name\n";
        return false;
    }


    pos = name.find('.');
    name.erase(0 , pos + 1);

    if (name != "txt")
    {
        cout << "Invalid name\n";
        return false;
    }

    return true;
}



//*******************
//make output file
//******************
void makeOutputFile(BST *bst , hashedDict<std::string , Athlete*> *hash , Stack *mystack)
{
    string fileName;
    cout << "Enter a name for output file (followed by .txt):\t";
    getline(cin , fileName);

    if (out_file_name_is_valid (fileName))
    {
        std::ofstream outFile(fileName);
        bst->saveFileInOrder(outFile);

        cout<<" Output is saved in file called " <<fileName<<endl;
        outFile.close();
    }

}
