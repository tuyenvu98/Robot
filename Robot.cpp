#include <iostream>
#include <string.h>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

const vector<string> moveTypes = {"MOVE_TO","LINE_TO"};
int dimension; 

// strip spaces in string 
string stripstr(string str)
{
    if (str.find(" "))
    {
       str.replace(str.find(" "),1, "");
       cout <<"Replaced : "<< str<< endl;
    }
    return str;
}

bool validateCmd (string moveType, int x, int y)
{
    if (x > dimension ||y > dimension ||x <0 || y<0)
    {
        cout << "Position not valid" <<endl;
        return false;
    }
    bool isMoveType = false;
    for (int i =0; i < moveTypes.size();i++)
    {
        if (moveTypes[i] == moveType )
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

map<string, string> parseCmd(string cmd)
{
    map<string, string> commandMap;
    int spacePos = cmd.find(" ");
    int commaPos = cmd.find(",");

    if (spacePos > 0){
        commandMap ["moveType"] = cmd.substr(0,spacePos);
        if(commaPos>spacePos)
        {
            commandMap ["y"]= cmd.substr(commaPos+1,cmd.length()-1);
            cmd.replace(commaPos,cmd.length() - commaPos-1, "");
            commandMap ["x"]= cmd.substr(spacePos+1,cmd.length());
        }
        else 
            commandMap ["x"]= cmd.substr(spacePos+1,cmd.length());
    }

    return commandMap;
    
}

bool checkCrossed(int x, int y, float minX, float minY, int diffX, int diffY)
{

    if (((diffX*(y-minY)-diffY*(x - minX)) * (diffX*(y+1-minY)-diffY*(x+1 - minX)) < 0)
    ||((diffX*(y+1-minY)-diffY*(x - minX)) * (diffX*(y-minY)-diffY*(x+1 - minX)) < 0))
    {
        return true;
    }
    else 
        return false;
}

class Robot
{
    public:
        int getX()
        {
            return x;
        }
        int getY()
        {
            return y;
        }
        // Move to return a map of crossed positions (just old and new position)
        std::vector<std::vector<int>> moveTo(int x, int y)
        {
            std::vector<std::vector<int>> crossPos; 
            crossPos.push_back({this->x,this->y});
            crossPos.push_back({x,y});
            this->x = x;
            this->y = y;
            return crossPos;
        }
        // Line move return a map of crossed positions
        std::vector<std::vector<int>> lineTo(int x, int y)
        {
            std::vector<std::vector<int>> crossPos; 
            int minX = min(x, this->x);
            int minY = min(y, this->y);
            int maxX = max(x, this->x);
            int maxY = max(y, this->y);
            int diffX = maxX - minX;
            int diffY = maxY -minY;
            for (int i = minX; i<= maxX; i++)
             for (int j = minY; j<= maxY; j++)
             {
                if (checkCrossed(i, j, minX + 0.5, minY + 0.5, diffX, diffY))
                {
                    crossPos.push_back({i,j});
                }
             }
             
            this->x = x;
            this->y = y;
            return crossPos;
            
        }
    private :
        int x = 0;
        int y = 0;
        
};

int main() {
    // Create a text string, which is used to output the text file
    string dimensionLine;
    string command;
    
    
    // Read from the text file
    ifstream cmdFile("command.txt");
    if (!cmdFile.good())
    {
        cout << "File is not valid." << endl;
        return 1;
    }
    getline (cmdFile, dimensionLine);
    map<string, string> dimensionLineMap = parseCmd(dimensionLine);
    if (dimensionLineMap["moveType"].compare("DIMENSION") == 0)
        stringstream(dimensionLineMap["x"]) >> dimension;
    else 
    {
        cout << "Dimension not found." << endl;
        return 1;
    }
    cout << "Dimension : "<< dimension<< endl;
    Robot *robot = new Robot();
    
    // Use a while loop to read the command file line by line
    while (getline (cmdFile, command)) {
        map<string, string> commandMap = parseCmd(command);
        if (commandMap["moveType"].compare("DIMENSION") != 0)
        {
            string mType = commandMap ["moveType"];
            int oldX = robot->getX();
            int oldY = robot->getY();
            int x,y;
            stringstream(commandMap["x"]) >> x;
            stringstream(commandMap["y"]) >> y;
            if (!validateCmd(mType, x, y))
            {
                cout<< "Skipped." << endl;
                continue;
            }
            std::vector<std::vector<int>> crossed;
            if (mType == "LINE_TO")
                crossed = robot->lineTo(x,y);
            else if (mType == "MOVE_TO")
                crossed = robot ->moveTo(x,y);
            
            cout<< "Robot " <<mType<< " from :" << oldX << "," << oldY << " to " << robot->getX() << "," << robot->getY() <<endl;
            ostringstream ostr;
            ostr << "Crossed positions : ";
            for (int i = 0; i < crossed.size(); i++)
                ostr<< crossed[i][0]<< "," << crossed[i][1] << "  ";
            cout << ostr.str()<< endl;
        }

    }

    // Close the file
   cmdFile.close();

   return 0;
}