/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupHeuristics.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:52:25 by glions            #+#    #+#             */
/*   Updated: 2026/02/13 15:22:06 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setupHeurisitics.hpp"

int	distManhattan(
	const Node 								*a,
	const Node 								*b,
	const PatternDatabase					*pdb
)
{
	(void)pdb;
	int	size = b->getGrid().size();
	std::vector<int> mem(size * size, -1);
	int	dist = 0;

	for (size_t i = 0; (int)i < size; i++)
		for (size_t j = 0; (int)j < (int)b->getGrid()[i].size(); j++)
			mem[b->getGrid()[i][j]] = i * size + j;

	for (size_t i = 0; (int)i < size; i++)
	{
		for (size_t j = 0; (int)j < (int)a->getGrid()[i].size(); j++)
		{
			if (a->getGrid()[i][j] == 0)
				continue ;
			int	pos = mem[a->getGrid()[i][j]];
			dist += manhattan(i, j, pos / size, pos % size);
		}
	}
	return (dist);
}

int	distPDB(
	const Node 								*a,
	const Node 								*b,
	const PatternDatabase					*pdb
)
{
	(void)b;
	int	h = 0;

	for (size_t i = 0; i < pdb->getPatterns().size(); i++)
	{
		const PDBTable table = pdb->getPDBs()[i];
		PatternState key(a->getGrid().size());
		key.makePatternState(*a, pdb->getPatterns()[i]);
		auto it = table.find(key);
		if (it != table.end())
			h += it->second;
		else
			h += 0;
	}
	return (h);
}

static std::vector<int> genOrderTargetLine(const std::vector<int> &lineA,
	const std::vector<int> &lineB)
{
	std::vector<int>	orderTarget;

	for (size_t i = 0; i < lineA.size(); i++)
	{
		if (lineA[i] == 0)
			continue ;
		for (size_t j = 0; j < lineB.size(); j++)
			if (lineA[i] == lineB[j])
				orderTarget.push_back(j);
	}
	return (orderTarget);
}

static int	countLinearConflict(const std::vector<int> &lineA,
	const std::vector<int> &lineB)
{
	std::vector<int> orderTarget = genOrderTargetLine(lineA, lineB);
	int	conflicts = 0;

	for (size_t i = 0; i < orderTarget.size(); i++)
		for (size_t j = i + 1; j < orderTarget.size(); j++)
			if (orderTarget[i] > orderTarget[j])
				conflicts++;
	return (conflicts);
}

int	distLinearConflict(
	const Node 								*a,
	const Node 								*b,
	const PatternDatabase					*pdb
)
{
	int	dist = distManhattan(a, b, pdb);
	for (size_t i = 0; i < a->getGrid().size(); i++)
		dist += 2 * countLinearConflict(a->getGrid()[i], b->getGrid()[i]);
	for (size_t i = 0; i < a->getGrid().size(); i++)
	{
		std::vector<int> colA;
		std::vector<int> colB;
		for (size_t j = 0; j < a->getGrid().size(); j++)
		{
			colA.push_back(a->getGrid()[j][i]);
			colB.push_back(b->getGrid()[j][i]);
		}
		dist += 2 * countLinearConflict(colA, colB);
	}
	return (dist);
}





