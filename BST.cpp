
#include "BST.h"
#include <iomanip>
#include <iostream>
//#include <string>

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

        while ( pWalk )
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
 bool BST::Search(std::string target)//, Athlete &foundedItem)
 {
     BST_Node *found = _search(target);
    if (found)
    {
        std::cout << "found\n";
        found->anAthlete->print();

        return true;
    }
     std::cout << "found failed\n";

     return false;
 }


 //template <class T , class R>
 BST_Node* BST::_search(std::string target)
 {
     if (!root)         //tree is empty
         return NULL;

  //tree is not empty
     BST_Node *pWalk = root;

     while( pWalk )
     {
         if (target < pWalk->anAthlete->getName())
         {std::cout << pWalk->anAthlete->getName();

             pWalk = pWalk->left;              }
         
         else if (target > pWalk->anAthlete->getName() )
                 pWalk = pWalk->right;
         
             else
                 return pWalk;      //found
     }

 return NULL;   //not found
 }







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
    if (root )
    {
        std::cout << std::right << std::setw(i) << i << ".  ";
        
        root->anAthlete->print();
        _BST_Indented_List(root->right , ++i);
        _BST_Indented_List(root->left , i);
    }
}




/**~*~*
Delete
 *~**/

//bool BST::BST_Delete (const std::string anEntry)
//{
//    if (_BST_Delete(anEntry))
//        return true;
//        
//        else return false;
//
//}
//
//
//void BST::_BST_Delete (std::string target)
//{
//    BST_Node *targetNodePtr = _search(target);
//
//    
//    if (!root)       //  tree is empty
//        return NULL;
//    
//   // tree is not empty
//    BST_Node *pWalk = root;
//    BST_Node *parent = root;
//    
//    while( pWalk )
//    {
//        if (target < pWalk->anAthlete->getName())
//        {
//            std::cout << pWalk->anAthlete->getName();
//            
//            parent = pWalk;
//            
//            pWalk = pWalk->left;
//        }
//        
//        else if (target > pWalk->anAthlete->getName())
//        {
//            parent = pWalk;
//
//            pWalk = pWalk->right;
//        }
//        
//        else
//            return pWalk;    //  found
//        
//       // leaf
//        if (!pWalk->right && !pWalk->left)
//        {parent = NULL;}
//        
//        
//        //has one child
//         else if (!pWalk->right || !pWalk->left)
//         {
//             if (!pWalk->left)  has right child
//                 parent = pWalk->right;
//             else   has left child
//                 parent = pWalk->left;
//         }
//        
//        
//        //has two children
//        else if (pWalk->right && pWalk->left)
//        {
//           //find largest n left subtree
//            BST_Node *findLarge = pWalk->left;
//            if ()
//            
//        }
//    }
//    
//    return NULL;   not found
//    
//    
//    
//    
//    
//    if (targetNodePtr)
//    {
//    }
//    else
//    
//}
//



///**~*~*
// This function calls a recursive function that finds
// all the values greater than a given ky
// *~**/
//void BST::find_keys_Greater(T target)
//{
//    _find_keys_Greater(target , root);
//    
//}

/**~*~*
 This function find all the values greater than a given ky
 *~**/
//void BST::_find_Greatest(BST_Node *root)
//{
//    Athlete largest = root->anAthlete->getName();
//    
//    if (root)
//    {
//        
////        _find_Greatet(target , root->left);
////        if (root->movie.getyear() > target)
////        {root->movie.print();}
////        _find_Greatet(target,root->right);
//    }
//    
//}




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
