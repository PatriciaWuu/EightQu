
//
//  main.cpp
//  EightQ
//
//  Created by Patricia Wu on 5/1/20.
//  Copyright © 2020 Patricia Wu. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <iomanip>
using namespace std;
struct Position
{
    int row, col;
};
//This function check validation of user input
int numberValidation()
{
    int num;
    cout << "Please enter the number of Queens you want to play:";
    do{
        cin >> num;
        cout << endl;
        cin.clear();
        cin.ignore();
    }while(std::cin.fail()|| num < 1);
    return num;
}

//This function check the position of each queen
bool checkposition(int numQ, Position pos, stack<Position> *curr)
{
    int avai[100][100];
    for(int m = 0; m < numQ; m++)
    {
        for(int n = 0; n < numQ;n++)
        {
            avai[m][n] = 0;
        }
    }
    //for invalid position due to another queen's influence
    stack<Position> occ;
    //for invalid position of previous queen
    stack<Position> waste;
    int j = 0;
    bool rowFlag;
    int count = 0;
    for(int i = 0; i < numQ; i++)
    {
        rowFlag = 0;
        for(; j < numQ && !rowFlag; j++)
        {
            if(avai[i][j] == 0)
            {
                avai[i][j] = 1;
                rowFlag = 1;
                count++;
                pos.row = i; pos.col = j;
                curr->push(pos);
                occ.push(pos);

                //check for col
                for(int c = i+1; c < numQ; c++)
                {
                    if(avai[c][j] == 0)
                    {
                        avai[c][j] = 2;
                        pos.row = c; pos.col = j;
                        occ.push(pos);
                    }

                }
                //check down left digonal
                for(int a = i + 1,temp = j - 1;static_cast<void>(a < numQ), temp >= 0;a++, temp--)
                {
                    if(avai[a][temp] == 0)
                    {
                        avai[a][temp] = 2;
                        pos.row = a; pos.col = temp;
                        occ.push(pos);
                    }
                }
                //check for down right digonal
                for(int b = i + 1, temp = j + 1;static_cast<void>(b < numQ), temp < numQ;b++, temp++)
                {
                    if(avai[b][temp] == 0)
                    {
                        avai[b][temp] = 2;
                        pos.row = b; pos.col = temp;
                        occ.push(pos);
                    }
                }
            }
        }
       //if no space in one row
        if(!rowFlag)
            {
                    //mark previous col avaiable
                    while(avai[pos.row][pos.col] != 1)
                        if(!occ.empty())
                        {
                            pos = occ.top();
                            if(avai[pos.row][pos.col] != 1)
                            {
                                avai[pos.row][pos.col] = 0;
                                occ.pop();
                            }
                        }
                    //pop one queen and push in as waste position
                    if(!curr->empty())
                    {
                        pos = curr->top();
                        avai[pos.row][pos.col] = 3;
                        curr->pop();
                        waste.push(pos);
                        j = pos.col + 1;
                        i = pos.row - 1;
                        count--;
                    }
                    //fix queen table as original
                    if(count == 0)
                    {
                        i = -1;
                        while (!waste.empty()) {
                            pos = waste.top();
                            avai[pos.row][pos.col] = 0;
                            waste.pop();
                        }
                    }
            }
        else
            j = 0;
       if(count == numQ)
           return true;
    }
    return false;
}

//this function print the solution of queen if possible
void printTable(int numQ, stack<Position> *curr)
{
    Position pos;
    cout << "  Queens' Table  " << endl;
    cout << endl << "  ";
    for(int i = 0; i < numQ - 1; i++)
           cout << "- " ;
       cout << "-" << endl;
    cout <<  "  ";
    for(int i = 0; i < numQ; i++)
        cout << i+1 << " ";
    cout << endl;
    for(int i = 0; i < numQ && !curr->empty(); i++)
    {
        cout << right << setw(3) << i+1 << "|";
        pos = curr->top();
        for(int j = 0; j < numQ; j++)
        {
            if(j == pos.col)
                cout <<  "Q|";
            else
                cout << " |";
        }
        curr->pop();
        cout << endl;
    }
    cout <<  "  ";
    for(int i = 0; i < numQ-1; i++)
        cout << "- " ;
    cout << "-" << endl;

}

int main() {
    Position pos;
    stack<Position> curr ;
    int numQ = numberValidation();
    if(checkposition(numQ, pos, &curr))
        printTable(numQ, &curr);
    else
        cout << numQ << " queens don't have solution." << endl;
    return 0;
}

/*Simple output
Please enter the number of Queens you want to play:8

  Queens' Table

  - - - - - - - -
  1 2 3 4 5 6 7 8
1| | | |Q| | | | |
2| |Q| | | | | | |
3| | | | | | |Q| |
4| | |Q| | | | | |
5| | | | | |Q| | |
6| | | | | | | |Q|
7| | | | |Q| | | |
8|Q| | | | | | | |
  - - - - - - - -
*/
