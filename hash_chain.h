#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H
#include <string>
#define CHAIN_LENGTH 1000
class Hash_Chain{
    std::string head ;
    std::string tail ;
    void generateChain();
    std::string reduction_function(int lenghtOfPasswd,int nbOfReduction, std::string &hash);
    public:
    Hash_Chain(int lenght);
    std::string to_string();
};

#endif // HASh_CHAIN_H