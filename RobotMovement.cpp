#include <fstream>
#include "robot.h"
#include "command.h"
#include "board.h"

using namespace std;


int main() {

    // Read from the text file
    ifstream cmdFile("command.txt");
    if (!cmdFile.good())
    {
        cout << "File is not valid." << endl;
        return 1;
    }

    Robot *robot = new Robot();
    int oldX = robot->getX();
    int oldY = robot->getY();
    static int dimension;
    // Use a while loop to read the command file line by line
    string command;
    while (getline (cmdFile, command)) {
        Command cmd(command);
        if (cmd.mType =="DIMENSION")
            dimension  = cmd.x;
        else
        {
            if (!cmd.validateCmd(dimension))
            {
                cout<< "Skipped." << endl;
                continue;
            }
            if (cmd.mType == "LINE_TO")
                robot->lineTo(cmd.x,cmd.y);
            else if (cmd.mType== "MOVE_TO")
                robot ->moveTo(cmd.x,cmd.y);
            robot->printLog(oldX, oldY, cmd.mType);
            Board brd(robot->crossedPos,dimension);
            brd.show();
            
        }

    }

    // Close the file
   cmdFile.close();

   return 0;
}