#include "board.h"
#include <iostream>
using namespace std;
Board::Board(vector<vector<int>> cPos, int size)
{
    dimension = size;
    crossedPos = cPos;
}

void Board::show()
{
    cout << " ";
    for(int j =0; j<dimension; j++)
        cout <<" " <<j ;
    cout<< endl;
    for(int i =0; i<dimension;i++)
    {
        cout << i << "|";
        for(int j =0; j<dimension; j++)
        {
            string str = "  ";
            for (int m = 0; m < crossedPos.size(); m++)
                if (crossedPos[m][0] == j && crossedPos[m][1] == i)
                    {
                        str = "X ";
                    }
            cout << str;
        }
        cout<< endl;
    }
}

