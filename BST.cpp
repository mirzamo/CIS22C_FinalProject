#include "BST.h"
#include "Stack.h"
#include <iomanip>
#include <fstream>
#include <iostream>
//#include <string>


/**~*~*
 Insert a new Node into a BST
 *~**/
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



/**~*~*
 Search
 *~**/
bool BST::Search(std::string target)

{
    BST_Node *found = _search(target);
    if (found)
    {
        found->anAthlete->print();

        return true;
    }
    
    return false;
}



/****
 search function
 ***/
BST_Node* BST::_search(std::string target)

{
    if (!root)         //tree is empty
        return NULL;

    //tree is not empty
    BST_Node *pWalk = root;

    while( pWalk )
    {
        if (target < pWalk->anAthlete->getName())
        {
            pWalk = pWalk->left;
        }

        else if (target > pWalk->anAthlete->getName() )
            pWalk = pWalk->right;

        else
            return pWalk;      //found
    }
    return NULL;   //not found
}



/**~*~*
 Indented List
 *~**/
void BST::BST_Indented_List()
{
    _indentedList(root,1,0);
}


/**~*~*
 This function calls a recursive function to traverse the
 tree as an indentent list
 *~**/
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



/***
 Delete
 ****/
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
    {
        std::cout << "Tree is empty" << std::endl;
        return;
    }


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
        return ;
    }

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
    else if ((pWalk->right == nullptr && pWalk->left) || (pWalk->right && pWalk->left == nullptr))
    {
        // Right Leaf Present, No Left Leaf
        if (pWalk->left == nullptr && pWalk->right)
        {
            // If parent's left tree equals Node
            if (parent->left == pWalk)
            {
                parent->left = pWalk->right;
            }
            // If parent's right tree equals Node n
            else
            {
                // then parent's right tree becomes n's right tree
                // and delete n
                parent->right = pWalk->right;
            }
        }

        else // Left Leaf Present, No Right Leaf Present
        {
            if(parent->left == pWalk)
            {
                parent->left = pWalk->left;
            }
            else
            {
                parent->right = pWalk->left;
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
    if (pWalk->left && pWalk->right)
    {
        BST_Node* smallest = new BST_Node;
        smallest = pWalk->right;
        

        if (smallest->right == nullptr && smallest->left == nullptr)
        {
            pWalk->anAthlete = smallest->anAthlete;
            pWalk->right = nullptr;
        }
        
        if (smallest->right != nullptr && smallest->left == nullptr)
        {
            pWalk->anAthlete = smallest->anAthlete;
            pWalk->right = smallest->right;
        }
        
        else {
        //go to smallest node in right subtree
        while (smallest->left)
        {
            parent = smallest;
            smallest = smallest->left;
        }
        pWalk->anAthlete = smallest->anAthlete;

        if(smallest->right == nullptr)
        {
            parent->left = nullptr;
        }

        else
        {
            parent->left = smallest->right;
        }
        }
        std::cout << target << " has been removed from the Tree." << std::endl;
        
        smallest->anAthlete = nullptr;
        smallest->right = nullptr;
        smallest->left = nullptr;
        delete smallest;
        
        count--;
        return;

    }
}


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
            Athlete* tmp = root->anAthlete;

            outFile << tmp->getName()<< " "<< tmp->getAge()<<" "<<tmp->getWinStats()._country<<" " <<
            tmp->getWinStats()._year<<" " <<tmp->getWinStats()._ceremonyDate<<" " <<" " <<
            tmp->getWinStats()._sportType<<" " <<tmp->getMedalCount(Medal::GOLD)<<" " <<
            tmp->getMedalCount(Medal::SILVER)<<" " <<tmp->getMedalCount(Medal::BRONZE)<< std::endl;
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
