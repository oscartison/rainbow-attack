#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H
#include <string>
<<<<<<< HEAD
#include "sha256.h"
#include <iostream>
#include <functional>
#include <cmath>
=======
#include <map>
>>>>>>> 5f19106b888a23922e9011caf0db071518865597
#define CHAIN_LENGTH 1000

namespace rainbow {
class Hash_Chain{
    std::string head_ ;
    std::string tail_ ;
    void generateChain();
<<<<<<< HEAD
    public:
    std::string static reduction_function(int lenghtOfPasswd,int nbOfReduction, std::string &hash);
=======
    std::string generate_passwd(int length);
    std::string reduction_function(int lenghtOfPasswd,int nbOfReduction, std::string &hash);
    public:
    std::string head() ;
    std::string tail() ;
>>>>>>> 5f19106b888a23922e9011caf0db071518865597
    Hash_Chain(int lenght);
    std::string to_string();
};
}

#endif // HASh_CHAIN_H