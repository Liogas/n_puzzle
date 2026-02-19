/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:29:50 by glions            #+#    #+#             */
/*   Updated: 2026/02/19 15:37:33 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.hpp"

int manhattan(const NPuzzleState &s, const NPuzzleState &g)
{
	int	h = 0;
	for (size_t i = 0; i < s.board.size(); i++)
	{
		if (s.board[i] == 0) continue;
		size_t goalIndex = std::find(g.board.begin(),
			g.board.end(), s.board[i]) - g.board.begin();
		int curRow = i / s.size, curCol = i % s.size;
		int	goalRow = goalIndex / s.size, goalCol = goalIndex % s.size;
		h += std::abs(curRow - goalRow) + std::abs(curCol - goalCol);
	}	
	return (h);
}
