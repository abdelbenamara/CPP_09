/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:04:34 by abenamar          #+#    #+#             */
/*   Updated: 2024/06/27 02:20:25 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include "RPN.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: RPN expression" << std::endl;

		return (2);
	}

	try
	{
		std::cout << RPN::process(argv[1]) << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << e.what() << std::endl;

		return (1);
	}

	return (0);
}
