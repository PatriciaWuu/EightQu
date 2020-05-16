/**~*~*
 8 Queens Problem
 
 Extra Credit: This program prints one solution to the 8 Queens Puzzle.
 Change it to display and count all solutions.
 
 Run the program and save the output as a comment at the end of the source file
 
 NAME:Patricia Wu
 IDE: xcode
 *~**/

#include <iostream>
#include <iomanip>

#include "StackADT.h"

using namespace std;

const int SIZE = 30;

int getValidSize(int low, int high, string msg);
bool threatened(int board[][SIZE], int row, int col, int boardSize);
void placeQueens(Stack<int> *stack, int boardSize, int &cnt);
void printBoard(Stack<int> *stack, int boardSize);

int main ( void )
{
    int  boardSize;
    Stack<int> *stack = new Stack<int>;
    int cnt = 0;
    cout << "\n\t **~*~** Eight Queens problem **~*~** \n\n"
    "\t Place a queen in each row of the board\n"
    "\t so that no two queens threaten each other. \n";
    
    boardSize = getValidSize (4, SIZE, "the board size: ");
    placeQueens(stack, boardSize, cnt);
    
    cout << "There are " << cnt << " solution(s) for " << boardSize << " queens!\n\n";
    
    cout << "\n\t **~*~** THE END **~*~** \n\n";
    return 0;
}

/**~*~*
 This function prompts the user to enter an integer number within a given range
 If the input is not valid (not a number or if it is outside of the range) it
 prompts the user to enter a new number, until the input is valid.
 *~**/
