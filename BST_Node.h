#ifndef DataStructure_TeamProject_BST_Node_h
#define DataStructure_TeamProject_BST_Node_h

class BST_Node
{
public:
    Athlete* anAthlete;
    BST_Node *left;
    BST_Node *right;
    bool delete_flag;
    
    
    BST_Node (Athlete* theObject): anAthlete(theObject), left(nullptr), right (nullptr){};      //??
} ;

#endif
