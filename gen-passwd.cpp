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

	if (!myfile)
	{
		std::cout << "Unable to open the file" << std::endl;
	}

	while (std::getline(myfile, line))
	{
		fileLines.push_back(line);
	}

	sort(fileLines.begin(), fileLines.end()); 
	std::ofstream newfile(of_pwd);
	for (std::string &s : fileLines)
	{
		newfile << s << std::endl;
	};
}

int main(int argc, char *argv[])
{

	int n = std::thread::hardware_concurrency();

	ThreadPool t(n);

	std::vector<std::future<void>> v;
	std::cout << n << " concurrent threads are supported.\n";

	for (int i = 0; i < n; i++)
	{
		v.push_back(t.enqueue(rainbow::mass_generate, 100000000 / n, 8, "table6.txt"));
	}

	for (auto &&future : v)
	{
		future.wait();
	}


	sortFile("table6.txt");
}
