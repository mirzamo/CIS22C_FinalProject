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
#include "Athlete.h"

using namespace std;

class FileIO {
public:
   // string fileName;
    bool readFile ();
    void parseInput (vector &);
}

//**************
//Read Files    *
//**************

bool FileIO::readFile()
{
    ifstream inFile (FILE_NAME);
    string readItem;
    vector<string> data_vector;
    
    if (!inFile)
    {cout << "File not found.\n" ; return 0 }
    
    while (getline(inFile , readItem))
    {
        data_vector.pushback (readItem);
        //seperateTokens(readItem);
    }
        
}

//******************
//Seperate Tokens    *
//******************
void FileIO::parseInput(vector &invector)
{
    size_t pos = 0;
    string token;
    
    for (int i = 0 ; i < invector.size() )
    pos = insrting.find(delimeter);
    token = input.substr(0 , pos);
    input.erase(0 , pos + 1);
    
    return token;
}

#endif
