/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:54:20 by abenamar          #+#    #+#             */
/*   Updated: 2024/06/24 22:33:49 by abenamar         ###   ########.fr       */
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

	std::deque<std::deque<int> > tmp;

	for (i = 0; i < limit; ++i)
	{
		tmp.push_back(std::deque<int>(1, deque.front()));
		deque.pop_front();
		tmp.back().push_back(deque.front());
		deque.pop_front();
	}

	if (!even)
	{
		tmp.push_back(std::deque<int>(1, deque.front()));
		deque.pop_front();
	}

	pairs.insert(pairs.begin(), tmp.begin(), tmp.end());

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 2 */

	for (i = 0; i < limit; ++i)
		if (pairs.at(i).front() > pairs.at(i).back())
			std::swap(pairs.at(i).front(), pairs.at(i).back());

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 3 */

	std::deque<std::deque<int> >::iterator it = pairs.begin();

	for (i = 0; i < limit; ++i)
	{
		deque.push_back(it->back());

		++it;
	}

	if (limit > 1)
		PmergeMe::sort(deque, pairs, limit);

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 4 */

	int j;

	for (i = 0; i < limit; ++i)
	{
		it = pairs.begin() + i;

		for (j = i; j < limit; ++j)
		{
			if (deque.at(i) == it->back())
			{
				pairs.insert(pairs.begin() + i, *it);
				pairs.erase(it + 1);

				break;
			}

			++it;
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

	std::vector<std::vector<int> > tmp;

	if (!even)
	{
		tmp.push_back(std::vector<int>(1, vector.back()));
		vector.pop_back();
	}

	for (i = 0; i < limit; ++i)
	{
		tmp.push_back(std::vector<int>(1, vector.back()));
		vector.pop_back();
		tmp.back().push_back(vector.back());
		vector.pop_back();
	}

	pairs.insert(pairs.end(), tmp.begin(), tmp.end());

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 2 */

	for (i = 0; i < limit; ++i)
		if (pairs.at(i).front() > pairs.at(i).back())
			std::swap(pairs.at(i).front(), pairs.at(i).back());

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 3 */

	std::vector<std::vector<int> >::iterator it = pairs.end();

	for (i = 0; i < limit; ++i)
		vector.push_back((--it)->back());

	if (limit > 1)
		PmergeMe::sort(vector, pairs, limit);

	/* https://en.wikipedia.org/wiki/Merge-insertion_sort#Algorithm -> step 4 */

	int j;

	for (i = 0; i < limit; ++i)
	{
		it = pairs.end() - i - 1;

		for (j = i; j < limit; ++j)
		{
			if (vector.at(i) == it->back())
			{
				pairs.insert(pairs.end() - limit + i + 1, *it);
				pairs.erase(it);

				break;
			}

			--it;
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

void PmergeMe::sort(std::deque<int> &sequence)
{
	std::deque<std::deque<int> > pairs;

	if (sequence.size() == 0)
		return;

	PmergeMe::sort(sequence, pairs, sequence.size());

	return;
}

void PmergeMe::sort(std::vector<int> &sequence)
{
	std::vector<std::vector<int> > pairs;

	if (sequence.size() == 0)
		return;

	PmergeMe::sort(sequence, pairs, sequence.size());

	return;
}
