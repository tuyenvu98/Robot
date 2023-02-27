#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;
class Command
{
    public:
        int x;
        int y;
        string mType;
        Command(string);
        bool validateCmd(int dimension);
};
