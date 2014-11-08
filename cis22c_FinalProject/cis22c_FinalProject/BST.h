//
//  BST.h
//  bst_2
//
//  Created by Mahsa Mirza on 11/7/14.
//  Copyright (c) 2014 Mahsa. All rights reserved.
//

#define BST_H

#include "Movie.h"
#include "BST_Node.h"
#include "Queue.h"
#include <iomanip>

using namespace std;

template <class T , class R>
class BST
{
private:

    BST_Node<T,R> *root;       // root of the tree
    int count;            // number of nodes in the tree
    
    
    BST_Node<T,R> *_search(int target);
    void _BST_InorderTraverse( BST_Node<T,R> *root ) const;
    void _BST_PreorderTraverse( BST_Node<T,R> *root ) const;
    void _BST_PostorderTraverse( BST_Node<T,R> *root ) const;
    void _BST_BreadthFisrtTraversal( BST_Node<T,R> *root ) const;
    void _BST_Indented_List(BST_Node<T,R> *root , int) const;
    void _find_keys_Greater(T target , BST_Node<T,R> *);
    void _BST_Destroy(BST_Node<T , R> *root);

    
public:
    // Constructor
    BST() {root = NULL;    count = 0;}

    // Destructor
    ~BST();

    // Binary Tree operations
    void BST_insert(Movie<T,R> dataIn);
    bool Search(int target, Movie<T,R> &movie);
    void BST_InorderTraverse() const;
    void BST_PreorderTraverse() const;
    void BST_PostorderTraverse() const;
    void BST_BreadthFisrtTraversal() const;
    void find_keys_Greater(T target);
    void BST_Indented_List() const;
    bool isEmpty() const	{return count == 0;}
    int size() const	    {return count;}
    
};
//#endif





/**~*~*
 This function calls a recursive function to traverse the
 tree in inorder
 *~**/
template <class T , class R>
void BST<T,R>::BST_InorderTraverse() const
{
    
    _BST_InorderTraverse(root);
}

/**~*~*
 Inorder Traversal of the Binary Tree:
 Left-Root-Right
 *~**/
template <class T , class R>
void BST<T,R>::_BST_InorderTraverse(BST_Node<T,R> *root) const
{
    if (root)
    {
        _BST_InorderTraverse(root->left);
        root->movie.print();
        _BST_InorderTraverse(root->right);
    }
}



/**~*~*
 This function calls a recursive function to traverse the
 tree in Preorder
 *~**/
template <class T , class R>
void BST<T,R>::BST_PreorderTraverse() const
{
    _BST_PreorderTraverse(root);
}

/**~*~*
 Preorder Traversal of the Binary Tree:
 Root-Left-Right
 *~**/
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
template <class T , class R>
void BST<T,R>::BST_PostorderTraverse() const
{
    _BST_PostorderTraverse(root);
}

/**~*~*
 Postorder Traversal of the Binary Tree:
 Left-Right-Root
 *~**/
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
template <class T , class R>
void BST<T,R>::BST_BreadthFisrtTraversal() const
{
    _BST_BreadthFisrtTraversal(root);
}

/**~*~*
 Bredth Traversal of the Binary Tree:
 (using a queue)
 *~**/
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
template <class T , class R>
void BST<T,R>::BST_Indented_List() const
{
    _BST_Indented_List(root , 1) ;
}

/**~*~*
 Indentent List of the Binary Tree:
 *~**/
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
template <class T , class R>
void BST<T,R>::BST_insert(Movie<T,R> newmovie)
{
    BST_Node<T,R> *newNode;
    BST_Node<T,R> *pWalk;
    BST_Node<T,R> *parent;
    
    // allocate the new node
    newNode = new BST_Node<T,R>;
    newNode->movie.setname(newmovie.getname());
    newNode->movie.setyear(newmovie.getyear());
    newNode->left  = NULL;
    newNode->right = NULL;
    
    if (!root) // tree is empty
        root = newNode;
    else
    {
        pWalk = root;
        while( pWalk )
        {
            parent   = pWalk;
            if( newmovie.getyear() < pWalk->movie.getyear() )
                pWalk = pWalk->left;
            else
                pWalk = pWalk->right;
        }
        
        // insert the new node
        if( newmovie.getyear() < parent->movie.getyear() ) // no left child
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
template <class T , class R>
BST<T,R>::~BST()
{
    if (root)
        _BST_Destroy(root);
}

/**~*~*
 This function traverses the binary tree in postorder and deletes every node
 *~**/
template <class T , class R>
void BST<T,R>::_BST_Destroy(BST_Node<T,R> *root)
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
 Search a BST for a given target: if found, returns true and passes back
 movie, otherwise returns false. It calls the private _search to locate the node.
 *~**/
template <class T , class R>
bool BST<T,R>::Search(int target, Movie<T,R> &foundmovie)
{
    BST_Node<T,R> *found = _search(target);
    if (found)
    {
        foundmovie.setname( found->movie.getname());
        foundmovie.setyear( found->movie.getyear());
        
        return true;
    }
    return false;
}


/**~*~*
 Locates the node that contains a given target in a BST:
 - if found returns a pointer to that node
 - if not found returns NULL
 *~**/
template <class T , class R>
BST_Node<T,R>* BST<T,R>::_search(int target)
{
    if (!root) // tree is empty
        return NULL;
    
    // tree is not empty
    BST_Node<T,R> *pWalk = root;
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



/**~*~*
 This function calls a recursive function that finds
 all the values greater than a given ky
 *~**/
template <class T , class R>
void BST<T,R>::find_keys_Greater(T target)
{
    _find_keys_Greater(target , root);
    
}

/**~*~*
 This function find all the values greater than a given ky
 *~**/
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


