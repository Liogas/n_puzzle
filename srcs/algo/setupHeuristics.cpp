/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupHeuristics.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:52:25 by glions            #+#    #+#             */
/*   Updated: 2026/02/06 12:50:18 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setupHeurisitics.hpp"

int	distManhattan(const Node &a, const Node &b)
{
	int	size = b.getGrid().size();
	std::vector<int> mem(size * size, -1);
	int	dist = 0;

	for (size_t i = 0; (int)i < size; i++)
		for (size_t j = 0; (int)j < (int)b.getGrid()[i].size(); j++)
			mem[b.getGrid()[i][j]] = i * size + j;

	for (size_t i = 0; (int)i < size; i++)
	{
		for (size_t j = 0; (int)j < (int)a.getGrid()[i].size(); j++)
		{
			if (a.getGrid()[i][j] == 0)
				continue ;
			int	pos = mem[a.getGrid()[i][j]];
			dist += manhattan(i, j, pos / size, pos % size);
		}
	}
	return (dist);
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

int	distLinearConflict(const Node &a, const Node &b)
{
	int	dist = distManhattan(a, b);
	for (size_t i = 0; i < a.getGrid().size(); i++)
		dist += 2 * countLinearConflict(a.getGrid()[i], b.getGrid()[i]);
	return (dist);
}
