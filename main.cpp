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
//#include "LinkedStack.h"
#include "hashedDict.h"
#include "validation.h"
#include <vector>
#include <string>
#include "Stack.h"

using namespace std;


//file name
//const string FNAME = "/Users/Mahsa/Documents/College/CIS22C/CIS22C_FinalProject/short.txt";

const string FNAME = "OlympicAthletes.txt";
const string OUTPUT_FNAME = "Output.txt";



//file processing functions
bool readData(int, BST*,hashedDict<string,Athlete*>*);
void parseInput(string&, string&, string&, string&, string&, int&, int*, int&);
void processCommand(BST*, /*LinkedStack<Athlete>**/ Stack *,hashedDict<string,Athlete*>*);
int hashSize(int);
void projectInfo();
unsigned int hashMap(const string&, const int);
int getNumObjects();
bool out_file_name_is_valid (string name);





//
bool deleteNode(string& delNode, BST*, /*LinkedStack<Athlete>**/ Stack*, hashedDict<string,Athlete*>*,unsigned int (*)(const std::string&));
void insert_input( BST* bst, /*LinkedStack<Athlete>* Stack*/Stack *myStack, hashedDict<string,Athlete*>* hashTable,
                  unsigned int (*hashFuncPtr)(const std::string&, const int));





int main()
{
    int numObjects = getNumObjects();
    int hash_size = hashSize(numObjects);
    BST* bst = new BST;
    
    //LinkedStack<Athlete>* Stack = new LinkedStack<Athlete>;
    Stack* myStack = new Stack;
    
    hashedDict<string,Athlete*>* hashTable = new hashedDict<string,Athlete*>(hash_size);
    readData(hash_size, bst, hashTable);
    
    processCommand(bst, myStack, hashTable);
    delete bst;
    delete myStack;
    delete hashTable;
    return 0;
}


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

/**
 MISHA:
 Function asks user to input name of an Athlete to delete,
 searches bst for whether that athlete is present, displays error message if not found
 returns true/false depending on whether found
 changes delNode by reference
 */
bool getUserNode(string& userNode);

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

bool deleteNode(string& delNode, BST* bst, /*LinkedStack<Athlete>* Stack*/Stack *myStack, hashedDict<string,Athlete*>* hashTable,
                unsigned int (*hashFuncPtr)(const std::string&, const int))
{
    
    bool ableToDelete = false;
    // cout<<hashTable->searchNode(delNode,hashFuncPtr)<<endl;
    
    //Kelly: search Node from hash table, getAthlete data for constructor below - if found, turn ableToDelete to true;
    ableToDelete = hashTable->searchNode(delNode, hashFuncPtr);
    
    Sport winStats(" ",0," ",0);
    Athlete athlete(delNode , 0 , {0} , winStats);
    myStack->push(athlete);
    
    
    if (ableToDelete)
    {
        bst->BST_Delete(athlete);
    }
    
    /**
     Athlete* athlete = new Athlete(name, age, medals, winStats);
     Stack->push(athlete);
     */
    // Mahsa: bst delete ptr
    //Kelly: hash func delete ptr + node
    return ableToDelete;
}


