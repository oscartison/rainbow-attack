#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include "hash_chain.h"
#include "random.hpp"
#include "sha256.h"

namespace rainbow
{

	std::mutex mtx; // mutex for critical section

	void mass_generate(std::size_t n, int mc, const std::string &of_pwd)
	{
		std::ofstream passwd_file;
		passwd_file.open(of_pwd, std::ios::app);
		if (passwd_file.is_open())
		{
			std::size_t sizeSubString = 10000;

			for (std::size_t i = 0; i < n / sizeSubString; i++)
			{
				
				std::string l = std::string((sizeSubString * mc * 2) + sizeSubString, 'c');
				for (std::size_t j = 0; j < sizeSubString; j++)
				{
					rainbow::Hash_Chain hc = rainbow::Hash_Chain(mc);

					l.replace(j * ((2 * mc) + 2), (j * ((2 * mc) + 2) + (mc * 2 + 2)), hc.to_string());

				}
				mtx.lock();
				passwd_file << l;
				mtx.unlock();
			}

			passwd_file.close();
		}
		else
			throw std::runtime_error("Output files could not be opened");
	}

} //rainbow namespace
