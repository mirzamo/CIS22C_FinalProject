//
//  BST_Node.h
//  bst_2
//
//  Created by Mahsa Mirza on 11/7/14.
//  Copyright (c) 2014 Mahsa. All rights reserved.
//

#ifndef bst_2_BST_Node_h
#define bst_2_BST_Node_h

#include "Athlete.h"

//template <class T , class R>
class BST_Node
{
public:
    Athlete anAthlete;         // The value in this node

    BST_Node *left;    // To point to the left node
    BST_Node *right;   // To point to the right node
    
    
    BST_Node () {left = NULL ; right = NULL;}
} ;

#endif