bool undoDelete(/*LinkedStack<Athlete>**/Stack *myStack, BST* bst)
{
    bool ableToReturn = false;
    
    if (!myStack->isEmpty())
    {
        Athlete oldAthlete;
        myStack->pop(oldAthlete);
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
    cout << setw(w1) << left << "0: " << setw(w2) << left << "Display information about dataset and implementation" << endl;
    cout << setw(w1) << left << "1: " << setw(w2) << left << "Insert new entry" << endl;
    cout << setw(w1) << left << "2: " <<  setw(w2) << left << "Delete an entry"<< endl;
    cout << setw(w1) << left << "3: " <<  setw(w2) << left << "Display entries in an indented list in bst"<< endl;
    cout << setw(w1) << left << "4: " <<  setw(w2) << left << "Display entries in hash table"<< endl;
    cout << setw(w1) << left << "5: " <<  setw(w2) << left << "Search for an entry"<< endl;
    cout << setw(w1) << left << "6: " <<  setw(w2) << left << "Show hash table statistics"<< endl;
    cout << setw(w1) << left << "7: " <<  setw(w2) << left << "Undo delete"<<endl;
    cout << setw(w1) << left << "8: " <<  setw(w2) << left << "Show number of nodes in data structures"<<endl;
    cout << setw(w1) << left << "9: " <<  setw(w2) << left << "Save to a file and Quit"<<endl;
}

/**
 Validated whether user input is valid.
 */
bool validChoice(string choice)
{
    string allowable = "0123456789";
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
unsigned int hashMap(const string& key, const int hash_size)
{
    unsigned len = key.size()+1;
    char Key[len];
    strcpy(Key,key.c_str());
    
    unsigned h = 0, i = 0;
    
    for ( i = 0; i < len; i++ )
        h = ( h << 4 ) ^ ( h >> 28 ) ^ Key[i]*3;
    
    return h % hash_size;
}

/**
 Processes user command for the data entries.
 */
void processCommand(BST* bst, /*LinkedStack<Athlete>* Stack*/Stack *myStack, hashedDict<string,Athlete*>* hashTable)
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
                deleteNode(key, bst, myStack, hashTable, hashFuncPtr);
                break;
            }
            case '3':
            {
                bst->BST_Indented_List();
                break;
            }
            case '4':
            {
                string key = " ";
                cout << "Please enter athlete name to search: ";
                getline(cin, key);
                hashTable->searchNode(key,hashFuncPtr);
                break;
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
                cout<<"Number of nodes in each linked list: " << endl;;
                break;
            }
            case '7':
            {
                undoDelete(myStack, bst);
                break;
            }
            case '7':
            {
                string name;
                cout << "Enter a name for output file (followed by .txt)" << endl;
                cin.ignore();
                getline(cin , name);
                
                if (out_file_name_is_valid (name))      //check is out file name is the right format
                { hashTable->saveFile(name);}
                break;
            }
            case '8':
            {
                cout<<" #Items in BST: " << bst->size()<< endl;
                cout<<" #Items in Hash Table: " << hashTable->getCount() << endl;
                cout<<" #Items in Stack: " << myStack->getCount() << endl;
                break;
            }
            case '9':
            {
                //saveOutput(bst);
                inProgress = false;
            }
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
    int hashSize = numAthletes * 2+1;
    while (!isPrime(hashSize))
        hashSize++;
    return hashSize;
}


//void insert_input(BST* bst , hashedDict<string,Athlete*>* hashTable )
void insert_input (BST* bst, /*LinkedStack<Athlete>* Stack*/Stack *myStack, hashedDict<string,Athlete*>* hashTable,
                   unsigned int (*hashFuncPtr)(const std::string&, const int))
{
    string name = " ", country = " ", sport = " ", date = " ";
    int age =0, year=0;
    int medals[3] = {0};
    
    cout << "Enter Athlete's Name and family name: ";
    getline (cin , name);
    cin.ignore();
    cout << "Enter Country: ";
    getline (cin , country);
    cin.ignore();
    cout << "Enter Sport ";
    getline (cin , sport);
    cin.ignore();
    cout << "Enter date ";
    cin >> date;
    
    cout << "Enter Age ";
    cin >> age;
    
    cout << "Enter year ";
    cin >> year;
    
    
    cout << "Enter number of gold medals: ";
    cin >> medals[0];
    cout << "Enter number of gold medals: ";
    cin >> medals[1];
    cout << "Enter number of gold medals: ";
    cin >> medals[2];
    
    Sport winStats(country,year,sport,date);
    Athlete* athlete = new Athlete(name, age, medals, winStats);
    
    // unsigned int (*hashFuncPtr)(const string&, const int) = hashMap;
    
    if (hashTable->searchNode(name, hashFuncPtr))
    {cout << "Duplication!!" << std::endl; return;}
    
    //        if (bst->Search(*athlete))
    //        {cout << "Duplication!!" << std::endl; return;}
    //
    
    bst->BST_insert(athlete);
    hashTable->addNode(name, athlete, hashFuncPtr);
    
    cout << athlete->getName() << " added successfully." << endl;
}


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
    {cout << "Invalid name\n";    return false;}
    
    
    pos = name.find('.');
    name.erase(0 , pos + 1);
    
    if (name != "txt")
    {cout << "Invalid name\n";    return false;}
    
    return true;
}
