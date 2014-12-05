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

    else if (newNode->getAthletePtr()->getName() < subTree->getAthletePtr()->getName())
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


void BST::BST_Indented_List()
{
    _indentedList(root,1,0);
}


void BST::_indentedList(BST_Node* subTree, int level =1, int indent =0)
{
    if (indent)
    {
        std::cout << std::setw(indent) << ' ';
        level++;
    }
    std::cout <<level<<". " << subTree->getAthletePtr()->getName() <<"\n ";
    if(subTree != nullptr)
    {
        if(subTree->getLeft())
            _indentedList(subTree->getLeft(), level, indent+4);
        if(subTree->getRight())
            _indentedList(subTree->getRight(), level, indent+4);
    }
}


/**~*~*
 This function calls a recursive function to traverse the
 tree as an indentent list
 *~**/
/*
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

*/


/**~*~*
 Delete
 *~**/
//BST_Node* BST::_BST_Delete(BST_Node* root, std::string target)
//{
//    // STEP 1: PERFORM STANDARD BST DELETE
//    
//    if (root == NULL)
//        return root;
//    
//    // If the key to be deleted is smaller than the root's key,
//    // then it lies in left subtree
//    if ( target < root->anAthlete->getName() )
//        root->left = _BST_Delete(root->left, target);
//    
//    // If the key to be deleted is greater than the root's key,
//    // then it lies in right subtree
//    else if( target > root->anAthlete->getName() )
//        root->right = _BST_Delete(root->right, target);
//    
//    // if key is same as root's key, then This is the node
//    // to be deleted
//    else
//    {
//        // node with only one child or no child
//        if( (root->left == NULL) || (root->right == NULL) )
//        {
//            BST_Node* temp = root->left ? root->left : root->right;
//            
//            // No child case
//            if(temp == NULL)
//            {
//                temp = root;
//                root = NULL;
//            }
//            else // One child case
//                *root = *temp; // Copy the contents of the non-empty child
//            
//            free(temp);
//        }
//        else
//        {
//            // node with two children: Get the inorder successor (smallest
//            // in the right subtree)
//            BST_Node* temp = minValueNode(root->right);
//            
//            // Copy the inorder successor's data to this node
//            root->data = temp->data;
//            
//            // Delete the inorder successor
//            root->right = _deleteNode(root->right, temp->data);
//        }
//    }
//    
//    // If the tree had only one node then return
//    if (root == NULL)
//        return root;
//    
//    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
//    root->level = max(height(root->left), height(root->right)) + 1;
//    
//
//    
//    return root;
//}
//
//
//
//
//void BST::BST_delete(Data dataIn) 
//{
//    root = _deleteNode(root,dataIn);
//}

void BST::BST_Delete (const std::string anEntry)
{
    _BST_Delete(root , anEntry);
}


