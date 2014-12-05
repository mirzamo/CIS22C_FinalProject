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

Athlete* getAthletePtr() const
    {
        return anAthlete;
    }
     void setLeft(BST_Node* leftNew)
    {
        left = leftNew;
    };
    void setRight(BST_Node* rightNew)
    {
        right = rightNew;
    };

    BST_Node* getLeft() const
    {
        return left;
    };
    BST_Node* getRight() const
    {
        return right;
    };

} ;

#endif
