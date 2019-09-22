//Name: Node.h
//File: Saurav Bhattarai

#ifndef NODE_H
#define NODE_H

#include "Connect4.h"
#include <vector>

const int MAX_DEPTH = 11;  //analyzes eleven steps ahead
const int POS_INFINITY = 9999;   //this is bigger than the max possible points given by the heuristics
const int NEG_INFINITY = -9999;  //this is smaller than the min possible points given by the heuristics
const int NONE = -123456;        //represents None value  

class Node
{
public:
    Node(Connect4 * game, Node * parent=NULL, int depth=0)
        : _game(new Connect4(game)), _parent(parent), _depth(depth)
    {
        if (_game->turn() == MAXIMIZER) _ismaximizer = true;
        else _ismaximizer = false;
    }

    Connect4 * give_game(int col) const
    {
        if (_game->isgameover() || !(_game->is_move_legal(col))) return NULL;
        Connect4 * newgame = new Connect4(_game);
        newgame->make_move(col);
        return newgame;
    }

    int minimax()  //return the move which results in the maximum possible points
    {
        int alpha = NEG_INFINITY;
        int beta = POS_INFINITY;
        int move = -1;
        if (_game->isgameover()) return move;
        int value = NEG_INFINITY;
        for (int i = 0; i < COL; ++i)
        {
            Connect4 * new_game = give_game(i);
            if (new_game != NULL)
            {
                Node * new_child = new Node(new_game, this, _depth + 1);
                _childrens.push_back(new_child);
                delete new_game;
                int new_value = new_child->min_value(alpha, beta);
                if (value < new_value)
                {
                    value = new_value;
                    move = i;
                }
                alpha = value;
            }
        }
        if (debug_printing) std::cout << "Returned value by minimax: " << value << std::endl;
        return move;
    }

    int min_value(int alpha, int beta) //returns the minimum of the node
    {
        if (_game->isgameover() || _depth >= MAX_DEPTH) return _game->points();
        int value = POS_INFINITY;
        for (int i = 0; i < COL; ++i)
        {
            Connect4 * new_game = give_game(i);
            if (new_game != NULL)
            {
                Node * new_child = new Node(new_game, this, _depth + 1);
                _childrens.push_back(new_child);
                delete new_game;
                int new_value = new_child->max_value(alpha, beta);
                if (new_value == NONE) continue;
                if (new_value <= alpha)
                {
                    return NONE;
                }
                if (beta > new_value) beta = new_value;
                if (value > new_value) value = new_value;
            }
        }
        return value;
    }

    int max_value(int alpha, int beta) //return the maximum of the node
    {
        if (_game->isgameover() || _depth >= MAX_DEPTH) return _game->points();
        int value = NEG_INFINITY;
        for (int i = 0; i < COL; ++i)
        {
            Connect4 * new_game = give_game(i);
            if (new_game != NULL)
            {
                Node * new_child = new Node(new_game, this, _depth + 1);
                _childrens.push_back(new_child);
                delete new_game;
                int new_value = new_child->min_value(alpha, beta);
                if (new_value == NONE) continue;
                if (new_value >= beta)
                {
                    return NONE;
                }
                if (alpha < new_value) alpha = new_value;
                if (value < new_value) value = new_value;
            }
        }
        return value;
    }
    void clear()
    {
        for (int i = 0; i < _childrens.size(); ++i)
        {
            delete _childrens[i];
        }
    }

    friend std::ostream & operator<<(std::ostream & cout, const Node & node)
    {
        cout << "<Node " << &node << " _parent: " << node._parent << " _depth: " << node._depth << " _ismaximizer: " << node._ismaximizer << " no_of_childrens: " << node._childrens.size() << " >\n";
        cout << *node._game;
        for (int i = 0; i < node._childrens.size(); ++i)
        {
            cout << *node._childrens[i];
        }
        return cout;
    }
    ~Node()
    {
        clear();
        delete _game;
    }

    static bool debug_printing;
private:

    Connect4 * _game;
    Node * _parent;
    int _depth;
    bool _ismaximizer;
    std::vector< Node * > _childrens;
};

#endif

