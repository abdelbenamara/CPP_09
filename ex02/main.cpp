/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:38:47 by abenamar          #+#    #+#             */
/*   Updated: 2024/06/24 22:34:22 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <ctime>
#include <deque>
#include <iostream>
#include <sstream>
#include <vector>
#include "PmergeMe.hpp"

bool isValidInput(int const argc, char const *const *const argv)
{
	std::stringstream sstream;
	int element;
	std::string value;

	for (int i = 1; i < argc; ++i)
	{
		sstream << argv[i];
		sstream >> element;

		if (sstream.fail() || element < 0)
		{
			std::cout << "Error: invalid input: `" << argv[i] << "'" << std::endl;

			return (false);
		}

		sstream.clear();

		sstream << element;
		sstream >> value;

		if (value != argv[i])
		{
			std::cout << "Error: invalid input: `" << argv[i] << "'" << std::endl;

			return (false);
		}

		sstream.clear();
	}

	return (true);
}

template <typename Sequence>
std::clock_t fill(Sequence &sequence, int const argc, char const *const *const argv)
{
	std::stringstream sstream;
	int element;
	std::clock_t t = std::clock();

	for (int i = 1; i < argc; ++i)
	{
		sstream << argv[i];
		sstream >> element;

		sequence.push_back(element);
		sstream.clear();
	}

	return (std::clock() - t);
}

template <typename InputIterator>
void print(char const *const prefix, InputIterator begin, InputIterator end)
{
	std::cout << prefix;

	for (InputIterator it = begin; it != end; ++it)
		std::cout << *it << ' ';

	std::cout << std::endl;
}

template <typename SizeType>
void stats(SizeType const size, char const *const type, std::clock_t const elapsed) { std::cout << "Time to process a range of " << size << " elements with " << type << " : " << elapsed << " us" << std::endl; }

int main(int argc, char *argv[])
{
	std::clock_t t0, t1, t2, t3;
	std::vector<int> vector;
	std::deque<int> deque;

	if (argc < 2)
	{
		std::cout << "Usage: PmergeMe positive-integer1 ... positive-integerN" << std::endl;

		return (2);
	}

	if (!::isValidInput(argc, argv))
		return (1);

	t0 = ::fill(vector, argc, argv);

	::print("Before: ", vector.begin(), vector.end());

	t1 = std::clock();

	PmergeMe::sort(vector);

	t1 = std::clock() - t1;

	if (*std::min_element(vector.begin(), vector.end()) != vector.front() || *std::max_element(vector.begin(), vector.end()) != vector.back())
	{
		std::cout << "Error: range of " << vector.size() << " elements with std::vector is not sorted" << std::endl;

		return (1);
	}

	t2 = ::fill(deque, argc, argv);
	t3 = std::clock();

	PmergeMe::sort(deque);

	t3 = std::clock() - t3;

	if (*std::min_element(deque.begin(), deque.end()) != deque.front() || *std::max_element(deque.begin(), deque.end()) != deque.back())
	{
		std::cout << "Error: range of " << deque.size() << " elements with std::deque is not sorted" << std::endl;

		return (1);
	}

	::print("After:  ", vector.begin(), vector.end());
	::stats(vector.size(), "std::vector", t0 + t1);
	::stats(deque.size(), "std::deque ", t2 + t3);

	return (0);
}
