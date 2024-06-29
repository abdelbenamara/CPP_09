/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:54:20 by abenamar          #+#    #+#             */
/*   Updated: 2024/06/29 19:19:51 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) throw() { return; }

PmergeMe::PmergeMe(PmergeMe const & /* src */) throw() { return; }

PmergeMe::~PmergeMe(void) throw() { return; }

PmergeMe &PmergeMe::operator=(PmergeMe const & /* rhs */) throw() { return (*this); }

void PmergeMe::sort(std::deque<int> &deque, std::deque<std::deque<int> > &pairs, int const size)
{
	bool const even = (size % 2 == 0);
	int limit = size / 2;
	int i;

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 1 */

	if (!even)
	{
		pairs.push_front(std::deque<int>(1, deque.front()));
		deque.pop_front();
	}

	for (i = 0; i < limit; ++i)
	{
		pairs.push_front(std::deque<int>(1, deque.front()));
		deque.pop_front();
		pairs.front().push_front(deque.front());
		deque.pop_front();
	}

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 2 */

	std::deque<std::deque<int> >::iterator it;

	for (i = 0, it = pairs.begin(); i < limit; ++i, ++it)
		if (it->front() > it->back())
			std::swap(it->front(), it->back());

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 3 */

	for (i = 0, it = pairs.begin(); i < limit; ++i, ++it)
		deque.push_back(it->back());

	if (limit > 1)
		PmergeMe::sort(deque, pairs, limit);

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 4 */

	int j;

	for (i = 0; i < limit; ++i)
	{
		for (j = i, it = pairs.begin() + i; j < limit; ++j, ++it)
		{
			if (deque.at(i) == it->back())
			{
				pairs.insert(pairs.begin() + i, *it);
				pairs.erase(pairs.begin() + j + 1);

				break;
			}
		}
	}

	deque.push_front(pairs.front().front());
	pairs.pop_front();

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 5 */

	int e = 2;
	int pos = limit;
	int end;

	limit *= 2;
	j = 2;

	if (even)
		--limit;

	while (pos < limit)
	{
		end = std::min(j, limit - pos);
		it = pairs.begin() + end - 1;

		for (i = end - 1; i >= 0; --i)
		{
			deque.insert(deque.begin() + PmergeMe::binary_search(it->front(), deque, pos + end - i), it->front());

			it = pairs.erase(it) - 1;
		}

		pos += j;
		j = std::pow(2.0F, e) - j;
		++e;
	}

	return;
}

void PmergeMe::sort(std::vector<int> &vector, std::vector<std::vector<int> > &pairs, int const size)
{
	bool const even = (size % 2 == 0);
	int limit = size / 2;
	int i;

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 1 */

	if (!even)
	{
		pairs.push_back(std::vector<int>(1, vector.back()));
		vector.pop_back();
	}

	for (i = 0; i < limit; ++i)
	{
		pairs.push_back(std::vector<int>(1, vector.back()));
		vector.pop_back();
		pairs.back().push_back(vector.back());
		vector.pop_back();
	}

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 2 */

	std::vector<std::vector<int> >::iterator it;

	for (i = 0, it = pairs.end() - 1; i < limit; ++i, --it)
		if (it->front() > it->back())
			std::swap(it->front(), it->back());

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 3 */

	for (i = 0, it = pairs.end() - 1; i < limit; ++i, --it)
		vector.push_back(it->back());

	if (limit > 1)
		PmergeMe::sort(vector, pairs, limit);

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 4 */

	int j;

	for (i = 0; i < limit; ++i)
	{
		for (j = i, it = pairs.end() - 1 - i; j < limit; ++j, --it)
		{
			if (vector.at(i) == it->back())
			{
				pairs.insert(pairs.end() - i, *it);
				pairs.erase(pairs.end() - j - 2);

				break;
			}
		}
	}

	vector.insert(vector.begin(), pairs.back().front());
	pairs.pop_back();

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 5 */

	int e = 2;
	int pos = limit;
	int end;

	limit *= 2;
	j = 2;

	if (even)
		--limit;

	while (pos < limit)
	{
		end = std::min(j, limit - pos);
		it = pairs.end() - 1;

		for (i = end - 1; i >= 0; --i)
		{
			vector.insert(vector.begin() + PmergeMe::binary_search(it->front(), vector, pos + end - i), it->front());

			it = pairs.erase(it) - 1;
		}

		pos += j;
		j = std::pow(2.0F, e) - j;
		++e;
	}

	return;
}

std::clock_t PmergeMe::sort(std::deque<int> &sequence)
{
	std::clock_t t = std::clock();
	std::deque<std::deque<int> > pairs;

	if (sequence.size() == 0)
		return (0);

	PmergeMe::sort(sequence, pairs, sequence.size());

	return (std::clock() - t);
}

std::clock_t PmergeMe::sort(std::vector<int> &sequence)
{
	std::clock_t t = std::clock();
	std::vector<std::vector<int> > pairs;

	if (sequence.size() == 0)
		return (0);

	PmergeMe::sort(sequence, pairs, sequence.size());

	return (std::clock() - t);
}
