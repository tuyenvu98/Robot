#include <string.h>
#include <vector>
using namespace std;
class Board
{
    public:
        Board(vector<vector<int>>,int);
        void show();
    private:
        int dimension;
        vector<vector<int>> crossedPos;
    
};
