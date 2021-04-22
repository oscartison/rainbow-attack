#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H
#include <string>
#include "sha256.h"
#include <iostream>
#include <functional>
#include <cmath>
#include <map>
#define CHAIN_LENGTH 10000

namespace rainbow {
class Hash_Chain{
    std::string head_ ;
    std::string tail_ ;
    void generateChain();
    public:
    std::string static reduction_function(int lenghtOfPasswd,int nbOfReduction, std::string &hash);
    std::string generate_passwd(int length);
    public:
    std::string head() ;
    std::string tail() ;
    Hash_Chain(int lenght);
    std::string to_string();
};
}

#endif // HASh_CHAIN_H