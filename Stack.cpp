#include "Stack.h"
/*
   Destructor
*/
Stack::~Stack()
{
    StackNode *currNode, *nextNode;

    // Position nodePtr at the top of the stack.
    currNode = top;

    // Traverse the list deleting each node.
    while (currNode)
    {
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}


/*
  Member function push pushes the argument onto
  the stack.
*/
bool Stack::push(Athlete item)
{
    StackNode *newNode = new StackNode;

    if (!newNode)
        return false;
    newNode->value = item;

    newNode->next = top;
    top = newNode;
    count++;

    return true;
}

bool Stack:: pop(Athlete& data)
{
    bool ableToPop = !isEmpty();
    if (ableToPop)
    {
        data = top->value;
        StackNode* topF = top->next;
        delete top;
        count--;
        top = topF;
        std::cout<<"Popped "<<data.getName()<<" from stack"<<std::endl;
    }
    return ableToPop;
}

bool Stack::pop()
{
    StackNode *temp;

    // empty stack
    if (count == 0)
        return false;

    // pop value off top of stack
    temp = top->next;
    delete top;
    top = temp;
    count--;
    return true;
}




bool Stack::clearStack()
{
    while (!isEmpty())
        pop();
    return isEmpty();
}


/*
  Member function isEmpty returns true if the stack
  is empty, or false otherwise.
*/
bool Stack::isEmpty()
{
    return count == 0;
}


/*
  Member function getcount returns the count in the stack.
*/
//template <class T>
int Stack::getCount()
{
    return count;
}


/*
  Member function getTop returns true and copies its top value to an argement.
  return false if the stack is empty.
*/
bool Stack::getTop(Athlete &item)
{
    if( top == NULL )
        return false;

    item = top -> value;
    return true;
}
