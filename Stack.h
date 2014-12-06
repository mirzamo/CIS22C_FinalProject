/*
   Stack template
*/
#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H
#include <iostream>
#include "Athlete.h"


class Stack
{
private:
    struct StackNode
    {
        Athlete value;          // Value in the node
        StackNode *next;  // Pointer to next node
    };

    StackNode *top;     // Pointer to the stack top
    int count;

public:
    Stack()
    {
        top = NULL;
        count = 0;
    }

    ~Stack();

    bool push(Athlete);
    bool pop(Athlete&);
    bool pop();
    bool isEmpty();
    int getCount();
    bool getTop(Athlete &);
    bool clear();
};

#endif
