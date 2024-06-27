/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:03:00 by abenamar          #+#    #+#             */
/*   Updated: 2024/06/27 02:20:19 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void) { return; }

RPN::RPN(RPN const & /* src */) { return; }

RPN::~RPN(void) { return; }

RPN RPN::operator=(RPN const & /* rhs */) { return (*this); }

int RPN::process(std::string const &expression) throw(std::invalid_argument)
{
	std::string const tokens("0123456789+-/*");
	std::stringstream sstream(expression);
	std::string str;
	std::stack<int, std::list<int> > stack;
	int item;

	while (sstream.good())
	{
		sstream >> str;

		if (sstream.fail() || str.length() != 1 || tokens.find(str.at(0)) == std::string::npos)
			throw std::invalid_argument("Error: invalid expression");
		else if (tokens.find(str.at(0), 10) != std::string::npos)
		{
			if (stack.empty())
				throw std::invalid_argument("Error: invalid expression");

			item = stack.top();

			stack.pop();

			if (stack.empty())
				throw std::invalid_argument("Error: invalid expression");

			switch (str.at(0))
			{
			case '+':
				item = stack.top() + item;

				break;

			case '-':
				item = stack.top() - item;

				break;

			case '/':
				if (item == 0)
					throw std::invalid_argument("Error: division by zero");

				item = stack.top() / item;

				break;

			// case '*':
			default:
				item = stack.top() * item;

				break;
			}

			stack.pop();
			stack.push(item);
		}
		else
			stack.push(str.at(0) - '0');
	}

	item = stack.top();

	stack.pop();

	if (!stack.empty())
		throw std::invalid_argument("Error: invalid expression");

	return (item);
}
