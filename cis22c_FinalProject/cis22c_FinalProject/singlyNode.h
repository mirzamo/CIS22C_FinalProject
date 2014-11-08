/**
    Template code for a singly linked tree node for a binary tree.
*/

#ifndef NODE_H
#define NODE_H

#include "Date.h"
#include "Athlete.h"

class singlyNode
{
private:
    Athlete person(std::string name, int age,Medal [3] medals, Sport winningStats);
    singlyNode* _left;
    singlyNode* _right;
public:
    treeNode(): _left(nullptr), _right(nullptr) {};
    treeNode(Y year, N name): Movie<Y,N>(year,name), _left(nullptr), _right(nullptr) {};
    treeNode(Movie<Y,N> movie): _movie(movie), _left(nullptr), _right(nullptr) {};
    ~treeNode() {};
    Y getYear() const
    {
        return _movie._year;
    };
    N getName() const
    {
        return _movie._name;
    };
    Movie<Y,N> getMovie() const
    {
        return _movie;
    }

    singlyNode* getLeft() const
    {
        return _left;
    };
    singlyNode* getRight() const
    {
        return _right;
    };
    void setLeft(singlyNode*left)
    {
        _left = left;
    };
    void setRight(singlyNode* right)
    {
        _right = right;
    };
    bool isLeaf() const
    {
        return (_left==nullptr && _right == nullptr);
    };
};
#endif // NODE_H

