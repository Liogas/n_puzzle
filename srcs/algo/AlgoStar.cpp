/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlgoStar.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:13:26 by glions            #+#    #+#             */
/*   Updated: 2026/02/02 12:06:19 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "AlgoStar.hpp"

AlgoStar::AlgoStar(const Node &start, const Node &goal):
	_start(start),
	_goal(goal),
	_opened(),
	_closed(),
	_heuristics()
{
	std::cout << "AlgoStar default constructor called" << std::endl;
	this->_opened.push(start);
}

bool	AlgoStar::addHeuristic(HeuristicType h, Heuristic fn)
{
	if (this->_heuristics.find(h) != this->_heuristics.end())
	{
		std::cerr << "Heuristic already stocked" << std::endl;
		return (false);
	}
	this->_heuristics[h] = fn;
	return (true);
}

bool	AlgoStar::start(HeuristicType h)
{
	if (this->_heuristics.find(h) == this->_heuristics.end())
	{
		std::cerr << "Heuristic unknown" << std::endl;
		return (false);
	}
	return (true);
}