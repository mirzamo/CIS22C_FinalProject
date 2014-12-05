#include "BST.h"
#include "Stack.h"
#include <iomanip>
#include <fstream>
#include <iostream>
//#include <string>

/**~*~*
 Insert a new Node into a BST
 *~**/
 /*
void BST::BST_insert(Athlete* anAthlete)
{
    BST_Node* newNode = new BST_Node(anAthlete);
    BST_Node *pWalk;
    BST_Node *parent;

    if (!root)          // tree is empty
        root = newNode;

    //    if (_search(anAthlete->getName()))
    //    {std::cout << "Duplication!!" << std::endl; return;}

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
*/

void BST::BST_insert(Athlete* newAthlete)
{
    BST_Node* newNode = new BST_Node(newAthlete);
    root = _insertNode(root, newNode);
}


BST_Node* BST:: _insertNode(BST_Node* subTree, BST_Node* newNode)
{
    if (subTree == nullptr)
    {
        subTree = newNode;
        count++;
    }

    else if (newNode->getAthletePtr()<subTree->getAthletePtr())
        subTree->setLeft(_insertNode(subTree->getLeft(), newNode));

    else
        subTree->setRight(_insertNode(subTree->getRight(), newNode));
    return subTree;
}



bool BST::Search(std::string target)

{
    BST_Node *found = _search(target);
    if (found)
    {
        found->anAthlete->print();

        return true;
    }
    //std::cout << "found failed\n";

    return false;
}


//template <class T , class R>
//BST_Node* BST::_search(std::string target)
BST_Node* BST::_search(std::string target)

{
    if (!root)         //tree is empty
        return NULL;

    //tree is not empty
    BST_Node *pWalk = root;

    while( pWalk )
    {
        if (target < pWalk->anAthlete->getName())
        {//std::cout << pWalk->anAthlete->getName();

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
    if (root)
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

void BST::BST_Delete (const std::string anEntry)
{
    _BST_Delete(root , anEntry);
}


void BST::_BST_Delete (BST_Node* n , std::string target)
{
    BST_Node *targetNodePtr = _search(target);


    //    if (!root)       //  tree is empty
    //        return NULL;
    // LinkedStack<Athlete> myStack;
    //Stack myStack;


    bool found = false;
    BST_Node *pWalk = n;
    BST_Node *parent = nullptr;

    if (!pWalk)
    {std::cout << "Tree is empty" << std::endl;  return;}

    while( pWalk )
    {
        if (pWalk->anAthlete->getName() == target)
        {found = true;
            break;
        }

        else
        {
            parent = pWalk;
            if (target > pWalk->anAthlete->getName())
                pWalk = pWalk->right;
            else
                pWalk = pWalk->left;
        }


        if (!found)
        {
            //std::cout << target << "does not exist" << std::endl;
            return ;
        }


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

        // leaf
        if (!pWalk->right && !pWalk->left)
        {parent = NULL;}


        //has one child
        else if ((pWalk->right == nullptr && pWalk->left != nullptr) || (pWalk->left != nullptr && pWalk->right == nullptr))
            // Right Leaf Present, No Left Leaf
            if(pWalk->left== nullptr && pWalk->right != nullptr)
            {
                // If parent's left tree equals Node n
                if(parent->left==pWalk)
                {
                    // then parent's left tree becomes n's right tree
                    // and delete n
                    parent->left=pWalk->right;
                    // myStack.push(*pWalk->anAthlete);

                    delete pWalk;
                    pWalk=nullptr;
                    std::cout << target <<" has been removed from the Tree." << std::endl;
                }
                // If parent's right tree equals Node n
                else
                {
                    // then parent's right tree becomes n's right tree
                    // and delete n
                    parent->right=pWalk->right;
                    // myStack.push(*pWalk->anAthlete);
                    delete pWalk;
                    pWalk=nullptr;
                    std::cout << target << " has been removed from the Tree." << std::endl;
                }
            }
            else // Left Leaf Present, No Right Leaf Present
            {
                if(parent->left==pWalk)
                {
                    parent->left=pWalk->left;
                    //   myStack.push(*pWalk->anAthlete);

                    delete pWalk;
                    count--;
                    pWalk=nullptr;
                    std::cout<< target <<" has been removed from the Tree."<< std::endl;
                }
                else
                {
                    parent->right=pWalk->left;
                    //   myStack.push(*pWalk->anAthlete);

                    delete pWalk;
                    count--;
                    pWalk=nullptr;
                    std::cout << target <<" has been removed from the Tree."<< std::endl;
                }
            }
        return;
    }
    // CASE 2: Removing a Leaf Node
    if(pWalk->left==nullptr && pWalk->right==nullptr)
    {
        if(parent->left==pWalk)
            parent->left=nullptr;
        else
            parent->right=nullptr;
        //  myStack.push(*pWalk->anAthlete);

        delete pWalk;count--;
        std::cout << target <<" has been removed from the Tree."<<std::endl;
        return;
    }
    // CASE 3: Node has two children
    // Replace Node with smallest value in right subtree
    if(pWalk->left != nullptr && pWalk->right != nullptr)
    {
        BST_Node* check=pWalk->right;
        if((pWalk->left==nullptr)&&(pWalk->right==nullptr))
        {
            pWalk=check;
            //  myStack.push(*pWalk->anAthlete);

            delete check; count--;

            pWalk->right == nullptr;
            std::cout << target <<" has been removed from the Tree."<< std::endl;
        }
        else // Right child has children
        {
            // If the node's right child has a left child
            // Move all the way down left to locate smallest element
            if((pWalk->right)->left!=nullptr)
            {
                BST_Node* leftpWalk;
                BST_Node* leftpWalkPred;
                leftpWalkPred=pWalk->right;
                leftpWalk=(pWalk->right)->left;
                while(leftpWalk->left != nullptr)
                {
                    leftpWalkPred=leftpWalk;
                    leftpWalk=leftpWalk->left;
                }
                pWalk->anAthlete =leftpWalk->anAthlete;    //?????
                //       myStack.push(*pWalk->anAthlete);

                delete leftpWalk;count--;
                leftpWalkPred->left == nullptr;
                std::cout << target <<" has been removed from the Tree."<< std::endl;
            }
            else
            {
                BST_Node* temp=pWalk->right;
                pWalk->anAthlete = temp->anAthlete;
                pWalk->right=temp->right;
                //      myStack.push(*pWalk->anAthlete);

                delete temp;count--;
                std::cout << target << " has been removed from the Tree."<<std::endl;
            }
        }
        return;
    }
}

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




////*************************
///* SAVE the updated text  *
// to an putput file        *
// //************************/
//void BST::saveFile(BST_Node *root , std::string fileName)
//{
//    ofstream outFile(fileName);
//
//    BST_Node *pWalk = root;
//
//    if (outFile)
//       // while (pWalk)
//
//            if (root )
//            {
//                std::cout << std::right << std::setw(i) << i << ".  ";
//
//                root->anAthlete->print();
//                _BST_Indented_List(root->right , ++i);
//                _BST_Indented_List(root->left , i);
//            }
//}
//        {
//            outFile << pWalk->anAthlete;
//
//            nodePtr = nodePtr->forw;
//        }
//
//    outFile.close();
//}



/**~*~*
 Destructor
 This function calls a recursive function to delete all nodes in the binary tree
 *~**/

BST::~BST()
{
    if (root)
        _BST_Destroy(root);
}
