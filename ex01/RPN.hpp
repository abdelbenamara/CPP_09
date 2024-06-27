/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:00:23 by abenamar          #+#    #+#             */
/*   Updated: 2024/06/27 02:20:02 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RPN_HPP__
#define __RPN_HPP__

#include <list>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

class RPN
{
public:
	static int process(std::string const &expression) throw(std::invalid_argument);

private:
	RPN(void);
	RPN(RPN const & /* src */);
	~RPN(void);

	RPN operator=(RPN const & /* rhs */);
};

#endif
