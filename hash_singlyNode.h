/**
 Templated header file for implementation of a node that stores 2 entries and a pointer to the next node.
 */

#ifndef HASH_SINGLY_NODE_H
#define HASH_SINGLY_NODE_H

template <class keyT, class itemT>
class HsinglyNode
{
private:
    keyT _key;
    itemT _item;
    HsinglyNode* _fwd;

public:
    HsinglyNode (): _fwd(nullptr) {};
    HsinglyNode (keyT key, itemT item): _key(key), _item(item),_fwd(nullptr) {};
    ~HsinglyNode() {};

    void setItem(const itemT& item)
    {
        _item = item;
    }
    void setKey(const keyT& key)
    {
        _key=key;
    }
    void setFwd (HsinglyNode<keyT, itemT>* nextNode)
    {
        _fwd = nextNode;
    }
    itemT getItem() const
    {
        return _item;
    }
    keyT getKey() const
    {
        return _key;
    }
    HsinglyNode<keyT,itemT>* getFwd() const
    {
        return _fwd;
    }

};
#endif // HASH_SINGLY_NODE_H
