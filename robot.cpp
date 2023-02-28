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
std::vector<std::vector<int>> moveTo(int oldX,int oldY,int x, int y)
{
    std::vector<std::vector<int>> crossedPos;
    crossedPos.clear();
    crossedPos.push_back({x,y});
    crossedPos.push_back({oldX,oldY});
    return crossedPos;

}
// Line move return a map of crossed positions
std::vector<std::vector<int>> lineTo(int oldX,int oldY,int x, int y)
{
    std::vector<std::vector<int>> crossedPos;
    int minX = min(oldX, x);
    int minY = min(oldY, y);
    int maxX = max(oldX, x);
    int maxY = max(oldY, y);
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
    return crossedPos;
            
}

void Robot::makeMove(Command cmd)
{
    if (cmd.mType == "LINE_TO")
        crossedPos = lineTo(x,y,cmd.x,cmd.y);
    else if (cmd.mType== "MOVE_TO")
        crossedPos = moveTo(x,y,cmd.x,cmd.y);
    
    x = cmd.x;
    y = cmd.y;
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
