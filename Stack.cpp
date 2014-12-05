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
    while (currNode) //while (currNode != NULL)
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



/**~*~*
  Member function pop pops the value at the top
  of the stack off, and copies it into the variable
  passed as an argument.
*~**/
//template <class T>
bool Stack::pop(Athlete &item)
{
    StackNode *temp;

    // empty stack
    if (count == 0)
        return false;

    // pop value off top of stack
    item = top->value;
    temp = top->next;
    delete top;
    top = temp;
    count--;

    return true;
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

bool Stack::clear ()
{
    while(count)
    {
        pop ();
    }
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
//template <class T>
bool Stack::getTop(Athlete &item)
{
    if( top == NULL )
        return false;

    item = top -> value;
    return true;
}
