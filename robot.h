#include <vector>
#include <string>
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
        
        void moveTo(int , int );

        void lineTo(int , int );
        
        void printLog(int, int, string);
        
        std::vector<std::vector<int>> crossedPos;
    private :
        int x = 0;
        int y = 0;
        
};
