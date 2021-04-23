#include <iostream>
#include "hash_chain.h"
#include <functional>
#include <fstream>
#include "sha256.h"
#include <algorithm>
#include "threadpool.hpp"
#include <queue>
#include <vector>
#include <iterator>
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
std::string find_passwd(std::string &head, std::string &hash, int &length)
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
        pass = Hash_Chain::reduction_function(length, index, candidatHash);
        candidatHash = a(pass);
        index++;
    }
    return "";
}

std::string GetHead(std::ifstream &inFile, int &pos, int &length)
{
    char buffer[length];
    inFile.clear();
    inFile.seekg((pos * (2 * length) + (pos * 2) + length + 1), std::ios::beg);
    inFile.read(buffer, length);
    return buffer;
}

std::string GetTail(std::ifstream &inFile, int &pos, int &length)
{
    char buffer[length];
    inFile.clear();
    inFile.seekg((pos * (2 * length) + (pos * 2)), std::ios::beg);
    inFile.read(buffer, length);
    return buffer;
}

std::string Binary_Search(const string &filename, string &SearchVal, int &length, int &sizeFile)
{
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        cout << "\n";
        return "";
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
            cout << "Found!" << std::endl;
            lowerLimit = 1;
            upperLimit = 0;
            return GetHead(file, pos, length);
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
    return "";
}

void find_pwd_in_file(const std::string &if_tail, std::vector<std::string> &vecHash, int &length)
{
    std::ifstream tail_file;
    tail_file.open(if_tail);

    if (tail_file.is_open())
    {
        std::string tail;

        int nbLines = std::count(std::istreambuf_iterator<char>(tail_file),
                                 std::istreambuf_iterator<char>(), '\n');

       for(auto crack: vecHash)
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
                if (head.compare("") != 0)
                {
                    std::string pass = find_passwd(head, crack, length);
                    std::cout << crack << ":" << pass << std::endl;
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

std::vector<std::vector<std::string>> divideFile(const std::string &if_crack, size_t &nbThread)
{
    std::ifstream crack_file;
    crack_file.open(if_crack);

    std::vector<std::vector<std::string>> output;

    std::vector<std::string> cracks;

    std::copy(std::istream_iterator<std::string>(crack_file),
              std::istream_iterator<std::string>(),
              std::back_inserter(cracks));

    size_t length = cracks.size() / nbThread;
    size_t remain = cracks.size() % nbThread;

    std::size_t begin = 0;
    std::size_t end = 0;
//https://stackoverflow.com/questions/6861089/how-to-split-a-vector-into-n-almost-equal-parts
    for (size_t i = 0; i < std::min(nbThread, cracks.size()); ++i)
    {
        end += (remain > 0) ? (length + !!(remain--)) : length;

        output.push_back(std::vector<std::string>(cracks.begin() + begin, cracks.begin() + end));

        begin = end;
    }
    return output;
}

int main(int argc, char *argv[])
{
    if (argc == 4)
    {
        int n = std::thread::hardware_concurrency();
        ThreadPool t(n);
        std::vector<std::future<void>> v;
        std::cout << n << " concurrent threads are supported.\n";
        int length = atoi(argv[1]);
        std::string rt = argv[2];
        std::string to_crack = argv[3];

        size_t nbVectors = n;

        std::vector<std::vector<std::string>> vec = divideFile(to_crack, nbVectors);

        for (int i = 0; i < n; i++)
        {
            v.push_back(t.enqueue(find_pwd_in_file, rt, vec[i], length));
        }

        for (auto &&future : v)
        {
            future.wait();
        }
    }
    else
    {
        std::cout << "erreur" << std::endl;
    }

    return 0;
}
