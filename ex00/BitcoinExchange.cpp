/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:41:15 by abenamar          #+#    #+#             */
/*   Updated: 2024/06/18 01:09:18 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) throw() { return; }

BitcoinExchange::BitcoinExchange(BitcoinExchange const & /* src */) throw() { return; }

BitcoinExchange::~BitcoinExchange(void) throw() { return; }

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const & /* rhs */) throw() { return (*this); }

std::pair<std::string, float> const BitcoinExchange::parse(std::string const &input) throw(std::invalid_argument)
{
	std::stringstream line(input);
	std::string date, tmp;
	float amount;
	int year(0), month(0), day(0);

	line >> date >> tmp >> amount;

	if (!line.eof() || line.fail() || tmp != "|" || std::count(date.begin(), date.end(), '-') != 2)
		throw std::invalid_argument(std::string("Error: bad input => ") + input);

	tmp = date;

	std::replace(tmp.begin(), tmp.end(), '-', ' ');
	line.clear();
	line.str(tmp);

	line >> year >> month >> day;

	switch (month)
	{
	case 2:
		if ((year % 4 != 0 || (year % 100 == 0 && year % 400 != 0)) && day > 28)
			tmp.clear();
		else if (day > 29)
			tmp.clear();

		break;

	case 4:
	case 6:
	case 9:
	case 11:
		if (day > 30)
			tmp.clear();

		break;

	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (day > 31)
			tmp.clear();

		break;

	default:
		tmp.clear();

		break;
	}

	if (day < 1 || tmp.empty())
		throw std::invalid_argument(std::string("Error: invalid date => ") + date);

	if (amount < 0.0F)
		throw std::invalid_argument("Error: not a positive number.");

	if (amount > 1000.0F)
		throw std::invalid_argument("Error: too large a number.");

	return (std::make_pair(date, amount));
}

std::string const BitcoinExchange::compute(std::string const &date, float const amount, std::map<std::string, float> const &database)
{
	float rate;
	std::ostringstream o;

	try
	{
		rate = database.at(date);
	}
	catch (const std::out_of_range &e)
	{
		std::map<std::string, float>::const_iterator it;

		for (it = database.begin(); it != database.end() && it->first < date; ++it)
			;

		if (it != database.begin())
			--it;

		rate = it->second;
	}

	o << date << " => " << amount << " = " << (rate * amount);

	return (o.str());
}
