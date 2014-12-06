/**
 Hashed dictionary implementation using an array.
 Implemented as a template, thus parameter for static array is passed in as an argument.
 Hashed table takes user-defined pointer function to input-specific hashing function.
 Collision resolution implemented using linked lists as the overflow area for synonyms given same hash table index.
 */

#ifndef HASHED_DICT_H
#define HASHED_DICT_H

#include <iomanip>
#include <fstream>
#include <iostream>
#include "hash_singlyNode.h"
#include "validation.h"

/*******************************
 Class and method declarations.
 ********************************/
template <class keyT, class itemT>
class hashedDict
{
private:
    int _numCollisions;
    int _count;
    int _arSize;
    int* _LLsize;
    HsinglyNode<keyT, itemT>** _nodes;
protected:
    void _clearDict() const;

public:
    void saveFile(std::ostream &fileName ) const;

    hashedDict(const int arSize): _numCollisions(0), _count(0), _arSize(arSize),
        _LLsize(new int[arSize]), _nodes(new HsinglyNode<keyT, itemT>*[arSize])
    {
        for (int i = 0; i< arSize; i++)
        {
            _nodes[i] = nullptr;
            _LLsize[i] = 0;
        }

    }
    ~hashedDict()
    {
        _clearDict();
    }
    bool addNode(const keyT&, itemT, unsigned int (*)(const keyT&, const int));
    bool searchNode(const keyT&, unsigned int (*)(const std::string&, const int) );
    bool deleteNode(const keyT&, unsigned int (*)(const std::string&, const int) );
    Athlete getAthleteCopy(const keyT&, unsigned int (*)(const std::string&, const int) );

    // Aids for statistics for hash table
    int getCount() const;
    int getColl() const;
    int getAveLLsize() const;
    int getMaxLLsize() const;
    float getLoadFac() const;
    int getNumLL() const;
    void printLLnum() const;
    void printHashed(bool) const;
};

/*******************************
 Method definitions.
 ********************************/

/**
 Getter functions for display of statistics:
 -Total number of elements stored in hash table and overflow area.
 -Number of collisions of synonyms with the same index for the hash table.
 -Load Factor (how full the actual array of elements is), not including linked lists.
 -Number of chains that contain at least 2 elements in the same hash dictionary index.
 -Ave linked list size.
 -Max linked list size.
 -Print size of all linked lists as they result in the hash table.

 */

template <class keyT, class itemT>
int hashedDict<keyT,itemT> ::  getCount() const
{
    return _count;
}

template <class keyT, class itemT>
int hashedDict<keyT,itemT> :: getColl() const
{
    return _numCollisions;
}

template <class keyT, class itemT>
float hashedDict<keyT,itemT> :: getLoadFac() const
{
    return (float)(_count - _numCollisions)*100 / _arSize;
}

template <class keyT, class itemT>
int hashedDict<keyT, itemT> :: getNumLL() const
{
    int numLL = 0;
    for (int i=0 ; i < _arSize; i++)
    {
        if (_LLsize[i] > 1)
            numLL++;
    }
    return numLL;
}

template <class keyT, class itemT>
int hashedDict<keyT,itemT>::getAveLLsize() const
{
    int sum =0, numLL =0;
    for (int i = 0; i<_arSize; i++)
        if (_LLsize[i] > 1)
        {
            numLL ++;
            sum += _LLsize[i];
        }
    if (numLL == 0)
        return 0;
    else
        return sum / numLL;
}

template <class keyT, class itemT>
int hashedDict<keyT,itemT>::getMaxLLsize() const
{
    int Max = _LLsize[0];
    for (int i = 1; i<_arSize; i++)
    {
        if (_LLsize[i] != 0 && _LLsize[i] > Max)
        {
            Max = _LLsize[i];
        }

    }
    return Max;
}


template <class keyT, class itemT>
void hashedDict<keyT,itemT>::printLLnum() const
{
    for (int i=0; i<_arSize; i++)
        std::cout<< _LLsize[i] << " ";
    std::cout<<std::endl;

}
/**
 Creates a node with provided item and key, obtains a hashed value using a function pointer provided,
 and inserts pointer to hash table that points to new node.
 Function returns true if added into hash, false if added into LL.
 */

template <class keyT, class itemT>
bool hashedDict<keyT, itemT>::addNode (const keyT& newKey, itemT newItem, unsigned int (*hashFuncPtr)(const keyT&, const int))
{
    bool ableToHash = true;
    HsinglyNode<keyT, itemT>* newNode = new HsinglyNode <keyT, itemT> (newKey, newItem);
    const int Size = _arSize;
    int hashIndex = hashFuncPtr(newKey, Size);
    if (_nodes[hashIndex] == nullptr)
    {
        _nodes[hashIndex] = newNode;
    }
    else
    {
        ableToHash = false;
        newNode->setFwd(_nodes[hashIndex]); // add newNode to front of LL
        _nodes[hashIndex] = newNode;
        _numCollisions++;
         _LLsize[hashIndex]++;
    }
    _count++;
    return ableToHash;
}

