// OTUS_HW_ip_filter.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdarg.h>

using namespace std;

using ip_string = std::vector<std::string>;
using ip_vector = std::vector< ip_string >;

ip_string split(const std::string &str, char d)
{
	ip_string r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while (stop != std::string::npos)
	{
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

void printIpString(const ip_string& ip)
{
	size_t szCount = 0;
	for (const auto ip_part : ip)
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
	for (const auto ip : ip_pool)
	{
		printIpString(ip);
	}
}

void printIpList(const ip_vector& ip_pool, const short int firstByte)
{
	for (const auto ip : ip_pool)
	{
		if (firstByte == stoi(ip[0]))
		{
			printIpString(ip);
		}
	}
}

void printIpList(const ip_vector& ip_pool, const short int firstByte, const short int secondByte)
{
	for (const auto ip : ip_pool)
	{
		if (firstByte == stoi(ip[0]) &&
			secondByte == stoi(ip[1]))
		{
			printIpString(ip);
		}
	}
}

void printIpList_any(const ip_vector& ip_pool, const short int anyByte)
{
	for (const auto ip : ip_pool)
	{
		if (anyByte == stoi(ip[0]) ||
			anyByte == stoi(ip[1]) || 
			anyByte == stoi(ip[2]) || 
			anyByte == stoi(ip[3]))
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
			ip_string v = split(line, '\t');
			ip_pool.push_back(split(v.at(0), '.'));
		}

		// TODO reverse lexicographically sort
		struct {
			bool operator()(ip_string a, ip_string b) const
			{
				bool res = false;
				for (size_t i = 0; i < a.size(); ++i)
				{
					int ip1_byte = stoi(a[i]);
					int ip2_byte = stoi(b[i]);
				
					if (ip1_byte > ip2_byte)
					{
						res = true;
						break;
					}
					else if(ip1_byte < ip2_byte)
					{
						res = false;
						break;
					}
				}					
				return res;
			}
		} ipSort;
		std::sort(ip_pool.begin(), ip_pool.end(), ipSort);
		
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