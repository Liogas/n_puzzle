/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlgoStar.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:13:26 by glions            #+#    #+#             */
/*   Updated: 2026/02/06 12:49:29 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "AlgoStar.hpp"

AlgoStar::AlgoStar(const Node &start, const Node &goal):
	_start(start),
	_goal(goal),
	_heuristic(nullptr),
	_opened(),
	_closed(),
	_distances(),
	_heuristics()	
{
	std::cout << "AlgoStar default constructor called" << std::endl;
	this->_opened.push(start);
	this->_distances[this->_start] = 0;
	this->_heuristics[HeuristicType::Manhattan] = distManhattan;
	this->_heuristics[HeuristicType::LinearConflict] = distLinearConflict;
}

bool	AlgoStar::start(HeuristicType h)
{
	this->setHeuristic(h);
	if (this->_opened.size() != 1 || this->_closed.size() != 0)
	{
		std::cerr << "Algo already started" << std::endl;
		return (false);
	} 
	while (!this->_opened.empty())
	{
		Node curr = this->_opened.top();
		this->_opened.pop();
		if (curr == this->_goal)
			break;
		this->_closed.insert(curr);
		for (Node &n : curr.genNeighbors())
		{
			if (this->_closed.count(n))
        		continue;
			n.setG(this->_distances[curr] + 1);
			if (!this->_distances.count(n) || n.getG() < this->_distances[n])
			{
				this->_distances[n] = n.getG();
				n.setH(this->_heuristic(n, this->_goal));
				n.setF(n.getG() + n.getH());
				this->_opened.push(n);
			}
		}
	}
	std::cout << "Result : " << this->_distances[this->_goal] << std::endl;
	return (true);
}

void	AlgoStar::setHeuristic(HeuristicType h)
{
	this->_heuristic = this->_heuristics[h];
}