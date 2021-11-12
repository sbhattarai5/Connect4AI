//Name: Saurav Bhattarai
//File: main.cpp

#include <iostream>
#include "GameTree.h"

bool Node::debug_printing = false; //debug printing is off by default

int main()
{
    Connect4 * game1 = new Connect4();
    GameTree tree1(game1);
    int col_input = -2;
    std::cout << "\n****************************************************************************";
    std::cout << "\nWelcome to the Connect4 AI game. Play against the AI who is not so smart...";
    std::cout << "\nThere are two players 'B' and 'Y'. ";
    std::cout << "AI is '" << MAXIMIZER << "' and you're '" << (MAXIMIZER == 'B' ? 'Y' : 'B') << "'. Goodluck!\n";
    std::cout << "****************************************************************************\n";
    std::cout << "\nEnter 42 to start playing: ";
    std::cin >> col_input;
    if (col_input != 42) return 0;
    while (col_input != -1 && !game1->isgameover())
    {
        if (game1->turn() == MAXIMIZER)
        {
            tree1.reinitialize(game1);
            col_input = tree1.best_move();
        }
        else
        {
            std::cout << *game1;
            std::cout << "Choose a column to play from 0 to 6: ";
            std::cin >> col_input;
        }
        game1->make_move(col_input);
    }
    if (game1->isgameover())
    {
        std::cout << *game1;
        if (game1->isdraw()) std::cout << "The game is draw!!\n";
        else std::cout << "\nThe winner is " << game1->winner() << "!!\n\n";
    }
    delete game1;
    return 0;
}