void BST::_BST_Delete (BST_Node* root , std::string target)
{
    bool found = false;
    BST_Node *pWalk = root;
    BST_Node *parent = nullptr;

    
    //empty tree
    if (!pWalk)
        {std::cout << "Tree is empty" << std::endl;  return;}

    
    //find the target node that needs to be deleted and found is going to be true if the key exist
    while ( pWalk )
    {
        if (pWalk->anAthlete->getName() == target)
        {
            found = true;
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
    }

    
    //target key deos not exist in tree
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

        // CASE 1: leaf
        if(!pWalk->left && !pWalk->right)
        {
            if (parent->left == pWalk)
                parent->left = nullptr;
            
            else
                parent->right = nullptr;
                //  myStack.push(*pWalk->anAthlete);
            pWalk->anAthlete = nullptr;
            delete pWalk;
            count--;
            std::cout << target <<" has been removed from the Tree."<<std::endl;
            return;
        }

    

        // CASE 2: has one child
        else if ((pWalk->right == nullptr && pWalk->left != nullptr) || (pWalk->right != nullptr && pWalk->left == nullptr))
        {
            // Right Leaf Present, No Left Leaf
            if (pWalk->left== nullptr && pWalk->right != nullptr)
            {
                // If parent's left tree equals Node
                if (parent->left == pWalk)
                {
                    // then parent's left tree becomes n's right tree
                    // and delete n
                    parent->left = pWalk->right;
                    // myStack.push(*pWalk->anAthlete);

                   // delete pWalk;
                }
                // If parent's right tree equals Node n
                else
                {
                    // then parent's right tree becomes n's right tree
                    // and delete n
                    parent->right = pWalk->right;
                    // myStack.push(*pWalk->anAthlete);
                    //delete pWalk;
                    //pWalk=nullptr;
                 
                }
            }
            
            else // Left Leaf Present, No Right Leaf Present
            {
                if(parent->left == pWalk)
                {
                    parent->left = pWalk->left;
                    //   myStack.push(*pWalk->anAthlete);

                    //delete pWalk;
                    //count--;
                   // pWalk=nullptr;
                }
                else
                {
                    parent->right = pWalk->left;
                    //   myStack.push(*pWalk->anAthlete);

                    //delete pWalk;
                   // count--;
                    //pWalk=nullptr;
                }
        }
            
        std::cout << target << " has been removed from the Tree." << std::endl;
        pWalk->anAthlete = nullptr;
        delete pWalk;
        count--;
        return;
        }


    

    
    
    // CASE 3: Node has two children
    // Replace Node with smallest value in right subtree
    if (!pWalk->left && !pWalk->right)
    {
        //BST_Node* check = pWalk->right;
        BST_Node* smallest = pWalk->right;

        
        //go to smallest node in right subtree
        while (smallest->left)
        {
            parent = smallest;
            smallest = smallest->left;
        }
        
        Athlete* temp = new Athlete;
        temp = smallest->anAthlete;
        smallest = pWalk;
        pWalk->anAthlete = temp;
        
        delete temp;
        
        if(!pWalk->right)
        {
            parent->left = nullptr;
//            delete pWalk;
//            count--;
        }
        
        else
        {
            parent = pWalk->right;
            
        }
        
        std::cout << target << " has been removed from the Tree." << std::endl;
        pWalk->anAthlete = nullptr;
        delete pWalk;
        count--;
        return;
        
    }
//    
//        
//        if((pWalk->left == nullptr) && (pWalk->right==nullptr) )
//        {
//            pWalk = check;
//            //  myStack.push(*pWalk->anAthlete);
//
//            delete check; count--;
//
//            pWalk->right == nullptr;
//            std::cout << target << " has been removed from the Tree."<< std::endl;
//        }
//        else // Right child has children
//        {
//            // If the node's right child has a left child
//            // Move all the way down left to locate smallest element
//            if((pWalk->right)->left!=nullptr)
//            {
//                BST_Node* leftpWalk;
//                BST_Node* leftpWalkPred;
//                leftpWalkPred=pWalk->right;
//                leftpWalk=(pWalk->right)->left;
//                while(leftpWalk->left != nullptr)
//                {
//                    leftpWalkPred=leftpWalk;
//                    leftpWalk=leftpWalk->left;
//                }
//                pWalk->anAthlete =leftpWalk->anAthlete;    //?????
//                //       myStack.push(*pWalk->anAthlete);
//
//                delete leftpWalk;count--;
//                leftpWalkPred->left == nullptr;
//                std::cout << target <<" has been removed from the Tree."<< std::endl;
//            }
//            else
//            {
//                BST_Node* temp=pWalk->right;
//                pWalk->anAthlete = temp->anAthlete;
//                pWalk->right=temp->right;
//                //      myStack.push(*pWalk->anAthlete);
//
//                delete temp;count--;
//                std::cout << target << " has been removed from the Tree."<<std::endl;
//            }
//        }
//        return;
    }
    /*
    if (!pWalk->left && !pWalk->right)
    {
        BST_Node* check = pWalk->right;
        
        if((pWalk->left == nullptr) && (pWalk->right==nullptr) )
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
    */
//}

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
 This function calls a recursive function to traverse the
 tree in inorder
 *~**/
//void BST::BST_InorderTraverse() const
//{
//    _BST_InorderTraverse(root);
//}

/**~*~*
 Inorder Traversal of the Binary Tree:
 Left-Root-Right
 *~**/
//void BST::_BST_InorderTraverse(BST_Node *root) const
//{
//    if (root)
//    {
//        _BST_InorderTraverse(root->left);
//        root->movie.print();
//        _BST_InorderTraverse(root->right);
//    }
//}



//*************************
/* SAVE the updated text  *
 to an putput file        *
 ************************/
void BST::saveFileInOrder(std::ostream &outFile) const
{
    _saveFileInOrder(root , outFile);

}

void BST::_saveFileInOrder(BST_Node *root , std::ostream &outFile) const
{
    if (outFile)
        if (root)
        {
            _saveFileInOrder(root->left , outFile);
            outFile << root->anAthlete->getName() << std::endl;
            _saveFileInOrder(root->right , outFile);
        }
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
