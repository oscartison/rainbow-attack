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
        if (hash.compare(candidatHash) == 0)
        {
            return pass;
        }
        pass = Hash_Chain::reduction_function(head.size(), index, candidatHash);
        candidatHash = a(pass);
        index++;
    }
    return "";
}

std::string GetHead(std::ifstream &inFile, int pos, int length)
{
    char buffer[length];
    inFile.clear();
    inFile.seekg((pos * (2 * length) + (pos * 2) + length + 1), std::ios::beg);
    inFile.read(buffer, length);
    return buffer;
}

std::string GetTail(std::ifstream &inFile, int pos, int length)
{
    char buffer[length];
    inFile.clear();
    inFile.seekg((pos * (2 * length) + (pos * 2)), std::ios::beg);
    inFile.read(buffer, length);
    return buffer;
}

std::string Binary_Search(const string &filename, string SearchVal, int length, int sizeFile)
{
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        cout << "\n";
        return "" ;
    }
    int pos = 0;
    int lowerLimit = 0;
    int recordCount = sizeFile;
    int upperLimit = recordCount;
    while ((lowerLimit < upperLimit)) 
    {
        pos = (lowerLimit + upperLimit) / 2;
        std::string buffer = GetTail(file, pos, length);

        if (buffer == SearchVal)
        {
            cout << "Found!" <<std::endl;
            lowerLimit = 1; 
            upperLimit = 0;
            return GetHead(file,pos,length) ;
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
    return "" ;
}

void find_pwd_in_file(const std::string &if_tail, const std::string &if_crack, int length)
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

        while (std::getline(crack_file, crack))
        {
            int i = CHAIN_LENGTH;
            bool cont = true;

            while (i >= 0 && cont)
            {
                std::string candidatHashc = crack;
                std::string tempS;
                int tmp = i;

                while (tmp < CHAIN_LENGTH && cont)
                {
                    tempS = rainbow::Hash_Chain::reduction_function(length, tmp, candidatHashc);
                    candidatHashc = a(tempS);
                    tmp++;
                }
                std::string head = Binary_Search(if_tail, tempS, length, nbLines);
                if(head.compare("") != 0){
                    std::string pass = find_passwd(head,crack);
                    std::cout << crack << ":"<< pass << std::endl;
                    cont = false;
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
      std::ifstream tail_file;
    tail_file.open(argv[1]);

    find_pwd_in_file(argv[1], argv[2], 6);
    return 0;
}
