
#include "BST.h"
#include <iomanip>

 /**~*~*
 Insert a new Node into a BST
 *~**/
void BST::BST_insert(Athlete* anAthlete)
{
    BST_Node* newNode = new BST_Node(anAthlete);
    BST_Node *pWalk;
    BST_Node *parent;

    if (!root)          // tree is empty
        root = newNode;

    else
    {
        pWalk = root;

        while( pWalk )
        {
            parent = pWalk;
            if (newNode->anAthlete < pWalk->anAthlete )
                pWalk = pWalk->left;
            else
                pWalk = pWalk->right;
        }

        if (newNode->anAthlete < parent->anAthlete )
            parent->left  = newNode;

        else
            parent->right = newNode;
    }

    count++;
}




//
// //template <class T , class R>
// bool BST::Search(int target, Athlete &foundedItem)
// {
// BST_Node *found = _search(target);
// if (found)
// {
// foundmovie.setname( found->anAthlete.getname());
// foundmovie.setyear( found->anAthlete.getyear());
//
// return true;
// }
// return false;
// }
//
//
// //template <class T , class R>
// BST_Node* BST::_search(int target)
// {
//     if (!root)         //tree is empty
//         return NULL;
//
//  //tree is not empty
//     BST_Node *pWalk = root;
//
//     while( pWalk )
//     {
//         if (target < pWalk->anAthlete->getName())
//             pWalk = pWalk->left;
//         else
//             if (target > pWalk->movie.getyear() )
//                 pWalk = pWalk->right;
//             else
//                 return pWalk;      //found
//     }
//
// return NULL;   //not found
// }
//
//





/**~*~*
 This function calls a recursive function to traverse the
 tree as an indentent list
 *~**/

//template <class T , class R>
void BST::BST_Indented_List() const
{
    _BST_Indented_List(root , 1) ;
}


void BST::_BST_Indented_List(BST_Node *root , int i) const
{
    if (root)
    {
        root->anAthlete->print();
        _BST_Indented_List(root->right , ++i);
        _BST_Indented_List(root->left , i);
    }
}




/**~*~*
Delete
 *~**/




/**~*~*
 This function traverses the binary tree in postorder and deletes every node
 *~**/

void BST::_BST_Destroy(BST_Node *root)
{
    if (root)
    {
        _BST_Destroy(root->left);
        _BST_Destroy(root->right);
        delete root;
    }
    return;
}





/**~*~*
 Destructor
 This function calls a recursive function to delete all nodes in the binary tree
 *~**/

BST::~BST()
{
    if (root)
        _BST_Destroy(root);
}
