#include <iostream>
#include "hash_chain.h"
#include <functional>
#include <fstream>
using std::cout;
using std::endl;
using std::string;
/**
 * @brief Find the password that generate the given hash
 * 
 * @param head 
 * @param hash 
 * @return std::string 
 */
std::string find_passwd(std::string head, std::string hash){
    using namespace rainbow;
    int index =  0;
    std::string pass = head;
    std::string candidatHash = sha256(head);

    while(index<CHAIN_LENGTH){
        if (hash == candidatHash)
        {
            return pass;
        }
        pass = Hash_Chain::reduction_function(head.size(), index, candidatHash);
        candidatHash = sha256(pass);
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
    using namespace rainbow ;
    int i = CHAIN_LENGTH;
    //std::cout << "tail : "<< tail  << std::endl;

    while (i > 0)
    {
        std::string candidatHashc = hash ;
        int tmp = i ;
       // std::cout << "i :" << i << std::endl;
        while (tmp <= CHAIN_LENGTH)
        {
            //std::cout << "tmp :" << tmp << std::endl;
            //std::cout << "candidatHashc :" << candidatHashc << std::endl;
            std::string temp = Hash_Chain::reduction_function(tail.size(), tmp, candidatHashc);
            //std::cout <<"temp :"<< temp << std::endl;

            if(temp == tail ){     
               
                return find_passwd(head, hash);
            }
            candidatHashc = sha256(temp);
            tmp++;
        }
        //std::cout << "end of while imbrique avec i :" << i << std::endl;
        i--;
    }
    if(sha256(head)==hash){
        return head ;
    }
    if (sha256(tail) == hash)
    {
        return tail;
    }
    return "" ;
}

double find_pwd_in_file(const std::string& if_head, const std::string& if_tail,const std::string& if_crack )
{
	std::ifstream head_file;
	head_file.open(if_head);

	std::ifstream tail_file;
	tail_file.open(if_tail);

    std::ifstream crack_file;
	crack_file.open(if_crack);

	if(head_file.is_open() && tail_file.is_open())
	{		
		std::string head;
		std::string tail;
        std::string crack;

        int count = 0;
        int success = 0;
        while (std::getline(crack_file, crack))
        {

            while(std::getline(head_file, head) && std::getline(tail_file, tail))
		    {
			    count++;
			    if(find_passwd(crack,head, tail).compare("") != 0){
				    success++;
                    std::cout << "1 succes" << std::endl;
                }
		    }

		head_file.close();
		tail_file.close();
        }
		return (static_cast<double>(success) / count) * 100;
	}
	else
		throw std::runtime_error("Input files could not be opened");
}

int main(int argc, char *argv[])
{
    rainbow::Hash_Chain c{6};
    //std::cout << c.to_string() << std::endl ;
    //0HYp6N this password had generate this hash .
    std::string temp = "27de0a9c4aa8ff2719e01ff0a986ee386aa7cfe0fca1f37509a922641573657c";
    std::string head = c.to_string().substr(0, 6);
    std::string tail = c.to_string().substr(7, 12);

    std::cout <<"finded : "<<find_passwd(temp, head,tail) << std::endl;


    //std::cout << find_pwd_in_file(argv[1],argv[2],argv[3]) << std::endl;
    return 0;
}
