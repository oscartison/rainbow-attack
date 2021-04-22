#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include "hash_chain.h"
#include "random.hpp"
#include "sha256.h"

namespace rainbow {

std::mutex mtx;           // mutex for critical section


void mass_generate(std::size_t n, int mc, int MC, const std::string& of_pwd)
{
	std::ofstream passwd_file;
	passwd_file.open(of_pwd,std::ios::app);


	if(passwd_file.is_open())
	{		
		for(std::size_t i = 0; i < n; i++)
		{
			
			rainbow::Hash_Chain hc = rainbow::Hash_Chain(rainbow::random(mc, MC));
			mtx.lock();
			passwd_file << hc.tail() << ":" << hc.head() << std::endl;
			mtx.unlock();
		}

		passwd_file.close();
	}
	else
		throw std::runtime_error("Output files could not be opened");
}

}//rainbow namespace
