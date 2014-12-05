//<<<<<<< HEAD
#ifndef BST_H
#define BST_H

#include "Athlete.h"
#include "BST_Node.h"

class BST
{
private:

    BST_Node* root;
    int count;

    BST_Node*_search(std::string );
    void _BST_Indented_List(BST_Node *root , int) const;
    void _BST_Destroy(BST_Node *root);
    void _BST_Delete (BST_Node* , const std::string taregetNodePtr);
    //void _BST_InorderTraverse( BST_Node *root ) const;
    void _saveFileInOrder(BST_Node *root , std::ostream &outFile) const;


   // BST_Node* _BST_Delete(BST_Node* root, std::string target);

protected:
    BST_Node* _insertNode(BST_Node*, BST_Node*);
    void getAthlete(Athlete &);

    void _indentedList(BST_Node*, int, int);

public:

    BST() {root = NULL;    count = 0;}

    // Binary Tree operations
    void BST_insert(Athlete* dataIn);
    bool Search(std::string anathlete);
    void BST_Delete (const std::string anEntry);
   // void BST_InorderTraverse() const;
    void BST_Indented_List();
    bool isEmpty() const	{return count == 0;}
    int size() const	    {return count;}
    void saveFileInOrder(std::ostream &outFile) const;

    
    
    
    
//    Athlete getAthlete(std::string entry)
//    {
//        
//        return this_search(entry);
//    }


    ~BST();
};

#endif
