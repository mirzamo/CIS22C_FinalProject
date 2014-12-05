//<<<<<<< HEAD
#ifndef BST_H
#define BST_H

#include "Athlete.h"
#include "BST_Node.h"

class BST
{
private:

    BST_Node *root;
    int count;

    BST_Node*_search(std::string );
    void _BST_Indented_List(BST_Node *root , int) const;
    void _BST_Destroy(BST_Node *root);
    void _BST_Delete (BST_Node* , const std::string taregetNodePtr);
    void getAthlete(Athlete &);

public:

    BST() {root = NULL;    count = 0;}

    // Binary Tree operations
    void BST_insert(Athlete* dataIn);
    bool Search(std::string anathlete);
    void BST_Delete (const std::string anEntry);
    void BST_Indented_List() const;
    bool isEmpty() const	{return count == 0;}
    int size() const	    {return count;}
    
    
    
    
//    Athlete getAthlete(std::string entry)
//    {
//        
//        return this_search(entry);
//    }


    ~BST();
};





#endif // BST_H
//=======
//#ifndef BST_H
//#define BST_H
//
//#include "Athlete.h"
//#include "BST_Node.h"
//
//class BST
//{
//private:
//
//    BST_Node *root;
//    int count;
//
//    BST_Node*_search(int target);
//    void _BST_Indented_List(BST_Node *root , int) const;
//    void _BST_Destroy(BST_Node *root);
//    void _BST_Delete (BST_Node *taregetNodePtr);
//
//
//public:
//
//    BST()
//    {
//        root = NULL;
//        count = 0;
//    }
//
//    // Binary Tree operations
//    void BST_insert(Athlete* dataIn);
//    bool Search(int target, Athlete &anathlete);
//    bool BST_Delete (const Athlete & anEntry);
//    void BST_Indented_List() const;
//    bool isEmpty() const
//    {
//        return count == 0;
//    }
//    int size() const
//    {
//        return count;
//    }
//
//    ~BST();
//};
//
//



//#endif // BST_H
//>>>>>>> FETCH_HEAD