int getValidSize(int low, int high, string msg)
{
    int num;
    
    do
    {
        cout << "\nPlease enter " << msg << " (" << low << " to " << high << "): ";
        cin >> num;
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(cin.fail() || num < low || num > high);
    
    return num;
}

/**~*~*
 Position queens on a game board so that no queen
 can capture any other queen.
 *~**/
void placeQueens(Stack<int> *stack, int boardSize, int &cnt)
{
    int  row, col;
    int     board[SIZE][SIZE] = {0};    // 0 no queen: 1 queen
    
    row = 0;
    col = -1;
    // row could not go beyond row = 0
    while (row < boardSize && row > -1)
    {
        while(col < boardSize && row < boardSize && row > -1){
        col++;
            
        if (!threatened(board, row, col, boardSize))
        {
            //1 means Q will be put there, so this position will be set to not avaiable.
            board[row][col] = 1;
            stack->push(col);
            
            if(stack -> getCount() == boardSize){
                printBoard(stack, boardSize);
                //pop the last row to start from next stack
                stack -> pop(col);
                //reset the last right position for avaiable.
                board[row][col] = 0;
                //one solution is ready
                cnt++;
            }
            else{
            //move to next row
            row++;
            col = -1;
            }
        }
            //backtracking: this row is fail, move to previous row and previous col.
        while (col >= boardSize - 1 && row > -1)
        {
            stack->pop(col);
            row--;
            board[row][col] = 0;
        }
    }
}
}

/**~*~*
 Checks rows, columns, and diagonals for threatening queens
 - board contains current positions for queens.
 - row and col are position for new queen
 - boardSize is number of rows and cols in board.
 - returns true if guarded; false if not guarded
 *~**/
bool threatened(int board[][SIZE], int row, int col, int boardSize)
{
    int r, c;
    
    // Check current col for a queen
    c = col;
    for (r = 0; r < row; r++)
        if (board[r][c] == 1)
            return true;
    
    // Check diagonal right-up
    for (r = row - 1, c = col + 1; r > -1 && c < boardSize; r--, c++)
        if (board[r][c] == 1)
            return true;
    
    // Check diagonal left-up
    for (r = row - 1, c = col - 1; r > -1 && c > -1; r--, c--)
        if (board[r][c] == 1)
            return true;
    
    return false;
}

/**~*~*
 Print positions of chess queens on a game board
 - stack contains positions of queen.
 - boardSize is the number of rows and columns
 *~**/
void printBoard (Stack<int> *stack, int boardSize)
{
    int col, stCol;
    
    Stack<int> *pOutStack = new Stack<int>;
    
    if (stack->isEmpty())
    {
        cout << "There are no positions on this board\n";
        return;
    }
    if (boardSize > 16)
    {
        cout << "Only boards <= 16 are printed!\n";
        return;
    }
    
    // Reverse stack
    while (!stack->isEmpty())
    {
        stack->pop(stCol);
        pOutStack->push(stCol);
    }
    
    
    // Print Column numbers
    cout << "\n           ";
    for(int i = 0; i < boardSize; i++)
        cout << setw(3) << i + 1 << "|";
    cout << endl;
    
    // print divider
    cout << "           ";
    for(int i = 0; i < boardSize; i++)
        cout << "--- ";
    cout << endl;
    
    // print board
    int row = 0;
    while (!pOutStack->isEmpty())
    {
        pOutStack->pop(stCol);
        //push back to hold position for backtracking
        stack->push(stCol);
        cout << "(" << setw(2) << row + 1 << ", " << setw(2) << stCol + 1 << "}  |";
        for (col = 0; col < boardSize; col++)
        {
            if (stCol == col)
                cout << " Q |";
            else
                cout << "   |";
        }
        cout << endl;
        cout << "           ";
        for(int i = 0; i < boardSize; i++)
        {
            cout << "--- ";
        }
        cout << endl;
        
        row++;
    }
}

/**~*~*
 
 **~*~** Eight Queens problem **~*~**
 
 Place a queen in each row of the board
 so that no two queens threaten each other.
 
 Please enter the board size:  (4 to 30): 6
 
 1|  2|  3|  4|  5|  6|
 --- --- --- --- --- ---
 ( 1,  2}  |   | Q |   |   |   |   |
 --- --- --- --- --- ---
 ( 2,  4}  |   |   |   | Q |   |   |
 --- --- --- --- --- ---
 ( 3,  6}  |   |   |   |   |   | Q |
 --- --- --- --- --- ---
 ( 4,  1}  | Q |   |   |   |   |   |
 --- --- --- --- --- ---
 ( 5,  3}  |   |   | Q |   |   |   |
 --- --- --- --- --- ---
 ( 6,  5}  |   |   |   |   | Q |   |
 --- --- --- --- --- ---
 
 1|  2|  3|  4|  5|  6|
 --- --- --- --- --- ---
 ( 1,  3}  |   |   | Q |   |   |   |
 --- --- --- --- --- ---
 ( 2,  6}  |   |   |   |   |   | Q |
 --- --- --- --- --- ---
 ( 3,  2}  |   | Q |   |   |   |   |
 --- --- --- --- --- ---
 ( 4,  5}  |   |   |   |   | Q |   |
 --- --- --- --- --- ---
 ( 5,  1}  | Q |   |   |   |   |   |
 --- --- --- --- --- ---
 ( 6,  4}  |   |   |   | Q |   |   |
 --- --- --- --- --- ---
 
            1|  2|  3|  4|  5|  6|
            --- --- --- --- --- ---
 ( 1,  4}  |   |   |   | Q |   |   |
            --- --- --- --- --- ---
 ( 2,  1}  | Q |   |   |   |   |   |
            --- --- --- --- --- ---
 ( 3,  5}  |   |   |   |   | Q |   |
            --- --- --- --- --- ---
 ( 4,  2}  |   | Q |   |   |   |   |
 --- --- --- --- --- ---
 ( 5,  6}  |   |   |   |   |   | Q |
 --- --- --- --- --- ---
 ( 6,  3}  |   |   | Q |   |   |   |
 --- --- --- --- --- ---
 
 1|  2|  3|  4|  5|  6|
 --- --- --- --- --- ---
 ( 1,  5}  |   |   |   |   | Q |   |
 --- --- --- --- --- ---
 ( 2,  3}  |   |   | Q |   |   |   |
 --- --- --- --- --- ---
 ( 3,  1}  | Q |   |   |   |   |   |
 --- --- --- --- --- ---
 ( 4,  6}  |   |   |   |   |   | Q |
 --- --- --- --- --- ---
 ( 5,  4}  |   |   |   | Q |   |   |
 --- --- --- --- --- ---
 ( 6,  2}  |   | Q |   |   |   |   |
 --- --- --- --- --- ---
 There are 4 solution(s) for 6 queens!
 
 
 **~*~** THE END **~*~**
 
 Program ended with exit code: 0
 *~**/
