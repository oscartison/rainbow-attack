#include <iostream>
#include "passwd-utils.hpp"
#include "threadpool.hpp"
#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <mutex>
#include <future>

int make_addition(int i, int j)
 {
     return i + j;
 }

int main(int argc, char *argv[])
{
	if(argc != 6)
	{
		std::cerr << "Usage : \"gen-passwd c mc MC of_pwd of_hash\", where" << std::endl
			<< "- c is the size of rainbow table in gb ," << std::endl
			<< "- mc is the minimum number of chars allowed in an alphanumeric password," << std::endl
			<< "- MC is the maximum number of chars allowed in an alphanumeric password," << std::endl
			<< "- of_pwd is the name of the output file where the passwords will be stored" << std::endl
			<< "- of_hash is the name of the output file where the sha-256 hashes of the passwords will be stored" << std::endl;
		return 1;
	}
	//change in size of rainbow table .
	int c = std::stoi(argv[1]);

	int mc = std::stoi(argv[2]);
	int MC = std::stoi(argv[3]);

	ThreadPool t(8); //a pool of 8 threads

    std::vector<std::future<void>> v; 

    for(int i = 0; i < 8; i++){
        v.push_back(t.enqueue(rainbow::mass_generate, c, mc, MC, argv[4], argv[5])); //I could push any function here, not only (int)(*f)(int,int)

	}
	for (auto &&future : v)
	{
		future.wait();
	}
	

	
}
