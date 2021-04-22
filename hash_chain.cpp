#include "hash_chain.h"
#include "random.hpp"

#include <iostream>
#include <functional>
#include <cmath>
#include <mutex>

namespace rainbow {


std::mutex mtx2;           // mutex for critical section

std::string Hash_Chain::generate_passwd(int length)
{
	static const std::string char_policy = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890";
	static const int c_len = char_policy.length();

	char str[length + 1];
	for(int i = 0; i < length; i++)
		str[i] = char_policy[rainbow::random(0, c_len - 1)];
	str[length] = '\0';

	return std::string(str);
}

    std::string Hash_Chain::head() {
        return head_;
    }

     std::string Hash_Chain::tail() {
        return tail_;
    }


Hash_Chain::Hash_Chain(int lenght)
{
    head_ = generate_passwd(lenght);
    generateChain();
}
void Hash_Chain::generateChain(){
    std::string hash ;
    std::string passwd = head_;
    int i = 0 ; 

    while (i<CHAIN_LENGTH)
    {
        SHA256 a;
        hash=a(passwd);
        passwd = reduction_function(head_.size(),i,hash);

        i++;
    }

    tail_ = passwd;
    
}
std::string Hash_Chain::reduction_function(int lenghtOfPasswd, int nbOfReduction, std::string &hash)
{
    std::string charset ="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::size_t hash_int = std::hash<std::string>{}(hash);
    
    hash_int = (hash_int + nbOfReduction) % (std::size_t)std::abs(std::pow(charset.size(), lenghtOfPasswd));
    
    // for (int i = 0; i < lenghtOfPasswd; i++)
    // {
    //     passwd = passwd + (charset.at((hash_int * std::pow(i, i))% charset.size()));
    // }


   std::string encoded = "";
   for (int i = 0; i < lenghtOfPasswd; i++) {
      int r = hash_int % 62;
      hash_int /= 62;
      encoded = charset[r] + encoded;

   } 

    return encoded ;
}

std::string Hash_Chain::to_string()
{
    return tail_ +":" + head_;
}
}