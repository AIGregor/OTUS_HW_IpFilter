// OTUS_HW_ip_filter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include <cassert>
//#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

using ip_string = std::vector<std::string>;
using ip_int = std::vector<int>;
using ip_vector = std::vector< ip_int >;

template <typename T>
std::vector<T> split(const std::string &str, char d)
{
	std::vector<T> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while (stop != std::string::npos)
	{
		r.push_back(
			ConvertString<T>(str.substr(start, stop - start))
		);

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}
	r.push_back(
		ConvertString<T>(str.substr(start))
	);

	return r;
}

template <typename T>
T ConvertString(const std::string &data)
{
	if (!data.empty())
	{
		T ret;
		std::istringstream iss(data);
		iss >> std::dec >> ret;

		if (iss.fail())
		{
			return T();
		}
		return ret;
	}
	return T();
}

void printIpString(const ip_int& ip)
{
	size_t szCount = 0;
	for (const auto& ip_part : ip)
	{
		std::cout << ip_part;
		++szCount;

		if (szCount < ip.size())
		{
			std::cout << ".";
		}
	}
	std::cout << std::endl;
}

void printIpList(const ip_vector& ip_pool)
{
	for (const auto& ip : ip_pool)
	{
		printIpString(ip);
	}
}

void printIpList(const ip_vector& ip_pool, const short int firstByte)
{
	for (const auto& ip : ip_pool)
	{
		if (firstByte == ip[0])
		{
			printIpString(ip);
		}
	}
}

void printIpList(const ip_vector& ip_pool, const short int firstByte, const short int secondByte)
{
	for (const auto& ip : ip_pool)
	{
		if (firstByte == ip[0] &&
			secondByte == ip[1])
		{
			printIpString(ip);
		}
	}
}

void printIpList_any(const ip_vector& ip_pool, const short int anyByte)
{
	for (const auto ip : ip_pool)
	{
		if (anyByte == ip[0] ||
			anyByte == ip[1] || 
			anyByte == ip[2] || 
			anyByte == ip[3])
		{
			printIpString(ip);
		}
	}
}

int main(int argc, char const *argv[])
{
	try
	{
		ip_vector ip_pool;

		for (std::string line; std::getline(std::cin, line);)
		{
			ip_string v = split<string>(line, '\t');
			ip_int ip = split<int>(v.at(0), '.');

			ip_pool.push_back(ip);
		}

		// TODO reverse lexicographically sort
		std::sort(ip_pool.begin(), ip_pool.end(), 
			[](const ip_int& a,const ip_int& b) {				
				int i = 0;
				int size = a.size() - 1;
				while (i < size && a[i] == b[i])
				{
					++i;
				}
				return a[i] > b[i];
			}
		);
		
		// Sorted vector
		printIpList(ip_pool);

		// Filter by first byte equal 1
		printIpList(ip_pool, 1);

		// Filter by first byte equal 46 and second byte equal 70
		printIpList(ip_pool, 46, 70);

		// Filter by any byte and output
		printIpList_any(ip_pool, 46);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}