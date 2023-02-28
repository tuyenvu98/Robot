#include <vector>
#include <string>
#include "command.h"
using namespace std;
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
        
        void printLog(int, int, string);
        
        std::vector<std::vector<int>> crossedPos;
        
        void makeMove (Command);
    private :
        int x = 0;
        int y = 0;
        
};
