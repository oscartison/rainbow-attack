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

	sort(fileLines.begin(), fileLines.end()); 
	std::ofstream newfile(of_pwd);
	for (std::string &s : fileLines)
	{

		newfile << s << std::endl;
	};
}

int main(int argc, char *argv[])
{

	unsigned int n = std::thread::hardware_concurrency();

	ThreadPool t(n); //a pool of 8 threads

	std::vector<std::future<void>> v;
	std::cout << n << " concurrent threads are supported.\n";

	for (int i = 0; i < n; i++)
	{
		v.push_back(t.enqueue(rainbow::mass_generate, 18000 / n, 6, 6, "table6.txt"));
		//v.push_back(t.enqueue(rainbow::mass_generate, 250000000 / n, 7, 7, "table7.txt"));
		//v.push_back(t.enqueue(rainbow::mass_generate, 15000000000, 8, 8, "table8.txt")); //I could push any function here, not only (int)(*f)(int,int)
	}

	for (auto &&future : v)
	{
		future.wait();
	}

	sortFile("table6.txt");
	//sortFile("table7.txt");
	//sortFile("table8.txt");

}
