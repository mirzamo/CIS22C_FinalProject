#ifndef BST_H
#define BST_H

#include "Athlete.h"
#include "Queue.h"
#include <iomanip>

class BST_Node
{
public:
    Athlete* anAthlete;
    BST_Node *left;
    BST_Node *right;


    BST_Node (Athlete* theObject): anAthlete(theObject), left(nullptr), right (nullptr){};
} ;

class BST
{
private:

    BST_Node *root;
    int count;


    BST_Node*_search(int target);
    void _BST_InorderTraverse( BST_Node *root ) const;
   // void _BST_PreorderTraverse( BST_Node<T,R> *root ) const;
    //void _BST_PostorderTraverse( BST_Node<T,R> *root ) const;
    //void _BST_BreadthFisrtTraversal( BST_Node<T,R> *root ) const;
    //void _BST_Indented_List(BST_Node<T,R> *root , int) const;
    //void _find_keys_Greater(T target , BST_Node<T,R> *);
    void _BST_Destroy(BST_Node *root);


public:
    // Constructor
    BST() {root = NULL;    count = 0;}

    // Destructor
    ~BST();

    // Binary Tree operations
    void BST_insert(Athlete* dataIn);
    bool Search(int target, Athlete &anathlete);
    void BST_InorderTraverse() const;
   // void BST_PreorderTraverse() const;
    //void BST_PostorderTraverse() const;
    //void BST_BreadthFisrtTraversal() const;
    //void find_keys_Greater(T target);
    //void BST_Indented_List() const;
    bool isEmpty() const	{return count == 0;}
    int size() const	    {return count;}

};
//#endif





/**~*~*
 This function calls a recursive function to traverse the
 tree in inorder
 *~**/
void BST::BST_InorderTraverse() const
{

    _BST_InorderTraverse(root);
}

/**~*~*
 Inorder Traversal of the Binary Tree:
 Left-Root-Right
 *~**/
void BST::_BST_InorderTraverse(BST_Node *root) const
{
    if (root)
    {
        _BST_InorderTraverse(root->left);
        std::cout << root->anAthlete->getName() << std:: endl;
        //root->movie.print();
        _BST_InorderTraverse(root->right);
    }
}



/**~*~*
 This function calls a recursive function to traverse the
 tree in Preorder
 *~**/
/*
template <class T , class R>
void BST<T,R>::BST_PreorderTraverse() const
{
    _BST_PreorderTraverse(root);
}

/**~*~*
 Preorder Traversal of the Binary Tree:
 Root-Left-Right
 *~**/
/*
template <class T , class R>
void BST<T,R>::_BST_PreorderTraverse(BST_Node<T,R> *root) const
{
    if (root == NULL)   return;

    root->movie.print();
    _BST_PreorderTraverse(root->left);
    _BST_PreorderTraverse(root->right);

}



/**~*~*
 This function calls a recursive function to traverse the
 tree in Postorder
 *~**/
/*
template <class T , class R>
void BST<T,R>::BST_PostorderTraverse() const
{
    _BST_PostorderTraverse(root);
}

/**~*~*
 Postorder Traversal of the Binary Tree:
 Left-Right-Root
 *~**/
/*
template <class T , class R>
void BST<T,R>::_BST_PostorderTraverse(BST_Node<T,R> *root) const
{
    if (root)
    {
        _BST_PostorderTraverse(root->left);
        _BST_PostorderTraverse(root->right);
        root->movie.print();

    }
}



/**~*~*
 This function calls a recursive function to traverse the
 tree in breadth order
 *~**/
/*
template <class T , class R>
void BST<T,R>::BST_BreadthFisrtTraversal() const
{
    _BST_BreadthFisrtTraversal(root);
}

/**~*~*
 Bredth Traversal of the Binary Tree:
 (using a queue)
 *~**/
/*
template <class T , class R>
void BST<T,R>::_BST_BreadthFisrtTraversal(BST_Node<T,R> *root) const
{
    Queue<BST_Node<T,R>*> queue;
    BST_Node<T,R> *node;
    queue.enqueue(root);

    while (!queue.isEmpty()) {
        queue.dequeue(node);
        node->movie.print();
        if (node->left) {
            queue.enqueue(node->left);
        }
        if (node->right) {

            queue.enqueue(node->right);
        }
    }

}



/**~*~*
 This function calls a recursive function to traverse the
 tree as an indentent list
 *~**/
/*
template <class T , class R>
void BST<T,R>::BST_Indented_List() const
{
    _BST_Indented_List(root , 1) ;
}

/**~*~*
 Indentent List of the Binary Tree:
 *~**/
/*
template <class T , class R>
void BST<T,R>::_BST_Indented_List(BST_Node<T,R> *root , int i) const
{
    if (root)
    {
        cout  << setw(i*10) << i << ".  ";

        root->movie.print();
        _BST_Indented_List(root->right , ++i);
        _BST_Indented_List(root->left , i);

    }
}



/**~*~*
 Insert movie into a BST
 *~**/
void BST::BST_insert(Athlete* anAthlete)
{
    BST_Node* newNode = new BST_Node(anAthlete);
    BST_Node *pWalk;
    BST_Node *parent;

    if (!root) // tree is empty
        root = newNode;
    else
    {
        pWalk = root;
        while( pWalk )
        {
            parent   = pWalk;
            if( newNode->anAthlete < pWalk->anAthlete )
                pWalk = pWalk->left;
            else
                pWalk = pWalk->right;
        }

       if( newNode->anAthlete < parent->anAthlete )
            parent->left  = newNode;
    else
            parent->right = newNode;
    }

    count++;
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


/*

template <class T , class R>
bool BST::Search(int target, Movie &foundmovie)
{
    BST_Node *found = _search(target);
    if (found)
    {
        foundmovie.setname( found->movie.getname());
        foundmovie.setyear( found->movie.getyear());

        return true;
    }
    return false;
}
*/

/*
template <class T , class R>
BST_Node* BST::_search(int target)
{
    if (!root) // tree is empty
        return NULL;

    // tree is not empty
    BST_Node *pWalk = root;
    while( pWalk )
    {
        if( target < pWalk->movie.getyear() )
            pWalk = pWalk->left;
        else
            if( target > pWalk->movie.getyear() )
                pWalk = pWalk->right;
            else
                return pWalk; // found
    }

    return NULL; // not found
}
*/


/**~*~*
 This function calls a recursive function that finds
 all the values greater than a given ky
 *~**/
/*
template <class T , class R>
void BST<T,R>::find_keys_Greater(T target)
{
    _find_keys_Greater(target , root);

}

/**~*~*
 This function find all the values greater than a given ky
 *~**/
/*
template <class T , class R>
void BST<T,R>::_find_keys_Greater(T target , BST_Node<T,R> *root)
{
    if (root)
    {
        _find_keys_Greater(target , root->left);
        if (root->movie.getyear() > target)
        {root->movie.print();}
        _find_keys_Greater(target,root->right);
    }

}
*/

#endif // BST_H