/**
 Takes in a search key and runs it through user-defined hashing function to get hash table index.
 Searches the hash at the given index, and searched the attached linked list in until it's found.
 Returns true if item is found, false otherwise.
 */
template<class keyT, class itemT>
bool hashedDict<keyT,itemT> :: searchNode(const keyT& searchKey, unsigned int (*hashFuncPtr)(const std::string&, const int))// , keyT &item)
{
    const int Size = _arSize;
    int index = hashFuncPtr(searchKey, Size);
    bool ableToFind = false;

    HsinglyNode<keyT, itemT>* searchPtr = _nodes[index];
    for (int i = 0; i < _LLsize[index]; i++)
    {
        if (searchPtr->getKey() != searchKey)
            searchPtr = searchPtr->getFwd();
        else
        {
            ableToFind = true;
            searchPtr->getItem()->printFull();
            // item = searchPtr->getItem();
            break;
        }
    }
//    if (!ableToFind)
//        printErrorMsg(Error::BAD_SEARCH);
    return ableToFind;
}

template<class keyT, class itemT>
Athlete hashedDict<keyT,itemT> ::getAthleteCopy(const keyT& searchKey, unsigned int (*hashFuncPtr)(const std::string&, const int) )
{
    Athlete athleteCopy;
    const int Size = _arSize;
    int index = hashFuncPtr(searchKey, Size);

    HsinglyNode<keyT, itemT>* searchPtr = _nodes[index];
    for (int i = 0; i < _LLsize[index]; i++)
    {
        if (searchPtr->getKey() != searchKey)
        {
            searchPtr = searchPtr->getFwd();
        }

        else
        {
            searchPtr->getItem()->printFull();
            athleteCopy = searchPtr->getItem()->getAthlete();

            break;
        }
    }
    return athleteCopy;

}


template<class keyT, class itemT>
bool hashedDict<keyT,itemT> :: deleteNode(const keyT& searchKey, unsigned int (*hashFuncPtr)(const std::string&, const int))
{
    //search for the node
    const int Size = _arSize;
    int index = hashFuncPtr(searchKey, Size);
    bool ableToFind = false;

    HsinglyNode<keyT, itemT>* searchPtr = _nodes[index];
    HsinglyNode<keyT, itemT>* searchPrev = searchPtr;

    for (int i = 0; i < _LLsize[index]; i++)
    {
        if (searchPtr->getKey() != searchKey)
        {
            searchPtr = searchPtr->getFwd();
            if (i>0)
                searchPrev = searchPrev->getFwd();
        }
        else
        {
            ableToFind = true;
            searchPrev->setFwd(searchPtr->getFwd());
            delete searchPtr;
            _count--;
            std::cout<< searchPtr->getItem()->getName() << " has been removed from the Hash Table."<<std::endl;
            break;
        }
    }

//    if (!ableToFind)
//        printErrorMsg(Error::BAD_SEARCH);
    return ableToFind;
}

/**
 Prints hash table, taking in bool variable indent.
 If indent is true, method prints the entries in an indented way showing hash index and whether it's in a linked list.
 If indent is false, method prints entires in a column in the order they're placed in the table.
 */
template <class keyT, class itemT>
void hashedDict<keyT,itemT>:: printHashed(bool indent) const
{
    for(int i = 0; i < _arSize; i++)
    {
        if (indent)
        {
            std::cout << "Index "<< i <<": ";
            if (_LLsize[i] == 0)
                std::cout << std::endl;
        }
        if (_LLsize[i] >0)
        {
            if (indent)
                std::cout<< std::right << std::setw(5);
            _nodes[i]->getItem()->print();
            HsinglyNode<keyT,itemT>* nextNode = _nodes[i]->getFwd();
            int i = _LLsize[i];
            while (nextNode && i>0)
            {
                std::cout<<nextNode->getItem()->getName()<<std::endl;
                if (indent)
                    std::cout<< std::right << std::setw(20);
                nextNode->getItem()->print();
                nextNode = nextNode->getFwd();
                i--;
            }
        }
    }
}

/**
 Function that clears hash table and associated linked lists.
 This protected method can be called only by destructor.
 */

template <class keyT, class itemT>
void hashedDict<keyT, itemT>::_clearDict() const
{
    for (int i =0; i< getCount(); i++)
        delete _nodes[i];
}




//*************************
/* SAVE the updated text  *
 to an putput file        *
 ************************/
template <class keyT, class itemT>
void hashedDict<keyT, itemT>::saveFile(std::ostream &outFile) const
{
    // std::ofstream outFile(fileName);

    if (outFile)
        for(int i = 0; i < _arSize; i++)
        {


            if (_LLsize[i] >0)
            {
                outFile << _nodes[i]->getItem() << std::endl;
                HsinglyNode<keyT,itemT>* nextNode = _nodes[i]->getFwd();
                while (nextNode)
                {

                    outFile << nextNode->getItem()->getName() <<std::endl;
                    nextNode = nextNode->getFwd();
                }
            }
        }
    // outFile.close();
}


#endif // HASHED_DICT_H
