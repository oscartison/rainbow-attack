#include <iostream>
#include "more efficient sha256/sha256.h"
 
using std::string;
using std::cout;
using std::endl;
 
int main(int argc, char *argv[])
{
    string input = "grape";
    SHA256 hash ;
    string output1 =hash(input);
 
    cout << "sha256('"<< input << "'):" << output1 << endl;
    return 0;
}
