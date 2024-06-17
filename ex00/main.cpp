/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:12:38 by abenamar          #+#    #+#             */
/*   Updated: 2024/06/17 22:00:11 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include "BitcoinExchange.hpp"

bool initDatabase(std::ifstream &dfs, std::map<std::string, float> &database)
{
	std::string line;
	float price;

	std::getline(dfs, line);

	while (std::getline(dfs, line, ','))
	{
		if (dfs.fail())
			return (false);

		dfs >> price;

		if (dfs.fail())
			return (false);

		database[line] = price;

		std::getline(dfs, line, '\n');

		if (dfs.fail())
			return (false);
	}

	return (true);
}

void evaluateInput(std::ifstream &ifs, std::map<std::string, float> const &database)
{
	std::string line;
	std::pair<std::string, float> da;

	std::getline(ifs, line);

	while (std::getline(ifs, line))
	{
		try
		{
			da = BitcoinExchange::parse(line);

			std::cout << BitcoinExchange::compute(da.first, da.second, database) << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	return;
}

int main(int argc, char *argv[])
{
	std::ifstream ifs, dfs;
	std::map<std::string, float> database;

	if (argc < 2)
	{
		std::cerr << "Usage: btc filename" << std::endl;

		return (2);
	}

	dfs.open("data.csv");

	if (!dfs.is_open())
	{
		std::cerr << "Error: unable to open `data.csv'" << std::endl;

		return (1);
	}

	ifs.open(argv[1]);

	if (!ifs.is_open())
	{
		std::cerr << "Error: unable to open `" << argv[1] << '\'' << std::endl;

		dfs.close();

		return (1);
	}

	if (!::initDatabase(dfs, database))
	{
		std::cerr << "Error: fail to init database" << std::endl;

		return (1);
	}

	::evaluateInput(ifs, database);
	dfs.close();
	ifs.close();

	return (0);
}
