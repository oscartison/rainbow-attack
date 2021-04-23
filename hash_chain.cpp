#include "hash_chain.h"
#include "random.hpp"

#include <iostream>
#include <functional>
#include <cmath>
#include <cstring>
#include <mutex>

namespace rainbow
{

    std::mutex mtx2; // mutex for critical section

    std::string Hash_Chain::generate_passwd(int &length)
    {
        static const std::string char_policy = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890";
        static const int c_len = char_policy.length();

        char str[length + 1];
        for (int i = 0; i < length; i++)
            str[i] = char_policy[rainbow::random(0, c_len - 1)];
        str[length] = '\0';

        return std::string(str);
    }

    std::string Hash_Chain::head()
    {
        return head_;
    }

    std::string Hash_Chain::tail()
    {
        return tail_;
    }

    Hash_Chain::Hash_Chain(int &lenght):
    size_{lenght},
    head_{generate_passwd(lenght)}
    {
        generateChain();
    }

    void Hash_Chain::generateChain()
    {
        SHA256 a;
        std::string hash;
        std::string&& passwd = std::string(head_);
        int size = passwd.size();
        int i = 0;

        while (i < CHAIN_LENGTH)
        {
            
            hash = a(passwd);
            passwd = reduction_function(size, i, hash);

            i++;
        }

        tail_ = passwd;
    }
    std::string Hash_Chain::reduction_function(int &lenghtOfPasswd, int &nbOfReduction, std::string &hash)
    {
        static const std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        static const std::size_t p = (std::size_t)std::abs(std::pow(charset.size(), lenghtOfPasswd));
        std::size_t hash_int = (std::hash<std::string>{}(hash) + nbOfReduction) % p;

        std::string encoded = std::string(lenghtOfPasswd,'c');
        for (int i = 0; i < lenghtOfPasswd; i++)
        {
            int r = hash_int % 62;
            hash_int /= 62;
            encoded[i] = charset[r];
        }

        return encoded;
    }

    std::string Hash_Chain::to_string()
    {
        std::string s = std::string((((size_) *2) + 2), ':');
        s.replace(0,size_ - 1,tail_);
        s.replace(size_ + 1, size_ * 2, head_);
        s.replace(size_ *2 +1,size_*2 + 2, "\n");

        return s;
    }
}