/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:40:23 by abenamar          #+#    #+#             */
/*   Updated: 2024/06/17 11:56:04 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BITCOINEXCHANGE_HPP__
#define __BITCOINEXCHANGE_HPP__

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include <utility>

class BitcoinExchange
{
public:
	static std::pair<std::string, float> const parse(std::string const &input) throw(std::invalid_argument);
	static std::string const compute(std::string const &date, float const amount, std::map<std::string, float> const &database);

private:
	BitcoinExchange(void) throw();
	BitcoinExchange(BitcoinExchange const & /* src */) throw();
	virtual ~BitcoinExchange(void) throw();

	BitcoinExchange &operator=(BitcoinExchange const & /* rhs */) throw();
};

#endif
