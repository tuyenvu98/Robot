#include "command.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
const vector<string> moveTypes = {"MOVE_TO","LINE_TO"};

Command::Command(string cmd)
{
    int spacePos = cmd.find(" ");
    int commaPos = cmd.find(",");
    string xStr, yStr;
    if (spacePos > 0){
        mType = cmd.substr(0,spacePos);
        if(commaPos>spacePos)
        {
            stringstream(cmd.substr(commaPos+1,cmd.length()-1)) >> y;
            cmd.replace(commaPos,cmd.length() - commaPos, "");
            stringstream(cmd.substr(spacePos+1,cmd.length())) >>x;
        }
        else 
            stringstream(cmd.substr(spacePos+1,cmd.length())) >>x;
    }
    
}

bool Command::validateCmd(int dimension)
{
    if (x > dimension ||y > dimension ||x <0 || y<0)
    {
        cout << "Position not valid" <<endl;
        return false;
    }
    bool isMoveType = false;
    for (int i =0; i < moveTypes.size();i++)
    {
        if (moveTypes[i] == mType )
        {
            isMoveType =true;
            break;
        }
    }
    if(isMoveType ==false)
    {
        cout << "Move type not valid" <<endl;
        return false;
    }
    return true;
}