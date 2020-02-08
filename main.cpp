#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';//нічия
const char NO_ONE = 'N';//продовження

void instructions();
char askYesNo (const string& question);
unsigned int askNumber (const string& question, unsigned int high, unsigned int low = 1);
char humanPiece();
char opponent(char piece);
void displayBoard (const vector<char>& board);
char winner (const vector<char>& board);
inline bool isLegal (const vector<char>& board, unsigned int move);
unsigned int humanMove (const vector<char>& board, char human);
unsigned int computerMove (vector<char> board, char computer);
void announceWinner (char winner, char computer, char human);

int main()
{
    unsigned int move;
    const unsigned int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);
    instructions();
    char human = humanPiece();
    char computer = opponent(human);
    char turn = X;
    displayBoard(board);
    while (winner(board) == NO_ONE)
    {
        if (turn == human)
        {
            move = humanMove(board, human);
            board[move] = human;
        }
        else
        {
            move = computerMove(board, computer);
            board[move] = computer;
        }
        displayBoard(board);
        turn = opponent(turn);
    }
    announceWinner(winner(board), computer, human);
    return 0;
}

void instructions()
{
    cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
    cout << "--where human brain is pit against silicon processor\n\n";
    cout << "Make your move known Ьу entering а number. О - 8. The number\n";
    cout << "corresponds to the desired board position. as illustrated:\n\n";
    cout << " 1 | 2 | 3\n";
    cout << " ---------\n";
    cout << " 4 | 5 | 6\n";
    cout << " ---------\n";
    cout << " 7 | 8 | 9\n\n";
    cout << "Prepare yourself. human. The battle is about to begin.\n\n";
}

char askYesNo (const string& question)
{
    char response;
    do
    {
        cout << question <<  " (y/n): ";
        cin >> response;
    } while (response != 'y' && response != 'n');
    return response;
}

unsigned int askNumber(const string& question, unsigned int high, unsigned int low)
{
    unsigned int number;
    do {
        cout << question << " (" << low << "): ";
        cin >> number;
    } while (number > high || number < low);
    return number;
}

char humanPiece()
{
    char go_first = askYesNo("Do you require the first move?");
    if (go_first == 'y') {
        cout << "\nThen take the first move. You will need it.\n";
        return X;
    }
    else
    {
        cout << "\nYour bravery will";
        return O;
    }
}

char opponent(char piece)
{
    if(piece==X)
    {
        return O;
    }
    else
    {
        return X;
    }
}

void displayBoard (const vector<char>& board)
{
    cout << "\033[2J\033[1;1H";
    cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2] << "\t 1 | 2 | 3 ";
    cout << "\n\t" << "---------" << "\t-----------";
    cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5] << "\t 4 | 5 | 6 ";
    cout << "\n\t" << "---------" << "\t-----------";
    cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8] << "\t 7 | 8 | 9 ";
    cout << "\n\n";
}

char winner (const vector<char>& board)
{
    const unsigned int WINNING_ROWS[8][3] =
            {
             {0, 1, 2},
             {3, 4, 5},
             {6, 7, 8},
             {0, 3, 6},
             {1, 4, 7},
             {2, 5, 8},
             {0, 4, 8},
             {2, 4, 6}
            };
    const unsigned int TOTAL_ROWS = 8;
    for (unsigned int row = 0;row<TOTAL_ROWS; ++row)
    {
        if((board[WINNING_ROWS[row][0]]!=EMPTY)&&
           (board[WINNING_ROWS[row][0]]==board[WINNING_ROWS[row][1]])&&
           (board[WINNING_ROWS[row][1]]==board[WINNING_ROWS[row][2]]))
        {
            return board[WINNING_ROWS[row][0]];
        }
    }
    if(count(board.begin(), board.end(), EMPTY)==0)
    {
        return TIE;
    }
    return NO_ONE;
}

inline bool isLegal(const vector<char>& board, unsigned int move)
{
    return (board[move]==EMPTY);
}

unsigned int humanMove (const vector<char>& board, char human)
{
    unsigned int move = askNumber("Where will you move", (board.size()))-1;
    while (!isLegal(board, move))
    {
        cout << "\nThat square is already occupied, foolish human";
        move = askNumber("Where will you move", (board.size()))-1;
    }
    cout << "Fine...";
    return move;
}

unsigned int computerMove (vector<char> board, char computer)
{
    unsigned int move = 0;
    bool found = false;
    while (!found&&(move<board.size()))
    {
        if(isLegal(board, move))
        {
            board[move] = computer;
            found = winner(board)==computer;
            board[move] = EMPTY;
        }
        if(!found)
        {
            ++move;
        }
    }

    if(!found)
    {
        move = 0;
        char human = opponent(computer);
        while (!found&&(move<board.size()))
        {
            if(isLegal(board, move))
            {
                board[move] = human;
                found = winner(board)==human;
                board[move] = EMPTY;
            }
            if(!found)
            {
                ++move;
            }
        }
    }

    if(!found)
    {
        move = 0;
        unsigned int i = 0;
        const unsigned int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
        while (!found && i<board.size())
        {
            move = BEST_MOVES[i];
            if(isLegal(board, move))
            {
                found = true;
            }
            ++i;
        }
    }
    cout << "I would take square number" << move << endl;
    return move;
}

void announceWinner (char winner, char computer, char human)
{
    if(winner==computer)
    {
        cout << winner << " has won!!!" << endl;
    }
    else if (winner==human)
    {
        cout << winner << " has won!!!" << endl;
    }
    else
    {
        cout << "It is a tie" << endl;
    }
}