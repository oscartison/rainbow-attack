#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H
#include <string>
#include "sha256.h"
#include <iostream>
#include <functional>
#include <cmath>
#include <map>

#define CHAIN_LENGTH 50000

namespace rainbow
{
    
    
   /**
     * @brief This class represent a chain of passwords hashes of which we have stored only the head and tail given
     * that the intermediate is calculable .
     * 
     */
    class Hash_Chain
    {
        
        std::string head_;
        std::string tail_;
        const int size_;
        /**
         * @brief generates a chain of length "CHAIN_LENGTH" using the reduction function and set the tail of chain .
         * 
         */
        void generateChain();

    public:

        /**
         * @brief Creates a valid alphanumeric (lower and upper case) of length received in parameters a password 
         * using the given hash  
         * and returns them .
         * @param lenghtOfPasswd an integer .
         * @param nbOfReduction an integer .
         * @param hash string version of hash calculated usind sha-256 function .
         * @return std::string 
         */
        std::string static reduction_function(int& lenghtOfPasswd, int & nbOfReduction, std::string &hash);

        /**
         * @brief generates a random password using alphanumeric (lower and upper case) charset of given, length .
         * 
         * @param length an integer .
         * @return std::string password random generated .
         */
        std::string generate_passwd(int& length);

        /**
         * @brief A simple getter .
         * 
         * @return std::string version of head .
         */
        std::string head();

        /**
         * @brief A simple getter .
         * 
         * @return std::string version of tail .
         */
        std::string tail();

        /**
         * @brief Construct a new Hash_Chain object with given lenght for each element in chain . 
         * 
         * @param lenght an integer .
         */
        Hash_Chain(int& lenght);
        
        /**
         * @brief Returns string version of a chain .
         * 
         * @return std::string version of a chain .
         */
        std::string to_string();
    };
}

#endif // HASh_CHAIN_H
