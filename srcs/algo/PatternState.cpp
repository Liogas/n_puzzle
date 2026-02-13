/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PatternState.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:39:29 by glions            #+#    #+#             */
/*   Updated: 2026/02/13 15:23:14 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PatternState.hpp"

PatternState::PatternState():
	_grid(),
	_blankIndex(-1)
{}

PatternState::PatternState(int size):
	_grid(),
	_blankIndex(-1)
{
	this->_grid.resize(size * size, -1);
}

std::vector<PatternState> PatternState::genNeighbors(int size) const
{
	std::vector<PatternState> ns;
	int y = this->_blankIndex / size;
	int x = this->_blankIndex % size;
	const int dirs[4][2] = {
		{-1,0},{1,0},{0,-1},{0,1}
	};
	for (auto &d : dirs)
	{
		int ny = y + d[0];
		int nx = x + d[1];
		if (ny < 0 || nx < 0 || ny >= size || nx >= size)
			continue ;
		int targetIndex = ny * size + nx;
		PatternState next = *this;
		int val = next.getGrid()[targetIndex];
		next.setValueGrid(this->_blankIndex, -1);
		next.setValueGrid(targetIndex, 0);
		next.setBlankIndex(targetIndex);
		if (val != -1)
			next.setValueGrid(this->_blankIndex, val);
		ns.push_back(next);
	} 
	return (ns);
}

PatternState	PatternState::makePatternState(
	const Node &node,
	const std::unordered_set<int> &pattern
)
{
	int	size = node.getGrid().size();
	PatternState ps(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int val = node.getGrid()[i][j];
			int idx = i * size + j;
			if (val == 0)
			{
				ps.setValueGrid(idx, val);
				ps.setBlankIndex(idx);
			}
			else if (pattern.count(val))
				ps.setValueGrid(idx, val);
			else
				ps.setValueGrid(idx, -1);
		}
	}
	return (ps);
}

bool PatternState::operator==(const PatternState &other) const
{
	return (this->_grid == other.getGrid());
}

std::vector<int>	PatternState::getGrid() const
{
	return (this->_grid);
}

void	PatternState::setValueGrid(int pos, int val)
{
	this->_grid[pos] = val;
}

void	PatternState::setBlankIndex(int pos)
{
	this->_blankIndex = pos;
}