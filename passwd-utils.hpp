#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include "hash_chain.h"
#include "random.hpp"
#include "sha256.h"

namespace rainbow {

std::mutex mtx;           // mutex for critical section


void mass_generate(int n, int mc, int MC, const std::string& of_pwd)
{
	std::ofstream passwd_file;
	passwd_file.open(of_pwd,std::ios::app);


	if(passwd_file.is_open())
	{		
		// ici tant que pas 10 Gb
		for(int i = 0; i < n; i++)
		{
			
			mtx.lock();
			rainbow::Hash_Chain hc = rainbow::Hash_Chain(rainbow::random(mc, MC));
			passwd_file << hc.tail() << ":" << hc.head() << std::endl;
			mtx.unlock();

		
		}

		passwd_file.close();
	}
	else
		throw std::runtime_error("Output files could not be opened");
}

inline bool check_pwd(const std::string& pwd, const std::string& hash)
{
	return sha256(pwd) == hash;
}

double mass_check(const std::string& if_pwd, const std::string& if_hash)
{
	std::ifstream passwd_file;
	passwd_file.open(if_pwd);

	std::ifstream hash_file;
	hash_file.open(if_hash);

	if(passwd_file.is_open() && hash_file.is_open())
	{		
		std::string pass;
		std::string hash;

		int count = 0;
		int success = 0;
		while(std::getline(passwd_file, pass) && std::getline(hash_file, hash))
		{
			count++;
			if(check_pwd(pass, hash))
				success++;
		}

		passwd_file.close();
		hash_file.close();

		return (static_cast<double>(success) / count) * 100;
	}
	else
		throw std::runtime_error("Input files could not be opened");
}

}//rainbow namespace
