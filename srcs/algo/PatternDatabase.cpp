/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PatternDatabase.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:26:25 by glions            #+#    #+#             */
/*   Updated: 2026/02/13 15:22:47 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PatternDatabase.hpp"

PatternDatabase::PatternDatabase():
	_patterns(),
	_PDBs()
{}


PDBTable	PatternDatabase::buildPDB(const Node &goal, std::unordered_set<int> &pattern)
{
	PDBTable	pdb;

	std::queue<PatternState> q;
	std::unordered_map<PatternState, int, PatternHash> dist;
	PatternState g(goal.getGrid().size());
	g.makePatternState(goal, pattern);
	q.push(g);
	dist[g] = 0;
	pdb[g] = 0;
	while (!q.empty())
	{
		PatternState curr = q.front();
		q.pop();
		for (auto &next : curr.genNeighbors(goal.getGrid().size()))
		{
			if (!dist.count(next))
			{
				dist[next] = dist[curr]+ 1;
				pdb[next] = dist[next];
				q.push(next);
			}
		}
	}
	return (pdb);
}

void	PatternDatabase::buildAllPDBs(const Node &goal)
{
	for (auto &pattern : this->_patterns)	
		this->_PDBs.push_back(this->buildPDB(goal, pattern));
}

void	PatternDatabase::buildPatterns(int size)
{
	int	n = size * size - 1;
	int	patternSize = std::min(6, n);
	std::unordered_set<int> currPattern;
	for (int tile = 1; tile <= n; tile++)
	{
		currPattern.insert(tile);
		if ((int)currPattern.size() == patternSize)
		{
			this->_patterns.push_back(currPattern);
			currPattern.clear();
		}
	}
	if (!currPattern.empty())
		this->_patterns.push_back(currPattern);
}

std::vector<std::unordered_set<int>>	PatternDatabase::getPatterns() const
{
	return (this->_patterns);
}


std::vector<PDBTable>	PatternDatabase::getPDBs() const
{
	return (this->_PDBs);
}