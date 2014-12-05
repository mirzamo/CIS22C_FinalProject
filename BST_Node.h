#ifndef DataStructure_TeamProject_BST_Node_h
#define DataStructure_TeamProject_BST_Node_h

#include "Athlete.h"
class BST_Node
{
public:
    Athlete* anAthlete;
    BST_Node *left;
    BST_Node *right;

    BST_Node (Athlete* theObject): anAthlete(theObject), left(nullptr), right (nullptr) {};
    ~BST_Node () {};
} ;

#endif
