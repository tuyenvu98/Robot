#include "robot.h"
#include <iostream>
#include <sstream>
using namespace std;

bool checkCrossed(int x, int y, float minX, float minY, int diffX, int diffY)
{

    if (((diffX*(y-minY)-diffY*(x - minX)) * (diffX*(y+1-minY)-diffY*(x+1 - minX)) < 0)||((diffX*(y+1-minY)-diffY*(x - minX)) * (diffX*(y-minY)-diffY*(x+1 - minX)) < 0))
    {
        return true;
    }
    else 
        return false;
}
// Move to return a map of crossed positions (just old and new position)
void Robot::moveTo(int a, int b)
{
    crossedPos.clear();
    crossedPos.push_back({x,y});
    crossedPos.push_back({a,b});
    x = a;
    y= b;

}
// Line move return a map of crossed positions
void Robot::lineTo(int a, int b)
{
    crossedPos.clear();
    int minX = min(a, x);
    int minY = min(b, y);
    int maxX = max(a, x);
    int maxY = max(b, y);
    int diffX = maxX - minX;
    int diffY = maxY -minY;
    for (int i = minX; i<= maxX; i++)
        for (int j = minY; j<= maxY; j++)
            {
                if (checkCrossed(i, j, minX + 0.5, minY + 0.5, diffX, diffY))
                {
                    crossedPos.push_back({i,j});
                }
            }
             
    x = a;
    y = b;
            
}

void Robot::printLog(int oldX, int oldY, string mType)
{
    cout<< "Robot " <<mType<< " from :" << oldX << "," << oldY << " to " << x << "," << y <<endl;
    ostringstream ostr;
    ostr << "Crossed positions : ";
    for (int i = 0; i < crossedPos.size(); i++)
        ostr<< crossedPos[i][0]<< "," << crossedPos[i][1] << "  ";
    cout << ostr.str()<< endl;
}
