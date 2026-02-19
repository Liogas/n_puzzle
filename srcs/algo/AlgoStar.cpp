/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlgoStar.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:13:26 by glions            #+#    #+#             */
/*   Updated: 2026/02/19 12:27:07 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "AlgoStar.hpp"



	
AlgoStar::AlgoStar(const Node &start, const Node &goal):
	_expandedNodes(0),
	_maxStates(0),
	_start(start),
	_goal(goal),
	_heuristic(nullptr),
	_opened(),
	_closed(),
	_distances(),
	_fathers(),
	_heuristics(),
	_pdb()
{
	std::cout << "AlgoStar default constructor called" << std::endl;
	this->_opened.push(start);
	this->_distances[this->_start] = 0;
	this->_heuristics[HeuristicType::Manhattan] = distManhattan;
	this->_heuristics[HeuristicType::LinearConflict] = distLinearConflict;
	this->_heuristics[HeuristicType::PDB] = distPDB;
}

void	AlgoStar::showResult()
{
	std::cout << "Result: "<< std::endl;
	std::cout << "Time complexity: " << this->_expandedNodes << std::endl;
	std::cout << "Size complexity: " << this->_maxStates << std::endl;
	std::cout << "Number of moves: " << this->_distances[this->_goal] << std::endl;
	std::cout << "Path: " << std::endl;
	std::deque<Node> path;
	Node curr = this->_goal;
	while (curr != this->_start)
	{
		path.push_front(curr);
		curr = this->_fathers[curr];
	}
	path.push_front(this->_start);
	for (const Node &n : path)
		std::cout << n << std::endl << std::endl;
}

bool	AlgoStar::start(HeuristicType h)
{
	this->setHeuristic(h);
	if (this->_opened.size() != 1 || this->_closed.size() != 0)
	{
		std::cerr << "Algo already started" << std::endl;
		return (false);
	} 
	if (h == HeuristicType::PDB)
	{
		this->_pdb.buildPatterns(this->_goal.getGrid().size());
		this->_pdb.buildAllPDBs(this->_goal);
	}
	while (!this->_opened.empty())
	{
		Node curr = this->_opened.top();
		this->_opened.pop();
		this->_expandedNodes++;
		if (this->_opened.size() + this->_closed.size() > (unsigned long)this->_maxStates)
			this->_maxStates = this->_opened.size() + this->_closed.size();
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
				this->_fathers[n] =  curr;
				int	distH = this->calcHeuristic(n);
				if (distH == -1)
				{
					std::cerr << "Calc heuristic crashed" << std::endl;
					return (false);
				}
				n.setH(distH);
				n.setF(n.getG() + n.getH());
				this->_opened.push(n);
			}
		}
	}
	this->showResult();
	return (true);
}

int			AlgoStar::calcHeuristic(const Node &n)
{
	switch (this->_heuristicT)
	{
		case HeuristicType::Manhattan:
			return (this->_heuristic(&n, &this->_goal, nullptr));
			break ;
		case HeuristicType::LinearConflict:
			return (this->_heuristic(&n, &this->_goal, nullptr));
			break ;
		case HeuristicType::PDB:
			return (this->_heuristic(&n, nullptr, &this->_pdb));
			break ;
		default:
			return (-1);
	}
}



void	AlgoStar::setHeuristic(HeuristicType h)
{
	this->_heuristic = this->_heuristics[h];
	this->_heuristicT = h;
}