/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:51:32 by abenamar          #+#    #+#             */
/*   Updated: 2024/06/25 20:36:33 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <vector>

class PmergeMe
{
public:
	static std::clock_t sort(std::deque<int> &sequence);
	static std::clock_t sort(std::vector<int> &sequence);

private:
	PmergeMe(void) throw();
	PmergeMe(PmergeMe const & /* src */) throw();
	virtual ~PmergeMe(void) throw();

	PmergeMe &operator=(PmergeMe const & /* rhs */) throw();

	template <typename Sequence>
	static int binary_search(int const value, Sequence const &sequence, int const size)
	{
		int left = 0;
		int right = size - 1;
		int idx = right / 2;

		while (left <= right)
		{
			if (sequence[idx] < value)
				left = idx + 1;
			else if (sequence[idx] > value)
				right = idx - 1;
			else
				break;

			if (right < 0)
				return (0);

			idx = (left + right) / 2;
		}

		return (idx + 1);
	}

	static void sort(std::deque<int> &sequence, std::deque<std::deque<int> > &pairs, int const size);
	static void sort(std::vector<int> &sequence, std::vector<std::vector<int> > &pairs, int const size);
};

#endif
