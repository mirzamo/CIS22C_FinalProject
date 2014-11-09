//
//  FileIO.h
//  cis22c_FinalProject
//
//  Created by Mahsa Mirza on 11/8/14.
//  Copyright (c) 2014 Mahsa. All rights reserved.
//

#ifndef cis22c_FinalProject_FileIO_h
#define cis22c_FinalProject_FileIO_h


//#define FILE_NAME "OlympicAthleteMedals.txt"
#define FILE_NAME "/Users/Mahsa/Documents/College/CIS22C/CIS22C_FinalProject/cis22c_FinalProject/cis22c_FinalProject/OlympicAthleteMedals.txt"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "Athlete.h"

using namespace std;

class FileIO {
private:
    int lineCount;

public:
   // string fileName;
    FileIO() {lineCount = 0;}
    
    bool readFile ();
    void parseInput (vector<string> &);
    bool isPrime (int);
    int hashSize();

    
};

//**************
//Read Files    *
//**************

bool FileIO::readFile()
{
    ifstream inFile (FILE_NAME);
    string readItem;
    vector<string> data_vector;
    
    if (!inFile)
    {cout << "File not found.\n" ; return 0; }
    
    while (getline(inFile , readItem))
    {
        data_vector.push_back (readItem);
        //seperateTokens(readItem);
        
        lineCount++;
    }
        
}

//******************
//Seperate Tokens    *
//******************
/*
void FileIO::parseInput(vector<string> &invector)
{
    size_t pos = 0;
    string element;
    string token;
    
    for (int i = 0 ; i < invector.size() ; i++ )
    {
        element =
        pos = invector.find(delimeter);
        token = input.substr(0 , pos);
        input.erase(0 , pos + 1);
    }
    
    return token;
}
*/



//****************
// Deterine hash siz
//****************
int FileIO:: hashSize()
{
    int hashSize = lineCount * 2;
    //int nextPrime = hashSize + 1;
    
    for (hashSize + 1 ; !isPrime(hashSize) ; hashSize++ ) {}
    
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

#endif
