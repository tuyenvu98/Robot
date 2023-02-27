#include <fstream>
#include "robot.h"
#include "command.h"
#include "board.h"

using namespace std;

int dimension; 

int main() {

    // Read from the text file
    ifstream cmdFile("command.txt");
    if (!cmdFile.good())
    {
        cout << "File is not valid." << endl;
        return 1;
    }
    
    string dimensionLine;
    getline (cmdFile, dimensionLine);
    Command dimensionLineMap(dimensionLine);
    if (dimensionLineMap.mType =="DIMENSION")
        dimension = dimensionLineMap.x;
    else 
    {
        cout << "Dimension not found." << endl;
        return 1;
    }
    Robot *robot = new Robot();
    int oldX = robot->getX();
    int oldY = robot->getY();
    
    // Use a while loop to read the command file line by line
    string command;
    while (getline (cmdFile, command)) {
        Command cmd(command);
        if (cmd.mType !="DIMENSION")
        {
            string mType = cmd.mType;
            if (!cmd.validateCmd(dimension))
            {
                cout<< "Skipped." << endl;
                continue;
            }
            if (mType == "LINE_TO")
                robot->lineTo(cmd.x,cmd.y);
            else if (mType == "MOVE_TO")
                robot ->moveTo(cmd.x,cmd.y);
            robot->printLog(oldX, oldY, mType);
            Board brd(robot->crossedPos,dimension);
            brd.show();
            
        }

    }

    // Close the file
   cmdFile.close();

   return 0;
}