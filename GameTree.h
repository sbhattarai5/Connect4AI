//Name: Node.h
//File: Saurav Bhattarai

#ifndef GAMETREE_H
#define GAMETREE_H
#include "Node.h"

class GameTree
{
public:
    GameTree(Connect4 * game)
    {
        Node * node = new Node(game);
        _root = node;
    }
    void reinitialize(Connect4 * game)
    {
        delete _root;
        Node * node = new Node(game);
        _root = node;
    }

    int best_move() const
    {
        return _root->minimax();
    }
    ~GameTree()
    {
        delete _root;
    }

    friend std::ostream & operator<< (std::ostream & cout, const GameTree & tree)
    {
        cout << "<Tree " << &tree << " _root: " << tree._root << " >\n";
        if (tree._root != NULL)
        {
            cout << "priniting games....\n\n";
            cout << *tree._root;
        }
        return cout;
    }
private:
    Node * _root;
};

#endif
