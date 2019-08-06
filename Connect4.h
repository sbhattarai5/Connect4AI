//Name: Saurav Bhattarai
//File: Connect4.h

#ifndef CONNECT4_H
#define CONNECT4_H

const int ROW=6;
const int COL=7;
const int SEQUENCE_REQUIRED = 4;    //sequence required to win the game
const char B = 'B';
const char Y = 'Y';
const char SPACE = ' ';
const char MAXIMIZER = 'B';    //my minimax algorithm calculates the heurestics on the basis of maximizer

class Connect4
{
public:
    Connect4 ()
        : _turn('B'), _winner(' '), _isgameover(false), _emptyspots(ROW * COL), _lastmoverow(-1), _lastmovecol(-1), _points(0)
    {
        for (int i = 0; i < ROW; ++i)
        {
            for (int j = 0; j < COL; ++j)
            {
                _board[i][j] = ' ';
            }
        }
    }

    Connect4 (const Connect4 * game)
    {
        _turn = game->_turn;
        _winner = game->_winner;
        _isgameover = game->_isgameover;
        _emptyspots = game->_emptyspots;
        _lastmoverow = game->_lastmoverow;
        _lastmovecol = game->_lastmovecol;
        _points = game->_points;
        for (int i = 0; i < ROW; ++i)
        {
            for (int j = 0; j < COL; ++j)
            {
                _board[i][j] = game->_board[i][j];
            }
        }
    }

    int get_move_row(int col) const
    {
        if (col < 0 || col >= COL) return -1;
        for(int i = ROW - 1; i >= 0; --i)
        {
            if (_board[i][col] == ' ') return i;
        }
        return -1;
    }

    bool is_move_legal(int col) const
    {
        return (get_move_row(col) != -1);
    }
    
    void make_move(int col)
    {
        //std::cout << col << std::endl;
        int row = get_move_row(col);
        if (row == -1)
        {
            std::cout << "\nIllegal move!\n";
            return;
        }
        _board[row][col] = _turn;
        _lastmoverow = row;
        _lastmovecol = col;
        --_emptyspots;
        check_gameover();   //checks if the game is over  //updates the value of winner, _isgameover
        _turn = (_turn == 'B' ? 'Y' : 'B');
        return;
    }
    
    void check_gameover() 
    {
        if (_turn == ' ' || _lastmoverow == -1 || _lastmovecol == -1) return;
        if (check_E() + 1 + check_W() >= SEQUENCE_REQUIRED ||
            check_NE() + 1 + check_SW() >= SEQUENCE_REQUIRED ||
            check_N() + 1 + check_S() >= SEQUENCE_REQUIRED ||
            check_NW() + 1 + check_SE() >= SEQUENCE_REQUIRED)
        {
            _isgameover = true;
            _winner = _turn;
            if (_turn == MAXIMIZER) _points = 1000;
            else _points = -1000;
        }
        else
        {
            if (_emptyspots == 0)
            {
                _isgameover = true;
                _points = 100;
            }
        }
        
    }

    bool isgameover() const { return _isgameover; }
    bool isdraw() const { return (_isgameover && _winner == ' '); }
    char winner() const { return _winner; }
    char turn() const { return _turn; }
    int points () const { return _points; }
    int lastmovecol() const { return _lastmovecol; }
    int check_E() //return the number of pieces towards the east side from where the move was made
    {
        int row = _lastmoverow;
        int col = _lastmovecol;
        int no_of_consequent_pieces = 0;
        ++col;
        while (col < COL)
        {
            if (_board[row][col] == _turn) no_of_consequent_pieces += 1;
            else break;
            ++col;
        }
        return no_of_consequent_pieces;
    }

    int check_NE() //return the number of pieces towards the north-east side from where the move was made
    {
        int row = _lastmoverow;
        int col = _lastmovecol;
        int no_of_consequent_pieces = 0;
        ++col;
        --row;
        while (row >= 0 && col < COL)
        {
            if (_board[row][col] == _turn) no_of_consequent_pieces += 1;
            else break;
            ++col;
            --row;
        }
        return no_of_consequent_pieces;
    }

    int check_N() //return the number of pieces towards the north side from where the move was made
    {
        int row = _lastmoverow;
        int col = _lastmovecol;
        int no_of_consequent_pieces = 0;
        --row;
        while (row >= 0)
        {
            if (_board[row][col] == _turn) no_of_consequent_pieces += 1;
            else break;
            --row;
        }
        return no_of_consequent_pieces;
    }

    int check_NW() //return the number of pieces towards the north-west side from where the move was made
    {
        int row = _lastmoverow;
        int col = _lastmovecol;
        int no_of_consequent_pieces = 0;
        --col;
        --row;
        while (row >= 0 && col >= 0)
        {
            if (_board[row][col] == _turn) no_of_consequent_pieces += 1;
            else break;
            --col;
            --row;
        }
        return no_of_consequent_pieces;
    }
    
    int check_W() //return the number of pieces towards the west side from where the move was made
    {
        int row = _lastmoverow;
        int col = _lastmovecol;
        int no_of_consequent_pieces = 0;
        --col;
        while (col >= 0)
        {
            if (_board[row][col] == _turn) no_of_consequent_pieces += 1;
            else break;
            --col;
        }
        return no_of_consequent_pieces;
    }

    int check_SW() //return the number of pieces towards the south-west side from where the move was made
    {
        int row = _lastmoverow;
        int col = _lastmovecol;
        int no_of_consequent_pieces = 0;
        --col;
        ++row;
        while (row < ROW && col >= 0)
        {
            if (_board[row][col] == _turn) no_of_consequent_pieces += 1;
            else break;
            --col;
            ++row;
        }
        return no_of_consequent_pieces;
    }
    
    int check_S() //return the number of pieces towards the south side from where the move was made
    {
        int row = _lastmoverow;
        int col = _lastmovecol;
        int no_of_consequent_pieces = 0;
        ++row;
        while (row < ROW)
        {
            if (_board[row][col] == _turn) no_of_consequent_pieces += 1;
            else break;
            ++row;
        }
        return no_of_consequent_pieces;
    }

    int check_SE() //return the number of pieces towards the south-east side from where the move was made
    {
        int row = _lastmoverow;
        int col = _lastmovecol;
        int no_of_consequent_pieces = 0;
        ++col;
        ++row;
        while (row < ROW && col < COL)
        {
            if (_board[row][col] == _turn) no_of_consequent_pieces += 1;
            else break;
            ++col;
            ++row;
        }
        return no_of_consequent_pieces;
    }
    
    friend std::ostream & operator<<(std::ostream & cout, Connect4 & game)
    {
        cout << '\n';
        cout << ' ';
        for (int i = 0; i < COL; ++i)
        {
            cout << "+-";
        }
        cout << '+';
        cout << '\n';
        
        for (int i = 0; i < ROW; ++i)
        {
            cout << i;    //comment this after done debugging
            //cout << ' ';    //commented for debugging purposes
            cout << '|';
            for (int j = 0; j < COL; ++j)
            {
                cout << game._board[i][j] << '|';
            }

            cout << '\n';

            cout << ' ';
            for (int i = 0; i < COL; ++i)
            {
                cout << "+-";
            }
            cout << '+';
            cout << '\n';
        }

        cout << ' ';
        for (int i = 0; i < COL; ++i)
        {
            cout << " " << i;
        }
        cout << '\n';
        return cout;
    }
private:
    char _board[ROW][COL];
    char _turn;
    char _winner;
    bool _isgameover;
    int _emptyspots;
    int _lastmoverow;
    int _lastmovecol;
    int _points;
};

#endif

