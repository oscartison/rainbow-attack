#include <iostream>
#include "hash_chain.h"
#include <functional>
using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
    Hash_Chain c{6};
    std::cout << c.to_string() << std::endl ;
    return 0;
}
