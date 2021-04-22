#include <iostream>
#include "hash_chain.h"
#include <functional>
#include <fstream>
#include "sha256.h"
#include <algorithm>

using std::cout;
using std::endl;
using std::string;

  SHA256 a;

/**
 * @brief Find the password that generate the given hash
 * 
 * @param head 
 * @param hash 
 * @return std::string 
 */
std::string find_passwd(std::string head, std::string hash)
{
  
    using namespace rainbow;
    int index = 0;
    std::string pass = head;
    std::string candidatHash = a(head);

    while (index < CHAIN_LENGTH)
    {
        if (hash == candidatHash)
        {
            return pass;
        }
        pass = Hash_Chain::reduction_function(head.size(), index, candidatHash);
        candidatHash = a(pass);
        index++;
    }
    return "";
}
/**
 * @brief checks is in chain with given head and tail it is a password with given hash if it is returns the password otherwise returns empty string . 
 * 
 * @param hash the hash of a password to crack
 * @param head the head of a chain .
 * @param tail the tail of a chain .
 * @return std::string the password that generates the given hash ;
 */
std::string find_passwd(std::string hash, std::string head, std::string tail)
{
    using namespace rainbow;
    int i = CHAIN_LENGTH;
    //std::cout << "tail : "<< tail  << std::endl;

    while (i > 0)
    {
        std::string candidatHashc = hash;
        int tmp = i;
        // std::cout << "i :" << i << std::endl;
        while (tmp <= CHAIN_LENGTH)
        {
            //std::cout << "tmp :" << tmp << std::endl;
            //std::cout << "candidatHashc :" << candidatHashc << std::endl;
            std::string temp = Hash_Chain::reduction_function(tail.size(), tmp, candidatHashc);
            //std::cout <<"temp :"<< temp << std::endl;

            if (temp == tail)
            {

                return find_passwd(head, hash);
            }
            candidatHashc = a(temp);
            tmp++;
        }
        //std::cout << "end of while imbrique avec i :" << i << std::endl;
        i--;
    }
    if (a(head) == hash)
    {
        return head;
    }
    if (a(tail) == hash)
    {
        return tail;
    }
    return "";
}

std::string GetRecord(std::ifstream &inFile, int pos, int length)
{
    char buffer[length];
    inFile.clear();
    inFile.seekg((pos * (2 * length) + (pos * 2)), std::ios::beg);
    inFile.read(buffer, length);
    return buffer;
}

bool Binary_Search(const string &filename, string SearchVal, int length, int sizeFile)
{
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        cout << "\n";
        return false ;
    }
    int pos = 0;
    int lowerLimit = 0;
    int recordCount = sizeFile;
    int upperLimit = recordCount;
    while ((lowerLimit < upperLimit)) // Searching as long as it doesn't find it
    {
        pos = (lowerLimit + upperLimit) / 2;
        std::string buffer = GetRecord(file, pos, length);

        if (buffer == SearchVal)
        {
            cout << "Found!";
            lowerLimit = 1; // For stopping (If found!)
            upperLimit = 0; // For stopping
            return true ;
        }
        else if (SearchVal > buffer)
        {
            lowerLimit = pos + 1;
        }
        else if (SearchVal < buffer)
        {
            upperLimit = pos;
        }
    }
    return false ;
}

void find_pwd_in_file(const std::string &if_tail, const std::string &if_crack)
{
    std::ifstream tail_file;
    tail_file.open(if_tail);

    std::ifstream crack_file;
    crack_file.open(if_crack);

    if (tail_file.is_open())
    {
        std::string tail;
        std::string crack;

        int nbLines = std::count(std::istreambuf_iterator<char>(tail_file),
                                 std::istreambuf_iterator<char>(), '\n');
        std::cout << nbLines << std::endl;

        int count = 0;
        int success = 0;
        while (std::getline(crack_file, crack))
        {
            int i = CHAIN_LENGTH;

            while (i >= 0)
            {
                std::string candidatHashc = crack;
                std::string tempS;
                int tmp = i;

                while (tmp <= CHAIN_LENGTH)
                {
                    tempS = rainbow::Hash_Chain::reduction_function(6, tmp, candidatHashc);
                    candidatHashc = a(tempS);
                    tmp++;
                }
                if(Binary_Search(if_tail, tempS, 6, nbLines)){
                    std::string  head  = crack.substr(crack.size() - 6, crack.size());
                    std::cout << head << std::endl;
                    std::string pass = find_passwd(head,crack);
                    std::cout << pass << std::endl;
                }
                i--;
            }
        }
        tail_file.close();
    }
    else
        throw std::runtime_error("Input files could not be opened");
}

int main(int argc, char *argv[])
{
    find_pwd_in_file(argv[1], argv[2]);
    return 0;
}
