/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupHeuristics.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:52:25 by glions            #+#    #+#             */
/*   Updated: 2026/02/05 19:34:21 by glions           ###   ########.fr       */
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
