//
//  Stack.h
//  CIS22C_FinalProject
//
//  Created by Mahsa Mirza on 12/3/14.
//  Copyright (c) 2014 Mahsa. All rights reserved.
//

#ifndef __CIS22C_FinalProject__Stack__
#define __CIS22C_FinalProject__Stack__

#include <stdio.h>



//#ifndef DYNAMICSTACK_H
//#define DYNAMICSTACK_H
#include <iostream>
#include "Athlete.h"
using namespace std;

class Stack
{
private:
    struct StackNode
    {
        Athlete value;
        StackNode *next;
    };
    
    StackNode *top;
    int count;
    
public:
    //Constructor
    Stack(){top = NULL; count = 0;}
    
    // Destructor
    ~Stack();
    
    // Stack operations
    bool push(Athlete);
    bool pop(Athlete &);
    bool isEmpty();
    int getCount();
    bool getTop(Athlete &);
};



Stack::~Stack()
{
    StackNode *currNode, *nextNode;
    
    currNode = top;
    
    while (currNode)
    {
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}


bool Stack::push(Athlete item)
{
    StackNode *newNode;
    
    newNode = new StackNode;
    if (!newNode)
        return false;
    newNode->value = item;
    
    newNode->next = top;
    top = newNode;
    count++;
    
    return true;
}


bool Stack::pop(Athlete &item)
{
    StackNode *temp;
    
    // empty stack
    if (count == 0)
        return false;
    
    item = top->value;
    temp = top->next;
    delete top;
    top = temp;
    count--;
    
    return true;
}


bool Stack::isEmpty()
{
    return count == 0;
}



int Stack::getCount()
{
    return count;
}



bool Stack::getTop(Athlete &item)
{
    if( top == NULL )
        return false;
    
    item = top -> value;
    return true;
}


#endif /* defined(__CIS22C_FinalProject__Stack__) */
