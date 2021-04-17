#include "hash_chain.h"
#include "passwd-utils.hpp"
#include <iostream>
#include <functional>
#include <cmath>
Hash_Chain::Hash_Chain(int lenght)
{
    head = rainbow::generate_passwd(lenght);
    generateChain();
}
void Hash_Chain::generateChain(){
    std::string hash ;
    std::string passwd ;
    int i = 0 ; 
    hash = sha256(head);
    while (i<CHAIN_LENGTH)
    {
        passwd = reduction_function(head.size(),i,hash);
        hash=sha256(passwd);
        i++;
    }
    tail = passwd;
    
}
std::string Hash_Chain::reduction_function(int lenghtOfPasswd, int nbOfReduction, std::string &hash)
{
    std::string charset ="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string passwd ;
    std::size_t hash_int = std::hash<std::string>{}(hash);
    hash_int = (hash_int + nbOfReduction) % (std::size_t)std::abs(std::pow(charset.size(), lenghtOfPasswd));
    for (int i = 0; i < lenghtOfPasswd; i++)
    {
        passwd = passwd + (charset.at((hash_int *i )% charset.size()));
    }
    return passwd ;
}

std::string Hash_Chain::to_string()
{
    return head+ ":" + tail;
}