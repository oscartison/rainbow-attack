#include <iostream>
#include "passwd-utils.hpp"
#include "threadpool.hpp"
#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <mutex>
#include <future>
#include <string>

void sortFile(const std::string &of_pwd)
{
	std::vector<std::string> fileLines;
	std::string line;
	std::ifstream myfile(of_pwd);

	//stack overflow example
	if (!myfile) //test the file
	{
		std::cout << "Unable to open the file" << std::endl;
	}

	while (std::getline(myfile, line))
	{
		fileLines.push_back(line);
		//cout << line << '\n';
	}

	sort(fileLines.begin(), fileLines.end()); //sorting string vector
	std::ofstream newfile(of_pwd);
	for (std::string &s : fileLines)
	{

		newfile << s << std::endl;
	};
}

int main(int argc, char *argv[])
{
	if (argc != 5)
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

	unsigned int n = std::thread::hardware_concurrency();

	ThreadPool t(n); //a pool of 8 threads

	std::vector<std::future<void>> v;
	std::cout << n << " concurrent threads are supported.\n";

	for (int i = 0; i < n; i++)
	{
		v.push_back(t.enqueue(rainbow::mass_generate, c, mc, MC, argv[4])); //I could push any function here, not only (int)(*f)(int,int)
	}

	for (auto &&future : v)
	{
		future.wait();
	}

	sortFile(argv[4]);
}
