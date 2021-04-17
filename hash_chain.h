#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H
#include <string>
#include <map>
#define CHAIN_LENGTH 1000

namespace rainbow {
class Hash_Chain{
    std::string head_ ;
    std::string tail_ ;
    void generateChain();
    std::string generate_passwd(int length);
    std::string reduction_function(int lenghtOfPasswd,int nbOfReduction, std::string &hash);
    public:
    std::string head() ;
    std::string tail() ;
    Hash_Chain(int lenght);
    std::string to_string();
};
}

#endif // HASh_CHAIN_H