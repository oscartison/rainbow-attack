#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H
#include <string>
#include "sha256.h"
#include <iostream>
#include <functional>
#include <cmath>
#define CHAIN_LENGTH 1000
class Hash_Chain{
    std::string head ;
    std::string tail ;
    void generateChain();
    public:
    std::string static reduction_function(int lenghtOfPasswd,int nbOfReduction, std::string &hash);
    Hash_Chain(int lenght);
    std::string to_string();
};

#endif // HASh_CHAIN_H